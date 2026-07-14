009_spotify.md

Spotify

Objetivo

Implementar a integração completa com a API do Spotify, permitindo autenticação do usuário, controle da reprodução, sincronização com o K.O.R.E. OS e exibição das informações da reprodução no Companion.

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

Configuração

As credenciais da API do Spotify deverão ser armazenadas exclusivamente em:

/src-tauri/config/config.rs

O arquivo deverá conter:

* SPOTIFY_CLIENT_ID
* SPOTIFY_CLIENT_SECRET
* SPOTIFY_REDIRECT_URI

O arquivo deverá estar presente no .gitignore.

Não utilizar .env ou arquivos de configuração externos.

Os dados das variáveis serão abastecidos pelo usuário no arquivo citado.

⸻

Redirect URI

O Spotify deverá utilizar obrigatoriamente:

kore://callback

Devido a esta limitação, os testes de autenticação deverão ser realizados apenas utilizando a aplicação compilada.

O fluxo OAuth não deverá ser considerado funcional durante npm run tauri dev.

⸻

Arquitetura

Toda a integração com o Spotify é responsabilidade da camada nativa da aplicação.

A implementação deverá utilizar:

* Tauri
* Rust
* Swift (quando necessário)

O frontend React nunca deverá acessar diretamente a API do Spotify.

Fluxo:

Spotify API
        ↓
Backend (Rust/Tauri)
        ↓
State Global
        ↓
React

O Backend é responsável por:

* Login OAuth.
* Refresh Token.
* Renovação automática da sessão.
* Monitoramento da reprodução.
* Controles do player.
* Sincronização com a ESP32.
* Atualização do State Global.

O React é responsável apenas por:

* Exibir os dados.
* Solicitar conexão/desconexão.
* Solicitar comandos do player.
* Atualizar a interface através do State Global.

⸻

Watcher

O Backend deverá manter um monitoramento contínuo da reprodução do Spotify.

Sempre que houver alteração de estado, o State Global deverá ser atualizado automaticamente.

O React deverá manter um watcher do State Global para atualizar a interface em tempo real.

⸻

Sincronização com o Firmware

Enquanto existir uma música sendo reproduzida, o Backend deverá enviar automaticamente para a ESP32 o comando:

spotify|TRACK|ARTIST|ALBUM|PROGRESS|DURATION

Onde:

* TRACK → Nome da música.
* ARTIST → Nome do artista.
* ALBUM → Nome do álbum.
* PROGRESS → Tempo atual da reprodução em milissegundos.
* DURATION → Duração total da música em milissegundos.

A sincronização deverá ocorrer:

* imediatamente ao iniciar uma nova música;
* imediatamente ao alterar a música;
* a cada 5 segundos durante a reprodução.

Ao finalizar a reprodução, deverá ser enviado:

spotify_stop

⸻

Interface

A tela deverá exibir:

Conta

* Ícone do Spotify.
* Estado da conexão.
* Foto do perfil.
* Nome do usuário.

O ícone deverá permitir:

* Conectar.
* Desconectar.

Estados:

* Verde → conectado.
* Vermelho → desconectado.

⸻

Reprodução

Exibir:

* Capa do álbum.
* Nome da música.
* Nome do artista.
* Nome do álbum.

⸻

Progresso

Exibir:

* Barra de progresso.
* Tempo atual.
* Tempo total.

A barra deverá ser atualizada continuamente através do State Global.

⸻

Controles

Disponibilizar:

* Play.
* Pause.
* Previous / Rewind.
* Next.

Todos os comandos deverão ser enviados ao Backend.

O Backend será responsável por comunicar-se com a API do Spotify.

⸻

Não faz parte

* Playlist.
* Busca.
* Biblioteca.
* Controle de volume.
* Shuffle.
* Repeat.
* Letras.
* Recomendações.

⸻

Critérios de Aceitação

* O usuário consegue conectar ao Spotify.
* A sessão permanece autenticada utilizando Refresh Token.
* O React nunca acessa diretamente a API do Spotify.
* O Backend mantém o State Global atualizado.
* O React atualiza automaticamente a interface através do State Global.
* O perfil do usuário é exibido corretamente.
* A reprodução atual é exibida corretamente.
* Os controles Play, Pause, Previous e Next funcionam corretamente.
* O Backend envia spotify|TRACK|ARTIST|ALBUM|PROGRESS|DURATION para a ESP32 ao iniciar uma música, ao trocar de música e a cada 5 segundos durante a reprodução, utilizando PROGRESS e DURATION em milissegundos.
* O comando spotify_stop é enviado quando não existir reprodução ativa.
* O módulo permanece desacoplado da interface e da camada de comunicação definida em 006_connection.md.