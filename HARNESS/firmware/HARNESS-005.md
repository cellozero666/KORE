# HARNESS-005 — Apple Notification Center Service (ANCS)

## Objetivo

Implementar suporte ao Apple Notification Center Service (ANCS), permitindo que o K.O.R.E. OS receba notificações de dispositivos iOS utilizando Bluetooth Low Energy.

Esta implementação deverá utilizar obrigatoriamente a arquitetura criada na **HARNESS-004 (Input Adapter)**.

Nenhuma regra de negócio poderá ser implementada dentro do módulo ANCS.

Toda notificação deverá ser convertida para o protocolo textual do K.O.R.E. antes de chegar ao `command_parser`.

---

## Escopo

Implementar:

- cliente ANCS
- descoberta automática dos serviços ANCS
- recebimento de notificações
- leitura dos atributos da notificação
- conversão para o protocolo K.O.R.E.
- integração com o Input Adapter

Não implementar:

- respostas para notificações
- ações rápidas
- Siri
- leitura de histórico
- qualquer funcionalidade fora do ANCS

---

## Arquitetura esperada

Toda notificação deverá seguir obrigatoriamente o fluxo abaixo.

```
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
```

O módulo ANCS não poderá acessar diretamente nenhum manager, controller ou screen.

---

## Descoberta de serviços

Durante a conexão deverão ser descobertos automaticamente:

- ANCS Service
- Notification Source
- Control Point
- Data Source

Caso algum serviço obrigatório não seja encontrado, a conexão deverá falhar de forma controlada.

---

## Recebimento de notificações

Sempre que uma nova notificação for recebida, o módulo deverá:

- identificar o Notification UID;
- solicitar seus atributos utilizando o Control Point;
- aguardar a resposta do Data Source;
- montar a estrutura completa da notificação;
- encaminhar o resultado ao Input Adapter.

Nenhuma regra de negócio poderá ser executada neste processo.

---

## Conversão

Toda notificação deverá ser convertida para o protocolo textual já utilizado pelo firmware.

Formato:

```
notification|APP|SENDER|CONTENT
```

Exemplo:

```
notification|WhatsApp|João|Cheguei em casa.
```

Caso algum campo não exista, utilizar campo vazio.

O parser continuará sendo o único responsável pela interpretação do comando.

---

## Categorias

Sempre que possível reconhecer:

- Incoming Call
- Missed Call
- Message
- Social
- Email
- Calendar
- Reminder
- News
- Health
- Finance
- Other

Categorias desconhecidas não deverão interromper o processamento.

---

## Estados

Implementar gerenciamento dos estados:

- desconectado
- conectando
- descobrindo serviços
- aguardando notificações
- sincronizado
- erro

Mudanças de estado deverão permitir recuperação automática.

---

## Reconexão

A implementação deverá prever:

- perda da conexão BLE;
- perda do serviço ANCS;
- reconexão automática;
- nova descoberta dos serviços;
- retomada automática do recebimento de notificações.

Nenhuma dessas situações deverá exigir reinicialização do firmware.

---

## Robustez

A implementação deverá tratar corretamente:

- notificações incompletas;
- atributos ausentes;
- mensagens muito longas;
- timeouts;
- erros de comunicação;
- perda de pacotes;
- múltiplas notificações recebidas em sequência.

Nenhuma dessas situações poderá comprometer o restante do firmware.

---

## Restrições

É proibido:

- implementar lógica de negócio dentro do módulo ANCS;
- acessar managers diretamente;
- modificar o protocolo textual do K.O.R.E.;
- alterar o comportamento do `command_parser`;
- adicionar funcionalidades fora do escopo desta HARNESS.

---

## Validação

Ao final da implementação validar:

- descoberta automática dos serviços ANCS;
- conexão com iPhone compatível;
- recebimento de novas notificações;
- leitura correta dos atributos;
- conversão para o protocolo K.O.R.E.;
- passagem obrigatória pelo Input Adapter;
- processamento correto pelo `command_parser`;
- funcionamento contínuo após perda e recuperação da conexão.

---

## Entrega

Ao concluir a implementação apresentar:

- resumo da arquitetura implementada;
- arquivos criados;
- arquivos modificados;
- fluxo completo da comunicação ANCS;
- justificativa das decisões técnicas;
- evidências da integração com o Input Adapter;
- resultados das validações realizadas.