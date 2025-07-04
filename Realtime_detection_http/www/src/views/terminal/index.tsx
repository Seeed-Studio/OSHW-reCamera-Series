import { useEffect, useState } from "react";

import useConfigStore from "@/store/config";

function WebShell() {
  const { deviceInfo } = useConfigStore();
  const [iframeUrl, setIframeUrl] = useState("");
  useEffect(() => {
    if (deviceInfo) {
      const url =
        import.meta.env.MODE === "development"
          ? "http://192.168.120.99"
          : window.location.origin;
      setIframeUrl(`${url}:${deviceInfo.terminalPort}`);
    }
  }, [deviceInfo]);
  return (
    <div className="w-full h-full">
      <iframe
        src={iframeUrl}
        style={{ width: "100%", height: "100%" }}
      ></iframe>
    </div>
  );
}

export default WebShell;
