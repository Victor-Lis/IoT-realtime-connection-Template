#include "web_interface.h"

void setupWebServer()
{
  server.on("/", handleRoot);
  server.on("/save", handleSave);
  server.onNotFound(handleRoot);
}

void handleRoot()
{
  String html =
    "<!DOCTYPE html>"
    "<html lang='pt-br'>"
    "<head>"
    "<meta charset='UTF-8' />"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0' />"
    "<title>Configuração da Controladora</title>"
    "<style>"
    "body {"
    "  font-family: Arial, sans-serif;"
    "  margin: 0;"
    "  padding: 20px;"
    "  background-color: oklch(0.147 0.004 49.25);"
    "  color: white;"
    "}"
    "h1 {"
    "  color: oklch(0.795 0.184 86.047);"
    "}"
    ".container {"
    "  max-width: 500px;"
    "  margin: 0 auto;"
    "  background: #1f1f1f;"
    "  padding: 20px;"
    "  border-radius: 8px;"
    "  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);"
    "}"
    "label {"
    "  display: block;"
    "  margin-top: 10px;"
    "  font-weight: bold;"
    "  color: white;"
    "}"
    "input[type='text'], input[type='password'] {"
    "  width: 100%;"
    "  padding: 8px;"
    "  margin-top: 5px;"
    "  margin-bottom: 10px;"
    "  border: 1px solid #ddd;"
    "  border-radius: 4px;"
    "  box-sizing: border-box;"
    "  background-color: #333;"
    "  color: white;"
    "}"
    "input[type='number'] {"
    "  width: 100%;"
    "  padding: 8px;"
    "  margin-top: 5px;"
    "  margin-bottom: 10px;"
    "  border: 1px solid #ddd;"
    "  border-radius: 4px;"
    "  box-sizing: border-box;"
    "  background-color: #333;"
    "  color: white;"
    "}"
    "button {"
    "  background-color: oklch(0.795 0.184 86.047);"
    "  color: #2e2e2e;"
    "  font-weight: bold;"
    "  padding: 10px 15px;"
    "  border: none;"
    "  border-radius: 4px;"
    "  cursor: pointer;"
    "}"
    "button:hover {"
    "  background-color: oklch(0.795 0.184 86.047);"
    "}"
    ".show-password {"
    "  cursor: pointer;"
    "  color: #bbb;"
    "  font-size: 14px;"
    "  margin-top: 5px;"
    "  display: block;"
    "}"
    "#code {"
    "  text-transform: uppercase;"
    "}"
    ".disabled, .disabled:hover {"
    "  color: #c0c0c0;"
    "  background-color: #555;"
    "  cursor: not-allowed;"
    "}"
    "select {"
    "  width: 100%;"
    "  padding: 8px;"
    "  margin-top: 5px;"
    "  margin-bottom: 10px;"
    "  border: 1px solid #ddd;"
    "  border-radius: 4px;"
    "  box-sizing: border-box;"
    "  background-color: #333;"
    "  color: white;"
    "}"
    "</style>"
    "</head>"
    "<body>"
    "<div class='container'>"
    "<h1>Configuração da Controladora</h1>"
    "<form action='/save' method='post'>"
    "<label for='ssid'>Nome da Rede WiFi:</label>"
    "<input type='text' id='ssid' name='ssid' value='' required />"
    "<label for='password'>Senha da Rede WiFi:</label>"
    "<input type='password' id='password' name='password' value='' required />"
    "<span class='show-password' onclick='togglePassword()'>Mostrar Senha</span>"
    "<label for='code'>Código de acesso:</label>"
    "<input type='text' id='code' name='code' value='' required />"
    "<label for='ledPin'>Pino do Led:</label>"
    "<input type='number' id='ledPin' name='ledPin' min='1' max='10' required />"
    "<button type='submit'>Salvar e Reiniciar</button>"
    "</form>"
    "</div>"
    "<script>"
    "function togglePassword() {"
    "  const passwordInput = document.getElementById('password');"
    "  const passwordType = passwordInput.type === 'password' ? 'text' : 'password';"
    "  passwordInput.type = passwordType;"
    "}"
    "</script>"
    "</body>"
    "</html>";

  server.send(200, "text/html", html);
}

void handleSave()
{
  if (server.method() == HTTP_POST)
    {
      strncpy(config.ssid, server.arg("ssid").c_str(), sizeof(config.ssid));
      strncpy(config.password, server.arg("password").c_str(),
              sizeof(config.password));
      strncpy(config.code, server.arg("code").c_str(), sizeof(config.code));

      // Garantir que as strings são terminadas corretamente
      config.ssid[sizeof(config.ssid) - 1] = '\0';
      config.password[sizeof(config.password) - 1] = '\0';
      config.code[sizeof(config.code) - 1] = '\0';

      // Capturar os pinos dos relés
      int ledPin = server.arg("ledPin").toInt();

      config.isConfigured = true;
      config.ledPin = ledPin;
      
      saveConfiguration();

      String html =
          "<!DOCTYPE html>"
          "<html lang='pt-br'>"
          "<head>"
          "<meta charset='UTF-8' />"
          "<meta name='viewport' content='width=device-width, initial-scale=1.0' />"
          "<title>Configuração Salva</title>"
          "<style>"
          "body {"
          "  font-family: Arial, sans-serif;"
          "  margin: 0;"
          "  padding: 20px;"
          "  background-color: oklch(0.147 0.004 49.25);"
          "  color: white;"
          "  text-align: center;"
          "}"
          ".container {"
          "  max-width: 500px;"
          "  margin: 0 auto;"
          "  background: #2e2e2e;"
          "  padding: 20px;"
          "  border-radius: 8px;"
          "  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);"
          "}"
          "h1 {"
          "  color: oklch(0.795 0.184 86.047);"
          "}"
          "p {"
          "  font-size: 24px;"
          "  color: white;"
          "}"
          ".countdown {"
          "  font-size: 30px;"
          "  font-weight: bold;"
          "  color: oklch(0.795 0.184 86.047);"
          "}"
          "</style>"
          "</head>"
          "<body>"
          "<div class='container'>"
          "<h1>Configuração Salva!</h1>"
          "<p>"
          "O dispositivo será reiniciado em "
          "<span id='countdown' class='countdown'>5</span> segundos..."
          "</p>"
          "<span>Você já pode fechar esta página</span>"
          "</div>"
          "<script>"
          "let countdownValue = 5;" // Iniciar contagem a partir de 5 segundos
          "const countdownElement = document.getElementById('countdown');"
          "function updateCountdown() {"
          "  if (countdownValue > 0) {"
          "    countdownValue--;"
          "    countdownElement.textContent = countdownValue;"
          "  }"
          "}"
          "setInterval(updateCountdown, 1000);" // Atualizar a contagem a cada segundo
          "</script>"
          "</body>"
          "</html>";

      server.send(200, "text/html", html);

      // Aguardar um tempo para a resposta ser enviada e então reiniciar
      delay(5000);
      ESP.restart();
    }
  }