import { useEffect, Reducer, useReducer, useRef } from "react";
import { FormInstance } from "antd-mobile/es/components/form";
import {
  getWifiListApi,
  getWifiResultListApi,
  getDeviceWifiInfoApi,
  switchWiFiApi,
  disconnectWifiApi,
  connectWifiApi,
  autoConnectWiFiApi,
  forgetWiFiApi,
  getWifiStatusApi,
} from "@/api/network";
import {
  WifiConnectedStatus,
  WifiStatus,
  WifiIpAssignmentRule,
  WifiAuth,
  WifiType,
} from "@/enum/network";
import { getSignalStrengthLevel } from "@/utils";
import { IWifiInfo, IConnectParams } from "@/api/network/network";
import useConfigStore from "@/store/config";
import { message } from "antd";

interface FormParams {
  password?: string;
}
const initialWifiList = [
  {
    label: "",
    key: "Internet",
    list: [],
  },
  {
    label: "Enable Wi-Fi",
    key: WifiConnectedStatus.Yes,
    list: [],
  },
  {
    label: "Networks Found",
    key: WifiConnectedStatus.No,
    list: [],
  },
];
const timeGap = 30000;
let timer: NodeJS.Timeout | null = null;
let resultTimer: NodeJS.Timeout | null = null;
let resultTotalCount = 0;

export enum OperateType {
  Connect = "Connect",
  DisConnect = "DisConnect",
  Forget = "Forget",
  AutoConnect = "AutoConnect",
}
export enum FormType {
  Password = "Password",
  Disabled = "Disabled",
}
interface IInfo {
  label: string;
  key: WifiConnectedStatus | string;
  list: IWifiInfo[];
}
interface IInitialState {
  queryNum: number;
  wifiStatus: WifiStatus;
  wifiChecked: boolean;
  wifiVisible: boolean;
  visible: boolean;
  passwordVisible: boolean;
  password: string;
  channel: string;
  internetList: IWifiInfo[];
  hasConnectedList: IWifiInfo[];
  disConnectedList: IWifiInfo[];
  deviceWifiInfo?: IWifiInfo;
  curWifiInfo: Partial<IWifiInfo>;
  wifiList: IInfo[];
  timer: NodeJS.Timeout | null;
  formType: FormType;
  submitLoading: boolean;
  submitType?: OperateType;
  needRefresh: boolean;
  hasWired: boolean;
  connectLoading: boolean;
}
type ActionType = { type: "setState"; payload: Partial<IInitialState> };
const initialState: IInitialState = {
  queryNum: 0,
  wifiStatus: 0,
  wifiChecked: false,
  wifiVisible: false,
  visible: false,
  password: "",
  channel: "",
  internetList: [],
  hasConnectedList: [],
  disConnectedList: [],
  curWifiInfo: {},
  wifiList: initialWifiList,
  timer: null,
  formType: FormType.Disabled,
  submitLoading: false,
  needRefresh: true,
  hasWired: false,
  passwordVisible: false,
  connectLoading: false,
};
function reducer(state: IInitialState, action: ActionType): IInitialState {
  switch (action.type) {
    case "setState":
      return {
        ...state,
        ...action.payload,
      };
    default:
      throw new Error();
  }
}

