# 005_state.md

# State Management

## Objetivo

Implementar o gerenciamento de estado global do K.O.R.E. Companion, estabelecendo uma arquitetura centralizada, modular e escalável para compartilhamento de dados entre os módulos da aplicação.

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
- 004_navigation.md

---

## Escopo

- Definir a arquitetura de gerenciamento de estado global.
- Criar a Store principal da aplicação.
- Criar Stores independentes para cada módulo.
- Implementar Providers necessários.
- Preparar o compartilhamento de estado entre componentes.
- Preparar comunicação entre Frontend e Backend.
- Permitir atualização reativa dos estados.
- Reutilizar o máximo possível de código existente do Companion macOS localizado em `ROOT/COMPANION/macos/APP`, preservando a arquitetura e adaptando apenas o que for necessário para compatibilidade com iOS.

### Stores

- App
- Dashboard
- Spotify
- Google
- Weather
- Settings

As Stores poderão iniciar vazias, servindo como base para os próximos módulos.

---

## Não faz parte

- Persistência de dados.
- Comunicação com o firmware.
- Consumo de APIs.
- Regras de negócio.
- Implementação das funcionalidades dos módulos.

---

## Critérios de Aceitação

- A Store global está configurada.
- Todas as Stores dos módulos foram criadas.
- O estado pode ser compartilhado entre componentes.
- A atualização dos estados ocorre de forma reativa.
- A arquitetura está preparada para os próximos módulos.
- O código permanece modular e escalável.