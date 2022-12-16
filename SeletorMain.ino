                  /*Placa Seletora 2
                   Thinger.io login:
            email: grupo2tcc2022senai@gmail.com
                   senha: senai2016+
                  */


//Bibliotecas do projeto
#include "Arduino.h"  //Biblioteca do Arduino
#include <WiFi.h>
#include <ThingerESP32.h>

//Definição dos pinos dos LED's
#define LEDS1  27     //Define o pino 27 como LED Seleção 1
#define LEDS2  14     //Define o pino 14 como LED Seleção 2
#define LEDS3  12     //Define o pino 12 como LED Seleção 3
#define LEDS4  13     //Define o pino 13 como LED Seleção 4
#define LEDS5   0     //Define o pino 15 como LED Seleção 5
#define LEDST1  2     //Define o pino 0 como LED Status
#define DHTPIN 21     //Define o pino 21 como SDA do DHT

//Definição dos pinos das MV's do processo
#define PT         36 //Define o pino 36 como PT
#define MV_YEW     39 //Define o pino 39 como MV_YEW150
#define MV_S71200  34 //Define o pino 34 como MV_S71200
#define MV_ARDUINO 35 //Define o pino 35 como MV_ARDUINO
#define MV_ESP32   32 //Define o pino 32 como MV_ESP32
#define MV_RASP    33 //Define o pino 33 como MV_RASP

//Definição dos pinos das PV's do processo
#define PV_YEW      21 //Define o pino 21 como PV_YEW
#define PV_ARDUINOS 19 //Define o pino 19 como PV_ARDUINOS
#define PV_ESP32S   18 //Define o pino 18 como PV_ESP32S
#define PV_RASPS     5 //Define o pino 5  como PV_RASPS
#define PV_VALVULA  17 //Define o pino 17 como PV_VALVULA

//Variáveis para média da leitura das entradas analógicas
unsigned long int tA  = 0;  //Armazena o tempo anterior do millis do led pisca
const int numReadings  = 10;
int readings [numReadings];
int readIndex  = 0;

const int numReadings1  = 10;
int readings1 [numReadings1];
int readIndex1  = 0;

const int numReadings2  = 10;
int readings2 [numReadings2];
int readIndex2  = 0;

const int numReadings3  = 10;
int readings3 [numReadings3];
int readIndex3  = 0;

const int numReadings4  = 10;
int readings4 [numReadings4];
int readIndex4  = 0;

const int numReadings5  = 10;
int readings5 [numReadings5];
int readIndex5  = 0;

//Váriaveis para guardar a leitura das entradas analógicas
int MV_YEWM     = 0; //Armazena o valor lido na entrada MV_YEW150M
int MV_S71200M  = 0; //Armazena o valor lido na entrada MV_S71200M
int MV_ARDUINOM = 0; //Armazena o valor lido na entrada MV_ARDUINOM
int MV_ESP32M   = 0; //Armazena o valor lido na entrada MV_ESP32M
int MV_RASPM    = 0; //Armazena o valor lido na entrada MV_RASPM
int aisVal  = 0;

//Váriaveis para o funcionamento do touch
int touchValue;     //Valor lido no touch
int tP       = 500; //Tempo para o pisca do LED
int contarT0 = 0;   //Váriavel que conta os acionamentos do touch
long TB      = 0;   //Variável que armazena o tempo anterior do millis no touch
long TR      = 0;   //Variável que armazena o tempo anterior do millis no touch
long T       = 0;   //Variável que armazena o millis no touch
long total   = 0;   //Variável que armazena o total
long total1   = 0;   //Variável que armazena o total
long total2   = 0;   //Variável que armazena o total
long total3   = 0;   //Variável que armazena o total
long total4   = 0;   //Variável que armazena o total
long total5   = 0;   //Variável que armazena o total
bool TAC;           //Armazena o estado atual para evitar multiplas contagens
bool BT;            //Armazena o estado do botão
bool eL = false;    //Armazena o estado do LEDST1

//CD600
float cValvula;
float Fator;
float ZeroE;
float ZeroS;
//ARDUINO
float cValvula1;
float Fator1;
float ZeroE1;
float ZeroS1;
//ESP32
float cValvula2;
float Fator2;
float ZeroE2;
float ZeroS2;
//RASPB
float cValvula3;
float Fator3;
float ZeroE3;
float ZeroS3;
//VALVULA
float cValvula4;
float Fator4;
float ZeroE4;
float ZeroS4;

//Configurações para conexão com a rede WiFi
//const char* ssid     = "AAPM_A";
//const char* password = "";

//Equação CD600 e PT PV

float ganho1 = 0.8415;
float zeroE1 = 535;
float zeroS1 = 630.4545;

//Equação ESP E RASP PV

