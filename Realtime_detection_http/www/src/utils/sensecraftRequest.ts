import axios, { InternalAxiosRequestConfig, AxiosRequestConfig } from "axios";
import {
  getToken,
  setToken,
  getRefreshToken,
  savePlatformInfo,
} from "@/store/platform";
import { refreshTokenApi } from "@/api/sensecraft";
import { sensecraftAuthorize } from "@/utils";

interface SensecraftResponse<T> {
  code: number | string;
  data: T;
  msg?: string;
}

const portalApi = import.meta.env.VITE_PORTAL_URL;
const sensecraftApi = import.meta.env.VITE_SENSECRAFT_URL;

// 和平台通信的接口
const sensecraftService = axios.create({});

// 根据api类型修改baseurl
sensecraftService.interceptors.request.use((config) => {
  config.headers.Authorization = getToken();
  if (config.url?.startsWith("portalapi")) {
    config.baseURL = portalApi;
  } else if (config.url?.startsWith("aiserverapi")) {
    config.baseURL = sensecraftApi;
  }
  return config;
});

/**
 * @description sensecraftService响应拦截器
 */
sensecraftService.interceptors.response.use(
  async (response) => {
    const code = response.data?.code;
    if (
      (code == 11101 || code == 11102) &&
      !response.request.responseURL.includes("portalapi/auth/refreshToken")
    ) {
      return handleTokenRefresh(response.config);
    }
    return response;
  },
  async (error) => {
    const { response = {} } = error;
    const code = response.data?.code;
    if (code === 11101 || code === 11102) {
      return handleTokenRefresh(error.config);
    }
    return Promise.reject(error);
  }
);

async function handleTokenRefresh(config: InternalAxiosRequestConfig<any>) {
  try {
    const newToken = await refreshToken();
    config.headers.Authorization = newToken;
    return sensecraftService.request(config);
  } catch (refreshError) {
    console.error("Token refresh failed:", refreshError);
    return Promise.reject(refreshError);
  }
}

/**
 * 刷新令牌
 * @param config 过期请求配置
 * @returns {any} 返回结果
 */
const refreshToken = async () => {
  const refresh_token = getRefreshToken();
  const token = getToken();

  if (!refresh_token || refresh_token == null || !token || token == null) {
    // 需要登录
    // sensecraftAuthorize();
    return Promise.reject();
  }
  try {
    const resp = await refreshTokenApi({
      refreshToken: refresh_token,
    });
    const newToken = resp.data.token;
    setToken(newToken);
    savePlatformInfo();
    return newToken;
  } catch (error) {
    sensecraftAuthorize();
    return Promise.reject();
  }
};

const createSensecraftRequest = () => {
  return async <T>(
    config: AxiosRequestConfig
  ): Promise<SensecraftResponse<T>> => {
    return await new Promise((resolve, reject) => {
      sensecraftService.request<SensecraftResponse<T>>(config).then(
        (res) => {
          if (res.data.code != 0 && res.data.code != "0") {
            reject(res.data);
            return;
          }
          resolve(res.data);
        },
        (err: any) => {
          reject(err);
        }
      );
    });
  };
};

const sensecraftRequest = createSensecraftRequest();

export default sensecraftRequest;
