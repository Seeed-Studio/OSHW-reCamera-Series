import { DeviceChannleMode, DeviceNeedRestart, ServiceStatus } from "@/enum";

interface IDeviceInfo {
  appName: string;
  deviceName: string;
  isReCamera: boolean;
  ip: string;
  sn: string;
  wifiIp: string;
  mask: string;
  gateway: string;
  dns: string;
  channel: DeviceChannleMode;
  serverUrl: string;
  officialUrl: string;
  cpu: string;
  ram: string;
  npu: string;
  osVersion: string;
  osName: string;
  osUpdateTime: string;
  needRestart: DeviceNeedRestart;
  [prop: string]: string;
}

interface IChannelParams {
  channel?: DeviceChannleMode;
  serverUrl?: string;
}

interface IServiceStatus {
  sscmaNode: ServiceStatus;
  nodeRed: ServiceStatus;
  system: ServiceStatus;
  uptime: number;
}

interface IIPDevice {
  device: string;
  info: { sn: string; lastSix: string } | string;
  ip: string;
  type: string;
}
