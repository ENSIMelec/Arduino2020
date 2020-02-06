/*
Nom : Stepper
Auteur : Quentin MONNIER
Date : 06 Février 2020
Initialisation : Position Courante -> 0
Valeur positive : Sens de rotation horaire
Valeur négative : Sens anti-horaire
*/



#include <Arduino.h>
//#include <Stepper.h>
#include "AccelStepper.h"
#define MAX_SPEED 500
#define MIN_SPEED 0.1

AccelStepper moteur(AccelStepper::DRIVER,3,2); //pin stp = 3, pin dir = 2
long posi = 3600;
void setup()
{
  Serial.begin(9600);
  moteur.setMaxSpeed(10000.0);
  moteur.setAcceleration(1000);
  Serial.println("On essaie de faire tourner le bousin");
  moteur.setSpeed(4000); //Environ 1 tr/sec, mesure schlag

}

void loop()
{
  moteur.moveTo(posi);
  while(moteur.distanceToGo()!=0)
  {
    moteur.run();
    Serial.println(moteur.currentPosition());
  }
  posi=moteur.currentPosition();
 if(posi==3600)
 {
   posi = -3600;
 }
 else
 {
   posi = 3600;
 }
 Serial.print("Position du moteur : ");
 Serial.println(moteur.currentPosition());
 delay(1000);
  /* test rotation du moteur
  moteur.runSpeed();
  Serial.print("Position actuelle : ");
  Serial.println(moteur.currentPosition()); // Renvoie la position actuelle absolue du moteur
  */

}
