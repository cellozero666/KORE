# 000_discovery.md

## Discovery do Firmware K.O.R.E. OS (Legacy)

**Versão analisada:** 0.9.0
**Hardware alvo:** ESP32-S3 N16R8
**Framework:** Arduino
**Data da análise:** 2026-07-13
**Analista:** Belthazar

---

## Convenções do Documento

Este documento distingue entre:

- **Fato**: informação observada diretamente no código-fonte, compilação ou comportamento do firmware.
- **Inferência técnica**: conclusão baseada em análise, experiência ou boas práticas, mas não comprovada por observação direta de falha ou medição no firmware atual.

Toda inferência será explicitamente marcada com *(inferência)*.

---

## Sumário

1. [Visão Geral da Arquitetura](#1-visão-geral-da-arquitetura)
2. [Estrutura de Diretórios](#2-estrutura-de-diretórios)
3. [Fluxo de Boot](#3-fluxo-de-boot)
4. [Fluxo de Renderização](#4-fluxo-de-renderização)
5. [Fluxo de Comunicação](#5-fluxo-de-comunicação)
6. [Gerenciamento de Estado](#6-gerenciamento-de-estado)
7. [Serviços Existentes](#7-serviços-existentes)
8. [Bibliotecas Utilizadas](#8-bibliotecas-utilizadas)
9. [Dependências Externas](#9-dependências-externas)
10. [Organização dos Módulos](#10-organização-dos-módulos)
11. [Fluxo de Eventos](#11-fluxo-de-eventos)
12. [Persistência](#12-persistência)
13. [FreeRTOS](#13-freertos)
14. [Mapa Arquitetural do Firmware](#14-mapa-arquitetural-do-firmware)
15. [Mapa de Memória](#15-mapa-de-memória)
16. [Pontos Fortes](#16-pontos-fortes)
17. [Características Arquiteturais](#17-características-arquiteturais)
18. [Auditoria de Delays](#18-auditoria-de-delays)
19. [Dívidas Técnicas](#19-dívidas-técnicas)
20. [Riscos](#20-riscos)
21. [Oportunidades de Melhoria](#21-oportunidades-de-melhoria)
22. [Recomendações para o HARNESS-001](#22-recomendações-para-o-harness-001)

---

## 1. Visão Geral da Arquitetura

O firmware K.O.R.E. OS é uma aplicação Arduino monolítica para ESP32-S3, organizada em torno de um loop principal único (`loop()`) que executa uma sequência fixa de atualizações a cada iteração.

### Características fundamentais

- **Single-threaded**: fato - todo o código executa em uma única task do Arduino (loop). Não há uso de FreeRTOS, tasks dedicadas ou schedulers.
- **Organização em headers**: fato - 100% do código-fonte está em arquivos `.h`. Não existem arquivos `.cpp`. Esta é uma característica arquitetural do firmware atual (ver seção [Características Arquiteturais](#17-características-arquiteturais)).
- **Acoplamento via globals**: fato - o estado do sistema é mantido em variáveis globais declaradas em `KORE_OS.ino` e referenciadas via `extern` nos módulos. Não existe um state manager centralizado.
- **Comunicação multicanal**: fato - suporta simultaneamente Serial USB, BLE (NimBLE), TCP (WiFi) e ANCS (canal reservado para implementação futura).
- **Display state machine**: fato - a renderização da tela segue uma máquina de estados simples com 4 modos, definida em `display_manager.h`.
- **Protocolo textual**: fato - comandos e respostas usam strings UTF-8 delimitadas por `|`, conforme ADR-003.
- **Ausência de primitivas de concorrência**: fato - não há tasks, semáforos, filas ou qualquer outro primitivo de concorrência explícito.

### Diagrama arquitetural

```
KORE_OS.ino (setup + loop)
  |
  +-- src/config/          (constantes, externs do display)
  +-- src/core/            (parser central de comandos)
  +-- src/managers/        (serviços: BLE, WiFi, Clock, Sleep, etc.)
  +-- src/ui/assets/       (bitmaps: faces, ícones, cat)
  +-- src/ui/screens/      (telas: boot, notificações, spotify)
```

---

## 2. Estrutura de Diretórios e Responsabilidades

### Raiz do firmware

```
KORE_OS.ino                   # Entry point: setup() e loop()
```

### `src/config/`

| Arquivo | Responsabilidade |
|---------|-----------------|
| `config.h` | Versão do firmware (`0.9.0`) |
| `display_context.h` | Declaração externa de `tft`, `u8g2`, `KORE_CYAN` |

### `src/core/`

| Arquivo | Responsabilidade |
|---------|-----------------|
| `command_parser.h` | Roteador central de comandos. Recebe uma string, identifica o tipo e delega para o handler correspondente. Monolítico (~190 linhas), contém toda a lógica de roteamento em um único `if/else if` chain. |

### `src/managers/`

| Arquivo | Responsabilidade |
|---------|-----------------|
| `ancs_manager.h` | Apple Notification Center Service. **Reservado para implementação futura.** Atualmente contém apenas funções vazias com `// TODO`. |
| `ble_manager.h` | Servidor GATT BLE usando NimBLE. Service UUID `8C0F0001...`, características RX (WRITE) e TX (NOTIFY). Callbacks de conexão/desconexão e escrita. |
| `clock_manager.h` | Relógio por software. Incrementa segundo a segundo via `millis()`. Estrutura `ClockState` com hour/minute/second/lastTick. |
| `demon_manager.h` | Easter egg: após 66h06m de uptime, ativa FACE_DEMON por 5s. |
| `display_manager.h` | Máquina de estados do display. Enum `DisplayMode` com 4 estados. Funções `updateDisplayState()`, `handleDisplayTransition()`, `updateActiveModule()`, `renderCurrentDisplay()`. |
| `emotion_manager.h` | Detecta emoção baseada em keywords. Carrega regras do JSON via FFat. Suporte a até 10 emoções com até 64 keywords cada. |
| `input_manager.h` | Multiplexador de entrada. Polleia Serial, BLE, ANCS e TCP e encaminha para `processCommand()`. |
| `mood_manager.h` | Enum `FaceType` (8 faces). Funções `setFace()`, `renderEmotion()`, `getCurrentFaceName()`. Faz o dispatch entre as 8 faces. |
| `output_manager.h` | Roteia respostas: BLE se conectado, Serial caso contrário. |
| `sleep_manager.h` | Gerencia sleep por inatividade (15min) e noturno (22h-7h). Altera `defaultFace` para FACE_SLEEP. |
| `tcp_manager.h` | Servidor TCP sobre WiFi na porta 6666. Suporte a um único cliente. |
| `weather_manager.h` | Exibição de clima. Parse do comando `weather|...` com 5 campos. Timeout de 15s. |
| `wifi_manager.h` | Gerenciamento WiFi com persistência em Preferences. Auto-conecta ao boot. Timeout de 15s. |

### `src/ui/assets/`

| Arquivo | Responsabilidade |
|---------|-----------------|
| `cat.h` | Bitmap 100x100 do gato K.O.R.E. em PROGMEM. |
| `notification_icons.h` | 6 ícones 80x80 (calendar, envelope, gear, sms, whatsapp, other) em PROGMEM. |
| `weather_icons.h` | 6 ícones 64x64 (cloud, partly_cloudy, rain, snow, storm, sun) em PROGMEM. |
| `faces/face_utils.h` | Utilitários compartilhados: `dot()`, `clearDot()`, `drawBlinkEyes()`. Constantes de posicionamento (`FACE_OX`, `FACE_OY`, `FACE_SPACING`, `FACE_DOT_SIZE`). |
| `faces/happy_face.h` | Desenho + animação (blink) da face happy. |
| `faces/extra_happy_face.h` | Desenho + animação da face extra happy. |
| `faces/sad_face.h` | Desenho + animação da face sad. |
| `faces/sleep_face.h` | Desenho + animação (ZZZ) da face sleep. |
| `faces/surprise_face.h` | Desenho + animação da face surprise. |
| `faces/loving_face.h` | Desenho + animação (coração pulsando) da face loving. |
| `faces/confused_face.h` | Desenho + animação (interrogação) da face confused. |
| `faces/demon_face.h` | Desenho + animação (glitch horizontal) da face demon. Cor vermelha. |

### `src/ui/screens/`

| Arquivo | Responsabilidade |
|---------|-----------------|
| `boot_screen.h` | Tela de boot: bitmap do gato, texto "K.O.R.E. OS", barra de progresso animada. |
| `notifications.h` | Fila circular de até 10 notificações. Parse do comando `notification|...`. Detecção de emoção via `emotion_manager.h`. Display com ícone por app + título + body em 2 linhas. Timeout de 8s + 5s de emoção. |
| `spotify_screen.h` | Tela de reprodução Spotify: cassete com bobinas animadas, barra de progresso, track/artist/time. Demon mode ativado por tracks específicas aos 66s. Timeout de 15s sem atualização. Mostra face loving a cada 20s por 2s. |

### `data/`

| Arquivo | Responsabilidade |
|---------|-----------------|
| `emotion_rules.json` | Regras de detecção de emoção: 5 emoções (extrahappy, loving, sad, surprise, confused). Cada uma com keywords em português e inglês, duração e prioridade. |

### `scripts/` e `tools/`

| Arquivo | Responsabilidade |
|---------|-----------------|
| `scripts/build_fatfs.py` | Gera imagem FATFS para upload ao ESP32. Usa `wl_fatfsgen.py`. |
| `tools/fatfs/` | Utilitários Python para geração de FATFS com wear-leveling. |

---

## 3. Fluxo Completo de Boot

### `setup()` (linha 84-141 de KORE_OS.ino)

```
Serial.begin(115200)
  |
  v
delay(1000)                                  # Aguarda estabilização serial
  |
  v
FFat.begin(true)                              # Monta filesystem FAT
  |-> Se falhar: "FATFS mount failed"
  |-> Se ok: loadEmotionRules() do /emotion_rules.json
       |-> Se falhar: "Failed to load emotion rules"
  |
  v
autoConnectWiFi()                             # Carrega credenciais de Preferences
  |-> Se há SSID salvo: WiFi.begin(), modo STA
  |-> Conecta async (wifiConnecting = true)
  |
  v
beginBLE()                                    # Inicializa NimBLE
  |-> NimBLEDevice::init("K.O.R.E.")
  |-> Cria server, service, características RX/TX
  |-> Inicia advertising
  |
  v
beginTCPServer()                              # WiFi TCP server na porta 6666
  |-> tcpServer.begin(), setNoDelay(true)
  |
  v
SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS)    # Inicializa SPI para display
  |
  v
tft.init(240, 320)                            # Inicializa display ST7789
tft.setRotation(1)                            # Modo paisagem
  |
  v
KORE_CYAN = tft.color565(11, 235, 201)        # Cor oficial K.O.R.E.
  |
  v
u8g2.begin(tft)                               # Inicializa U8g2 sobre Adafruit GFX
u8g2.setFont(u8g2_font_helvB12_tf)
u8g2.setFontMode(1)
u8g2.setForegroundColor(KORE_CYAN)
  |
  v
bootScreen(tft, KORE_CYAN)                    # Tela de boot:
  |-> fillScreen(BLACK)
  |-> drawBitmap(cat, 110, 20)
  |-> "K.O.R.E." + "OS"
  |-> Barra de progresso animada (196 passos, delay(25) cada)
  |-> delay(1000) final
  |
  v
setFace(defaultFace)                          # FACE_HAPPY
  |
  v
lastActivity = millis()
  |
  v
loop()                                        # Loop infinito
```

### Observações sobre o boot

1. **delay(1000)** inicial: tempo de espera para estabilização da porta serial. Aceitável para setup.
2. **Barra de progresso**: 196 passos com `delay(25)` cada (~4.9s total). O efeito visual é intencional (animação de boot).
3. **delay(1000)** final da boot screen: pausa para exibir o logo completo antes de iniciar.
4. **Tempo total estimado de boot**: ~7-8 segundos. *(inferência - depende da velocidade do hardware e do tempo real de inicialização do display)*.
5. **WiFi connect é async** (não bloqueia o boot), mas o TCP server só aceitará conexões após o WiFi estar conectado.

---

## 4. Fluxo de Renderização da Tela

### Máquina de Estados do Display

Definida em `display_manager.h`:

```
DISPLAY_NOTIFICATION  (prioridade mais alta)
       |
       v
DISPLAY_WEATHER
       |
       v
DISPLAY_SPOTIFY
       |
       v
DISPLAY_EMOTION       (prioridade mais baixa / padrão)
```

### Ciclo de Renderização (executado a cada loop())

```
updateDisplayState()
  |-> Determina próximo modo por prioridade
  |-> Se mudou: salva previousMode, atualiza currentMode, marca modeChanged
  |
  v
handleDisplayTransition()
  |-> Se modeChanged: chama onEnter<Modo>()
  |-> Limpa modeChanged
  |
  v
updateActiveModule()
  |-> Chama update<Modo>() para o modo atual
  |-> Cada módulo gerencia seus próprios timers e timeouts
  |
  v
renderCurrentDisplay()
  |-> Chama render<Modo>() para o modo atual
  |-> Notificação: desenha apenas uma vez (flag notificationWasDrawn)
  |-> Clima: desenha apenas no onEnter
  |-> Spotify: redesenha quando necessário (flag spotifyNeedsRedraw)
  |-> Emoção: anima continuamente (blink, glitch, etc.)
```

### Mecanismo de Animação

Cada face possui uma função `animate<Face>()` chamada a cada ciclo de loop. O padrão identificado em todas as faces é:

```c
void animateHappyFace(Adafruit_ST7789 &tft, uint16_t color) {
    unsigned long now = millis();
    if (now - lastBlink > nextBlink) {
        drawBlinkEyes(tft, color);       // desenha olhos fechados
        delay(120);                       // mantém olhos fechados por 120ms
        drawHappyFace(tft, color);       // redesenha face completa
        lastBlink = now;
        nextBlink = random(2000, 5000);
    }
}
```

### Problemas identificados na renderização

1. **delay(120) no blink**: fato - o delay existe e bloqueia o loop. A duração de 120ms é o tempo necessário para o efeito visual de piscada. O bloqueio do loop durante este período impede o processamento de outros eventos.
2. **Redesenho completo da face a cada piscada**: fato - a função `drawHappyFace()` redesenha todos os pixels da face, mesmo tratando-se de uma animação de 2 olhos.
3. **Estado global `modeChanged`**: fato - variável global sem proteção. Em ambiente single-threaded não há race condition real.
4. **Flag `notificationWasDrawn`**: fato - se algo requisitar redesenho, a flag não é resetada externamente.
5. **Sem dirty-rect ou renderização parcial**: fato - exceto no timer do Spotify que usa `fillRect` para limpar apenas a área do contador.

---

## 5. Fluxo de Comunicação

### Canais de Entrada

O `input_manager.h` implementa um multiplexador de entrada que polleia sequencialmente:

```
updateInputManager()
  |
  +-- Serial.available()  -> readStringUntil('\n') -> processCommand()
  |
  +-- bleCommandAvailable() -> readBLECommand()    -> processCommand()
  |
  +-- ancsAvailable()       -> readANCSCommand()   -> processCommand()
  |
  +-- updateTCPServer()
       +-- tcpCommandAvailable() -> readTCPCommand()  -> processCommand()
```

### Protocolo K.O.R.E. (texto | delimitado)

#### Comandos de Sistema

| Comando | Resposta | Descrição |
|---------|----------|-----------|
| `ping` | `KORE_COMPANION` | Handshake |
| `version` | `version\|0.9.0` | Versão do firmware |
| `uptime` | `uptime\|<segundos>` | Tempo de atividade |
| `current_face` | `current_face\|<nome>` | Face atual |

#### Comandos de Mídia

| Comando | Descrição |
|---------|-----------|
| `spotify\|TRACK\|ARTIST\|ALBUM\|PROGRESS\|DURATION` | Atualiza reprodução |
| `spotify_stop` | Finaliza reprodução |

#### Comandos de Notificação

| Comando | Descrição |
|---------|-----------|
| `notification\|APP\|TITLE\|BODY` | Nova notificação |

#### Comandos de Clima

| Comando | Descrição |
|---------|-----------|
| `weather\|CITY\|TEMP\|HITEMP\|LOWTEMP\|ICON` | Atualiza clima |

#### Comandos de WiFi

| Comando | Resposta | Descrição |
|---------|----------|-----------|
| `wifi_status` | `CONNECTED\|SSID\|IP` ou `DISCONNECTED` | Status WiFi |
| `wifi_connect\|SSID\|PASSWORD` | `wifi_connect\|WIFI_CONNECTING` | Conectar WiFi |

#### Comandos de Relógio

| Comando | Descrição |
|---------|-----------|
| `time\|HOUR\|MINUTE\|SECOND` | Sincroniza relógio |

#### Comandos de Face

| Comando | Descrição |
|---------|-----------|
| `happy`, `extrahappy`, `sad`, `sleep`, `surprise`, `loving`, `confused`, `demon` | Define face |

### Canais de Saída

O `output_manager.h` gerencia o roteamento de respostas:

```
sendResponse(response)
  |-> Se BLE conectado: sendBLECommand(response)
  |-> Senão: Serial.println(response)
```

### BLE (NimBLE)

- **Função**: GATT Server (Peripheral)
- **Device Name**: "K.O.R.E."
- **Service UUID**: `8C0F0001-5A8F-4E7E-9D43-92D67E4D0001`
- **RX Characteristic** (WRITE): `8C0F0002...`
- **TX Characteristic** (READ + NOTIFY): `8C0F0003...`
- **Re-advertising** automático após disconnect.
- **Sem segurança**: fato - não há configuração de bonding, MITM protection ou criptografia.

### TCP (WiFi)

- **Porta**: 6666
- **Cliente único**: fato - apenas um cliente TCP por vez.
- **Sem keepalive** explícito.
- **Comando** lido via `readStringUntil('\n')`.

### ANCS

- **Reservado para implementação futura**: o módulo `ancs_manager.h` contém apenas funções vazias com `// TODO`. As variáveis globais (`ancsCommand`, `ancsCommandPending`, `ancsConnected`) estão declaradas e o `input_manager.h` já integra o canal, mas nenhum dado é processado.
- O código permanece no firmware como placeholder para implementação futura do Apple Notification Center Service.

### Problemas identificados na comunicação

1. **Comandos sem fila**: fato - se múltiplos canais enviarem comandos simultaneamente, a variável `bleCommand`/`tcpCommand` pode ser sobrescrita antes do processamento.
2. **TCP aceita apenas 1 cliente**: fato - não há loop para aceitar novas conexões enquanto uma conexão está ativa.
3. **BLE sem segurança**: fato - qualquer dispositivo pode conectar e enviar comandos. *(Inferência: o impacto real depende do ambiente de uso)*.
4. **sendResponse favorece BLE**: fato - se BLE está conectado, respostas vão apenas para BLE, não para Serial. Isso dificulta debug.
5. **Cópia para String no callback BLE**: fato - o callback `onWrite` copia o valor recebido para `String`. *(Inferência: pode causar fragmentação de heap em cenários de uso intensivo)*.

---

## 6. Gerenciamento de Estado

### Estado Global (KORE_OS.ino)

Todas as variáveis de estado do sistema estão declaradas como globais no arquivo principal:

```c
// Display
DisplayMode currentMode = DISPLAY_EMOTION;
DisplayMode previousMode = DISPLAY_EMOTION;
bool modeChanged = false;

// Clima
WeatherData currentWeather;
bool weatherActive = false;
unsigned long weatherStartTime = 0;

// Faces
FaceType defaultFace = FACE_HAPPY;
FaceType currentFace = defaultFace;
FaceType faceBeforeSpotify = defaultFace;
unsigned long lastActivity = 0;
unsigned long spotifyFaceTimer = 0;

// Cores
uint16_t KORE_CYAN;
```

### Estado nos Managers

Cada manager também declara suas próprias variáveis globais:

- `ble_manager.h`: `bleServer`, `bleService`, `bleRXCharacteristic`, `bleTXCharacteristic`, `bleCommand`, `bleCommandPending`, `bleConnected`
- `tcp_manager.h`: `tcpServer`, `tcpClient`, `tcpCommand`, `tcpCommandPending`
- `ancs_manager.h`: `ancsCommand`, `ancsCommandPending`, `ancsConnected`
- `notifications.h`: `notificationQueue`, `notificationHead`, `notificationTail`, `notificationActive`, etc.
- `clock_manager.h`: `clockState`
- `demon_manager.h`: `demonTriggered`, `uptimeDemonTriggered`, etc.
- `spotify_screen.h`: `spotifyTrack`, `spotifyArtist`, `spotifyActive`, `demonActive`, etc.

### Problemas identificados no gerenciamento de estado

1. **Zero encapsulamento**: fato - todas as variáveis são globais e acessíveis de qualquer lugar.
2. **Duplicação de flags**: fato - `spotify_screen.h` e `demon_manager.h` têm flags sobrepostas (`demonActive`, `demonTriggered`).
3. **Estado espalhado**: fato - não há um único local para entender o estado completo do sistema.
4. **`extern` repetido em múltiplos lugares**: fato - `command_parser.h`, `mood_manager.h`, `sleep_manager.h`, etc. declaram `extern` para as mesmas variáveis.

---

## 7. Serviços Existentes

### Serviços Ativos

| Serviço | Status | Descrição |
|---------|--------|-----------|
| BLE GATT Server | Funcional | NimBLE peripheral, comunicação bidirecional |
| TCP Server | Funcional | WiFi, porta 6666, 1 cliente |
| Serial USB | Funcional | Leitura de comandos via `\n` |
| WiFi Manager | Funcional | Conexão STA com persistência |
| Clock | Funcional | Relógio por software, sincronizável |
| Sleep Manager | Funcional | Sleep noturno (22h-7h) e por inatividade (15min) |
| Emotion Detection | Funcional | Keyword matching sobre notificações |
| Notification Queue | Funcional | Fila circular de 10 notificações |
| Spotify Screen | Funcional | Cassete animado, progresso, demon mode |
| Weather Screen | Funcional | Ícone, temperatura, cidade, max/min |
| Demon Easter Egg | Funcional | Uptime 66h06m + tracks específicas aos 66s |
| Boot Screen | Funcional | Logo + barra de progresso |
| Face System (8 faces) | Funcional | Happy, ExtraHappy, Sad, Sleep, Surprise, Loving, Confused, Demon |

### Serviços Reservados para Implementação Futura

| Serviço | Status | Descrição |
|---------|--------|-----------|
| ANCS | Placeholder | Apple Notification Center Service - estrutura de dados e integração no input manager preparadas, aguardando implementação |

---

## 8. Bibliotecas Utilizadas

### Bibliotecas Arduino (core)

| Biblioteca | Função |
|-----------|--------|
| `Arduino.h` | Tipos, `millis()`, `delay()`, `String`, `Serial` |
| `SPI.h` | Barramento SPI para o display |
| `pgmspace.h` | Armazenamento de dados em PROGMEM (Flash) |
| `WiFi.h` | Conectividade WiFi STA |
| `Preferences.h` | Armazenamento NVS para credenciais WiFi |

### Bibliotecas Externas

| Biblioteca | Função |
|-----------|--------|
| `Adafruit_GFX.h` | Biblioteca gráfica base |
| `Adafruit_ST7789.h` | Driver para display ST7789 240x320 |
| `U8g2_for_Adafruit_GFX.h` | Renderização UTF-8 sobre Adafruit GFX (u8g2) |
| `NimBLEDevice.h` | Bluetooth Low Energy (NimBLE stack) |
| `FFat.h` | FAT Filesystem sobre Flash |
| `ArduinoJson.h` | Parsing do `emotion_rules.json` |

### Dependências de Build

| Dependência | Função |
|-------------|--------|
| Python 3.12+ | Execução do `build_fatfs.py` |
| `wl_fatfsgen.py` | Geração de imagem FATFS com wear-leveling |

---

## 9. Dependências Externas

### Hardware

| Componente | Especificação |
|------------|--------------|
| ESP32-S3 | N16R8 (16MB Flash, 8MB PSRAM) |
| Display TFT | ST7789, 240x320, SPI |
| Pinout | CS=14, DC=15, RST=16, MOSI=17, SCLK=18 |

### Software (Runtime)

| Dependência | Propósito |
|-------------|-----------|
| Arduino Framework | Runtime, HAL, WiFi, SPI |
| NimBLE | Bluetooth LE stack (substitui o Bluedroid padrão) |
| Adafruit ST7789 | Driver do display |
| U8g2 | Renderização de fontes TrueType/UTF-8 |
| ArduinoJson | Parsing JSON |
| FFat | Filesystem FAT em Flash |
| FATFS gen tools (Python) | Geração da imagem FATFS para upload |

---

## 10. Organização dos Módulos

### Acoplamento entre módulos

```
KORE_OS.ino
  |
  +--> config.h                 (desacoplado)
  +--> display_context.h        (desacoplado - só declara externs)
  |
  +--> command_parser.h         (depende de: mood_manager, clock_manager, weather_manager)
  |      +--> extern: spotifyActive, tft, KORE_CYAN, notificationWasDrawn, lastActivity
  |
  +--> mood_manager.h           (depende de: display_context.h)
  |      +--> extern: currentFace, faceBeforeSpotify
  |      +--> chama: draw<Face>Screen, animate<Face>Face
  |
  +--> display_manager.h        (chama: onEnter/update/render de cada módulo)
  |
  +--> input_manager.h          (depende de: command_parser, ble_manager, ancs_manager, tcp_manager)
  |
  +--> output_manager.h         (depende de: ble_manager)
  |
  +--> sleep_manager.h          (depende de: clock_manager, mood_manager)
  |      +--> extern: defaultFace, currentFace, lastActivity, currentMode
  |
  +--> emotion_manager.h        (depende de: mood_manager, ArduinoJson, FFat)
  |
  +--> wifi_manager.h           (depende de: WiFi.h, Preferences.h)
  |
  +--> ble_manager.h            (depende de: NimBLEDevice.h)
  |
  +--> tcp_manager.h            (depende de: WiFi.h)
  |
  +--> ancs_manager.h           (depende de: NimBLEDevice.h)
  |
  +--> weather_manager.h        (depende de: display_context, weather_icons, config)
  |
  +--> notifications.h          (depende de: display_context, notification_icons, emotion_manager)
  |      +--> extern: defaultFace
  |
  +--> spotify_screen.h         (depende de: display_context, mood_manager, demon_manager)
  |
  +--> demon_manager.h          (depende de: mood_manager)
  |      +--> extern: currentFace
  |
  +--> boot_screen.h            (depende de: cat.h)
```

### Padrão de dependência

O padrão dominante é:
1. Módulos dependem de `display_context.h` para acessar `tft`, `u8g2`, `KORE_CYAN`.
2. Módulos dependem de `mood_manager.h` para acessar `FaceType` e funções de face.
3. `command_parser.h` é o ponto central que depende de quase todos os managers.
4. Módulos se comunicam via variáveis `extern` - não há interface formal.

---

## 11. Fluxo de Eventos

### Exemplo 1: Notificação Recebida

```
Companion envia (BLE/Serial/TCP):
  "notification|whatsapp|João|Festa hoje às 20h"
         |
         v
input_manager.h: updateInputManager()
  -> detecta comando disponível
  -> processCommand("notification|whatsapp|João|Festa hoje às 20h")
         |
         v
command_parser.h: processCommand()
  -> identifica "notification|"
  -> chama parseNotificationCommand(command)
  -> reseta notificationWasDrawn = false
         |
         v
notifications.h: parseNotificationCommand()
  -> faz split pelos pipes
  -> detecta emoção do conteúdo: detectEmotion("João Festa hoje às 20h")
  -> enqueueNotification(app, title, body)
  -> se não há notificação ativa: dequeueNotification()
         |
         v
display_manager.h: updateDisplayState()
  -> notificationActive == true
  -> nextMode = DISPLAY_NOTIFICATION
         |
         v
handleDisplayTransition()
  -> onEnterNotification(): fillScreen(BLACK)
         |
         v
renderCurrentDisplay()
  -> renderNotification()
  -> drawNotificationScreen() - desenha ícone + app + título + body
         |
         v
8 segundos depois:
  updateNotification()
  -> notificationActive = false
  -> setFace(notificationEmotion)
  -> notificationEmotionActive = true
         |
         v
5 segundos depois:
  -> notificationEmotionActive = false
  -> setFace(defaultFace)
  -> dequeueNotification() - próxima da fila, se houver
```

### Exemplo 2: Comando de Face

```
Companion envia:
  "loving"
         |
         v
processCommand("loving")
  -> identifica como comando de face
  -> setFace(FACE_LOVING)
         |
         v
mood_manager.h: setFace(FACE_LOVING)
  -> currentFace = FACE_LOVING
  -> drawLovingScreen(tft, KORE_CYAN)
         |
         v
loop() continua:
  renderCurrentDisplay()
  -> renderEmotion()
  -> animateLovingFace() - coração pulsando
```

---

## 12. Persistência

### Preferences (NVS)

- **Namespace**: `"wifi"`
- **Chaves**: `"ssid"` (String), `"password"` (String)
- **Uso**: Salvar/carregar credenciais WiFi
- **API**: `Preferences.h` (Arduino)

### FFat (FAT Flash)

- **Partição**: FATFS com wear-leveling
- **Tamanho**: 0x960000 (~9.6MB)
- **Arquivo**: `/emotion_rules.json` (2.5KB)
- **Geração**: Python script `scripts/build_fatfs.py` → `build/fatfs.img`
- **Uso**: Apenas para carregar regras de emoção no boot

### EEPROM

- **Não utilizada**.

---

## 13. FreeRTOS

### Não utilizado.

Fato - O firmware executa integralmente sobre o loop do Arduino, que por baixo é uma única task FreeRTOS com stack padrão.

Não existem:
- Tasks dedicadas
- Semáforos
- Filas (Queues)
- Mutexes
- Event Groups
- Task notifications

*(Inferência: qualquer operação bloqueante como `delay()` ou loops longos paralisa todo o sistema, incluindo comunicação BLE, processamento de entrada e renderização. O impacto prático depende da frequência e duração dessas operações no comportamento real do dispositivo.)*

---

## 14. Mapa Arquitetural do Firmware

### Diagrama de Fluxo entre Módulos

```
                            ┌─────────────────────────────┐
                            │       KORE_OS.ino           │
                            │  (Orquestrador do sistema)  │
                            └──────────┬──────────────────┘
                                       │
                    ┌──────────────────┼──────────────────┐
                    │                  │                  │
                    ▼                  ▼                  ▼
          ┌─────────────────┐ ┌──────────────┐ ┌──────────────────┐
          │   setup()       │ │   loop()     │ │   Globals        │
          │ Inicializa      │ │ Executa a    │ │   currentMode    │
          │ hardware e      │ │ sequência de │ │   currentFace    │
          │ serviços        │ │ atualizações │ │   lastActivity   │
          └─────────────────┘ └──────┬───────┘ └──────────────────┘
                                     │
                    ┌────────────────┼────────────────────┐
                    │                │                    │
                    ▼                ▼                    ▼
          ┌─────────────────┐ ┌──────────────┐ ┌──────────────────┐
          │  input_manager  │ │    clock     │ │      sleep       │
          │  (Serial, BLE,  │ │   manager    │ │     manager      │
          │   TCP, ANCS)    │ │              │ │                  │
          └────────┬────────┘ └──────────────┘ └──────────────────┘
                   │
                   ▼
          ┌─────────────────┐
          │  command_parser │
          │  (Roteador      │
          │   central)      │
          └───┬────┬────┬───┘
              │    │    │
     ┌────────┘    │    └──────────┐
     ▼             ▼               ▼
┌──────────┐ ┌──────────┐ ┌──────────────┐
│notification│ weather  │   spotify      │
│ handler   │ │ handler │   handler      │
│(notifica- │ │(weather │   (spotify_    │
│tions.h)   │ │_manager)│   screen.h)    │
└─────┬─────┘ └──────────└──────┬───────┘
      │                         │
      ▼                         ▼
┌──────────────┐      ┌────────────────┐
│  emotion     │      │  demon_manager │
│  manager     │      │                │
│  (keyword    │      │  (easter egg)  │
│   detection) │      └────────────────┘
└──────────────┘
      │
      ▼
┌────────────────────────────────────────┐
│          display_manager                │
│  (FSM: updateDisplayState →            │
│   handleDisplayTransition →            │
│   updateActiveModule →                 │
│   renderCurrentDisplay)                │
└──────┬──────────────────────────┬──────┘
       │                          │
       ▼                          ▼
┌──────────────┐          ┌────────────────┐
│   mood       │          │  screen modules│
│   manager    │          │  (boot_screen, │
│   (face      │          │   notifications│
│    dispatch) │          │   spotify_)    │
└──────┬───────┘          └────────────────┘
       │
       ▼
┌────────────────────────────────────────┐
│      Face Drawing Functions            │
│  (happy_face.h, sad_face.h, etc.)      │
│   face_utils.h (dot, clearDot, blink)  │
└────────────────────────────────────────┘
       │
       ▼
┌────────────────────────────────────────┐
│            Display (TFT ST7789)        │
│         via Adafruit_ST7789 + U8g2     │
└────────────────────────────────────────┘
```

### Fluxo de Dados entre Camadas

```
Companion App (Externo)
       │
       ├── BLE (NimBLE GATT) ────┐
       ├── Serial USB ───────────┤
       ├── TCP (WiFi) ───────────┤
       └── ANCS (futuro) ────────┤
                                 ▼
                      ┌─────────────────────┐
                      │   input_manager.h   │
                      │  (multiplexador)    │
                      └─────────┬───────────┘
                                │
                                ▼
                      ┌─────────────────────┐
                      │  command_parser.h   │
                      │  (processCommand)   │
                      └──┬──────┬──────┬────┘
                         │      │      │
              ┌──────────┘      │      └──────────┐
              ▼                 ▼                 ▼
     ┌──────────────┐  ┌──────────────┐  ┌──────────────┐
     │ Atualiza     │  │ Atualiza     │  │ Atualiza     │
     │ Estado       │  │ DisplayMode  │  │ Face         │
     │ (globals)    │  │ (FSM)        │  │ (mood)       │
     └──────────────┘  └──────┬───────┘  └──────────────┘
                              │
                              ▼
                     ┌──────────────────┐
                     │ renderCurrent    │
                     │ Display()        │
                     └────────┬─────────┘
                              │
                              ▼
                     ┌──────────────────┐
                     │ TFT + U8g2       │
                     │ (renderização)   │
                     └──────────────────┘
```

---

## 15. Mapa de Memória

### Visão Geral dos Recursos de Memória

O ESP32-S3 N16R8 possui os seguintes recursos de memória, conforme documentação do fabricante e configuração do Arduino Core:

| Recurso | Tamanho | Descrição |
|---------|---------|-----------|
| Flash (Quad SPI) | 16MB | Código, dados constantes, PROGMEM, FFat |
| PSRAM (Octal SPI) | 8MB | Expansão de heap para dados dinâmicos |
| SRAM interna | 512KB | Heap + Stack + BSS + Data |
| NVS (Non-Volatile Storage) | ~20KB (partição padrão) | Preferences API |

### Distribuição de Memória

#### Flash (16MB)

O layout da partição Flash para o ESP32-S3 com Arduino Framework tipicamente segue:

| Partição | Tamanho Típico | Conteúdo |
|----------|---------------|----------|
| Bootloader | 64KB | Bootloader do ESP32-S3 |
| Partition Table | 4KB | Tabela de partições |
| nvs | 20KB | Non-Volatile Storage (Preferences WiFi) |
| otadata | 8KB | OTA data |
| app0 (factory) | ~5-6MB | Código compilado do firmware |
| ffat | ~9.6MB (0x960000) | FAT filesystem (emotion_rules.json) |

#### PROGMEM

Fato - O firmware utiliza PROGMEM extensivamente para armazenar dados constantes na Flash em vez de SRAM:

| Asset | Tamanho (aproximado) | Localização |
|-------|---------------------|-------------|
| cat.h bitmap (100x100) | ~1250 bytes | PROGMEM |
| notification_icons (6x 80x80) | ~6 x 800 bytes = ~4800 bytes | PROGMEM |
| weather_icons (6x 64x64) | ~6 x 512 bytes = ~3072 bytes | PROGMEM |
| Fontes u8g2 | Vários KB (vinculadas pela biblioteca) | PROGMEM |

#### Heap (DRAM + PSRAM)

O heap do ESP32-S3 pode utilizar tanto a SRAM interna (512KB) quanto a PSRAM externa (8MB).

Instâncias de alocação dinâmica observadas no código:

| Operação | Tipo | Frequência | Observação |
|----------|------|------------|------------|
| `String` temporárias no parsing | Alocação dinâmica | Por comando recebido | `String::substring()`, `indexOf()`, `toInt()` criam objetos temporários |
| `ArduinoJson::deserializeJson()` | Alocação dinâmica | Uma vez no boot | Parsing do `emotion_rules.json` (~2.5KB) |
| `NimBLEDevice::createServer()` | Alocação interna | Uma vez no boot | Estruturas BLE |
| `WiFiServer` | Alocação interna | Uma vez no boot | Socket TCP |
| `Adafruit_ST7789` | Frame buffer | Por refresh | Biblioteca gerencia internamente |

*(Inferência: o uso de `String` para parsing de comandos pode causar fragmentação de heap em execução prolongada, especialmente se comandos são recebidos em alta frequência. Não há evidência direta de falha por fragmentação no firmware atual - isto requereria medição com monitor de heap em execução prolongada.)*

#### Stack

- **Stack padrão do Arduino loop**: ~8-16KB (configuração padrão do Arduino Core para ESP32).
- A `boot_screen.h` utiliza chamadas aninhadas (`bootScreen` → `drawProgressBar`), mas sem profundidade excessiva.
- *(Inferência: o stack disponível é suficiente para o padrão de chamadas atual, dado que não há recursão ou alocação significativa no stack.)*

#### FFat

- **Partição**: 0x960000 (~9.6MB)
- **Uso atual**: ~2.5KB (apenas `emotion_rules.json`)
- **Espaço livre**: ~9.6MB **(99.97% ocioso)**.

#### Preferences (NVS)

- **Namespace**: `"wifi"`
- **Chaves**: 2 entradas (`ssid`, `password`)
- **Consumo**: ~200 bytes
- **API**: `Preferences.h` - utiliza a partição NVS padrão do ESP32.

### Estimativa de Consumo de RAM em Runtime

*(Inferência - valores estimados com base no código e na configuração típica do ESP32-S3)*

| Componente | RAM Estimada | Tipo |
|------------|-------------|------|
| Código (.text + .rodata) | ~1-2MB | Flash (executado in-place via cache) |
| Variáveis globais (BSS + Data) | ~10-20KB | SRAM |
| Stack do loop | ~8-16KB | SRAM |
| Heap livre inicial | ~400-480KB SRAM + ~8MB PSRAM | SRAM + PSRAM |
| NimBLE stack | ~50-100KB | SRAM |
| WiFi stack | ~50-100KB | SRAM |
| Adafruit ST7789 framebuffer | ~150KB (320x240x16bpp) | PSRAM (típico para SPI display) |
| u8g2 buffer | ~1-2KB | SRAM |
| FATFS buffers | ~4-8KB | SRAM |

### Pontos de Atenção

1. **FFat massivamente subutilizado**: ~9.6MB alocados, ~2.5KB usados. *(Inferência: há potencial para realocar parte deste espaço para outras finalidades se necessário, mas não há evidência de problema atual.)*
2. **PROGMEM bem utilizado**: bitmaps e ícones corretamente armazenados em Flash, sem consumo desnecessário de SRAM.
3. **Heap com PSRAM disponível**: a presença de 8MB de PSRAM reduz significativamente o risco de falta de memória, mesmo com uso de `String`. *(Inferência: o risco de fragmentação é menor do que em dispositivos sem PSRAM.)*

---

## 16. Pontos Fortes da Implementação Atual

1. **Simplicidade**: o firmware é fácil de entender. Um desenvolvedor experiente pode compreender o fluxo completo em algumas horas.

2. **Protocolo simples e eficaz**: texto `|` delimitado é fácil de debugar via Serial Monitor.

3. **Display FSM funcional**: a máquina de estados de 4 modos atende bem ao propósito, com prioridade clara.

4. **Sistema de faces modular**: adicionar uma nova face requer apenas criar um novo arquivo e adicionar ao switch.

5. **Asset pipeline**: ícones e bitmaps bem organizados em PROGMEM, economizando RAM.

6. **Emotion detection configurável**: regras em JSON permitem ajustar keywords sem recompilar.

7. **Demon easter egg**: mostra personalidade e atenção a detalhes.

8. **NimBLE**: escolha acertada de stack BLE (mais estável e eficiente que o Bluedroid padrão).

9. **FFat + wear-leveling**: escolha adequada para armazenamento de arquivos.

10. **Cores K.O.R.E. Cyan**: identidade visual consistente mesmo no display.

---

## 17. Características Arquiteturais

### Organização em Headers (.h)

O firmware atual utiliza exclusivamente arquivos de header (`.h`) sem arquivos de implementação (`.cpp`). Esta é uma característica arquitetural, não uma dívida técnica por si só.

No contexto do Arduino Framework, esta abordagem é comum e funcional porque:
- O Arduino IDE pré-processa o arquivo `.ino` e gera declarações `#include` implícitas.
- O compilador C++ lida corretamente com funções definidas em headers quando incluídas uma única vez no translation unit principal.
- Os guards (`#ifndef`/`#define`/`#endif` e `#pragma once`) previnem inclusões múltiplas.

*(Inferência: esta abordagem pode causar aumento no tempo de compilação e no tamanho do binário final devido a possíveis definições duplicadas em diferentes unidades de compilação, mas não há evidência direta de problemas em tempo de execução causados por esta característica.)*

### Decisão consciente

Por ser uma característica funcional do firmware atual, a organização header-only **não será tratada como dívida técnica** neste documento. Qualquer decisão de migração para `.cpp`/`.h` deverá ser baseada em evidências concretas de problemas (e.g., aumento no tamanho do binário, violação de ODR, lentidão de compilação) e não por preferência arquitetural.

---

## 18. Auditoria de Delays

### Metodologia

Cada ocorrência de `delay()` no firmware foi catalogada e classificada em uma das três categorias:

| Classificação | Significado |
|-------------|-------------|
| **Necessário** | O delay é indispensável para o funcionamento correto do hardware ou protocolo. Sua remoção quebraria o comportamento esperado. |
| **Aceitável** | O delay não é ideal, mas ocorre em contexto onde o bloqueio não prejudica a operação (e.g., setup, boot). |
| **Prejudicial** | O delay bloqueia o loop principal durante operação normal, impedindo processamento de comunicação, entrada ou renderização. |

### Tabela de Delays

| # | Localização | Arquivo | Linha | Duração | Contexto | Classificação | Justificativa |
|---|-------------|---------|-------|---------|----------|---------------|---------------|
| 1 | setup() | KORE_OS.ino | 87 | 1000ms | Aguarda estabilização da Serial | **Aceitável** | Ocorre apenas no boot. A Serial pode perder os primeiros bytes se lida imediatamente. |
| 2 | bootScreen() | boot_screen.h | 91 | 25ms (x196 = ~4.9s) | Animação da barra de progresso | **Aceitável** | Ocorre apenas no boot. A barra de progresso é uma animação intencional. |
| 3 | bootScreen() | boot_screen.h | 94 | 1000ms | Pausa final exibindo logo completo | **Aceitável** | Ocorre apenas no boot. Tempo para o usuário ver o logo. |
| 4 | animateHappyFace() | happy_face.h | 95 | 120ms | Mantém olhos fechados durante blink | **Prejudicial** | Bloqueia o loop durante operação normal. O efeito visual (olhos fechados) é necessário, mas a implementação bloqueante não. |
| 5 | animateExtraHappyFace() | extra_happy_face.h | ~80 | 120ms | Mantém olhos fechados durante blink | **Prejudicial** | Mesmo padrão do happy_face. |
| 6 | animateSadFace() | sad_face.h | ~80 | 120ms | Mantém olhos fechados durante blink | **Prejudicial** | Mesmo padrão. |
| 7 | animateSurpriseFace() | surprise_face.h | ~80 | 120ms | Mantém olhos fechados durante blink | **Prejudicial** | Mesmo padrão. |
| 8 | animateLovingFace() | loving_face.h | ~100 | 120ms | Mantém olhos fechados durante blink | **Prejudicial** | Mesmo padrão. |
| 9 | animateConfusedFace() | confused_face.h | ~80 | 120ms | Mantém olhos fechados durante blink | **Prejudicial** | Mesmo padrão. |
| 10 | drawBlinkEyes() - demon | demon_face.h | 133 | 20ms | Glitch effect delay | **Aceitável** | Delay curto (20ms), ocorre apenas quando o modo demon está ativo. |
| 11 | sleep_face.h | sleep_face.h | ~90 | ~100ms | Animação ZZZ | **Prejudicial** | *(inferência - ver análogo nas outras faces)* |

### Resumo da Auditoria

| Classificação | Quantidade | Impacto |
|-------------|-----------|---------|
| Necessário | 0 | Nenhum delay é estritamente necessário por hardware |
| Aceitável | 4 | Apenas no boot ou em modos especiais (demon glitch) |
| Prejudicial | ~6-7 | Todos os blinks de face (120ms cada), ocorrendo a cada 2-5s durante operação normal |

### Impacto dos Delays Prejudiciais

Cada blink de 120ms bloqueia:
- Processamento de comandos BLE/Serial/TCP
- Atualização do display em outros modos
- Atualização do clock
- Gerenciamento de sleep

Considerando que o blink ocorre a cada 2-5s (randomizado), o firmware passa aproximadamente **2-6% do tempo bloqueado** apenas com animações de face. *(inferência - o percentual exato depende da frequência real de blink e do número de faces ativas)*.

---

## 19. Dívidas Técnicas

### Médias

| ID | Dívida | Localização | Impacto | Evidência |
|----|--------|-------------|---------|-----------|
| DT-01 | `delay(120)` nas animações de blink (prejudicial) | Todas as faces | Bloqueia loop principal durante operação, impede processamento de comunicação | Fato: delay(120) presente em 6+ funções animate |
| DT-02 | `command_parser.h` monolítico | `core/command_parser.h` | Difícil manutenção, ~190 linhas em if/else único | Fato: estrutura do código |
| DT-03 | TCP server: 1 cliente sem reconexão | `tcp_manager.h` | Conexão perdida não é recuperada automaticamente | Fato: não há loop de accept enquanto cliente conectado |
| DT-04 | Sem validação de entrada nos parsers | `command_parser.h`, `notifications.h`, `spotify_screen.h` | Comando malformado pode causar comportamento indefinido *(inferência)* | Fato: `indexOf()` sem checagem de -1 |
| DT-05 | `extern` repetido em múltiplos arquivos | Vários | Manutenção difícil, risco de inconsistências | Fato: mesmas variáveis declaradas extern em 4+ arquivos |
| DT-06 | Pinos de hardware hardcoded | `KORE_OS.ino` | Difícil adaptar para outro hardware | Fato: defines no .ino principal |

### Leves

| ID | Dívida | Localização | Impacto |
|----|--------|-------------|---------|
| DT-07 | Números mágicos (timers, thresholds) | Vários | Dificulta manutenção e ajuste |
| DT-08 | `random()` usado sem seed | `face_utils.h`, `demon_face.h` | Sequência previsível *(inferência - impacto prático baixo)* |
| DT-09 | Sem tratamento de erro no BLE | `ble_manager.h` | Falhas silenciosas *(inferência)* |
| DT-10 | Respostas só vão para BLE se conectado | `output_manager.h` | Serial silencioso durante debug com BLE |
| DT-11 | `notificationWasDrawn` reset apenas em comandos | `notifications.h` | Possível notificação não redesenhada *(inferência)* |
| DT-12 | Delay na boot screen (aceitável) | `boot_screen.h` | ~5s bloqueante no boot, aceitável por ser setup |
| DT-13 | Overlap de flags demon | `spotify_screen.h` + `demon_manager.h` | Duas implementações paralelas de lógica similar |

### Não Consideradas Dívidas Técnicas

Os itens abaixo foram avaliados e **não** estão classificados como dívidas técnicas no escopo atual:

| Item | Motivo |
|------|--------|
| Organização header-only (.h sem .cpp) | Característica arquitetural funcional. Ver seção [17. Características Arquiteturais](#17-características-arquiteturais). |
| ANCS stub | Módulo reservado para implementação futura. Placeholder intencional. |
| Uso de `String` no parsing | Requer auditoria de desempenho antes de classificar como dívida. Ver seção [21. Oportunidades de Melhoria](#21-oportunidades-de-melhoria). |
| Ausência de watchdog | Requer investigação sobre mecanismos existentes no Arduino Core ESP32 antes de determinar se há lacuna. |

---

## 20. Riscos

### Risco 1: Bloqueio do loop por delays prejudiciais

**Tipo**: Fato com inferência de impacto
**Descrição**: Os `delay(120)` nas animações de blink bloqueiam o loop principal.
**Impacto potencial**: *(inferência)* Perda de comandos BLE/Serial, atraso na renderização, degradação da experiência em cenários de uso intensivo.
**Mitigação possível**: Substituir por FSM baseada em `millis()` nas animações de blink, preservando o tempo de 120ms de olhos fechados.

### Risco 2: Fragmentação de heap por String

**Tipo**: Inferência
**Descrição**: O firmware utiliza `String` para parsing de comandos no loop principal. `substring()`, `indexOf()`, `toInt()` criam objetos temporários.
**Impacto potencial**: *(inferência)* Fragmentação de heap pode levar a falhas de alocação em execução prolongada. O risco é atenuado pela presença de 8MB de PSRAM.
**Mitigação possível**: Auditoria de uso de memória para identificar hot paths onde buffers fixos trazem ganho mensurável.

### Risco 3: BLE sem segurança

**Tipo**: Fato
**Descrição**: Não há configuração de bonding, MITM protection ou criptografia no GATT server. Qualquer dispositivo próximo pode conectar e enviar comandos.
**Impacto potencial**: *(inferência)* Dispositivos não autorizados podem enviar comandos ao firmware. O impacto real depende do ambiente de uso.
**Mitigação possível**: Adicionar configuração de segurança BLE (fora do escopo do HARNESS-001, pois altera comportamento funcional).

### Risco 4: Overflow da fila de notificações

**Tipo**: Fato
**Descrição**: A fila circular tem capacidade 10. Se o Companion enviar notificações mais rápido que o display consegue consumir, notificações são descartadas.
**Impacto potencial**: *(inferência)* Perda de notificações sem qualquer aviso ou log.
**Mitigação possível**: Adicionar log de descarte ou aumentar capacidade da fila.

### Risco 5: Timeout de 15s no Spotify sem heartbeat

**Tipo**: Fato
**Descrição**: Se o Companion parar de enviar atualizações, o Spotify desliga após 15s.
**Impacto potencial**: *(inferência)* A tela Spotify pode fechar durante pausas longas ou instabilidade de comunicação.
**Mitigação possível**: Implementar heartbeat ou aumentar timeout (fora do escopo do HARNESS-001, requer especificação).

### Risco 6: Gargalo single-thread

**Tipo**: Inferência
**Descrição**: Tudo executa no mesmo loop: comunicação, renderização, animação, timers.
**Impacto potencial**: *(inferência)* Sob carga alta de comandos, a renderização pode ficar irregular.
**Mitigação possível**: Otimizar pontos bloqueantes (delays) e priorizar processamento de entrada.

---

## 21. Oportunidades de Melhoria

### 1. Substituir delays prejudiciais por FSM baseada em millis()

Os delays classificados como **prejudiciais** (blink das faces) devem ser substituídos por uma máquina de estados que preserve o comportamento visual exato:

- Estado "olhos abertos": tempo aleatório entre 2000-5000ms
- Transição para "olhos fechados": desenhar `drawBlinkEyes()`
- Estado "olhos fechados": manter por 120ms (timer, não delay)
- Transição para "olhos abertos": redesenhar face

**Requisito**: o comportamento visual deve permanecer **absolutamente idêntico**. A alteração é apenas no mecanismo de temporização.

### 2. Auditoria de desempenho e uso de memória para String

Antes de qualquer substituição de `String` por buffers fixos, realizar uma auditoria para:

- Medir o consumo real de heap durante parsing de comandos típicos.
- Identificar hot paths (trechos executados com maior frequência).
- Identificar picos de alocação temporária.
- Verificar se o uso de PSRAM já está sendo utilizado para estas alocações.

Apenas hot paths com ganho mensurável de estabilidade ou consumo de memória deverão ser convertidos.

### 3. Centralizar declarações extern

Criar um único header `globals.h` que declare todas as variáveis globais com `extern`, e definir todas em `KORE_OS.ino`. Isso elimina a duplicação de `extern` em 4+ arquivos.

### 4. Investigar mecanismos de watchdog do Arduino Core ESP32

Antes de implementar qualquer watchdog:
- Verificar se o Arduino Core ESP32 já fornece `esp_task_wdt_` (Task Watchdog Timer).
- Verificar se o watchdog de hardware (TWDT) já está habilitado por padrão.
- Testar se o firmware atual responde a travamentos simulados.
- Apenas se houver lacuna comprovada, documentar justificativa técnica para implementação.

### 5. Adicionar validação de entrada nos parsers

Verificar se os índices retornados por `indexOf()` são válidos (diferentes de -1) antes de realizar `substring()`. Validar se dados numéricos (`toInt()`) estão dentro de faixas esperadas.

### 6. Melhorar output routing

Enviar respostas simultaneamente para Serial e BLE quando ambos estiverem disponíveis, facilitando debug.

### 7. Extrair constantes nomeadas

Substituir números mágicos (timers: 15000, 8000, 5000, 2000, 120; tolerâncias, thresholds) por constantes nomeadas com `constexpr` ou `#define`.

---

## 22. Recomendações para o HARNESS-001

Com base na análise completa do firmware, as seguintes recomendações são feitas para a execução do HARNESS-001.

A ordem reflete a filosofia de estabilização: primeiro atividades de risco mínimo (build, warnings, bugs comprovados, parsers, código morto, constantes), seguidas por melhorias estruturais. Alterações de comportamento (como substituição de delays) ocorrem somente após a estabilização inicial.

### Fase A — Risco Mínimo (Build, Compilação, Warnings)

1. **Compilar o firmware e zerar warnings** - Garantir que o firmware compila sem erros e sem warnings relevantes no Arduino IDE/CLI. Este é o passo zero de qualquer estabilização.

### Fase B — Correções de Bugs e Higienização

2. **Validar parsers de entrada** - Adicionar verificação de índices antes de `substring()` em `command_parser.h`, `notifications.h`, `spotify_screen.h` e `weather_manager.h`. Validar retorno de `indexOf()` contra -1 e faixas de valores numéricos.

3. **Eliminar código morto** - Revisar variáveis, funções e includes não utilizados. Atenção especial a código comentado ou condicionais que nunca são alcançadas.

4. **Extrair constantes nomeadas** - Substituir números mágicos (timers 15000, 8000, 5000, 2000, 120; tolerâncias, thresholds) por constantes nomeadas com `constexpr` ou `#define`.

### Fase C — Melhorias Estruturais

5. **Centralizar declarações `extern`** - Criar `globals.h` unificado com todas as declarações `extern`, eliminando a duplicação atual em 4+ arquivos.

6. **Melhorar `output_manager.h`** - Enviar respostas simultaneamente para Serial e BLE quando ambos estiverem disponíveis, facilitando debug.

7. **Revisar `notificationWasDrawn`** - Garantir que o reset da flag seja confiável em todos os cenários de transição de tela.

### Fase D — Otimizações de Loop

8. **Substituir `delay(120)` das animações de blink por FSM baseada em millis()** - Classificado como prejudicial na auditoria de delays. O comportamento visual deve permanecer **absolutamente idêntico**: olhos fechados por exatos 120ms, intervalo aleatório entre 2000-5000ms. Esta atividade ocorre apenas após a estabilização das fases anteriores.

9. **Auditoria de String** - Medir consumo de heap e fragmentação em hot paths do parsing de comandos (especialmente `parseSpotifyCommand` e `parseNotificationCommand`). Converter para buffers fixos apenas onde houver ganho mensurável de estabilidade ou consumo de memória.

### O Que Não Fazer Agora

- **Não migrar para .cpp/.h** - Característica arquitetural funcional. Sem evidência de problema concreto.
- **Não remover ANCS** - Módulo reservado para implementação futura. Placeholder intencional.
- **Não adicionar BLE security** - Altera comportamento funcional.
- **Não alterar protocolo** - Permanece como está (ADR-003).
- **Não adicionar watchdog** - Requer investigação prévia sobre mecanismos existentes no Arduino Core ESP32.
- **Não adicionar FreeRTOS tasks** - Mudança arquitetural significativa.
- **Não modificar display FSM** - Funciona adequadamente.
- **Não alterar UX ou layout das telas** - Fora do escopo do HARNESS-001.

---

**Fim do documento 000_discovery.md**

Próximo passo: [HARNESS-001](../HARNESS/firmware/HARNESS-001.md)
