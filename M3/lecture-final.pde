//From Arduino to Processing to Txt or cvs etc.
//import
import processing.serial.*;                              //importation de la bibliothèque processing.serial
import java.lang.System;
//declare
PrintWriter output;                                      //initialisation du port serie                                  
Serial udSerial;                                         //initialisation pour ecrire dans un fichier externe 
long timeStamp = 0L;

void setup() {
   udSerial = new Serial(this, Serial.list()[0], 9600);     //recherche du port connecté a la Arduino
   output = createWriter("/media/pierre122/36758165-9a66-490c-94b9-9328adf594f1/Exia/2018-2019/U.E_1/Projet/Prog/Battements.csv");                //creation du fichiers "battements.csv"   
   timeStamp = System.currentTimeMillis() / 1000;
   output.println(timeStamp+";;");
   output.flush(); 
}

 void draw() {
   if (udSerial.available() > 0) {                          //si la carte arduino envoie des données
     String SenVal = udSerial.readString();                 //le port série lit les données
     delay(500);                                            //delai de 200 millisecondes
       if (SenVal != null) {                                  // si la Arduino envoi des valeurs
         println("Enregistrement");
          //ecriture des données dans le fichiers "Battements.csv"
          output.print(SenVal);
         output.flush();
         delay(200);                                          //delai de 200 millisecondes
        }
    }
 }
 
 void keyPressed(){
 
   switch(key)
   {
     case 'e':                                             //definition de la touche 'e'                           
     output.close();                                       //fermeture du programme
     exit();
     break;
   }
   
}
