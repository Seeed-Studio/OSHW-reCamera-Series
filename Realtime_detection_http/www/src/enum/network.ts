export enum WifiStatus {
  Open = 1, // 已开启-未连接
  Close = 0, //未开启
  Connecting = 2, //连接中
  Connected = 3, //已连接
  Disable = 4, //没有wifi
}
export enum WifiMode {
  Open = 1, //开启
  Close = 0, //未开启
}
// wifi是否加密
export enum WifiAuth {
  Need = 1,
  NoNeed = 0,
}
// wifi是否连接过
export enum WifiConnectedStatus {
  Yes = 1,
  No = 0,
}
// wifi是否自动连接
export enum WifiAutoConnect {
  Yes = 1,
  No = 0,
}
// IP 分配规则
export enum WifiIpAssignmentRule {
  Automatic = 1, //动态
  Static = 0, //静态
}
// WifiType
export enum WifiType {
  Wired = 1, //有线
  Wireless = 0, //无线
}
// wifi连接状态
export enum WifiConnectStatus {
  Wired = 0, //有线
  Wireless_Connect = 1, //无线-已连接
  Wireless_DisConnect = 2, //无线-未连接
}
