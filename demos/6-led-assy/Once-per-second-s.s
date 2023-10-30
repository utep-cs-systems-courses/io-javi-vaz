	.arch msp430g2553
	.p2align 1,0
	.text

	.global oncePerSecond
	.extern blinkLimit

oncePerSecond:
	add #1, &blinkLimit
	cmp #8, &blinkLimit
	jc reset
	pop r0
reset:
	mov #0, &blinkLimit
	pop r0
