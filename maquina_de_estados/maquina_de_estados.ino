//  PINES

//  ESTADOS

#define STBY 0        //Se verifica el estado del bufer, se leen las entradas y se encapsula parte de la trama.
#define LECTURA 1     //Lee la trama que llego y compara si hay algun cambio en la salida.
#define ENVIO 3       //Se envia la trama al DemoQE
#define SALIDAS 2     //Si hubo algun cambio en la salida reencapsula y actualizaq la salida (activa el riego).  

int estado = 0;

bool riego = false; 

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  switch (estado)
  {
  case STBY:
  
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
