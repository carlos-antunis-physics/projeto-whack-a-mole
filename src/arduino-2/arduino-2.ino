/*
 * Software: Jogador 2 do Jogo da Marmota
 *
 * Criado em: 02 - Jun - 2025
 *
 * Autores:
 *   Carlos, Filipe, Flavia, Giovanna, Lucitania e Mirian.
 *
 * Descrição:
 *   Este código implementa as funcionalidades do lado do jogador 2 do jogo da marmota
 *   bem como sua comunicação com o outro jogador. Ela inclui métodos de comunicação e
 *   controle mútuo de pontuações. O código aqui fornecido foi projetado com fins edu-
 *   cacionais - não o utilize para fins de produção.
 *
 * Copyright (C) 2025 Carlos, Filipe, Flavia, Giovanna, Lucitania e Mirian.
 */

#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

//  pino dos botoes
unsigned int pinoBotao[4] = {A1, A2, A3, A4};

//  pino dos leds
unsigned int pinoLed[44] = {4,5,3,2};

//  pino do buzzer
unsigned int pinoBuzzer = 6;

//  conexao serial entre arduinos
SoftwareSerial link(11, 10);
//  display de cristal liquido
LiquidCrystal_I2C lcd(0x27, 16, 2);

//  tempo maximo de uma partida
const unsigned long int tempoMaximo = 60000 /*ms*/;
//  tempo maximo de espera de um botao
const unsigned long int tempoBotao = 2000 /*ms*/;

//  índice de jogador em arrays
enum indiceJogador
{
  jogador = 0,
  adversario
};

//  modos de jogo
enum modosJogo
{
  DESLIGADO = 0,
  TRADICIONAL,
  PROGRESSIVO
};

//  botoes
enum botao
{
  NENHUM = -1,
  AZUL,
  VERDE,
  AMARELO,
  VERMELHO
};

//  informação de prontidão do jogador
const bool PRONTO = true;

//  modo de jogo escolhido nos arduinos
unsigned int modo[2] = {DESLIGADO, DESLIGADO};

//  função que computa o botão pressionado
int botaoPressionado();

//  metodo para tocar som de acerto
void somAcerto();
//  metodo para tocar som de erro
void somErro();

//  protocolo de conexao entre arduinos
void inicializarArduinos();

//  escolher modo de jogo
void escolherModo();

//  inicializar jogo
void iniciarJogo();

//  jogo tradicional com 2 jogadores
void jogoTradicional2P();
//  jogo progressivo com 2 jogadores
void jogoProgressivo2P();

/*===================================================================================
                                  Rotinas de execucao
===================================================================================*/

void setup()
{
  inicializarArduinos();
  escolherModo();
  iniciarJogo();
}

void loop()
{
  //  Não executa nada - existem 6 loops principais possíveis implementados noutras
  //  partes do código, dependendo do modo de jogo escolhido.
}

/*===================================================================================
                                  Funções auxiliares
===================================================================================*/

int botaoPressionado()
{
  bool ehAzul = digitalRead(pinoBotao[AZUL]) == LOW;
  bool ehVermelho = digitalRead(pinoBotao[VERMELHO]) == LOW;
  bool ehAmarelo = digitalRead(pinoBotao[AMARELO]) == LOW;
  bool ehVerde = digitalRead(pinoBotao[VERDE]) == LOW;

  if (ehAzul && !ehVermelho && !ehAmarelo && !ehVerde)
    return AZUL;
  else if (!ehAzul && ehVermelho && !ehAmarelo && !ehVerde)
    return VERMELHO;
  else if (!ehAzul && !ehVermelho && ehAmarelo && !ehVerde)
    return AMARELO;
  else if (!ehAzul && !ehVermelho && !ehAmarelo && ehVerde)
    return VERDE;
  digitalWrite(LED_BUILTIN, HIGH);
  return NENHUM;
}

