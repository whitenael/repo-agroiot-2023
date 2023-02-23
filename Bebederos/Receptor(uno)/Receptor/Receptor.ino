//// Programa lado Receptor ////

#include <RH_ASK.h>   // incluye libreria RadioHead.h
#include <SPI.h>    // incluye libreria SPI necesaria por RadioHead.h

RH_ASK rf_driver;   // crea objeto para modulacion por ASK

#define LED 2   // reemplaza ocurrencia de LED por el numero 2
const int minute = 3600;
#define LED_2 4

 
void setup(){
    pinMode(LED, OUTPUT); // pin 2 como salida
    rf_driver.init();   // inicializa objeto con valores por defecto
    Serial.begin(9600);
}
 
void loop(){
    uint8_t buf[1];     // espacio para mensaje recibido de 1 caracter
    uint8_t buflen = sizeof(buf); // longitud de buffer
   // Serial.println("El bebedero tiene suficiente agua");
    //delay(30*minute);         // demora de 30 minutos.
    
    if (rf_driver.recv(buf, &buflen)) // si se recibieron datos correctos
    {      
      if((char)buf[0]=='1')   // si el caracter es el numero 1
        {
            digitalWrite(LED, HIGH); //aplica valor alto al led
            delay(300);
            digitalWrite(LED, LOW);
            delay(1000);
            Serial.println("Entre al LED verde");
        } 

        if((char)buf[0]=='2')   // si el caracter es el numero 1
        {
            digitalWrite(LED_2, HIGH); //aplica valor alto al led
            delay(300);
            digitalWrite(LED_2, LOW);
            delay(1000);
            Serial.println("Entre al LED ROJO");
            Serial.print("Largo de cadena: ");
            Serial.println(buflen);
        }                         
    }
}
