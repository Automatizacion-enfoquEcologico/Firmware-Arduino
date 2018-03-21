# Firmware-Arduino

Contiene el programa en C++ que ejecuta el modulo externo (Arduino UNO) configurado como esclavo.

Este módulo está diseñado con el objetivo de tener un subsistema para capturar data del ambiente en el exterior del hogar, para ser transmitida al módulo central en el interior del hogar con un solo enlace mediante comunicación serial a 9600baudios.

Entradas:
=

+ Potencia instantánea consumida en el hogar, a través de entrada analógica.
+ Intensidad de luz mediante dos entradas digitales:
00- Ausencia luz.
01- Intensidad media de luz.
11- Intensidad Alta de luz.
+ Humedad del suelo mediante entrada digital.

Salida:
=
+ Salida digital a relevador para activar válvula de riego.
