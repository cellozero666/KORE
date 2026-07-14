# SPEC-002 — Emotion System v2

## Objetivo

Substituir integralmente a implementação atual do Emotion System.

A implementação atual deixou de ser confiável e será descontinuada.

O novo sistema deverá ser significativamente mais simples, mais determinístico e totalmente compilado no firmware.

O comportamento observado pelo usuário deverá permanecer o mesmo.

---

## Comportamento esperado

Ao receber uma notificação:

1. O texto completo (título + corpo) deverá ser analisado.

2. O sistema deverá procurar palavras-chave.

3. A emoção correspondente deverá ser escolhida.

4. A face deverá permanecer durante o tempo configurado.

5. Após esse período, a face anterior deverá ser restaurada.

---

## Fonte das regras

As regras existentes em:

LEGACY/KORE_OS/data/emotion_rules.json

devem ser utilizadas apenas como fonte de migração.

Após a implementação, esse arquivo deixará de existir.

---

## Nova arquitetura

O Emotion System será baseado em uma tabela compilada.

Cada emoção deverá conter:

- nome
- FaceType
- duração
- prioridade
- lista de palavras-chave

A implementação deverá ser totalmente residente em firmware.

Nenhum acesso a FFat.

Nenhum parsing JSON.

---

## Requisitos

O algoritmo deverá continuar suportando:

- múltiplas palavras-chave
- score por ocorrência
- desempate por prioridade

O comportamento observado deverá permanecer equivalente ao sistema atual.

---

## Restrições

Não alterar:

- Notification System
- Display System
- Mood System
- protocolo
- renderização
- animações

---

## Critérios

Mesmo texto

↓

Mesma emoção

↓

Mesmo tempo

↓

Mesmo retorno da face anterior.