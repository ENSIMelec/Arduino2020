#include <Arduino.h>
#include<Stepper.h>

/*
Nom : Stepper Manager
Auteur : Quentin MONNIER
Date : 02/02/2020

Permet de commander un moteur pas à pas en position à l'aide d'un driver Big Easy Driver
Pas du moteur = 1.8°
*/



//Declare pin functions on Arduino
#define stp 2
#define dir 3 //Direction de rotation
#define MS1 4 // Précision
#define MS2 5
#define MS3 6
#define EN  7


void setup() {
  pinMode(stp, OUTPUT); // Tous les pins utilisés sont en sortie
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(EN, OUTPUT);
  char user_input;
  void resetBEDpins(); //remise aux valeurs par défault
  void rotation(int Angle);
  //int distance;
  int Precision;
  //int Angle = 200;
  Precision = 1;
  //bool Direction;
  //Direction = false;
  void resetBEDpins();
  void setPrecision(int Precision);
  void setDirection(bool Direction);

}



void resetBEDpins()
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
  digitalWrite(EN, HIGH);
}
void setPrecision(int Precision)
{
  switch(Precision) // Rêgle la précision (pas complet au 16 ème de pas) ->  Valeur admise 1,2,4,8,16
  {
    case 1 :
    digitalWrite(MS1,LOW);
    digitalWrite(MS2,LOW);
    digitalWrite(MS3,LOW);
    break;

    case 2 :
    digitalWrite(MS1,HIGH);
    digitalWrite(MS2,LOW);
    digitalWrite(MS3,LOW);
    break;

    case 4 :
    digitalWrite(MS1,LOW);
    digitalWrite(MS2,HIGH);
    digitalWrite(MS3,LOW);
    break;

    case 8 :
    digitalWrite(MS1,HIGH);
    digitalWrite(MS2,HIGH);
    digitalWrite(MS3,LOW);
    break;

    case 16 :
    digitalWrite(MS1,HIGH);
    digitalWrite(MS2,HIGH);
    digitalWrite(MS3,HIGH);
    break;
  }

}

void setDirection(bool Direction)
{
  if (Direction) // 1 -> descente, 0 -> montée
  {
    digitalWrite(HIGH,dir);
  }
  else
  {
    digitalWrite(LOW,dir);
  }
}

void rotation(int Angle)
{
  for(int i=0;i<Angle;i++)
  {
    digitalWrite(HIGH,stp);
    delay(1);
    digitalWrite(LOW, stp);
    delay(1);
  }

}

void loop() {
  while(Serial.available())
  {
    Serial.println("coucou");
    char user_input = Serial.read();
    digitalWrite(EN, LOW); // Permet le contrôle du moteur
    Serial.println("Donnée reçue :");
    Serial.println(user_input);
    if(user_input == 'd') // Fait 1 tour
    {
      rotation(200);
      Serial.print("1 tour");
    }
  }

}
