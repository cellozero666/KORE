# SPEC-001 — Secure BLE Pairing & Bonding

- **Projeto:** K.O.R.E.
- **Módulo:** Shared
- **Status:** Aprovada
- **Escopo:** Firmware ESP32 + Companion iOS
- **Dependências:**
  - Camada de comunicação BLE existente
  - Módulo de conexão BLE do Companion

---

# 1. Objetivo

Definir a arquitetura responsável pelo estabelecimento de uma conexão BLE segura entre o K.O.R.E. e um iPhone.

Esta SPEC define todo o fluxo de onboarding responsável por criar um vínculo permanente (Bond) entre os dispositivos, permitindo a utilização de recursos que exigem comunicação BLE criptografada, como o Apple Notification Center Service (ANCS).

Esta SPEC **não implementa o ANCS**.

Ela apenas fornece a infraestrutura necessária para que o ANCS e outros serviços seguros possam funcionar futuramente.

---

# 2. Problema

Atualmente o Companion consegue conectar ao ESP32 utilizando BLE e trocar comandos normalmente.

Entretanto, essa conexão não estabelece uma relação de confiança com o iPhone.

Sem Pairing e Bonding:

- o iPhone não considera o dispositivo confiável;
- não existe canal BLE criptografado;
- o ANCS não pode ser utilizado;
- futuros serviços BLE seguros também não poderão ser utilizados.

É necessário criar um fluxo de onboarding seguro para estabelecer essa relação de confiança.

---

# 3. Objetivos da SPEC

Esta especificação deverá fornecer:

- Pairing BLE seguro;
- Bonding persistente;
- Canal BLE criptografado;
- Fluxo de pareamento utilizando exclusivamente o diálogo nativo do iOS;
- Reconexão automática após o primeiro pareamento;
- Infraestrutura reutilizável para qualquer serviço BLE que exija segurança.

---

# 4. Não faz parte desta SPEC

Esta especificação **não define**:

- Apple Notification Center Service (ANCS);
- processamento de notificações;
- integração com o Input Adapter;
- parser de notificações;
- renderização no display;
- interface do usuário além do fluxo de onboarding.

Esses itens serão tratados em especificações futuras.

---

# 5. Arquitetura

O fluxo de conexão BLE do K.O.R.E. passa a possuir uma etapa obrigatória de estabelecimento de confiança.

```
          Companion

              │

      Procura dispositivo

              │

         Conecta BLE

              │

 Descobre característica protegida

              │

 Solicita operação protegida

              │

──────────────────────────────────

      Camada de Segurança iOS

              │

 Diálogo nativo de Pairing

              │

 Usuário aceita

              │

 Criação do Bond

              │

 Canal criptografado

──────────────────────────────────

              │

 Companion continua inicialização

              │

 Sistema pronto
```

Todo o processo de pareamento deverá utilizar exclusivamente o mecanismo nativo do iOS.

Nenhum aplicativo de terceiros poderá ser necessário.

Nenhum diálogo de pareamento personalizado deverá ser implementado.

---

# 6. Responsabilidades

## Firmware

O Firmware será responsável por:

- disponibilizar suporte a Pairing;
- disponibilizar suporte a Bonding;
- manter as informações de segurança;
- expor uma operação protegida capaz de iniciar o processo de pareamento;
- restaurar automaticamente Bonds existentes.

O Firmware não deverá:

- controlar telas do Companion;
- solicitar interação do usuário;
- controlar o fluxo de onboarding.

---

## Companion

O Companion será responsável por:

- localizar dispositivos;
- conectar ao K.O.R.E.;
- identificar quando o dispositivo ainda não possui Bond;
- iniciar a operação protegida;
- aguardar a conclusão do Pairing;
- tratar sucesso;
- tratar cancelamento;
- tratar falhas;
- continuar a inicialização somente após a criação do Bond.

---

## iOS

O sistema operacional será responsável por:

- exibir o diálogo oficial de Pairing;
- validar o consentimento do usuário;
- criar o Bond BLE;
- armazenar as chaves de segurança;
- restaurar automaticamente conexões futuras.

