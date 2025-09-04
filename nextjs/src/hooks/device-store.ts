import { create } from "zustand";

type DeviceStore = {
  deviceCode: string;
  setDeviceCode: (code: string) => void;
};

export const useDeviceStore = create<DeviceStore>((set) => ({
  deviceCode: "",
  setDeviceCode: (code) => set({ deviceCode: code }),
}));
