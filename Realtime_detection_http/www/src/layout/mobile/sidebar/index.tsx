import { useState } from "react";
import { Popup } from "antd-mobile";
import OverviewImg from "@/assets/images/svg/overview.svg";
import SecurityImg from "@/assets/images/svg/security.svg";
import NetworkImg from "@/assets/images/svg/network.svg";
import TerminalImg from "@/assets/images/svg/terminal.svg";
import SystemImg from "@/assets/images/svg/system.svg";
import PowerImg from "@/assets/images/svg/power.svg";
import ApplicationImg from "@/assets/images/svg/application.svg";
import { useLocation, useNavigate } from "react-router-dom";
import useConfigStore from "@/store/config";
import { MenuOutlined } from "@ant-design/icons";

function Sidebar() {
  const location = useLocation();
  const currentRoute = location.pathname;
  const [visible, setVisible] = useState(false);
  const navigate = useNavigate();
  const { deviceInfo } = useConfigStore();

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
  return (
    <div className="inline-block">
      <div
        className="flex p-16 cursor-pointer"
        onClick={() => {
          setVisible(true);
        }}
      >
        <MenuOutlined />
      </div>

      <Popup
        visible={visible}
        onMaskClick={() => {
          setVisible(false);
        }}
        position="left"
        bodyStyle={{ width: "290px" }}
      >
        <div className="pt-80">
          <div className="font-bold text-24 pl-40 pb-24 truncate pr-20">
            {deviceInfo.deviceName}
          </div>
          <div className="border-t ">
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
                              setVisible(false);
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
        </div>
      </Popup>
    </div>
  );
}

export default Sidebar;
