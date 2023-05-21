unsigned long seconds = 1000L; //unsigned = solo almacena numeros positivos
unsigned long minutes = seconds * 60;
unsigned long hours = minutes * 60;
unsigned long tiempoEncedido = 0;
unsigned long tiempoSegundos = 0;

float Sensibilidad=0.100; //sensibilidad en Voltios/Amperio para sensor de 20A
float calibreEncendido = 0.1;
int muestras = 500;

bool encendido = false;
bool estadoAnterior = false;

void setup() {
  
  encendido = estaEncendido();
  Serial.begin(9600);
}

void loop() {
      
  tiempoEncedido = GetTiempoEncendido();

  if (tiempoEncedido !=0){
    reportarTiempoEncendido();
  }
  
  delay(3*seconds);     
}

float GetCorriente(int n_muestras)
{
  float voltajeSensor;
  float corriente=0;
  for(int i=0;i<n_muestras;i++)
  {
    voltajeSensor = analogRead(A0) * (5.0 / 1023.0);    
    corriente=corriente+(voltajeSensor-2.5)/Sensibilidad; //Ecuación  para obtener la corriente
  }
  corriente=corriente/n_muestras;

  if (corriente<0)
    return 0;

  return(corriente);
}

bool estaEncendido(){
  float corriente = GetCorriente(muestras);

  if (corriente > calibreEncendido) {
    return true;
  }

  return false;
}

long GetTiempoEncendido(){

  int t = 0;
  encendido = estaEncendido();

  if (!encendido)
    Serial.println("Actualmente apagado...");

  while(encendido){
    t++;
    encendido = estaEncendido();
    Serial.println("Actualmente encendido...");
    Serial.println(t);
    delay(1*seconds);
  }

  return t;
}

void reportarTiempoEncendido(){
  Serial.print("El equipo estuvo encendido por: ");
  Serial.print(tiempoEncedido);
  Serial.println(" Segundos");
  tiempoEncedido=0;
}