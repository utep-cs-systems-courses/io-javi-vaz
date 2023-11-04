
	.arch msp430g2553
	.p2align 1,0

	.data
red_on:		.word 0
green_on:	.word 0
led_changed:	.word 0

LEDS:		.word 1
	
redVal:		.word 0,1
greenVal:	.word 0,64
	
	.text

	.global led_init
	.global led_update
	.global red_on
	.global green_on
	.global led_changed
	.extern P1OUT
	.extern P1DIR
	bis.b #64, &LEDS

led_init:
	bis.b &P1DIR,&LEDS
	mov #1, &led_changed
	call #led_update
	pop r0

led_update:
	cmp #0, &led_changed
	jnz changed
	pop r0
changed:
	sub #1,r1
	
	mov &red_on, r12
	mov &green_on, r13
	bis.b greenVal(r13),redVal(r12)
	mov redVal(r12), 0(r1)

	xor.b #255,&LEDS
	bis.b &LEDS, 0(r1)
	and.b 0(r1), &P1OUT
	bis.b 0(r1), &P1OUT
	mov #0,&led_changed

	add #1, r1
	pop r0
