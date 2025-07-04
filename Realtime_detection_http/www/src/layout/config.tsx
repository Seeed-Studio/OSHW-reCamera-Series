import React, { useState, useEffect } from "react";
import { useMediaQuery } from "react-responsive";
import MobileLayout from "@/layout/mobile";
import PCLayout from "@/layout/pc";
import { parseUrlParam } from "@/utils";

interface Props {
  children: React.ReactNode;
}

const Config: React.FC<Props> = ({ children }) => {
  const isMobile = useMediaQuery({ maxWidth: 767 });
  const [isDashboard, setIsDashboard] = useState(false);

  useEffect(() => {
    const param = parseUrlParam(window.location.href);
    const dashboard = param.dashboard || param.disablelayout;
    setIsDashboard(dashboard == 1);
  }, []);

  return (
    <div className="flex flex-col w-full h-full">
      {isDashboard ? (
        <div className="w-full h-full">{children}</div>
      ) : isMobile ? (
        // 移动端布局
        <MobileLayout>{children}</MobileLayout>
      ) : (
        // PC端布局
        <PCLayout>{children}</PCLayout>
      )}
    </div>
  );
};

export default Config;