export function useData() {
  const { updateWifiStatus } = useConfigStore();

  // ---状态管理
  const [state, stateDispatch] = useReducer<Reducer<IInitialState, ActionType>>(
    reducer,
    initialState
  );
  const setStates = (payload: Partial<IInitialState>) => {
    stateDispatch({ type: "setState", payload: payload });
  };
  const passwordFormRef = useRef<FormInstance>(null);
  const getConnectText = (item: IWifiInfo) => {
    return item.connectedStatus === WifiConnectedStatus.Yes
      ? "Connected"
      : "Not Connected";
  };
  const filterList = (data: IWifiInfo[], etherinfo?: IWifiInfo) => {
    const [interneInfo, hasConnectedInfo, disConnectedInfo] = state.wifiList;
    const hasConnectedList: IWifiInfo[] = [],
      disConnectedList: IWifiInfo[] = [],
      internetList: IWifiInfo[] = [];
    if (etherinfo) {
      internetList.push({
        ...etherinfo,
        type: WifiType.Wired,
        ssid: "Ethernet",
        connectedStatusText: getConnectText(etherinfo),
      });
    }
    data.forEach((item: IWifiInfo) => {
      item.signal = getSignalStrengthLevel(item.signal);
      item.type = WifiType.Wireless;
      item.ipAssignmentText =
        item.ipAssignment === WifiIpAssignmentRule.Automatic
          ? "Automatic"
          : "Static";
      item.connectChecked = !!item.autoConnect;
      item.connectedStatusText = getConnectText(item);
      if (item.connectedStatus === WifiConnectedStatus.Yes) {
        hasConnectedList.push(item);
      } else {
        disConnectedList.push(item);
      }
    });
    hasConnectedList.sort(function (a, b) {
      return b.signal - a.signal;
    });
    disConnectedList.sort(function (a, b) {
      return b.signal - a.signal;
    });

    setStates({
      wifiList: [
        {
          ...interneInfo,
          list: internetList,
        },
        {
          ...hasConnectedInfo,
          list: hasConnectedList,
        },
        {
          ...disConnectedInfo,
          list: disConnectedList,
        },
      ],
      hasWired: !!internetList.length,
    });
  };
  const onStopGetWifiResultsList = () => {
    resultTimer && clearInterval(resultTimer);
  };
  const getWifiResults = async () => {
    const { data } = await getWifiResultListApi();
    filterList(data.wifiInfoList, data.etherinfo);
  };
  const getWifiInterval = async () => {
    getWifiResults();

    resultTimer = setInterval(() => {
      if (resultTotalCount >= 3) {
        onStopGetWifiResultsList();
      } else {
        // 3秒内 每秒获取一次result
        resultTotalCount++;
        getWifiResults();
      }
    }, 1000);
  };
  const getWifiList = async () => {
    try {
      if (state.visible || state.wifiVisible) return;
      await getWifiListApi({
        scanTime: 0.2,
      });
      // wifi没有开启不需要开启自动刷新
      if (!state.wifiChecked) return;
      getWifiInterval();
      return true;
    } catch (err) {}
  };
  const getDeviceWifiInfo = async () => {
    try {
      const { data } = await getDeviceWifiInfoApi();
      setStates({
        wifiStatus: data.status,
        deviceWifiInfo: data.wifiInfo,
        wifiChecked: data.status !== WifiStatus.Close,
      });
      return data.status;
    } catch (err) {}
  };
  //
  const onStopRefreshWifiList = () => {
    // state.timer && clearInterval(state.timer)
    timer && clearInterval(timer);
  };

  // 自动刷新wifilist
  const onAutoRefreshWifiList = async () => {
    onStopRefreshWifiList();
    // wifi没有开启不需要开启自动刷新
    if (!state.wifiChecked) return;
    timer = setInterval(() => {
      getWifiList();
    }, timeGap);
  };
  const handleSwitchWifi = async () => {
    await switchWiFiApi({ mode: Number(!state.wifiChecked) });
    setStates({
      wifiChecked: !state.wifiChecked,
      visible: false,
    });
  };
  const onSwitchEnabledWifi = async () => {
    if (state.wifiChecked) {
      setStates({
        visible: true,
        formType: FormType.Disabled,
      });
    } else {
      handleSwitchWifi();
    }
  };
  const toggleVisible = () => {
    setStates({
      visible: !state.visible,
    });
  };

  const resetFields = () => {
    passwordFormRef.current?.resetFields();
  };
  const onQueryData = async () => {
    try {
      const status = await getDeviceWifiInfo();
      if (status != WifiStatus.Disable) {
        await getWifiList();
      }
    } catch (err) {}
    setStates({
      needRefresh: false,
    });
  };

  const onShowWifiItemInfo = (item: IWifiInfo) => {
    setStates({
      curWifiInfo: item,
      wifiVisible: true,
    });
  };
  const onClickWifiItem = (
    item: IInfo,
    wifiItem: IWifiInfo,
    index: number,
    showInfo?: boolean
  ) => {
    onStopRefreshWifiList();
    if (
      showInfo ||
      wifiItem.type === WifiType.Wired ||
      item.key === WifiConnectedStatus.No ||
      wifiItem.ssid == state.deviceWifiInfo?.ssid
    ) {
      onShowWifiItemInfo(wifiItem);
    } else {
      if (state.connectLoading) {
        message.info("The current operation is prohibited");
        return;
      }
      onHandleConnect(item.list, index);
    }
  };
  const onHandleConnect = async (list?: IWifiInfo[], index?: number) => {
    try {
      if (list) {
        // 已连接过的直接连接
        setStates({
          deviceWifiInfo: undefined,
          connectLoading: true,
        });
        list && (list[index || 0].loading = true);
        await onConnect(undefined, list[index || 0].ssid);
        list && (list[index || 0].loading = false);
      } else if (state.curWifiInfo.auth === WifiAuth.Need) {
        setStates({
          visible: true,
          formType: FormType.Password,
        });
      }
    } catch (err) {
      list && (list[index || 0].loading = false);
    }
    setStates({
      connectLoading: false,
    });
  };

  const onConnect = async (values?: FormParams, ssid?: string) => {
    try {
      const params: IConnectParams = {
        ssid: ssid || state.curWifiInfo.ssid || "",
      };
      values && (params.password = values?.password || "");
      setStates({
        submitLoading: true,
      });
      await connectWifiApi(params);
      setStates({
        wifiVisible: false,
        visible: false,
      });
      refreshWifiStatus();
      setTimeout(() => {
        setStates({
          needRefresh: true,
        });
      }, 2000);
      resetFields();
    } catch (err) {}
    setStates({
      submitLoading: false,
    });
  };
  // 刷新wifi状态
  const refreshWifiStatus = async () => {
    const { data } = await getWifiStatusApi();
    updateWifiStatus(data.status);
  };
  const onHandleOperate = async (type: OperateType) => {
    const info = state.curWifiInfo;
    if (!info) return;
    setStates({
      submitType: type,
    });
    try {
      switch (type) {
        case OperateType.Connect:
          onHandleConnect();
          break;
        case OperateType.AutoConnect:
          setStates({
            submitLoading: true,
          });
          await autoConnectWiFiApi({
            ssid: info.ssid || "",
            mode: Number(!info.autoConnect),
          });
          refreshWifiStatus();
          setStates({
            submitLoading: false,
            curWifiInfo: {
              ...state.curWifiInfo,
              autoConnect: Number(!state.curWifiInfo.autoConnect),
              connectChecked: !state.curWifiInfo.connectChecked,
            },
            wifiVisible: true,
          });
          getWifiList();
          break;
        case OperateType.DisConnect:
          setStates({
            submitLoading: true,
          });
          await disconnectWifiApi({
            ssid: info.ssid || "",
          });
          refreshWifiStatus();

          setStates({
            wifiVisible: false,
            needRefresh: true,
          });
          break;
        case OperateType.Forget:
          setStates({
            submitLoading: true,
          });
          await forgetWiFiApi({
            ssid: info.ssid || "",
          });
          setStates({
            wifiVisible: false,
            needRefresh: true,
          });
          break;
        default:
          throw new Error();
      }
    } catch (err) {
      setStates({
        submitLoading: false,
      });
    }
  };

  useEffect(() => {
    if (state.wifiChecked && !state.wifiVisible && !state.visible) {
      getWifiInterval();
      onAutoRefreshWifiList();
    } else {
      onStopRefreshWifiList();
    }
    setStates({
      submitLoading: false,
    });
  }, [state.wifiChecked, state.wifiVisible, state.visible]);
  useEffect(() => {
    if (state.needRefresh) {
      onQueryData();
    }
  }, [state.needRefresh]);
  useEffect(() => {
    // 清除定时器
    return () => {
      onStopRefreshWifiList();
    };
  }, []);
  return {
    state,
    passwordFormRef,
    setStates,
    onSwitchEnabledWifi,
    toggleVisible,
    onConnect,
    onHandleOperate,
    onClickWifiItem,
    handleSwitchWifi,
  };
}
