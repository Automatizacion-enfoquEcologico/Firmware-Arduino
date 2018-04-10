

#define RAIZ 1.4142 // SQRT(2)
#define I_V 0.4457  // 1.56A / 3.5V
#define R_ENVIO 10502 // 0x3FFF/1.56 
#define T 50       //milisegundos tiempo para 3 ciclos a 60 HZ

//  PINES

#define LDR1 10
#define LDR2 11
#define HIGROMETRO 12
#define SCT A5
#define RELE 13

//  ESTADOS

#define ESPERA 0        //Se verifica el estado del bufer, se leen las entradas y se encapsula parte de la trama.
#define LECTURA 1     //Lee la trama que llego y compara si hay algun cambio en la salida.
#define ENVIO 3       //Se envia la trama al DemoQE
#define SALIDAS 2     //Si hubo algun cambio en la salida reencapsula y actualizaq la salida (activa el riego).  


// ETIQUETAS

#define INICIO 0xFF
#define tam_trama 4

int cont = 0;
int estado = ESPERA;
byte data_in = 0;
byte data_out = 0;
unsigned int adc = 254;
byte ldr = 0;
byte higrometro = 0;
float Irms = 0;
float Irms_pre = 0;
float vsct; //voltaje instantaneo del sensor
float sum = 0;  // acumulador de la suma del cuadrado de voltaje
int cont_s = 0;    // Periodo discreto
long tiempo = 0; // referencia temporal
int estado_espera = 0;
bool calcular = true;
bool riego = false;
byte trama [tam_trama] = {INICIO, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode (LDR1, INPUT_PULLUP);
  pinMode (LDR2, INPUT_PULLUP);
  pinMode (HIGROMETRO, INPUT_PULLUP);
  pinMode (RELE, OUTPUT);

  digitalWrite (RELE, !riego);
}

void loop() {
  // put your main code here, to run repeatedly:

  switch (estado)
  {
    case ESPERA:
      if (calcular) {
        sum = 0;
        cont_s = 0;
        Irms_pre = Irms;
        Irms = 0;
        estado_espera = 1;
        tiempo = millis();
        calcular = false;
      }
      else if (millis() - tiempo < T) // muestreo de la señal en T =  n vaces el periodo
      {
        vsct = analogRead(SCT) * (5 / 1023.0);//voltaje del sensor
        sum = sum + sq(vsct); //Sumatoria de Cuadrados
        cont_s = cont_s + 1;  // cuenta cada vez que toma una muestra
        delay(1);
      } else {
        vsct = sqrt((sum) / cont_s);
        Irms = vsct * I_V * RAIZ;
      }
      if (Serial.available() > 0)
      {
        estado = LECTURA;
        calcular = true;
      }

      break;
    case LECTURA:
      estado_espera = 0; //reinicio del estado ESPERA
      actualizar_entradas();
      data_in = Serial.read();

      if (data_in == 0xFF && riego) {
        riego = true;
        estado = ENVIO;
      } else  if (data_in == 0xFF && !riego) {
        riego = true;
        estado = SALIDAS;
      }
      else if (data_in == 0xF0 && !riego) {
        riego = false;
        estado = ENVIO;
      }
      else if (data_in == 0xF0 && riego) {
        riego = false;
        estado = SALIDAS;
      }
      break;
    case ENVIO:

      encapsular();
      for (cont = 0; cont < tam_trama; cont++)
      {
        Serial.write(trama[cont]);
      }
      estado = ESPERA;
      break;

    case SALIDAS:
      digitalWrite(RELE, !riego);
      estado = ENVIO;
      break;
    default:

      break;
  }

}

void encapsular(void)
{
  adc = Irms * R_ENVIO;
  if (adc > 0x3FFF) {
    adc = 0x3FFF;
  }
  adc = adc << 1;
  trama[1] = adc >> 8;
  trama[2] = adc & 0x00FF;
  trama[3] = ldr << 2;
  trama[3] = trama[3] + higrometro + riego;
}

void actualizar_entradas(void)
{
  ldr = 0;
  ldr = (!digitalRead(LDR1)) << 1;
  ldr = ldr + (!digitalRead(LDR2));
  higrometro = (!digitalRead(HIGROMETRO)) << 1;
}
void actualizar_entradas_deprueba(void)
{
  ldr = 0;
  ldr = HIGH << 1;
  ldr = ldr + HIGH;
  higrometro = HIGH << 1;
}

