#include "Arduino.h"
#include "LibL6470.hpp"
#include <SPI.h>
#include <Wire.h>

  Stepy::Stepy():
  Go(0x51),Back(0x50),Nop(0x00){}

void Stepy::L6470_send(unsigned char value2){
  digitalWrite(PIN_SPI_SS2, LOW); 
  SPI.transfer(value2);  //制御信号をSPI通信で送る
  digitalWrite(PIN_SPI_SS2, HIGH); 
}

word Stepy::stato(){
  L6470_send(0xD0);
  digitalWrite(PIN_SPI_SS2, LOW); 
  Status=SPI.transfer(0x00);  //制御信号をSPI通信で送る
  digitalWrite(PIN_SPI_SS2, HIGH);
  Status=Status>>5;    Status=Status<<14;
  return Status;
}

void Stepy::L6470_setup(){
  //デバイス設定
  L6470_send(0x00);
  L6470_send(0x00);
  L6470_send(0x00);
  L6470_send(0x00);  
  L6470_send(0x0c);

  L6470_send(0x03);//レジスタアドレス
  L6470_send(0x26);//値(10bit),デフォルト0x41
  
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

void Stepy::alto(){
  L6470_send(0xB8);//急停止(ハードストップ)
  L6470_send(0x00);
 }
 void Stepy::parar(){
  L6470_send(0xB0);//停止(ソフトストップ)
  L6470_send(0x00);
}
void Stepy::ir(bool dir, int spd){
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

void Stepy::ircasa(){
  L6470_send(0b01110000);
  L6470_send(Nop);
 }
