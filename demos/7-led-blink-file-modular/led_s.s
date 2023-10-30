	.arch msp430g2553
	.p2align 1,0

	.data
red_on:		.byte 0
green_on:	.byte 0
led_changed:	.byte 0
ledFlags:	.byte 0

redVal:	.word 0,&LED_RED
greenVal:	.word 0,&LED_GREEN
	
	.text

	.global led_init
	.global led_update
	.extern P1OUT
	.extern P1DIR
	.extern LEDS

led_init:
	bis.b &P1DIR,&LEDS
	mov #1, &led_changed
	call #led_update
	pop r0

led_update:
	cmp #0, &led_changed
	jmp changed
changed:	
	bis.b &ledFlags
