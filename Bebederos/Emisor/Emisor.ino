/// Programa lado Emisor ////

#include <RH_ASK.h>   // incluye libreria RadioHead.h
#include <SPI.h>    // incluye libreria SPI necesaria por RadioHead.h
 
RH_ASK rf_driver;   // crea objeto para modulacion por ASK

const int minute = 3600; //un minuto en segundos
volatile int estado = 0; 
void setup(){
     Serial.begin(9600);
     rf_driver.init();      // inicializa objeto con valores por defecto
     attachInterrupt(digitalPinToInterrupt(2), Bebedero, RISING); //Interrupcion para cuando el bebedero se queda sin agua
}
 
void loop(){
  int ant = 0;
  if(estado != ant)
  {
       const char *msg = "1";      // carga numero 1 en mensaje a enviar
       rf_driver.send((uint8_t *)msg, strlen(msg));  // envia el mensaje
       rf_driver.waitPacketSent();     // espera al envio correcto del mensaje
       estado = ant;
       Serial.println(*msg);
      
  }

}
void Bebedero()
{
estado++;  
}
