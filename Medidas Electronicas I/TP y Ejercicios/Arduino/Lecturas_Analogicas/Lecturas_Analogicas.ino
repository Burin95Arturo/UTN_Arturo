#define CUENTAS 1024.0 //ADC de 10 bits
#define VREF 3.3  //3,3 Volts
#define FACTOR_ESCALA VREF/CUENTAS
#define DEMORA 450

#define S 0.00018765 //pediente -> coeficiente de sensibilidad 

int analogPin=0;


void setup()
{
  Serial.begin(9600); //Inicializo puerto serie
  analogReference(EXTERNAL);
}


int analogMeas;
float escalado;
float i = 0;
float voff = 0; 
float s = 0.00018765;
int flag_medicion_offset = 1;
float promi = 0;
float contador = 0;
float suma = 0;
int var = 0;

void loop()
{ 
  //medicion del voff
  if(flag_medicion_offset){
        for(var=0;var<50;var++){
            analogMeas=analogRead(analogPin);
            escalado=analogMeas*FACTOR_ESCALA;  
            suma = suma + escalado;
        }
        voff= suma/50;
        Serial.print("Voff final\t");Serial.println(voff);
        flag_medicion_offset = 0;
        suma = 0;
  }
  
  //medicion de la corriente
  analogMeas=analogRead(analogPin);
  escalado=analogMeas*FACTOR_ESCALA; 
  i = (escalado - voff) / S;
  suma = suma + i;
  contador ++;
  if(contador == 1000){
      promi = suma/contador;
      //Serial.println("Crudo\tEscalado");
      //Serial.print(analogMeas); Serial.print("\t"); Serial.println(escalado);
      Serial.print("Corriente mA\t"); Serial.print(promi); Serial.print("\t"); Serial.print("Tension\t"); Serial.println(escalado);
      Serial.print("Numero de mediciones para el promedio de I: \t");Serial.println(contador);
      delay(DEMORA); 
      contador = 0; 
      suma = 0;
      promi = 0;
      i = 0;
  }
}
