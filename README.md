# IoT Real-Time Connection Template

Este repositório serve como um template completo para criar aplicações que conectam uma interface web moderna a um dispositivo de hardware (IoT) em tempo real, utilizando o protocolo MQTT. O projeto de exemplo permite controlar um LED conectado a um microcontrolador ESP32 através de uma página web construída com Next.js.

![Demonstração da Interface Web](/docs/web-image.png)

---

## 🎯 Para Que Serve?

O objetivo principal deste projeto é fornecer uma base sólida e reutilizável para desenvolvedores que desejam construir sistemas de controle e monitoramento de IoT. Ele resolve o desafio comum de estabelecer uma comunicação de baixa latência entre uma interface web e um dispositivo físico, ideal para:

- **Domótica (Casa Inteligente):** Controlar luzes, tomadas e outros aparelhos.
- **Monitoramento Remoto:** Ler dados de sensores e exibi-los em um dashboard.
- **Prototipagem Rápida:** Validar ideias de produtos IoT com um frontend funcional.
- **Projetos Educacionais:** Ensinar na prática a integração entre software e hardware.

---

## 🛠️ Funcionalidades

Este template inclui duas componentes principais:

### 1. Firmware para o Dispositivo IoT (ESP32)

- **Modo de Configuração:** Se o dispositivo não conseguir ligar-se a uma rede Wi-Fi conhecida, ele cria seu próprio Access Point (AP). O usuário pode conectar-se a este AP, acessar uma página web interna e configurar as credenciais do Wi-Fi, o código de acesso do dispositivo e o pino do LED.
- **Conexão MQTT Segura:** Conecta-se a um broker MQTT usando credenciais e publica um status "online".
- **Subscrição de Tópicos:** Subscreve um tópico MQTT específico (`controller/{codigo-do-dispositivo}/led/change`) para receber comandos.
- **Controlo de Hardware:** Ao receber a mensagem "toggle" no tópico subscrito, o firmware alterna o estado do LED (liga/desliga).
- **Reconexão Automática:** Tenta restabelecer a ligação com o Wi-Fi e o broker MQTT em caso de falha.

### 2. Interface Web (Next.js)

- **Controle em Tempo Real:** Interface simples para enviar comandos ao dispositivo.
- **Arquitetura Server-Side:** A comunicação com o broker MQTT é gerida pelo backend do Next.js (Server Actions), garantindo que as credenciais do broker nunca são expostas no navegador.
- **Estado Global com Zustand:** Gerencia o "código do dispositivo" de forma centralizada.
- **Validação de Formulário:** Utiliza `react-hook-form` e `zod` para validar o código do dispositivo inserido pelo usuário.
- **Feedback Visual:** Mostra o estado atual do broker e do LED, além de notificações de sucesso.

---

## 🏗️ Arquitetura

A comunicação entre a interface web e o ESP32 é intermediada por um broker MQTT. A arquitetura foi desenhada para ser segura e eficiente.

![Diagrama da Arquitetura do Projeto]

1. **Usuário Interage com a Web:** Insere o código do dispositivo e clica para ligar/desligar o LED.
2. **Frontend para Backend (Next.js):** O clique chama uma *Server Action* do Next.js.
3. **Backend para Broker MQTT:** A *Server Action* publica a mensagem "toggle" no tópico correto (ex: `controller/COXINHA1/led/change`).
4. **Broker para Dispositivo IoT:** O broker MQTT reencaminha a mensagem para o ESP32.
5. **Dispositivo Executa a Ação:** O ESP32 recebe a mensagem e alterna o estado do LED.

> **Nota:** Esta abordagem *server-side* é crucial porque navegadores não podem estabelecer ligações TCP diretas, necessárias para o protocolo MQTT padrão.

---

## 🚀 Tecnologias Utilizadas

