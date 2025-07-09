export interface IModelData {
  ai_framwork: string;
  algorithm: string;
  arguments: {
    url: string;
  };

  author: string;
  classes: string[];
  model_format: string;
  model_id: string;
  model_md5: string | null;
  model_name: string;
  model_name_cn: string | null;
  version: string;
  checksum: string | null;
}

export interface IAppInfo {
  app_id: string;
  user_id: string;
  app_name: string;
  flow_data: string;
  model_data: IModelData;
  res_url: string;
  created: number;
  updated: number;
}

export interface IActionInfo {
  action?: string; // new / app / clone / model /normal
  app_id?: string;
  model_id?: string;
}
