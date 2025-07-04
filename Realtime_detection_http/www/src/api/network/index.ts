import { supervisorRequest } from "@/utils/request";
import { WifiMode, WifiStatus, WifiConnectStatus } from "@/enum/network";
import { IWifiInfo, IConnectParams } from "./network";
// 获取设备的wifi信息
export const getDeviceWifiInfoApi = async () =>
  supervisorRequest<{
    status: WifiStatus;
    wifiInfo: IWifiInfo;
  }>(
    {
      url: "api/wifiMgr/queryWiFiInfo",
      method: "get",
    },
  );
// 获取wifi list
export const getWifiListApi = async (data: { scanTime: number }) =>
  supervisorRequest<{
    etherinfo: IWifiInfo;
    wifiInfoList: IWifiInfo[];
  }>(
    {
      url: "api/wifiMgr/scanWiFi",
      method: "post",
      data,
    },
  );
// 获取wifi 扫描结果
export const getWifiResultListApi = async () =>
  supervisorRequest<{
    etherinfo: IWifiInfo;
    wifiInfoList: IWifiInfo[];
  }>(
    {
      url: "api/wifiMgr/getWiFiScanResults",
      method: "get",
    },
  );
// 连接wifi
export const connectWifiApi = async (data: IConnectParams) =>
  supervisorRequest({
    url: "api/wifiMgr/connectWiFi",
    method: "post",
    data,
  });
// 断开wifi
export const disconnectWifiApi = async (data: { ssid: string }) =>
  supervisorRequest({
    url: "api/wifiMgr/disconnectWiFi",
    method: "post",
    data,
  });
// 启停wifi
export const switchWiFiApi = async (data: { mode: WifiMode }) =>
  supervisorRequest({
    url: "api/wifiMgr/switchWiFi",
    method: "post",
    data,
  });
// wifi自动连接
export const autoConnectWiFiApi = async (data: {
  ssid: string;
  mode: number;
}) =>
  supervisorRequest({
    url: "api/wifiMgr/autoConnectWiFi",
    method: "post",
    data,
  });
// wifi忘记
export const forgetWiFiApi = async (data: { ssid: string }) =>
  supervisorRequest({
    url: "api/wifiMgr/forgetWiFi",
    method: "post",
    data,
  });
// 获取wifi连接状态

export const getWifiStatusApi = async () =>
  supervisorRequest<{
    status: WifiConnectStatus;
  }>({
    url: "api/wifiMgr/getWifiStatus",
    method: "get",
  });
