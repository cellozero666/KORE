012_settings.md

Settings

Objetivo

Implementar a tela de configurações do K.O.R.E. Companion, permitindo configurar a localização utilizada pelo módulo Weather e os dados de conexão Wi-Fi do K.O.R.E. OS.

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
* 011_weather.md

⸻

Arquitetura

O frontend React é responsável apenas pela interface.

Toda persistência de configurações deverá ser realizada pelo Backend.

Fluxo:

React
    ↓
Backend (Rust/Tauri)
    ↓
Configuração Persistente

⸻

Seção “Location”

A tela deverá permitir dois modos de funcionamento.

Autodetect

Quando habilitado:

* A localização do usuário será obtida automaticamente.
* O módulo Weather utilizará esta localização.
* Os campos de País e Cidade permanecerão desabilitados.

⸻

Manual

Quando o Autodetect estiver desabilitado:

O usuário poderá selecionar:

* País
* Cidade

Estas informações serão utilizadas pelo módulo Weather para todas as consultas meteorológicas.

As configurações deverão permanecer salvas entre execuções da aplicação.

⸻

Seção “WiFi Settings”

A tela deverá conter:

* Campo SSID.
* Campo Password.
* Botão Connect WiFi.

Ao clicar no botão, o Companion deverá enviar para a ESP32:

wifi_connect|SSID|PASSWORD

Através da interface pública definida em 006_connection.md.

O Companion deverá aguardar a resposta do firmware para atualizar o estado da conexão Wi-Fi.

⸻

Persistência

As seguintes configurações deverão permanecer salvas:

* Autodetect habilitado/desabilitado.
* País.
* Cidade.

A senha do Wi-Fi não deverá permanecer armazenada após o envio.

⸻

Interface

A tela deverá conter duas seções:

Location

* Checkbox Autodetect Location.
* Seleção de País.
* Seleção de Cidade.
* Botão Save Location.

⸻

WiFi Settings

* Campo SSID.
* Campo Password.
* Botão Connect WiFi.

⸻

Não faz parte

* Gerenciamento de múltiplas redes Wi-Fi.
* Histórico de redes.
* Alteração de configurações do firmware.
* Configurações do Spotify.
* Configurações do Google.
* Configurações da aplicação.

⸻

Critérios de Aceitação

* O usuário pode habilitar ou desabilitar o modo Autodetect Location.
* O usuário pode selecionar País e Cidade quando o modo manual estiver ativo.
* As configurações de localização permanecem salvas entre execuções.
* O módulo Weather utiliza automaticamente a configuração salva.
* O usuário pode informar SSID e Password.
* O comando wifi_connect|SSID|PASSWORD é enviado corretamente para a ESP32 através da interface pública definida em 006_connection.md.
* O estado do Wi-Fi é atualizado conforme a resposta do firmware.
* O React permanece desacoplado da camada de comunicação e do armazenamento das configurações.