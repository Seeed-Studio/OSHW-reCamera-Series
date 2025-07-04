import {
  LockOutlined,
  UserOutlined,
  InfoCircleOutlined,
} from "@ant-design/icons";
import { Button, Form, Input, Modal, message, Checkbox } from "antd";
import { useState } from "react";
import recameraLogo from "@/assets/images/recamera.png";
import useUserStore from "@/store/user";
import { encryptPassword } from "@/utils";
import { requiredTrimValidate, passwordRules } from "@/utils/validate";
import { loginApi, updateUserPasswordApi } from "@/api/user";

const Login = () => {
  const { firstLogin, updateFirstLogin, updateUserInfo } = useUserStore();

  const [form] = Form.useForm();
  const [messageApi, messageContextHolder] = message.useMessage();
  const [agreed, setAgreed] = useState(false);
  const [showAgreement, setShowAgreement] = useState(false);
  const [passwordErrorMsg, setPasswordErrorMsg] = useState<string | null>(null);

  const handleChangePassword = async () => {
    const fieldsValue = form.getFieldsValue();
    const oldpassword = fieldsValue.oldpassword;
    const newpassword = fieldsValue.newpassword;
    const confirmpassword = fieldsValue.confirmpassword;
    if (
      oldpassword &&
      newpassword &&
      confirmpassword &&
      newpassword == confirmpassword
    ) {
      const encryptedOldpassword = encryptPassword(oldpassword);
      const encryptedNewPassword = encryptPassword(newpassword);
      const response = await updateUserPasswordApi({
        oldPassword: encryptedOldpassword,
        newPassword: encryptedNewPassword,
      });
      if (response.code == 0) {
        messageApi.success("Password changed successfully");
        updateFirstLogin(false);
      } else {
        messageApi.error("Password changed failed");
      }
    }
  };

  const loginAction = async (userName: string, password: string) => {
    try {
      const encryptedPassword = encryptPassword(password);
      const response = await loginApi({
        userName,
        password: encryptedPassword,
      });
      const code = response.code;
      const data = response.data;
      if (code === 0) {
        updateUserInfo({
          userName,
          password: encryptedPassword,
          token: data.token,
        });
        return { success: true };
      }
      // 统一错误信息
      let errorMsg = response.msg || "Login failed";
      if (code === -1 && data && typeof data.retryCount !== "undefined") {
        errorMsg =
          data.retryCount > 0
            ? `${data.retryCount} attempts remaining before temporary lock`
            : "Account locked - Please retry later";
        return { success: false, errorMsg, usePasswordErrorMsg: true };
      }
      return { success: false, errorMsg, usePasswordErrorMsg: false };
    } catch (error) {
      return {
        success: false,
        errorMsg: "Login failed",
        usePasswordErrorMsg: false,
      };
    }
  };

  const onFinish = async (values: { username: string; password: string }) => {
    const userName = values.username;
    const password = values.password;
    const result = await loginAction(userName, password);
    if (!result.success) {
      if (result.usePasswordErrorMsg) {
        setPasswordErrorMsg(result.errorMsg);
      } else {
        setPasswordErrorMsg(null);
        messageApi.error(result.errorMsg);
      }
    } else {
      setPasswordErrorMsg(null);
    }
  };

  const handleAcknowledge = () => {
    setShowAgreement(false);
    setAgreed(true);
  };

  const agreementTitle = (
    <div className="flex items-center">
      <InfoCircleOutlined className="text-primary text-24 mr-12" />
      <span>reCamera Connection Agreement</span>
    </div>
  );

  return (
    <div className="h-full flex flex-col justify-center items-center text-18">
      <img src={recameraLogo} className="w-300" />
      <div className="text-16 w-500 mt-40 mb-40">
        Welcome! Your exciting journey into the realm of Vision AI Platform
        starts right here. Let reCamera redefine your vision of possibilities.
      </div>
      <Form
        className="w-400"
        name="login"
        labelCol={{ span: 6 }}
        wrapperCol={{ span: 18 }}
        initialValues={{ username: "recamera" }}
        onFinish={onFinish}
      >
        <Form.Item
          name="username"
          label="Username"
          rules={[
            {
              required: true,
              message: "Please input Username",
              whitespace: true,
            },
          ]}
        >
          <Input prefix={<UserOutlined />} placeholder="Username" />
        </Form.Item>
        <Form.Item
          name="password"
          label="Password"
          rules={[requiredTrimValidate()]}
          validateStatus={passwordErrorMsg ? "error" : undefined}
          help={passwordErrorMsg}
          extra={
            !passwordErrorMsg && (
              <>
                * First time login password is&nbsp;
                <span className="font-bold text-primary">"recamera"</span>
              </>
            )
          }
        >
          <Input.Password
            prefix={<LockOutlined />}
            placeholder="Password"
            visibilityToggle
          />
        </Form.Item>
        <Form.Item className="w-full" noStyle>
          <Button block type="primary" htmlType="submit" disabled={!agreed}>
            Login
          </Button>
        </Form.Item>
      </Form>

      <div className="mt-16 w-750 flex items-center">
        <Checkbox
          checked={agreed}
          onChange={(e) => setAgreed(e.target.checked)}
          className="mt-1"
        />
        <div className="ml-10 text-14">
          Please view{" "}
          <span
            className="text-primary cursor-pointer underline"
            onClick={() => setShowAgreement(true)}
          >
            reCamera Connection Agreement
          </span>
          . By checking the box, users understand reCamera operates solely on
          local networks and commit to maintaining enterprise-grade network
          security for all vision AI operations.
        </div>
      </div>

      <Modal
        title={agreementTitle}
        open={showAgreement}
        closable={false}
        onCancel={() => setShowAgreement(false)}
        footer={
          <Button type="primary" onClick={handleAcknowledge}>
            Acknowledge
          </Button>
        }
        width={1000}
      >
        <div className="text-left text-14 leading-relaxed ml-36">
          <p className="text-15 font-medium mb-16">
            Welcome to reCamera Vision AI System. To ensure secure operation of
            your AI-powered camera, please review and confirm:
          </p>

          <h3 className="text-15 font-semibold mb-8 mt-24">
            Local Network Operation
          </h3>
          <p className="mb-4">
            This vision AI camera functions exclusively within local networks.
            You agree:
          </p>
          <ul className="list-none p-0 mt-4">
            <li className="mb-4">
              • Not to configure external/remote access capabilities
            </li>
            <li className="mb-4">
              • To maintain all connections within your private network
              environment
            </li>
            <li className="mb-4">
              • To disable UPnP/WAN exposure features if present
            </li>
          </ul>

          <h3 className="text-15 font-semibold mb-8 mt-24">
            Network Security Requirements
          </h3>
          <p className="mb-4">By proceeding, you confirm that your network:</p>
          <ul className="list-none p-0 mt-4">
            <li className="mb-4">
              • Implements WPA2/WPA3 encryption standards
            </li>
            <li className="mb-4">
              • Maintains updated firewall/security protocols
            </li>
            <li className="mb-4">• Restricts unauthorized device access</li>
            <li className="mb-4">
              • Uses strong unique credentials (recommended 12+ character
              password)
            </li>
          </ul>

          <h3 className="text-15 font-semibold mb-8 mt-24">
            Data Protection Understanding
          </h3>
          <p className="mb-4">As a vision AI camera, reCamera:</p>
          <ul className="list-none p-0 mt-4">
            <li className="mb-4">
              • Processes video data locally unless otherwise specified
            </li>
            <li className="mb-4">
              • Requires user-configured storage solutions
            </li>
            <li className="mb-4">
              • Excludes cloud connectivity by default design
            </li>
          </ul>

          <h3 className="text-15 font-semibold mb-8 mt-24">
            User Responsibilities
          </h3>
          <p className="mb-4">
            You acknowledge that Seeed Studio is not liable for:
          </p>
          <ul className="list-none p-0 mt-4">
            <li className="mb-4">
              • Security incidents from unsecured network environments
            </li>
            <li className="mb-4">
              • Unauthorized access through compromised credentials
            </li>
            <li className="mb-4">
              • Performance issues when used beyond local network parameters
            </li>
          </ul>
        </div>
      </Modal>

      <Modal
        title="Change password"
        open={firstLogin}
        closable={false}
        footer={
          <Button
            className="w-1/2 m-auto block"
            type="primary"
            onClick={handleChangePassword}
          >
            Confirm
          </Button>
        }
      >
        <Form
          form={form}
          name="dependencies"
          autoComplete="off"
          style={{ maxWidth: 600 }}
          layout="vertical"
        >
          <Form.Item
            name="oldpassword"
            label="Old Password"
            rules={[requiredTrimValidate()]}
            extra={
              <>
                For first time login, default password is&nbsp;
                <span className="font-bold text-primary">"recamera"</span>
              </>
            }
          >
            <Input.Password placeholder="recamera" visibilityToggle />
          </Form.Item>
          <Form.Item
            name="newpassword"
            label="New Password"
            rules={passwordRules}
          >
            <Input.Password
              placeholder="Enter new password here"
              visibilityToggle
            />
          </Form.Item>

          <Form.Item
            name="confirmpassword"
            label="Confirm New Password"
            dependencies={["newpassword"]}
            rules={[
              {
                required: true,
              },
              ({ getFieldValue }) => ({
                validator(_, value) {
                  if (!value || getFieldValue("newpassword") === value) {
                    return Promise.resolve();
                  }
                  return Promise.reject(
                    new Error("The new password that you entered do not match!")
                  );
                },
              }),
            ]}
          >
            <Input.Password
              placeholder="Confirm new password"
              visibilityToggle
            />
          </Form.Item>
        </Form>
      </Modal>
      {messageContextHolder}
    </div>
  );
};

export default Login;
