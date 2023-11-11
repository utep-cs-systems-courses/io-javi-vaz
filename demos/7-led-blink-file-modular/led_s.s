
	.arch msp430g2553
	.p2align 1,0

	.data
red_on:		.word 0
green_on:	.word 0
led_changed:	.word 0

LEDS:		.word 65
	
redVal:		.word 0,1
greenVal:	.word 0,64
	
	.text

	.global led_init
	.global led_update
	.global red_on
	.global green_on
	.global led_changed
	.global LEDS
	.extern P1OUT
	.extern P1DIR

led_init:
	bis &P1DIR,&LEDS
	mov #1, &led_changed
	call #led_update
	pop r0

led_update:
	cmp #0, &led_changed
	jnz changed
	pop r0
changed:
	sub #4,r1
	
	mov &red_on, r12
	mov &green_on, r13
	mov redVal(r12), 0(r1)
	bis greenVal(r13),0(r1)

	mov &LEDS, 2(r1)
	xor #255, 2(r1)
	bis 0(r1), 2(r1)
	and 2(r1), &P1OUT
	bis 0(r1), &P1OUT
	mov #0,&led_changed

	add #4, r1
	pop r0
