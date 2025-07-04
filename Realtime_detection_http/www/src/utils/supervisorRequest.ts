import axios, { AxiosRequestConfig, AxiosError } from "axios";
import { message } from "antd";
import { getToken, clearCurrentUser } from "@/store/user";
import { isDev } from "@/utils";

// 根据环境设置 baseURL
const baseIP = isDev ? "http://192.168.42.1" : window.location.origin;

// 和设备通信的
const supervisorService = axios.create({
  baseURL: baseIP,
});

// 设置token
supervisorService.interceptors.request.use((config) => {
  config.headers.Authorization = getToken();
  return config;
});

interface BaseResponse<T> {
  code: number | string;
  data: T;
  msg?: string;
  errorcode?: number;
  message?: string;
  timestamp?: string;
}
interface OtherRequestConfig {
  catchs?: boolean;
}

const createSupervisorRequest = () => {
  return async <T>(
    config: AxiosRequestConfig,
    otherConfig: OtherRequestConfig = {
      catchs: false,
    }
  ): Promise<BaseResponse<T>> => {
    const { catchs } = otherConfig;

    return await new Promise((resolve, reject) => {
      supervisorService.request<BaseResponse<T>>(config).then(
        (res) => {
          if (catchs) {
            resolve(res.data);
          } else {
            if (res.data.code !== 0 && res.data.code !== "0") {
              message.error(res.data.msg || "request error");
              reject(res.data);
              return;
            }
            resolve(res.data);
          }
        },
        (err: AxiosError) => {
          console.error(err);
          //鉴权失败，重新登录
          if (err.response?.status == 401) {
            clearCurrentUser();
          } else {
            if (!catchs) {
              message.error(err.message || "request error");
            }
          }
          reject(err);
        }
      );
    });
  };
};

const supervisorRequest = createSupervisorRequest();

export default supervisorRequest;
