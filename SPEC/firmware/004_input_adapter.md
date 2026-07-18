SPEC-004 — Input Adapter

Objetivo:

Implementar uma camada de adaptação de entrada (Input Adapter) responsável por normalizar todas as origens de dados antes de encaminhá-las ao `command_parser`.

Esta etapa é exclusivamente arquitetural.

Nenhuma regra de negócio deverá ser alterada.

Todo o comportamento atual do firmware deverá permanecer idêntico.

O objetivo é desacoplar o firmware das diferentes origens de comunicação e estabelecer o protocolo textual do K.O.R.E. como contrato único de entrada da lógica de negócio.

⸻

Objetivos

Criar uma camada responsável por:

* receber dados de qualquer origem
* identificar a origem da comunicação
* traduzir formatos externos quando necessário
* encaminhar sempre comandos utilizando o protocolo textual do K.O.R.E.
* entregar os comandos exclusivamente ao `command_parser`

O restante do firmware não deverá conhecer a origem dos dados.

⸻

Origens previstas

A arquitetura deverá suportar, no mínimo:

* Serial
* BLE Companion
* ANCS (iPhone)
* Companion Android

A implementação inicial deverá manter compatibilidade com as origens já existentes.

ANCS e Android poderão permanecer parcialmente implementados (placeholders), desde que a arquitetura esteja preparada.

⸻

Fluxo esperado

Toda entrada deverá seguir obrigatoriamente o fluxo abaixo:

                Serial
            BLE Companion
                 ANCS
               Android
                   │
                   ▼
            Input Adapter
                   │
                   ▼
       Protocolo K.O.R.E. (texto)
                   │
                   ▼
          command_parser.cpp
                   │
                   ▼
      Managers / Controllers / UI

Nenhuma origem deverá acessar diretamente managers, controllers ou screens.

⸻

Protocolo interno

O protocolo textual do K.O.R.E. passa a ser considerado o contrato interno de entrada do firmware.

Todos os comandos deverão chegar ao parser exatamente no formato já utilizado atualmente.

Exemplos:

```
notification|APP|SENDER|CONTENT
spotify|...
weather|...
version
uptime
happy
```

Nenhuma alteração deverá ser realizada no protocolo existente.

⸻

Compatibilidade

Esta implementação deverá preservar integralmente o comportamento atual.

O Companion existente deverá continuar funcionando sem qualquer alteração.

Todos os comandos atualmente suportados deverão continuar produzindo exatamente os mesmos resultados.

Não será permitida quebra de compatibilidade.

⸻

Escopo

Esta SPEC contempla apenas:

* criação da camada Input Adapter
* definição das responsabilidades
* integração com o `command_parser`
* adaptação da comunicação existente

Esta SPEC não contempla:

* implementação do ANCS
* implementação do Companion Android
* alteração dos managers
* alteração das telas
* alteração do protocolo K.O.R.E.

⸻

Critérios de aceite

A implementação será considerada concluída quando:

* existir apenas um ponto de entrada para a lógica de negócio (`command_parser`)
* toda origem de dados passar obrigatoriamente pelo Input Adapter
* o protocolo textual permanecer inalterado
* o Companion atual continuar funcionando sem modificações
* não houver alteração de comportamento funcional do firmware
* a arquitetura estiver preparada para receber novas origens de entrada sem necessidade de modificar o parser ou os managers