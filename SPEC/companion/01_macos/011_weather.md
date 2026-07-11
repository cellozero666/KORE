011_weather.md

Weather

Objetivo

Implementar a integração com o serviço de previsão do tempo, permitindo exibir as condições climáticas no Companion e enviar periodicamente as informações para o K.O.R.E. OS.

⸻

Diretório de Trabalho

ROOT/COMPANION/macos

Todo o desenvolvimento deste módulo deverá ocorrer exclusivamente neste diretório.

⸻

Dependências

SPECs

* 001_foundation.md
* 002_window.md
* 003_layout.md
* 004_navigation.md
* 005_state.md
* 006_connection.md

⸻

Arquitetura

Toda a integração com o serviço de clima é responsabilidade da camada nativa da aplicação.

A implementação deverá utilizar:

* Tauri
* Rust
* Swift (quando necessário)

O frontend React nunca deverá acessar diretamente a API de clima.

Fluxo:

Weather API
        ↓
Backend (Rust/Tauri)
        ↓
State Global
        ↓
React

O Backend é responsável por:

* Obter a localização.
* Consultar a API de clima.
* Atualizar o State Global.
* Enviar informações para a ESP32.

O React é responsável apenas por exibir os dados.

⸻

Localização

O módulo deverá possuir dois modos de funcionamento.

Cidade Manual

Caso exista uma cidade configurada em Settings, esta deverá ser utilizada para todas as consultas.

Localização Automática

Caso nenhuma cidade esteja configurada, o Backend deverá obter automaticamente a localização do usuário e utilizá-la para consultar a previsão do tempo.

⸻

Watcher

O Backend deverá manter um watcher permanente.

A previsão do tempo deverá ser atualizada a cada 20 minutos.

Independentemente disso, o firmware deverá receber uma atualização a cada 1 hora, mesmo que não exista alteração nas informações meteorológicas.

⸻

Comunicação com o Firmware

Ao carregar a tela Weather, o Backend deverá enviar imediatamente:

weather|CITY|TEMP|HITEMP|LOWTEMP|ICON

Onde:

* CITY → Nome da cidade.
* TEMP → Temperatura atual (°C).
* HITEMP → Temperatura máxima do dia (°C).
* LOWTEMP → Temperatura mínima do dia (°C).
* ICON → Índice do ícone utilizado pelo firmware.

Tabela de ícones:

Código ESP32	Ícone
0	Cloud
1	Partly Cloud
2	Rain
3	Snow
4	Storm
5	Sun

Além do envio inicial, o Backend deverá reenviar o comando automaticamente a cada 1 hora.

⸻

Interface

A tela deverá exibir:

* Cidade.
* Temperatura atual.
* Condição climática.
* Temperatura máxima.
* Temperatura mínima.
* Horário da última atualização.

⸻

Não faz parte

* Previsão para vários dias.
* Radar meteorológico.
* Umidade.
* Pressão atmosférica.
* Velocidade do vento.
* Qualidade do ar.
* Alertas meteorológicos.

⸻

Critérios de Aceitação

* O Backend obtém corretamente a localização do usuário ou utiliza a cidade configurada em Settings.
* O React nunca acessa diretamente a API de clima.
* O Backend mantém o State Global atualizado.
* O React atualiza automaticamente a interface através do State Global.
* A tela exibe corretamente cidade, temperatura, condição climática, máxima, mínima e horário da última atualização.
* O comando weather|CITY|TEMP|HITEMP|LOWTEMP|ICON é enviado ao carregar a tela Weather.
* O comando weather|CITY|TEMP|HITEMP|LOWTEMP|ICON é reenviado automaticamente a cada 1 hora.
* O módulo permanece desacoplado da interface e da camada de comunicação definida em 006_connection.md.