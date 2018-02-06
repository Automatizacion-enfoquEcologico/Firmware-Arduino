//  PINES

#define LDR1 7
#define LDR2 6
#define HIGROMETRO 5
#define CORRIENTE A0
#define RELE 13

//  ESTADOS

#define STBY 0        //Se verifica el estado del bufer, se leen las entradas y se encapsula parte de la trama.
#define LECTURA 1     //Lee la trama que llego y compara si hay algun cambio en la salida.
#define ENVIO 3       //Se envia la trama al DemoQE
#define SALIDAS 2     //Si hubo algun cambio en la salida reencapsula y actualizaq la salida (activa el riego).  

// ETIQUETAS PARA MASCARAS

#define LDR
#define H
#define INICIO 255


int estado = 0;
byte data_in = 0;
byte data_out = 0;
byte adc = 0;

bool riego = false;


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
    case STBY:
      if (Serial.available() > 0) {
        // read the incoming byte:
        data_in = Serial.read();
        //data_in = 0;
        // say what you got:
        Serial.write(data_in);
        digitalWrite(RELE, riego);
        riego = !riego;

        /*
          if(riego)digitalWrite(RELE,HIGH);
          else digitalWrite(RELE,LOW);
          riego = !riego;
          delay(50);
        */
      }

      break;
    case LECTURA:

      break;
    case ENVIO:

      break;

    case SALIDAS:

      break;
    default:

      break;


  }

}
