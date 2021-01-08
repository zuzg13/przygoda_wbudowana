# przygoda_wbudowana

## Projekt realizowany przy pomocy mikrokontrolera LPC1786

### Rejestrator temperatury i wilgotności:
- aplikacja obsługuje podwójny czujnik temperatury i wilgotności ***DHT11***
- wyniki pomiarów są prezentowane w formie liczbowej i wykresów na wyświetlaczu
- aplikacja liczy wartości średnie: minutową i dziesięciominutową
- kilka wartości średnich z przeszłości wraz z czasem ich zebrania jest zapisanych w pamici Flash mikrokontrolera programowanej poprzez *In Application Programming (IAP)* i wyświetlanych na żądanie na drugim ekranie.
