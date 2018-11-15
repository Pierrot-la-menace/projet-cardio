//From Arduino to Processing to Txt or cvs etc.
//import
import processing.serial.*;                              //importation de la bibliothèque processing.serial
//declare
PrintWriter output;                                      //initialisation du port serie                                  
Serial udSerial;  
//initialisation pour ecrire dans un fichier externe 
Table table;
String date;


void setup() {
 udSerial = new Serial(this, Serial.list()[0], 9600);     //recherche du port connecté a la Arduino
 output = createWriter ("Battements.csv");                //creation du fichiers "battements.csv"    
 table = new Table();
  //add a column header "Data" for the collected data
 table.addColumn("Data");
  //add a column header "Time" and "Date" for a timestamp to each data entry
 table.addColumn("Time");
 table.addColumn("Date");
}
 void draw() {
   //variables called each time a new data entry is received
  int d = day();
  int m = month();
  int y = year();
  int h = hour();
  int min = minute();
  int s = second();

 if (udSerial.available() > 0) {                          //si la carte arduino envoie des données
   String SenVal = udSerial.readString();                 //le port série lit les données
   delay(200);                                            //delai de 200 millisecondes
   if (SenVal != null) {                                  // si la Arduino envoi des valeurs
                                                          //ecriture des données dans le fichiers "Battements.csv"

     delay(200);                                          //delai de 200 millisecondes
      //add a new row for each value
      TableRow newRow = table.addRow();
      //place the new row and value under the "Data" column
      newRow.setString("Data", SenVal);
      //place the new row and time under the "Time" column
      newRow.setString("Time", str(h) + ":" + str(min) + ":" + str(s));
      //place the new row and date under the "Date" column
      newRow.setString("Date", str(d) + "/" + str(m) + "/" + str(y));
      print("data/" + str(m) + "-" + str(d) + "--" + str(h) + "-" + str(min) + "-" + str(s) +"==>" + SenVal);
 }
 }
 }
 void keyPressed(){
  switch(key)
  {
    case 'e':                                             //definition de la touche 'e'
    output.flush();                                       //fonction flush()                                            //definitionde la touche 'p'
    output.close();                                       //fermeture du programme
     exit();
    break;

 }
 }
