#include <Arduino.h>
#include <config/config.h>
#include <mqtt/mqtt_manager.h>
#include <web/web_interface.h>
#include <wifi/wifi_manager.h>
#include <control/control.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n--- Inicializando ---");

  pinMode(0, INPUT_PULLUP);

  // Carregar configurações da EEPROM
  loadConfiguration();

  // Inicializa pinos do hardware
  setupHardware();

  // Tentar conectar ao WiFi
  if (!connectToWifi())
  {
    startConfigMode();
    return;
  }

  // Configurar e conectar ao MQTT
  setupMqtt();
  reconnectMqtt();
}

void loop()
{
  static unsigned long buttonPressTime = millis();

  if (digitalRead(0) == LOW)
  {
    if (millis() - buttonPressTime > 5000) // Pressionado por 2 segundos
    {
      buttonPressTime = millis(); // Reinicia o tempo
      Serial.println("Botão pressionado por 5s: reiniciando...");
      resetConfiguration();
    }
  }

  if (Serial.available())
  {
    String comando = Serial.readStringUntil('\n');
    comando.trim(); // remove espaços e quebras de linha

    if (comando == "reset")
    {
      Serial.println("Reiniciando...");
      resetConfiguration();
    }
  }

  if (configMode)
  {
    dnsServer.processNextRequest();
    server.handleClient();
    return;
  }

  if (!mqttClient.connected())
  {
    reconnectMqtt();
  }
  mqttClient.loop();

  // Verifica periodicamente a conexão WiFi
  static unsigned long lastWifiCheck = 0;
  if (millis() - lastWifiCheck > 30000)
  { // A cada 30s
    verifyConnection();
    lastWifiCheck = millis();
  }

  static unsigned long lastKeepAlive = 0;
  if (millis() - lastKeepAlive > 10000)
  { // A cada 10s
    keepAlive();
    lastKeepAlive = millis();
  }
}
