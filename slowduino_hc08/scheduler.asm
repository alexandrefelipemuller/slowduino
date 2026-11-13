;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.2.0 #13081 (Linux)
;--------------------------------------------------------
	.module scheduler
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
	.globl _isr_tim1_ch1
	.globl _isr_tim1_ch0
	.globl _micros
	.globl _ignitionSchedule2
	.globl _ignitionSchedule1
	.globl _injector3Polling
	.globl _injector2Polling
	.globl _injector1Polling
	.globl _scheduleInjectorPolling
	.globl _processInjectorPolling
	.globl _schedulerInit
	.globl _setIgnitionSchedule
	.globl _clearIgnitionSchedule
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
_ignitionSchedule1::
	.ds 8
_ignitionSchedule2::
	.ds 8
;--------------------------------------------------------
; extended address mode data
;--------------------------------------------------------
	.area XSEG
_injector1Polling::
	.ds 10
_injector2Polling::
	.ds 10
_injector3Polling::
	.ds 10
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
;Allocation info for local variables in function 'getTimer1Count'
;------------------------------------------------------------
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;scheduler.h:55: static inline uint16_t getTimer1Count(void) {
;	-----------------------------------------
;	 function getTimer1Count
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_getTimer1Count:
	ais	#-2
;scheduler.h:56: return (uint16_t)((T1CNTH << 8) | T1CNTL);
	lda	*0x21
	clrx
	sta	1,s
	stx	2,s
	lda	*0x22
	ora	2,s
	psha
	txa
	ora	2,s
	tax
	pula
;scheduler.h:57: }
	ais	#2
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'beginCoil1Charge'
;------------------------------------------------------------
;scheduler.c:28: static void beginCoil1Charge(void) { PTA |= COIL1_BIT; }
;	-----------------------------------------
;	 function beginCoil1Charge
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_beginCoil1Charge:
	lda	*0x00
	ora	#0x01
	sta	*0x00
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'endCoil1Charge'
;------------------------------------------------------------
;scheduler.c:29: static void endCoil1Charge(void)   { PTA &= (uint8_t)~COIL1_BIT; }
;	-----------------------------------------
;	 function endCoil1Charge
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_endCoil1Charge:
	lda	*0x00
	and	#0xfe
	sta	*0x00
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'beginCoil2Charge'
;------------------------------------------------------------
;scheduler.c:30: static void beginCoil2Charge(void) { PTA |= COIL2_BIT; }
;	-----------------------------------------
;	 function beginCoil2Charge
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_beginCoil2Charge:
	lda	*0x00
	ora	#0x02
	sta	*0x00
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'endCoil2Charge'
;------------------------------------------------------------
;scheduler.c:31: static void endCoil2Charge(void)   { PTA &= (uint8_t)~COIL2_BIT; }
;	-----------------------------------------
;	 function endCoil2Charge
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_endCoil2Charge:
	lda	*0x00
	and	#0xfd
	sta	*0x00
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'openInjector1'
;------------------------------------------------------------
;scheduler.c:39: static void openInjector1(void)  { PTB |= INJ1_BIT; }
;	-----------------------------------------
;	 function openInjector1
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_openInjector1:
	lda	*0x01
	ora	#0x01
	sta	*0x01
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'closeInjector1'
;------------------------------------------------------------
;scheduler.c:40: static void closeInjector1(void) { PTB &= (uint8_t)~INJ1_BIT; }
;	-----------------------------------------
;	 function closeInjector1
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_closeInjector1:
	lda	*0x01
	and	#0xfe
	sta	*0x01
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'openInjector2'
;------------------------------------------------------------
;scheduler.c:41: static void openInjector2(void)  { PTB |= INJ2_BIT; }
;	-----------------------------------------
;	 function openInjector2
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_openInjector2:
	lda	*0x01
	ora	#0x02
	sta	*0x01
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'closeInjector2'
;------------------------------------------------------------
;scheduler.c:42: static void closeInjector2(void) { PTB &= (uint8_t)~INJ2_BIT; }
;	-----------------------------------------
;	 function closeInjector2
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_closeInjector2:
	lda	*0x01
	and	#0xfd
	sta	*0x01
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'openInjector3'
;------------------------------------------------------------
;scheduler.c:43: static void openInjector3(void)  { PTB |= INJ3_BIT; }
;	-----------------------------------------
;	 function openInjector3
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_openInjector3:
	lda	*0x01
	ora	#0x04
	sta	*0x01
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'closeInjector3'
;------------------------------------------------------------
;scheduler.c:44: static void closeInjector3(void) { PTB &= (uint8_t)~INJ3_BIT; }
;	-----------------------------------------
;	 function closeInjector3
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_closeInjector3:
	lda	*0x01
	and	#0xfb
	sta	*0x01
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'scheduleInjectorPolling'
;------------------------------------------------------------
;startDelay                Allocated to stack - sp +15
;pulseWidth                Allocated to stack - sp +19
;injState                  Allocated to stack - sp +11
;now                       Allocated to stack - sp +7
;sloc0                     Allocated to stack - sp +1
;sloc1                     Allocated to stack - sp +9
;sloc2                     Allocated to stack - sp +5
;------------------------------------------------------------
;scheduler.c:50: void scheduleInjectorPolling(InjectorPollingState *injState, uint32_t startDelay, uint16_t pulseWidth) {
;	-----------------------------------------
;	 function scheduleInjectorPolling
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 12 bytes.
_scheduleInjectorPolling:
	psha
	pshx
	ais	#-10
;scheduler.c:51: uint32_t now = micros();
	jsr	_micros
	sta	4,s
	stx	3,s
	lda	*___SDCC_hc08_ret2
	sta	2,s
	lda	*___SDCC_hc08_ret3
	sta	1,s
;scheduler.c:52: injState->openTime = now + startDelay;
	tsx
	lda	10,x
	sta	8,x
	lda	11,x
	sta	9,x
	lda	3,x
	add	17,x
	sta	3,x
	lda	2,x
	adc	16,x
	sta	2,x
	lda	1,x
	adc	15,x
	sta	1,x
	lda	,x
	adc	14,x
	sta	,x
	lda	8,x
	psha
	pulh
	ldx	10,s
	lda	1,s
	sta	2,x
	lda	2,s
	sta	3,x
	lda	3,s
	sta	4,x
	lda	4,s
	sta	5,x
;scheduler.c:53: injState->closeTime = injState->openTime + pulseWidth;
	tsx
	lda	10,x
	sta	8,x
	lda	11,x
	sta	9,x
	lda	19,x
	sta	7,x
	lda	18,x
	sta	6,x
	clra
	sta	5,x
	sta	4,x
	lda	3,x
	add	7,x
	sta	7,x
	lda	2,x
	adc	6,x
	sta	6,x
	lda	1,x
	adc	5,x
	sta	5,x
	lda	,x
	adc	4,x
	sta	4,x
	lda	8,x
	psha
	pulh
	ldx	10,s
	lda	5,s
	sta	6,x
	lda	6,s
	sta	7,x
	lda	7,s
	sta	8,x
	lda	8,s
	sta	9,x
;scheduler.c:54: injState->isScheduled = true;
	lda	11,s
	psha
	pulh
	ldx	12,s
	lda	#0x01
	sta	,x
;scheduler.c:55: injState->isOpen = false;
	tsx
	lda	10,x
	sta	4,x
	lda	11,x
	sta	5,x
	lda	4,x
	psha
	pulh
	ldx	6,s
	clra
	sta	1,x
;scheduler.c:56: }
	ais	#12
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'processInjectorPolling'
;------------------------------------------------------------
;now                       Allocated to stack - sp +5
;sloc0                     Allocated to stack - sp +5
;sloc1                     Allocated to stack - sp +1
;------------------------------------------------------------
;scheduler.c:58: void processInjectorPolling(void) {
;	-----------------------------------------
;	 function processInjectorPolling
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 8 bytes.
_processInjectorPolling:
	ais	#-8
;scheduler.c:59: uint32_t now = micros();
	jsr	_micros
	sta	8,s
	stx	7,s
	lda	*___SDCC_hc08_ret2
	sta	6,s
	lda	*___SDCC_hc08_ret3
	sta	5,s
;scheduler.c:61: if (injector1Polling.isScheduled) {
	lda	_injector1Polling
	bne	00205$
	bra	00109$
00205$:
;scheduler.c:62: if (!injector1Polling.isOpen && now >= injector1Polling.openTime) {
	ldx	(_injector1Polling + 0x0001)
	bne	00105$
	lda	(_injector1Polling + 0x0002)
	sta	1,s
	lda	((_injector1Polling + 0x0002) + 1)
	sta	2,s
	lda	((_injector1Polling + 0x0002) + 2)
	sta	3,s
	lda	((_injector1Polling + 0x0002) + 3)
	sta	4,s
	lda	8,s
	sub	4,s
	lda	7,s
	sbc	3,s
	lda	6,s
	sbc	2,s
	lda	5,s
	sbc	1,s
	bcs	00105$
;scheduler.c:63: openInjector1();
	jsr	_openInjector1
;scheduler.c:64: injector1Polling.isOpen = true;
	lda	#0x01
	sta	(_injector1Polling + 0x0001)
	bra	00109$
00105$:
;scheduler.c:65: } else if (injector1Polling.isOpen && now >= injector1Polling.closeTime) {
	tstx
	beq	00109$
	lda	(_injector1Polling + 0x0006)
	sta	1,s
	lda	((_injector1Polling + 0x0006) + 1)
	sta	2,s
	lda	((_injector1Polling + 0x0006) + 2)
	sta	3,s
	lda	((_injector1Polling + 0x0006) + 3)
	sta	4,s
	tsx
	lda	7,x
	sub	3,x
	lda	6,x
	sbc	2,x
	lda	5,x
	sbc	1,x
	lda	4,x
	sbc	,x
	bcs	00109$
;scheduler.c:66: closeInjector1();
	jsr	_closeInjector1
;scheduler.c:67: injector1Polling.isOpen = false;
	clra
	sta	(_injector1Polling + 0x0001)
;scheduler.c:68: injector1Polling.isScheduled = false;
	sta	_injector1Polling
00109$:
;scheduler.c:72: if (injector2Polling.isScheduled) {
	lda	_injector2Polling
	bne	00210$
	bra	00118$
00210$:
;scheduler.c:73: if (!injector2Polling.isOpen && now >= injector2Polling.openTime) {
	ldx	(_injector2Polling + 0x0001)
	bne	00114$
	lda	(_injector2Polling + 0x0002)
	sta	1,s
	lda	((_injector2Polling + 0x0002) + 1)
	sta	2,s
	lda	((_injector2Polling + 0x0002) + 2)
	sta	3,s
	lda	((_injector2Polling + 0x0002) + 3)
	sta	4,s
	lda	8,s
	sub	4,s
	lda	7,s
	sbc	3,s
	lda	6,s
	sbc	2,s
	lda	5,s
	sbc	1,s
	bcs	00114$
;scheduler.c:74: openInjector2();
	jsr	_openInjector2
;scheduler.c:75: injector2Polling.isOpen = true;
	lda	#0x01
	sta	(_injector2Polling + 0x0001)
	bra	00118$
00114$:
;scheduler.c:76: } else if (injector2Polling.isOpen && now >= injector2Polling.closeTime) {
	tstx
	beq	00118$
	lda	(_injector2Polling + 0x0006)
	sta	1,s
	lda	((_injector2Polling + 0x0006) + 1)
	sta	2,s
	lda	((_injector2Polling + 0x0006) + 2)
	sta	3,s
	lda	((_injector2Polling + 0x0006) + 3)
	sta	4,s
	tsx
	lda	7,x
	sub	3,x
	lda	6,x
	sbc	2,x
	lda	5,x
	sbc	1,x
	lda	4,x
	sbc	,x
	bcs	00118$
;scheduler.c:77: closeInjector2();
	jsr	_closeInjector2
;scheduler.c:78: injector2Polling.isOpen = false;
	clra
	sta	(_injector2Polling + 0x0001)
;scheduler.c:79: injector2Polling.isScheduled = false;
	sta	_injector2Polling
00118$:
;scheduler.c:83: if (injector3Polling.isScheduled) {
	lda	_injector3Polling
	bne	00215$
	bra	00128$
00215$:
;scheduler.c:84: if (!injector3Polling.isOpen && now >= injector3Polling.openTime) {
	ldx	(_injector3Polling + 0x0001)
	bne	00123$
	lda	(_injector3Polling + 0x0002)
	sta	1,s
	lda	((_injector3Polling + 0x0002) + 1)
	sta	2,s
	lda	((_injector3Polling + 0x0002) + 2)
	sta	3,s
	lda	((_injector3Polling + 0x0002) + 3)
	sta	4,s
	lda	8,s
	sub	4,s
	lda	7,s
	sbc	3,s
	lda	6,s
	sbc	2,s
	lda	5,s
	sbc	1,s
	bcs	00123$
;scheduler.c:85: openInjector3();
	jsr	_openInjector3
;scheduler.c:86: injector3Polling.isOpen = true;
	lda	#0x01
	sta	(_injector3Polling + 0x0001)
	bra	00128$
00123$:
;scheduler.c:87: } else if (injector3Polling.isOpen && now >= injector3Polling.closeTime) {
	tstx
	beq	00128$
	lda	(_injector3Polling + 0x0006)
	sta	1,s
	lda	((_injector3Polling + 0x0006) + 1)
	sta	2,s
	lda	((_injector3Polling + 0x0006) + 2)
	sta	3,s
	lda	((_injector3Polling + 0x0006) + 3)
	sta	4,s
	tsx
	lda	7,x
	sub	3,x
	lda	6,x
	sbc	2,x
	lda	5,x
	sbc	1,x
	lda	4,x
	sbc	,x
	bcs	00128$
;scheduler.c:88: closeInjector3();
	jsr	_closeInjector3
;scheduler.c:89: injector3Polling.isOpen = false;
	clra
	sta	(_injector3Polling + 0x0001)
;scheduler.c:90: injector3Polling.isScheduled = false;
	sta	_injector3Polling
00128$:
;scheduler.c:93: }
	ais	#8
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'schedulerInit'
;------------------------------------------------------------
;scheduler.c:95: void schedulerInit(void) {
;	-----------------------------------------
;	 function schedulerInit
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_schedulerInit:
;scheduler.c:96: DDRA |= (COIL1_BIT | COIL2_BIT);  /* bobinas como saida */
	lda	*0x04
	ora	#0x03
	sta	*0x04
;scheduler.c:97: DDRB |= (INJ1_BIT | INJ2_BIT | INJ3_BIT);  /* injetores como saida */
	lda	*0x05
	ora	#0x07
	sta	*0x05
;scheduler.c:98: endCoil1Charge();
	jsr	_endCoil1Charge
;scheduler.c:99: endCoil2Charge();
	jsr	_endCoil2Charge
;scheduler.c:100: closeInjector1();
	jsr	_closeInjector1
;scheduler.c:101: closeInjector2();
	jsr	_closeInjector2
;scheduler.c:102: closeInjector3();
	jsr	_closeInjector3
;scheduler.c:107: T1SC = (1 << T1SC_TRST);
	mov	#0x10,*0x20
;scheduler.c:108: T1SC0 = (1 << TxSCx_MSxA);
	mov	#0x10,*0x25
;scheduler.c:109: T1SC0 |= (1 << TxSCx_CHxIE);
	lda	*0x25
	ora	#0x40
	sta	*0x25
;scheduler.c:110: T1SC1 = (1 << TxSCx_MSxA) | (1 << TxSCx_CHxIE);
	mov	#0x50,*0x28
;scheduler.c:111: T1SC = (6 << T1SC_PS0);  /* PS[2:0]=110 -> /64. Ver US_TO_TIMER1 em scheduler.h */
	mov	#0x06,*0x20
;scheduler.c:112: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'handleIgnitionChannel'
;------------------------------------------------------------
;beginCharge               Allocated to stack - sp +11
;endCharge                 Allocated to stack - sp +13
;compareReg                Allocated to stack - sp +15
;schedule                  Allocated to stack - sp +7
;__1966080003              Allocated to registers a x 
;sloc0                     Allocated to stack - sp +5
;sloc1                     Allocated to stack - sp +1
;sloc2                     Allocated to stack - sp +3
;------------------------------------------------------------
;scheduler.c:114: static void handleIgnitionChannel(volatile IgnitionSchedule *schedule,
;	-----------------------------------------
;	 function handleIgnitionChannel
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 8 bytes.
_handleIgnitionChannel:
	psha
	pshx
	ais	#-6
;scheduler.c:118: if (schedule->status == SCHED_PENDING) {
	tsx
	lda	6,x
	sta	4,x
	lda	7,x
	sta	5,x
	lda	4,x
	psha
	pulh
	ldx	6,s
	lda	,x
	cbeqa	#0x01,00125$
	jmp	00104$
00125$:
;scheduler.c:119: schedule->status = SCHED_RUNNING;
	lda	5,s
	psha
	pulh
	ldx	6,s
	lda	#0x02
	sta	,x
;scheduler.c:120: beginCharge();
	bsr	00127$
	bra	00126$
00127$:
	lda	14,s
	psha
	lda	14,s
	psha
	rts
00126$:
;scheduler.c:121: *compareReg = schedule->endCompare;
	tsx
	lda	14,x
	sta	,x
	lda	15,x
	sta	1,x
	lda	4,x
	sta	2,x
	lda	5,x
	sta	3,x
	lda	2,x
	psha
	pulh
	ldx	4,s
	lda	4,x
	ldx	3,x
	pshx
	ldx	2,s
	pshx
	pulh
	ldx	3,s
	sta	1,x
	pula
	sta	,x
;scheduler.h:56: return (uint16_t)((T1CNTH << 8) | T1CNTL);
	lda	*0x21
	clrx
	sta	1,s
	stx	2,s
	lda	*0x22
	ora	2,s
	psha
	txa
	ora	2,s
	tax
	pula
;scheduler.c:123: if ((int16_t)(getTimer1Count() - schedule->endCompare) >= 0) {
	pshx
	ldx	4,s
	pshx
	pulh
	ldx	5,s
	psha
	lda	3,x
	sta	5,s
	lda	4,x
	sta	6,s
	pula
	pulx
	sub	4,s
	psha
	txa
	sbc	4,s
	tax
	pula
	txa
	sub	#0x00
	blt	00102$
;scheduler.c:124: schedule->status = SCHED_OFF;
	lda	5,s
	psha
	pulh
	ldx	6,s
	clra
	sta	,x
;scheduler.c:125: endCharge();
	bsr	00130$
	bra	00129$
00130$:
	lda	16,s
	psha
	lda	16,s
	psha
	rts
00129$:
00102$:
;scheduler.c:127: return;
	bra	00108$
00104$:
;scheduler.c:130: if (schedule->status == SCHED_RUNNING) {
	lda	5,s
	psha
	pulh
	ldx	6,s
	lda	,x
	cmp	#0x02
	bne	00108$
;scheduler.c:131: schedule->status = SCHED_OFF;
	lda	5,s
	psha
	pulh
	ldx	6,s
	clra
	sta	,x
;scheduler.c:132: endCharge();
	bsr	00133$
	bra	00132$
00133$:
	lda	16,s
	psha
	lda	16,s
	psha
	rts
00132$:
00108$:
;scheduler.c:134: }
	ais	#8
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'armIgnitionCompare'
;------------------------------------------------------------
;beginCharge               Allocated to stack - sp +13
;endCharge                 Allocated to stack - sp +15
;compareReg                Allocated to stack - sp +17
;schedule                  Allocated to stack - sp +9
;__1310720005              Allocated to registers a x 
;sloc0                     Allocated to stack - sp +5
;sloc1                     Allocated to stack - sp +7
;sloc2                     Allocated to stack - sp +3
;sloc3                     Allocated to stack - sp +1
;------------------------------------------------------------
;scheduler.c:136: static void armIgnitionCompare(volatile IgnitionSchedule *schedule,
;	-----------------------------------------
;	 function armIgnitionCompare
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 10 bytes.
_armIgnitionCompare:
	psha
	pshx
	ais	#-8
;scheduler.c:140: *compareReg = schedule->startCompare;
	tsx
	lda	16,x
	sta	4,x
	lda	17,x
	sta	5,x
	lda	8,x
	sta	6,x
	lda	9,x
	sta	7,x
	lda	6,x
	sta	2,x
	lda	7,x
	sta	3,x
	lda	2,x
	psha
	pulh
	ldx	4,s
	lda	2,x
	ldx	1,x
	pshx
	ldx	6,s
	pshx
	pulh
	ldx	7,s
	sta	1,x
	pula
	sta	,x
;scheduler.h:56: return (uint16_t)((T1CNTH << 8) | T1CNTL);
	lda	*0x21
	clrx
	sta	1,s
	stx	2,s
	lda	*0x22
	ora	2,s
	psha
	txa
	ora	2,s
	tax
	pula
;scheduler.c:142: if ((int16_t)(getTimer1Count() - schedule->startCompare) >= 0) {
	pshx
	ldx	4,s
	pshx
	pulh
	ldx	5,s
	psha
	lda	1,x
	sta	3,s
	lda	2,x
	sta	4,s
	pula
	pulx
	sub	2,s
	psha
	txa
	sbc	2,s
	tax
	pula
	txa
	sub	#0x00
	blt	00104$
;scheduler.c:143: handleIgnitionChannel(schedule, beginCharge, endCharge, compareReg);
	tsx
	lda	5,x
	psha
	lda	4,x
	psha
	lda	15,x
	psha
	lda	14,x
	psha
	lda	13,x
	psha
	lda	12,x
	psha
	lda	7,x
	ldx	6,x
	jsr	_handleIgnitionChannel
	ais	#6
00104$:
;scheduler.c:145: }
	ais	#10
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'setIgnitionSchedule'
;------------------------------------------------------------
;startTime                 Allocated to stack - sp +33
;duration                  Allocated to stack - sp +37
;channel                   Allocated to stack - sp +39
;schedule                  Allocated to stack - sp +27
;__1310720007              Allocated to stack - sp +25
;startTicks                Allocated to stack - sp +5
;durationTicks             Allocated to stack - sp +1
;totalTicks                Allocated to stack - sp +15
;minTicks                  Allocated to stack - sp +11
;currentCount              Allocated to registers 
;startTicks16              Allocated to registers x h 
;durationTicks16           Allocated to stack - sp +29
;sloc0                     Allocated to stack - sp +17
;sloc1                     Allocated to stack - sp +19
;sloc2                     Allocated to stack - sp +13
;sloc3                     Allocated to stack - sp +21
;sloc4                     Allocated to stack - sp +9
;------------------------------------------------------------
;scheduler.c:147: void setIgnitionSchedule(volatile IgnitionSchedule *schedule, uint32_t startTime,
;	-----------------------------------------
;	 function setIgnitionSchedule
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 30 bytes.
_setIgnitionSchedule:
	ais	#-30
	sta	28,s
	stx	27,s
;scheduler.c:153: schedule->status = SCHED_OFF;
	tsx
	lda	26,x
	sta	16,x
	lda	27,x
	sta	17,x
;scheduler.c:152: if (channel > 2) {
	lda	38,x
	cmp	#0x02
	bls	00102$
;scheduler.c:153: schedule->status = SCHED_OFF;
	lda	16,x
	psha
	pulh
	ldx	18,s
	clra
	sta	,x
;scheduler.c:154: return;
	jmp	00119$
00102$:
;scheduler.c:157: if (schedule->status == SCHED_RUNNING) {
	lda	17,s
	psha
	pulh
	ldx	18,s
	lda	,x
;scheduler.c:159: if (schedule->channel == 1) { endCoil1Charge(); } else { endCoil2Charge(); }
	tsx
	ldx	16,x
	stx	19,s
	psha
	lda	19,s
	sta	21,s
	pula
;scheduler.c:157: if (schedule->status == SCHED_RUNNING) {
	cmp	#0x02
	bne	00107$
;scheduler.c:158: schedule->status = SCHED_OFF;
	lda	17,s
	psha
	pulh
	ldx	18,s
	clra
	sta	,x
;scheduler.c:159: if (schedule->channel == 1) { endCoil1Charge(); } else { endCoil2Charge(); }
	lda	19,s
	psha
	pulh
	ldx	20,s
	lda	7,x
	cmp	#0x01
	bne	00104$
	jsr	_endCoil1Charge
	bra	00107$
00104$:
	jsr	_endCoil2Charge
00107$:
;scheduler.c:162: startTicks = US_TO_TIMER1(startTime);
	tsx
	lda	35,x
	ldx	34,x
	lsrx
	rora
	lsrx
	rora
	lsrx
	rora
	sta	16,s
	stx	15,s
	lda	34,s
	nsa	
	and	#0xf0
	lsla	
	ora	15,s
	sta	15,s
	lda	34,s
	ldx	33,s
	lsrx
	rora
	lsrx
	rora
	lsrx
	rora
	sta	14,s
	stx	13,s
	ldx	16,s
	lda	15,s
	psha
	pulh
	stx	16,s
	pshh
	pula
	sta	15,s
	clra
	sta	14,s
	sta	13,s
	tsx
	lda	12,x
	sta	4,x
	lda	13,x
	sta	5,x
	lda	14,x
	sta	6,x
	lda	15,x
	sta	7,x
;scheduler.c:163: durationTicks = US_TO_TIMER1(duration);
	lda	37,x
	ldx	36,x
	lsrx
	rora
	lsrx
	rora
	lsrx
	rora
	sta	24,s
	stx	23,s
	psha
	clra
	sta	23,s
	clra
	sta	22,s
	pula
	tsx
	lda	20,x
	sta	,x
	lda	21,x
	sta	1,x
	lda	22,x
	sta	2,x
	lda	23,x
	sta	3,x
;scheduler.c:164: if (durationTicks == 0) { durationTicks = 1; }
	lda	20,x
	ora	21,x
	ora	22,x
	ora	23,x
	bne	00109$
	clra
	sta	,x
	sta	1,x
	sta	2,x
	inca
	sta	3,x
00109$:
;scheduler.c:166: totalTicks = startTicks + durationTicks;
	tsx
	lda	15,x
	add	3,x
	sta	23,x
	lda	14,x
	adc	2,x
	sta	22,x
	lda	13,x
	adc	1,x
	sta	21,x
	lda	12,x
	adc	,x
	sta	20,x
;scheduler.c:167: minTicks = US_TO_TIMER1(IGNITION_MIN_DELAY_US);
	lda	(_IGNITION_MIN_DELAY_US + 1)
	ldx	_IGNITION_MIN_DELAY_US
	lsrx
	rora
	lsrx
	rora
	lsrx
	rora
	sta	12,s
	stx	11,s
	psha
	clra
	sta	11,s
	clra
	sta	10,s
	pula
;scheduler.c:169: if (startTicks < minTicks) {
	tsx
	lda	15,x
	sub	11,x
	lda	14,x
	sbc	10,x
	lda	13,x
	sbc	9,x
	lda	12,x
	sbc	8,x
	bcc	00114$
;scheduler.c:170: startTicks = minTicks;
	lda	8,x
	sta	4,x
	lda	9,x
	sta	5,x
	lda	10,x
	sta	6,x
	lda	11,x
	sta	7,x
;scheduler.c:171: if (totalTicks > startTicks) {
	lda	11,x
	sub	23,x
	lda	10,x
	sbc	22,x
	lda	9,x
	sbc	21,x
	lda	8,x
	sbc	20,x
	bcc	00111$
;scheduler.c:172: durationTicks = totalTicks - startTicks;
	lda	23,x
	sub	11,x
	sta	3,x
	lda	22,x
	sbc	10,x
	sta	2,x
	lda	21,x
	sbc	9,x
	sta	1,x
	lda	20,x
	sbc	8,x
	sta	,x
	bra	00114$
00111$:
;scheduler.c:174: durationTicks = 1;
	tsx
	clra
	sta	,x
	sta	1,x
	sta	2,x
	inca
	sta	3,x
00114$:
;scheduler.h:56: return (uint16_t)((T1CNTH << 8) | T1CNTL);
	lda	*0x21
	clrx
	sta	9,s
	stx	10,s
	lda	*0x22
	ora	10,s
	psha
	txa
	ora	10,s
	tax
	pula
	sta	26,s
	stx	25,s
;scheduler.c:179: startTicks16 = (uint16_t)startTicks;
	ldx	8,s
	lda	7,s
	psha
	pulh
;scheduler.c:180: durationTicks16 = (uint16_t)durationTicks;
	lda	4,s
	sta	30,s
	lda	3,s
	sta	29,s
;scheduler.c:182: schedule->startCompare = currentCount + startTicks16;
	lda	17,s
	sta	9,s
	lda	18,s
	sta	10,s
	txa
	add	26,s
	tax
	pshh
	pula
	adc	25,s
	pshx
	psha
	pshx
	lda	12,s
	psha
	pulh
	ldx	13,s
	sta	1,x
	pula
	sta	2,x
	pula
	pulx
;scheduler.c:183: schedule->endCompare = schedule->startCompare + durationTicks16;
	psha
	lda	18,s
	sta	22,s
	lda	19,s
	sta	23,s
	pula
	pshx
	ldx	10,s
	pshx
	pulh
	ldx	11,s
	psha
	lda	1,x
	lda	2,x
	pula
	pulx
	psha
	txa
	add	31,s
	tax
	pula
	adc	29,s
	pshx
	ldx	22,s
	pshx
	pulh
	ldx	23,s
	sta	3,x
	pula
	sta	4,x
;scheduler.c:184: schedule->duration = durationTicks16;
	tsx
	lda	16,x
	sta	8,x
	lda	17,x
	sta	9,x
	lda	8,x
	psha
	pulh
	ldx	10,s
	lda	29,s
	sta	5,x
	lda	30,s
	sta	6,x
;scheduler.c:185: schedule->channel = channel;
	lda	19,s
	psha
	pulh
	ldx	20,s
	lda	39,s
	sta	7,x
;scheduler.c:186: schedule->status = SCHED_PENDING;
	lda	17,s
	psha
	pulh
	ldx	18,s
	lda	#0x01
	sta	,x
;scheduler.c:188: if (channel == 1) {
	lda	39,s
	cmp	#0x01
	bne	00116$
;scheduler.c:189: armIgnitionCompare(schedule, beginCoil1Charge, endCoil1Charge, (volatile uint16_t *)&T1CH0H);
	lda	#0x26
	psha
	clra
	psha
	lda	#_endCoil1Charge
	psha
	lda	#>_endCoil1Charge
	psha
	lda	#_beginCoil1Charge
	psha
	lda	#>_beginCoil1Charge
	psha
	tsx
	lda	23,x
	ldx	22,x
	jsr	_armIgnitionCompare
	ais	#6
	bra	00119$
00116$:
;scheduler.c:191: armIgnitionCompare(schedule, beginCoil2Charge, endCoil2Charge, (volatile uint16_t *)&T1CH1H);
	lda	#0x29
	psha
	clra
	psha
	lda	#_endCoil2Charge
	psha
	lda	#>_endCoil2Charge
	psha
	lda	#_beginCoil2Charge
	psha
	lda	#>_beginCoil2Charge
	psha
	tsx
	lda	23,x
	ldx	22,x
	jsr	_armIgnitionCompare
	ais	#6
00119$:
;scheduler.c:193: }
	ais	#30
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'clearIgnitionSchedule'
;------------------------------------------------------------
;schedule                  Allocated to stack - sp +1
;------------------------------------------------------------
;scheduler.c:195: void clearIgnitionSchedule(volatile IgnitionSchedule *schedule) {
;	-----------------------------------------
;	 function clearIgnitionSchedule
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_clearIgnitionSchedule:
	psha
	pshx
;scheduler.c:196: schedule->status = SCHED_OFF;
	pulh
	pulx
	pshx
	pshh
	pshx
	pshh
	clra
	sta	,x
	pulh
	pulx
;scheduler.c:197: if (schedule->channel == 1) {
	lda	7,x
	cmp	#0x01
	bne	00104$
;scheduler.c:198: endCoil1Charge();
	jsr	_endCoil1Charge
	bra	00106$
00104$:
;scheduler.c:199: } else if (schedule->channel == 2) {
	lda	7,x
	cmp	#0x02
	bne	00106$
;scheduler.c:200: endCoil2Charge();
	jsr	_endCoil2Charge
00106$:
;scheduler.c:202: }
	ais	#2
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'isr_tim1_ch0'
;------------------------------------------------------------
;scheduler.c:205: void isr_tim1_ch0(void) __interrupt(4) {
;	-----------------------------------------
;	 function isr_tim1_ch0
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_isr_tim1_ch0:
	pshh
;scheduler.c:206: handleIgnitionChannel(&ignitionSchedule1, beginCoil1Charge, endCoil1Charge, (volatile uint16_t *)&T1CH0H);
	lda	#0x26
	psha
	clra
	psha
	lda	#_endCoil1Charge
	psha
	lda	#>_endCoil1Charge
	psha
	lda	#_beginCoil1Charge
	psha
	lda	#>_beginCoil1Charge
	psha
	lda	#_ignitionSchedule1
	ldx	#>_ignitionSchedule1
	jsr	_handleIgnitionChannel
	ais	#6
;scheduler.c:207: }
	pulh
	rti
;------------------------------------------------------------
;Allocation info for local variables in function 'isr_tim1_ch1'
;------------------------------------------------------------
;scheduler.c:209: void isr_tim1_ch1(void) __interrupt(5) {
;	-----------------------------------------
;	 function isr_tim1_ch1
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_isr_tim1_ch1:
	pshh
;scheduler.c:210: handleIgnitionChannel(&ignitionSchedule2, beginCoil2Charge, endCoil2Charge, (volatile uint16_t *)&T1CH1H);
	lda	#0x29
	psha
	clra
	psha
	lda	#_endCoil2Charge
	psha
	lda	#>_endCoil2Charge
	psha
	lda	#_beginCoil2Charge
	psha
	lda	#>_beginCoil2Charge
	psha
	lda	#_ignitionSchedule2
	ldx	#>_ignitionSchedule2
	jsr	_handleIgnitionChannel
	ais	#6
;scheduler.c:211: }
	pulh
	rti
	.area CSEG    (CODE)
	.area CONST   (CODE)
_IGNITION_MIN_DELAY_US:
	.dw #0x0019
	.area XINIT   (CODE)
__xinit__ignitionSchedule1:
	.db #0x00	; 0
	.dw #0x0000
	.dw #0x0000
	.dw #0x0000
	.db #0x01	; 1
__xinit__ignitionSchedule2:
	.db #0x00	; 0
	.dw #0x0000
	.dw #0x0000
	.dw #0x0000
	.db #0x02	; 2
	.area CABS    (ABS,CODE)
