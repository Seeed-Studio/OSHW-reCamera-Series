import { supervisorRequest } from "@/utils/request";
// 获取用户信息
export const getUserInfoApi = async () =>
  supervisorRequest<IUserInfo>({
    url: "api/userMgr/queryUserInfo",
    method: "get",
  });
// 修改用户信息
export const updateUserInfoApi = async (data: { userName: string }) =>
  supervisorRequest({
    url: "api/userMgr/updateUserName",
    method: "post",
    data,
  });
// 修改用户密码
export const updateUserPasswordApi = async (data: {
  oldPassword: string;
  newPassword: string;
}) =>
  supervisorRequest({
    url: "api/userMgr/updatePassword",
    method: "post",
    data,
  });
// 登录
export const loginApi = async (data: { userName: string; password: string }) =>
  supervisorRequest<{ token: string; retryCount?: number }>(
    {
      url: "api/userMgr/login",
      method: "post",
      data,
    },
    {
      catchs: true,
    }
  );
// 设置ssh开关
export const setSShStatusApi = async (data: {
  enabled: boolean;
}) =>
  supervisorRequest({
    url: "api/userMgr/setSShStatus",
    method: "post",
    data,
  });
// 新增ssh key
export const addSshKeyApi = async (data: {
  name: string;
  value: string;
  time: string;
}) =>
  supervisorRequest({
    url: "api/userMgr/addSShkey",
    method: "post",
    data,
  });
// 删除ssh key
export const delSshKeyApi = async (data: { id: string }) =>
  supervisorRequest({
    url: "api/userMgr/deleteSShkey",
    method: "post",
    data,
  });
