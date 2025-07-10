#include <iostream>
#include <signal.h>
#include <syslog.h>
#include <unistd.h>

#include "rtsp_demo.h"
#include "video.h"

static CVI_VOID app_ipcam_ExitSig_handle(CVI_S32 signo) {
    signal(SIGINT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);

    if ((SIGINT == signo) || (SIGTERM == signo)) {
        deinitVideo();
        deinitRtsp();
        APP_PROF_LOG_PRINT(LEVEL_INFO, "ipcam receive a signal(%d) from terminate\n", signo);
    }

    exit(-1);
}

static int fpSaveVencFrame(void* pData, void* pArgs, void* pUserData) {
    VENC_STREAM_S* pstStream = (VENC_STREAM_S*)pData;

    APP_DATA_CTX_S* pstDataCtx        = (APP_DATA_CTX_S*)pArgs;
    APP_DATA_PARAM_S* pstDataParam    = &pstDataCtx->stDataParam;
    APP_VENC_CHN_CFG_S* pstVencChnCfg = (APP_VENC_CHN_CFG_S*)pstDataParam->pParam;

    static uint32_t count = 0;
    /* dynamic touch a file: /tmp/rec then start save sreaming to flash or SD Card */
    /*if (access("/tmp/rec", F_OK) == 0)*/ {
        if (pstVencChnCfg->pFile == NULL) {
            char szFilePath[100] = {0};

            sprintf(szFilePath,
                    "/userdata/local/VENC%d_%d%s",
                    pstVencChnCfg->VencChn,
                    count++,
                    app_ipcam_Postfix_Get(pstVencChnCfg->enType));
            count %= 10;
            APP_PROF_LOG_PRINT(LEVEL_INFO, "start save file to %s\n", szFilePath);
            pstVencChnCfg->pFile = fopen(szFilePath, "wb");
            if (pstVencChnCfg->pFile == NULL) {
                APP_PROF_LOG_PRINT(LEVEL_ERROR, "open file err, %s\n", szFilePath);
                return CVI_FAILURE;
            }
        }

        VENC_PACK_S* ppack;
        /* just from I-frame saving */
        if ((pstVencChnCfg->enType == PT_H264) || (pstVencChnCfg->enType == PT_H265)) {
            if (pstVencChnCfg->fileNum == 0 && pstStream->u32PackCount < 2) {
                APP_PROF_LOG_PRINT(LEVEL_INFO, "skip first I-frame\n");
                return CVI_SUCCESS;
            }
        }
        for (CVI_U32 i = 0; i < pstStream->u32PackCount; i++) {
            ppack = &pstStream->pstPack[i];
            fwrite(ppack->pu8Addr + ppack->u32Offset,
                   ppack->u32Len - ppack->u32Offset,
                   1,
                   pstVencChnCfg->pFile);

            APP_PROF_LOG_PRINT(
                LEVEL_DEBUG,
                "pack[%d], PTS = %lu, Addr = %p, Len = 0x%X, Offset = 0x%X DataType=%d\n",
                i,
                ppack->u64PTS,
                ppack->pu8Addr,
                ppack->u32Len,
                ppack->u32Offset,
                ppack->DataType.enH265EType);
        }

        if (pstVencChnCfg->enType == PT_JPEG) {
            fclose(pstVencChnCfg->pFile);
            pstVencChnCfg->pFile = NULL;
            APP_PROF_LOG_PRINT(LEVEL_INFO, "End save! \n");
            // remove("/tmp/rec");
        } else {
            if (++pstVencChnCfg->fileNum > pstVencChnCfg->u32Duration) {
                pstVencChnCfg->fileNum = 0;
                fclose(pstVencChnCfg->pFile);
                pstVencChnCfg->pFile = NULL;
                APP_PROF_LOG_PRINT(LEVEL_INFO, "End save! \n");
                // remove("/tmp/rec");
            }
        }
    }

    return CVI_SUCCESS;
}

static int fpSaveVpssFrame(void* pData, void* pArgs, void* pUserData) {
    APP_VENC_CHN_CFG_S* pstVencChnCfg = (APP_VENC_CHN_CFG_S*)pArgs;
    VIDEO_FRAME_INFO_S* VpssFrame     = (VIDEO_FRAME_INFO_S*)pData;
    VIDEO_FRAME_S* f                  = &VpssFrame->stVFrame;

    char name[32]         = "";
    static uint32_t count = 0;
    snprintf(
        name, sizeof(name), "/mnt/sd/%d_%dx%d%s", count++, f->u32Width, f->u32Height, pUserData);
    if (count >= 10) {
        count = 0;
    }
    APP_PROF_LOG_PRINT(LEVEL_INFO, "save frame to %s\n", name);

    FILE* fp = fopen(name, "w");
    if (fp == CVI_NULL) {
        CVI_TRACE_LOG(CVI_DBG_ERR, "open data file error\n");
        return CVI_FAILURE;
    }

    for (uint32_t i = 0; i < 3; i++) {
        if (f->u32Length[i]) {
            f->pu8VirAddr[i] = (CVI_U8*)CVI_SYS_Mmap(f->u64PhyAddr[i], f->u32Length[i]);
            if (fwrite(f->pu8VirAddr[i], f->u32Length[i], 1, fp) <= 0) {
                CVI_TRACE_LOG(CVI_DBG_ERR, "fwrite data(%d) error\n", f->u32TimeRef);
            }
            CVI_SYS_Munmap(f->pu8VirAddr[i], f->u32Length[i]);
        }
    }

    fclose(fp);

    return CVI_SUCCESS;
}

int main(int argc, char* argv[]) {
    signal(SIGINT, app_ipcam_ExitSig_handle);
    signal(SIGTERM, app_ipcam_ExitSig_handle);

    if (initVideo())
        return -1;

    video_ch_param_t param;

    // ch0
    param.format = VIDEO_FORMAT_RGB888;
    param.width  = 1920;
    param.height = 1080;
    param.fps    = 10;
    setupVideo(VIDEO_CH0, &param);
    registerVideoFrameHandler(VIDEO_CH0, 0, fpSaveVpssFrame, (void*)".rgb");

    // ch1
    param.format = VIDEO_FORMAT_NV21;
    param.width  = 1920;
    param.height = 1080;
    param.fps    = 5;
    setupVideo(VIDEO_CH1, &param);
    registerVideoFrameHandler(VIDEO_CH1, 0, fpSaveVpssFrame, (void*)".nv21");

    // ch2
#if 0
    param.format = VIDEO_FORMAT_H264;
    param.width = 1920;
    param.height = 1080;
    param.fps = 30;
    setupVideo(VIDEO_CH2, &param);
    registerVideoFrameHandler(VIDEO_CH2, 0, fpSaveVencFrame, NULL);
#else
    param.format = VIDEO_FORMAT_H264;
    param.width  = 1920;
    param.height = 1080;
    param.fps    = 30;
    setupVideo(VIDEO_CH2, &param);
    registerVideoFrameHandler(VIDEO_CH2, 0, fpStreamingSendToRtsp, NULL);
    initRtsp((0x01 << VIDEO_CH2));
#endif

    startVideo();

    while (1) {
        sleep(1);
    }

    return 0;
}