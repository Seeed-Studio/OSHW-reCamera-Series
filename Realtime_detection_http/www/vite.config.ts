import { defineConfig, loadEnv } from "vite";
import path from "path";
import vitePluginImp from "vite-plugin-imp";
import react from "@vitejs/plugin-react";

const project = (config: { mode: string }) => {
  return defineConfig({
    base: loadEnv(config.mode, process.cwd()).DEV ? "./" : "/",
    resolve: {
      alias: {
        "@": path.join(__dirname, "src"),
      },
      extensions: [".ts", ".js", ".tsx"],
    },
    plugins: [
      react(),
      vitePluginImp({
        libList: [
          {
            libName: "antd-mobile",
            style: () => false,
            libDirectory: "es/components",
            replaceOldImport: true,
          },
          {
            libName: "antd",
            style: (name) => name !== "theme" && `antd/es/${name}/style`,
          },
        ],
      }),
    ],
    build: {
      rollupOptions: {
        input: {
          main: process.env.LANG === "jp" ? "./indexJp.html" : "./index.html",
        },
        output: {
          chunkFileNames: `js/[name].[hash].js`,
          entryFileNames: `js/[name].[hash].js`,
          assetFileNames: `assets/[ext]/[name].[hash].[ext]`,
        },
      },
    },
  });
};
export default project;
