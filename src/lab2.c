#include <avr/io.h>
#include <util/delay.h>

//#define  ONE_SEG  16000 // ~ un segundo para 16 MHz
#define ONE_SEG  1000 // ~ un segundo para 1 MHz

void pass_ped(int state);
void pass_veh(int state);


int main(void)
{
  DDRB = 0x1F; //Configuracion del puerto, B[0-5] como salida


  //Parpadear
  while (1) {
    PORTB = 0x00; 
    _delay_ms(ONE_SEG);
    PORTB = 0x1F; 
    _delay_ms(ONE_SEG);
  }
}

void pass_ped(int state){
  
};
void pass_veh(int state){
  
};