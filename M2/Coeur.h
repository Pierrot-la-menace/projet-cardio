#define temps 50
#include "param.h" /*Permet de savoir quel mode d'éclairage des LEDs l'utilisateur a choisit
                     et quelle LED il a choisit d'allumer s'il a choisit le mode n°5*/

void toutes_leds() //Fonction permettant de faire clignoter toutes les LEDs en fonction du coeur
{

  int led_rouge[]={2,3,4,5,6,7,8,9,10,11};//Déclare toutes les pins numériques utilisés
 
  int i = 0;
   for(i = 0; i < 10; i++)
   {
    digitalWrite(led_rouge[i], 1);// La valeur 1 correspond à HIGH
   }
   delay(temps);

  for(i = 0; i < 10; i++)
  {
    digitalWrite(led_rouge[i], 0);//La valeur 0 correspond à LOW
  }
 
}

void chenille()//Fonction permettant de faire clignoter les LEDs en mode chenille
{
 int i = 0;
 int led_rouge[]={2,3,4,5,6,7,8,9,10,11};
   

  for(i = 0; i < 10; i++)
  {
    digitalWrite(led_rouge[i], 1);
    delay(temps);
    digitalWrite(led_rouge[i], 0);

  }
}

void led_sur_deux()//Fonction permettant de faire clignoter une LED sur deux
{
  int led_rouge[]={2,3,4,5,6,7,8,9,10,11};
 


  digitalWrite(led_rouge[1], 0);
  digitalWrite(led_rouge[3], 0);
  digitalWrite(led_rouge[5], 0);
  digitalWrite(led_rouge[7], 0);
  digitalWrite(led_rouge[9], 0);
  
  digitalWrite(led_rouge[0], 1);
  digitalWrite(led_rouge[2], 1);
  digitalWrite(led_rouge[4], 1);
  digitalWrite(led_rouge[6], 1);
  digitalWrite(led_rouge[8], 1);
  delay(temps);

  digitalWrite(led_rouge[0], 0);
  digitalWrite(led_rouge[2], 0);
  digitalWrite(led_rouge[4], 0);
  digitalWrite(led_rouge[6], 0);
  digitalWrite(led_rouge[8], 0);

  digitalWrite(led_rouge[1], 1);
  digitalWrite(led_rouge[3], 1);
  digitalWrite(led_rouge[5], 1);
  digitalWrite(led_rouge[7], 1);
  digitalWrite(led_rouge[9], 1);

}

void led_sur_trois()//Fonction permettant de faire clignoter une LED sur trois
{
  int led_rouge[]={2,3,4,5,6,7,8,9,10,11};
 
  digitalWrite(led_rouge[2], 1);
  digitalWrite(led_rouge[3], 1);
  digitalWrite(led_rouge[7], 1);
  digitalWrite(led_rouge[8], 1);

  digitalWrite(led_rouge[4], 0);
  digitalWrite(led_rouge[5], 0);
  digitalWrite(led_rouge[6], 0);

  delay(temps);

  digitalWrite(led_rouge[2], 0);
  digitalWrite(led_rouge[3], 0);
  digitalWrite(led_rouge[7], 0);
  digitalWrite(led_rouge[8], 0);
  
  digitalWrite(led_rouge[0], 1);
  digitalWrite(led_rouge[1], 1);
  digitalWrite(led_rouge[9], 1);
  delay(temps);

  digitalWrite(led_rouge[0], 0);
  digitalWrite(led_rouge[1], 0);
  digitalWrite(led_rouge[9], 0);

  digitalWrite(led_rouge[4], 1);
  digitalWrite(led_rouge[5], 1);
  digitalWrite(led_rouge[6], 1);


}

void Une_LED_au_choix()//Fonction permettant de faire clignoter une LED choisit par l'utilisateur
{
  int led_rouge[]={2,3,4,5,6,7,8,9,10,11};

  digitalWrite(led_rouge[autre], 1);
  delay(temps);
  digitalWrite(led_rouge[autre], 0);

}
