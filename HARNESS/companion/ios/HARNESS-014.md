# HARNESS-014 - Stabilization & Optimization

## Objetivo

Executar uma auditoria técnica completa do Companion visando estabilidade, desempenho, qualidade de código e redução de complexidade, preservando integralmente o comportamento funcional da aplicação.

Este Harness NÃO implementa novas funcionalidades.

Seu objetivo é apenas melhorar a implementação existente.

---

## Referências

- PROJECT.md
- ADR/
- SPEC/companion/02_ios/
- Todo o código atual do Companion iOS

---

## Regras

É proibido:

- alterar regras de negócio;
- alterar arquitetura;
- alterar protocolos de comunicação;
- alterar fluxo de OAuth;
- alterar contratos públicos;
- alterar comunicação com o K.O.R.E. OS via BLE;
- remover funcionalidades.

- Reutilizar o máximo possível de código existente do Companion macOS localizado em `ROOT/COMPANION/macos/APP`, preservando a arquitetura e adaptando apenas o que for necessário para compatibilidade com iOS.

Toda otimização deverá preservar exatamente o comportamento atual.

Em caso de dúvida, preservar o comportamento existente.

---

## Escopo

Belthazar deverá realizar uma auditoria completa do projeto.

### 1. Performance

Analisar:

- loops desnecessários;
- polling excessivo;
- watchers;
- renderizações React;
- re-renderizações evitáveis;
- clonagens desnecessárias;
- alocações frequentes;
- bloqueios síncronos;
- uso de Mutex;
- uso de Arc;
- chamadas HTTP;
- serialização.

Sempre que possível:

- reduzir uso de CPU;
- reduzir uso de memória;
- reduzir chamadas desnecessárias.

---

### 2. Backend Rust

Revisar:

- ownership;
- clones;
- locks;
- async/await;
- uso de tokio;
- reqwest;
- tratamento de erros;
- Result;
- Option;
- logs.

Identificar:

- código duplicado;
- funções grandes;
- responsabilidades misturadas;
- oportunidades de simplificação.

---

### 3. Frontend React

Revisar:

- re-renderizações;
- useEffect;
- useMemo;
- useCallback;
- listeners;
- Stores;
- componentes.

Eliminar renderizações desnecessárias.

---

### 4. Comunicação

Revisar:

- CommunicationManager;
- BLE;
- filas;
- watchers;
- sincronizações.

Verificar:

- chamadas redundantes;
- payloads duplicados;
- envios desnecessários.

---

### 5. Memória

Verificar:

- vazamentos;
- listeners não removidos;
- timers;
- intervalos;
- tasks;
- threads.

---

### 6. Build

Eliminar:

- warnings;
- imports não utilizados;
- código morto;
- funções órfãs;
- constantes não utilizadas;
- módulos obsoletos.

---

### 7. Organização

Identificar:

- arquivos muito grandes;
- funções muito grandes;
- responsabilidades que podem ser separadas.

Somente refatorar quando não alterar comportamento.

---

### 8. Segurança

Revisar:

- armazenamento de tokens;
- tratamento de erros;
- logs sensíveis;
- credenciais.

---

### 9. UI

Validar:

- ausência de barras de rolagem;
- consistência visual;
- estados de interação;
- responsividade em diferentes tamanhos de tela suportados pelo iOS;
- comportamento em orientação portrait e landscape, quando aplicável.

Não alterar o Design System.

---

## Entrega

Ao concluir:

Apresentar um relatório contendo:

### Problemas encontrados

Classificados em:

- Crítico
- Alto
- Médio
- Baixo

---

### Melhorias implementadas

Listar:

- arquivo;
- motivo;
- impacto.

---

### Performance

Informar:

- otimizações realizadas;
- redução de chamadas;
- redução de renderizações;
- redução de alocações.

---

### Qualidade

Informar:

- código removido;
- duplicações eliminadas;
- warnings eliminados;
- simplificações realizadas.

---

### Validação

Executar obrigatoriamente:

- cargo build
- cargo clippy (quando aplicável)
- cargo fmt
- npm run build
- npm run tauri ios dev

Garantir:

- zero erros;
- zero regressões funcionais;
- comportamento idêntico ao aprovado pelo usuário.

Sempre que possível, validar também em dispositivo iOS real conectado ao K.O.R.E. OS.

---

## Critério de Aceitação

A aplicação deverá:

- manter exatamente o mesmo comportamento funcional;
- apresentar código mais limpo;
- reduzir complexidade onde possível;
- manter a arquitetura existente;
- permanecer 100% compatível com todas as SPECs aprovadas.

Nenhuma nova funcionalidade deverá ser implementada.

Não iniciar qualquer novo Harness sem aprovação explícita do usuário.