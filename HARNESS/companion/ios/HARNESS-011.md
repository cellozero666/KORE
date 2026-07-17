# HARNESS-011 - Weather

## Objetivo

Implementar a SPEC `011_weather.md`.

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/02_ios/011_weather.md

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
- Validar obtenção da localização através dos Serviços de Localização do iOS.
- Validar utilização da cidade configurada em Settings quando o modo automático estiver desabilitado.
- Validar atualização periódica do clima.
- Validar atualização do State Global.
- Validar envio de `weather|CITY|TEMP|HITEMP|LOWTEMP|ICON` para a ESP32 via BLE.
- Validar atualização automática a cada 1 hora.
- Validar em hardware real utilizando um dispositivo iOS e o K.O.R.E. OS.
- Comprovar, por meio de logs ou evidências, que os dados meteorológicos foram obtidos corretamente e enviados ao firmware.
- Apresentar o resultado para validação.

Não iniciar o próximo Harness sem aprovação explícita do usuário.