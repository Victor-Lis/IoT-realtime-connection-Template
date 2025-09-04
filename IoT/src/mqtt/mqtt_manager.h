#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include "../config/config.h"

void setupMqtt();
void reconnectMqtt();
void keepAlive();
void mqttCallback(char* topic, byte* payload, unsigned int length);

#endif