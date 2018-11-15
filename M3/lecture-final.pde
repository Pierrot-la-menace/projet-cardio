//From Arduino to Processing to Txt or cvs etc.
//import
import processing.serial.*;                              //importation de la bibliothèque processing.serial
//declare
PrintWriter output;                                      //initialisation du port serie                                  
Serial udSerial;                                         //initialisation pour ecrire dans un fichier externe 
long timeStamp = OL;

void setup() {
   udSerial = new Serial(this, Serial.list()[0], 9600);     //recherche du port connecté a la Arduino
   output = createWriter ("Battements.csv");                //creation du fichiers "battements.csv"              
}

 void draw() {
   if (udSerial.available() > 0) {                          //si la carte arduino envoie des données
     String SenVal = udSerial.readString();                 //le port série lit les données
     delay(200);                                            //delai de 200 millisecondes
       if (SenVal != null) {                                  // si la Arduino envoi des valeurs
         timeStamp = currentTimeMillis() / 1000;
         output.println(timeStamp+";"+SenVal);              //ecriture des données dans le fichiers "Battements.csv"
         delay(200);                                          //delai de 200 millisecondes
        }
    }
 }
 
 void keyPressed(){
 
   switch(key)
   {
     case 'e':                                             //definition de la touche 'e'
     output.flush();                                       //fonction flush()                             
     output.close();                                       //fermeture du programme
     exit();
     break;
   }
   
 }
