import { create } from "zustand";
import { IDeviceInfo } from "@/api/device/device";
import { WifiConnectStatus } from "@/enum/network";
import { DeviceChannleMode, UpdateStatus } from "@/enum";

interface SystemUpdateState {
  status: UpdateStatus;
  visible: boolean;
  channelVisible: boolean;
  updateInfoVisible: boolean;
  percent: number;
  channel: DeviceChannleMode;
  address: string;
  downloadUrl: string;
}

type ConfigStoreType = {
  deviceInfo: Partial<IDeviceInfo>;
  wifiStatus: WifiConnectStatus | undefined;
  systemUpdateState: Partial<SystemUpdateState>;
  updateDeviceInfo: (deviceInfo: IDeviceInfo) => void;
  updateWifiStatus: (wifiStatus: WifiConnectStatus) => void;
  setSystemUpdateState: (payload: Partial<SystemUpdateState>) => void;
};

const useConfigStore = create<ConfigStoreType>((set) => ({
  deviceInfo: {},
  wifiStatus: undefined,
  systemUpdateState: {
    status: UpdateStatus.Check,
    visible: false,
    channelVisible: false,
    percent: 0,
    channel: DeviceChannleMode.Official,
    updateInfoVisible: false,
    address: "",
    downloadUrl: "",
  },
  updateDeviceInfo: (deviceInfo: IDeviceInfo) => set(() => ({ deviceInfo })),
  updateWifiStatus: (wifiStatus: WifiConnectStatus) =>
    set(() => ({ wifiStatus })),
  setSystemUpdateState: (payload) =>
    set((state) => ({
      systemUpdateState: { ...state.systemUpdateState, ...payload },
    })),
}));

export default useConfigStore;
