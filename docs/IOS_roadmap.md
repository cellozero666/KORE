# iOS Roadmap — K.O.R.E. Companion

## 1. Estado Atual do Projeto

### HARNESS Concluídos

| HARNESS | Status | Descrição |
|---|---|---|
| HARNESS-001 | ✅ | Scaffold do projeto iOS (Tauri + React + TypeScript) |
| HARNESS-002 | ✅ | Configuração de janela (window config) |
| HARNESS-003 | ✅ | Layout base (LoadingScreen, Sidebar, Content area) |
| HARNESS-004 | ✅ | Navegação (HashRouter, Sidebar items, roteamento) |
| HARNESS-005 | ✅ | State management (Context + useReducer, 6 stores) |
| HARNESS-006 | ✅ | Conexão BLE (btleplug, unificado macOS/iOS, `build.rs` com CoreBluetooth) |
| HARNESS-007 | ✅ | Dashboard (reuso completo do código macOS) |

### Shared HARNESS Concluídos (Infraestrutura Firmware)

| HARNESS | Status | Descrição |
|---|---|---|
| SHARED-001 | ✅ | Secure BLE Pairing / Bonding / Reconexão |
| SHARED-002 | ✅ | ANCS — Notification Source, Control Point, Data Source, Input Adapter, Normalização, Notification Manager (Firmware) |

### HARNESS Pendentes

| HARNESS | Prioridade | SPEC |
|---|---|---|
| ~~HARNESS-008~~ | ~~Alta~~ | ~~`008_notifications.md`~~ — **OBSOLETO** (ver seção 7) |
| HARNESS-009 | Alta | `009_spotify.md` |
| HARNESS-010 | Alta | `010_google.md` |
| HARNESS-011 | Média | `011_weather.md` |
| HARNESS-012 | Média | `012_settings.md` |

### Funcionalidades Implementadas

- Conexão BLE com o K.O.R.E. OS (btleplug + CoreBluetooth)
- Handshake (`ping` → `KORE_COMPANION`)
- Loading screen com indicadores de etapa e diagnóstico após 15s
- Dashboard completo:
  - Indicador de conexão (verde/vermelho)
  - Versão do firmware (comando `version`)
  - Uptime do dispositivo (comando `uptime`)
  - Status Wi-Fi e IP (comando `wifi_status`)
  - Placeholders Spotify e Google (preparados para integração futura)
  - Command Test (envio de comandos arbitrários para a ESP32)
- 6 stores de estado (App, Dashboard, Spotify, Google, Weather, Settings)
- Sidebar com navegação entre páginas
- HashRouter com 5 rotas
- Instrumentação de diagnóstico para depuração da conexão BLE

### Infraestrutura Compartilhada (Firmware — Validada em Hardware)

- Secure BLE Pairing
- Secure BLE Bonding
- Reconexão automática
- ANCS Discovery
- Notification Source (ANCS)
- Control Point (ANCS)
- Data Source (ANCS)
- Input Adapter (normalização de eventos)
- Normalização de aplicativos (Bundle ID → nome canônico + ícone)
- Notification Manager (fila + exibição no display)

### Funcionalidades Ainda Não Implementadas

- Integração Spotify
- Integração Google
- Integração Weather
- Tela de Configurações
- Persistência de estado

### Arquitetura Atual do Companion

```
React (TypeScript)
    │
    ├── state/          ← Context + useReducer (6 stores)
    │   ├── AppStore.tsx
    │   ├── DashboardStore.tsx
    │   ├── SpotifyStore.tsx
    │   ├── GoogleStore.tsx
    │   ├── WeatherStore.tsx
    │   ├── SettingsStore.tsx
    │   └── StoreProvider.tsx
    │
    ├── hooks/          ← Hooks de conexão e dados
    │   ├── useConnection.ts
    │   └── useDashboard.ts
    │
    ├── services/       ← Interface pública com o backend Tauri
    │   └── protocol.ts
    │
    ├── components/
    │   ├── common/     ← LoadingScreen, KoreIcon
    │   └── layout/     ← App, Sidebar, sidebarItems
    │
    ├── pages/          ← 5 páginas (Dashboard, Spotify, Google, Weather, Settings)
    │
    └── assets/css/     ← tokens.css, App.css, Sidebar.css, LoadingScreen.css, Dashboard.css
            │
            ▼
    Tauri Commands (Rust)
            │
    ┌───────┴───────┐
    │               │
    commands/       events/
    connection.rs   connection.rs
            │
    communication/  ← Camada de comunicação com hardware
    │   ├── manager.rs     ← Gerenciador de transporte
    │   ├── ble.rs         ← Transporte BLE (btleplug)
    │   ├── handshake.rs   ← Handshake ping/KORE_COMPANION
    │   ├── protocol.rs    ← Formatação de comandos
    │   ├── serial.rs      ← Transporte Serial (placeholder)
    │   └── types.rs       ← Tipos de transporte
    │
    state/          ← Estado interno do backend
    │   └── connection.rs
    │
    models/
        └── connection.rs  ← Modelos ConnectionState, ConnectionStatus
```

