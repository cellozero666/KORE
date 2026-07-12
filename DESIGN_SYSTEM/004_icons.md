# DESIGN_SYSTEM

# 004_icons.md

# Icons

## Objetivo

Este documento define as diretrizes para utilização de ícones no ecossistema K.O.R.E.

O objetivo é garantir consistência visual, reutilização e facilidade de manutenção.

---

# Responsabilidade

Melchior é responsável por definir como os ícones serão utilizados na interface.

A implementação deverá garantir:

- Consistência visual.
- Legibilidade.
- Reutilização.
- Performance.

---

# Biblioteca Oficial

O projeto utilizará exclusivamente:

- Font Awesome

para todos os ícones da interface.

Não deverão ser utilizadas múltiplas bibliotecas de ícones.

---

# KoreIcon

O logotipo oficial do K.O.R.E. é o único ícone proprietário do projeto.

Ele deverá ser implementado como um componente React reutilizável.

Exemplo:

```
<KoreIcon />
```

O arquivo a ser usado está em /VISUAL/CAT.svg e deve ser copiado para o diretorio correto do companion app /src/assets/icons

---

# Implementação

O KoreIcon deverá utilizar SVG.

O SVG deverá permitir estilização através de CSS.

Sempre que possível utilizar:

- currentColor

para permitir alteração de aparência sem múltiplas versões do arquivo.

---

# Utilização

O KoreIcon poderá ser utilizado como elemento de interface.

Exemplos:

- Dashboard.
- Sidebar.
- Splash Screen.
- Tela inicial.
- Indicadores de estado.
- Outros locais definidos por Melchior.

---

# Estados

O KoreIcon poderá representar diferentes estados visuais da aplicação.

Exemplos:

- Connected
- Disconnected
- Loading
- Warning
- Error

A representação visual destes estados será definida por Melchior.

---

# Font Awesome

Todos os demais ícones da aplicação deverão utilizar Font Awesome.

Exemplos:

- Spotify
- Google
- Weather
- Wi-Fi
- Bluetooth
- Settings
- Dashboard
- Notification
- Calendar
- Email
- Connection

Evitar criar versões próprias destes ícones.

---

# Consistência

Todos os ícones deverão seguir uma linguagem visual consistente.

Melchior deverá definir:

- tamanhos padrão;
- pesos;
- alinhamentos;
- espaçamentos;
- regras de utilização.

---

# Performance

Evitar duplicação de ícones.

Reutilizar componentes sempre que possível.

Importar apenas os ícones efetivamente utilizados.

---

# Responsabilidade Final

O sistema de ícones é composto por:

- Font Awesome como biblioteca oficial da interface.
- KoreIcon como único ícone proprietário do projeto.

A definição de utilização pertence exclusivamente a Melchior.

Gaspar define apenas a estrutura do Design System.

Belthazar implementa conforme a especificação aprovada.