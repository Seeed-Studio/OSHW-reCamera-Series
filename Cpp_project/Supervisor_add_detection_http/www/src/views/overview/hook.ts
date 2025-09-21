import { useState, useEffect } from "react";
import useWebSocket from "react-use-websocket";
import { getWebSocketUrlApi } from "@/api";
import jmuxer from "jmuxer";

let jmuxerIns: any;

export default function usehookData() {
  const [socketUrl, setSocketUrl] = useState<string | null>(null);
  const [timeObj, setTimeObj] = useState({
    time: 0,
    delay: 0,
  });
  const { getWebSocket } = useWebSocket(socketUrl, {
    onMessage,
  });
  const getWebsocketUrl = async () => {
    try {
      const { data } = await getWebSocketUrlApi({
        time: Date.now(),
      });
      setSocketUrl(data.websocketUrl);
      // 使用useEffect无效，timeoute替代
      const timer = setTimeout(() => {
        const obj: any = getWebSocket();
        obj && (obj.binaryType = "arraybuffer");

        clearTimeout(timer);
      }, 0);
    } catch (err) {
      console.log("err:", err);
    }
  };

  function onMessage(evt: MessageEvent) {
    var buffer = new Uint8Array(evt.data);
    const lastEight = buffer.slice(-8);
    const dataView = new DataView(lastEight.buffer);
    const high = dataView.getUint32(4, true); // 读取高32位（第5到第8字节）
    const low = dataView.getUint32(0, true); // 读取低32位（第1到第4字节）
    const int64Value = (BigInt(high) << BigInt(32)) | BigInt(low);
    const time = Number(int64Value);
    setTimeObj({
      time: time,
      delay: Date.now() - time,
    });
    if (jmuxerIns) {
      jmuxerIns.feed({
        video: buffer,
      });
    }
  }

  useEffect(() => {
    jmuxerIns = new jmuxer({
      debug: false,
      node: "player",
      mode: "video",
      flushingTime: 0, //以毫秒为单位的缓冲区刷新时间
      fps: 30,
      clearBuffer: true,
    });
    getWebsocketUrl();
    return () => {
      jmuxerIns.destroy();
    };
  }, []);

  return { timeObj };
}