void somAcerto() {
  int divider, noteDuration;
  tone(pinoBuzzer, NOTE_A1, 100);
}

void somErro() {
  int divider, noteDuration;
  tone(pinoBuzzer, NOTE_G4, 100);
}

void inicializarArduinos()
{
  pinMode(LED_BUILTIN, OUTPUT);
  //  inicializar conexao entre arduinos
  link.begin(9600);
  link.write(PRONTO);
  while (!link.available())
  { /*aguarde*/
  }
  int resposta = link.read();
  //  inicializar display lcd
  lcd.init();
  lcd.backlight();
  //  inicializar buzzer
  pinMode(pinoBuzzer, OUTPUT);
  //  inicializar botoes e leds
  for (int i = 0; i < 4; i++)
  {
    pinMode(pinoBotao[i], INPUT_PULLUP);
    pinMode(pinoLed[i], OUTPUT);
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void escolherModo()
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("aguardando");
  lcd.setCursor(1, 1);
  lcd.print("adversario ...");
  while (!link.available()) {/*aguarde*/}
  modo[adversario] = link.read();

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("pronto");
  lcd.setCursor(3, 1);
  lcd.print("jogador 2?");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("escolha um modo");
  lcd.setCursor(4, 1);
  lcd.print("de jogo:");
  delay(2000);

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("[amarelo]");
  lcd.setCursor(5, 1);
  lcd.print("aceitar");
  delay(2000);

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("[verde]");
  lcd.setCursor(5, 1);
  lcd.print("aceitar");
  delay(2000);

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("[azul]");
  lcd.setCursor(5, 1);
  lcd.print("aceitar");
  delay(2000);

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("[vermelho]");
  lcd.setCursor(4, 1);
  lcd.print("1 jogador");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("escolha um modo");
  lcd.setCursor(4, 1);
  lcd.print("de jogo");

  int botao = NENHUM;
  while (botao == NENHUM)
  {
    botao = botaoPressionado();
  }

  if (botao == VERMELHO)
  {
    modo[jogador] = DESLIGADO;
  }
  else
  {
    modo[jogador] = modo[adversario];
  }

  link.write(modo[jogador]);
}

void iniciarJogo()
{
  if (modo[jogador] == DESLIGADO)
  {
    lcd.noBacklight();
    return;
  }

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Esmague a");
  lcd.setCursor(5, 1);
  lcd.print("marmota!");
  delay(1500);

  switch (modo[jogador])
  {
  case TRADICIONAL:
    jogoTradicional2P();
    break;
  case PROGRESSIVO:
    jogoProgressivo2P();
    break;
  }

  lcd.noBacklight();
}

void jogoTradicional2P()
{
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("modo");
  lcd.setCursor(3, 1);
  lcd.print("tradicional");
  delay(1500);

  int pontuacao[2] = {0, 0};
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Pontuacao");
  lcd.setCursor(7, 1);
  lcd.print("0");
  delay(100);

  //  enquanto houver tempo execute o jogo
  char pontuacaoString[16];
  bool acertou;
  int botaoEscolhido;
  while (!link.available()) {/*aguarde*/}
  link.read();
  link.write(PRONTO);
  unsigned long int tTurno, tempoInicial = millis();
  while (millis() - tempoInicial < tempoMaximo) {
    //  escolher um botão aleatório
    botaoEscolhido = random(0, 3);
    digitalWrite(pinoLed[botaoEscolhido], HIGH);
    acertou = false;

    //  aguardar o jogador pressionar o botão
    digitalWrite(LED_BUILTIN, HIGH);
    tTurno = millis();
    while (millis() - tTurno < tempoBotao) {
      //  se o botao pressionado for o sorteado
      if (botaoPressionado() == botaoEscolhido) {
        acertou = true;
        pontuacao[0] += 1;
        somAcerto();
        digitalWrite(LED_BUILTIN, LOW);
        break;
      }
    }
    //  se o botao sorteado nao foi pressionado
    if (!acertou) {
      somErro();
    } else {
      sprintf(pontuacaoString, "%d", pontuacao[0]);
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Pontuacao");
      lcd.setCursor(7, 1);
      lcd.print(pontuacaoString);
    }
    digitalWrite(pinoLed[botaoEscolhido], LOW);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tempo esgotado!");
  lcd.setCursor(3, 1);
  lcd.print("Fim de jogo");
  delay(1500);
  
  while (!link.available()) {/*aguarde*/}
  pontuacao[1] = link.read();
  link.write(pontuacao[0]);

  if (pontuacao[0] == pontuacao[1]) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("EMPATE");
    lcd.setCursor(4, 1);
    lcd.print("Parabens!");
    delay(2000);
  } else if (pontuacao[0] > pontuacao[1]) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("VITORIA");
    lcd.setCursor(4, 1);
    lcd.print("Parabens!");
    delay(2000);
  } else {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("DERROTA");
    lcd.setCursor(2, 1);
    lcd.print("Triste! ;--;");
    delay(2000);
  }
}

