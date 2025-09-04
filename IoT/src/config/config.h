#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <DNSServer.h>
#include <EEPROM.h>
#include <PubSubClient.h>
#include <WebServer.h>
#include <WiFi.h>
#include <esp_now.h>
#include <map>
#include <string>

// Configurações de timer
extern unsigned long lastGateStates[11];

// Configurações para o Access Point
extern const char *ap_ssid;
extern const char *ap_password;

// Configurações MQTT
extern const char *mqtt_server;
extern const int mqtt_port;
extern const char *mqtt_user;
extern const char *mqtt_password;

// Estrutura para armazenar as configurações
struct Config {
  char ssid[32];
  char password[64];
  char code[12]; // 11 caracteres + 1 para o caractere nulo
  bool isConfigured;
  int ledPin;
  bool ledState;
};

extern Config config;
extern bool configMode;

// Definição de endereços na EEPROM
#define CONFIG_START 0
#define CONFIG_SIZE sizeof(Config)

// Declaração de objetos
extern WebServer server;
extern DNSServer dnsServer;
extern const byte DNS_PORT;
extern WiFiClient espClient;
extern PubSubClient mqttClient;

// Declaração de funções
void loadConfiguration();
void saveConfiguration();
void setupHardware();
void resetConfiguration();
void resetLastGateState(int i);
bool hasGateTimeoutElapsed(int i);

#endif
