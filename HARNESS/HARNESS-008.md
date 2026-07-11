# HARNESS-008 - Notifications

## Objetivo

Implementar a SPEC `008_notifications.md`.

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/01_macos/008_notifications.md

## Regras

- Implementar apenas o que está definido na SPEC.
- Não adicionar funcionalidades extras.
- Não alterar a arquitetura definida nas ADRs.

## Entrega

Ao concluir o módulo:

- Garantir que o projeto compile.
- Corrigir erros e warnings.
- Executar testes do módulo.
- Validar solicitação de permissão de Accessibility.
- Validar captura de notificações do macOS.
- Validar conversão para o formato `notification|APP|SENDER|CONTENT`.
- Validar envio para a ESP32.
- Apresentar o resultado para validação.

Não iniciar o próximo Harness sem aprovação explícita do usuário.