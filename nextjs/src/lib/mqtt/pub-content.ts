"use server";
import { getConnectedClient } from "@/lib/mqtt/mqtt";

const client = await getConnectedClient();

export async function publishMessage(topic: string, message: string) {
  try {
    await client.publishAsync(topic, message, { qos: 0, retain: false });

    console.log(
      `Mensagem "${message}" enviada com sucesso para o tópico "${topic}"`
    );

    // client.end(); // Descomente se cada publicação for uma ação isolada.

    return { success: true };
  } catch (error: any) {
    console.error("Erro ao publicar mensagem:", error.message);
    throw new Error("Falha ao enviar a mensagem para o broker.");
  }
}
