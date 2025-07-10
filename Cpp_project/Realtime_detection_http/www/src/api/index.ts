import {supervisorRequest} from '@/utils/request'

// 获取websocket连接地址
export const getWebSocketUrlApi = async (params: { time: number }) =>
  supervisorRequest<{ websocketUrl: string }>({
    url: 'api/deviceMgr/getCameraWebsocketUrl',
    params,
  })
