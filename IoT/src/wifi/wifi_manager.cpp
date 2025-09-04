#include "wifi_manager.h"
#include <web/web_interface.h>

bool connectToWifi() {
  Serial.print("Conectando ao WiFi: ");
  Serial.println(config.ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(config.ssid, config.password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConectado ao WiFi!");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
    return true;
  } else {
    Serial.println("\nFalha ao conectar ao WiFi.");
    return false;
  }
}

void startConfigMode() {
  configMode = true;

  // Configurar o ESP como um Access Point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_password);

  Serial.print("AP Iniciado. IP: ");
  Serial.println(WiFi.softAPIP());

  // Configurar o servidor DNS para redirecionar todas as solicitações para o
  // ESP
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  // Definir rotas para o servidor web
  setupWebServer();

  // Iniciar o servidor web
  server.begin();
  Serial.println("Servidor web iniciado");

  // Piscar o LED para indicar modo de configuração
  // for (int i = 0; i < 5; i++) {
  //   digitalWrite(LED_PIN, HIGH);
  //   delay(200);
  //   digitalWrite(LED_PIN, LOW);
  //   delay(200);
  // }
}

void verifyConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado. Tentando reconectar...");
    if (!connectToWifi()) {
      Serial.println(
          "Falha na reconexão WiFi. Iniciando modo de configuração...");
      startConfigMode();
      return;
    }
  }
}