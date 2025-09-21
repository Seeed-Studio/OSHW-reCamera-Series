import React from "react";
import { useMediaQuery } from "react-responsive";
import { Popup, Button } from "antd-mobile";
import { Button as AntdButton, Modal } from "antd";
import { PopupProps } from "antd-mobile/es/components/popup";
import { CloseOutline } from "antd-mobile-icons";
export interface MyPopupProps extends PopupProps {
  onCancel: () => void;
  title?: string;
  onConfirm?: () => void;
  okText?: string;
}

const CommonPopup: React.FC<MyPopupProps> = ({
  title = "",
  onConfirm,
  onCancel,
  okText = "Save",
  children,
  position = "bottom",
  ...restProps
}) => {
  const isMobile = useMediaQuery({ maxWidth: 767 });

  return isMobile ? (
    <Popup
      bodyStyle={{ borderRadius: "16px 16px 0 0" }}
      position={position}
      {...restProps}
    >
      <div className="p-24 pb-30">
        <div className="flex text-18 font-bold relative mb-20">
          <span>{title}</span>
          <CloseOutline onClick={onCancel} className="absolute right-0 top-4" />
        </div>
        {children}
        {onConfirm && (
          <div className="mt-24">
            <Button className="w-full" color="primary">
              {okText}
            </Button>
          </div>
        )}
      </div>
    </Popup>
  ) : (
    <Modal
      title={title}
      centered
      open={restProps.visible}
      onCancel={onCancel}
      footer={
        onConfirm ? (
          <AntdButton type="primary" onClick={onConfirm}>
            {okText}
          </AntdButton>
        ) : null
      }
    >
      {children}
    </Modal>
  );
};

export default CommonPopup;