### Principais Arquivos Criados (Frontend)

| Arquivo | Descrição |
|---|---|
| `src/main.tsx` | Entry point React |
| `src/components/layout/App.tsx` | Componente raiz com roteamento e loading |
| `src/components/layout/Sidebar.tsx` | Sidebar de navegação |
| `src/components/layout/sidebarItems.ts` | Itens da sidebar |
| `src/components/common/LoadingScreen.tsx` | Tela de loading com diagnóstico |
| `src/components/common/KoreIcon.tsx` | Ícone SVG do K.O.R.E. |
| `src/pages/Dashboard.tsx` | Dashboard |
| `src/pages/Spotify.tsx` | Placeholder Spotify |
| `src/pages/Google.tsx` | Placeholder Google |
| `src/pages/Weather.tsx` | Placeholder Weather |
| `src/pages/Settings.tsx` | Placeholder Settings |
| `src/hooks/useConnection.ts` | Hook de conexão (eventos + diagnóstico) |
| `src/hooks/useDashboard.ts` | Hook de dados do Dashboard |
| `src/services/protocol.ts` | Interface de comunicação via Tauri |
| `src/state/AppStore.tsx` | Estado global (connected, loading, error) |
| `src/state/DashboardStore.tsx` | Estado do Dashboard |
| `src/state/SpotifyStore.tsx` | Estado do Spotify |
| `src/state/GoogleStore.tsx` | Estado do Google |
| `src/state/WeatherStore.tsx` | Estado do Weather |
| `src/state/SettingsStore.tsx` | Estado das Configurações |
| `src/state/StoreProvider.tsx` | Composição dos providers |
| `src/state/index.ts` | Barrel exports |
| `src/assets/css/tokens.css` | Design tokens (cores, espaçamentos, tipografia) |
| `src/assets/css/App.css` | Estilos globais |
| `src/assets/css/Sidebar.css` | Estilos da sidebar |
| `src/assets/css/LoadingScreen.css` | Estilos da tela de loading |
| `src/assets/css/Dashboard.css` | Estilos do Dashboard |

### Principais Arquivos Criados (Backend Rust)

| Arquivo | Descrição |
|---|---|
| `src-tauri/src/lib.rs` | Registro de módulos, plugins e comandos |
| `src-tauri/src/main.rs` | Bootstrap |
| `src-tauri/src/commands/connection.rs` | 4 comandos Tauri (connect, disconnect, send_command, get_connection_status) |
| `src-tauri/src/communication/manager.rs` | Gerenciador de transporte (BLE + Serial) |
| `src-tauri/src/communication/ble.rs` | Transporte BLE completo (scan, connect, handshake, subscribe, send/receive) |
| `src-tauri/src/communication/handshake.rs` | Handshake ping/KORE_COMPANION |
| `src-tauri/src/communication/protocol.rs` | Formatação de comandos do protocolo |
| `src-tauri/src/communication/types.rs` | Enum TransportType |
| `src-tauri/src/communication/serial.rs` | Transporte Serial (placeholder) |
| `src-tauri/src/state/connection.rs` | AppState com gerenciamento de conexão |
| `src-tauri/src/models/connection.rs` | ConnectionState, ConnectionStatus |
| `src-tauri/src/events/connection.rs` | Emissão de eventos de conexão |
| `src-tauri/src/build.rs` | Link de CoreBluetooth.framework para iOS |

### Módulos Existentes

| Módulo | Frontend | Backend Rust | Status |
|---|---|---|---|
| Connection | `useConnection`, `AppStore` | `commands/connection.rs`, `communication/*`, `state/connection.rs`, `events/connection.rs` | ✅ Completo |
| Dashboard | `Dashboard.tsx`, `useDashboard`, `DashboardStore`, `protocol.ts` | `send_command` (reuso) | ✅ Completo |
| Spotify | `Spotify.tsx`, `SpotifyStore` | — | ⏳ Placeholder |
| Google | `Google.tsx`, `GoogleStore` | — | ⏳ Placeholder |
| Weather | `Weather.tsx`, `WeatherStore` | — | ⏳ Placeholder |
| Settings | `Settings.tsx`, `SettingsStore` | — | ⏳ Placeholder |

