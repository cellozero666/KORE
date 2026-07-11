001_foundation.md

Foundation

Objetivo

Criar a estrutura base do Companion para macOS, estabelecendo a arquitetura inicial sobre a qual todos os demais módulos serão desenvolvidos.

⸻

Diretório de Trabalho

ROOT/COMPANION/macos

Todo o desenvolvimento deste módulo deverá ocorrer exclusivamente neste diretório.

⸻

Dependências

Instalar e configurar:

* Node.js LTS
* React
* TypeScript
* Tauri
* Rust
* Cargo
* Vite

Instalar todas as dependências necessárias para execução e desenvolvimento do projeto.

Backend (Cargo.toml)

tauri = { version = "2", features = [] }
tauri-plugin-opener = "2"
tauri-plugin-deep-link = "2"
dotenvy = "0.15"
urlencoding = "2.1"
reqwest = { version = "0.12", features = ["json"] }
serde = { version = "1", features = ["derive"] }
serde_json = "1"
serialport = "4.7"
tiny_http = "0.12"

Belthazar deverá instalar e configurar todas as dependências necessárias para que o projeto compile e execute corretamente.

⸻

Escopo

* Criar o projeto React + Tauri.
* Configurar TypeScript.
* Configurar Vite.
* Configurar Tauri.
* Garantir comunicação entre React e Tauri.
* Organizar a estrutura inicial de diretórios.

⸻

Não faz parte

* Interface gráfica.
* Navegação.
* Comunicação com o firmware.
* Componentes React.
* Funcionalidades do Companion.

⸻

Dependências da Documentação

* PROJECT.md
* AGENTS.md

⸻

Critérios de Aceitação

* Projeto criado em ROOT/COMPANION/macos.
* Dependências instaladas.
* Projeto executa corretamente em modo desenvolvimento.
* Build de produção executa sem erros.
* Estrutura pronta para os próximos módulos.