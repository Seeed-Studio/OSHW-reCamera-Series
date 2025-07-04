## 项目框架
react+Typescript+Tailwindcss+vite+antd-mobile+zustand

## 项目启动
- 开发环境运行:
```
npm install
npm run dev
```

- 测试环境打包:
```
npm install
npm run staging
```

- 正式环境打包:
```
npm install
npm run staging
```

## 部署到设备
### 一、将编译生成的dist文件夹传到设备
```
1. sftp recamera@192.168.42.1
  ip地址为设备ip地址，通过usb连接则固定为192.168.42.1

2. put -r dist
  dist为项目编译之后的dist本地目录
```

#### 二、将设备中的dist目录拷贝到www目录
```
1. cd /usr/share/supervisor/

2. sudo rm -rf www/
  如果supervisor目录下面有www目录，则需要先删除

3. sudo cp /home/recamera/dist/ www -r

4. sudo reboot
```

访问 http://192.168.42.1


### 项目目录说明

```
├── App.tsx
├── api // api相关
├── assets
│   ├── images
│   └── style
├── components //全局组件相关
├── enum //全局定义的枚举
├── layout //移动端与pc端布局适配
│   ├── mobile //移动端布局
│   ├── pc //PC端布局
│   └── index //响应式切换移动端PC端布局
├── main.tsx
├── router //路由
├── store // 全局状态管理
│   ├── config //设备配置相关
│   ├── platform //Sensecraft平台相关
│   └── user //设备账号密码相关
├── utils // 工具、方法
├── views // 页面
│   ├── dashboard //nodered的dashboard页面的封装
│   ├── login //Sensecraft平台相关 //设备登录页，与其他路由页面平级
│   ├── network //Sensecraft平台相关 //设备网络配置
│   ├── overview //Sensecraft平台相关 //设备预览
│   ├── power //Sensecraft平台相关 //设备开关
│   ├── security //Sensecraft平台相关 //设备安全
│   ├── system //Sensecraft平台相关 //设备系统信息
│   ├── terminal //Sensecraft平台相关 //设备终端
│   └── workspace //Sensecraft平台相关 //Sensecraft工作区
```