void jogoProgressivo2P()
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("modo versus");
  lcd.setCursor(3, 1);
  lcd.print("progressivo");
  delay(1500);

  int pontuacao[2] = {0, 0};
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Pontuacao");
  lcd.setCursor(7, 1);
  lcd.print("0");
  delay(100);

  //  enquanto houver tempo execute o jogo
  char pontuacaoString[16];
  bool acertou;
  int botaoEscolhido;
  unsigned long tempoBotaoProgresivo = tempoBotao;
  while (!link.available()) {/*aguarde*/}
  link.read();
  link.write(PRONTO);
  unsigned long int tTurno, tempoInicial = millis();
  while (millis() - tempoInicial < tempoMaximo) {
    //  escolher um botão aleatório
    botaoEscolhido = random(0, 3);
    digitalWrite(pinoLed[botaoEscolhido], HIGH);
    acertou = false;

    //  aguardar o jogador pressionar o botão
    digitalWrite(LED_BUILTIN, HIGH);
    tTurno = millis();
    while (millis() - tTurno < tempoBotaoProgresivo) {
      //  se o botao pressionado for o sorteado
      if (botaoPressionado() == botaoEscolhido) {
        acertou = true;
        pontuacao[0] += 1;
        somAcerto();
        digitalWrite(LED_BUILTIN, LOW);
        if (tempoBotaoProgresivo > 1000u /*ms*/) {
          tempoBotaoProgresivo -= 100u /*ms*/;//  diminuir o tempo de espera
        } else if (tempoBotaoProgresivo > 500u /*ms*/) {
          tempoBotaoProgresivo -= 50u /*ms*/; //  diminuir o tempo de espera
        }
        break;
      }
    }
    //  se o botao sorteado nao foi pressionado
    if (!acertou) {
      somErro();
    } else {
      sprintf(pontuacaoString, "%d", pontuacao[0]);
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Pontuacao");
      lcd.setCursor(7, 1);
      lcd.print(pontuacaoString);
    }
    digitalWrite(pinoLed[botaoEscolhido], LOW);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tempo esgotado!");
  lcd.setCursor(3, 1);
  lcd.print("Fim de jogo");
  delay(1500);
  
  while (!link.available()) {/*aguarde*/}
  pontuacao[1] = link.read();
  link.write(pontuacao[0]);

  if (pontuacao[0] == pontuacao[1]) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("EMPATE");
    lcd.setCursor(4, 1);
    lcd.print("Parabens!");
    delay(2000);
  } else if (pontuacao[0] > pontuacao[1]) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("VITORIA");
    lcd.setCursor(4, 1);
    lcd.print("Parabens!");
    delay(2000);
  } else {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("DERROTA");
    lcd.setCursor(2, 1);
    lcd.print("Triste! ;--;");
    delay(2000);
  }
}