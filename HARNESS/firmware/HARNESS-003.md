# HARNESS-003 — Firmware v1.0 Readiness

## Objetivo

Preparar o firmware para a versão 1.0, implementando melhorias arquiteturais, de confiabilidade e de manutenção aprovadas na revisão arquitetural.

Este HARNESS não adiciona novas funcionalidades ao produto.

Seu objetivo é aumentar a robustez, previsibilidade, escalabilidade e qualidade do firmware mantendo o comportamento funcional existente.

---

# Escopo

## 1. Corrigir bugs confirmados

Implementar apenas bugs comprovados pela revisão arquitetural.

Inclui:

- corrigir updateNotification() executado duas vezes (caso confirmado);
- adicionar resposta TCP em sendResponse();
- demais bugs confirmados durante a implementação.

Nenhum comportamento funcional deverá mudar além da correção do defeito.

---

## 2. Migrar arquitetura para .cpp/.h

Migrar o firmware do modelo atual header-only para separação tradicional:

- .h contendo interfaces;
- .cpp contendo implementações.

Objetivos:

- reduzir acoplamento;
- melhorar encapsulamento;
- reduzir recompilações;
- facilitar manutenção;
- preparar o projeto para crescimento futuro.

A API pública dos módulos deverá permanecer equivalente.

---

## 3. Implementar FaceController

Criar um módulo responsável por centralizar todas as alterações de face.

Após esta implementação:

nenhum módulo poderá alterar currentFace diretamente.

Todos deverão utilizar exclusivamente:

- requestFace(...)
- releaseFace(...)

O FaceController será o único responsável por alterar currentFace.

Não implementar filas complexas.

Não implementar máquina de estados extensa.

Utilizar apenas resolução por prioridade.

---

## 4. Tornar Boot não bloqueante

Eliminar delays bloqueantes do boot.

Preservar:

- identidade visual;
- barra de animação;
- experiência do usuário.

O firmware deverá permanecer disponível para inicialização dos demais subsistemas o mais cedo possível.

A animação poderá ser baseada em millis().

---

## 5. Watchdog

Implementar watchdog utilizando recursos oficiais do ESP32.

Inclui:

- registro da task principal;
- alimentação periódica;
- captura do motivo do último reset.

Não implementar Safe Mode neste HARNESS.

Safe Mode será tratado em futura SPEC.

---

## 6. Organização dos estados globais

Melhorar a organização dos estados globais.

Não criar singleton global.

Não criar State Manager.

Cada estado deverá possuir proprietário claramente definido.

Documentar ownership diretamente no código.

---

## 7. Reset de estados de animação

Garantir que mudanças de face reinicializem corretamente:

- blink;
- sleep;
- timers;
- estados internos de animação.

---

## 8. Melhorias menores aprovadas

Implementar:

- randomSeed();
- tratamento consistente para faces inválidas;
- demais melhorias classificadas como P0 ou P1 pela revisão arquitetural.

---

# Restrições

Não implementar:

- FreeRTOS;
- Registry de comandos;
- OTA;
- ANCS;
- Capability Negotiation;
- Versionamento de protocolo;
- Safe Mode;
- Criptografia de credenciais;
- Alterações de protocolo;
- Novas funcionalidades.

---

# Critérios de Aceitação

O firmware deverá:

- compilar sem warnings;
- preservar todas as funcionalidades atuais;
- manter compatibilidade com o Companion;
- manter compatibilidade com BLE;
- manter compatibilidade com TCP;
- manter compatibilidade com Serial;
- manter compatibilidade com Spotify;
- manter Emotion System;
- manter Notification System.

---

# Entregáveis

Ao final apresentar:

- lista de arquivos alterados;
- decisões arquiteturais tomadas;
- comparação Flash antes/depois;
- comparação RAM antes/depois;
- descrição das mudanças realizadas;
- riscos conhecidos;
- validações executadas.

Escrever esse relatorio em /docs/FIRMWARE_UPDATE.md (criar arquivo)