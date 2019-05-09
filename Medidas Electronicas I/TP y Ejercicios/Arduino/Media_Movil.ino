#define CUENTAS 1024.0 //ADC de 10 bits
#define VREF 5.0  //5 Volts
#define FACTOR_ESCALA VREF/CUENTAS
#define LECTURAS 8
#define DEMORA 450


int analogPin=0;
int analogMed;
float escalado;
float escaladoMM;
float mediaMovil;
int readings[LECTURAS];
char indexIn;
bool primeras;

void setup()
{
  Serial.begin(9600); //Inicializo puerto serie
  indexIn=0;
  primeras=true;
//  analogReference(EXTERNAL);
}

int cont=0;

void loop()
{

  analogMed=analogRead(analogPin);
  
  escalado=analogMed*FACTOR_ESCALA;
  readings[indexIn]=analogMed;
  indexIn++;
  
  if( primeras )  //todavia no hay LECTURAS-1 disponibles
  {
    if ( indexIn==LECTURAS-1 )  //con la proxima ya tengo LECTURAS-1 y puedo promediar
    {
      primeras=false;
    }

    Serial.print(cont);Serial.println(":");
    Serial.println("Crudo\tEscalado");
    Serial.print(analogMed); Serial.print("\t"); Serial.println(escalado);
    
  }else{
 
    indexIn%=LECTURAS;
    mediaMovil=0;
    for (char j=0;j<LECTURAS; j++)
    {
      mediaMovil+=readings[j];
    }
    mediaMovil/=LECTURAS;
    escaladoMM=mediaMovil*FACTOR_ESCALA;
    Serial.print(cont);Serial.println(":");
    Serial.println("Crudo\tEscalado\tMedia Movil");
    Serial.print(analogMed); Serial.print("\t"); Serial.print(escalado); Serial.print("\t"); Serial.println(escaladoMM);    
    
    
  }
  
  cont++;
  delay(DEMORA);
}
