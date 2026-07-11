# HARNESS-011 - Weather

## Objetivo

Implementar a SPEC `011_weather.md`.

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/01_macos/011_weather.md

## Regras

- Implementar apenas o que está definido na SPEC.
- Não adicionar funcionalidades extras.
- Não alterar a arquitetura definida nas ADRs.

## Entrega

Ao concluir o módulo:

- Garantir que o projeto compile.
- Corrigir erros e warnings.
- Executar testes do módulo.
- Validar localização automática.
- Validar utilização da cidade configurada em Settings.
- Validar atualização periódica do clima.
- Validar atualização do State Global.
- Validar envio de `weather|CITY|TEMP|HITEMP|LOWTEMP|ICON` para a ESP32.
- Validar atualização automática a cada 1 hora.
- Apresentar o resultado para validação.

Não iniciar o próximo Harness sem aprovação explícita do usuário.