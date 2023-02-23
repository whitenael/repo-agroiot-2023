#include <RH_ASK.h>
#include <SPI.h>

unsigned long seconds = 1000L; //unsigned = solo almacena numeros positivos
unsigned long minutes = seconds * 60;
unsigned long hours = minutes * 60;
unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;
unsigned long tiempoSegundos = 0;

const byte respuestaLen = 10; // Tamanio esperado de respuesta
int IdBebedero = 1;
const int cantBebedeors = 3;

RH_ASK askResponse;
RH_ASK askRequest;


// msg: es el array donde se almacenara el mensaje recibido
// msgLen: es la longitud esperada del mensaje

// En el caso de que se haya recibido un mensaje y este sea correcto, esta función devuelve true. 
// En caso contrario devuelve false.

    

void setup() {
  Serial.begin(9600);
  askResponse.init();
  askRequest.init();

}

void loop() {

  char medidasBebederos[cantBebedeors];
  int intentos = 0;

  while (IdBebedero != cantBebedeors)
  {
    // #### ENVIO SOLICITUD DE MEDICION #### // 
    char *request = IdBebedero;

    // Envio el mensaje
    askRequest.send((uint8_t *)request, strlen(*request));
    askRequest.waitPacketSent();

    // #### RECIBO REPUESTA DE MEDICION #### // 

    // Tamanio esperado del mensaje
    uint8_t msg[respuestaLen];
    uint8_t msgLen = sizeof(msg);

    // Comprobar si el mensaje recibido tiene el tamanio esperado

    while (intentos <= 100) 
    {
      if (askResponse.recv(msg, &msgLen))
      {
        // Mensaje de exito
        Serial.print("Dato recibido: ");
        Serial.println((char*)msg);

        medidasBebederos[IdBebedero] = (char*)msg; // Agregamos el dato al arreglo
        break;
      }
    
      intentos++;    
    }
    
    IdBebedero++; // Pasamos al siguiente bebedero
  }

  delay(30*seconds);
}
