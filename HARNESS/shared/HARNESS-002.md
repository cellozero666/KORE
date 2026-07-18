# HARNESS-002 — Apple Notification Center Service (ANCS)

- **Projeto:** K.O.R.E.
- **Módulo:** Shared
- **Versão:** 1.0.0
- **Status:** Aprovado
- **Relacionado à:** SPEC-002 — Apple Notification Center Service (ANCS)

---

# 1. Objetivo

Implementar a integração entre o firmware do K.O.R.E. e o Apple Notification Center Service (ANCS), permitindo que notificações do iPhone sejam recebidas e encaminhadas ao Input Adapter.

Ao final desta implementação, o ANCS deverá funcionar apenas como mais uma fonte de eventos do sistema, sem introduzir dependências entre o protocolo da Apple e a arquitetura interna do firmware.

---

# 2. Escopo

Esta implementação contempla:

- descoberta do serviço ANCS;
- estabelecimento da comunicação com o ANCS;
- recebimento de eventos do iPhone;
- obtenção dos atributos necessários das notificações;
- encaminhamento dos eventos ao Input Adapter.

Não faz parte deste HARNESS:

- Pairing;
- Bonding;
- Segurança BLE;
- implementação do Input Adapter;
- Parser;
- Managers;
- Interface gráfica;
- Renderização de notificações.

---

# 3. Requisitos

A implementação deverá atender aos seguintes requisitos.

## Firmware

O firmware deverá:

- identificar automaticamente a disponibilidade do ANCS após uma conexão segura;
- inicializar a comunicação com o serviço;
- receber eventos disponibilizados pelo ANCS;
- solicitar os atributos necessários para cada notificação;
- encaminhar todos os eventos ao Input Adapter.

O firmware não deverá:

- interpretar regras de negócio;
- acessar diretamente Managers;
- depender da implementação interna do Input Adapter.

---

## Companion

O Companion não deverá executar qualquer processamento relacionado ao ANCS.

Sua única responsabilidade é garantir que exista uma conexão BLE segura estabelecida conforme definido na SPEC-001.

---

# 4. Fluxo Esperado

```
Conexão BLE segura

↓

Descoberta do ANCS

↓

Inicialização da comunicação

↓

Recebimento de evento

↓

Leitura dos atributos necessários

↓

Encaminhamento ao Input Adapter

↓

Fluxo normal do sistema
```

---

# 5. Descoberta do Serviço

Após a conclusão da conexão segura, o firmware deverá:

- localizar automaticamente o serviço ANCS;
- validar sua disponibilidade;
- iniciar o consumo de eventos.

Caso o serviço não esteja disponível, o firmware deverá continuar operando normalmente.

---

# 6. Consumo de Eventos

A implementação deverá consumir os eventos disponibilizados pelo ANCS que sejam relevantes para o funcionamento do K.O.R.E.

Quando necessário, deverão ser obtidos os atributos associados à notificação antes do encaminhamento ao Input Adapter.

A seleção dos atributos utilizados ficará a cargo da implementação.

---

# 7. Integração com o Input Adapter

Toda comunicação entre o ANCS e o restante do firmware deverá ocorrer exclusivamente através do Input Adapter.

Nenhum outro componente poderá consumir diretamente:

- eventos do ANCS;
- estruturas de dados da biblioteca utilizada;
- APIs específicas da Apple.

O formato interno utilizado pelo Input Adapter deverá permanecer inalterado.

---

# 8. Tratamento de Erros

A implementação deverá tratar, no mínimo:

- ausência do serviço ANCS;
- falha durante a descoberta do serviço;
- perda da conexão BLE;
- falha na leitura de atributos;
- indisponibilidade temporária do serviço;
- revogação da permissão de compartilhamento de notificações pelo usuário.

Nenhuma dessas situações deverá interromper o funcionamento do restante do firmware.

---

# 9. Requisitos Técnicos

A implementação deverá utilizar uma biblioteca compatível com o Apple Notification Center Service.

A biblioteca escolhida deverá oferecer suporte para:

- descoberta do serviço;
- assinatura de eventos;
- leitura de atributos;
- funcionamento sobre conexões BLE seguras.

A escolha da biblioteca fica a cargo do implementador.

---

# 10. Entregáveis

Ao término deste HARNESS deverão existir:

- descoberta automática do serviço ANCS;
- inicialização automática após conexão segura;
- recebimento de notificações do iPhone;
- leitura dos atributos necessários;
- integração completa com o Input Adapter;
- isolamento total entre o protocolo ANCS e o restante do firmware.

---

# 11. Critérios de Validação

A implementação será considerada concluída quando:

- o firmware identificar automaticamente o serviço ANCS;
- eventos provenientes do iPhone forem recebidos corretamente;
- os atributos necessários das notificações forem obtidos com sucesso;
- todos os eventos forem encaminhados exclusivamente ao Input Adapter;
- nenhum componente interno depender diretamente da biblioteca ANCS;
- a substituição da biblioteca ANCS puder ocorrer sem alterações na arquitetura do restante do firmware.

---

# 12. Observações para Implementação

O implementador possui liberdade para definir:

- biblioteca ANCS;
- organização interna dos módulos;
- callbacks;
- estratégia de descoberta do serviço;
- estratégia de leitura dos atributos;
- gerenciamento da comunicação BLE.

Toda implementação deverá respeitar integralmente a arquitetura definida na SPEC-002.

Sempre que possível deverão ser utilizadas bibliotecas consolidadas, evitando implementações proprietárias do protocolo ANCS.