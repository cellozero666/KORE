SPEC-005 — Apple Notification Center Service (ANCS)

Objetivo:

Implementar suporte ao Apple Notification Center Service (ANCS), permitindo que o K.O.R.E. OS receba notificações de dispositivos iOS utilizando Bluetooth Low Energy.

A implementação deverá utilizar a arquitetura definida na SPEC-004, tratando o ANCS como mais uma origem de entrada do sistema.

Nenhuma regra de negócio deverá ser implementada diretamente no módulo ANCS.

Toda notificação deverá ser convertida para o protocolo textual do K.O.R.E. antes de chegar ao `command_parser`.

⸻

Objetivos

Permitir que o ESP32:

* conecte-se a um iPhone como ANCS Client
* descubra automaticamente os serviços necessários
* receba notificações do sistema
* obtenha os atributos das notificações
* converta essas informações para o protocolo K.O.R.E.
* encaminhe os comandos ao Input Adapter

O restante do firmware não deverá conhecer detalhes do ANCS.

⸻

Arquitetura

Fluxo esperado:

            iPhone
        (ANCS Server)
               │
               ▼
        BLE Central Client
               │
               ▼
          ANCS Module
               │
               ▼
         Input Adapter
               │
               ▼
    Protocolo K.O.R.E.
               │
               ▼
      command_parser.cpp
               │
               ▼
    Managers / Controllers / UI

O módulo ANCS deverá possuir responsabilidade exclusivamente sobre a comunicação com o serviço da Apple.

Toda lógica de negócio permanecerá fora deste módulo.

⸻

Descoberta de Serviços

A implementação deverá localizar automaticamente:

* ANCS Service
* Notification Source
* Control Point
* Data Source

A conexão deverá falhar de forma controlada caso algum serviço obrigatório não esteja disponível.

⸻

Recebimento de Notificações

Sempre que uma nova notificação for recebida, o firmware deverá:

* identificar o Notification UID
* solicitar seus atributos através do Control Point
* aguardar a resposta do Data Source
* montar uma estrutura completa da notificação

Apenas após possuir todas as informações necessárias a notificação deverá ser encaminhada ao Input Adapter.

⸻

Atributos

Sempre que disponíveis, deverão ser obtidos:

* Nome do aplicativo
* Título
* Subtítulo
* Mensagem
* Data
* Categoria

Caso algum atributo não exista, a implementação deverá continuar normalmente.

⸻

Conversão para o protocolo K.O.R.E.

Toda notificação deverá ser convertida para o protocolo textual já utilizado pelo firmware.

Formato:

```
notification|APP|SENDER|CONTENT
```

Onde:

APP

Nome do aplicativo.

SENDER

Pessoa, contato ou origem da notificação.

CONTENT

Texto principal da mensagem.

Caso alguma informação não exista, utilizar campo vazio.

Exemplo:

```
notification|WhatsApp|João|Cheguei em casa.
```

Nenhum manager deverá conhecer estruturas específicas do ANCS.

⸻

Categorias

A implementação deverá reconhecer, quando possível:

* Incoming Call
* Missed Call
* Message
* Social
* Email
* Calendar
* Reminder
* News
* Health
* Finance
* Other

Categorias desconhecidas deverão continuar sendo processadas normalmente.

⸻

Estados

Gerenciar corretamente:

* desconectado
* conectando
* descobrindo serviços
* aguardando notificações
* sincronizado
* erro

Mudanças de estado deverão permitir recuperação automática.

⸻

Reconexão

A implementação deverá prever:

* perda de conexão BLE
* perda do serviço ANCS
* reconexão automática
* nova descoberta de serviços
* retomada do recebimento de notificações

Sem necessidade de reinicializar o firmware.

⸻

Robustez

A implementação deverá tratar:

* notificações incompletas
* atributos ausentes
* mensagens muito longas
* timeouts
* erros de comunicação
* perda de pacotes
* múltiplas notificações em sequência

Nenhum erro poderá comprometer o restante do firmware.

⸻

Escopo

Esta SPEC contempla:

* implementação do cliente ANCS
* descoberta de serviços
* leitura de atributos
* tradução para o protocolo K.O.R.E.
* integração com o Input Adapter

Esta SPEC não contempla:

* respostas para notificações
* ações rápidas
* leitura de histórico
* envio de comandos ao iPhone
* integração com Siri
* funcionalidades fora do ANCS

⸻

Critérios de aceite

A implementação será considerada concluída quando:

* o ESP32 conectar corretamente a um iPhone compatível
* os serviços ANCS forem descobertos automaticamente
* novas notificações forem recebidas
* seus atributos forem recuperados corretamente
* todas as notificações forem convertidas para o protocolo textual do K.O.R.E.
* todas as notificações chegarem ao `command_parser` através do Input Adapter
* nenhuma regra de negócio for implementada dentro do módulo ANCS
* a perda de conexão puder ser recuperada automaticamente sem reinicialização do firmware