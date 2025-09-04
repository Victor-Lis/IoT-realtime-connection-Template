import { env } from "@/_config/env";

export default async function BrokerBox() {
  return (
    <div className="p-4 border border-gray-600 rounded-lg space-y-2">
      <p className="text-md text-gray-400">{`tcp://${env.NEXT_PUBLIC_MQTT_SERVER}:${env.NEXT_PUBLIC_MQTT_PORT}`}</p>
    </div>
  );
}
