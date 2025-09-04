"use client";
import { useState } from "react";
import { useDeviceStore } from "@/hooks/device-store";
import { publishMessage } from "@/lib/mqtt/pub-content";
import { LightbulbIcon, PowerIcon } from "@phosphor-icons/react/dist/ssr";

export default function ToggleLed() {
  const { deviceCode } = useDeviceStore();
  const [isLedOn, setIsLedOn] = useState(false);

  const topic = deviceCode ? `controller/${deviceCode}/led/change` : "";

  const handleToggleLed = () => {
    const newState = !isLedOn;
    setIsLedOn(newState);

    const message = "toggle";
    publishMessage(topic, message);
  };

  return (
    <div className="flex flex-col items-center justify-center space-y-6 pt-4">
      <div className="rounded-full transition-all duration-300">
        <LightbulbIcon
          size={60}
          className={`${isLedOn ? "text-yellow-500" : "text-gray-400"}`}
          style={
            isLedOn
              ? {
                  filter:
                    "drop-shadow(0 0 32px rgba(253,224,71,0.7)) drop-shadow(0 0 8px rgba(253,224,71,0.7))",
                }
              : undefined
          }
        />
      </div>

      <button
        onClick={handleToggleLed}
        className={`p-1 bg-white rounded-full cursor-pointer hover:opacity-80 hover:scale-105 transition-transform duration-200`}
      >
        <PowerIcon
          size={32}
          className={`inline-block ${
            isLedOn ? "text-red-400" : "text-green-500"
          }`}
        />
      </button>
    </div>
  );
}
