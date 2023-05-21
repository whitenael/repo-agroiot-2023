#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const int minute = 3600; //un minuto en segundos
const int N = 3; //cantidad de bebederos
int t0 = 0; //tiempo referencial para el millis
int IDBebederos[N]; //Vector que guardará los ID de los bebederos
int estados[N]; //vector donde guardaremos los estados de los N bebederos

//Variable con la dirección del canal por donde se va a transmitir y recibir
byte direccion[5]={'c','a','n','a','l'};

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
  Serial.println("Iniciando Maestro...");
  
  for(int j = 0x01; j <= N; j = j + 0x01) //Codifico los ID y los almaceno en el array segun N cantidad
  {
    IDBebederos[j-1] = j; 
    Serial.println(j);
  }
}

void loop() 
{
  if(millis() - t0 > 5000) //cada t minutos...
  {
    t0 = millis();
    for(int i = 0; i < N; i++)
    {
      radio.write(&IDBebederos[i], sizeof(IDBebederos[i])); //enviamos a los slaves los ID secuencialmente

      radio.openReadingPipe(1, direccion); //abrimos el canal de lectura
      radio.startListening(); //El maestro pasa a receptor

    for (int j = 0; j <= 100; j++){
      if(radio.available()) //Si hay datos disponibles...
      {
        radio.read(&estados[i], sizeof(estados[i])); //leemos los estados y los guardamos en el array estados[]
        Serial.print("SE REGISTRO UNA RESPUESTA DEL BEBEDERO ");
        Serial.println(i);

        Serial.print("Estado: ");
        Serial.println(estados[i]);
      }
      delay(100);
    }     
      Serial.print("No se registro respuesta del BEBEDERO: ");
      Serial.println(i);

      radio.stopListening(); //El maestro pasa a emisor
    }
  }
  delay(1000);
}
