# przygoda_wbudowana
##(eng below)
## Projekt realizowany przy pomocy płytki LPC1786 z mikrokontrolerem ARM Cortex M3

### Rejestrator temperatury i wilgotności:
- aplikacja obsługuje podwójny czujnik temperatury i wilgotności ***DHT11***
- wyniki pomiarów są prezentowane w formie liczbowej i wykresów na wyświetlaczu
- aplikacja liczy wartości średnie: minutową i dziesięciominutową
- kilka wartości średnich z przeszłości jest zapisanych w pamici Flash mikrokontrolera programowanej poprzez *In Application Programming (IAP)* i wyświetlanych na żądanie na drugim ekranie.

#### Funkcje związane z obsługą **IAP** są dostarczone z ogólnodostępnej biblioteki, dostępnej pod linkiem: [Firmware v2](https://github.com/ciaa/firmware_v2/tree/master/modules/lpc4337_m0/chip?fbclid=IwAR1Ff6qp_C65uYhZHZHFnJ-I0UVIhBOzcH_O-9MIg0_ZHXMGwxBFBQyllgA).

##English description
## Projekt realizowany przy pomocy płytki LPC1786 z mikrokontrolerem ARM Cortex M3

### Temperature and humidity recorder:
- the application supports a dual temperature and humidity sensor *** DHT11 ***
- measurement results are presented in the form of numbers and graphs on the display
- the application calculates the average values: minute and ten minutes
- several past average values are stored in the Flash memory of the microcontroller programmed via * In Application Programming (IAP) * and displayed on demand on the second screen.

#### Features related to the operation of ** IAP ** are provided from the public library, available at the link: [Firmware v2]
