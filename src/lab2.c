#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//#define  ONE_SEG  16000 // ~ 1 s for 16 MHz
#define ONE_SEG  1000 // ~ 1 s for 1 MHz
#define CAR_PASS      0x06
#define CAR_BLINK     0x02
#define CAR_BLINK2    0x0A
#define PED_PASS      0x11
#define PED_BLINK     0x10
#define PED_PASS_TIME 11*ONE_SEG

void cars_pass();
void cars_blink();
void pedestrian_blink();
void cars_no_pass();
void external_interrupt();

///// MAIN ///// 
int main(void)
{
  DDRB = 0x1F; //configuring ports: B[0-5] as Output
  external_interrupt();
  while (1) {
    // cars will keep passing until botton pressed
    cars_pass();
  }
}

//// FUNCTIONS ////

void cars_pass(){
  PORTB = CAR_PASS;
};

void cars_blink(){
  _delay_ms(ONE_SEG/2);   
  PORTB = CAR_BLINK;
  _delay_ms(ONE_SEG/2);
  PORTB = CAR_BLINK2;
  _delay_ms(ONE_SEG/2);
  PORTB = CAR_BLINK;
  _delay_ms(ONE_SEG/2);
  PORTB = CAR_BLINK2;
  _delay_ms(ONE_SEG/2);    
  PORTB = CAR_BLINK;
  _delay_ms(ONE_SEG/2);
  PORTB = CAR_BLINK2;
  _delay_ms(ONE_SEG/2);
  PORTB = CAR_BLINK;
  _delay_ms(ONE_SEG);
};

void pedestrian_blink(){
  PORTB = PED_BLINK;
  _delay_ms(ONE_SEG/2);
  PORTB = PED_PASS;
  _delay_ms(ONE_SEG/2);
  PORTB = PED_BLINK;
  _delay_ms(ONE_SEG/2);
  PORTB = PED_PASS;
  _delay_ms(ONE_SEG/2);
  PORTB = PED_BLINK;
  _delay_ms(ONE_SEG/2);
  PORTB = PED_PASS;
  _delay_ms(ONE_SEG/2);
  PORTB = PED_BLINK;
  _delay_ms(ONE_SEG);
};
void cars_no_pass(){
  //pedestrians pass:
  PORTB = PED_PASS;
  _delay_ms(PED_PASS_TIME);
  //blink pedestrians:
  pedestrian_blink();
};

ISR (INT0_vect){  
    //blink cars:
    cars_blink();
    // car no pass
    cars_no_pass();
}

void external_interrupt(){
  sei();     //enabling global interrupt
  GIMSK |= (1<<INT0);     // enabling the INT0 (external interrupt) 
  MCUCR |= (1<<ISC01);    // Configuring as falling edge
}
