# 001_foundation.md

# Foundation

## Objetivo

Criar a estrutura base do Companion para iOS, estabelecendo a arquitetura inicial sobre a qual todos os demais módulos serão desenvolvidos.

---

## Diretório de Trabalho

```
ROOT/COMPANION/ios/APP
```

Todo o desenvolvimento deste módulo deverá ocorrer exclusivamente neste diretório.

---

## Dependências

Já estão instalados e configurados:

- Node.js LTS
- React
- TypeScript
- Tauri
- Rust
- Cargo
- Vite
- Xcode
- iOS SDK

Belthazar deverá instalar e configurar todas as dependências necessárias para que o projeto compile e execute corretamente no simulador e em dispositivos físicos.


### Backend (Cargo.toml)

```toml
tauri = { version = "2", features = [] }
tauri-plugin-opener = "2"
dotenvy = "0.15"
urlencoding = "2.1"
reqwest = { version = "0.12", features = ["json"] }
serde = { version = "1", features = ["derive"] }
serde_json = "1"
```

Belthazar deverá instalar e configurar todas as dependências necessárias para que o projeto compile e execute corretamente no simulador e em dispositivos físicos.

---

## Escopo

- Validar o projeto React + Tauri Mobile.
- Configurar TypeScript.
- Configurar Vite.
- Configurar Tauri.
- Configurar o ambiente iOS.
- Garantir comunicação entre React e Tauri.
- Garantir execução no simulador iOS.
- Garantir execução em dispositivo físico.
- Organizar a estrutura inicial de diretórios.
- Reutilizar o máximo possível de código existente do Companion macOS localizado em `ROOT/COMPANION/macos/APP`, preservando a arquitetura e adaptando apenas o que for necessário para compatibilidade com iOS.

---

## Não faz parte

- Interface gráfica.
- Navegação.
- Comunicação com o firmware.
- Componentes React.
- Funcionalidades do Companion.
- BLE.
- ANCS.

---

## Dependências da Documentação

- PROJECT.md
- AGENTS.md

---

## Critérios de Aceitação

- Projeto criado em `ROOT/COMPANION/ios/APP`.
- Dependências instaladas.
- Projeto executa corretamente em modo desenvolvimento.
- Hot Reload funcionando.
- Projeto executa corretamente no simulador iOS.
- Projeto executa corretamente em dispositivo físico.
- Build de produção executa sem erros.
- Estrutura pronta para os próximos módulos.