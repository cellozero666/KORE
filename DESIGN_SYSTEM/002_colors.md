# DESIGN_SYSTEM

# 002_colors.md

# Colors

## Objetivo

Este documento define as regras para construção da paleta oficial de cores do K.O.R.E.

A definição da paleta é responsabilidade de Melchior durante o processo de Design System.

---

# Responsabilidade

Melchior deverá definir toda a paleta oficial do projeto utilizando UI/UX Pro Max.

A escolha das cores deverá considerar:

- identidade do produto;
- legibilidade;
- acessibilidade;
- consistência;
- plataformas suportadas;
- Dark Theme como padrão.
- #0bebc9 e #11111 como cores principais

---

# Entregáveis

A paleta deverá definir, no mínimo:

- Background
- Surface
- Elevated Surface
- Primary Text
- Secondary Text
- Disabled Text
- Border
- Divider
- Accent
- Success
- Warning
- Error
- Information

Caso necessário, poderão existir tokens adicionais.

---

# Tokens

As cores deverão ser organizadas como Design Tokens.

Exemplo:

- background.primary
- background.secondary
- surface.primary
- surface.elevated
- text.primary
- text.secondary
- border.default
- accent.primary
- status.success
- status.warning
- status.error

A nomenclatura definitiva será definida por Melchior.

---

# Estados

Todo componente deverá possuir tokens para:

- Default
- Hover
- Active
- Focus
- Disabled
- Success
- Warning
- Error
- Loading

---

# Consistência

Não deverão existir cores hardcoded nos componentes.

Todo componente deverá utilizar exclusivamente os tokens definidos pelo Design System.

---

# Escalabilidade

A paleta deverá ser reutilizável em:

- macOS
- Windows
- Linux
- iOS
- Android

---

# Acessibilidade

A paleta deverá atender critérios adequados de contraste.

Sempre que possível, seguir WCAG AA ou superior.

---

# Responsabilidade Final

A escolha das cores pertence exclusivamente a Melchior.

Gaspar não define identidade visual.

Belthazar implementa a paleta aprovada.

Toda decisão visual deverá ser documentada neste documento após aprovação.