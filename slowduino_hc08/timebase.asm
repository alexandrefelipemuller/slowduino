;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.2.0 #13081 (Linux)
;--------------------------------------------------------
	.module timebase
	.optsdcc -mhc08
	
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
	.area XINIT   (CODE)
	.area CONST   (CODE)
	.area DSEG    (PAG)
	.area OSEG    (PAG, OVR)
	.area XSEG
	.area XISEG
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _isr_tim2_overflow
	.globl _timebaseInit
	.globl _micros
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DSEG    (PAG)
;--------------------------------------------------------
; overlayable items in ram
;--------------------------------------------------------
;--------------------------------------------------------
; absolute ram data
;--------------------------------------------------------
	.area IABS    (ABS)
	.area IABS    (ABS)
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG
;--------------------------------------------------------
; extended address mode data
;--------------------------------------------------------
	.area XSEG
_tim2OverflowCount:
	.ds 4
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'noInterrupts'
;------------------------------------------------------------
;globals.h:100: static inline void noInterrupts(void) { __asm sei __endasm; }
;	-----------------------------------------
;	 function noInterrupts
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_noInterrupts:
	 sei	
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'interrupts'
;------------------------------------------------------------
;globals.h:101: static inline void interrupts(void)   { __asm cli __endasm; }
;	-----------------------------------------
;	 function interrupts
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_interrupts:
	 cli	
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'timebaseInit'
;------------------------------------------------------------
;timebase.c:15: void timebaseInit(void) {
;	-----------------------------------------
;	 function timebaseInit
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_timebaseInit:
;timebase.c:16: T2SC = (1 << T2SC_TRST);  /* reset do contador */
	mov	#0x10,*0x2b
;timebase.c:17: T2SC = (1 << T2SC_TOIE);  /* liga overflow interrupt, prescaler /1, roda */
	mov	#0x40,*0x2b
;timebase.c:18: tim2OverflowCount = 0;
	ldhx	#_tim2OverflowCount
	clra
	sta	,x
	sta	1,x
	sta	2,x
	sta	3,x
;timebase.c:19: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'micros'
;------------------------------------------------------------
;overflows                 Allocated to stack - sp +1
;count                     Allocated to registers x h 
;sloc0                     Allocated to stack - sp +13
;sloc1                     Allocated to stack - sp +9
;sloc2                     Allocated to stack - sp +5
;------------------------------------------------------------
;timebase.c:21: uint32_t micros(void) {
;	-----------------------------------------
;	 function micros
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 14 bytes.
_micros:
	ais	#-14
;timebase.c:30: }
	tpa
	sei
	psha
;timebase.c:28: overflows = tim2OverflowCount;
	tsx
	ldhx	#_tim2OverflowCount
	lda	,x
	sta	2,s
	lda	1,x
	sta	3,s
	lda	2,x
	sta	4,s
	lda	3,x
	sta	5,s
;timebase.c:29: count = (uint16_t)((T2CNTH << 8) | T2CNTL);
	lda	*0x2c
	clrx
	sta	14,s
	stx	15,s
	ldx	*0x2d
	clrh
	txa
	ora	15,s
	tax
	pshh
	pula
	ora	14,s
	psha
	pulh
	pula
	tap
;timebase.c:33: return (overflows << 13) + (count >> 3);
	pshx
	lda	4,s
	ldx	3,s
	lsla
	rolx
	lsla
	rolx
	lsla
	rolx
	lsla
	rolx
	lsla
	rolx
	sta	11,s
	stx	10,s
	pulx
	lda	4,s
	nsa	
	and	#0xf0
	lsla	
	sta	11,s
	lda	4,s
	lsra	
	lsra	
	lsra	
	ora	10,s
	sta	10,s
	clra
	sta	12,s
	txa
	pshh
	pulx
	lsrx
	rora
	lsrx
	rora
	lsrx
	rora
	sta	8,s
	stx	7,s
	psha
	clra
	sta	7,s
	clra
	sta	6,s
	pula
	tsx
	lda	11,x
	add	7,x
	sta	7,x
	lda	10,x
	adc	6,x
	sta	6,x
	lda	9,x
	adc	5,x
	sta	5,x
	lda	8,x
	adc	4,x
	sta	4,x
	lda	4,x
	sta	*___SDCC_hc08_ret3
	lda	5,x
	sta	*___SDCC_hc08_ret2
	ldx	6,x
	lda	8,s
;timebase.c:34: }
	ais	#14
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'isr_tim2_overflow'
;------------------------------------------------------------
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;timebase.c:36: void isr_tim2_overflow(void) __interrupt(9) {
;	-----------------------------------------
;	 function isr_tim2_overflow
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 4 bytes.
_isr_tim2_overflow:
	pshh
	ais	#-4
;timebase.c:37: if (T2SC & (1 << T2SC_TOF)) {
	lda	*0x2b
	bpl     00103$
;timebase.c:38: tim2OverflowCount++;
	tsx
	ldhx	#_tim2OverflowCount
	lda	,x
	sta	1,s
	lda	1,x
	sta	2,s
	lda	2,x
	sta	3,s
	lda	3,x
	sta	4,s
	tsx
	ldhx	#_tim2OverflowCount
	lda	4,s
	add	#0x01
	sta	3,x
	lda	3,s
	adc	#0
	sta	2,x
	lda	2,s
	adc	#0
	sta	1,x
	lda	1,s
	adc	#0
	sta	,x
;timebase.c:39: T2SC &= (uint8_t)~(1 << T2SC_TOF);  /* limpa flag (write 0 apos leitura) */
	lda	*0x2b
	and	#0x7f
	sta	*0x2b
00103$:
;timebase.c:41: }
	ais	#4
	pulh
	rti
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
