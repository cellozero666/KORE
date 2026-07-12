# 011_weather.md

# Weather

## Objetivo

Implementar a integração com o serviço de previsão do tempo, permitindo exibir as condições climáticas no Companion e enviar periodicamente as informações para o K.O.R.E. OS.

---

## Diretório de Trabalho

ROOT/COMPANION/macos

Todo o desenvolvimento deste módulo deverá ocorrer exclusivamente neste diretório.

---

## Dependências

### SPECs

- 001_foundation.md
- 002_window.md
- 003_layout.md
- 004_navigation.md
- 005_state.md
- 006_connection.md

---

# Serviço Meteorológico

O Companion utilizará obrigatoriamente a API **Open-Meteo** como provedor oficial de dados meteorológicos.

Endpoint:

```
https://api.open-meteo.com/v1/forecast
```

Consulta padrão:

```
current=temperature_2m,weather_code
daily=temperature_2m_max,temperature_2m_min
timezone=auto
```

As consultas deverão ser realizadas utilizando latitude e longitude.

Nenhuma outra API meteorológica deverá ser utilizada sem autorização explícita.

---

# Localização

O módulo deverá possuir dois modos de funcionamento.

## Cidade Manual

Caso exista uma cidade configurada em **Settings**, esta deverá ser utilizada para todas as consultas.

O Backend utilizará:

- Cidade
- Latitude
- Longitude

armazenadas nas configurações da aplicação.

---

## Localização Automática

Caso nenhuma cidade esteja configurada, o Backend deverá obter automaticamente a localização do usuário utilizando:

```
https://ipinfo.io/json
```

A resposta deverá fornecer:

- Cidade
- Latitude
- Longitude

As coordenadas obtidas deverão ser utilizadas para consultar a API Open-Meteo.

---

# Arquitetura

Toda a integração com o serviço de clima é responsabilidade da camada nativa da aplicação.

A implementação deverá utilizar:

- Tauri
- Rust
- Swift (quando necessário)

Fluxo:

```
IPInfo
      ↓
Open-Meteo
      ↓
Backend (Rust/Tauri)
      ↓
State Global
      ↓
React
```

O Backend é responsável por:

- Obter a localização.
- Consultar a API Open-Meteo.
- Converter weather_code para o índice utilizado pelo firmware.
- Atualizar o State Global.
- Enviar informações para a ESP32.

O React é responsável apenas por exibir os dados.

O React nunca deverá acessar diretamente qualquer API externa.

---

# Watcher

O Backend deverá manter um watcher permanente.

A API Open-Meteo deverá ser consultada a cada **20 minutos**.

Além disso:

- ao carregar a tela Weather;
- sempre que houver alteração nas informações meteorológicas;
- obrigatoriamente a cada **1 hora**;

o Backend deverá sincronizar os dados com o firmware.

---

# Comunicação com o Firmware

Ao carregar a tela Weather, o Backend deverá enviar imediatamente:

```
weather|CITY|TEMP|HITEMP|LOWTEMP|ICON
```

Onde:

- CITY → Nome da cidade.
- TEMP → Temperatura atual (°C).
- HITEMP → Temperatura máxima do dia (°C).
- LOWTEMP → Temperatura mínima do dia (°C).
- ICON → Índice do ícone utilizado pelo firmware.

---

# Conversão de Ícones

O Backend deverá converter o `weather_code` retornado pelo Open-Meteo para o índice utilizado pelo firmware.

Tabela oficial:

| Weather Code | Firmware |
|--------------|----------|
| 0 | 5 (Sun) |
| 1–3 | 1 (Partly Cloud) |
| 4–48 | 0 (Cloud) |
| 49–67 | 2 (Rain) |
| 68–77 | 3 (Snow) |
| 78+ | 4 (Storm) |

Esta conversão é considerada a implementação oficial do Companion.

---

# Otimização de Sincronização

O Backend deverá manter internamente o último payload enviado ao firmware.

Sempre que uma nova consulta meteorológica for realizada:

- se o payload for diferente do anterior, o comando deverá ser enviado imediatamente;
- se o payload for idêntico, o envio poderá ser ignorado.

Esta otimização não elimina o envio obrigatório realizado a cada 1 hora.

---

# Interface

A tela deverá exibir:

- Cidade.
- Temperatura atual.
- Condição climática.
- Temperatura máxima.
- Temperatura mínima.
- Horário da última atualização.

---

# Não faz parte

- Previsão para vários dias.
- Radar meteorológico.
- Umidade.
- Pressão atmosférica.
- Velocidade do vento.
- Qualidade do ar.
- Alertas meteorológicos.

---

# Critérios de Aceitação

- O Backend obtém corretamente a localização do usuário ou utiliza a cidade configurada em Settings.
- O Backend consulta exclusivamente a API Open-Meteo.
- O Backend utiliza IPInfo quando a localização automática estiver habilitada.
- O React nunca acessa diretamente qualquer API externa.
- O Backend mantém o State Global atualizado.
- O React atualiza automaticamente a interface através do State Global.
- A tela exibe corretamente cidade, temperatura, condição climática, máxima, mínima e horário da última atualização.
- O comando `weather|CITY|TEMP|HITEMP|LOWTEMP|ICON` é enviado ao carregar a tela Weather.
- O comando é reenviado automaticamente quando houver alteração nas informações meteorológicas.
- O comando é reenviado obrigatoriamente a cada 1 hora, mesmo que não exista alteração nos dados.
- A conversão de `weather_code` para `ICON` segue exatamente a tabela oficial definida nesta SPEC.
- O módulo permanece desacoplado da interface e da camada de comunicação definida em `006_connection.md`.