float ganho2 = 1.000007;
float zeroE2 = 535.00;
float zeroS2 = 744.4545;

//Equação Arduino PV
float ganho3 = 0.93;
float zeroE3 = 535.00;
float zeroS3 = 372.2727;
/////////////////////////////////
//Equação CD600 e S71200 saida V

float ganho4 = 0.95;
float zeroE4 = 576.00;
float zeroS4 = 695.4545;

//Equação ARDUINO
float ganho5 = 1.1230;
float zeroE5 = 272.00;
float zeroS5 = 620.4545;

//Equação ESP32 e RASPB
float ganho6 = 0.777;
float zeroE6 = 528.00;
float zeroS6 = 620.4545;

float ganho7 = 1.33;
float zeroE7 = 570.00;
float zeroS7 = 620.4545;

//CD600
int Valvula;
//ARDUINO
int Valvula1;
//ESP32
int Valvula2;
//RASPB
int Valvula3;
//VALVULA
int Valvula4;

//SINAL 4 a 20 mA da válvula
float PTV;

//Configurações para conexão com o Thinger.IO
//#define USERNAME "GRUPO2TCC"
//#define DEVICE_ID "Seletor"
//#define DEVICE_CREDENTIAL "agIj$PCsjny#dCL?"

//ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  /*
  Serial.begin(9600);  //Boundrate do serial
  delay(1000);         // Tempo para subir o serial
  Serial.println("SC2201 - Seletor de controle: monitor serial.");
  
  //Conexão da rede WiFi
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  Serial.println("Rede WiFi conectada");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());  
  */
  //Definição das saídas
  pinMode(PT,         INPUT);
  pinMode(MV_YEW,     INPUT);
  pinMode(MV_S71200,  INPUT);
  pinMode(MV_ARDUINO, INPUT);
  pinMode(MV_ESP32,   INPUT);
  pinMode(MV_RASP,    INPUT);
  pinMode(25,         OUTPUT);
  pinMode(LEDS1,      OUTPUT);                //Define LEDS1 como saída
  pinMode(LEDS2,      OUTPUT);                //Define LEDS2 como saída
  pinMode(LEDS3,      OUTPUT);                //Define LEDS3 como saída
  pinMode(LEDS4,      OUTPUT);                //Define LEDS4 como saída
  pinMode(LEDS5,      OUTPUT);                //Define LEDS5 como saída
  pinMode(LEDST1,     OUTPUT);                //Define LEDST1 como saída
  pinMode(2,          OUTPUT);                //Define o pino 2 (LED) como saída
  /*
  thing["BOTP"]      << digitalPin(25);
  thing["LEDS1T"]    >> outputValue(digitalRead(LEDS1));
  thing["LEDS2T"]    >> outputValue(digitalRead(LEDS2));
  thing["LEDS3T"]    >> outputValue(digitalRead(LEDS3));
  thing["LEDS4T"]    >> outputValue(digitalRead(LEDS4));
  thing["LEDS5T"]    >> outputValue(digitalRead(LEDS5));
  thing["LEDST1T"]   >> outputValue(digitalRead(LEDST1));
  thing["analogica"] >> [](pson & out){
    out = (smooth() - 734.61) * 0.0099999 + 1.950;
  };
  thing["analogica1"] >> [](pson & out){
    out = Valvula * (3.30 / 4095);
  };
  thing["analogica2"] >> [](pson & out){
    out = Valvula1 * (3.30 / 4095);
  };
  thing["analogica3"] >> [](pson & out){
    out = Valvula2 * (3.30 / 4095);
  };
  thing["analogica4"] >> [](pson & out){
    out = Valvula3 * (3.30 / 4095);
  };  
   thing["analogica5"] >> [](pson & out){
    out = Valvula4 * (20 / 3447.2454);
  }; 
  */
  analogReadResolution(12);                   //Define a resolução da leitura da entrada para 12bits
  analogSetPinAttenuation(PT, ADC_11db);       //Define a atenuação da leitura da entrada
  analogSetPinAttenuation(MV_YEW, ADC_11db);       //Define a atenuação da leitura da entrada
  analogSetPinAttenuation(MV_S71200, ADC_11db);       //Define a atenuação da leitura da entrada
  analogSetPinAttenuation(MV_ARDUINO, ADC_11db);       //Define a atenuação da leitura da entrada
  analogSetPinAttenuation(MV_ESP32, ADC_11db);       //Define a atenuação da leitura da entrada
  analogSetPinAttenuation(MV_RASP, ADC_11db);       //Define a atenuação da leitura da entrada

  ledcAttachPin(21, 0);    //Atribui o pino 19 ao canal 0.
  ledcSetup(0, 1000, 12);  //Atribui ao canal 0 a frequencia de 1000Hz com resolucao de 12bits.

  ledcAttachPin(19, 1);    //Atribui o pino 18 ao canal 1.
  ledcSetup(1, 1000, 12);  //Atribui ao canal 1 a frequencia de 1000Hz com resolucao de 12bits.

  ledcAttachPin(18, 2);     //Atribui o pino 5 ao canal 2.
  ledcSetup(2, 1000, 12);  //Atribui ao canal 2 a frequencia de 1000Hz com resolucao de 12bits.

  ledcAttachPin(5, 3);    //Atribui o pino 17 ao canal 3.
  ledcSetup(3, 1000, 12);  //Atribui ao canal 3 a frequencia de 1000Hz com resolucao de 12bits.

  ledcAttachPin(17, 4);    //Atribui o pino 16 ao canal 4.
  ledcSetup(4, 1000, 12);  //Atribui ao canal 4 a frequencia de 1000Hz com resolucao de 12bits.
}

