import { create } from "zustand";
import { getPlatformInfoApi, savePlatformInfoApi } from "@/api/device";
import { IAppInfo } from "@/api/sensecraft/sensecraft";

type PlatformStoreType = {
  token: string | null;
  refreshToken: string | null;
  nickname: string | null;
  appInfo: IAppInfo | null;
  updateToken: (token: string) => void;
  updateRefreshToken: (refreshToken: string) => void;
  updateNickname: (name: string) => void;
  updateAppInfo: (app: IAppInfo) => void;
  clearUserInfo: () => void;
};
// Platform
const usePlatformStore = create<PlatformStoreType>((set) => ({
  token: null,
  refreshToken: null,
  nickname: null,
  appInfo: null,
  updateToken: (token: string | null) => set(() => ({ token })),
  updateRefreshToken: (refreshToken: string | null) =>
    set(() => ({ refreshToken })),
  updateNickname: (name: string) => set(() => ({ nickname: name })),
  updateAppInfo: (app: IAppInfo) => set(() => ({ appInfo: app })),
  clearUserInfo: () =>
    set(() => ({
      token: null,
      refreshToken: null,
      nickname: null,
    })),
}));

export const setToken = (token: string) => usePlatformStore.setState({ token });
export const getToken = () => usePlatformStore.getState().token;
export const getRefreshToken = () => usePlatformStore.getState().refreshToken;

export const savePlatformInfo = async () => {
  try {
    const { token, refreshToken, nickname, appInfo } =
      usePlatformStore.getState();
    const platform_info = {
      user_info: {
        token,
        refreshToken,
        nickname,
      },
      app_info: JSON.stringify(appInfo),
    };
    await savePlatformInfoApi({ platform_info: JSON.stringify(platform_info) });
  } catch (error) {}
};

export const initPlatformStore = async (
  token?: string,
  refreshToken?: string
) => {
  try {
    const resp = await getPlatformInfoApi();
    if (resp.code == 0) {
      const data = resp.data;
      const platform_info = data?.platform_info;
      if (platform_info) {
        const platformInfo = JSON.parse(platform_info);

        let tempToken = token;
        let tempRefreshToken = refreshToken;
        let nickname = null;
        if (!tempToken || !tempRefreshToken) {
          const user_info = platformInfo.user_info;
          tempToken = user_info.token;
          tempRefreshToken = user_info.refreshToken;
          nickname = user_info.nickname;
        }

        let app_info;
        try {
          app_info = JSON.parse(platformInfo.app_info);
        } catch (error) {
          app_info = null;
        }

        usePlatformStore.setState({
          token: tempToken,
          refreshToken: tempRefreshToken,
          nickname: nickname,
          appInfo: app_info,
        });
      }
    } else {
      if (token && refreshToken) {
        usePlatformStore.setState({
          token,
          refreshToken,
        });
      }
    }
  } catch (error) {}
};

export const getLocalPlatformInfo = async () => {
  try {
    const resp = await getPlatformInfoApi();
    if (resp.code == 0) {
      const data = resp.data;
      const platform_info = data?.platform_info;
      if (platform_info) {
        const platformInfo = JSON.parse(platform_info);
        const user_info = platformInfo.user_info;
        const token = user_info.token;

        let app_info;
        try {
          app_info = JSON.parse(platformInfo.app_info);
        } catch (error) {
          app_info = null;
        }

        usePlatformStore.setState({
          token: token,
          refreshToken: user_info.refreshToken,
          nickname: user_info.nickname,
          appInfo: app_info,
        });
        return {
          user_info,
          app_info,
        };
      }
    }
    return null;
  } catch (error) {
    return null;
  }
};

export const logout = async () => {
  const { clearUserInfo } = usePlatformStore.getState();
  clearUserInfo();
  savePlatformInfo();
};

export default usePlatformStore;
