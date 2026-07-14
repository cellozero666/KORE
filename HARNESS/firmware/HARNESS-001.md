HARNESS-001

Objetivo

Preparar o firmware para a versão 1.0.

Não realizar redesign arquitetural.

⸻

Escopo

Permitido:

* corrigir bugs
* remover warnings
* remover código morto
* melhorar nomes
* melhorar comentários
* melhorar organização
* reduzir duplicação
* otimizar RAM
* otimizar Flash
* otimizar CPU
* revisar FreeRTOS
* revisar BLE
* revisar Serial
* revisar Display
* revisar watchdog
* revisar tratamento de erros

⸻

Proibido:

* trocar bibliotecas
* trocar protocolo
* trocar arquitetura
* trocar modelo de comunicação
* alterar UX
* alterar animações
* alterar layout
* alterar comportamento funcional
* alterar fluxo de boot
* alterar contratos públicos

⸻

Ordem de Trabalho

Fase A

Build

* compilar
* warnings
* erros

⸻

Fase B

Documentação

Mapear:

* módulos
* responsabilidades
* fluxo de boot
* fluxo de comunicação
* fluxo de renderização

⸻

Fase C

Auditoria

Identificar:

* bugs
* vazamentos
* duplicação
* consumo excessivo
* globals
* race conditions
* locks
* delays
* bloqueios

⸻

Fase D

Correções

Aplicar somente melhorias seguras.

Cada alteração deve:

* preservar comportamento
* compilar
* ser validada

⸻

Fase E

Validação

Verificar:

* boot
* display
* BLE
* Serial
* Spotify
* Google
* notificações
* sincronização
* estabilidade

⸻

Critérios de Aceitação

O HARNESS somente é concluído quando:

* zero erros
* zero warnings relevantes
* zero regressões
* firmware estável
* documentação atualizada
* consumo igual ou melhor
* comportamento idêntico

⸻

Critérios de Proibição

Belthazar não pode iniciar automaticamente:

* Firmware v2
* OTA
* BLE novo
* UI nova
* protocolo novo
* sistema novo de menus
* novo renderer
* novo scheduler
* nova arquitetura

Sem aprovação explícita.