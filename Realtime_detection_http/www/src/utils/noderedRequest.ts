import axios, { AxiosRequestConfig, AxiosError } from "axios";
import { isDev } from "./index";

// 根据环境设置 baseURL
export const baseIP = isDev ? "http://192.168.42.1" : window.location.origin;

// nodered的接口
const noderedService = axios.create({
  baseURL: `${baseIP}:1880`,
  headers: {
    "Content-Type": "application/json",
    "Node-RED-API-Version": "v2"
  },
});

// 响应拦截器
noderedService.interceptors.response.use(
  (response) => {
    if (response.status == 200 || response.status == 204) {
      return response;
    } else {
      return Promise.reject(response.data.message);
    }
  },
  (error: AxiosError) => {
    return Promise.reject(error.message);
  }
);

const createNoderedRequest = () => {
  return async <T>(config: AxiosRequestConfig): Promise<T | null> => {
    const response = await noderedService.request<T>(config);
    return response.data;
  };
};

const noderedRequest = createNoderedRequest();

export default noderedRequest;