---

## 2. BLE — Evolução e Estado Atual

### Problema Inicial

O Companion iOS compilava e instalava no dispositivo, mas ficava preso na tela de Loading indefinidamente. A instrumentação de diagnóstico (adicionada no HARNESS-006) revelou que o fluxo parava em:

```
Current State: Querying BLE adapters
```

A chamada `manager.adapters().await` nunca retornava.

### Investigação Realizada

1. **Instrumentação do backend**: Adicionados logs granulares em cada etapa da conexão BLE (`ble.rs`), incluindo timeout de 10s em `manager.adapters()`.

2. **Análise do btleplug v0.11.8 (iOS/CoreBluetooth)**:
   - `Manager::new()` é um `no-op` — retorna imediatamente.
   - `manager.adapters()` chama `Adapter::new()`, que:
     1. Cria um canal `mpsc` e spawna uma thread dedicada via `run_corebluetooth_thread()`.
     2. Dentro da thread, cria um runtime Tokio single-threaded e instancia `CoreBluetoothInternal`.
     3. `CoreBluetoothInternal::new()` cria um `CBCentralManager` com `initWithDelegate:queue:`, apontando para uma GCD queue serial.
     4. O **delegate callback** `centralManagerDidUpdateState:` deveria ser chamado assincronamente pelo CoreBluetooth na GCD queue.
     5. `Adapter::new()` então **bloqueia** (`receiver.next().await`) aguardando o evento `CoreBluetoothEvent::DidUpdateState`.
   - **Não há timeout** — se `centralManagerDidUpdateState:` nunca for chamado, o future nunca resolve.

3. **Causa raiz identificada**: O Info.plist do iOS **não continha** as chaves `NSBluetoothPeripheralUsageDescription` e `NSBluetoothAlwaysUsageDescription`. Sem essas chaves:
   - O iOS não exibe o prompt de permissão Bluetooth.
   - A autorização fica como `NotDetermined`.
   - O `CBCentralManager` nunca completa sua inicialização.
   - O delegate `centralManagerDidUpdateState:` nunca é chamado.
   - btleplug fica bloqueado para sempre.

4. **Confirmação**: O crash log do macOS (arquivo `docs/ERROR_COMPANION.MD`) confirma exatamente o mesmo problema:
   ```
   Termination Reason: Namespace TCC, Code 0
   This app has crashed because it attempted to access privacy-sensitive data
   without a usage description. The app's Info.plist must contain an
   NSBluetoothAlwaysUsageDescription key
   ```

### Solução Aplicada

1. **Info.plist** (`src-tauri/gen/apple/kore-companion_iOS/Info.plist`): Adicionadas as chaves:
   - `NSBluetoothPeripheralUsageDescription`: *"K.O.R.E. Companion uses Bluetooth to communicate with your K.O.R.E. device."*
   - `NSBluetoothAlwaysUsageDescription`: *"K.O.R.E. Companion uses Bluetooth to communicate with your K.O.R.E. device."*

2. **project.yml** (`src-tauri/gen/apple/project.yml`): Adicionadas as mesmas chaves na seção `info.properties` para persistência durante regeneração do projeto Xcode.

3. **Timeout de segurança** (`ble.rs`): Adicionado `tokio::time::timeout(Duration::from_secs(10), manager.adapters())` com mensagem de diagnóstico clara sobre a causa e solução.

4. **Instrumentação granular** (`ble.rs`): Logs em cada sub-etapa:
   - `Step 1.0`: Enter `Manager::new()`
   - `Step 1.1`: `Manager::new()` completed
   - `Step 2.0`: About to call `manager.adapters()`
   - `Step 2.1`: `manager.adapters()` returned Ok
   - `Step 2.ERR`: Falha com elapsed time
   - `Step 2.TIMEOUT`: Timeout com diagnóstico

### Permissões Adicionadas ao Info.plist

```xml
<key>NSBluetoothPeripheralUsageDescription</key>
<string>K.O.R.E. Companion uses Bluetooth to communicate with your K.O.R.E. device.</string>
<key>NSBluetoothAlwaysUsageDescription</key>
<string>K.O.R.E. Companion uses Bluetooth to communicate with your K.O.R.E. device.</string>
```

