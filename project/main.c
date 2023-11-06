#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "led.h"

int main{
  led_init();
  configureClocks();
  enabledWDTInterrupts();

  or_sr(0x18);
}

void

__interrupt_vec(WDT_VECTOR) WDT()/* 250 interrupts/sec */

{
  P1OUT ^= LEDS;
} 
