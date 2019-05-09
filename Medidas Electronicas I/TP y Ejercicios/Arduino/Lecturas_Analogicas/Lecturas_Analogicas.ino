#define CUENTAS 1024.0 //ADC de 10 bits
#define VREF 5.0  //5 Volts
#define FACTOR_ESCALA VREF/CUENTAS
#define DEMORA 450

int analogPin=0;


void setup()
{
  Serial.begin(9600); //Inicializo puerto serie
//  analogReference(EXTERNAL);
}

int analogMeas;
float escalado;
void loop()
{
  
  analogMeas=analogRead(analogPin);
  escalado=analogMeas*FACTOR_ESCALA;
    
  Serial.println("Crudo\tEscalado");
  Serial.print(analogMeas); Serial.print("\t"); Serial.println(escalado);
  delay(DEMORA);
}
