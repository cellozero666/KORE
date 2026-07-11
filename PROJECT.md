PROJECT.md

K.O.R.E.

Visão Geral

K.O.R.E. é um ecossistema composto por um firmware embarcado para ESP32 e um conjunto de aplicações Companion multiplataforma.

O projeto tem como objetivo criar uma experiência integrada entre hardware e software, oferecendo uma interface inteligente, responsiva e consistente em todas as plataformas suportadas.

O ecossistema é composto por:

* Firmware K.O.R.E. para ESP32.
* Companion App para macOS.
* Companion App para Windows.
* Companion App para Linux.
* Companion App para iOS.
* Companion App para Android.

Todos os componentes devem compartilhar a mesma arquitetura, filosofia de desenvolvimento e identidade do produto.

⸻

Objetivos

O projeto possui os seguintes objetivos principais:

* Desenvolver uma arquitetura moderna, modular e escalável.
* Manter alta qualidade de código.
* Garantir facilidade de manutenção.
* Minimizar retrabalho.
* Centralizar decisões técnicas na documentação.
* Reduzir perda de contexto durante o desenvolvimento.
* Permitir evolução contínua do sistema.

⸻

Filosofia do Projeto

Todo desenvolvimento deverá seguir os seguintes princípios:

* Simplicidade acima de complexidade.
* Clareza acima de criatividade.
* Código limpo acima de soluções engenhosas.
* Escalabilidade sem overengineering.
* Modularidade.
* Responsabilidade única.
* Evolução incremental.
* Documentação como fonte oficial da verdade.

⸻

Metodologia

O projeto utiliza Spec Driven Development (SDD).

Nenhuma funcionalidade deverá ser implementada antes da existência de sua especificação.

Toda implementação deverá possuir um Harness correspondente.

Toda decisão arquitetural deverá ser registrada através de uma ADR quando aplicável.

⸻

Organização da Documentação

A documentação do projeto é organizada da seguinte forma:

* PROJECT.md
* SPEC/
* ADR/
* HARNESS/
* AGENTS.md
* GEMINI.md

PROJECT.md é o documento raiz do projeto.

Os demais documentos complementam este documento.

⸻

Fluxo de Desenvolvimento

Todo desenvolvimento deverá seguir obrigatoriamente o fluxo abaixo:

Especificação

↓

Harness

↓

Implementação

↓

Testes

↓

Validação

↓

Aprovação

↓

Próximo módulo

Nenhum módulo deverá ser considerado concluído sem aprovação.

⸻

Desenvolvimento Modular

Todo desenvolvimento será dividido em módulos independentes.

Cada módulo deverá possuir:

* Objetivo definido.
* Escopo limitado.
* Critérios claros de conclusão.
* Critérios de aceitação.
* Possibilidade de testes isolados.

Ao finalizar um módulo, o desenvolvimento deverá ser interrompido para validação antes do início do próximo.

⸻

Arquitetura Geral

O projeto é dividido em dois grandes produtos.

K.O.R.E. OS

Responsável pelo firmware executado no ESP32.

Companion

Responsável pelas aplicações desktop e mobile.

Toda lógica compartilhada deverá ser reutilizada sempre que possível.

⸻

Gurus do Projeto

Gaspar

Responsável por:

* Arquitetura.
* Spec Driven Development.
* ADRs.
* Revisão técnica.
* Consistência arquitetural.

Belthazar

Responsável por:

* Implementação.
* Refatoração.
* Testes.
* Evolução da base de código.

Belthazar corresponde exclusivamente à combinação:

* OpenCode
* Laguna XS 2.1OpenRouter

Melchior

Responsável por:

* Interface.
* Experiência do usuário.
* Design System.
* Componentização.

Melchior corresponde exclusivamente à combinação:

* Gemini CLI
* UI/UX Pro Max

⸻

Fonte Oficial da Verdade

Toda decisão do projeto deverá estar documentada.

Em caso de conflito entre implementação e documentação, a documentação prevalece.

Em caso de conflito entre documentos, deverá ser respeitada a ordem de precedência definida em AGENTS.md e GEMINI.md.

Nenhum agente deverá criar requisitos ou tomar decisões fora da documentação oficial do projeto.