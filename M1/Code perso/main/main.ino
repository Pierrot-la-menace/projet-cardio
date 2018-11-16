 
//***************************************** Lib *****************************************
#include"cardio.h"  //Lib pour le capteur cardiaque

//***************************************** Var ***************************************** 
int temps1;  //variables le calcule de la periode cardiaque 
int temps2;

//***************************************** Setup ***************************************** 
void setup() {
  
   Serial.begin(9600);  //debut de la liaison serie
   }
}

//***************************************** Loop ***************************************** 
void loop() {
  
//----------------------------------------- Calcul de la periode -----------------------------------------
  temps1=pulse();  
  
//----------------------------------------- Affichage du temps et du pouls sur le port serie -----------------------------------------
  if(temps1-temps2 > 0){  

    Serial.print(millis());
    Serial.print(";");
    Serial.print(rythmeC(temps1,temps2));  // appel de la fonction rythmeC qui calcul les BPM a partir de delta t
    Serial.println(";");
    temps2=temps1;  // t2 devient t1 pour calculer la prochaine periode
  }  
}
