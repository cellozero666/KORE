001_foundations.md

O documento deixa claro:

O firmware NÃO está em fase de redesign.

Objetivo:

* estabilizar
* corrigir
* otimizar
* documentar

Nunca reescrever.

⸻

Princípios

Preserve o funcionamento existente

Todo comportamento funcional existente deve ser preservado.

⸻

Refatoração somente quando necessária

Refatorações são permitidas apenas quando:

* eliminam bugs
* melhoram legibilidade
* reduzem duplicação
* reduzem consumo de memória
* simplificam manutenção

Nunca por preferência estética.

⸻

Firmware First

O hardware é a fonte da verdade.

A interface Companion adapta-se ao firmware, nunca o contrário.

⸻

Zero Regressões

Toda alteração deve produzir exatamente o mesmo comportamento observável.

⸻

Release-Oriented

O objetivo é entregar uma Release 1.0 estável.

Não adicionar funcionalidades.