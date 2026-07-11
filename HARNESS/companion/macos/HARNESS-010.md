# HARNESS-010 - Google

## Objetivo

Implementar a SPEC `010_google.md`.

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/01_macos/010_google.md

## Regras

- Implementar apenas o que está definido na SPEC.
- Não adicionar funcionalidades extras.
- Não alterar a arquitetura definida nas ADRs.

## Entrega

Ao concluir o módulo:

- Garantir que o projeto compile.
- Corrigir erros e warnings.
- Executar testes do módulo.
- Validar autenticação OAuth.
- Validar Refresh Token.
- Validar atualização do State Global.
- Validar watcher do Gmail.
- Validar watcher do Google Calendar.
- Validar envio de `notification|mail|SENDER|CONTENT`.
- Validar envio de `notification|calendar|SENDER|CONTENT`.
- Apresentar o resultado para validação.

Não iniciar o próximo Harness sem aprovação explícita do usuário.