import { useEffect, useMemo } from "react";
import { ConfigProvider } from "antd";
import { createHashRouter, RouterProvider } from "react-router-dom";
import Routes from "@/router";
import Login from "@/views/login";
import { queryDeviceInfoApi } from "@/api/device/index";
import { getUserInfoApi } from "@/api/user";
import useUserStore from "@/store/user";
import useConfigStore from "@/store/config";
import { Version } from "@/utils";

const router = createHashRouter(Routes);

const App = () => {
  const {
    currentSn,
    usersBySn,
    setCurrentSn,
    updateFirstLogin,
    clearCurrentUserInfo,
  } = useUserStore();

  const { updateDeviceInfo } = useConfigStore();

  useEffect(() => {
    console.log(`%cVersion: ${Version}`, "font-weight: bold");
    initUserData();
  }, []);

  const token = useMemo(() => {
    return currentSn ? usersBySn[currentSn]?.token : null;
  }, [usersBySn, currentSn]);

  const initUserData = async () => {
    try {
      const response = await queryDeviceInfoApi();
      const deviceInfo = response.data;
      // 查询设备信息，获取sn
      updateDeviceInfo(deviceInfo);
      const sn = deviceInfo.sn;
      setCurrentSn(sn);
      if (sn) {
        // 查询设备是否第一次登录，第一次登录，直接进登录页
        const response = await getUserInfoApi();
        if (response.code == 0) {
          const data = response.data;
          const firstLogin = data.firstLogin;
          updateFirstLogin(firstLogin);
          if (firstLogin) {
            clearCurrentUserInfo();
          }
        }
      }
    } catch (error) {
      // 不能清用户信息，很可能是服务没起来超时
    }
  };

  return (
    <ConfigProvider
      theme={{
        token: {
          colorPrimary: "#8FC31F",
          colorPrimaryHover: "#81AE1B",
        },
      }}
    >
      <div className="w-full h-full">
        {token ? <RouterProvider router={router} /> : <Login />}
      </div>
    </ConfigProvider>
  );
};

export default App;
