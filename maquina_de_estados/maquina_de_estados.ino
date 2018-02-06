//  PINES

#define LDR1 7
#define LDR2 6
#define HIGROMETRO 5
#define CORRIENTE A0
#define RELE 13

//  ESTADOS

#define ESPERA 0        //Se verifica el estado del bufer, se leen las entradas y se encapsula parte de la trama.
#define LECTURA 1     //Lee la trama que llego y compara si hay algun cambio en la salida.
#define ENVIO 3       //Se envia la trama al DemoQE
#define SALIDAS 2     //Si hubo algun cambio en la salida reencapsula y actualizaq la salida (activa el riego).  

// ETIQUETAS


#define INICIO 0xFF
#define tam_trama 3

int cont = 0;
int estado = ESPERA;
byte data_in = 0;
byte data_out = 0;
byte adc = 254;
byte ldr = 0;
byte higrometro = 0;


bool riego = false;
byte trama [tam_trama] = {INICIO, 0, 0};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode (LDR1, INPUT_PULLUP);
  pinMode (LDR2, INPUT_PULLUP);
  pinMode (HIGROMETRO, INPUT_PULLUP);
  pinMode (RELE, OUTPUT);

  digitalWrite (RELE, riego);
}

void loop() {
  // put your main code here, to run repeatedly:

  switch (estado)
  {
    case ESPERA:
      actualizar_entradas_deprueba();
      if (Serial.available() > 0) {
        // read the incoming byte:
        estado = LECTURA;
      }
      break;
    case LECTURA:

      encapsular();
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
      for (cont = 0; cont < tam_trama; cont++)
      {
        Serial.write(trama[cont]);
      }
      estado = ESPERA;
      break;

    case SALIDAS:
      digitalWrite(RELE, riego);
      encapsular();
      estado = 3;
      break;
    default:

      break;


  }

}

void encapsular(void)
{
  trama[1] = adc; // Prueba
  trama[2] = ldr << 2;
  trama[2] = trama[2] + higrometro + riego;
}

void actualizar_entradas(void)
{
  ldr = 0;
  adc = digitalRead(CORRIENTE) / 4;
  if (adc == 255)adc = 254;
  ldr = digitalRead(LDR1) << 1;
  ldr = ldr + digitalRead(LDR2);
  higrometro = digitalRead(HIGROMETRO) << 1;
}
void actualizar_entradas_deprueba(void)
{
  ldr = 0;
  adc = 255;
  if (adc == 255)adc = 254;
  ldr = HIGH << 1;
  ldr = ldr + HIGH;
  higrometro = HIGH << 1;
}



