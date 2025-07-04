import { useState, useEffect, useRef } from "react";
import {
  Modal,
  Button,
  Input,
  ConfigProvider,
  Spin,
  message,
  ButtonProps,
} from "antd";
import {
  PlusCircleOutlined,
  WifiOutlined,
  SyncOutlined,
  EditOutlined,
  DeleteOutlined,
  UserOutlined,
  LeftOutlined,
  RightOutlined,
  UpOutlined,
  DownOutlined,
  SettingOutlined,
  FileOutlined,
} from "@ant-design/icons";
import {
  getDeviceListApi,
  getModelInfoApi,
  uploadModelApi,
} from "@/api/device";
import { IIPDevice } from "@/api/device/device";
import {
  getFlows,
  saveFlows,
  getFlowsState,
  setFlowsState,
} from "@/api/nodered";
import {
  getAppListApi,
  createAppApi,
  viewAppApi,
  updateAppApi,
  deleteAppApi,
  getSensecraftUserInfoApi,
  acquireFileUrlApi,
  removeFileApi,
  applyModelApi,
} from "@/api/sensecraft";
import recamera_logo from "@/assets/images/recamera_logo.png";
import { IAppInfo, IModelData, IActionInfo } from "@/api/sensecraft/sensecraft";
import { sensecraftAuthorize, parseUrlParam, DefaultFlowData } from "@/utils";
import usePlatformStore, {
  savePlatformInfo,
  initPlatformStore,
  getLocalPlatformInfo,
  logout,
} from "@/store/platform";
import useConfigStore from "@/store/config";
import { getToken } from "@/store/user";
import Network from "@/views/network";
import NodeRed from "@/views/nodered";
import styles from "./index.module.css";

// 定义 type 优先级
const typePriority = { eth: 1, usb: 2, wlan: 3 };

// 类型守卫函数
function isValidType(type: string): type is keyof typeof typePriority {
  return type in typePriority;
}

