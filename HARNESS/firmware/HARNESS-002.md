Objetivo

Substituir completamente o Emotion System.

Não reparar a implementação existente.

Construir uma nova implementação simples, determinística e compilada.

---

Utilizar como referência funcional:

- emotion_rules.json
- comportamento atual esperado
- documentação existente

---

Preservar apenas o contrato público:

Recebe texto

↓

Detecta emoção

↓

Seleciona FaceType

↓

Mantém a emoção durante o tempo definido

↓

Restaura a face anterior

---

É permitido:

- substituir completamente loadEmotionRules()
- remover ArduinoJson
- remover FFat
- reorganizar EmotionRule
- substituir estruturas internas
- simplificar detectEmotion()

Desde que o comportamento observado permaneça equivalente.

---

Ao final:

- remover emotion_rules.json
- remover FFat
- remover ArduinoJson
- documentar a nova implementação
- validar em hardware