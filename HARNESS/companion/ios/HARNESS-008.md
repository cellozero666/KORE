# HARNESS-008 - Notifications

## Objetivo

Implementar a SPEC `008_notifications.md`.

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/02_ios/008_notifications.md

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
- Validar solicitação de permissão para notificações no iOS.
- Validar captura de notificações através do Apple Notification Center Service (ANCS).
- Validar conversão para o formato `notification|APP|SENDER|CONTENT`.
- Validar envio para a ESP32.
- Validar em hardware real utilizando um dispositivo iOS e o K.O.R.E. OS.
- Comprovar, por meio de logs ou evidências, que a notificação foi capturada pelo ANCS, convertida para o protocolo do K.O.R.E. e recebida corretamente pela ESP32.
- Apresentar o resultado para validação.

Não iniciar o próximo Harness sem aprovação explícita do usuário.