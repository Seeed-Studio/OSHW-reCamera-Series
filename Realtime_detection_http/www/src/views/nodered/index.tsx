import { useEffect, useRef } from "react";

const NodeRed = ({
  ip,
  timestamp = 1,
  onReceivedDeployData,
}: {
  ip: string;
  timestamp: number;
  onReceivedDeployData?: (revision: string | null | undefined) => void;
}) => {
  const onReceivedDeployDataRef = useRef(onReceivedDeployData);
  const isConnectedRef = useRef(false);
  const isUnmountedRef = useRef(false);
  const socketRef = useRef<WebSocket | null>(null);

  useEffect(() => {
    onReceivedDeployDataRef.current = onReceivedDeployData;
  }, [onReceivedDeployData]);

  const onReceivedMessage = (data: any) => {
    try {
      const message = JSON.parse(data);
      // 查找topic为"notification/runtime-deploy"的消息
      const deployData =
        message.find(
          (item: { topic: string }) =>
            item.topic === "notification/runtime-deploy"
        )?.data || null;

      if (deployData) {
        const revision = deployData.revision;
        onReceivedDeployDataRef.current?.(revision);
      }
    } catch (error) {
      console.error("Error parsing message:", error);
    }
  };

  const connect = () => {
    if (isUnmountedRef.current) return;

    const socket = new WebSocket(`ws://${ip}:1880/comms`);
    socketRef.current = socket;

    socket.onopen = () => {
      console.log("Nodered ws connection established");
      isConnectedRef.current = true;
    };

    socket.onmessage = (event) => {
      onReceivedMessage(event.data);
    };

    socket.onerror = (error) => {
      console.error("Nodered ws error:", error);
      isConnectedRef.current = false;
    };

    socket.onclose = () => {
      console.log("Nodered ws connection closed");
      isConnectedRef.current = false;
    };
  };

  useEffect(() => {
    connect();

    const handleVisibilityChange = () => {
      if (document.visibilityState === "visible" && !isConnectedRef.current) {
        console.log("Nodered ws connection retry");
        connect();
      }
    };

    document.addEventListener("visibilitychange", handleVisibilityChange);

    return () => {
      isUnmountedRef.current = true;
      document.removeEventListener("visibilitychange", handleVisibilityChange);
      if (socketRef.current) {
        socketRef.current.close();
      }
    };
  }, [ip]);

  return (
    <iframe
      className="w-full h-full"
      src={`http://${ip}:1880?timestamp=${timestamp}`}
    />
  );
};

export default NodeRed;
