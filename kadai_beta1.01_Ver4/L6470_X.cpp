#include "Arduino.h"
#include "LibL6470.hpp"
#include <SPI.h>
#include <Wire.h>

  Servi::Servi():
  Servomin(150),Servomax(600){}

  Stepx::Stepx():
  Go(0x51),Back(0x50),Nop(0x00){}

 void Stepx::L6470_send(unsigned char value){
  digitalWrite(PIN_SPI_SS, LOW); 
  SPI.transfer(value);  //制御信号をSPI通信で送る
  digitalWrite(PIN_SPI_SS, HIGH); 
}

void Stepx::L6470_setup(){
  //デバイス設定
  L6470_send(0x00);
  L6470_send(0x00);
  L6470_send(0x00);
  L6470_send(0x00);  
  L6470_send(0x0c);

  L6470_send(0x03);//レジスタアドレス
  L6470_send(0x25);//値(10bit),デフォルト0x41
  
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
  L6470_send(0x07);//値(8bit)

}

void Stepx::ir(bool dir, int spd){
  Speed=spd;
  if(dir){
     L6470_send(Go);//Run(DIR,SPD),0x51:正転,0x50:逆転 
     L6470_send(0x00);
     L6470_send(Speed);//回転スピードの設定
     L6470_send(0x00);
  }else{
     L6470_send(Back);//Run(DIR,SPD),0x51:正転,0x50:逆転 
     L6470_send(0x00);
     L6470_send(Speed);//回転スピードの設定
     L6470_send(0x00);
  }
  
}

void Stepx::alto(){
  L6470_send(0xB8);//急停止(ハードストップ)
  L6470_send(0x00);
}
void Stepx::parar(){
  L6470_send(0xB0);//停止(ソフトストップ)
  L6470_send(0x00);
}
void Stepx::ircasa(){
  L6470_send(0b01110000);
  L6470_send(Nop);
 }

