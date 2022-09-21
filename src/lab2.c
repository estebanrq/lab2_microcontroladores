#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//#define  ONE_SEG  16000 // ~ un segundo para 16 MHz
#define ONE_SEG  1000 // ~ un segundo para 1 MHz
//            B    43210
#define Gv_Rp     0x06
#define Rv_Gp     0x11
#define Vy_blink  0b00001000
#define Gp_blink  0b00000001

void cars_pass(){
  PORTB = 0x06;
};
void cars_no_pass(){
  PORTB = 0x11;
  _delay_ms(ONE_SEG*5);
  PORTB = 0x10;
  _delay_ms(ONE_SEG/2);
  PORTB = 0x11;
  _delay_ms(ONE_SEG/2);
  PORTB = 0x10;
  _delay_ms(ONE_SEG/2);
  PORTB = 0x11;
  _delay_ms(ONE_SEG/2);
  PORTB = 0x10;
  _delay_ms(ONE_SEG/2);
  PORTB = 0x11;
  _delay_ms(ONE_SEG/2);
  PORTB = 0x10;
  _delay_ms(ONE_SEG);

};

ISR (INT0_vect){  
    _delay_ms(ONE_SEG/2);      
    PORTB = 0x02;
    _delay_ms(ONE_SEG/2);
    PORTB = 0x0A;
    _delay_ms(ONE_SEG/2);
    PORTB = 0x02;
    _delay_ms(ONE_SEG/2);
    PORTB = 0x0A;
    _delay_ms(ONE_SEG/2);    
    PORTB = 0x02;
    _delay_ms(ONE_SEG/2);
    PORTB = 0x0A;
    _delay_ms(ONE_SEG/2);
    PORTB = 0x02;
    _delay_ms(ONE_SEG);
    cars_no_pass();
}

//ISR (PCINT0_vect){        // Interrupt service routine 
//  PB5 < 1;    // Toggling the PB2 pin 
//}

void external_interrupt(){
  //DDRB |= (1<<PB1)|(1<<PB5);     // set PB2 as output(LED)
  sei();     //enabling global interrupt
  GIMSK |= (1<<INT0);     // enabling the INT0 (external interrupt) 
  MCUCR |= (1<<ISC01);    // Configuring as falling edge 
}

void pin_change_interrupt(){
  DDRB|=(1<<PB0);
  GIMSK|= (1<<PCIE0);
  PCMSK|=(1<<PCINT1);
}


///// MAIN ///// 
int main(void)
{
  DDRB = 0x1F; //Configuracion del puerto, B[0-5] como salida
  external_interrupt();
  //pin_change_interrupt();
  //Parpadear
  while (1) {
    cars_pass();
  }
}