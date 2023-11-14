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
int blinkFrequency = 1;
static int blinks = 0;
static int secondCount = 0;
int countState = 0;
short count = 0;
void
__interrupt_vec(WDT_VECTOR) WDT()/* 250 interrupts/sec */

{
  if(secondCount>=250){
    switch(countState){ /* Updates the counting number each second */
    case 0:
      count &= ~LEDS;
      break;
    case 1:
      count |= LED_GREEN;
      count &= ~LED_RED;
      break;
    case 2:
      count |= LED_RED;
      count &= ~LED_GREEN;
      break;
    case 3:
      count |= LEDS;
      break;
    }
    secondCount = 0;
    updateCountState();
    
    blinkFrequency += 5; /* Makes the light brighter with each second*/
    if(blinkFrequency>30){
      blinkFrequency = 1;
    }
  }
  secondCount++;
  
  if(blinks>=blinkFrequency){ /* Lights up the proper leds at the given brightness */
    blinks = 0;
    P1OUT = count;
  }else{
    P1OUT &= ~LEDS;
  }
  blinks++;
} 

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */
  }
}
