#include <Adafruit_PWMServoDriver.h>

#include <Arduino.h>
#include <SPI.h>  //(1)SPI通信をするための読み込み
#include <Wire.h>

//servo motor setup
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN 150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600

// this is the 'maximum' pulse length count (out of 4096)




//(2)ステッピングモーター用のピンの定義
#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13
#define PIN_SPI_SS 10
#define PIN_SPI_SS2 9
const int buttonON=LOW;
const int buttonOFF=HIGH;
const int buttonPin=14;
const int buttonPinR=15;
const int mainswitch=16;
int buttonstateL=1;
int buttonstateR=1;
bool buttonstateM=false;

void servo_write(int n, int ang){ //動かすサーボと角度を引数に持つ
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～600）へ変換
  pwm.setPWM(n, 0, ang);
}



void setup()
{
 pwm.begin();
 pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates
 servo_write(0,0);
  
  
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
  L6470_setup();
  L6470v2_setup();
}
 
//**********************************************
//(6)SPI通信するための関数
//**********************************************
void L6470_send(unsigned char value){
  //digitalWrite(PIN_SPI_SS2, HIGH);
  digitalWrite(PIN_SPI_SS, LOW); 
  SPI.transfer(value);  //制御信号をSPI通信で送る
  digitalWrite(PIN_SPI_SS, HIGH); 
}
 
//**********************************************
// (7)L6470のセットアップ
//**********************************************
void L6470_setup(){
  //デバイス設定
  L6470_send(0x00);
  L6470_send(0x00);
  L6470_send(0x00);
  L6470_send(0x00);  
  //L6470_send(0x00);
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

void L6470v2_send(unsigned char value2){
  //digitalWrite(PIN_SPI_SS, HIGH);
  digitalWrite(PIN_SPI_SS2, LOW); 
  SPI.transfer(value2);  //制御信号をSPI通信で送る
  digitalWrite(PIN_SPI_SS2, HIGH); 
}

void L6470v2_setup(){
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

  //減速係数
  
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
    L6470v2_send(0xB8);//急停止(ハードストップ)
    L6470v2_send(0x00);
    L6470_send(0x50);//Run(DIR,SPD),0x51:正転,0x50:逆転 
    L6470_send(0x00);
    L6470_send(0x20);//回転スピードの設定
    L6470_send(0x00);
    buttonstateL=digitalRead(buttonPin);
  }
  L6470_send(0xB8);//急停止(ハードストップ)
  L6470_send(0x00);
  delay(100);
  while(buttonstateR){
      buttonstateR=digitalRead(buttonPinR);
  }
  
  while(buttonstateR==buttonON){
    delay(100);
    
    L6470v2_send(0x50);//Run(DIR,SPD),0x51:正転,0x50:逆転 
    L6470v2_send(0x00);
    L6470v2_send(0x20);//回転スピードの設定
    L6470v2_send(0x00);
    buttonstateR=digitalRead(buttonPinR);

    }
    L6470v2_send(0xB8);//急停止(ハードストップ)
    L6470v2_send(0x00);
    delay(500);
    servo_write(0,170);
    delay(1000);
}

