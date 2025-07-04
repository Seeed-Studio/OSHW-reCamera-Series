import React, { useState, useEffect } from "react";
import { Modal, Button } from "antd";
import { UpdateStatus, DeviceChannleMode } from "@/enum";
import { ServiceStatus } from "@/enum";
import useConfigStore from "@/store/config";
import Loading from "@/components/loading";

interface Props {
  children: React.ReactNode;
}

const Main: React.FC<Props> = ({ children }) => {
  const [serviceStatus, setServiceStatus] = useState<ServiceStatus>(
    ServiceStatus.STARTING
  );
  const [isNewVersionModalOpen, setIsNewVersionModalOpen] = useState(false);
  const [newVersion, setNewVersion] = useState("");
  const { systemUpdateState, setSystemUpdateState } = useConfigStore();
  const { deviceInfo } = useConfigStore();

  const checkNewVersion = async () => {
    try {
      if (
        deviceInfo.channel == DeviceChannleMode.Official &&
        systemUpdateState.status != UpdateStatus.NeedUpdate
      ) {
        const response = await fetch(
          "https://api.github.com/repos/seeed-Studio/recamera-os/releases/latest"
        );
        if (response.ok && response.status == 200) {
          const data = await response.json();
          const version = data.tag_name;
          if (version != deviceInfo?.osVersion) {
            setNewVersion(version);
            setSystemUpdateState({
              status: UpdateStatus.NeedUpdate,
            });
            setIsNewVersionModalOpen(true);
          }
        }
      }
    } catch (error) {}
  };

  useEffect(() => {
    if (serviceStatus === ServiceStatus.RUNNING) {
      const timer = setTimeout(() => {
        checkNewVersion();
      }, 10000);

      return () => clearTimeout(timer);
    }
  }, [serviceStatus, deviceInfo?.osVersion, systemUpdateState.status]);

  const handleServiceStatusChange = (serviceStatus: ServiceStatus) => {
    setServiceStatus(serviceStatus);
  };

  const handleCancel = () => {
    setIsNewVersionModalOpen(false);
  };

  const handleOk = () => {
    setIsNewVersionModalOpen(false);
    window.location.href = `${window.location.origin}/#/system`;
  };

  return (
    <>
      {serviceStatus === ServiceStatus.RUNNING ? (
        children
      ) : (
        <Loading onServiceStatusChange={handleServiceStatusChange} />
      )}
      <Modal
        title="New Version Release"
        open={isNewVersionModalOpen}
        onCancel={handleCancel}
        footer={
          <Button type="primary" onClick={handleOk}>
            Go to update
          </Button>
        }
      >
        <p style={{ marginBottom: "6px" }}>
          reCamera is now on version {newVersion} now. Check update details
          here:
        </p>
        <a
          href="https://github.com/Seeed-Studio/reCamera-OS/releases"
          style={{
            color: "#4096ff",
          }}
          target="_blank"
        >
          https://github.com/Seeed-Studio/reCamera-OS/releases
        </a>
      </Modal>
    </>
  );
};

export default Main;
