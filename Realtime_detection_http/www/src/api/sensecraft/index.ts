import { sensecraftRequest } from "@/utils/request";
import { IAppInfo, IModelData } from "./sensecraft";

//获取Sensecraft平台用户信息
export const getSensecraftUserInfoApi = async () =>
  sensecraftRequest<{
    nickname: string;
  }>({
    url: "portalapi/user/getUserOrgInfo",
    method: "get",
  });

// 刷新token
export const refreshTokenApi = async (params: { refreshToken: string }) =>
  sensecraftRequest<{
    token: string;
  }>({
    url: "portalapi/auth/refreshToken",
    method: "get",
    params,
  });

// 获取应用列表
export const getAppListApi = async () =>
  sensecraftRequest<{
    list: IAppInfo[];
  }>({
    url: "aiserverapi/flow/application/list_app",
    method: "get",
  });

// 获取应用列表
export const getPublicAppListApi = async () =>
  sensecraftRequest<{
    list: IAppInfo[];
  }>({
    url: "aiserverapi/flow/application/query_by_option",
    method: "get",
  });

// 新建应用
export const createAppApi = async (data: {
  app_name?: string | null;
  flow_data?: string | null;
  model_data?: IModelData | null;
}) =>
  sensecraftRequest<{
    app_id: string;
  }>({
    url: "aiserverapi/flow/application/create_app",
    method: "post",
    data,
  });

// 查看应用
export const viewAppApi = async (app_id: string) =>
  sensecraftRequest<IAppInfo>({
    url: "aiserverapi/flow/application/view_app",
    method: "get",
    params: {
      app_id,
    },
  });

// 更新应用
export const updateAppApi = async (data: {
  app_id: string;
  app_name?: string | null;
  flow_data?: string | null;
  model_data?: IModelData | null;
}) =>
  sensecraftRequest<{
    app_id: string;
  }>({
    url: "aiserverapi/flow/application/update_app",
    method: "post",
    data,
  });

// 删除应用
export const deleteAppApi = async (data: { app_id: string }) =>
  sensecraftRequest<{
    app_id: string;
  }>({
    url: "aiserverapi/flow/application/delete_app",
    method: "post",
    data,
  });

// 上传 图片/模型
export const acquireFileUrlApi = async (file_name: string) =>
  sensecraftRequest<{
    file_url: string;
    upload_url: string;
  }>({
    url: "aiserverapi/user/acquire_file_url",
    method: "get",
    params: {
      file_name,
      file_type: 3,
    },
  });

// 删除 图片/模型 应用
export const removeFileApi = async (file_name: string) =>
  sensecraftRequest<{
    file_url: string;
    upload_url: string;
  }>({
    url: "aiserverapi/user/remove_file",
    method: "post",
    data: {
      file_name,
      file_type: 3,
    },
  });

// 查询模型文件详情
export const applyModelApi = async (model_id: string) =>
  sensecraftRequest<{
    model_snapshot: IModelData;
  }>({
    url: "aiserverapi/model/apply_model",
    method: "get",
    params: {
      model_id,
      uniform_type: 40,
    },
  });