//Loop

void loop() {
  //thing.handle();
  //readAnalogSmooth();  //Função para média da entrada analógica PT
  ledpisca();          //Inicia o pisca do LED de status
  touchacquisition();  //Inicia a acquisição do touch
  analogR();           //Inicia a acquisição de leitura da YEW150
  //Serial.println(MV_YEWM);
  //Serial.println(MV_S71200M);
  //Serial.println(MV_ARDUINOM);
  //Serial.println(MV_ESP32M);
  //Serial.println(MV_RASPM);

      //CD600
    cValvula =  smooth();
    Fator = ganho1;
    ZeroE = zeroE1;
    Valvula = ((cValvula - ZeroE) * Fator) + zeroS1;
    ledcWrite(0, Valvula);

    //ARDUINO
    cValvula1 = smooth();
    Fator1 = ganho3;
    ZeroE1 = zeroE3;
    Valvula1 = ((cValvula1 - ZeroE1) * Fator1) + zeroS3;
    ledcWrite(1, Valvula1);

    //ESP32
    cValvula2 = smooth();
    Fator2 = ganho2;
    ZeroE2 = zeroE2;
    Valvula2 = ((cValvula2 - ZeroE2) * Fator2) + zeroS2;
    ledcWrite(2, Valvula2);  

    //RASP
    cValvula3 = smooth();
    Fator3 = ganho2;
    ZeroE3 = zeroE2;
    Valvula3 = ((cValvula3 - ZeroE3) * Fator3) + zeroS2;
    ledcWrite(3, Valvula3);
    //Serial.println(smooth());

    
  if (contarT0 == 0) {
    leds1on();   
    //VALVULA(4 a 20mA)
    cValvula4 = MV_YEWM;
    Fator4 = ganho4;
    ZeroE4 = zeroE4;
    Valvula4 = ((cValvula4 - ZeroE4) * 0.985) + 350;
    if(Valvula4 > 0){
    //Serial.println(MV_YEWM);
    ledcWrite(4,Valvula4);
    }
  } else {
    leds1off();
  }

  if (contarT0 == 1) {
    leds2on();
    //VALVULA(4 a 20mA)
    cValvula4 = MV_S71200M;
    Fator4 = ganho4;
    ZeroE4 = zeroE4;
    Valvula4 = ((cValvula4 - ZeroE4) * 0.92) + zeroS4;
    //Serial.println(MV_S71200M);
    ledcWrite(4,Valvula4);
  } else {
    leds2off();
  }

  if (contarT0 == 2) {
    leds3on();
    //VALVULA(4 a 20mA)
    cValvula4 = MV_ARDUINOM;
    Fator4 = ganho5;
    ZeroE4 = zeroE5;
    Valvula4 = ((cValvula4 - ZeroE4) * Fator4) + zeroS5;
    //Serial.println(MV_ARDUINOM);
    ledcWrite(4,Valvula4);
  } else {
    leds3off();
  }

  if (contarT0 == 3) {
    leds4on();
    //VALVULA(4 a 20mA)
    cValvula4 = MV_ESP32M;
    Fator4 = ganho6;
    ZeroE4 = zeroE6;
    Valvula4 = ((cValvula4 - ZeroE4) * Fator4) + zeroS6;
    //Serial.println(MV_ESP32M);
    ledcWrite(4,Valvula4);
  } else {
    leds4off();
  }

  if (contarT0 == 4) {
    leds5on();
    //VALVULA(4 a 20mA)
    cValvula4 = MV_RASPM;
    Fator4 = ganho6;
    ZeroE4 = zeroE6;
    Valvula4 = ((cValvula4 - ZeroE4) * Fator4) + zeroS6;
    ledcWrite(4,Valvula4);
    //Serial.println(MV_RASPM);
  } else {
    leds5off();
  }
  
  if (contarT0 == 5) {
    contarT0 = 0;
  }

}
