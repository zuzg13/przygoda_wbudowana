# przygoda_wbudowana

## Projekt realizowany przy pomocy mikrokontrolera LPC1786

### Rejestrator temperatury i wilgotności:
- aplikacja obsługuje podwójny czujnik temperatury i wilgotności ***DHT11***
- wyniki pomiarów są prezentowane w formie liczbowej i wykresów na wyświetlaczu
- aplikacja liczy wartości średnie: minutową i dziesięciominutową
- kilka wartości średnich z przeszłości jest zapisanych w pamici Flash mikrokontrolera programowanej poprzez *In Application Programming (IAP)* i wyświetlanych na żądanie na drugim ekranie.

#### Funkcje związane z obsługą **IAP** są dostarczone z ogólnodostępnej biblioteki, dostępnej pod linkiem: [Firmware v2](https://github.com/ciaa/firmware_v2/tree/master/modules/lpc4337_m0/chip?fbclid=IwAR1Ff6qp_C65uYhZHZHFnJ-I0UVIhBOzcH_O-9MIg0_ZHXMGwxBFBQyllgA).
