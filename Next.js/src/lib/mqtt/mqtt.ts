"use server";

import { env } from "@/_config/env";
import mqtt from "mqtt";
import type { MqttClient } from "mqtt";

const brokerUrl = `tcp://${env.NEXT_PUBLIC_MQTT_SERVER}:${env.NEXT_PUBLIC_MQTT_PORT}`;
const options = {
  username: env.NEXT_PUBLIC_MQTT_USER,
  password: env.NEXT_PUBLIC_MQTT_PASSWORD,
  connectTimeout: 4000,
};

let client: MqttClient | null = null;
let connectionPromise: Promise<MqttClient> | null = null;

export async function getConnectedClient(): Promise<MqttClient> {
  if (client && client.connected) {
    return Promise.resolve(client);
  }

  if (connectionPromise) {
    return connectionPromise;
  }

  connectionPromise = new Promise((resolve, reject) => {
    console.log(`Tentando conectar ao broker em ${brokerUrl}...`);

    if (client) {
      client.end(true);
    }

    client = mqtt.connect(brokerUrl, options);

    client.on("connect", () => {
      console.log("Cliente MQTT conectado com sucesso no lado do servidor.");
      resolve(client!);
    });

    client.on("error", (err) => {
      console.error("Erro de conexão MQTT:", err.message);
      client?.end(true);
      client = null;
      connectionPromise = null;
      reject(err);
    });

    client.on("offline", () => {
      console.log("Cliente MQTT ficou offline.");
      client = null;
      connectionPromise = null;
    });

    client.on("end", () => {
      console.log("Cliente MQTT desconectado.");
      client = null;
      connectionPromise = null;
    });
  });

  return connectionPromise;
}
