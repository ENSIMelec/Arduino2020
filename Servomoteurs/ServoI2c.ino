#include <Wire.h>
#include <Servo.h>
#include <avr/wdt.h>

#define ADDR_ARDUINO 6
#define SERVO_PIN2 2
#define SERVO_PIN3 3
#define SERVO_PIN4 4
#define SERVO_PIN5 5
#define SERVO_PIN6 6
#define SERVO_PIN7 7
#define SERVO_PIN8 8
#define SERVO_PIN9 9
#define SERVO_PIN10 10
#define SERVO_PIN11 11
#define SERVO_PIN12 12
#define SERVO_PIN13 13

int servoN;
int rotation;

uint8_t data[6];
Servo s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(ADDR_ARDUINO);
  Wire.onReceive(recv);
  //Wire.onRequest(sendData);
  s1.attach(SERVO_PIN2);
  s2.attach(SERVO_PIN3);
  s3.attach(SERVO_PIN4);
  s4.attach(SERVO_PIN5);
  s5.attach(SERVO_PIN6);
  s6.attach(SERVO_PIN7);
  s7.attach(SERVO_PIN8);
  s8.attach(SERVO_PIN9);
  s9.attach(SERVO_PIN10);
  s10.attach(SERVO_PIN11);
  s11.attach(SERVO_PIN12);
  s12.attach(SERVO_PIN13);
  s1.write(0);
  s2.write(0);
  s3.write(0);
  s4.write(0);
  s5.write(155);
  s6.write(160);
  s7.write(0);
  s8.write(0);
  s9.write(0);
  s10.write(155);
  s11.write(155);
  s12.write(0);
  Serial.print("Ready \n");
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
void recv(int bytes)
{
     wdt_reset();
     while(Wire.available()) 
     {
      servoN = Wire.read();
      rotation = Wire.read();
      Serial.print("Donnee recue : ");
      Serial.print(servoN);
      Serial.print("rotation = ");
      Serial.print(rotation);
      Serial.print("\n");
      switch (servoN)
      {
        case 1:
           s1.write(rotation);
        break;
        case 2 :
          s2.write(rotation);
        break;
        case 3 :
           s3.write(rotation);
        break;
        case 4 :
           s4.write(rotation);
        break;
        case 5 :
           s5.write(rotation);
        break;
        case 6 :
           s6.write(rotation);
        break;
        case 7 :
           s7.write(rotation);
        break;
        case 8 :
           s8.write(rotation);
        break;
        case 9 :
           s9.write(rotation);
        break;
        case 10 :
           s10.write(rotation);
        break;
        case 11 :
           s11.write(rotation);
        break;
        case 12 :
           s12.write(rotation);
        break;
      }
     }
    
}
