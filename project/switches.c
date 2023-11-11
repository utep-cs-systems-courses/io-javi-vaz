#include <msp430.h>
#include "switches.h"
#include "buzzer.h"

char switch_state_down, switch_state_changed; /* effectively boolean */

static char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */
  return p2val;
}

void
switch_init()/* setup switch */
{
  P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE |= SWITCHES;/* enable interrupts from switches */
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */
  switch_update_interrupt_sense();
}
int switches = 0;
void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
  if (switches & SW1) {
    buzzer_set_period(478); /* C */
  }else if(switches & SW2){
    buzzer_set_period(425); /* D */
  }else if (switches & SW3) {
    buzzer_set_period(379); /* E */
  }else if(switches & SW4){
    buzzer_set_period(338); /* F */
  } else {
    buzzer_set_period(0);
  }
}
