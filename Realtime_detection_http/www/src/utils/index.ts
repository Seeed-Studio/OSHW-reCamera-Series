import CryptoJS from "crypto-js";

//信号强度转换
export function getSignalStrengthLevel(rssi: number) {
  if (rssi >= -60) {
    return 4;
  } else if (rssi >= -70) {
    return 3;
  } else if (rssi >= -80) {
    return 2;
  } else {
    return 1;
  }
}

/**
 * @description 将url请求参数转为json格式
 * @param url
 * @returns {{}|any}
 */
export function parseUrlParam(url: string): {} | any {
  try {
    const search = url.split("?")[1];
    if (!search) {
      return {};
    }
    return JSON.parse(
      '{"' +
        decodeURIComponent(search)
          .replace(/"/g, '\\"')
          .replace(/&/g, '","')
          .replace(/=/g, '":"')
          .replace(/\+/g, " ") +
        '"}'
    );
  } catch (error) {
    return {};
  }
}

//是否开发环境
export const isDev = import.meta.env.MODE === "development";

export const sensecraftAuthorize = () => {
  window.location.href = `${
    import.meta.env.VITE_AUTHORIZE_URL
  }?response_type=token&client_id=seeed_recamera&scop=profile&redirec_url=${
    window.location.href
  }`;
};

const EncryptKey = "zqCwT7H7!rNdP3wL"; // 16 字节密钥

export const encryptPassword = (password: string) => {
  const key = CryptoJS.enc.Utf8.parse(EncryptKey); // 16 字节密钥

  const encrypted = CryptoJS.AES.encrypt(password, key, {
    mode: CryptoJS.mode.ECB,
    padding: CryptoJS.pad.ZeroPadding,
  });

  const encryptedPassword = encrypted.ciphertext.toString(CryptoJS.enc.Hex);

  return encryptedPassword;
};

export const DefaultFlowData =
  '[{"id":"30a71ccb9b1d15ef","type":"tab","label":"Flow 1","disabled":false,"info":"","env":[]},{"id":"9d4b3a6a5e8eaea6","type":"sscma","host":"localhost","mqttport":"1883","apiport":"80","clientid":"recamera","username":"","password":""},{"id":"144cb94c134b5e2a","type":"camera","z":"30a71ccb9b1d15ef","option":0,"light":false,"client":"9d4b3a6a5e8eaea6","x":150,"y":140,"wires":[["a7f38a5be039ae97"]]},{"id":"a7f38a5be039ae97","type":"model","z":"30a71ccb9b1d15ef","name":"","uri":"","model":"Gesture Detection","tscore":0.45,"tiou":0.25,"debug":false,"trace":false,"counting":false,"classes":"paper,rock,scissors","splitter":"0,0,0,0","client":"9d4b3a6a5e8eaea6","x":350,"y":140,"wires":[[]]}]';

export const Version = "2025-04-29 18:00";
