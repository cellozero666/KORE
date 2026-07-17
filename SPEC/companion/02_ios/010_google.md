# 010_google.md

# Google

## Objetivo

Implementar a integração com as APIs do Google, permitindo autenticação do usuário, monitoramento contínuo do Gmail e Google Calendar e envio de notificações para o K.O.R.E. OS.

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

## Configuração

As credenciais da API do Google deverão ser armazenadas no mesmo arquivo utilizado pelo Spotify:

```
/src-tauri/config/config.rs
```

O arquivo deverá conter:

```rust
pub const GOOGLE_CLIENT_ID: &str = "";
pub const GOOGLE_CLIENT_SECRET: &str = "";
pub const GOOGLE_REDIRECT_URI: &str = "";
```

O arquivo deverá estar presente no `.gitignore`.

Não utilizar `.env` ou arquivos de configuração externos.

Os dados das variáveis serão abastecidos pelo usuário no arquivo citado.

---

## Autenticação

A autenticação deverá utilizar o fluxo OAuth através de Authorization Code.

Todo o processo de autenticação deverá ser executado exclusivamente pelo Backend.

O Backend será responsável por:

- Login OAuth.
- Obtenção do Authorization Code.
- Troca do Authorization Code pelos Tokens.
- Armazenamento do Refresh Token.
- Renovação automática da sessão.

O React nunca deverá acessar diretamente as APIs do Google.

---

## Arquitetura

Toda a integração com o Google é responsabilidade da camada nativa da aplicação.

A implementação deverá utilizar:

- Tauri
- Rust
- Swift (quando necessário)

Fluxo:

```text
Google APIs
        ↓
Backend (Rust/Tauri)
        ↓
State Global
        ↓
React
```

O Backend é responsável por:

- Login OAuth.
- Refresh Token.
- Monitoramento do Gmail.
- Monitoramento do Google Calendar.
- Atualização do State Global.
- Envio das notificações para a ESP32.

O React é responsável apenas por:

- Exibir os dados.
- Solicitar conexão/desconexão.
- Atualizar a interface através do State Global.

---

## Watchers

O Backend deverá manter watchers permanentes para:

- Gmail.
- Google Calendar.

Os watchers deverão consultar as APIs do Google a cada 3 minutos.

Sempre que forem encontrados novos eventos desde a última consulta, estes deverão ser convertidos para o protocolo de notificações do K.O.R.E. e enviados imediatamente para a ESP32.

---

## Gmail

Cada novo e-mail deverá gerar:

```
notification|mail|SENDER|CONTENT
```

Onde:

- SENDER → Remetente do e-mail.
- CONTENT → Assunto do e-mail.

---

## Google Calendar

Cada novo evento ou lembrete deverá gerar:

```
notification|calendar|SENDER|CONTENT
```

Onde:

- SENDER → Organizador ou nome da agenda, quando disponível.
- CONTENT → Título do evento.

---

## Interface

A tela deverá exibir:

### Conta

- Ícone do Google.
- Estado da conexão.
- Foto do perfil.
- Nome do usuário.

O ícone deverá permitir:

- Conectar.
- Desconectar.

Estados:

- Verde → conectado.
- Vermelho → desconectado.

---

## Escopo

- Implementar autenticação OAuth do Google.
- Implementar gerenciamento de sessão utilizando Refresh Token.
- Implementar watcher do Gmail.
- Implementar watcher do Google Calendar.
- Implementar envio de notificações para a ESP32.
- Implementar atualização do State Global.
- Implementar interface do módulo Google.
- Reutilizar o máximo possível de código existente do Companion macOS localizado em `ROOT/COMPANION/macos/APP`, preservando a arquitetura e adaptando apenas o que for necessário para compatibilidade com iOS.

---

## Não faz parte

- Leitura completa de e-mails.
- Envio de e-mails.
- Criação de eventos.
- Edição de eventos.
- Exclusão de eventos.
- Google Drive.
- Google Contacts.
- Google Tasks.
- Google Meet.

---

## Critérios de Aceitação

- O usuário consegue conectar à conta Google.
- A sessão permanece autenticada utilizando Refresh Token.
- O React nunca acessa diretamente as APIs do Google.
- O Backend mantém o State Global atualizado.
- O React atualiza automaticamente a interface através do State Global.
- Os watchers consultam as APIs do Google a cada 3 minutos.
- Novos e-mails geram notificações no formato `notification|mail|SENDER|CONTENT`.
- Novos eventos do Google Calendar geram notificações no formato `notification|calendar|SENDER|CONTENT`.
- As notificações são enviadas para a ESP32 através da interface pública definida em `006_connection.md`.
- O módulo permanece desacoplado da interface e da camada de comunicação definida em `006_connection.md`.