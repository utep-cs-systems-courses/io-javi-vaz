#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

#define SW1 BIT3		/* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */

void main(void) 
{  
  configureClocks();
  enableWDTInterrupts();

  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */

  or_sr(0x18);  // CPU off, GIE on
} 

char toggle = 0;
void
switch_interrupt_handler()
{
  char p1val = P1IN;		/* switch is in P1 */

/* update switch interrupt sense to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */

/* up=red, down=green */
  if (p1val & SW1) {
    toggle++;
    // P1OUT |= LED_RED;
    //P1OUT &= ~LED_GREEN;
  } else {
    toggle++;
    //P1OUT |= LED_GREEN;
    //P1OUT &= ~LED_RED;
  }
  switch(toggle){
  case 1:
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
    break;
  case 2:
    break;
  case 3:
    P1OUT &= ~LED_RED;
    P1OUT |= LED_GREEN;
    break;
  case 4:
    toggle = 0;
    break;
    
  }
  
    
}


/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P1IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

// global state var to count time

int secondCount = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()/* 250 interrupts/sec */
{
  secondCount ++;
  if (secondCount >= 125) { /* once each sec... */
    secondCount = 0;/* reset count */
    //P1OUT ^= LED_GREEN;/* toggle green LED */
    //P1OUT ^= LED_RED;           /* toggle red LED */
    switch(toggle){
    case 0:
      P1OUT |= LEDS;
      break;
    default:
      P1OUT ^= LEDS;
      break;
    }
  }
} 
