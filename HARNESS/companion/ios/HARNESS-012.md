# HARNESS-012 - Settings

## Objetivo

Implementar a SPEC `012_settings.md`.

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/02_ios/012_settings.md

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
- Validar persistência das configurações.
- Validar seleção de localização manual.
- Validar modo Autodetect utilizando os Serviços de Localização do iOS.
- Validar envio do comando `wifi_connect|SSID|PASSWORD` para o K.O.R.E. OS via BLE.
- Validar resposta do firmware.
- Validar em hardware real utilizando um dispositivo iOS e o K.O.R.E. OS.
- Comprovar, por meio de logs ou evidências, que as configurações foram persistidas corretamente e que os comandos enviados ao firmware foram recebidos e processados.
- Apresentar o resultado para validação.

Não iniciar o próximo Harness sem aprovação explícita do usuário.