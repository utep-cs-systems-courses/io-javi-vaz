	.arch  msp430g2553
	.p2align 1,0
	.text

	.global updateBlinkFrequency
	.extern blinkFrequency

updateBlinkFrequency:
	cmp #1000,&blinkFrequency
	jge fourseconds
	cmp #500, &blinkFrequency
	jge twoseconds
	cmp #250, &blinkFrequency
	jge onesecond
	mov #250, &blinkFrequency
	pop r0
onesecond:
	mov #500, &blinkFrequency
	pop r0
twoseconds:
	mov #1000, &blinkFrequency
	pop r0
fourseconds:
	mov #125, &blinkFrequency
	pop r0
