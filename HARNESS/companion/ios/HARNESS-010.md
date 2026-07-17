# HARNESS-010 - Google

## Objetivo

Implementar a SPEC `010_google.md`.

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/02_ios/010_google.md

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
- Validar autenticação OAuth.
- Validar Refresh Token.
- Validar atualização do State Global.
- Validar watcher do Gmail.
- Validar watcher do Google Calendar.
- Validar envio de `notification|mail|SENDER|CONTENT`.
- Validar envio de `notification|calendar|SENDER|CONTENT`.
- Validar em hardware real utilizando um dispositivo iOS e o K.O.R.E. OS.
- Comprovar, por meio de logs ou evidências, que os eventos do Gmail e Google Calendar foram processados corretamente e enviados ao firmware.
- Apresentar o resultado para validação.

Não iniciar o próximo Harness sem aprovação explícita do usuário.