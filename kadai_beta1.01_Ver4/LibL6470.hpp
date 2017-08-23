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

class Stepx{
  private:
   byte Nop;
   byte Go;
   byte Back;
   int Speed;
  public:
   Stepx();
   void L6470_send(unsigned char value);
   void L6470_setup();
   void ir(bool dir, int spd);
   void alto();
   void parar();
   void ircasa();
};

class Stepy{
  private:
  byte Nop;
  byte Go;
  byte Back;
  int Speed;
  public:
  Stepy();
  void L6470_send(unsigned char value2);
  void L6470_setup();
  void ir(bool dir, int spd);
  void alto();
  void parar();
  void ircasa();
};
#endif
