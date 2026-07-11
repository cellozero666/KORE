# HARNESS-009 - Spotify

## Objetivo

Implementar a SPEC `009_spotify.md`.

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/01_macos/009_spotify.md

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
- Validar interface React.
- Validar controles Play, Pause, Previous e Next.
- Validar envio de `spotify|TRACK|ARTIST|ALBUM|PROGRESS|DURATION` para a ESP32.
- Validar envio de `spotify_stop`.
- Apresentar o resultado para validação.

Não iniciar o próximo Harness sem aprovação explícita do usuário.