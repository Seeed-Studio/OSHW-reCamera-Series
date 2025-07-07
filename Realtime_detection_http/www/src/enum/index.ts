export enum PowerMode {
  Shutdown = 0, //关机
  Restart = 1, //重启
}
export enum DeviceChannleMode {
  Official = 0, //官方
  Self = 1, //自定义
}
export enum DeviceNeedRestart {
  No = 0, //不需要
  Yes = 1, //需要
}

export enum IsUpgrading {
  No = 0, //不在升级中
  Yes = 1, //升级中
}

export enum ServiceStatus {
  RUNNING = 0, //运行正常
  STARTING = 1, //启动中
  FAILED = 2, //启动失败
  ERROR = 4, //运行异常
}

export enum UpdateStatus {
  Check = "Check",
  NeedUpdate = "NeedUpdate", //有新版本需要更新
  NoNeedUpdate = "NoNeedUpdate", //不需要更新
  Updating = "Updating", //更新中
  UpdateDone = "UpdateDone", //更新完毕
}
