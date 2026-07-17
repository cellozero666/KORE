# HARNESS-013 - Cleanup & Polish

## Objetivo

Preparar o K.O.R.E. Companion para sua primeira versão funcional, removendo código temporário, eliminando warnings de compilação, padronizando o branding da aplicação e realizando os ajustes finais de qualidade.

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/02_ios/

## Regras

- Não alterar a arquitetura definida nas ADRs.
- Reutilizar o máximo possível de código existente do Companion macOS localizado em `ROOT/COMPANION/macos/APP`, preservando a arquitetura e adaptando apenas o que for necessário para compatibilidade com iOS.
- Não adicionar novas funcionalidades.
- Apenas realizar ajustes de qualidade, acabamento e manutenção.
- Todo código temporário utilizado durante os Harnesses anteriores deverá ser removido.

## Escopo

- Remover todos os warnings de compilação.
- Remover funções, constantes e código morto não utilizados.
- Remover logs e instrumentações temporárias utilizadas durante os testes.
- Garantir que o projeto compile sem warnings.

### Branding

Padronizar o nome da aplicação em todo o projeto para:

```
K.O.R.E. Companion
```

Isso inclui:

- Nome do aplicativo no iOS.
- Nome exibido na Tela Inicial (Home Screen).
- Nome exibido em Ajustes > Apps.
- Nome exibido durante a instalação e execução.
- Nome do bundle gerado para distribuição.
- Demais pontos onde ainda aparecer "kore-companion".

## Entrega

Ao concluir o módulo:

- Garantir que `cargo build` compile sem warnings.
- Garantir que `npm run build` compile sem erros.
- Garantir que `npm run tauri ios build` gere o aplicativo corretamente.
- Validar que o aplicativo seja exibido como **K.O.R.E. Companion** em todo o iOS.
- Validar que não exista código temporário remanescente.
- Validar em dispositivo iOS real sempre que aplicável.
- Apresentar um relatório contendo:
  - arquivos modificados;
  - warnings removidos;
  - ajustes de branding realizados;
  - validações executadas.

Não iniciar o próximo Harness sem aprovação explícita do usuário.