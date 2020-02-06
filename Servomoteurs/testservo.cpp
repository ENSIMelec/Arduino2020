#include <Arduino.h>

#include <Wire.h>
#include <Servo.h>
#include <avr/wdt.h>

#define ADDR_ARDUINO 6
#define SERVO_PIN8 8


int servoN;
int rot=0;

uint8_t data[6];
Servo s1;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Wire.begin(ADDR_ARDUINO);
  //Wire.onReceive(recv);
  //Wire.onRequest(sendData);
  s1.attach(SERVO_PIN8);

  s1.write(0);

  Serial.print("Ready \n");
}

void loop()
{
  if(rot==200)
  {
    rot =0;
  }
  else
  {
    rot = 200;
  }
  s1.write(rot);
  delay(1000);
}
/*void recv(int bytes)
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
*/
