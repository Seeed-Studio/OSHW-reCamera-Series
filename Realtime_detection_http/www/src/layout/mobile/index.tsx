import React from "react";
import Header from "@/layout/mobile/header";

interface Props {
  children: React.ReactNode;
}

const MobileLayout: React.FC<Props> = ({ children }) => {
  return (
    <>
      <Header />
      <div className="flex-1">{children}</div>
    </>
  );
};

export default MobileLayout;
