SPEC-003 — Firmware Architecture Review

Objetivo:

Realizar uma auditoria completa da arquitetura do firmware, identificando oportunidades de melhoria sem alterar o comportamento funcional.

Esta etapa não implementa mudanças.

Seu único objetivo é produzir um plano técnico para evolução do firmware rumo à versão 1.0.

⸻

Áreas de análise

1. Arquitetura

* Separação de responsabilidades
* Acoplamento
* Dependências circulares
* Organização dos managers
* Organização dos screens
* Organização dos estados

⸻

2. Segurança

Mesmo sendo firmware local.

Verificar:

* validação dos comandos BLE
* validação Serial
* tamanho máximo de mensagens
* String overflows
* parsers
* comandos inválidos
* ataques por flooding
* reconnect BLE
* watchdog
* fail-safe

⸻

3. Memória

Verificar:

* Strings temporárias
* Fragmentação
* cópias desnecessárias
* uso de stack
* objetos globais
* arrays
* PROGMEM
* const correctness

⸻

4. Performance

Verificar:

* redraws desnecessários
* SPI
* display
* animações
* loops
* millis()
* timers
* renderizações repetidas

⸻

5. Escalabilidade

Responder:

Se amanhã adicionarmos:

* Music
* Calendar
* Weather 2
* Home Assistant
* MQTT
* BLE Client
* Wi-Fi OTA

A arquitetura suporta?

Onde quebra?

⸻

6. Robustez

Verificar:

* recovery
* timeouts
* reconexão
* watchdog
* estados inválidos
* race conditions

⸻

7. API interna

Os managers conversam corretamente?

Existem dependências escondidas?

Existem globais desnecessárias?

Pode haver encapsulamento melhor?

⸻

8. Código

Verificar:

* duplicação
* constantes
* includes
* forward declarations
* macros
* constexpr
* enum class
* const
* static
* inline

⸻

9. Arduino Best Practices

Comparar o firmware com as boas práticas do ESP32 Arduino Core.

Não com C++ desktop.

⸻

10. Release 1.0

Responder:

O que impediria este firmware de ser considerado uma Release 1.0?