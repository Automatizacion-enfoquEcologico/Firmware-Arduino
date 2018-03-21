# Firmware-Arduino

Contiene el programa en C++ que ejecuta el modulo externo (Arduino UNO) configurado como esclavo.

Este modulo esta diseñado con el objetivo de tener un subsistema para capturar data del ambiente en el exterior del hogar, para ser transmitida al modulo central en el interior del hogar con un solo enlace mediante comunicacion serial a 9600baudios.

Entradas:
=

+ Potencia instantanea consumida en el hogar, a traves de entrada analogica.
+ Intensidad de luz mediante dos entradas digitales:
00- Ausencia luz.
01- Intensidad media de luz.
11- Intensidad Alta de luz.
+ Humedad del suelo mediante entrada digital.

Salida:
=
+ salida digital a relevador para activar valvula de riego.
