#include <Wire.h>
#define interCodG  0 //pin2 (interrupt0)
#define interCodD  1 //pin3 (interrup1)
#define AV 1 //indexs pour les tableaux de retour de la fonction de conversion (normalement inutilisé mais on va les garder pour la norme)
#define ARR 0
#define GAUCHE 0
#define DROIT 1

#define PIN_ATT 5


#define CANAL_BD  8 //canal avant ou arrière pour les codeurs (droit)
#define CANAL_BG  7 // (gauche)

#define ADDR_ARDUINO  9

#define CMD_RESET_ACTIONNEURS -1
#define CMD_RESET_CODEURS -3
#define CMD_ACK -2



volatile int nbTicD; //compteur de ticks codeur droit
volatile int nbTicG; // compteur de ticks codeur gauche

void setup()
{
   Serial.begin(115000);
  //Wire.begin(ADDR_ARDUINO);//adresse i2c en 9 pour les codeurs
  //Wire.onRequest(rqst);//reception i2c
  //Wire.onReceive(recv);
  reset_actionneurs();

  reset();
  attachInterrupt(interCodD, compterTicDroit, RISING );
  attachInterrupt(interCodG, compterTicGauche, RISING);
}


void reset()
{
  nbTicD = 0;
  nbTicG = 0;
}

void reset_actionneurs()
{
  digitalWrite(PIN_ATT, LOW);
}


void loop()
{
  Serial.print("?");
        Serial.print(nbTicG);
        Serial.print("!");
        Serial.println(nbTicD);
   if (Serial.available()) 
  {
    int data = Serial.read();

   switch (data)
   {
      case 'C' :
        //delay(20);
        Serial.print("?");
        Serial.print(nbTicG);
        Serial.print("!");
        Serial.print(nbTicD);
        reset();
      break;

      case 'R' :
         reset();
      break;
   }   
     
  }
  
}


void compterTicDroit ()
{
  if (digitalRead(CANAL_BD) == HIGH)
  {
    nbTicD--;
  }
  else
    nbTicD++;
}

void compterTicGauche ()
{
  if (digitalRead(CANAL_BG) == HIGH)
  {
    nbTicG++;
  }
  else
    nbTicG--;
}
void rqst() //appelée lorsque la rasp demande l'état des codeurs
{
  
  int16_t ar[4] = {nbTicG, nbTicD, nbTicG, nbTicD};
  Wire.write((const char*)ar, 8);
 
  /*String ar = String(nbTicG) + " " + String(nbTicD) + " "+ String(nbTicG) +" "+ String(nbTicD);
  Wire.write(ar.c_str());*/
  nbTicD = 0;
  nbTicG = 0;
  
}
void recv(int bytes) { //demande d'actions
  /*
     recéption reset
  */
  if (bytes == 1) // reset si 1 byte
  {
    int8_t cmd = Wire.read();
    //Serial.print("\nCommande : ");
    //Serial.print(cmd);

    if (cmd == CMD_RESET_CODEURS)
      reset();

  }

}

bool isBetween(int min, int val, int max)
{
  if (val < min || val > max)
    return false;
  return true;
}
