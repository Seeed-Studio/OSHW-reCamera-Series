function getSizeByNumber(maxNum, start = 0, gap = 1) {
  const sizeObj = {};
  for (let index = start; index <= maxNum; index += gap) {
    sizeObj[index] = index;
  }
  return sizeObj;
}

export default {
  content: ["./index.html", "./src/**/*.{js,ts,jsx,tsx}"],
  theme: {
    extend: {
      colors: {
        primary: "#8fc31f",
        "3d": "#3d3d3d",
        background: "#F2F3F1",
        selected: "#F7F9F2",
        disable: "#D2D9C3",
        text: "#878B7E",
        error: "#D54941",
      },
      width: getSizeByNumber(750),
      minWidth: getSizeByNumber(300),
      height: getSizeByNumber(100),
      fontSize: getSizeByNumber(50, 12),
      opacity: getSizeByNumber(1, 0, 0.5),
      borderRadius: getSizeByNumber(25),
      zIndex: getSizeByNumber(100, 0, 10),
      //  -20：处理负数失效问题（-mt-20、-top-20）
      spacing: getSizeByNumber(200, -60),
    },
  },
  plugins: [],
};
