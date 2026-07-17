# 006_connection.md

# Connection

## Objetivo

Implementar a camada de comunicação entre o K.O.R.E. Companion e o K.O.R.E. OS, criando uma interface única, desacoplada e reutilizável para comunicação via Bluetooth Low Energy (BLE).

---

## Diretório de Trabalho

```
ROOT/COMPANION/ios/APP
```

Todo o desenvolvimento deste módulo deverá ocorrer exclusivamente neste diretório.

---

## Dependências

### SPECs

- 001_foundation.md
- 002_window.md
- 003_layout.md
- 004_navigation.md
- 005_state.md

---

## Arquitetura

A comunicação com o K.O.R.E. OS é responsabilidade exclusiva da camada nativa da aplicação.

A implementação deverá utilizar:

- Tauri
- Rust
- Swift (quando necessário para integração nativa com o iOS)

O frontend React nunca deverá acessar diretamente o Bluetooth Low Energy (BLE).

Todo acesso ao hardware deverá ocorrer através da camada de comunicação disponibilizada pelo backend.

Fluxo:

```text
React
    ↓
Tauri Commands
    ↓
Communication Layer
    ↓
BLE
    ↓
K.O.R.E. OS
```

O React apenas consome os estados e eventos disponibilizados pela camada de comunicação.

---

## Meio de Comunicação

O Companion deverá utilizar Bluetooth Low Energy (BLE) como meio de comunicação com o K.O.R.E. OS.

Toda a aplicação deverá utilizar uma interface pública única, sem conhecer detalhes da implementação da comunicação BLE.

---

## Fluxo de Inicialização

Ao iniciar o Companion, a aplicação deverá permanecer na tela de Loading criada na `003_layout.md`.

Durante este período, a camada de comunicação deverá:

1. Procurar dispositivos BLE compatíveis.
2. Tentar estabelecer a conexão BLE.
3. Executar o Handshake.

A tela de Loading somente poderá ser encerrada quando uma conexão válida com o K.O.R.E. OS for estabelecida.

Enquanto não existir uma conexão válida, a aplicação não deverá permitir acesso aos demais módulos.

Após o Handshake ser concluído com sucesso, a aplicação deverá navegar automaticamente para o Dashboard.

---

## Ordem de Conexão

Sempre que iniciar uma busca pelo dispositivo K.O.R.E., o Companion deverá seguir obrigatoriamente a seguinte ordem:

1. Procurar dispositivos BLE compatíveis.
2. Estabelecer a conexão.
3. Validar a conexão através do Handshake.
4. Somente após um Handshake válido a conexão será considerada estabelecida.

---

## Handshake

Após estabelecer uma conexão física, o Companion deverá validar o dispositivo.

Comando enviado:

```
ping
```

Resposta esperada:

```
KORE_COMPANION
```

Somente após receber esta resposta a conexão deverá ser considerada válida.

Caso contrário:

- a conexão deverá ser encerrada;
- o dispositivo deverá ser ignorado.

---

## Formato dos Comandos

Toda comunicação deverá utilizar mensagens de texto UTF-8.

Os parâmetros deverão utilizar o caractere `|` como delimitador.

Exemplos:

```text
ping
version
uptime
current_face
wifi_status
wifi_connect|SSID|PASSWORD
time|HH|MM|SS
spotify|...
spotify_stop
notification|...
weather|...
happy
extrahappy
sad
sleep
surprise
loving
confused
demon
```

Este formato deverá ser utilizado por todos os Companion Apps e pelo firmware.

---

## Interface Pública

A camada de comunicação deverá disponibilizar, no mínimo:

- Connect
- Disconnect
- Send
- Receive
- Connection Status

Toda comunicação do Companion com o firmware deverá ocorrer exclusivamente através desta interface.

---

## Escopo

- Implementar comunicação BLE.
- Detectar dispositivos compatíveis.
- Implementar conexão.
- Implementar desconexão.
- Implementar Handshake.
- Implementar envio de comandos.
- Implementar recebimento de mensagens.
- Atualizar o estado global da conexão.
- Emitir eventos para o frontend React.
- Implementar persistência de conexão APP -> ESP32.
- Reutilizar o máximo possível de código existente do Companion macOS localizado em `ROOT/COMPANION/macos/APP`, preservando a arquitetura e adaptando apenas o que for necessário para compatibilidade com iOS.

---

## Eventos

Estados mínimos da conexão:

- Disconnected
- Connecting
- Connected
- Error

---

## Não faz parte

- Regras de negócio.
- Dashboard.
- Spotify.
- Google.
- Weather.
- Configurações.
- Reconexão automática.
- Sincronização de dados.

---

## Critérios de Aceitação

- O Companion detecta dispositivos BLE.
- O Handshake utilizando `ping` funciona corretamente.
- Apenas dispositivos que respondem `KORE_COMPANION` são aceitos.
- O envio e recebimento de mensagens funciona corretamente.
- O React recebe os estados através da camada de comunicação.
- Nenhum componente React acessa diretamente o BLE.
- A camada de comunicação permanece desacoplada das regras de negócio.
- A arquitetura está preparada para os próximos módulos.