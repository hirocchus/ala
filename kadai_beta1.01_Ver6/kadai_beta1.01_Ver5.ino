#include <Chrono.h>
#include "LibL6470.hpp"
#include <SPI.h>  //(1)SPI通信をするための読み込み
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Chrono uno;
Chrono dos;
Chrono unoMicros(Chrono::MICROS);
Chrono dosMicros(Chrono::MICROS);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void servo_write(word n, word ang){
  ang = map(ang, 0, 180, 150, 600); //角度（0～180）をPWMのパルス幅（150～600）へ変換
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
byte z=0;
byte l=1;
byte r=2;
Stepx x; //X軸
Stepy y; //Y軸
void setup()
{
 
 pwm.begin();
 pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates

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
  x.L6470_setup();
  y.L6470_setup();
}
 
//**********************************************
// (8)メイン処理 - loop()
//**********************************************
void loop(){
  servo_write(z,10);
  delay(300);
  servo_write(l,10);
  delay(10);
  servo_write(r,170);
  delay(300);
  buttonstateL=digitalRead(buttonPin);
  buttonstateR=digitalRead(buttonPinR);
  buttonstateM=digitalRead(mainswitch);
  
  while(buttonstateL){
      buttonstateL=digitalRead(buttonPin);
  }
  uno.start();
  while(buttonstateL==buttonON){
    y.alto();
    x.ir(false,0x20);
    delay(100);
    buttonstateL=digitalRead(buttonPin);
  }
  x.alto();
  uno.stop();
  unsigned long ela=uno.elapsed();
  
  delay(100);
  while(buttonstateR){
      buttonstateR=digitalRead(buttonPinR);
  }
  dos.start();
  while(buttonstateR==buttonON){
    x.alto();
    y.ir(false,0x20);
    delay(100);
    buttonstateR=digitalRead(buttonPinR);

   }
    y.alto();
    dos.stop();
    unsigned long ala=dos.elapsed();
    delay(500);
    servo_write(l,170);
    delay(10);
    servo_write(r,10);
    delay(1000);
    servo_write(z,175);
    delay(2000);
    servo_write(l,10);
    delay(10);
    servo_write(r,170);
    delay(1500);
    servo_write(z,10);
    delay(1000);
    x.ircasa();
    y.ircasa();
    if(ela>ala)   delay(ela);
    else          delay(ala);
    
    delay(100);
    servo_write(l,170);
    delay(10);
    servo_write(r,10);
    delay(2000);
    

}

