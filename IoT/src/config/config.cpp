#include "config.h"
#include "secrets.h" // ARQUIVO EQUIVALENTE AO .env
#include <control/control.h>

// Configurações para o Access Point
const char *ap_ssid = AP_SSID;
const char *ap_password = AP_PASSWORD;

// Configurações MQTT
const char *mqtt_server = MQTT_SERVER;
const int mqtt_port = MQTT_PORT;
const char *mqtt_user = MQTT_USER;
const char *mqtt_password = MQTT_PASSWORD;

// Instâncias
Config config;
bool configMode = false;
int dutyCycle = 0;

WebServer server(80);
DNSServer dnsServer;
const byte DNS_PORT = 53;
WiFiClient espClient;
PubSubClient mqttClient(espClient);

void loadConfiguration() {
  EEPROM.begin(CONFIG_SIZE);
  EEPROM.get(CONFIG_START, config);
  EEPROM.end();

  // Configuração padrão se não houver dados válidos
  if (!config.isConfigured) {
    strcpy(config.ssid, "");
    strcpy(config.password, "");
    strcpy(config.code, "");
    config.isConfigured = false;
  }

  Serial.println("Configuração carregada da EEPROM.");
}

void saveConfiguration() {
  EEPROM.begin(CONFIG_SIZE);
  config.isConfigured = true;
  config.ledState = false;
  EEPROM.put(CONFIG_START, config);
  EEPROM.commit();
  EEPROM.end();

  Serial.println("Configuração salva na EEPROM.");
}

void resetConfiguration() {
  EEPROM.begin(CONFIG_SIZE);
  Config emptyConfig;
  memset(&emptyConfig, 0, sizeof(Config));
  EEPROM.put(CONFIG_START, emptyConfig);
  EEPROM.commit();
  EEPROM.end();

  Serial.println("Configuração resetada! Reiniciando...");

  delay(1000);
  ESP.restart();
}

void setupHardware() {
  if (config.ledPin == 0) return;
  pinMode(config.ledPin, OUTPUT);
}