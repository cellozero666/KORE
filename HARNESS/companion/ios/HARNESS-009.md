# HARNESS-009 - Spotify

## Objetivo

Implementar a SPEC `009_spotify.md`.

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/02_ios/009_spotify.md

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
- Validar interface React.
- Validar controles Play, Pause, Previous e Next.
- Validar envio periódico de `spotify|TRACK|ARTIST|ALBUM|PROGRESS|DURATION` para a ESP32 via BLE.
- Validar envio de `spotify_stop`.
- Validar em hardware real utilizando um dispositivo iOS e o K.O.R.E. OS.
- Comprovar, por meio de logs ou evidências, que os comandos e informações do Spotify foram enviados pelo Companion e recebidos corretamente pelo firmware.
- Apresentar o resultado para validação.

Não iniciar o próximo Harness sem aprovação explícita do usuário.