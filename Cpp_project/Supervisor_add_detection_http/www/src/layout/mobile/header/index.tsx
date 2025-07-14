import { useState, useRef, useEffect } from "react";
import Sidebar from "../sidebar/index";
import CommonPopup from "@/components/common-popup";
import EditImg from "@/assets/images/svg/edit.svg";
import { Form, Input, Button } from "antd-mobile";
import { FormInstance } from "antd-mobile/es/components/form";
import useConfigStore from "@/store/config";
import { updateDeviceInfoApi, queryDeviceInfoApi } from "@/api/device/index";
import { getWifiStatusApi } from "@/api/network";
import { requiredTrimValidate } from "@/utils/validate";

interface FormParams {
  deviceName: string;
}

function Header() {
  const [visible, setVisible] = useState(false);
  const formRef = useRef<FormInstance>(null);
  const { deviceInfo, updateDeviceInfo, updateWifiStatus } = useConfigStore();

  const onFinish = async (values: FormParams) => {
    await updateDeviceInfoApi(values);
    onCancel();
    await onQueryDeviceInfo();
  };
  const onCancel = () => {
    setVisible(false);
    resetFields();
  };
  const resetFields = () => {
    formRef.current?.resetFields();
  };
  const onQueryDeviceInfo = async () => {
    const res = await queryDeviceInfoApi();
    updateDeviceInfo(res.data);
  };
  const getWifiStatus = async () => {
    let { data } = await getWifiStatusApi();
    updateWifiStatus(data.status);
  };
  useEffect(() => {
    getWifiStatus();
    onQueryDeviceInfo();
  }, []);
  return (
    <div className="bg-white text-center py-10">
      <div className="text-primary text-18 font-medium relative flex justify-center px-40 pl-50">
        <div className="absolute left-0 -mt-4 ">
          <Sidebar></Sidebar>
        </div>
        <div className="truncate">{deviceInfo?.deviceName}</div>
        <img
          className="w-24 h-24 ml-1 self-center"
          onClick={() => {
            setVisible(true);
          }}
          src={EditImg}
          alt=""
        />
        <CommonPopup
          visible={visible}
          title={"Edit Device Name"}
          onCancel={onCancel}
        >
          <Form
            requiredMarkStyle="none"
            onFinish={onFinish}
            initialValues={{ deviceName: deviceInfo?.deviceName }}
            footer={
              <Button block type="submit" color="primary">
                Save
              </Button>
            }
          >
            <Form.Item
              name="deviceName"
              label="Name"
              rules={[requiredTrimValidate()]}
            >
              <Input placeholder="recamera_132456" maxLength={32} clearable />
            </Form.Item>
          </Form>
        </CommonPopup>
      </div>
      <div className="mt-2 text-black opacity-60">{deviceInfo?.ip}</div>
    </div>
  );
}

export default Header;
