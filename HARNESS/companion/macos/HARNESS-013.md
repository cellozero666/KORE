# HARNESS-013 - Cleanup & Polish

## Objetivo

Preparar o K.O.R.E. Companion para sua primeira versão funcional, removendo código temporário, eliminando warnings de compilação, padronizando o branding da aplicação e realizando os ajustes finais de qualidade.

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/01_macos/

## Regras

- Não alterar a arquitetura definida nas ADRs.
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

- Nome do bundle (.app)
- Nome do DMG
- Nome exibido na barra da janela
- Nome exibido no Dock
- Nome exibido pelo Finder
- Nome exibido pelo Activity Monitor
- Demais pontos onde ainda aparecer "kore-companion"

## Entrega

Ao concluir o módulo:

- Garantir que `cargo build` compile sem warnings.
- Garantir que `npm run build` compile sem erros.
- Garantir que `npm run tauri build` gere o bundle corretamente.
- Validar que o aplicativo seja exibido como **K.O.R.E. Companion** em todo o macOS.
- Validar que não exista código temporário remanescente.
- Apresentar um relatório contendo:
  - arquivos modificados;
  - warnings removidos;
  - ajustes de branding realizados;
  - validações executadas.

Não iniciar o próximo Harness sem aprovação explícita do usuário.