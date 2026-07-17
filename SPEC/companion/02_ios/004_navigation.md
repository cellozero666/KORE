# 004_navigation.md

# Navigation

## Objetivo

Implementar a navegação principal do K.O.R.E. Companion entre os módulos da aplicação.

---

## Diretório de Trabalho

```
ROOT/COMPANION/ios/APP
```

Todo o desenvolvimento deste módulo deverá ocorrer exclusivamente neste diretório.

---

## Dependências

### SPECs

- 001_foundation.md
- 002_window.md
- 003_layout.md

---

## Escopo

- Configurar o React Router.
- Criar as rotas principais da aplicação.
- Implementar a navegação entre os módulos.
- Destacar visualmente o módulo ativo.
- Implementar a navegação inicial para o Dashboard.
- Criar páginas temporárias para todos os módulos.
- Preparar a estrutura para futuras rotas.
- Reutilizar o máximo possível de código existente do Companion macOS localizado em `ROOT/COMPANION/macos/APP`, preservando a arquitetura e adaptando apenas o que for necessário para compatibilidade com iOS.

### Rotas

- Dashboard (/)
- Spotify (/spotify)
- Google (/google)
- Weather (/weather)
- Settings (/settings)

---

## Não faz parte

- Funcionalidades dos módulos.
- Comunicação com o firmware.
- Gerenciamento de estado.
- Integrações externas.
- Conteúdo definitivo das páginas.

---

## Critérios de Aceitação

- Todas as rotas estão funcionando.
- A navegação funciona corretamente entre as páginas.
- O módulo ativo é destacado visualmente.
- Dashboard é carregado como página inicial.
- Todas as páginas temporárias são exibidas corretamente.
- A navegação funciona sem recarregar a aplicação.
- A estrutura está preparada para os próximos módulos.