#include "LibL6470.hpp"
#include <SPI.h>  //(1)SPI通信をするための読み込み
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void Servi::servo_write(word n, word ang){
  ang = map(ang, 0, 180, Servomin, Servomax); //角度（0～180）をPWMのパルス幅（150～600）へ変換
  pwm.setPWM(n, 0, ang);
}

const bool buttonON=LOW;
const bool buttonOFF=HIGH;
const byte buttonPin=14;
const byte buttonPinR=15;
const byte mainswitch=16;
bool buttonstateL=true;
bool buttonstateR=true;
bool buttonstateM=false;
Servi servos;
Steps smor; //smor=Stepping MORtor
void setup()
{
 pwm.begin();
 pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates
 servos.servo_write(0,0);
  
  
  delay(1000);
  Serial.begin(9600);
   
  //(3)ステッピングモーター用のピンの準備
  pinMode(PIN_SPI_MOSI, OUTPUT);
  pinMode(PIN_SPI_MISO, INPUT);
  pinMode(PIN_SPI_SCK, OUTPUT);
  pinMode(PIN_SPI_SS, OUTPUT);
  pinMode(PIN_SPI_SS2, OUTPUT);
  digitalWrite(PIN_SPI_SS, HIGH);
  digitalWrite(PIN_SPI_SS2, HIGH);
  pinMode(14,  INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP); 
  pinMode(16, INPUT_PULLUP); 

  //(4)SPI通信の開始宣言
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);//SCKの立上りでテータを送受信、アイドル時はpinをHIGHに設定
  SPI.setBitOrder(MSBFIRST);//MSBから送信
  //(5)L6470の利用設定
  smor.L6470_setup();
  smor.L6470v2_setup();
}
 
//**********************************************
// (8)メイン処理 - loop()
//**********************************************
void loop(){
  buttonstateL=digitalRead(buttonPin);
  buttonstateR=digitalRead(buttonPinR);
  buttonstateM=digitalRead(mainswitch);
  
  while(buttonstateL){
      buttonstateL=digitalRead(buttonPin);
  }
  while(buttonstateL==buttonON){
    delay(100);
    smor.s2alto();
    smor.s1va();
    smor.s1speed();
    buttonstateL=digitalRead(buttonPin);
  }
  smor.s1alto();
  delay(100);
  while(buttonstateR){
      buttonstateR=digitalRead(buttonPinR);
  }
  
  while(buttonstateR==buttonON){
    delay(100);
    smor.s2va();
    smor.s2speed();
    buttonstateR=digitalRead(buttonPinR);

    }
    smor.s2alto();
    delay(500);
    servos.servo_write(0,170);
    delay(1000);
}

