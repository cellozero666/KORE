# HARNESS-004 — Input Adapter

## Objetivo

Implementar a arquitetura definida na **SPEC-004**, introduzindo uma camada de adaptação de entrada (Input Adapter) responsável por normalizar todas as origens de comunicação antes de encaminhá-las ao `command_parser`.

Esta implementação é exclusivamente arquitetural.

Nenhuma regra de negócio poderá ser alterada.

Nenhum comportamento funcional do firmware poderá mudar.

O protocolo textual do K.O.R.E. continuará sendo o único contrato interno da lógica de negócio.

---

## Escopo

Implementar:

- camada Input Adapter
- interface pública para entrada de comandos
- integração com o `command_parser`
- adaptação das entradas existentes

Não implementar:

- ANCS
- Android Companion
- novos comandos
- novos managers
- alterações no parser
- alterações no protocolo textual

---

## Arquitetura esperada

Toda entrada deverá obrigatoriamente seguir o fluxo abaixo.

```
            Serial
        BLE Companion
             ANCS
           Android
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

Não será permitido qualquer acesso direto ao `command_parser` por módulos externos.

---

## Implementação

Criar uma camada responsável por:

- receber comandos de qualquer origem;
- identificar sua origem;
- realizar adaptações quando necessário;
- encaminhar sempre comandos utilizando o protocolo textual existente;
- entregar os comandos exclusivamente ao `command_parser`.

A camada deverá ser transparente para o restante do firmware.

---

## Compatibilidade

A implementação deverá preservar integralmente o comportamento atual.

O Companion existente deverá continuar funcionando sem qualquer modificação.

Todos os comandos atualmente suportados deverão continuar produzindo exatamente os mesmos resultados.

Não será permitida quebra de compatibilidade.

---

## Critérios técnicos

Ao final da implementação deverá existir apenas um ponto de entrada para a lógica de negócio.

Todo comando deverá obrigatoriamente passar pelo Input Adapter antes de chegar ao parser.

O parser continuará responsável exclusivamente por interpretar comandos do protocolo K.O.R.E.

Nenhum manager deverá conhecer a origem da comunicação.

Nenhum manager deverá depender de Serial, BLE, ANCS ou Android.

---

## Estrutura

A organização dos arquivos poderá ser alterada caso necessário, desde que respeite a arquitetura definida na SPEC-004 e mantenha o código consistente com o restante do projeto.

---

## Restrições

É proibido:

- alterar regras de negócio;
- alterar o protocolo K.O.R.E.;
- alterar comandos existentes;
- modificar comportamento dos managers;
- modificar telas;
- adicionar funcionalidades fora do escopo desta HARNESS.

---

## Validação

Ao final da implementação validar:

- comunicação via Serial;
- comunicação via BLE Companion;
- funcionamento de todos os comandos existentes;
- compatibilidade total com o Companion atual;
- inexistência de regressões funcionais.

---

## Entrega

Ao concluir a implementação apresentar:

- resumo da arquitetura adotada;
- arquivos criados;
- arquivos modificados;
- justificativa das decisões arquiteturais;
- evidências da manutenção da compatibilidade;
- resultados das validações realizadas.