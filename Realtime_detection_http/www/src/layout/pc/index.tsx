import React, { useState } from "react";
import { Form, Input, Modal } from "antd";
import useConfigStore from "@/store/config";
import EditImg from "@/assets/images/svg/edit.svg";
import OverviewImg from "@/assets/images/svg/overview.svg";
import SecurityImg from "@/assets/images/svg/security.svg";
import NetworkImg from "@/assets/images/svg/network.svg";
import TerminalImg from "@/assets/images/svg/terminal.svg";
import SystemImg from "@/assets/images/svg/system.svg";
import PowerImg from "@/assets/images/svg/power.svg";
import ApplicationImg from "@/assets/images/svg/application.svg";
import { updateDeviceInfoApi, queryDeviceInfoApi } from "@/api/device/index";
import { requiredTrimValidate } from "@/utils/validate";
import { useLocation, useNavigate } from "react-router-dom";

interface Props {
  children: React.ReactNode;
}

const menuList = [
  [
    {
      label: "Overview",
      icon: OverviewImg,
      route: "/overview",
      judgeApp: true,
    },
    { label: "Workspace", icon: ApplicationImg, route: "/workspace" },
    { label: "Security", icon: SecurityImg, route: "/security" },
    { label: "Network", icon: NetworkImg, route: "/network" },
  ],
  [
    { label: "Terminal", icon: TerminalImg, route: "/terminal" },
    { label: "System", icon: SystemImg, route: "/system" },
    { label: "Power", icon: PowerImg, route: "/power" },
  ],
];

const PCLayout: React.FC<Props> = ({ children }) => {
  const { deviceInfo, updateDeviceInfo } = useConfigStore();
  const [isEditNameModalOpen, setIsEditNameModalOpen] = useState(false);
  const [confirmLoading, setConfirmLoading] = useState(false);
  const location = useLocation();
  const [form] = Form.useForm();
  const currentRoute = location.pathname;
  const navigate = useNavigate();

  const onQueryDeviceInfo = async () => {
    const res = await queryDeviceInfoApi();
    updateDeviceInfo(res.data);
  };

  const handleEditNameOk = async () => {
    const fieldsValue = form.getFieldsValue();
    const deviceName = fieldsValue.deviceName?.trim() || "";
    if (deviceName && deviceName.length > 0) {
      setConfirmLoading(true);
      await updateDeviceInfoApi({
        deviceName: deviceName,
      });
      setIsEditNameModalOpen(false);
      setConfirmLoading(false);
      form.resetFields();
      await onQueryDeviceInfo();
    }
  };

  const handleEditNameCancel = () => {
    setIsEditNameModalOpen(false);
    form.resetFields();
  };

  return (
    <>
      <div className="bg-white text-center py-10 border-b">
        <div className="text-primary text-18 font-medium relative flex justify-center px-40 pl-50">
          <div className="absolute left-0 -mt-4 "></div>
          <div className="truncate">{deviceInfo?.deviceName}</div>
          <img
            className="w-24 h-24 ml-1 self-center cursor-pointer"
            onClick={() => {
              setIsEditNameModalOpen(true);
            }}
            src={EditImg}
            alt=""
          />
        </div>
        <div className="mt-2 text-black opacity-60">{deviceInfo?.ip}</div>
      </div>

      <div className="flex flex-1">
        <div className="h-full w-300 bg-white">
          {menuList.map((item, index) => {
            return (
              <div key={index}>
                <div className={`${index && "border-t"}  mx-20`}></div>
                <div className={`py-14`}>
                  {item.map((citem, cindex) => {
                    return (
                      (deviceInfo.isReCamera || !citem.judgeApp) && (
                        <div
                          className={`px-40 py-10 text-17 flex ${
                            currentRoute === citem.route ? "active" : ""
                          }`}
                          key={`${index}${cindex}`}
                          style={{
                            background:
                              currentRoute === citem.route ? "#ECF4D9" : "",
                          }}
                          onClick={() => {
                            navigate(citem.route);
                          }}
                        >
                          <img
                            className="w-24 h-24 mr-12"
                            src={citem.icon}
                            alt=""
                          />
                          <span>{citem.label}</span>
                        </div>
                      )
                    );
                  })}
                </div>
              </div>
            );
          })}
        </div>
        <div style={{ maxWidth: "900px" }} className="w-full px-48">
          {children}
        </div>
        <div className="flex-1 h-full bg-[#F2F2F2]"></div>
      </div>

      <Modal
        title="Edit Device Name"
        open={isEditNameModalOpen}
        confirmLoading={confirmLoading}
        onOk={handleEditNameOk}
        onCancel={handleEditNameCancel}
      >
        <Form
          form={form}
          name="dependencies"
          autoComplete="off"
          style={{ maxWidth: 600 }}
          layout="vertical"
        >
          <Form.Item
            name="deviceName"
            label="Name"
            rules={[requiredTrimValidate()]}
          >
            <Input placeholder="recamera_132456" maxLength={32} allowClear />
          </Form.Item>
        </Form>
      </Modal>
    </>
  );
};

export default PCLayout;