const Workspace = () => {
  const { token, appInfo, nickname, updateAppInfo, updateNickname } =
    usePlatformStore();
  const { deviceInfo } = useConfigStore();

  const [actionInfo, setActionInfo] = useState<IActionInfo | null>(null);

  const [messageApi, messageContextHolder] = message.useMessage();
  const [modal, modalContextHolder] = Modal.useModal();

  const [isNetworkModalOpen, setIsNetworkModalOpen] = useState(false);

  const [applist, setApplist] = useState<IAppInfo[]>([]);
  const [devicelist, setDevicelist] = useState<IIPDevice[]>([]);

  const [isExpand, setIsExpand] = useState(true);
  const [showDeviceList, setShowDeviceList] = useState(false);
  const [syncing, setSyncing] = useState(false);
  const [loading, setLoading] = useState(false);
  const [refreshing, setRefreshing] = useState(false);
  const [loadingTip, setLoadingTip] = useState("");

  const [focusAppid, setFocusAppid] = useState("");
  const revRef = useRef<string>("");
  const inputRef = useRef<string>("");

  const [timestamp, setTimestamp] = useState<number>(1);

  useEffect(() => {
    const initPlatform = async () => {
      const param = parseUrlParam(window.location.href);
      const token_url = param.token;
      const refresh_token = param.refresh_token;
      const action = param.action; //new / app / clone / model /normal  action为空默认为normal
      const app_id = param.app_id; //type为app时才需要传
      const model_id = param.model_id; //type为model时才需要传

      let actionInfo;
      if (action) {
        actionInfo = {
          action: action,
          app_id: app_id,
          model_id: model_id,
        };
      } else {
        actionInfo = {
          action: "normal",
        };
      }

      if (token_url && refresh_token) {
        await initPlatformStore(token_url, refresh_token);
        setActionInfo(actionInfo);
        savePlatformInfo();
        const currentUrl = window.location.href;
        const indexOfQuestionMark = currentUrl.indexOf("?");
        // 如果存在问号，截取问号之前的部分
        if (indexOfQuestionMark !== -1) {
          const newUrl = currentUrl.substring(0, indexOfQuestionMark);
          window.location.href = newUrl;
        }
      } else {
        await initPlatformStore();
        setActionInfo(actionInfo);
      }
    };
    initPlatform();
  }, []);

  const handleRefreshDeviceList = async () => {
    try {
      setRefreshing(true);
      const { data } = await getDeviceListApi();
      const deviceList = data.deviceList.map((device) => {
        if (device.info && typeof device.info === "string") {
          const infoString = device.info.replace(/"/g, "");
          const infoParts = infoString.split(";");

          const infoObject = infoParts.reduce((acc, part) => {
            const [key, value] = part.split("=");
            (acc as Record<string, string>)[key] = value;
            return acc;
          }, {} as { sn: string; lastSix: string });

          if (infoObject.sn) {
            infoObject.lastSix = infoObject.sn.slice(-6);
          }

          device.info = infoObject;
        }
        return device;
      });

      const filteredDeviceList = deviceList.reduce((acc, device) => {
        const info = device.info as { sn: string; lastSix: string };
        if (info.sn === deviceInfo?.sn) {
          return acc;
        }
        const existingIndex = acc.findIndex(
          (d) => (d.info as { sn: string }).sn === info.sn
        );

        if (existingIndex === -1) {
          acc.push(device);
        } else {
          const existingDevice = acc[existingIndex];
          const currentType = device.type.replace(/[0-9]/g, "");
          const existingType = existingDevice.type.replace(/[0-9]/g, "");

          if (isValidType(currentType) && isValidType(existingType)) {
            if (typePriority[currentType] < typePriority[existingType]) {
              acc[existingIndex] = device;
            }
          }
        }
        return acc;
      }, [] as typeof deviceList);
      setDevicelist(filteredDeviceList);
      setRefreshing(false);
      setShowDeviceList(filteredDeviceList.length > 0);
    } catch (error) {
      setRefreshing(false);
      console.error("Error fetching DeviceList status:", error);
    }
  };

  useEffect(() => {
    handleRefreshDeviceList();
  }, [deviceInfo?.sn]);

  useEffect(() => {
    if (token && deviceInfo?.ip) {
      getSensecraftUserInfo();
      getAppList();
    }
  }, [deviceInfo?.ip, token]);

  useEffect(() => {
    const initAction = async () => {
      if (actionInfo?.action && token) {
        const action = actionInfo.action; //new / app / clone / model /normal  action为空默认为normal
        const app_id = actionInfo.app_id; //type为app时才需要传
        const model_id = actionInfo.model_id; //type为model时才需要传
        if (action == "app") {
          if (app_id) {
            //打开云端应用
            viewAppForSensecraft(app_id);
          }
        } else if (action == "new") {
          //新建应用
          createAppForSensecraft();
        } else if (action == "clone") {
          //克隆公开的应用到自己的列表
          if (app_id) {
            //克隆公开应用
            cloneAppForSensecraft(app_id);
          }
        } else if (action == "model") {
          //部署模型
          if (model_id) {
            //获取模型详情
            deployAndCreateAppForSensecraft(model_id);
          }
        } else if (action == "normal") {
          checkAndSyncAppData();
        }
        setActionInfo(null);
      }
    };
    initAction();
  }, [actionInfo?.action, token]);

  const getSensecraftUserInfo = async () => {
    try {
      const response = await getSensecraftUserInfoApi();
      if (response.code == 0) {
        const data = response.data;
        const nickname = data.nickname;
        updateNickname(nickname);
        savePlatformInfo();
      }
    } catch (error) {}
  };

  // 获取应用列表
  const getAppList = async () => {
    try {
      const response = await getAppListApi();
      if (response.code == 0) {
        const data = response.data;
        const list = data.list;
        setApplist(list);
      }
    } catch (error) {
      setApplist([]);
    }
  };

  const getModelInfo = async () => {
    try {
      const response = await getModelInfoApi();
      if (response.code == 0) {
        const data = response.data;
        if (data?.model_info) {
          const model_data = JSON.parse(data.model_info);
          return {
            model_data: model_data as IModelData,
            model_md5: data.model_md5,
          };
        }
      }
      throw null;
    } catch (error) {
      return { model_data: null, model_md5: null };
    }
  };

  //将云端模型上传到设备
  const uploadModel = async (model_data: IModelData) => {
    if (model_data) {
      const url = model_data.arguments?.url;
      const model_md5 = model_data.model_md5;
      if (model_md5) {
        const { model_md5: md5 } = await getModelInfo();
        //如果模型md5没有变化，则不需要重新下载模型上传
        if (model_md5 == md5) {
          return true;
        }
      }
      //是否预置模型
      const isPreset =
        model_data.model_id == "10001" ||
        model_data.model_id == "10002" ||
        model_data.model_id == "10003" ||
        model_data.model_id == "10004";

      if (isPreset || url) {
        try {
          setLoading(true);
          setLoadingTip("Uploading model to reCamera");
          const formData = new FormData();
          //如果是设备预置模型，只需要更新描述信息
          if (!isPreset) {
            const response = await fetch(
              `${url}?timestamp=${new Date().getTime()}`
            );
            const blob = await response.blob();
            formData.append("model_file", blob); // 文件名可以根据需要修改
          }
          formData.append("model_info", JSON.stringify(model_data));
          const resp = await uploadModelApi(formData);
          setLoading(false);
          setLoadingTip("");
          const ret = resp.code == 0;
          if (!ret) {
            messageApi.error("Upload model failed");
          }
          return ret;
        } catch (error) {
          console.log(error);
          setLoading(false);
          setLoadingTip("");
          messageApi.error("Upload model failed");
          return false;
        }
      }
    }
    return true;
  };

  //获取应用详情
  const getAppInfo = async (appid?: string) => {
    try {
      if (!appid) {
        return null;
      }
      const response = await viewAppApi(appid);
      if (response.code == 0) {
        return response.data;
      }
      return null;
    } catch (error) {
      return null;
    }
  };

  // 获取本地模型描述文件及模型MD5
  const getLocalModel = async (flowsData: [] | null | undefined) => {
    try {
      //判断flow里面有没有模型积木，如果有模型积木，则需要处理模型文件的下载更新
      const hasModel = flowsData?.some((node: any) => node.type === "model");
      if (hasModel) {
        // 查询设备本地模型信息与模型MD5
        const { model_data: data, model_md5: md5 } = await getModelInfo();
        const model_data = data;
        if (model_data) {
          model_data.model_md5 = md5;
        }
        return model_data;
      } else {
        return null;
      }
    } catch (error) {
      return null;
    }
  };

  //往nodered更新flow
  const sendFlow = async (flows?: string) => {
    try {
      const revision = await saveFlows(flows);
      if (revision) {
        revRef.current = revision;
        const response = await getFlowsState();
        if (response?.state == "stop") {
          await setFlowsState({ state: "start" });
        }
        setTimestamp(new Date().getTime());
      }
    } catch (error) {
      //
      console.log(error);
    }
  };

  // 判断本地应用和云端应用是否一致
  const isCloudAppSameAsLocal = (
    localFlows: string,
    localModel: IModelData | null,
    cloudApp: IAppInfo
  ) => {
    const isFlowDataEqual =
      (localFlows === "" && cloudApp.flow_data === "[]") ||
      (localFlows === "[]" && cloudApp.flow_data === "") ||
      localFlows === cloudApp.flow_data;
    // 判断本地模型MD5是否变化
    const isLocalModelUnchanged =
      cloudApp.model_data.model_id === "0" &&
      localModel?.model_md5 === cloudApp.model_data.model_md5;
    // 判断是否本地模型
    const isNonLocalModel = cloudApp.model_data.model_id !== "0";
    return isFlowDataEqual && (isLocalModelUnchanged || isNonLocalModel);
  };

  // 从平台携带应用id打开云端应用
  const viewAppForSensecraft = async (app_id: string) => {
    try {
      setLoading(true);
      setLoadingTip("Loading app");
      const isSaveSuccess = await checkAndSaveLocalApp();
      if (isSaveSuccess) {
        //查询应用详情
        const cloudApp = await getAppInfo(app_id);
        if (cloudApp) {
          //更新
          syncCloudAppToLocal(cloudApp);
        }
      } else {
        messageApi.error("Load app failed");
      }
      setLoading(false);
      setLoadingTip("");
    } catch (error) {
      setLoading(false);
      setLoadingTip("");
    }
  };

  // 从平台克隆公开应用
  const cloneAppForSensecraft = async (app_id: string) => {
    try {
      setLoading(true);
      setLoadingTip("Cloning app");
      const isSaveSuccess = await checkAndSaveLocalApp();
      if (isSaveSuccess) {
        //查询应用详情
        const cloudApp = await getAppInfo(app_id);
        if (cloudApp) {
          const model_data = cloudApp.model_data;
          if (model_data) {
            //上传设备本地
            const ret = await uploadModel(model_data);
            if (!ret) {
              messageApi.error("Clone app failed");
              return;
            }
          }
          await createAppAndUpdateFlow({
            app_name: `${cloudApp.app_name}_clone`,
            flow_data: cloudApp.flow_data,
            model_data: model_data,
            needUpdateFlow: true,
          });
        } else {
          messageApi.error("App is not exist");
        }
      } else {
        messageApi.error("Clone app failed");
      }
      setLoading(false);
      setLoadingTip("");
    } catch (error) {
      messageApi.error("Clone app failed");
      setLoading(false);
      setLoadingTip("");
    }
  };

  // 从平台新建应用
  const createAppForSensecraft = async () => {
    try {
      setLoading(true);
      setLoadingTip("Creating App");
      const isSaveSuccess = await checkAndSaveLocalApp();
      if (isSaveSuccess) {
        // 创建新的应用覆盖本地应用
        await createAppAndUpdateFlow({
          needUpdateFlow: true,
        });
      } else {
        messageApi.error("Create app failed");
      }
      setLoading(false);
      setLoadingTip("");
    } catch (error) {
      setLoading(false);
      setLoadingTip("");
      messageApi.error("Create app failed");
    }
  };

  //从平台部署模型
  const deployAndCreateAppForSensecraft = async (model_id: string) => {
    try {
      setLoading(true);
      setLoadingTip("Deploying model");
      // 获取模型下载地址
      const response = await applyModelApi(model_id);
      if (response.code == 0) {
        const data = response.data;
        const model_snapshot = data.model_snapshot;
        if (model_snapshot) {
          //上传设备本地
          const ret = await uploadModel(model_snapshot);
          if (ret) {
            await createAppAndUpdateFlow({
              flow_data: DefaultFlowData,
              model_data: model_snapshot,
              needUpdateFlow: true,
            });
          }
          return;
        }
      }
      messageApi.error("Deploy model failed");
      setLoading(false);
      setLoadingTip("");
    } catch (error) {
      messageApi.error("Deploy model failed");
      setLoading(false);
      setLoadingTip("");
    }
  };

  //检查提示用户当前应用是不是需要保存，如果需要就保存
  const checkAndSaveLocalApp = async () => {
    try {
      // 查询当前应用的云端数据
      const cloudApp = await getAppInfo(appInfo?.app_id);
      // 查询当前应用的本地flow数据
      const localFlowsData = await getFlows();
      const localFlowsDataStr = JSON.stringify(localFlowsData);
      // 查询当前应用的模型数据
      const model_data = await getLocalModel(localFlowsData);
      if (cloudApp) {
        // 如果当前应用的云端数据和本地数据不一致，需要提示用户保存
        const needConfirm = !isCloudAppSameAsLocal(
          localFlowsDataStr,
          model_data,
          cloudApp
        );
        if (needConfirm) {
          const config = {
            title: `Are you sure to save ${cloudApp.app_name}`,
            content: (
              <div>
                <p className="mb-16">A new application will be created.</p>
                <p>Do you want to save the current application?</p>
              </div>
            ),
          };
          const confirmed = await modal.confirm(config);
          // 保存当前应用到云端
          if (confirmed) {
            const ret = await syncLocalAppToCloud({
              cloudApp,
              flow_data_str: localFlowsDataStr,
              model_data: model_data,
            });
            return ret;
          }
          return true;
        }
      } else {
        // 如果本地flow是空的，则不需要提示保存
        if (localFlowsDataStr !== "" && localFlowsDataStr !== "[]") {
          const config = {
            title: `Save current device data`,
            content: (
              <div>
                <p className="mb-16">A new application will be created.</p>
                <p>Do you want to save the current device data?</p>
              </div>
            ),
          };
          const confirmed = await modal.confirm(config);
          // 保存当前应用到云端
          if (confirmed) {
            // 给设备当前应用创建app
            const firstTabNode = localFlowsData?.find(
              (node: any) => node.type === "tab"
            ) as any;
            let app_name;
            if (firstTabNode) {
              app_name = firstTabNode.label;
            }
            await createAppAndUpdateFlow({
              app_name,
              flow_data: localFlowsDataStr,
              model_data: model_data,
              needUpdateApp: false,
            });
          }
          return true;
        }
      }
      return true;
    } catch (error) {
      return false;
    }
  };

  // 检查本地应用是否存在，如果本地应用不存在则新建应用，如果本地应用存在，则与云端应用对比，提示用户使用哪个版本
  const checkAndSyncAppData = async () => {
    try {
      // 查询当前应用的云端数据
      const cloudApp = await getAppInfo(appInfo?.app_id);
      // 查询当前应用的本地flow数据
      const localFlowsData = await getFlows();
      const localFlowsDataStr = JSON.stringify(localFlowsData);
      // 查询当前应用的模型数据
      const model_data = await getLocalModel(localFlowsData);
      if (cloudApp) {
        const needConfirm = !isCloudAppSameAsLocal(
          localFlowsDataStr,
          model_data,
          cloudApp
        );
        if (needConfirm) {
          const config = {
            title: `Are you sure to overwrite ${cloudApp.app_name}`,
            content: (
              <div>
                <p className="mb-16">
                  Your app has been updated on other devices.
                </p>
                <p>
                  Do you want to overwrite the device data with the cloud data?
                </p>
              </div>
            ),
          };
          const confirmed = await modal.confirm(config);
          //将云端版本更新到设备
          if (confirmed) {
            syncCloudAppToLocal(cloudApp);
          } else {
            //保存当前应用到云端
            const ret = await syncLocalAppToCloud({
              cloudApp,
              flow_data_str: localFlowsDataStr,
              model_data: model_data,
            });
            return ret;
          }
        }
      } else {
        // 给设备当前应用创建app
        const firstTabItem = localFlowsData?.find(
          (node: any) => node.type === "tab"
        ) as any;
        let app_name;
        if (firstTabItem) {
          app_name = firstTabItem.label;
        }
        await createAppAndUpdateFlow({
          app_name,
          flow_data: localFlowsDataStr,
          model_data: model_data,
        });
      }
    } catch (error) {}
  };

  //将云端数据同步到本地
  const syncCloudAppToLocal = async (app?: IAppInfo) => {
    if (!app) {
      return;
    }
    try {
      setLoading(true);
      setLoadingTip(
        "Syncing SenseCraft Cloud application to Node-red. The flow will be automatically deploy on the device."
      );
      let ret = true;
      if (app?.model_data) {
        ret = await uploadModel(app.model_data);
      }
      if (ret) {
        await sendFlow(app?.flow_data);
        updateAppInfo(app);
        savePlatformInfo();
      } else {
        messageApi.error("Upload model failed");
      }
      setLoading(false);
    } catch (error) {
      setLoading(false);
    }
  };

  // 同步当前应用到云端
  const syncLocalAppToCloud = async ({
    cloudApp,
    flow_data_str,
    model_data,
  }: {
    cloudApp: IAppInfo;
    flow_data_str?: string;
    model_data?: IModelData | null;
  }) => {
    try {
      setSyncing(true);
      setLoadingTip("Syncing application with SenseCraft Cloud");
      if (!cloudApp.app_id) {
        setSyncing(false);
        return false;
      }

      let needUpdate = false;
      needUpdate = cloudApp.flow_data !== flow_data_str;

      if (model_data) {
        const model_id = model_data.model_id;
        // 判断模型是本地模型还是云端模型 本地模型，需要上传到云端保存
        if (model_id == "0") {
          //判断当前模型的md5有没有变化
          // 如果md5值有变化就重新上传
          // 如果云端应用没有url
          if (
            !cloudApp.model_data.arguments?.url ||
            cloudApp.model_data.model_md5 != model_data.model_md5
          ) {
            const model_name = model_data.model_name;
            const file_name = `${model_name}_${cloudApp.app_id}`;
            // 先从设备拿到模型文件
            const fileRes = await fetch(
              `http://${deviceInfo?.ip}/api/deviceMgr/getModelFile`,
              {
                method: "GET",
                headers: {
                  Authorization: getToken() || "",
                },
              }
            );
            if (fileRes.ok && fileRes.status == 200) {
              const blob = await fileRes.blob();
              // 获取云端文件上传地址
              const response = await acquireFileUrlApi(file_name);
              if (response.code == 0) {
                const data = response.data;
                //上传本地模型到云端
                const fileRes = await fetch(data.upload_url, {
                  method: "put",
                  body: blob,
                  headers: { "Content-Type": "application/octet-stream" },
                });

                if (fileRes.ok) {
                  //将模型在云端的地址保存在应用模型信息
                  model_data.arguments = { url: data.file_url };
                  needUpdate = true;
                } else {
                  setSyncing(false);
                  return false;
                }
              }
            } else {
              setSyncing(false);
              return false;
            }
          }
        }
      }

      if (needUpdate) {
        const response = await updateAppApi({
          app_id: cloudApp.app_id,
          flow_data: flow_data_str,
          model_data: model_data,
        });
        if (response.code == 0) {
          cloudApp.flow_data = flow_data_str || "[]";
          if (model_data) {
            cloudApp.model_data = model_data;
          }
          updateAppInfo(cloudApp);
          savePlatformInfo();
          setSyncing(false);
          return true;
        }
        setSyncing(false);
        return false;
      }
      setSyncing(false);
      return true;
    } catch (error) {
      setSyncing(false);
      return false;
    }
  };

  //创建应用，可能更新flow
  const createAppAndUpdateFlow = async ({
    app_name,
    flow_data,
    model_data,
    needUpdateFlow,
    needUpdateApp = true,
  }: {
    app_name?: string;
    flow_data?: string;
    model_data?: IModelData | null;
    needUpdateFlow?: boolean;
    needUpdateApp?: boolean;
  }) => {
    try {
      setLoading(true);
      setLoadingTip("Creating App");
      const res = await createAppApi({
        app_name: app_name,
        flow_data: flow_data,
        model_data: model_data,
      });

      if (res.code == 0) {
        const response = await getAppListApi();
        if (response.code == 0) {
          const data = response.data;
          const list = data.list;
          if (needUpdateApp && list.length > 0) {
            const app = list[0];
            await syncLocalAppToCloud({
              cloudApp: app,
              flow_data_str: flow_data,
              model_data: model_data,
            });
            if (needUpdateFlow) {
              await sendFlow(app.flow_data);
            }
            updateAppInfo(app);
            savePlatformInfo();
          }
          setApplist(list);
          messageApi.success("Create app successful");
          setLoading(false);
          setLoadingTip("");
          return true;
        }
      }
      messageApi.error("Create app failed");
      setLoading(false);
      setLoadingTip("");
      return false;
    } catch (error) {
      messageApi.error("Create app failed");
      setLoading(false);
      setLoadingTip("");
      return false;
    }
  };

  const saveApp = async () => {
    try {
      const localPlatformData = await getLocalPlatformInfo();
      if (!localPlatformData) {
        return;
      }
      const { user_info: localUserInfo, app_info: localAppInfo } =
        localPlatformData;

      // 当前账号变化
      if (localUserInfo.token != token) {
        Modal.info({
          title: "SenseCraft Account has been changed",
          content: (
            <div>
              <p>
                It looks like the SenseCraft Account has been changed on this
                device. The application list is now changed.
              </p>
            </div>
          ),
        });
        setTimestamp(new Date().getTime());
        return;
      }

      if (appInfo?.app_id != localAppInfo.app_id) {
        setTimestamp(new Date().getTime());
        getAppList();
        Modal.info({
          title: "Flow has been changed",
          content: (
            <div>
              <p>
                Due to the device limitation, please notice that only one flow
                can be deployed on the device. The flow has been changed to the
                current flow that is running on the device at this moment.
              </p>
            </div>
          ),
        });
      } else {
        setSyncing(true);
        // 查询当前应用的本地flow数据
        const localFlowsData = await getFlows();
        // 查询当前应用的模型数据
        const model_data = await getLocalModel(localFlowsData);
        const localFlowsDataStr = JSON.stringify(localFlowsData);

        await syncLocalAppToCloud({
          cloudApp: localAppInfo,
          flow_data_str: localFlowsDataStr,
          model_data: model_data,
        });
        const app = applist.find((item) => item.app_id === localAppInfo.app_id);
        if (app) {
          app.flow_data = localAppInfo.flow_data;
          app.model_data = localAppInfo.model_data;
        }
      }
    } catch (error) {
      console.log(error);
    } finally {
      setSyncing(false);
    }
  };

  const onReceivedDeployData = (revision: string | null | undefined) => {
    // 如果版本不一样，说明是通过nodered触发的部署
    if (revRef.current != revision) {
      saveApp();
    }
  };

  const handleCreateApp = async () => {
    try {
      inputRef.current = "";
      const config = {
        title: "New Application",
        content: (
          <Input
            placeholder="Please input application name"
            maxLength={32}
            defaultValue={inputRef.current}
            onChange={handleInputNameChange}
          />
        ),
      };
      const confirmed = await modal.confirm(config);
      if (confirmed) {
        await createAppAndUpdateFlow({
          app_name: inputRef.current,
          needUpdateFlow: true,
        });
      }
    } catch (error) {
      messageApi.error("Create app failed");
    }
  };

  const handleEditApp = async (appId: string) => {
    try {
      const currApp = applist.find((app) => app.app_id == appId);
      if (!currApp) {
        return;
      }
      inputRef.current = currApp.app_name;
      const config = {
        title: "Edit Application name",
        content: (
          <Input
            placeholder="Please input application name"
            maxLength={32}
            defaultValue={inputRef.current}
            onChange={handleInputNameChange}
          />
        ),
      };
      const confirmed = await modal.confirm(config);
      if (confirmed) {
        const response = await updateAppApi({
          app_id: appId,
          app_name: inputRef.current,
        });
        if (response.code == 0) {
          currApp.app_name = inputRef.current;
          setApplist(applist);
        }
      }
    } catch (error) {}
  };

  const handleDeleteApp = async (app: IAppInfo) => {
    const config = {
      title: `Are you sure to delete ${app.app_name}`,
      content: (
        <div>
          <p className="mb-16">
            You are about to permanently delete this project. This action cannot
            be undone.
          </p>
          <p>
            Please ensure that you have backed up any essential information
            before proceeding. Are you sure you want to continue with the
            deletion?
          </p>
        </div>
      ),
      okButtonProps: {
        type: "primary",
        danger: true,
      } as ButtonProps,
      okText: "Delete",
    };
    const confirmed = await modal.confirm(config);
    if (confirmed) {
      const response = await deleteAppApi({ app_id: app.app_id });
      if (response.code == 0) {
        const model_data = app.model_data;
        //如果是本地模型。则把本地模型在云端的存储也删掉
        if (model_data.model_id == "0") {
          const model_name = model_data.model_name;
          const file_name = `${model_name}_${app.app_id}`;
          //异步删除就好，不需要考虑结果
          removeFileApi(file_name);
        }

        const updatedAppList = applist.filter(
          (item) => item.app_id !== app.app_id
        );
        setApplist(updatedAppList);
        // 如果删除的是当前应用则切换为第一个应用
        if (app.app_id == appInfo?.app_id) {
          syncCloudAppToLocal(updatedAppList[0]);
        }
      }
    }
  };

  const handleSelectApp = async (app: IAppInfo) => {
    if (app.app_id != appInfo?.app_id) {
      await syncCloudAppToLocal(app);
    }
  };

  const handleLogout = async () => {
    const config = {
      title: "Are you sure to log out?",
      content: (
        <div>
          <p className="mb-16">
            After log out, you will lose the access to other models on
            SenseCraft, and your application will not be auto backup in cloud.
          </p>
          <p>
            Please ensure to deploy the flow to save all information on the
            device.
          </p>
        </div>
      ),
      okButtonProps: {
        type: "primary",
        danger: true,
      } as ButtonProps,
      okText: "Log Out",
    };
    const confirmed = await modal.confirm(config);
    if (confirmed) {
      logout();
    }
  };

  const handleInputNameChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    inputRef.current = e.target.value;
  };

  const handleFocusApp = async (appId: string) => {
    setFocusAppid(appId);
  };

  const handleBlurApp = async () => {
    setFocusAppid("");
  };

  const handleCollapseExpand = () => {
    setIsExpand(!isExpand);
  };

  const handleShowDeviceList = () => {
    if (!showDeviceList) {
      handleRefreshDeviceList();
    } else {
      setShowDeviceList(false);
    }
  };

  const handleNetworkModalOk = () => {
    setIsNetworkModalOpen(false);
  };

  const handleNetworkModalCancel = () => {
    setIsNetworkModalOpen(false);
  };

  const showNetworkModal = () => {
    setIsNetworkModalOpen(true);
  };

  const gotoConfig = () => {
    window.open(`http://${deviceInfo?.ip}/#/init`, "_blank");
  };

  const gotoOtherDevice = (ip: string) => {
    window.open(`http://${ip}/#/workspace`, "_blank");
  };

  const gotoWiki = () => {
    window.open(
      "https://wiki.seeedstudio.com/recamera_getting_started/",
      "_blank"
    );
  };

  const gotoDashboard = () => {
    window.open(`http://${deviceInfo?.ip}/#/dashboard`, "_blank");
  };

  return (
    <div className="flex h-full">
      <Spin spinning={loading} tip={loadingTip} fullscreen></Spin>
      {isExpand ? (
        <div className="flex flex-col justify-between w-320 bg-background relative p-24 pr-30 overflow-y-auto">
          {deviceInfo?.ip && (
            <div className="mb-10">
              <div className="text-20 font-semibold mb-12">My Device</div>
              <div className="max-h-400 overflow-y-auto">
                <div className="bg-selected rounded-4 p-8 border border-primary mb-12">
                  <div className="flex items-center">
                    <img className="w-24 mr-8" src={recamera_logo} />
                    <div className="text-primary text-18 font-medium overflow-hidden text-ellipsis whitespace-nowrap">
                      {deviceInfo?.deviceName}
                    </div>
                  </div>
                  <div className="flex pt-6 text-text">
                    <span className="w-24 text-12">IP:</span>
                    <span className="text-12 ml-6">{deviceInfo?.ip}</span>
                  </div>
                  <div className="flex pt-5 text-text">
                    <span className="w-24 text-12">OS:</span>
                    <span className="text-12 ml-6">
                      {deviceInfo?.osVersion}
                    </span>
                  </div>
                  <div className="flex pt-5 text-text">
                    <span className="w-24 text-12">S/N:</span>
                    <span className="text-12 ml-6">{deviceInfo?.sn}</span>
                  </div>
                  <div className="flex mt-6">
                    <Button
                      className="mx-auto text-primary text-12 rounded-24 h-24"
                      icon={<SettingOutlined />}
                      onClick={gotoConfig}
                    >
                      Setting
                    </Button>
                    <Button
                      className="mx-auto text-primary text-12 rounded-24 h-24"
                      icon={<WifiOutlined />}
                      onClick={showNetworkModal}
                    >
                      Network
                    </Button>
                  </div>
                </div>

                <Spin spinning={refreshing}>
                  <div className="rounded-4 p-8 border border-disable">
                    <div className="flex justify-between items-center text-12 text-primary">
                      <div>View device under same network</div>
                      <div
                        className="cursor-pointer"
                        onClick={handleShowDeviceList}
                      >
                        {showDeviceList ? <UpOutlined /> : <DownOutlined />}
                      </div>
                    </div>
                    {showDeviceList && devicelist?.length > 0 && (
                      <div className="max-h-200 overflow-y-auto mt-8">
                        {devicelist.map((device, index) => (
                          <div
                            key={index}
                            className="bg-background mb-8 p-4 rounded-4 hover:bg-selected cursor-pointer"
                            onClick={() => gotoOtherDevice(device.ip)}
                          >
                            <div className="text-14 text-3d overflow-hidden text-ellipsis whitespace-nowrap mb-4">
                              {device.device}
                            </div>
                            <div className="flex justify-between text-12 text-text">
                              <div>IP: {device.ip}</div>
                              <div>
                                S/N Last 6:{" "}
                                {typeof device.info == "object" &&
                                  device.info.lastSix}
                              </div>
                            </div>
                          </div>
                        ))}
                      </div>
                    )}
                  </div>
                </Spin>
                <div className="flex mt-10">
                  <Button
                    className="mx-auto text-12 rounded-24 h-24"
                    type="primary"
                    disabled={refreshing}
                    onClick={handleRefreshDeviceList}
                  >
                    Refresh
                  </Button>
                </div>
              </div>
            </div>
          )}
          <div className="flex flex-col">
            <div className="flex justify-between mb-12">
              <div className="text-20 font-semibold">My Application</div>
              {token && (
                <PlusCircleOutlined
                  className="text-primary text-20"
                  onClick={handleCreateApp}
                />
              )}
            </div>
            {token ? (
              <div className="flex flex-col">
                <div className="max-h-200 overflow-y-auto">
                  {applist?.length > 0 &&
                    applist.map((app, index) =>
                      appInfo?.app_id == app.app_id ? (
                        <div key={index} className="flex mb-10 mr-6 h-40">
                          <div
                            className="flex flex-1 text-14 text-primary border border-primary rounded-4 p-8"
                            onMouseEnter={() => handleFocusApp(app.app_id)}
                            onMouseLeave={() => handleBlurApp()}
                          >
                            <div
                              className="flex flex-1 font-medium cursor-pointer overflow-hidden text-ellipsis whitespace-nowrap"
                              onClick={() => handleSelectApp(app)}
                            >
                              {app.app_name}
                            </div>
                            <div
                              className={`flex ${
                                focusAppid == app.app_id ? "flex" : "hidden"
                              }`}
                            >
                              <EditOutlined
                                className="mr-5 ml-5 pt-5 pb-5"
                                onClick={() => handleEditApp(app.app_id)}
                              />
                              {applist.length > 1 && (
                                <DeleteOutlined
                                  className="pt-5 pb-5"
                                  onClick={() => handleDeleteApp(app)}
                                />
                              )}
                            </div>
                          </div>

                          {syncing && (
                            <SyncOutlined
                              className="text-disable ml-10 mr-15 text-20"
                              spin
                            />
                          )}
                        </div>
                      ) : (
                        <div
                          key={index}
                          className="flex mb-10 mr-6 h-30 text-12 bg-background text-text border border-disable rounded-4 px-8"
                          onMouseEnter={() => handleFocusApp(app.app_id)}
                          onMouseLeave={() => handleBlurApp()}
                        >
                          <div
                            className="flex flex-1 items-center cursor-pointer overflow-hidden text-ellipsis whitespace-nowrap"
                            onClick={() => handleSelectApp(app)}
                          >
                            {app.app_name}
                          </div>
                          <div
                            className={`flex ${
                              focusAppid == app.app_id ? "flex" : "hidden"
                            }`}
                          >
                            <EditOutlined
                              className="mr-5 ml-5 pt-5 pb-5"
                              onClick={() => handleEditApp(app.app_id)}
                            />
                            {applist.length > 1 && (
                              <DeleteOutlined
                                className="pt-5 pb-5"
                                onClick={() => handleDeleteApp(app)}
                              />
                            )}
                          </div>
                        </div>
                      )
                    )}
                </div>
                <div>
                  <div className="text-text text-12 mt-10 mb-10">
                    reCamera can only run 1 application at a time
                  </div>
                  <div className="flex justify-between items-center">
                    <div className="flex items-center">
                      <div className="flex justify-center items-center w-48 h-48 bg-primary rounded-24">
                        <UserOutlined className="text-white text-28" />
                      </div>
                      <div className="ml-10 max-w-98 overflow-hidden text-ellipsis whitespace-nowrap">
                        {nickname}
                      </div>
                    </div>

                    <ConfigProvider
                      theme={{
                        components: {
                          Button: {
                            defaultHoverBorderColor: "#ff4d4f",
                            defaultHoverColor: "#ff4d4f",
                          },
                        },
                      }}
                    >
                      <Button onClick={handleLogout}>Log out</Button>
                    </ConfigProvider>
                  </div>
                </div>
              </div>
            ) : (
              <Button
                type="primary"
                className="block my-24 mx-auto"
                onClick={sensecraftAuthorize}
              >
                Login to SenseCraft
              </Button>
            )}
          </div>
          <div className={styles.collapse} onClick={handleCollapseExpand}>
            <LeftOutlined />
          </div>
        </div>
      ) : (
        <div className="flex justify-center items-center w-40 bg-background relative">
          <div className={styles.expand} onClick={handleCollapseExpand}>
            <RightOutlined />
          </div>
        </div>
      )}
      <div className="flex-1">
        {deviceInfo?.ip && (
          <div className="w-full h-full relative overflow-hidden">
            <NodeRed
              ip={deviceInfo.ip}
              timestamp={timestamp}
              onReceivedDeployData={onReceivedDeployData}
            />
            <Button
              className={styles.wiki}
              onClick={gotoWiki}
              icon={<FileOutlined />}
            >
              reCamera Wiki
            </Button>
            <Button
              className={styles.dashboard}
              type="primary"
              onClick={gotoDashboard}
            >
              Dashboard
            </Button>
          </div>
        )}
      </div>
      <Modal
        title="Network"
        open={isNetworkModalOpen}
        destroyOnClose
        onCancel={handleNetworkModalCancel}
        footer={
          <Button type="primary" onClick={handleNetworkModalOk}>
            OK
          </Button>
        }
      >
        <div className={styles.networkModal}>
          <Network />
        </div>
      </Modal>
      {messageContextHolder}
      {modalContextHolder}
    </div>
  );
};

export default Workspace;
