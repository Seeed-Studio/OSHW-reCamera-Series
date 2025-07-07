import CommonPopup from "@/components/common-popup";
import { Button, Form, Input, Switch } from "antd";
import KeyImg from "@/assets/images/svg/key.svg";
import { DeleteOutlined } from "@ant-design/icons";
import { useData, IFormTypeEnum } from "./hook";
import moment from "moment";
import {
  requiredTrimValidate,
  publicKeyValidate,
  passwordRules,
} from "@/utils/validate";

const titleObj = {
  [IFormTypeEnum.Key]: "Add new SSH Key",
  [IFormTypeEnum.Username]: "Edit Username",
  [IFormTypeEnum.Password]: "Confirm Password",
  [IFormTypeEnum.DelKey]: "Remove SSH Key",
};

const Security = () => {
  const {
    state,
    formRef,
    passwordFormRef,
    usernameFormRef,
    onCancel,
    onEdit,
    addSshKey,
    onPasswordFinish,
    onUsernameFinish,
    onDelete,
    onAddSshFinish,
    onDeleteFinish,
    setSShStatus,
  } = useData();

  const handleSShStatusChange = (checked: boolean) => {
    setSShStatus(checked);
  };

  return (
    <div className="my-8 p-16">
      <div className="font-bold text-18 ">User</div>
      <div className="rounded-16 bg-white p-30 mt-12 mb-24">
        <div className="flex justify-between mb-16">
          <span className="text-3d">Username</span>
          <div className="flex">
            <span className="text-3d">{state.username}</span>
          </div>
        </div>
        <div className="flex justify-center">
          <Button
            color="primary"
            variant="outlined"
            onClick={() => onEdit(IFormTypeEnum.Password)}
          >
            Change Password
          </Button>
        </div>
      </div>
      <div className="font-bold text-18 flex justify-between items-center">
        <span>SSH</span>
        <Switch checked={state.sshEnabled} onChange={handleSShStatusChange} />
      </div>
      {state.sshEnabled && (
        <div className="rounded-16 bg-white p-30 mt-12 mb-24">
          {state.sshkeyList?.length ? (
            state.sshkeyList.map((item, index) => {
              return (
                <div
                  className="bg-white border rounded-20 p-16 flex mb-16"
                  key={item.id || index}
                >
                  <div className="mr-20">
                    <img className="w-44 h-44 mb-16" src={KeyImg} alt="" />
                    <div className="border px-5 py-3 rounded-2">SSH</div>
                  </div>
                  <div className="flex-1 truncate">
                    <div className="text-16 flex justify-between">
                      <span className="">{item.name}</span>
                      <DeleteOutlined
                        className="font-bold cursor-pointer"
                        style={{ fontSize: 18, color: "#D54941" }}
                        onClick={() => onDelete(item)}
                      />
                    </div>
                    <div className="text-black opacity-60 mt-12 mb-8 text-wrap break-words">
                      {item.value}
                    </div>
                    <div className="text-black opacity-60">
                      <div>
                        Added on
                        {item.addTime &&
                          moment(item.addTime).format(" MMMM DD,YYYY")}
                      </div>
                    </div>
                  </div>
                </div>
              );
            })
          ) : (
            <div className="text-14 text-text">
              There are no SSH keys associated with your device.
            </div>
          )}
          <div className="flex justify-center mt-24">
            <Button color="primary" variant="outlined" onClick={addSshKey}>
              Add New Key
            </Button>
          </div>
        </div>
      )}
      <CommonPopup
        visible={state.visible}
        title={titleObj[state.formType]}
        onCancel={onCancel}
      >
        {state.formType == IFormTypeEnum.Key && (
          <Form
            form={formRef}
            className="border-b-0"
            onFinish={onAddSshFinish}
            labelCol={{ style: { width: 55 } }}
          >
            <Form.Item
              name="sshName"
              label="Title"
              rules={[requiredTrimValidate()]}
            >
              <Input placeholder="recamera_132456" allowClear maxLength={32} />
            </Form.Item>
            <Form.Item
              name="sshKey"
              label="Key"
              trigger="onChange"
              rules={[publicKeyValidate()]}
            >
              <Input.TextArea
                rows={8}
                placeholder="Begins with 'ssh-rsa', 'ssh-ed25519',  or 'ssh-dss'"
              />
            </Form.Item>
            <Form.Item>
              <Button type="primary" block htmlType="submit">
                Add SSH Key
              </Button>
            </Form.Item>
          </Form>
        )}
        {state.formType == IFormTypeEnum.Password && (
          <Form
            form={passwordFormRef}
            className="border-b-0"
            onFinish={onPasswordFinish}
            labelCol={{ style: { width: 120 } }}
          >
            <Form.Item
              name="oldPassword"
              label="Old Password"
              rules={[requiredTrimValidate()]}
            >
              <Input placeholder="" allowClear maxLength={16} />
            </Form.Item>
            <Form.Item
              name="newPassword"
              label="New Password"
              rules={passwordRules}
            >
              <Input placeholder="" allowClear maxLength={16} />
            </Form.Item>
            <Form.Item>
              <Button type="primary" block htmlType="submit">
                Confirm
              </Button>
            </Form.Item>
          </Form>
        )}
        {state.formType == IFormTypeEnum.Username && (
          <Form
            form={usernameFormRef}
            onFinish={onUsernameFinish}
            initialValues={{
              username: state.username,
            }}
          >
            <Form.Item
              name="username"
              label="Username"
              rules={[requiredTrimValidate()]}
            >
              <Input placeholder="" allowClear maxLength={32} />
            </Form.Item>
            <Form.Item>
              <Button type="primary" block htmlType="submit">
                Confirm
              </Button>
            </Form.Item>
          </Form>
        )}
        {state.formType == IFormTypeEnum.DelKey && (
          <div>
            <div className="text-3d text-16 mb-20">
              This action cannot revert, are you sure you want to remove this
              SSH key?
            </div>
            <Button type="primary" block danger onClick={onDeleteFinish}>
              Confirm
            </Button>
          </div>
        )}
      </CommonPopup>
    </div>
  );
};

export default Security;
