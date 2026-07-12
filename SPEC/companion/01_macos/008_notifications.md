008_notifications.md

Notifications

Objetivo

Implementar o monitoramento contínuo das notificações do macOS, capturando eventos do sistema através da API de Accessibility e encaminhando-os ao K.O.R.E. OS.

⸻

Diretório de Trabalho

ROOT/COMPANION/macos

Todo o desenvolvimento deste módulo deverá ocorrer exclusivamente neste diretório.

⸻

Dependências

SPECs

* 001_foundation.md
* 002_window.md
* 003_layout.md
* 004_navigation.md
* 005_state.md
* 006_connection.md

⸻

Escopo

* Solicitar permissão de Accessibility ao usuário.
* Verificar se a permissão foi concedida.
* Implementar um watcher permanente de notificações.
* Capturar todas as notificações do macOS.
* Identificar o aplicativo de origem.
* Identificar o remetente (quando disponível).
* Identificar o conteúdo da notificação.
* Converter a notificação para o protocolo do K.O.R.E.
* Enviar a notificação para a ESP32 através da camada de comunicação.

⸻

## Decisão Arquitetural

O monitoramento de notificações do macOS utilizará obrigatoriamente a API de Accessibility.

Esta decisão foi validada na implementação legada do Companion e permanece como padrão oficial da arquitetura do K.O.R.E.

Belthazar não deverá substituir esta abordagem por outras APIs, frameworks ou mecanismos de captura sem autorização explícita.

⸻

Permissões

Ao iniciar o Companion, caso a permissão de Accessibility não tenha sido concedida, a aplicação deverá solicitá-la ao usuário.

Enquanto a permissão não for concedida, o watcher de notificações não deverá ser iniciado.

⸻

Watcher

O monitoramento deverá permanecer ativo durante toda a execução do Companion.

Toda nova notificação recebida pelo macOS deverá ser processada automaticamente.

Não deverá existir necessidade de intervenção do usuário.

O watcher deverá ser inicializado apenas uma única vez durante todo o ciclo de vida da aplicação.

⸻

Responsabilidades

A camada responsável pela captura das notificações deverá produzir um objeto estruturado contendo:

* app
* sender
* content

A conversão para o protocolo do K.O.R.E.

notification|APP|SENDER|CONTENT

é responsabilidade exclusiva da camada de comunicação.

A camada de captura nunca deverá montar manualmente mensagens do protocolo.

⸻

Formato da Mensagem

Toda notificação deverá ser enviada para o firmware no formato:

notification|APP|SENDER|CONTENT

Exemplo:

notification|whatsapp|Jose|Festa na floresta

⸻

Aplicações Suportadas

Aplicação Valor enviado

WhatsApp  whatsapp

Calendar  calendar

Mail  mail

Email mail

Messages  messages

Mensagens messages

SMS messages

Toda aplicação não identificada deverá ser enviada como:

settings

⸻

Campos

APP

Aplicação de origem da notificação.

Obrigatório.

⸻

SENDER

Nome do remetente.

Quando não existir remetente, utilizar a seguinte ordem:

1. Título da notificação.
2. Contexto disponível (horário, data ou nome do aplicativo).
3. String vazia.

⸻

CONTENT

Conteúdo textual da notificação.

Deve ser limitado a 30 caracteres.

Quando ultrapassar 30 caracteres deverá ser truncado e finalizado com:

...

Quando inexistente, enviar uma string vazia.

⸻

Usar exemplo

osascript -e 'display notification "Sua mensagem aqui" with title "Título da Notificação"'

⸻

Não faz parte

* Histórico de notificações.
* Persistência.
* Filtros.
* Configuração de aplicativos.
* Agrupamento de notificações.
* Resposta às notificações.
* Ações sobre notificações.

⸻

Critérios de Aceitação

* O Companion solicita permissão de Accessibility quando necessário.
* O watcher permanece ativo durante toda a execução da aplicação.
* O watcher é inicializado apenas uma única vez.
* Toda notificação recebida pelo macOS é capturada.
* O aplicativo de origem é identificado corretamente.
* O remetente é identificado quando disponível.
* O conteúdo é identificado quando disponível.
* As notificações são convertidas para o formato notification|APP|SENDER|CONTENT.
* Aplicações não mapeadas são enviadas como settings.
* As notificações são enviadas para a ESP32 através da interface pública definida em 006_connection.md.
* O módulo permanece desacoplado da camada de comunicação.
* O módulo é validado em macOS real utilizando:
  * osascript
  * WhatsApp
  * Messages
  * Mail
  * Calendar
  * pelo menos uma aplicação não mapeada.
* O HARNESS somente poderá ser considerado concluído após validação em hardware real, comprovando que a notificação foi capturada pelo macOS, convertida para o protocolo do K.O.R.E. e recebida corretamente pela ESP32.