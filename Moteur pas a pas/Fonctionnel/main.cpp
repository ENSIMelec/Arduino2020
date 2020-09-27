/*
Nom : Stepper
Auteur : Quentin MONNIER
Date : 06 Février 2020
Initialisation : Position Courante -> 0
Valeur positive : Sens de rotation horaire
Valeur négative : Sens anti-horaire

Commentaires généraux :
Test de fonctionnement avec commnication I2C + Fonctionnement du Stepper
*/



#include <Arduino.h>
#include <Wire.h>
#include "AccelStepper.h"

#define STEPPER_ADDR 0x09
#define MS1 4
#define MS2 5
#define MS3 6
#define SWB 9
#define SWH 8
#define EN 12

AccelStepper moteur(AccelStepper::DRIVER,3,2); //pin stp = 3, pin dir = 2
long posi = 3600;
char lect[8];
long pos;
long val = 10;
bool Drec = false;

void initPosition()
{
  while (!digitalRead(SWB) && (!digitalRead(SWH)))
  {
    moteur.moveTo(200);
    moteur.setSpeed(500);
    moteur.runSpeed();
    //Serial.println(moteur.currentPosition());
  }
  if(digitalRead(SWB))
  {
    Serial.println("On a atteint la bonne position");
    moteur.setCurrentPosition(0);
    moteur.moveTo(-200);
    while(moteur.distanceToGo()!=0 && !digitalRead(SWH))
    {

      moteur.run();
      Serial.println(moteur.currentPosition());
    }

  }
  else if(digitalRead(SWH))
  {
    Serial.println("On est pas du bon côté");
  }

}

long Posytostp(long posy)
{
  Serial.print(" Pos avant traitement : ");
  Serial.println(posy);
  long bite = -(posy*20); // posy en mm, bite en stp
  Serial.print("Pos apres traitement : ");
  Serial.println(bite);
  return bite;
}

void receive(int bytes)
{
  while(Wire.available())
  {

    val=Wire.read();
    Serial.print("Donnée recue : ");
    Serial.print(val);
    Serial.println("");
    //delay(5000);


 //delay(1000);

  /* test rotation du moteur
  moteur.runSpeed();
  Serial.print("Position actuelle : ");
  Serial.println(moteur.currentPosition()); // Renvoie la position actuelle absolue du moteur
  */
  }
}



void sendNudes() // Fonction à dev pour envoyer des flags à la Rasp
{

}
void setup()
{
  Serial.begin(9600);
  Wire.begin(STEPPER_ADDR);
  Wire.onReceive(receive);
  Wire.onRequest(sendNudes);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(SWB, INPUT);
  pinMode(SWH, INPUT);
  pinMode(EN, OUTPUT);
  moteur.setMaxSpeed(10000.0);
  moteur.setAcceleration(1000); //C'est lent
  Serial.println("On essaie de faire tourner le bousin");
  moteur.setSpeed(10000); //Environ 1 tr/sec, mesure schlag
  digitalWrite(MS1,LOW); // Passage en pas complet
  digitalWrite(MS2,LOW);
  digitalWrite(MS3,LOW);
  digitalWrite(EN, LOW);
  initPosition();

}

void loop()
{

  if(Posytostp(val)!=moteur.distanceToGo())
  {
    if(val<10 || val>130)
    {
      Serial.println("Sortie de la course possible. Veuillez choisir une valeur comprise entre 10 et 130");
      val = 10;
    }
    pos = Posytostp(val);
    Serial.print("Position a atteindre 1 : ");
    Serial.println(pos);
    /*if(posi==0)
    {
      posi =-200;
    }
    */

  /*if(moteur.distanceToGo()==0)
  {
    moteur.moveTo(posi);
    //moteur.setAcceleration(5000);
  }
  */
    moteur.moveTo(pos); // sélectionne la position à atteindre
    moteur.setAcceleration(1000); //
    Serial.print("Distance a atteindre 2 : ");
    Serial.println(pos);
    Serial.print("Distance a atteindre 3 : ");
    Serial.println(moteur.distanceToGo());
    delay(1000);
    while(moteur.distanceToGo()!=0 && !digitalRead(SWH) && !digitalRead(SWB))
    {
      moteur.run();
      Serial.println(moteur.currentPosition());
    }



    if(digitalRead(SWB) || digitalRead(SWH))
    {
      Serial.println("Un Switch a été activé. On stop tout !");
      digitalWrite(EN, HIGH);

    }
    Serial.println("Posisiton attendue de l'ascenceur (mm):");
    Serial.println(val);
    Serial.println("Position attendue de l'ascenceur (en step)");
    Serial.println(Posytostp(val));

    Serial.print("Position atteinte du moteur : ");
    Serial.println(moteur.currentPosition());
  }
}
