#define temps 50
#include "param.h" 

void toutes_leds()
{

  int led_rouge[]={2,3,4,5,6,7,8,9,10,11};
 
  int i = 0;
   for(i = 0; i < 10; i++)
   {
    digitalWrite(led_rouge[i], 1);
   }
   delay(temps);

  for(i = 0; i < 10; i++)
  {
    digitalWrite(led_rouge[i], 0);
  }
 
}

void chenille()
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

void led_sur_deux()
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

void led_sur_trois()
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

void Une_LED_au_choix()
{
  int led_rouge[]={2,3,4,5,6,7,8,9,10,11};

  digitalWrite(led_rouge[autre], 1);
  delay(temps);
  digitalWrite(led_rouge[autre], 0);

}
