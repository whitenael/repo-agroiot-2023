#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const int minute = 3600; //un minuto en segundos
const int N = 3; //cantidad de bebederos
int t0 = 0; //tiempo referencial para el millis
int IDBebederos[N] = {0x01, 0x02, 0x03};
int estados[N]; //vector donde guardaremos los estados de los N bebederos

//Variable con la dirección del canal por donde se va a transmitir y recibir
byte direccion[5] ={'c','a','n','a','l'};

//Creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

void setup() 
{
  //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600);
  //Abrimos canal de escritura
  radio.openWritingPipe(direccion); 
}

void loop() 
{
  if(millis() - t0 > 30*minute) //cada 30 minutos...
  {
    t0 = millis();
    for(int i = 0; i <= N; i++)
    {
      radio.write(&IDBebederos[i], sizeof(IDBebederos[i])); //enviamos a los slaves los ID secuencialmente
      radio.startListening(); //El maestro pasa a receptor
      radio.openReadingPipe(1, direccion); //abrimos el canal de lectura
      if(radio.available()) //Si hay datos disponibles...
      {
        radio.read(&estados[i], sizeof(estados[i])); //leemos los estados y los guardamos en el array datos[]
      }
      radio.stopListening(); //El maestro pasa a emisor
    }
  }
}
