import { noderedRequest } from "@/utils/request";

// 获取flow数据
export const getFlows = async () => {
  try {
    const response = await noderedRequest<{ flows: [] }>({
      url: "flows",
      method: "get",
    });
    return response?.flows;
  } catch (error) {
    return null;
  }
};

// 给nodered发送flow数据
export const saveFlows = async (data?: string) => {
  let flows = null;
  try {
    flows = data ? JSON.parse(data) : [];
    const response = await noderedRequest<{ rev: string }>({
      url: "flows",
      method: "post",
      data: {
        flows,
      },
    });
    return response?.rev;
  } catch (error) {
    return null;
  }
};

// 获取flow的状态
export const getFlowsState = async () =>
  noderedRequest<{ state: string }>({
    url: "flows/state",
    method: "get",
  });

// 设置flow的状态
export const setFlowsState = async (data: { state: string }) =>
  noderedRequest({
    url: "flows/state",
    method: "post",
    data: JSON.stringify(data),
  });