| Área             | Tecnologia                                                                 |
|------------------|----------------------------------------------------------------------------|
| **Hardware**     | [ESP32-S3](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/index.html) (ou similar)                                                      |
| **Firmware**     | C++ com Arduino Framework, [PlatformIO](https://platformio.org/)                                      |
| **Frontend Web** | [Next.js](https://nextjs.org/), [React](https://react.dev/), [Tailwind CSS](https://tailwindcss.com/) |
| **Comunicação**  | [MQTT](https://mqtt.org/)                                                  |
| **Estado (Web)** | [Zustand](https://zustand-demo.pmnd.rs/)                                   |
| **Formulários**  | [React Hook Form](https://react-hook-form.com/), [Zod](https://zod.dev/)   |

---

## ⚙️ Configuração e Execução

Siga os passos abaixo para colocar o projeto a funcionar.

### Pré-requisitos

- Um broker MQTT acessível publicamente.
- [Visual Studio Code](https://code.visualstudio.com/) com a extensão [PlatformIO IDE](https://platformio.org/platformio-ide).
- [Node.js](https://nodejs.org/) (versão 18 ou superior).
- Um microcontrolador ESP32.

---

### 1. Configurar o Firmware do IoT

1. **Abra a Pasta `IoT`:**  
  Abra `IoT-realtime-connection-Template/IoT` no VS Code (deve detectar como projeto PlatformIO).

2. **Crie o Ficheiro `secrets.h`:**  
  Na pasta `src`, crie `secrets.h` e adicione as credenciais do seu broker MQTT.  
  > Este ficheiro está no `.gitignore` para não ser enviado ao repositório.

  ```cpp
  // IoT-realtime-connection-Template/IoT/src/secrets.h

  #pragma once

  // Access Point (para o modo de configuração)
  #define AP_SSID "ESP32-Config"
  #define AP_PASSWORD "12345678"

  // Credenciais do seu Broker MQTT
  #define MQTT_SERVER "seu-broker.com"
  #define MQTT_PORT 1883
  #define MQTT_USER "seu_usuario"
  #define MQTT_PASSWORD "sua_senha"
  ```

3. **Compile e Envie:**  
  Com o ESP32 ligado ao computador, use o PlatformIO para compilar (`Build`) e enviar (`Upload`) o firmware.

4. **Primeira Configuração:**  
  - Abra o *Serial Monitor* do PlatformIO.
  - Se for a primeira vez, o ESP32 entrará em modo de configuração.
  - Conecte-se à rede Wi-Fi "ESP32-Config".
  - Acesse `192.168.4.1` no navegador.
  - Preencha o formulário com os dados da sua rede Wi-Fi, um **código de acesso** único (ex: `MEU-ESP-01`) e o pino GPIO do LED.
  - Clique em salvar. O dispositivo irá reiniciar e conectar-se à sua rede e ao broker.

---

### 2. Configurar a Aplicação Web

1. **Navegue para a Pasta `nextjs`:**

  ```bash
  cd IoT-realtime-connection-Template/nextjs
  ```

2. **Instale as Dependências:**

  ```bash
  pnpm install
  ```

3. **Crie o Ficheiro de Ambiente:**  
  Crie `.env.local` na raiz da pasta `nextjs` e adicione as credenciais do broker.

  ```env
  # IoT-realtime-connection-Template/nextjs/.env.local

  NEXT_PUBLIC_MQTT_SERVER="seu-broker.com" // somente o IP
  NEXT_PUBLIC_MQTT_PORT=1883
  NEXT_PUBLIC_MQTT_USER="seu_usuario"
  NEXT_PUBLIC_MQTT_PASSWORD="sua_senha"
  ```

4. **Inicie o Servidor de Desenvolvimento:**

  ```bash
  pnpm dev
  ```

5. **Acesse a Aplicação:**  
  Abra o navegador e visite [http://localhost:3000](http://localhost:3000).

6. **Teste:**  
  Insira o mesmo **código de acesso** configurado no seu dispositivo IoT e clique no botão para controlar o LED!
  > O código de acesso serve como identificador único de cada plaquinha, para caso seja necessário expandir o projeto registar em um banco de dados isso.

---

## 📜 Licença

Este projeto está licenciado sob a Licença MIT. Consulte o ficheiro [LICENSE](LICENSE) para mais detalhes.

