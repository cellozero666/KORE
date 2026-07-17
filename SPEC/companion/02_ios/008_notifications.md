# 008_notifications.md

# Notifications

## Objetivo

Implementar o monitoramento contínuo das notificações do iOS utilizando o Apple Notification Center Service (ANCS), capturando eventos do sistema e encaminhando-os ao K.O.R.E. OS.

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

- Solicitar permissão para acesso às notificações quando necessário.
- Verificar se a permissão foi concedida.
- Implementar monitoramento contínuo utilizando o Apple Notification Center Service (ANCS).
- Capturar as notificações disponibilizadas pelo ANCS.
- Identificar o aplicativo de origem.
- Identificar o remetente (quando disponível).
- Identificar o conteúdo da notificação.
- Converter a notificação para o protocolo do K.O.R.E.
- Enviar a notificação para a ESP32 através da camada de comunicação.
- Reutilizar o máximo possível de código existente do Companion macOS localizado em `ROOT/COMPANION/macos/APP`, preservando a arquitetura e adaptando apenas o que for necessário para compatibilidade com iOS.

---

## Decisão Arquitetural

O monitoramento de notificações do iOS utilizará obrigatoriamente o Apple Notification Center Service (ANCS).

Esta decisão faz parte da arquitetura oficial do K.O.R.E.

Belthazar não deverá substituir esta abordagem por outras APIs, frameworks ou mecanismos de captura sem autorização explícita.

O firmware permanecerá utilizando exatamente o mesmo protocolo definido para o Companion macOS.

---

## Permissões

Ao iniciar o Companion, caso a permissão para notificações ainda não tenha sido concedida, a aplicação deverá solicitá-la ao usuário.

Enquanto a permissão não for concedida, o monitoramento de notificações não deverá ser iniciado.

---

## Watcher

O monitoramento deverá permanecer ativo durante toda a execução do Companion.

Toda nova notificação disponibilizada pelo ANCS deverá ser processada automaticamente.

Não deverá existir necessidade de intervenção do usuário.

O watcher deverá ser inicializado apenas uma única vez durante todo o ciclo de vida da aplicação.

---

## Responsabilidades

A camada responsável pela captura das notificações deverá produzir um objeto estruturado contendo:

- app
- sender
- content

A conversão para o protocolo do K.O.R.E.

```
notification|APP|SENDER|CONTENT
```

é responsabilidade exclusiva da camada de comunicação.

A camada de captura nunca deverá montar manualmente mensagens do protocolo.

---

## Formato da Mensagem

Toda notificação deverá ser enviada para o firmware no formato:

```
notification|APP|SENDER|CONTENT
```

Exemplo:

```
notification|whatsapp|Jose|Festa na floresta
```

---

## Aplicações Suportadas

| Aplicação | Valor enviado |
|-----------|---------------|
| WhatsApp | whatsapp |
| Calendar | calendar |
| Mail | mail |
| Email | mail |
| Messages | messages |
| Mensagens | messages |
| SMS | messages |

Toda aplicação não identificada deverá ser enviada como:

```
settings
```

---

## Campos

### APP

Aplicação de origem da notificação.

Obrigatório.

---

### SENDER

Nome do remetente.

Quando não existir remetente, utilizar a seguinte ordem:

1. Título da notificação.
2. Contexto disponível.
3. String vazia.

---

### CONTENT

Conteúdo textual da notificação.

Deve ser limitado a 30 caracteres.

Quando ultrapassar 30 caracteres deverá ser truncado e finalizado com:

```
...
```

Quando inexistente, enviar uma string vazia.

---

## Não faz parte

- Histórico de notificações.
- Persistência.
- Filtros.
- Configuração de aplicativos.
- Agrupamento de notificações.
- Resposta às notificações.
- Ações sobre notificações.

---

## Critérios de Aceitação

- O Companion solicita permissão para acesso às notificações quando necessário.
- O watcher permanece ativo durante toda a execução da aplicação.
- O watcher é inicializado apenas uma única vez.
- Toda notificação disponibilizada pelo ANCS é capturada.
- O aplicativo de origem é identificado corretamente.
- O remetente é identificado quando disponível.
- O conteúdo é identificado quando disponível.
- As notificações são convertidas para o formato `notification|APP|SENDER|CONTENT`.
- Aplicações não mapeadas são enviadas como `settings`.
- As notificações são enviadas para a ESP32 através da interface pública definida em `006_connection.md`.
- O módulo permanece desacoplado da camada de comunicação.
- O HARNESS somente poderá ser considerado concluído após validação em hardware real, comprovando que a notificação foi capturada pelo ANCS, convertida para o protocolo do K.O.R.E. e recebida corretamente pela ESP32.