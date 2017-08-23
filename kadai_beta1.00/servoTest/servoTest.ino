#include <Wire.h>

#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600 // this is the 'maximum' pulse length count (out of 4096)

void setup() {
 pwm.begin();
 pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates
 servo_write(0,90);
}

void loop() {
 //0番ピンのサーボに角度10度を指示
servo_write(0,10);
 delay(500);
 //0番ピンのサーボに角度170度を指示
servo_write(0,170);
 delay(500);
}

void servo_write(int n, int ang){ //動かすサーボと角度を引数に持つ
ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～600）へ変換
pwm.setPWM(n, 0, ang);
}

