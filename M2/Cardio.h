//***************************************** Var preprocesseur *****************************************
#define vitesseLecture 20
#define pin A0
#define pot A1

//***************************************** Def fonction *****************************************

int pulse(){  //fonction pour analyser une pulsation

  int valeurCapteur;
  int maximum = 0;
  int t1=0;
  int seuil = 0.5*analogRead(pot) ;  //le seuil change en fonction de la position du potentiometre
  
  while (analogRead(pin) > seuil){   
    
    valeurCapteur = analogRead(pin);    
    
    if  (valeurCapteur>maximum){
      
      maximum=valeurCapteur;
      t1 = millis();     
      delay(vitesseLecture);   
                
    }else if(valeurCapteur<maximum){
      
      delay(vitesseLecture);   
    }
  } 
  return t1;
}

int rythmeC(int temp1,int temp2){  //def de la fonction rythmeC qui calcul les BPM a partir de delta t
  
  return (60000/(temp1-temp2));
}
