#include <SoftwareSerial.h> //Incluimos la libreria Software Serial

//Creado por youtube/ElTallerDeTD
//eltallerdetd@gmail.com

SoftwareSerial SIM800L(12,13); //Instanciamos el objeto SIM800L y le pasamos los parametros de los pines TX y RX
String valor;  //Declaramos la variable de tipo String valor.
void setup() {  
  Serial.begin(9600); //Inicializamos la primera comunicacion Serial.
  SIM800L.begin(9600); //Inicializamos la segunda comunicacion Serial.
  
  delay(100); //Delay de 0.1 sec
  SIM800L.println("AT+CNMI=1,2,0,0,0"); //Configurar el SIM800L p/ que muestre msm por com. serie.

}

void loop() {     
  updateSerial();
  enviarMensaje();
  delay(30000);
}

void enviarMensaje() {
  SIM800L.println("AT");
  updateSerial();
  SIM800L.println("AT+CMGS=?");
  updateSerial();
  SIM800L.println("AT+CMGF=1");// Cambiar a modo texto
  updateSerial();
  SIM800L.println("AT+CMGS=\"+542215062397\""); //Numero con codigo de area
  updateSerial();
  SIM800L.print("Comprobando desde SIM800L"); //Mensaje
  updateSerial();
  SIM800L.write(26);
}

void recibirMensaje() {

 //Lograr que nos muestre lo que nos llega de mensaje por el monitor serial.
  if(SIM800L.available()){
    valor = SIM800L.readString(); //Guardar en la var valor el sms que recibe el Arduino
    //Serial.println("Nuevo SMS: "+ valor); //Imprime ese SMS en el monitor Serial
  }
  
  Serial.println(valor);

}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    SIM800L.write(Serial.read());
  }
  while(SIM800L.available()) 
  {
    Serial.write(SIM800L.read());
  }
}