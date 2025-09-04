import { z } from "zod";

const MQTT_SERVER = process.env.NEXT_PUBLIC_MQTT_SERVER;
const MQTT_PORT = process.env.NEXT_PUBLIC_MQTT_PORT;
const MQTT_USER = process.env.NEXT_PUBLIC_MQTT_USER;
const MQTT_PASSWORD = process.env.NEXT_PUBLIC_MQTT_PASSWORD;

const envSchema = z.object({
  NODE_ENV: z
    .enum(["development", "test", "production"])
    .default("development"),
  NEXT_PUBLIC_MQTT_SERVER: z.string(),
  NEXT_PUBLIC_MQTT_PORT: z.coerce.number(),
  NEXT_PUBLIC_MQTT_USER: z.string(),
  NEXT_PUBLIC_MQTT_PASSWORD: z.string(),
});

export const env = envSchema.parse({
  NODE_ENV: process.env.NODE_ENV,
  NEXT_PUBLIC_MQTT_SERVER: MQTT_SERVER,
  NEXT_PUBLIC_MQTT_PORT: MQTT_PORT,
  NEXT_PUBLIC_MQTT_USER: MQTT_USER,
  NEXT_PUBLIC_MQTT_PASSWORD: MQTT_PASSWORD,
});

console.log("Variáveis de ambiente validadas:", env)