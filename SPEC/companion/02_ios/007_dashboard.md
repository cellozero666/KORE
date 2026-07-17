# 007_dashboard.md

# Dashboard

## Objetivo

Implementar o Dashboard do K.O.R.E. Companion, apresentando informações de status do dispositivo e disponibilizando uma área de testes para desenvolvimento e depuração.

---

## Diretório de Trabalho

```
ROOT/COMPANION/ios/APP
```

Todo o desenvolvimento deste módulo deverá ocorrer exclusivamente neste diretório.

---

## Dependências

### SPECs

- 001_foundation.md
- 002_window.md
- 003_layout.md
- 004_navigation.md
- 005_state.md
- 006_connection.md

---

## Escopo

Implementar a tela inicial da aplicação contendo:

- Nome da aplicação.
- Indicador de conexão com o K.O.R.E.
- Área de informações do dispositivo.
- Área de testes para envio de comandos.
- Reutilizar o máximo possível de código existente do Companion macOS localizado em `ROOT/COMPANION/macos/APP`, preservando a arquitetura e adaptando apenas o que for necessário para compatibilidade com iOS.

---

## Layout

### Cabeçalho

Exibir:

```
K.O.R.E.
```

Ao lado do nome deverá existir um indicador de conexão.

Estados:

- Connected
- Disconnected

Cores:

- Verde → Connected
- Vermelho → Disconnected

O ícone será definido posteriormente por Melchior.

---

### Área "Device"

#### Firmware

Exibir a versão do firmware.

Origem:

```
version
```

---

#### Uptime

Exibir o tempo de funcionamento da ESP32.

Origem:

```
uptime
```

---

### Separador

---

#### Spotify

Exibir o estado da conexão:

- Connected
- Disconnected

Origem:

Estado da conexão com a API do Spotify.

Nesta etapa, a área deverá apenas existir, permanecendo preparada para futura implementação.

---

#### Google

Exibir o estado da conexão:

- Connected
- Disconnected

Origem:

Estado da conexão com a API Google.

Nesta etapa, a área deverá apenas existir, permanecendo preparada para futura implementação.

---

### Separador

---

#### Wi-Fi

Exibir o estado da conexão:

- Connected
- Disconnected

Origem:

```
wifi_status
```

Nesta etapa, a área deverá apenas existir, permanecendo preparada para futura implementação.

---

#### IP

Exibir o endereço IP do dispositivo.

Origem:

```
wifi_status
```

Nesta etapa, a área deverá apenas existir, permanecendo preparada para futura implementação.

---

## Área "Command Test"

Criar uma área destinada exclusivamente ao desenvolvimento.

Componentes:

- Campo de texto.
- Botão Send.

O conteúdo digitado deverá ser enviado diretamente para a ESP32 utilizando a interface pública definida em `006_connection.md`.

Exemplos:

```text
notification|...
uptime
version
happy
sad
spotify_stop
```

Esta ferramenta existe apenas para desenvolvimento.

Não deverá fazer parte da versão final do Companion.

---

## Não faz parte

- Configuração do Spotify.
- Configuração do Google.
- Configuração do Wi-Fi.
- Logs.
- Histórico de comandos.
- Persistência.
- Funcionalidades dos demais módulos.

---

## Critérios de Aceitação

- O Dashboard é exibido como tela inicial da aplicação.
- O nome K.O.R.E. é exibido corretamente.
- O indicador de conexão reflete corretamente o estado da conexão com o K.O.R.E. OS.
- A versão do firmware é obtida através do comando `version`.
- O uptime é obtido através do comando `uptime`.
- Wi-Fi e IP são obtidos através do comando `wifi_status`.
- As áreas de Spotify e Google são exibidas, preparadas para futura integração.
- A área Command Test permite o envio de comandos para a ESP32 através da interface pública definida em `006_connection.md`.
- O Dashboard permanece desacoplado da camada de comunicação, consumindo apenas os estados e comandos disponibilizados pelo módulo `006_connection.md`.