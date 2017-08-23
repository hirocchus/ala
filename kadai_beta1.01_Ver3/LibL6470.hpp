//(2)ステッピングモーター用のピンの定義
#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13
#define PIN_SPI_SS 10
#define PIN_SPI_SS2 9


#ifndef LibL6470_h
#define LibL6470_h 
 
 class Servi{
  private:
   int Servomin;
   int Servomax;
  public:
   Servi();
   void servo_write(word n, word ang);
};

class Steps{
  public:
   void L6470_send(unsigned char value);
   void L6470_setup();
   void L6470v2_send(unsigned char value2);
   void L6470v2_setup();
   void s1va();
   void s1speed();
   void s1alto();
   
   void s2va();
   void s2speed();
   void s2alto();
};

#endif
