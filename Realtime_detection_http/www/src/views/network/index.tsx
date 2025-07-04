import { Form, Input, Button, Mask, Switch, SpinLoading } from "antd-mobile";
import { Button as AntdButton } from "antd";
import { CloseOutlined } from "@ant-design/icons";
import CommonPopup from "@/components/common-popup";
import WarnImg from "@/assets/images/warn.png";
import LockImg from "@/assets/images/svg/lock.svg";
import ConnectedImg from "@/assets/images/svg/connected.svg";
import WireImg from "@/assets/images/svg/wire.svg";
import Wifi1 from "@/assets/images/svg/wifi_1.svg";
import Wifi2 from "@/assets/images/svg/wifi_2.svg";
import Wifi3 from "@/assets/images/svg/wifi_3.svg";
import Wifi4 from "@/assets/images/svg/wifi_4.svg";
import { EyeInvisibleOutline, EyeOutline } from "antd-mobile-icons";
import { useData, OperateType, FormType } from "./hook";
import { IWifiInfo } from "@/api/network/network";
import {
  WifiAuth,
  WifiConnectedStatus,
  WifiStatus,
  WifiType,
} from "@/enum/network";
import { requiredTrimValidate } from "@/utils/validate";

const wifiImg: {
  [prop: number]: string;
} = {
  1: Wifi1,
  2: Wifi2,
  3: Wifi3,
  4: Wifi4,
};
const wifiInfoList = [
  {
    label: "",
    key: "info",
    children: [
      { label: "Auto Connect", key: "autoConnect", wiredHide: true },
      { label: "Status", key: "connectedStatusText" },
      { label: "MAC Address", key: "macAddress" },
    ],
  },
  {
    label: "IPV4 ADDRESS",
    key: "ipv4",
    children: [
      { label: "IP Address Assignment", key: "ipAssignmentText" },
      { label: "IP Address", key: "ip" },
      { label: "Subnet Mask", key: "subnetMask" },
    ],
  },
];
const titleObj = {
  [FormType.Password]: "Password",
  [FormType.Disabled]: "Disable Wi-Fi",
};
function Network() {
  const {
    state,
    passwordFormRef,
    setStates,
    onSwitchEnabledWifi,
    toggleVisible,
    onConnect,
    onHandleOperate,
    onClickWifiItem,
    handleSwitchWifi,
  } = useData();

  return (
    <div className="px-16 pb-24">
      <div className="text-24 font-bold mt-24">Internet</div>
      {!state.wifiChecked && !state.hasWired && (
        <div className="flex mt-10">
          <img className="w-24" src={WarnImg} alt="" />
          <span className="ml-12 self-center text-16">
            Not connected to a network
          </span>
        </div>
      )}
      {state.wifiList.map((item, i) => {
        return (
          <div key={i} className={` ${item.label && "mt-30"}`}>
            {state.wifiStatus == WifiStatus.Disable
              ? item.key == "Internet"
              : (item.key == "Internet" ||
                  state.wifiChecked ||
                  (item.label &&
                    !state.wifiChecked &&
                    item.key == WifiConnectedStatus.Yes)) && (
                  <div className="flex justify-between mb-20">
                    <div className="font-bold text-18">{item.label}</div>
                    {item.key == WifiConnectedStatus.Yes && (
                      <Switch
                        checked={state.wifiChecked}
                        onChange={onSwitchEnabledWifi}
                      />
                    )}
                  </div>
                )}
            {(item.key || state.wifiStatus != WifiStatus.Close) &&
            item.list?.length ? (
              <div
                className={` ${
                  (state.wifiChecked || item.key == "Internet") && "border-b"
                } text-16`}
              >
                {item.list.map((wifiItem, index) => {
                  return (
                    (state.wifiChecked ||
                      (!state.wifiChecked &&
                        wifiItem.type === WifiType.Wired)) && (
                      <div
                        className="flex justify-between border-t py-10"
                        key={index}
                        onClick={() => onClickWifiItem(item, wifiItem, index)}
                      >
                        <span className="flex flex-1 truncate">
                          {wifiItem.loading && (
                            <SpinLoading
                              color="primary"
                              className="mr-10"
                              style={{ "--size": "18px" }}
                            />
                          )}
                          {wifiItem.ssid == state.deviceWifiInfo?.ssid && (
                            <img
                              className="w-18 mr-12  "
                              src={ConnectedImg}
                              alt=""
                            />
                          )}
                          <span className="self-center truncate">
                            {wifiItem.ssid}
                          </span>
                        </span>
                        <div className="flex">
                          {wifiItem.auth == WifiAuth.Need &&
                            wifiItem &&
                            wifiItem.type == WifiType.Wireless && (
                              <div className="px-12 ">
                                <img
                                  className="w-18 "
                                  src={LockImg}
                                  alt=""
                                  onClick={(event: any) => {
                                    if (event.stopPropagation) {
                                      event.stopPropagation();
                                    } else {
                                      // 对于不支持的浏览器（非常旧的浏览器）
                                      event.cancelBubble = true;
                                    }
                                    onClickWifiItem(
                                      item,
                                      wifiItem,
                                      index,
                                      true
                                    );
                                  }}
                                />
                              </div>
                            )}
                          {wifiItem.type == WifiType.Wireless ? (
                            <img
                              className="w-18"
                              src={wifiImg[wifiItem.signal]}
                              alt=""
                            />
                          ) : (
                            <img className="w-18" src={WireImg} alt="" />
                          )}
                        </div>
                      </div>
                    )
                  );
                })}
              </div>
            ) : (
              ""
            )}
          </div>
        );
      })}
      <CommonPopup
        visible={state.visible}
        title={titleObj[state.formType]}
        onCancel={toggleVisible}
      >
        {state.formType === FormType.Disabled && (
          <div>
            <div className="text-3d text-16 mb-20">
              This action will prevent you from access this web dashboard. Are
              you sure want to turn off it now?
            </div>
            <Button
              block
              shape="rounded"
              type="submit"
              color="danger"
              loading={state.submitLoading}
              onClick={handleSwitchWifi}
            >
              Confirm
            </Button>
          </div>
        )}
        {state.formType === FormType.Password && (
          <Form
            ref={passwordFormRef}
            className="border-b-0"
            requiredMarkStyle="none"
            onFinish={onConnect}
            initialValues={{
              password: state.password,
            }}
            footer={
              <Button
                block
                type="submit"
                color="primary"
                loading={state.submitLoading}
              >
                Confirm
              </Button>
            }
          >
            <Form.Item
              name="password"
              label=""
              rules={[requiredTrimValidate()]}
              extra={
                <div>
                  {!state.passwordVisible ? (
                    <EyeInvisibleOutline
                      fontSize={18}
                      onClick={() =>
                        setStates({
                          passwordVisible: true,
                        })
                      }
                    />
                  ) : (
                    <EyeOutline
                      fontSize={18}
                      onClick={() =>
                        setStates({
                          passwordVisible: false,
                        })
                      }
                    />
                  )}
                </div>
              }
            >
              <Input
                type={state.passwordVisible ? "text" : "password"}
                className="border rounded-6 p-10 pr-6"
                placeholder=""
                clearable
                maxLength={63}
              />
            </Form.Item>
          </Form>
        )}
      </CommonPopup>
      <Mask
        visible={state.wifiVisible}
        onMaskClick={() => {
          setStates({
            wifiVisible: false,
          });
        }}
      >
        <div
          className="absolute"
          style={{
            height: "60%",
            width: "90%",
            left: "50%",
            top: "50%",
            transform: "translate(-50%,-50%)",
            maxWidth: "480px",
          }}
        >
          <div className="h-full p-20 pr-6 bg-white rounded-16">
            <div className="text-3d  pr-14 h-full overflow-y-auto flex-1 flex flex-col justify-between">
              <div className="flex justify-between">
                <div className="font-bold text-16 break-words">
                  {state.curWifiInfo.ssid}
                </div>
                <AntdButton
                  icon={<CloseOutlined />}
                  className="border-none"
                  onClick={() => {
                    setStates({
                      wifiVisible: false,
                    });
                  }}
                />
              </div>
              {state.curWifiInfo.type == WifiType.Wireless && (
                <div className="flex mt-20">
                  {state.curWifiInfo.connectedStatus ==
                  WifiConnectedStatus.No ? (
                    <Button
                      fill="none"
                      size="small"
                      className="flex-1 bg-primary text-white"
                      loading={state.submitLoading}
                      onClick={() => onHandleOperate(OperateType.Connect)}
                    >
                      <span className="text-14">Connect</span>
                    </Button>
                  ) : (
                    <>
                      <Button
                        fill="none"
                        size="small"
                        className="flex-1 mr-28 bg-error text-white"
                        loading={
                          state.submitLoading &&
                          state.submitType == OperateType.Forget
                        }
                        onClick={() => onHandleOperate(OperateType.Forget)}
                      >
                        <span className="text-14">Forget</span>
                      </Button>
                      <Button
                        fill="none"
                        size="small"
                        className="flex-1 bg-primary text-white"
                        loading={
                          state.submitLoading &&
                          state.submitType == OperateType.DisConnect
                        }
                        onClick={() => onHandleOperate(OperateType.DisConnect)}
                      >
                        <span className="text-14">Disconnect</span>
                      </Button>
                    </>
                  )}
                </div>
              )}

              <div className="flex-1 mt-20 border-t">
                {wifiInfoList.map((item, index) => {
                  return (
                    (item.key != "ipv4" ||
                      state.curWifiInfo.type == WifiType.Wired ||
                      state.curWifiInfo.connectedStatus ==
                        WifiConnectedStatus.Yes) && (
                      <div key={index}>
                        {item.label && (
                          <div className="font-bold border-b mt-24 py-6">
                            {item.label}
                          </div>
                        )}
                        {item.children.map((citem, cindex) => {
                          //网络连上了才可以显示auto connect
                          return (
                            (citem.key == "autoConnect" &&
                              state.curWifiInfo.connectedStatus ==
                                WifiConnectedStatus.No) ||
                            ((!citem.wiredHide ||
                              !(state.curWifiInfo.type === WifiType.Wired)) && (
                              <div
                                key={cindex}
                                className={`flex justify-between border-b ${
                                  citem.key !== "autoConnect" && "py-6"
                                }`}
                              >
                                <span className=" self-center">
                                  {citem.label}
                                </span>
                                {citem.key === "autoConnect" ? (
                                  <Switch
                                    checked={state.curWifiInfo.connectChecked}
                                    onChange={() =>
                                      onHandleOperate(OperateType.AutoConnect)
                                    }
                                  />
                                ) : (
                                  <span className="text-8d text-black opacity-60">
                                    {
                                      state.curWifiInfo[
                                        citem.key as keyof IWifiInfo
                                      ]
                                    }
                                  </span>
                                )}
                              </div>
                            ))
                          );
                        })}
                      </div>
                    )
                  );
                })}
              </div>
            </div>
          </div>
        </div>
      </Mask>
    </div>
  );
}

export default Network;
