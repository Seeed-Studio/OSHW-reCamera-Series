import { create } from "zustand";
import { persist } from "zustand/middleware";

type UserInfo = {
  userName: string | null;
  password: string | null;
  token: string | null;
};

type UserStoreType = {
  firstLogin: boolean;
  usersBySn: Record<string, UserInfo>;
  currentSn: string | null;
  updateFirstLogin: (firstLogin: boolean) => void;
  updateUserInfo: (userInfo: UserInfo) => void;
  setCurrentSn: (sn: string) => void;
  updateUserName: (userName: string | null) => void;
  updatePassword: (password: string | null) => void;
  updateToken: (token: string | null) => void;
  clearCurrentUserInfo: () => void;
};

const useUserStore = create<UserStoreType>()(
  persist(
    (set, get) => ({
      firstLogin: false,
      usersBySn: {},
      currentSn: null,
      updateFirstLogin: (firstLogin: boolean) => set(() => ({ firstLogin })),
      updateUserInfo: (userInfo: UserInfo) => {
        const { currentSn, usersBySn } = get();
        if (currentSn) {
          set({
            usersBySn: {
              ...usersBySn,
              [currentSn]: userInfo,
            },
          });
        }
      },
      setCurrentSn: (sn: string) => {
        const { usersBySn } = get();
        if (sn) {
          const currentUser = usersBySn[sn] || {};
          set({
            currentSn: sn,
            usersBySn: {
              ...usersBySn,
              [sn]: {
                ...currentUser,
              },
            },
          });
        }
      },
      updateUserName: (userName: string | null) => {
        const { currentSn, usersBySn } = get();
        if (currentSn) {
          const currentUser = usersBySn[currentSn] || {};
          set({
            usersBySn: {
              ...usersBySn,
              [currentSn]: {
                ...currentUser,
                userName,
              },
            },
          });
        }
      },
      updatePassword: (password: string | null) => {
        const { currentSn, usersBySn } = get();
        if (currentSn) {
          const currentUser = usersBySn[currentSn] || {};
          set({
            usersBySn: {
              ...usersBySn,
              [currentSn]: {
                ...currentUser,
                password,
              },
            },
          });
        }
      },
      updateToken: (token: string | null) => {
        const { currentSn, usersBySn } = get();
        if (currentSn) {
          const currentUser = usersBySn[currentSn] || {};
          set({
            usersBySn: {
              ...usersBySn,
              [currentSn]: {
                ...currentUser,
                token,
              },
            },
          });
        }
      },
      clearCurrentUserInfo: () => {
        const { currentSn, usersBySn } = get();
        if (currentSn) {
          const currentUser = usersBySn[currentSn] || {};
          useUserStore.setState({
            usersBySn: {
              ...usersBySn,
              [currentSn]: {
                ...currentUser,
                password: null,
                token: null,
              },
            },
          });
        }
      },
    }),
    {
      name: "user-storage",
      partialize: (state) => ({
        usersBySn: state.usersBySn,
        currentSn: state.currentSn,
      }),
    }
  )
);

export const getToken = () => {
  const { currentSn, usersBySn } = useUserStore.getState();
  return currentSn ? usersBySn[currentSn]?.token : null;
};

export const clearCurrentUser = async () => {
  const { clearCurrentUserInfo } = useUserStore.getState();
  clearCurrentUserInfo();
};

export default useUserStore;
