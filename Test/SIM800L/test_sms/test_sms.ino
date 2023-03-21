/*
 *Programa para mandar mensajes con el modulo SIM800L
 *Rafael Lozano Rolon
 *soporte@taloselectronics.com
 */
#include <SoftwareSerial.h>
#define Gsm_tx 12
#define Gsm_rx 13

unsigned long seconds = 1000L; //unsigned = solo almacena numeros positivos
unsigned long minutes = seconds * 60;
unsigned long hours = minutes * 60;
unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;
unsigned long tiempoSegundos = 0;

SoftwareSerial MOD_SIM800L(Gsm_tx, Gsm_rx);
String Numero_cliente = "150";

String apn_personal   = "internet.personal.com";
String apn_u_personal = "internet";
String apn_p_personal = "internet";

void setup()
{
  Serial.begin(9600); 
  MOD_SIM800L.begin(9600);

  MOD_SIM800L.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  MOD_SIM800L.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  MOD_SIM800L.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();

  gsm_recall();
  //enviarMensaje(Numero_cliente, "Saldo");
  
}
void loop()
{
  // gsm_recall();  
  enviarMensaje(Numero_cliente, "Saldo");
  delay(5*seconds);
  String valor = recibirMensaje();    
  
  String saldo = valor.substring(87, 257);

  Serial.println("---- NUEVO SMS RECIBIDO ------ ");
  Serial.println(saldo);
  Serial.println("---- FIN SMS RECIBIDO ------ ");
  Serial.println(valor.length());

  delay(30*seconds);
}
void enviarMensaje(String numero, String msj)
{
  //Se establece el formato de SMS en ASCII
  MOD_SIM800L.write(27);
  String config_numero = "AT+CMGS=\"" + numero + "\"\r\n";  
  MOD_SIM800L.println(config_numero);
  //Enviar contenido del SMS
  MOD_SIM800L.print(msj);
  delay(1000);

  //Enviar Ctrl+Z
  MOD_SIM800L.write((char)26);
  delay(1000);
  Serial.println("Mensaje enviado");
}

// void testearSenial(){
//   String senial;
//   MOD_SIM800L.println("AT+CSQ"); // Preguntamos por la senial
//   if(MOD_SIM800L.available()){
//     senial = MOD_SIM800L.readString(); //Guardar en la var valor el sms que recibe el Arduino
//     Serial.println("Intensidad de senal: "+ senial); //Imprime ese SMS en el monitor Serial
//     Serial.println("Fin de mensaje.");
//   }
//   delay(10000);
// }

String recibirMensaje() {
  String valor;
 //Lograr que nos muestre lo que nos llega de mensaje por el monitor serial.
  if(MOD_SIM800L.available()){
    valor = MOD_SIM800L.readString(); //Guardar en la var valor el sms que recibe el Arduino    
  }    
  return valor;
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    MOD_SIM800L.write(Serial.read());
  }
  while(MOD_SIM800L.available()) 
  {
    Serial.write(MOD_SIM800L.read());
  }
}

void gsm_recall(){

  String apn;
  String apn_u;
  String apn_p;

  apn = apn_personal;
  apn_u = apn_u_personal;
  apn_p = apn_p_personal;

  Serial.println("########## RECALLING... ##########");

  Serial.print("Señal del Modulo: ");
  MOD_SIM800L.println("AT+CSQ");
  print_gsm_status();
  delay(1*seconds);
  
  Serial.print("IP del servidor: ");
  MOD_SIM800L.println("AT+SAPBR=2,1");
  print_gsm_status();
  delay(1*seconds);

  MOD_SIM800L.println("AT+CGATT=1"); 
  print_gsm_status();
  delay(1000);

  MOD_SIM800L.println("AT+SAPBR=3,1,Contype,GPRS");
  print_gsm_status();
  delay(1000);
  
  MOD_SIM800L.println("AT+SAPBR=3,1,APN," + apn);
  print_gsm_status();
  delay(1000);
  
  MOD_SIM800L.println("AT+SAPBR=3,1,USER," + apn_u); 
  print_gsm_status();
  delay(1000);
  
  MOD_SIM800L.println("AT+SAPBR=3,1,PWD," + apn_p); 
  print_gsm_status();
  delay(1000);
  
  MOD_SIM800L.println("AT+SAPBR=1,1");
  print_gsm_status();
  delay(1000);
  
  delay(10000);
}

void print_gsm_status(){
  while(MOD_SIM800L.available()){
    Serial.write(MOD_SIM800L.read());
  }
}