### Funcionamento Atual

O fluxo completo de conexão BLE é:

1. App inicia → LoadingScreen com diagnóstico
2. `Manager::new()` → retorna imediatamente (no-op)
3. `manager.adapters()` → timeout de 10s, internamente:
   - Verifica autorização Bluetooth (`CBManager.authorization`)
   - Cria thread dedicada com Tokio single-threaded
   - Cria `CBCentralManager` com delegate em GCD queue serial
   - Aguarda `centralManagerDidUpdateState:` (prompt de permissão é exibido ao usuário)
   - Retorna adaptadores disponíveis
4. Scan BLE por serviço `8c0f0001-5a8f-4e7e-9d43-92d67e4d0001` (timeout 10s)
5. Conecta ao primeiro dispositivo encontrado
6. Handshake: envia `ping`, espera `KORE_COMPANION`
7. Sincronização de clock
8. Subscribe a notificações na TX characteristic
9. Dashboard é exibido

### Limitações Conhecidas

- **Conexão bloqueante**: O Mutex no `CommunicationManager` impede polling de status durante a conexão — step events são o único mecanismo de diagnóstico.
- **Primeiro dispositivo**: A conexão seleciona o primeiro dispositivo BLE encontrado, sem filtro por nome ou ID.
- **Threading frágil**: btleplug depende de `futures::executor::block_on()` dentro do delegate `centralManagerDidUpdateState:`, criando dependência entre GCD e Tokio.
- **Sem reconexão automática no Companion**: Após desconexão, o usuário precisa reiniciar o app. A reconexão no firmware (ESP32) está implementada e validada.
- **Sem filtro de dispositivos**: Qualquer dispositivo com o serviço UUID é aceito.

### Confirmação de Funcionamento em Dispositivo Físico

O app compila e é instalado no dispositivo iOS via `tauri ios build --debug`. O **build é bem-sucedido** (assinado, `K.O.R.E. Companion.app` gerado). O funcionamento foi confirmado em dispositivo físico (BLE + Dashboard operacional).

---

## 3. Dashboard — Estado Atual

### Funcionalidades Implementadas

| Funcionalidade | Status | Detalhes |
|---|---|---|
| Tela inicial | ✅ | Rota padrão `path="/"` no HashRouter |
| Nome "K.O.R.E." | ✅ | Exibido no cabeçalho com `h1` |
| Indicador de conexão | ✅ | KoreIcon + label "Connected"/"Disconnected", verde/vermelho |
| Versão do firmware | ✅ | Comando `version` via `send_command` |
| Uptime | ✅ | Comando `uptime` via `send_command`, formatado (ex: "2 h 30 min") |
| Status Wi-Fi | ✅ | Comando `wifi_status` via `send_command` |
| Endereço IP | ✅ | Extraído do campo `ipAddress` do `wifi_status` |
| Placeholder Spotify | ✅ | Exibe "Connected"/"Disconnected" (preparado) |
| Placeholder Google | ✅ | Exibe "Connected"/"Disconnected" (preparado) |
| Command Test | ✅ | Input + Send, envia comandos arbitrários para a ESP32 |
| Desacoplado | ✅ | Consome apenas `send_command` (Tauri) e estados do módulo 006 |

### Comunicação com ESP32

A comunicação segue o fluxo:

```
Dashboard (React)
    │ sendRawCommand(cmd)
    ▼
useDashboard.ts
    │ sendCommand(cmd)
    ▼
protocol.ts
    │ invoke<string>("send_command", { command })
    ▼
Tauri IPC
    │
    ▼
commands/connection.rs::send_command()
    │ state.send_command(command)
    ▼
state/connection.rs::send_command()
    │ manager.send_command(&command)
    ▼
communication/manager.rs::send_command()
    │ ble.send(command)
    ▼
ble.rs::send() → write RX characteristic → wait notification TX characteristic
    │
    ▼
ESP32 (K.O.R.E. OS)
```

---

## 4. ANCS — Investigação e Implementação

### Conclusão da Investigação

**ANCS não pode ser consumido por um aplicativo rodando no próprio iPhone.**

- O **iPhone atua como ANCS Server** (Apple Notification Center Service).
- O **acessório BLE atua como ANCS Client** (o ESP32 no caso do K.O.R.E.).
- O Companion App (iOS) **não participa da entrega das notificações**.
- O Companion não pode se inscrever como cliente ANCS no próprio iPhone — isso viola a arquitetura do ANCS.

### Implementação Realizada

