#include <RH_ASK.h>
#include <SPI.h>

const char id = 1;

RH_ASK askRequest;
RH_ASK askResponse;

const byte solicitudLen = 1;


void setup()
{
  Serial.begin(9600);
  askRequest.init();
  askResponse.init();
}

void loop()
{      
   uint8_t msg[solicitudLen];
   uint8_t msgLen = sizeof(msg);

  if (askResponse.recv(msg, &msgLen))
  {
    if (msg[0] == id){
      // Le envio medida actual del sensor
      char estado = "F"; // F = LLENO, E = VACIO
      char *msg = estado; 

      // Envio la informacion
      askRequest.send((uint8_t *)msg, strlen(*msg));
      askRequest.waitPacketSent();
    }
  }

}
