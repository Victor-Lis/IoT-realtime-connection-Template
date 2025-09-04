#include "mqtt_manager.h"
#include "../control/control.h"

void setupMqtt() {
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(mqttCallback);
  mqttClient.setKeepAlive(5);
}

void reconnectMqtt() {
  int attempts = 0;
  while (!mqttClient.connected() && attempts < 5) {
    String willTopic = "controller/" + String(config.code) + "/online";
    String base_topic = "controller/" + String(config.code) + "/";

    String willMessage = "offline";

    if (mqttClient.connect(config.code, mqtt_user, mqtt_password,
                           willTopic.c_str(), 1, true, willMessage.c_str())) {
      Serial.print("Conectado com ID: ");
      Serial.println(config.code);

      mqttClient.publish(willTopic.c_str(), "online");

      mqttClient.subscribe((base_topic + "led/change").c_str());
    } else {
      Serial.print("Falha, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Tentando novamente...");
      delay(2000);
      attempts++;
    }
  }
}

void keepAlive() {
  String keepAliveTopic = "controller/" + String(config.code) + "/online";
  mqttClient.publish(keepAliveTopic.c_str(), "online", true);

  Serial.print("Enviando keepAlive: ");
  Serial.println(keepAliveTopic.c_str());
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  toggleLed();
}