A implementação completa do ANCS ocorreu **exclusivamente no firmware do ESP32**, conforme documentado em:

- `/SPEC/shared/002_apple_notification_center_service.md`
- `/HARNESS/shared/HARNESS-002.md`

Funcionalidades validadas em hardware:

- Discovery do serviço ANCS
- Subscrição ao Notification Source
- Escrita no Control Point (GetNotificationAttributes)
- Recebimento no Data Source
- Parsing de atributos (AppID, Title, Message)
- Normalização de Bundle IDs
- Exibição no display via Notification Manager

### Impacto no Companion iOS

O Companion iOS **não foi afetado** por esta implementação. O fluxo de notificações é:

```
iPhone
  ↓ (ANCS nativo)
ESP32 (ANCS Client)
  ↓ (protocolo textual)
Input Adapter → Notification Manager → Display
```

O Companion iOS continua sendo apenas mais uma origem de dados que se comunica com o firmware via BLE usando o protocolo textual.

---

## 5. Motivo da Pausa (Resolvido)

### Melhoria Arquitetural Implementada

A melhoria arquitetural do firmware foi concluída. O Input Adapter foi implementado e validado, unificando o tratamento de todas as origens de dados (Serial, BLE Companion, ANCS) sob o mesmo protocolo textual K.O.R.E.

### Impacto no Companion iOS

O Companion iOS **não foi afetado** por essa mudança arquitetural. Ele continua se comunicando com o firmware através do mesmo protocolo textual via BLE (`send_command` → `serialização` → `escrita na RX characteristic`). A interface permanece idêntica.

---

## 6. Próximos Passos — Checklist para Retomada

### Fase 1: Firmware ✅ (Concluída)

- [x] Implementar a camada Input Adapter no firmware do ESP32
- [x] Criar adaptador para Serial
- [x] Criar adaptador para BLE Companion
- [x] Criar adaptador para ANCS
- [x] Validar que a compatibilidade com o protocolo atual foi preservada
- [x] Testar o firmware atualizado com o Companion (Serial e BLE)

### Fase 2: Integração ✅ (Concluída)

- [x] Integrar novamente o Companion ao firmware atualizado
- [x] Validar comunicação BLE completa (scan, connect, handshake, send, receive)
- [x] Revisar impactos da nova arquitetura no Companion
- [x] Atualizar documentação

### Fase 3: Retomada do iOS

- [x] Revisar o estado do código iOS (verificar se algo quebrou com as mudanças no firmware)
- [x] Executar `cargo check` e `npx tsc --noEmit` para validar compilação
- [x] Realizar deploy em dispositivo físico para validar BLE
- [ ] Retomar HARNESS pendentes na ordem:
  1. ~~HARNESS-008: Notificações~~ **OBSOLETO** — substituído por SHARED-002 (firmware)
  2. HARNESS-009: Spotify
  3. HARNESS-010: Google
  4. HARNESS-011: Weather
  5. HARNESS-012: Settings
- [ ] Continuar normalmente o desenvolvimento iOS seguindo SDD

---

## 7. HARNESS-008 — Descontinuado

### Motivo

O fluxo de notificações foi completamente movido para a infraestrutura Shared (firmware ESP32).

O Companion iOS não participa mais do processamento ou entrega das notificações. O fluxo oficial é:

```
iPhone → ANCS (nativo) → ESP32 → Input Adapter → Notification Manager → Display
```

### Documentos de Substituição

A responsabilidade do HARNESS-008 foi absorvida por:

| Documento | Caminho |
|---|---|
| SPEC | `/SPEC/shared/002_apple_notification_center_service.md` |
| HARNESS | `/HARNESS/shared/HARNESS-002.md` |

### Status dos Documentos Originais

| Documento | Status |
|---|---|
| `SPEC/companion/02_ios/008_notifications.md` | ⛔ Substituída — manter no projeto para referência histórica |
| `HARNESS/companion/ios/HARNESS-008.md` | ⛔ Obsoleto — manter no projeto para referência histórica |

---

*Documento gerado em 2026-07-18. Última atualização: 2026-07-20.*
*Último HARNESS concluído: HARNESS-007 (Dashboard) + SHARED-001 e SHARED-002 (Infraestrutura Firmware).*
*Motivo da pausa original (Input Adapter): Resolvido. Infraestrutura compartilhada validada em hardware.*
*HARNESS-008 descontinuado — responsabilidade absorvida pela arquitetura Shared (firmware).*
*Próximo HARNESS: HARNESS-009 (Spotify).*
