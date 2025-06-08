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

//  pino dos botoes
unsigned int pinoBotao[4] = {A1, A2, A3, A4};

//  pino dos leds
unsigned int pinoLed[44] = {9, 8, 7, 6};

//  pino do buzzer
unsigned int pinoBuzzer = 5;

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
  PROGRESSIVO,
  GENIUS
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
//  jogo genius com 2 jogadores
void jogoGenius2P();

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
  return VERMELHO; // NENHUM;
}

void somAcerto() {}

void somErro() {}

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
  while (!link.available())
  { /*aguarde*/
  }
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
  case GENIUS:
    jogoGenius2P();
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
}

void jogoProgressivo2P()
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("modo versus");
  lcd.setCursor(3, 1);
  lcd.print("progressivo");
  delay(1500);
}

void jogoGenius2P()
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("modo versus");
  lcd.setCursor(5, 1);
  lcd.print("genius");
  delay(1500);
}
