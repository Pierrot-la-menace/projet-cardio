 
//***************************************** Lib *****************************************
#include "coeur.h"  //Lib pour le coeur de LEDs
#include "param.h"  //Fichier option

#include"cardio.h"  //Lib pour le capteur cardiaque

//***************************************** Var ***************************************** 
int temps1;  //variables le calcule de la periode cardiaque 
int temps2;

//***************************************** Setup ***************************************** 
void setup() {
  
   Serial.begin(9600);  //debut de la liaison serie
   
   int led_rouge[]={2,3,4,5,6,7,8,9,10,11};  //definition du pinMode des LED
   for(int i=0; i<10; i++){
    
      pinMode(led_rouge[i], OUTPUT);
   }
}

//***************************************** Loop ***************************************** 
void loop() {
  
//----------------------------------------- Calcul de la periode -----------------------------------------
  temps1=pulse();  

//----------------------------------------- Selection du mod de clignotement -----------------------------------------
  switch(OPTION){ 

  case 1:
    toutes_leds();  //toutes les leds clignotent
  break;
  
  case 2:
    led_sur_deux();  //une led sur deux
  break;
  
  case 3:
    led_sur_trois();  //une led sur trois
  break;
  
  case 4:                                                        
    chenille();  //leds une par une
  break;
  
  case 5: 
    Une_LED_au_choix();  //une seule led au choix
  break;
  }
  
//----------------------------------------- Affichage du temps et du pouls sur le port serie -----------------------------------------
  if(temps1-temps2 > 0){  

    Serial.print(millis());
    Serial.print(",");
    Serial.print(rythmeC(temps1,temps2));  // appel de la fonction rythmeC qui calcul les BPM a partir de delta t
    Serial.println(";");
    temps2=temps1;  // t2 devient t1 pour calculer la prochaine periode
  }  
}
