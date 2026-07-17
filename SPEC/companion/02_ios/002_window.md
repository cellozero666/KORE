# 002_window.md

# Window

## Objetivo

Configurar a janela principal do K.O.R.E. Companion para iOS utilizando os recursos nativos do Tauri Mobile, estabelecendo o comportamento padrão da aplicação.

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

---

## Escopo

- Configurar a janela principal da aplicação.
- Definir o título da aplicação como K.O.R.E. Companion.
- Configurar o comportamento ao iniciar a aplicação.
- Configurar o comportamento ao retornar do background.
- Configurar o comportamento ao encerrar a aplicação.
- Configurar o foco da aplicação.
- Configurar suporte ao modo escuro do iOS.
- Preparar a aplicação para futuras integrações com Deep Links, notificações e recursos nativos do iOS.
- Reutilizar o máximo possível de código existente do Companion macOS localizado em `ROOT/COMPANION/macos/APP`, preservando a arquitetura e adaptando apenas o que for necessário para compatibilidade com iOS.

---

## Não faz parte

- Interface gráfica.
- Layout.
- Navegação.
- Persistência de estado.
- Comunicação com o firmware.
- BLE.
- ANCS.

---

## Critérios de Aceitação

- A aplicação inicia corretamente.
- A tela principal é exibida sem erros.
- O título da aplicação é K.O.R.E. Companion.
- O ícone da aplicação está configurado.
- O comportamento de abertura, background e encerramento funciona corretamente.
- O projeto permanece pronto para evolução dos próximos módulos.