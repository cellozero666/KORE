# SPEC-002 — Apple Notification Center Service (ANCS)

- **Projeto:** K.O.R.E.
- **Módulo:** Shared
- **Versão:** 1.0.0
- **Status:** Aprovada
- **Escopo:** Firmware ESP32 + Companion iOS
- **Dependências:**
  - SPEC-001 — Secure BLE Pairing & Bonding
  - /HARNESS/firmware/HARNESS-004 — Input Adapter

---

# 1. Objetivo

Definir como o Apple Notification Center Service (ANCS) será integrado ao ecossistema K.O.R.E., estabelecendo o ANCS como uma fonte de eventos para o Input Adapter já existente.

Esta especificação define exclusivamente a arquitetura de integração entre o protocolo ANCS e o firmware, garantindo que todo o restante do sistema permaneça desacoplado das tecnologias e APIs específicas da Apple.

---

# 2. Problema

Após o estabelecimento de uma conexão BLE segura, o firmware ainda não possui um mecanismo para receber notificações do sistema operacional iOS.

É necessário integrar o Apple Notification Center Service sem criar dependências entre o protocolo da Apple e a arquitetura interna do K.O.R.E.

---

# 3. Objetivos

Esta especificação deverá fornecer:

- Integração com o Apple Notification Center Service (ANCS);
- Recebimento de notificações provenientes do iPhone;
- Encaminhamento dos eventos ao Input Adapter;
- Isolamento completo entre o protocolo ANCS e o restante do firmware.

---

# 4. Não faz parte desta SPEC

Esta especificação não define:

- Pairing;
- Bonding;
- Segurança BLE;
- Funcionamento interno do Input Adapter;
- Interface gráfica;
- Renderização de notificações.

Esses componentes já existem ou são definidos em outras especificações.

---

# 5. Arquitetura

```
iPhone

↓

Apple Notification Center Service (ANCS)

↓

Biblioteca ANCS

↓

Input Adapter

↓

Sistema K.O.R.E.
```

O ANCS deverá ser tratado apenas como mais uma fonte de eventos do sistema.

Todo o restante da arquitetura permanecerá completamente desacoplado do protocolo da Apple.

---

# 6. Responsabilidades

## Biblioteca ANCS

Será responsável por:

- descobrir o serviço ANCS;
- estabelecer comunicação com o iPhone;
- receber eventos do ANCS;
- encaminhar os eventos ao Input Adapter.

Não deverá:

- conhecer regras de negócio;
- acessar diretamente componentes internos do firmware;
- modificar estados internos do sistema.

---

## Input Adapter

O Input Adapter será o único ponto autorizado a receber eventos provenientes do ANCS.

Seu funcionamento interno é definido pelo HARNESS-004 e não faz parte desta especificação.

---

# 7. Fluxo

```
Nova notificação

↓

iPhone

↓

Apple Notification Center Service

↓

Biblioteca ANCS

↓

Input Adapter

↓

Sistema K.O.R.E.
```

---

# 8. Regras Arquiteturais

Toda implementação específica do protocolo ANCS deverá permanecer completamente isolada.

Nenhum componente interno do firmware poderá depender diretamente:

- da biblioteca ANCS;
- do protocolo ANCS;
- de APIs específicas do iOS;
- de estruturas de dados fornecidas pela Apple.

O único ponto oficial de integração será o Input Adapter.

Após o Input Adapter, o restante do sistema não poderá distinguir se um evento foi originado pelo:

- Companion;
- ANCS;
- outra fonte suportada futuramente.

---

# 9. Tratamento de Eventos

O firmware deverá ser capaz de consumir todos os eventos disponibilizados pelo Apple Notification Center Service que sejam relevantes para o funcionamento do K.O.R.E.

Novos eventos poderão ser suportados futuramente sem necessidade de alterações na arquitetura definida nesta especificação.

---

# 10. Tratamento de Falhas

O firmware deverá continuar funcionando normalmente quando:

- o ANCS estiver indisponível;
- o usuário desabilitar o compartilhamento de notificações;
- o iPhone não suportar o serviço;
- ocorrer perda temporária da conexão.

A indisponibilidade do ANCS nunca deverá comprometer a comunicação BLE existente nem o funcionamento do restante do sistema.

---

# 11. Critérios de Aceitação

## AC-001

Após a conclusão do Pairing, o firmware identifica a disponibilidade do serviço ANCS.

---

## AC-002

O firmware recebe eventos provenientes do Apple Notification Center Service.

---

## AC-003

Todos os eventos recebidos são encaminhados exclusivamente ao Input Adapter.

---

## AC-004

Nenhum componente interno do firmware possui dependência direta da biblioteca ANCS ou de APIs específicas da Apple.

---

## AC-005

A substituição da biblioteca responsável pela implementação do ANCS não exige alterações na arquitetura do restante do firmware.

---

# 12. Observações

Esta especificação define apenas a arquitetura de integração entre o Apple Notification Center Service e o K.O.R.E.

A escolha da biblioteca, callbacks, APIs, descoberta de serviços, características BLE, gerenciamento de atributos, estrutura dos pacotes e demais detalhes de implementação deverão ser definidos durante a elaboração do HARNESS correspondente.