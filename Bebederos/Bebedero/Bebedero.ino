#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ID_BEBEDERO 0x01
#define LED 2
//Declaramos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10

const int minute = 3600; //un minuto en segundos
volatile int estado = 0;
int t0 = 0; //tiempo referencial para el millis

int ID; //Variable donde guardaremos los ID enviados desde el Maestro

//Variable con la dirección del canal por donde se va a transmitir y recibir
byte direccion[5] ={'c','a','n','a','l'};

//Creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

void setup() 
{
  pinMode(LED, OUTPUT);
  //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
  Serial.println("Iniciando Bebedero...");
  //Abrimos un canal de lectura
  radio.openReadingPipe(1,direccion);
  //Empezamos a escuchar por el canal
  radio.startListening(); 

  //Interrupcion para cuando el bebedero se queda sin agua
  attachInterrupt(digitalPinToInterrupt(2), EstadoBebedero, RISING); 
}

void loop()
{
  const int ant = 0;
  if(radio.available()) //Si hay mensajes disponibles...
  {
    //leemos el ID enviado desde el Maestro y lo guardamos en la variable ID
    radio.read(&ID, sizeof(ID));
    Serial.print("Identificando ID...");   
    if(ID_BEBEDERO == ID) //comparamos el ID mandado desde el Maestro con el del Bebedero
    {
      radio.stopListening(); //el bebedero pasa a emisor
      radio.closeReadingPipe(direccion); //cierro el canal de lectura
      radio.openWritingPipe(direccion); //abro el canal de escritura
      Serial.println(ID);  
      Serial.println("ID Identificado exitosamente");      
      if(estado != ant) //me pregunto si el bebedero reporto falta de agua
      {
        radio.write(&estado, sizeof(estado)); //enviamos un 1 desde el bebedero
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED,LOW);                
        Serial.print("Estado: ");
        Serial.println(estado);
      }
      else //sino...
      {  
        radio.write(&ant, sizeof(ant)); //enviamos un 0
        Serial.print("Estado: ");
        Serial.println(ant);
      } 
    }     
  }    

  delay(1000);
}

void EstadoBebedero()
{
  estado = 1;    
}