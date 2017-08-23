#include "Arduino.h"
#include "LibL6470.hpp"
#include <SPI.h>
#include <Wire.h>

  Servi::Servi():
  Servomin(150),Servomax(600){}
 
 //**********************************************
//(6)SPI通信するための関数
//**********************************************
 void Steps::L6470_send(unsigned char value){
  digitalWrite(PIN_SPI_SS, LOW); 
  SPI.transfer(value);  //制御信号をSPI通信で送る
  digitalWrite(PIN_SPI_SS, HIGH); 
}

//**********************************************
// (7)L6470のセットアップ
//**********************************************
void Steps::L6470_setup(){
  //デバイス設定
  L6470_send(0x00);
  L6470_send(0x00);
  L6470_send(0x00);
  L6470_send(0x00);  
  L6470_send(0x0c);

 
  //最大回転スピード設定
  L6470_send(0x07);//レジスタアドレス
  L6470_send(0x20);//値(10bit),デフォルト0x41
 
  //モータ停止中の電圧設定
  L6470_send(0x09);//レジスタアドレス
  L6470_send(0xFF);//値(8bit),デフォルト0x29
 
  //モータ定速回転時の電圧設定
  L6470_send(0x0a);//レジスタアドレス
  L6470_send(0xFF);//値(8bit),デフォルト0x29
 
  //加速中の電圧設定
  L6470_send(0x0b);//レジスタアドレス
  L6470_send(0xFF);//値(8bit),デフォルト0x29
 
  //減速中の電圧設定
  L6470_send(0x0c);//レジスタアドレス
  L6470_send(0xFF);//値(8bit),デフォルト0x29
 
  //フルステップ,ハーフステップ,1/4,1/8,…,1/128ステップの設定
  L6470_send(0x16);//レジスタアドレス
  L6470_send(0x00);//値(8bit)

  //減速係数
  
}

void Steps::L6470v2_send(unsigned char value2){
  digitalWrite(PIN_SPI_SS2, LOW); 
  SPI.transfer(value2);  //制御信号をSPI通信で送る
  digitalWrite(PIN_SPI_SS2, HIGH); 
}

void Steps::L6470v2_setup(){
  //デバイス設定
  L6470v2_send(0x00);
  L6470v2_send(0x00);
  L6470v2_send(0x00);
  L6470v2_send(0x00);  
  //L6470v2_send(0x00);
  L6470v2_send(0x0c);

 
  //最大回転スピード設定
  L6470v2_send(0x07);//レジスタアドレス
  L6470v2_send(0x20);//値(10bit),デフォルト0x41
 
  //モータ停止中の電圧設定
  L6470v2_send(0x09);//レジスタアドレス
  L6470v2_send(0xFF);//値(8bit),デフォルト0x29
 
  //モータ定速回転時の電圧設定
  L6470v2_send(0x0a);//レジスタアドレス
  L6470v2_send(0xFF);//値(8bit),デフォルト0x29
 
  //加速中の電圧設定
  L6470v2_send(0x0b);//レジスタアドレス
  L6470v2_send(0xFF);//値(8bit),デフォルト0x29
 
  //減速中の電圧設定
  L6470v2_send(0x0c);//レジスタアドレス
  L6470v2_send(0xFF);//値(8bit),デフォルト0x29
 
  //フルステップ,ハーフステップ,1/4,1/8,…,1/128ステップの設定
  L6470v2_send(0x16);//レジスタアドレス
  L6470v2_send(0x00);//値(8bit)
}
  
 void Steps::s1va(){
  L6470_send(0x50);//Run(DIR,SPD),0x51:正転,0x50:逆転 
  L6470_send(0x00);
 }
void Steps::s1speed(){
  L6470_send(0x20);//回転スピードの設定
  L6470_send(0x00);
}
void Steps::s1alto(){
  L6470_send(0xB8);//急停止(ハードストップ)
  L6470_send(0x00);
}
void Steps::s2va(){
  L6470v2_send(0x50);//Run(DIR,SPD),0x51:正転,0x50:逆転 
  L6470v2_send(0x00);
}
void Steps::s2speed(){
  L6470v2_send(0x20);//回転スピードの設定
  L6470v2_send(0x00);
}
void Steps::s2alto(){
  L6470v2_send(0xB8);//急停止(ハードストップ)
  L6470v2_send(0x00);
 }

