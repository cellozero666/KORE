002_window.md

Window

Objetivo

Configurar a janela principal do K.O.R.E. Companion para macOS utilizando os recursos nativos do Tauri, estabelecendo o comportamento padrão da aplicação.

⸻

Diretório de Trabalho

ROOT/COMPANION/macos

Todo o desenvolvimento deste módulo deverá ocorrer exclusivamente neste diretório.

⸻

Dependências

SPECs

* 001_foundation.md

⸻

Escopo

* Configurar a janela principal da aplicação.
* Definir o título da aplicação como K.O.R.E. Companion.
* Definir o tamanho inicial da janela:
    * Width: 900 px
    * Height: 700 px
* Definir dimensões mínimas da janela.
* Configurar a janela como redimensionável.
* Configurar o comportamento ao iniciar a aplicação.
* Configurar o comportamento ao fechar a janela.
* Configurar o foco da janela.
* Configurar suporte ao modo escuro do macOS.
* Preparar a janela para futuras integrações com Tray, Deep Links e notificações.

⸻

Não faz parte

* Interface gráfica.
* Layout.
* Navegação.
* Tray Icon.
* Menu Bar.
* Atalhos globais.
* Persistência da posição e tamanho da janela.
* Comunicação com o firmware.

⸻

Critérios de Aceitação

* A aplicação inicia corretamente.
* A janela principal é exibida sem erros.
* O título da aplicação é K.O.R.E. Companion.
* A janela inicia com 900 x 700 px.
* A janela não pode ser redimensionada.
* O ícone da aplicação está configurado.
* O comportamento de abertura e fechamento funciona corretamente.
* O projeto permanece pronto para evolução dos próximos módulos.