O Companion nunca deverá substituir o comportamento nativo do iOS.

---

# 7. Fluxo do Usuário

Primeira utilização:

```
Abrir Companion

↓

Encontrar K.O.R.E.

↓

Conectar

↓

Solicitar operação protegida

↓

Popup nativo do iOS

↓

Usuário aceita

↓

Bond criado

↓

Canal criptografado

↓

Dashboard
```

Próximas utilizações:

```
Abrir Companion

↓

Encontrar K.O.R.E.

↓

Conectar

↓

Canal seguro restaurado

↓

Dashboard
```

O usuário não deverá visualizar novamente o diálogo de pareamento.

---

# 8. Estados da Conexão

O módulo de conexão deverá suportar os seguintes estados:

```
Searching

↓

Connecting

↓

Pairing

↓

Bonding

↓

Secure Connection

↓

Ready
```

Fluxos de erro:

```
Searching

↓

Connecting

↓

Pairing

↓

Cancelado pelo usuário

↓

Retry
```

ou

```
Searching

↓

Connecting

↓

Falha no Pairing

↓

Retry
```

---

# 9. Requisitos de Segurança

A infraestrutura BLE deverá suportar:

- autenticação;
- criptografia;
- bonding;
- reconexão segura.

Os detalhes de implementação ficam a cargo do HARNESS correspondente.

---

# 10. Gatilho do Pairing

O Companion não deverá iniciar diretamente um processo de Pairing.

O Pairing deverá ocorrer de forma indireta através da solicitação de uma operação BLE protegida.

Caso ainda não exista um Bond entre os dispositivos, o iOS deverá interromper a operação, apresentar seu diálogo oficial de pareamento e, após a confirmação do usuário, retomar automaticamente a execução.

---

# 11. Persistência

Após o primeiro pareamento:

- o Bond deverá sobreviver ao reinício do ESP32;
- o Bond deverá sobreviver ao reinício do Companion;
- novas conexões deverão ocorrer automaticamente;
- não deverá existir novo onboarding.

---

# 12. Tratamento de Falhas

O Companion deverá tratar:

- cancelamento do usuário;
- timeout;
- falha no pareamento;
- perda de conexão durante o Pairing;
- reinicialização do dispositivo durante o onboarding.

Sempre deverá existir possibilidade de nova tentativa.

---

# 13. Critérios de Aceitação

## AC-001

O Companion identifica um dispositivo ainda não pareado.

---

## AC-002

O Companion conecta normalmente ao dispositivo.

---

## AC-003

Uma operação protegida provoca a abertura do diálogo nativo de Pairing do iOS.

---

## AC-004

Após a confirmação do usuário, o Bond BLE é criado.

---

## AC-005

A conexão passa a operar em modo criptografado.

---

## AC-006

O Companion conclui normalmente sua inicialização.

---

## AC-007

Após reiniciar ambos os dispositivos, a conexão ocorre automaticamente sem novo pareamento.

---

## AC-008

O dispositivo passa a aparecer em:

Ajustes

→ Bluetooth

→ Meus Dispositivos

---

# 14. Consumidores desta Infraestrutura

A infraestrutura criada por esta SPEC será utilizada por:

- Apple Notification Center Service (ANCS);
- futuros serviços BLE seguros;
- qualquer funcionalidade que exija comunicação BLE autenticada.

Esta SPEC define apenas a infraestrutura de segurança.

Os serviços que utilizarão essa infraestrutura serão definidos em especificações próprias.

---

# 15. Próximas SPECs

Após a conclusão desta especificação deverão ser produzidas:

- SPEC-002 — Integração ANCS
- SPEC-003 — Sincronização de Notificações iOS

---

# 16. Observações

Esta especificação define exclusivamente a arquitetura e o comportamento esperado do sistema.

Escolha de bibliotecas, APIs, callbacks, configuração do BLE, advertising, características protegidas e demais detalhes técnicos deverão ser definidos durante a elaboração do HARNESS correspondente.