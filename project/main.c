#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

int main(void)
{
  led_init();
  configureClocks();
  enableWDTInterrupts();
  switch_init();
  buzzer_init();
  or_sr(0x18);
}

static int secondCount = 0;
int countState = 0;
void
__interrupt_vec(WDT_VECTOR) WDT()/* 250 interrupts/sec */

{
  if(secondCount>=250){
    switch(countState){
    case 0:
      P1OUT &= ~LEDS;
      break;
    case 1:
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
      break;
    case 2:
      P1OUT |= LED_RED;
      P1OUT &= ~LED_GREEN;
      break;
    case 3:
      P1OUT |= LEDS;
      break;
    }
    secondCount = 0;
    updateCountState();
  }
  secondCount++;
} 

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */
  }
}
