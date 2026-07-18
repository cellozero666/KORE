# HARNESS-001 — Secure BLE Pairing & Bonding

- **Projeto:** K.O.R.E.
- **Módulo:** Shared
- **Versão:** 1.0.0
- **Status:** Aprovado
- **Relacionado à:** SPEC-001 — Secure BLE Pairing & Bonding

---

# 1. Objetivo

Implementar toda a infraestrutura necessária para permitir que o ESP32 estabeleça uma conexão BLE segura com dispositivos iOS através do processo nativo de Pairing e Bonding.

Ao final desta implementação, o firmware deverá ser reconhecido pelo iPhone como um dispositivo confiável e ser capaz de utilizar serviços BLE protegidos, como o Apple Notification Center Service (ANCS).

---

# 2. Escopo

Esta implementação contempla:

- configuração da camada de segurança BLE;
- suporte a Pairing;
- suporte a Bonding;
- persistência do Bond;
- restauração automática do Bond;
- implementação do gatilho de Pairing;
- atualização do fluxo de conexão do Companion.

Não faz parte deste HARNESS:

- implementação do ANCS;
- renderização de notificações;
- Input Adapter;
- interface gráfica.

---

# 3. Requisitos

A implementação deverá atender aos seguintes requisitos.

## Firmware

O firmware deverá:

- permitir Pairing BLE;
- permitir Bonding BLE;
- permitir comunicação criptografada;
- restaurar Bonds existentes após reinicialização;
- disponibilizar pelo menos uma operação protegida que exija conexão criptografada.

---

## Companion

O Companion deverá:

- detectar dispositivos ainda não pareados;
- conectar normalmente;
- executar uma operação protegida para iniciar o Pairing;
- aguardar a conclusão do processo;
- continuar a inicialização automaticamente após o sucesso.

---

# 4. Fluxo Esperado

Primeira conexão

```
Scan

↓

Connect

↓

Operação protegida

↓

iOS apresenta Pairing

↓

Usuário aceita

↓

Bond criado

↓

Sessão criptografada

↓

Inicialização continua
```

Reconexão

```
Scan

↓

Connect

↓

Sessão criptografada restaurada

↓

Inicialização continua
```

---

# 5. Persistência

Após o primeiro Pairing:

- o Bond deverá sobreviver ao reboot do ESP32;
- o Bond deverá sobreviver ao reinício do Companion;
- o usuário não deverá repetir o processo de pareamento.

---

# 6. Requisitos Técnicos

A implementação deverá utilizar uma stack BLE que suporte:

- Pairing;
- Bonding;
- conexões criptografadas;
- persistência de chaves.

A escolha da biblioteca fica a cargo do implementador, desde que todos os requisitos da SPEC-001 sejam atendidos.

---

# 7. Gatilho de Pairing

O Pairing deverá ocorrer através da tentativa de acesso a um recurso protegido.

A implementação deverá garantir que:

- o Companion não invoque APIs específicas de Pairing;
- o sistema operacional seja responsável por apresentar o diálogo oficial;
- após o aceite do usuário a operação seja retomada normalmente.

---

# 8. Tratamento de Erros

A implementação deverá tratar:

- cancelamento pelo usuário;
- timeout;
- perda da conexão;
- falha na criação do Bond;
- tentativa de reconexão com Bond inválido.

Sempre deverá existir possibilidade de nova tentativa.

---

# 9. Entregáveis

Ao término deste HARNESS deverão existir:

- suporte completo a Pairing;
- suporte completo a Bonding;
- conexão BLE criptografada;
- restauração automática de Bonds;
- fluxo de onboarding funcional.

O firmware deverá aparecer no iOS em:

```
Ajustes

↓

Bluetooth

↓

Meus Dispositivos
```

---

# 10. Critérios de Validação

A implementação será considerada concluída quando:

- o Pairing ocorrer utilizando exclusivamente o diálogo nativo do iOS;
- o Bond permanecer válido após reinicialização do ESP32;
- o Companion reconectar automaticamente;
- nenhuma etapa manual adicional seja necessária após o primeiro pareamento;
- a infraestrutura esteja apta para utilização pelo ANCS.

---

# 11. Observações para Implementação

O implementador possui liberdade para definir:

- biblioteca BLE;
- callbacks;
- configuração de segurança;
- características protegidas;
- estratégia de advertising;
- estrutura interna do código.

Qualquer decisão deverá respeitar integralmente a arquitetura definida na SPEC-001.

A implementação deverá privilegiar soluções nativas e consolidadas, evitando código proprietário quando houver bibliotecas estáveis que atendam aos requisitos.