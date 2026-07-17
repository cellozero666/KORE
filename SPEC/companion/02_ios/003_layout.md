# 003_layout.md

# Layout

## Objetivo

Criar a estrutura base da interface do K.O.R.E. Companion para iOS, definindo o layout principal da aplicação e preparando a navegação entre os módulos.

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

---

## Escopo

- Criar a estrutura principal da aplicação.
- Criar uma tela de loading inicial com duração de 5 segundos.
- Criar o layout utilizando componentes React.
- Criar a navegação principal da aplicação.
- Criar a área principal de conteúdo.
- Preparar o layout para futuras telas.
- Garantir que o layout ocupe toda a área útil da tela.
- Reutilizar o máximo possível de código existente do Companion macOS localizado em `ROOT/COMPANION/macos/APP`, preservando a arquitetura e adaptando apenas o que for necessário para compatibilidade com iOS.

### Itens de Navegação

- Dashboard (tela inicial)
- Spotify
- Google
- Weather
- Settings

Os itens de navegação deverão estar visíveis e preparados para futura implementação, mesmo que ainda não possuam funcionalidade.

---

## Não faz parte

- Funcionalidades dos módulos.
- Comunicação com o firmware.
- Gerenciamento de estado.
- Integração com Spotify.
- Integração com Google.
- Integração com Weather.
- Configurações da aplicação.

---

## Critérios de Aceitação

- A tela de loading é exibida corretamente.
- O layout principal é exibido corretamente.
- Os itens de navegação são exibidos corretamente.
- Os atalhos dos módulos estão visíveis.
- Dashboard é a tela inicial.
- O layout ocupa toda a área útil da tela.
- A estrutura permanece preparada para os próximos módulos.