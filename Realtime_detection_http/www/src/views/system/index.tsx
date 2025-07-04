import { useEffect, useMemo, useState } from "react";
import EditBlackImg from "@/assets/images/svg/editBlack.svg";
import ArrowImg from "@/assets/images/svg/downArrow.svg";
import CommonPopup from "@/components/common-popup";
import { Form, Input, Picker, ProgressBar, Mask } from "antd-mobile";
import {
  PickerValue,
  PickerValueExtend,
} from "antd-mobile/es/components/picker";
import { Button } from "antd";
import moment from "moment";
import { useData } from "./hook";
import { DeviceChannleMode, UpdateStatus } from "@/enum";
import { requiredTrimValidate } from "@/utils/validate";
import { parseUrlParam } from "@/utils";
import useConfigStore from "@/store/config";

const channelList = [
  { label: "Self-Host", value: DeviceChannleMode.Self },
  { label: "Seeed-Official", value: DeviceChannleMode.Official },
];
const infoList = [
  { label: "CPU", key: "cpu" },
  { label: "RAM", key: "ram" },
  { label: "NPU", key: "npu" },
  { label: "OS", key: "osVersion" },
];
function System() {
  const {
    deviceInfo,
    addressFormRef,
    onEditServerAddress,
    onCancel,
    onFinish,
    onUpdateCancel,
    onUpdateApply,
    onConfirm,
    onChannelChange,
    onUpdateRestart,
    onUpdateCheck,
  } = useData();

  const { systemUpdateState, setSystemUpdateState } = useConfigStore();

  const [isDashboard, setIsDashboard] = useState(false);
  useEffect(() => {
    const param = parseUrlParam(window.location.href);
    const dashboard = param.dashboard || param.disablelayout;
    setIsDashboard(dashboard == 1);
  }, []);

  const channelLable = useMemo(() => {
    const index = channelList.findIndex(
      (item) => item.value === systemUpdateState.channel
    );
    return index > -1 && channelList[index].label;
  }, [systemUpdateState.channel]);

  return (
    <div className="my-8 p-16">
      <div className="font-bold text-18 mb-14">Update</div>
      <div className="bg-white rounded-20 px-24">
        <div className="flex justify-between pt-24">
          <span className="opacity-60 self-center mr-20">Software Update</span>
          <div className="flex-1 text-right justify-end flex">
            {systemUpdateState.status == UpdateStatus.NoNeedUpdate && (
              <span className="self-center ml-12">Up to Date</span>
            )}
            {systemUpdateState.status == UpdateStatus.Check && (
              <Button type="primary" onClick={() => onUpdateCheck(true)}>
                Check Update
              </Button>
            )}
            {systemUpdateState.status == UpdateStatus.NeedUpdate && (
              <Button type="primary" onClick={onUpdateApply}>
                Update
              </Button>
            )}
            {systemUpdateState.status == UpdateStatus.Updating && (
              <Button onClick={onUpdateCancel}>Cancel</Button>
            )}
            {systemUpdateState.status == UpdateStatus.UpdateDone && (
              <Button type="primary" onClick={onUpdateRestart}>
                Reboot
              </Button>
            )}
          </div>
        </div>
        <div className="flex justify-between py-12 text-3d ">
          {systemUpdateState.status == UpdateStatus.NoNeedUpdate && (
            <span className="text-12">
              Up to date: last checked a minutes ago
            </span>
          )}
          {systemUpdateState.status == UpdateStatus.UpdateDone && (
            <span className="text-12">
              Please reboot the device to finish the update
            </span>
          )}
          {systemUpdateState.status == UpdateStatus.Updating && (
            <div className="w-full mb-8">
              <div className="flex justify-between mb-4">
                <span>{systemUpdateState.percent}%</span>
                <span>{moment().fromNow()}</span>
              </div>
              <div>
                <ProgressBar
                  className="w-full"
                  rounded={false}
                  percent={systemUpdateState.percent}
                />
              </div>
              <div className="mt-8">
                The update can last several minutes depends on the network
                condition
              </div>
            </div>
          )}
        </div>
      </div>
      <div className="font-bold text-18 mb-14 my-24"> Beta Participation</div>

      <div className="bg-white rounded-20 px-24">
        <div className="flex justify-between py-24">
          <span className="opacity-60 mr-20">Channel</span>
          <div
            className="flex-1 text-right justify-end flex"
            onClick={onChannelChange}
          >
            <span>{channelLable}</span>
            <span className="self-center ml-12">
              <img
                className={`w-24 h-24 ml-6 self-center ${
                  systemUpdateState.channelVisible && "rotate-180 "
                }`}
                src={ArrowImg}
                alt=""
              />
            </span>
          </div>
        </div>
        {systemUpdateState.channel == DeviceChannleMode.Self && (
          <div className="flex justify-between py-24 w-full border-t">
            <span className="opacity-60 mr-20">Server Address</span>
            <div
              className="flex-1 text-right justify-end flex truncate"
              onClick={onEditServerAddress}
            >
              <span className="truncate ">{systemUpdateState.address}</span>
              <img
                className="w-24 h-24 ml-6 self-center"
                src={EditBlackImg}
                alt=""
              />
            </div>
          </div>
        )}
      </div>
      <Picker
        columns={[channelList]}
        visible={systemUpdateState.channelVisible}
        onClose={() => {
          setSystemUpdateState({
            channelVisible: false,
          });
        }}
        value={[systemUpdateState.channel] as PickerValue[]}
        onConfirm={
          onConfirm as (value: PickerValue[], extend: PickerValueExtend) => void
        }
      />

      {!isDashboard && (
        <div>
          <div className="font-bold text-18 mb-14 my-24"> System Info</div>
          <div className="bg-white rounded-20 px-24">
            {infoList.map((item, index) => {
              return (
                <div
                  key={item.key}
                  className={`flex justify-between py-24 ${
                    index && "border-t"
                  }`}
                >
                  <span className="opacity-60 text-black mr-20">
                    {item.label}
                  </span>
                  <div className="flex-1 truncate text-right">
                    {item.key == "osVersion"
                      ? `${deviceInfo.osName} ${deviceInfo[item.key]}`
                      : deviceInfo[item.key]}
                  </div>
                </div>
              );
            })}
          </div>
        </div>
      )}

      <CommonPopup
        visible={systemUpdateState.visible}
        title={"Server Address"}
        onCancel={onCancel}
      >
        <Form
          ref={addressFormRef}
          className="border-b-0"
          requiredMarkStyle="none"
          onFinish={onFinish}
          initialValues={{
            serverUrl: systemUpdateState.address,
          }}
          footer={
            <Button block htmlType="submit" type="primary">
              Confirm
            </Button>
          }
        >
          <Form.Item name="serverUrl" label="" rules={[requiredTrimValidate()]}>
            <Input className="border rounded-6 p-10" placeholder="" clearable />
          </Form.Item>
        </Form>
      </CommonPopup>
      <Mask
        visible={systemUpdateState.updateInfoVisible}
        onMaskClick={() =>
          setSystemUpdateState({
            updateInfoVisible: false,
          })
        }
      >
        <div className="px-30 pt-100 pb-100 h-full" style={{ height: "100vh" }}>
          <div className="text-3d bg-white  rounded-16 p-20 h-full flex-1  flex flex-col justify-between">
            <div className="font-bold text-16">reCamera OS Update</div>
            <div className="flex justify-between opacity-60 font-bold mt-6 mb-10">
              <span>Version 15.4</span>
              <span>24/06/2024</span>
            </div>
            <div className="flex-1 overflow-y-auto">
              <div className="text-12">
                channel, and included all the changes have been tested in
                preview
              </div>
            </div>
            <div className="flex mt-20">
              <Button className="flex-1 mr-28" onClick={onUpdateCancel}>
                Cancel
              </Button>
              <Button type="primary" className="flex-1" onClick={onUpdateApply}>
                Apply
              </Button>
            </div>
          </div>
        </div>
      </Mask>
    </div>
  );
}

export default System;
