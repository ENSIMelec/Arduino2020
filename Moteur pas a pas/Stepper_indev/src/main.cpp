/*
Nom : Stepper
Auteur : Quentin MONNIER
Contact : quentin91.monnier1998@gmail.com
Association : ENSIM'ELEC
Date : 10 Février 2020
Initialisation : Position Courante -> 0
Valeur positive : Sens de rotation horaire
Valeur négative : Sens anti-horaire

Course maximum : 190 mm = 19 tours = 19*200 = 3800stp
1mm -> 20 stp
*/

// Hauteur max = 170 mm -> 17 tours = 3400 stp
//Hauteur min = 0 mm

#include <Arduino.h>
//#include <Stepper.h>
#include "AccelStepper.h"
#define MAX_SPEED 500
#define MIN_SPEED 0.1
#define MS1 4
#define MS2 5
#define MS3 6
#define SWB 9
#define SWH 8




AccelStepper moteur(AccelStepper::DRIVER,3,2); //pin stp = 3, pin dir = 2
//long posi = 1000; // environ 50 mm
char string[50]; // Chaine reçue 0
long val;
long posi;

void initPosition()
{
  while (digitalRead(SWB) && (digitalRead(SWH)))
  {
    moteur.moveTo(200);
    moteur.runSpeed();
    //Serial.println(moteur.currentPosition());
  }
  if(!digitalRead(SWB))
  {
    Serial.println("On a atteint la bonne position");
    moteur.setCurrentPosition(0);
    /*moteur.moveTo(-2600);
    while(moteur.distanceToGo()!=0 && digitalRead(SWH))
    {
      moteur.runSpeed();
      Serial.println(moteur.currentPosition());
    }
    */
  }
  else
  {
    Serial.println("On est pas du bon côté");
  }
}

long Posytostp(long posy)
{
  return -posy*20;
}

void setup()
{
  Serial.begin(9600);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(SWB, INPUT);
  pinMode(SWH, INPUT);
  moteur.setMaxSpeed(1000000.0);
  moteur.setAcceleration(150000.0);
  //Serial.println("On essaie de faire tourner le bousin");
  moteur.setSpeed(300000.0);
  //moteur.setCurrentPosition(0);
  digitalWrite(MS1,LOW); // Passage en pas complet
  digitalWrite(MS2,LOW);
  digitalWrite(MS3,LOW);
  initPosition();

  Serial.println("Entrez la position verticale à atteindre en mm svp : ");

}




void loop()
{

  if(Serial.available())
  {
    for(int i=0; i<32; i++)
    {
      string[i]=Serial.read();
    }
    val=atol(string);
    Serial.println("Position a atteindre :");
    Serial.println(val);
    posi = Posytostp(val);
    }
    else
    {
      Serial.println("Pas de Donnée recue");
    }


  moteur.moveTo(posi); // sélectionne la position à atteindre
  while(moteur.distanceToGo()!=0 && digitalRead(SWH))
  {
    moteur.runSpeed();
    Serial.println(moteur.currentPosition());
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
