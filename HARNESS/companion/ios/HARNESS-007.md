# HARNESS-007 - Dashboard

## Objetivo

Implementar a SPEC `007_dashboard.md`.

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/02_ios/007_dashboard.md

## Regras

- Implementar apenas o que está definido na SPEC.
- Reutilizar o máximo possível de código existente do Companion macOS localizado em `ROOT/COMPANION/macos/APP`, preservando a arquitetura e adaptando apenas o que for necessário para compatibilidade com iOS.
- Não adicionar funcionalidades extras.
- Não alterar a arquitetura definida nas ADRs.

## Entrega

Ao concluir o módulo:

- Garantir que o projeto compile.
- Corrigir erros e warnings.
- Executar os testes do módulo.
- Validar em hardware real utilizando o K.O.R.E. OS.
- Validar comunicação com o K.O.R.E. OS.
- Validar obtenção de `version`.
- Validar obtenção de `uptime`.
- Validar obtenção de `wifi_status`.
- Validar o envio de comandos através da área **Command Test**.
- Comprovar, por meio de logs ou evidências, que os comandos foram enviados ao firmware e que as respostas foram recebidas corretamente.
- Apresentar o resultado para validação.

Não iniciar o próximo Harness sem aprovação explícita do usuário.