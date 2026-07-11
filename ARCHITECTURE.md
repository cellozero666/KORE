# ARCHITECTURE.md

# K.O.R.E. Architecture

## Objetivo

Definir a arquitetura oficial do projeto K.O.R.E., estabelecendo responsabilidades, organização dos componentes e fluxo de comunicação entre o Companion e o K.O.R.E. OS.

---

# Visão Geral

O projeto é composto por dois sistemas independentes.

```text
                K.O.R.E.
                   │
        ┌──────────┴──────────┐
        │                     │
   Companion App          K.O.R.E. OS
```

O Companion é responsável pela integração com o sistema operacional e serviços externos.

O K.O.R.E. OS é responsável pela interface física, sensores, display e experiência do dispositivo.

---

# Companion

O Companion possui arquitetura em camadas.

```text
React UI
    │
    ▼
State Global
    │
    ▼
Tauri Commands
    │
    ▼
Rust Backend
    │
    ▼
Swift (quando necessário)
```

## Responsabilidades

### React

- Interface gráfica.
- Navegação.
- Componentes.
- Consumo do State Global.

Nunca acessa:

- Hardware.
- BLE.
- Serial.
- APIs externas.
- Credenciais.

---

### State Global

Única fonte de verdade da aplicação.

Todos os módulos consomem este estado.

---

### Backend

Responsável por:

- Bluetooth Low Energy.
- Serial USB.
- Spotify.
- Google.
- Weather.
- Persistência.
- OAuth.
- Refresh Token.
- Comunicação com o firmware.

---

# K.O.R.E. OS

Responsável por:

- Display.
- Faces.
- Spotify Screen.
- Weather Screen.
- Notifications.
- Clock.
- Wi-Fi.
- Gerenciamento de Hardware.

O firmware nunca acessa serviços externos.

Toda informação chega através do Companion.

---

# Comunicação

Fluxo oficial.

```text
Spotify
Google
Weather
macOS
        │
        ▼
Backend
        │
        ▼
State Global
        │
        ▼
React
        │
        ▼
Serial / BLE
        │
        ▼
K.O.R.E. OS
```

---

# Protocolo

O protocolo oficial utiliza mensagens UTF-8 delimitadas por `|`.

Exemplos:

```text
ping

version

notification|APP|SENDER|CONTENT

spotify|TRACK|ARTIST|ALBUM|PROGRESS|DURATION

weather|CITY|TEMP|HITEMP|LOWTEMP|ICON
```

---

# Organização do Projeto

```text
COMPANION/
    android/
    ios/
    linux/
    macos/
    shared/
    windows/

KORE_OS/

LEGACY/
    COMPANION APP/
    KORE_OS/

SPEC/
ADR/
HARNESS/
```

---

# Fluxo de Desenvolvimento

Todo desenvolvimento segue obrigatoriamente:

```text
ADR
    │
    ▼
SPEC
    │
    ▼
Harness
    │
    ▼
Implementação
    │
    ▼
Testes
    │
    ▼
Validação
```

Nenhum módulo poderá avançar sem validação do usuário.

---

# Agentes

## Gaspar

- Arquitetura.
- SDD.
- ADRs.
- Revisões técnicas.

## Belthazar

- Implementação.
- Refatoração.
- Testes.
- Correções.

Ferramentas:

- OpenCode
- Laguna XS 2.1OpenRouter

## Melchior

- Interface.
- UX/UI.
- Componentização.

Ferramentas:

- Gemini CLI
- UI Pro Max

---

# Princípios

- Specification Driven Development.
- Arquitetura modular.
- Backend como única fonte de integração.
- React desacoplado da infraestrutura.
- Uma única fonte de verdade (State Global).
- Código limpo, funcional e escalável.
- Implementação incremental.
- Testes obrigatórios ao final de cada módulo.