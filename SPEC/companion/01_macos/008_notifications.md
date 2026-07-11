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

Permissões

Ao iniciar o Companion, caso a permissão de Accessibility não tenha sido concedida, a aplicação deverá solicitá-la ao usuário.

Enquanto a permissão não for concedida, o watcher de notificações não deverá ser iniciado.

⸻

Watcher

O monitoramento deverá permanecer ativo durante toda a execução do Companion.

Toda nova notificação recebida pelo macOS deverá ser processada automaticamente.

Não deverá existir necessidade de intervenção do usuário.

⸻

Formato da Mensagem

Toda notificação deverá ser enviada para o firmware no formato:

notification|APP|SENDER|CONTENT

Exemplo:

notification|whatsapp|Jose|Festa na floresta

⸻

Aplicações Suportadas

Os seguintes identificadores deverão ser utilizados:

Aplicação	Valor enviado
WhatsApp	whatsapp
Calendar	calendar
Mail	mail
Email	mail
Messages	messages
Mensagens	messages
SMS	messages

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

Quando não existir remetente, enviar o contexto (como horario ou data, ou nome de aplicativo) ou titulo da notificação.
Caso não existir nenhum enviar uma string vazia.

⸻

CONTENT

Conteúdo textual da notificação.

Deve ser limitado a 30 caracteres, finalizar com ... quando ultrapassar 30 caracteres

Quando inexistente, enviar uma string vazia.

⸻

Usar exemplo
osascript -e 'display notification "Sua mensagem aqui" with title "Título da Notificação"'

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
* Toda notificação recebida pelo macOS é capturada.
* O aplicativo de origem é identificado corretamente.
* O remetente é identificado quando disponível.
* O conteúdo é identificado quando disponível.
* As notificações são convertidas para o formato notification|APP|SENDER|CONTENT.
* Aplicações não mapeadas são enviadas como settings.
* As notificações são enviadas para a ESP32 através da interface pública definida em 006_connection.md.
* O módulo permanece desacoplado da camada de comunicação.