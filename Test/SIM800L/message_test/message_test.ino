#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(12, 13);

void setup()
{
  Serial.begin(9600);
  gsmSerial.begin(9600);

  Serial.println("Inicializando..");
  delay(3000);

  gsmSerial.println("AT");
  updateSerial();
  gsmSerial.println("AT+CMGS=?");
  updateSerial();
  gsmSerial.println("AT+CMGF=1");// Cambiar a modo texto
  updateSerial();
  gsmSerial.println("AT+CMGS=\"+542215062397\""); //Numero con codigo de area
  updateSerial();
  gsmSerial.print("Comprobando desde SIM800L"); //Mensaje
  updateSerial();
  gsmSerial.write(26);
}

void loop()
{
  //No incluye loop
}

//Metodo de comunicacion serial
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    gsmSerial.write(Serial.read());
  }
  while(gsmSerial.available()) 
  {
    Serial.write(gsmSerial.read());
  }
}
