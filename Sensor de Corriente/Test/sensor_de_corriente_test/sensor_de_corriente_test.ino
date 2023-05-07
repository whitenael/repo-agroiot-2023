float Sensibilidad=0.100; //sensibilidad en Voltios/Amperio para sensor de 20A
int calibre = 500;

void setup() {
  
  Serial.begin(9600);
}

void loop() {
  
  float I=get_corriente(calibre);//obtenemos la corriente promedio de 500 muestras 
  Serial.print("Corriente: ");
  Serial.print(I,3); 
  Serial.println("A");
  Serial.print("Lectura real: ");
  Serial.println(analogRead(A0));
  delay(1000);     
}

float get_corriente(int n_muestras)
{
  float voltajeSensor;
  float corriente=0;
  for(int i=0;i<n_muestras;i++)
  {
    voltajeSensor = analogRead(A0) * (5.0 / 1023.0);
    ////lectura del sensor
    corriente=corriente+(voltajeSensor-2.5)/Sensibilidad; //Ecuación  para obtener la corriente
  }
  corriente=corriente/n_muestras;

  if (corriente<0)
    return 0;

  return(corriente);
}

float get_corriente_sin_filtro(){
  float voltajeSensor= analogRead(A0)*(5.0 / 1023.0); //lectura del sensor   
  float corriente=(voltajeSensor-2.5)/Sensibilidad; //Ecuación  para obtener la corriente

  return corriente;

}