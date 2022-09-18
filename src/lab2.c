#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  //int ONE_SEG = 16000; // ~ un segundo para 16 MHz
  int ONE_SEG = 1000; // ~ un segundo para 1 MHz
  DDRB = 0x1F; //Configuracion del puerto, B[0-5] como salida


  //Parpadear
  while (1) {
    PORTB = 0x00; 
    _delay_ms(ONE_SEG);
    PORTB = 0x1F; 
    _delay_ms(ONE_SEG);
  }
}
