;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.2.0 #13081 (Linux)
;--------------------------------------------------------
	.module decoders
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
	.globl _isr_irq
	.globl _micros
	.globl _scheduleInjectorPolling
	.globl _setIgnitionSchedule
	.globl _revolutionCounter
	.globl _triggerState
	.globl _triggerSetup_MissingTooth
	.globl _triggerSetup_BasicDistributor
	.globl _triggerInit
	.globl _calculateRPM
	.globl _checkSyncLoss
	.globl _angleToTime
	.globl _timeToAngle
	.globl _getCrankAngle
	.globl _attachTriggerInterrupt
	.globl _resetTriggerState
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
_revolutionCounter::
	.ds 1
_triggerEdgesPerTooth:
	.ds 1
;--------------------------------------------------------
; extended address mode data
;--------------------------------------------------------
	.area XSEG
_triggerState::
	.ds 41
_currentTriggerISR:
	.ds 2
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
;Allocation info for local variables in function 'scheduleInjectionISR'
;------------------------------------------------------------
;timeToInjection           Allocated to stack - sp +5
;pw1                       Allocated to stack - sp +7
;pw2                       Allocated to stack - sp +5
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;decoders.c:43: static void scheduleInjectionISR(void) {
;	-----------------------------------------
;	 function scheduleInjectionISR
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 8 bytes.
_scheduleInjectionISR:
	ais	#-8
;decoders.c:47: if (triggerState.revolutionTime == 0) return;
	lda	(_triggerState + 0x0008)
	sta	1,s
	lda	((_triggerState + 0x0008) + 1)
	sta	2,s
	lda	((_triggerState + 0x0008) + 2)
	sta	3,s
	lda	((_triggerState + 0x0008) + 3)
	sta	4,s
	tsx
	lda	,x
	ora	1,x
	ora	2,x
	ora	3,x
	bne	00102$
	jmp	00112$
00102$:
;decoders.c:49: timeToInjection = ((uint32_t)INJECTION_ANGLE * triggerState.revolutionTime) / 360UL;
	lda	(_triggerState + 0x0008)
	sta	1,s
	lda	((_triggerState + 0x0008) + 1)
	sta	2,s
	lda	((_triggerState + 0x0008) + 2)
	sta	3,s
	lda	((_triggerState + 0x0008) + 3)
	sta	4,s
	tsx
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	lda	#0x0e
	psha
	lda	#0x01
	psha
	deca
	psha
	psha
	jsr	__mullong
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#8
	lda	#0x68
	psha
	lda	#0x01
	psha
	deca
	psha
	psha
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
;decoders.c:51: pw1 = currentStatus.PW1;
	jsr	__divulong
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#8
	lda	(_currentStatus + 0x001c)
	sta	7,s
	lda	((_currentStatus + 0x001c) + 1)
	sta	8,s
;decoders.c:52: pw2 = currentStatus.PW2;
	lda	(_currentStatus + 0x001e)
	sta	5,s
	lda	((_currentStatus + 0x001e) + 1)
	sta	6,s
;decoders.c:53: if (pw1 < INJ_MIN_PW || pw1 > INJ_MAX_PW) pw1 = INJ_MIN_PW;
	lda	7,s
	psha
	pulh
	ldx	8,s
	cphx	#0x01f4
	bcs	00103$
	cphx	#0x4e20
	bls	00104$
00103$:
	tsx
	lda	#0x01
	sta	6,x
	lda	#0xf4
	sta	7,x
00104$:
;decoders.c:54: if (pw2 < INJ_MIN_PW || pw2 > INJ_MAX_PW) pw2 = INJ_MIN_PW;
	lda	5,s
	psha
	pulh
	ldx	6,s
	cphx	#0x01f4
	bcs	00106$
	cphx	#0x4e20
	bls	00107$
00106$:
	tsx
	lda	#0x01
	sta	4,x
	lda	#0xf4
	sta	5,x
00107$:
;decoders.c:56: if (revolutionCounter == 0) {
	lda	_revolutionCounter
	bne	00110$
;decoders.c:57: scheduleInjectorPolling(&injector1Polling, timeToInjection, pw1);
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	lda	#_injector1Polling
	ldx	#>_injector1Polling
	jsr	_scheduleInjectorPolling
	ais	#6
	bra	00112$
00110$:
;decoders.c:59: scheduleInjectorPolling(&injector2Polling, timeToInjection, pw2);
	tsx
	lda	5,x
	psha
	lda	4,x
	psha
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	lda	#_injector2Polling
	ldx	#>_injector2Polling
	jsr	_scheduleInjectorPolling
	ais	#6
00112$:
;decoders.c:61: }
	ais	#8
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'scheduleIgnitionISR'
;------------------------------------------------------------
;advance                   Allocated to stack - sp +9
;dwellTime                 Allocated to stack - sp +12
;dwellAngle                Allocated to stack - sp +10
;sparkAngle                Allocated to stack - sp +14
;dwellStartAngle           Allocated to registers x h 
;timeToDwell               Allocated to stack - sp +3
;sloc0                     Allocated to stack - sp +1
;sloc1                     Allocated to stack - sp +5
;------------------------------------------------------------
;decoders.c:63: static void scheduleIgnitionISR(void) {
;	-----------------------------------------
;	 function scheduleIgnitionISR
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 15 bytes.
_scheduleIgnitionISR:
	ais	#-15
;decoders.c:68: if (triggerState.revolutionTime == 0) return;
	lda	(_triggerState + 0x0008)
	sta	1,s
	lda	((_triggerState + 0x0008) + 1)
	sta	2,s
	lda	((_triggerState + 0x0008) + 2)
	sta	3,s
	lda	((_triggerState + 0x0008) + 3)
	sta	4,s
	tsx
	lda	,x
	ora	1,x
	ora	2,x
	ora	3,x
	bne	00102$
	jmp	00115$
00102$:
;decoders.c:70: advance = currentStatus.advance;
	lda	(_currentStatus + 0x0025)
	sta	9,s
;decoders.c:71: dwellTime = currentStatus.dwell;
	lda	(_currentStatus + 0x0026)
	sta	12,s
	lda	((_currentStatus + 0x0026) + 1)
	sta	13,s
;decoders.c:72: if (dwellTime < DWELL_MIN) dwellTime = DWELL_MIN;
	lda	13,s
	ldx	12,s
	sub	#0xe8
	txa
	sbc	#0x03
	bcc	00104$
	tsx
	lda	#0x03
	sta	11,x
	lda	#0xe8
	sta	12,x
00104$:
;decoders.c:73: if (dwellTime > DWELL_MAX) dwellTime = DWELL_MAX;
	lda	12,s
	psha
	pulh
	ldx	13,s
	cphx	#0x1f40
	bls	00106$
	tsx
	lda	#0x1f
	sta	11,x
	lda	#0x40
	sta	12,x
00106$:
;decoders.c:75: dwellAngle = (uint16_t)(((uint32_t)dwellTime * 360UL) / triggerState.revolutionTime);
	tsx
	lda	12,x
	sta	3,x
	lda	11,x
	sta	2,x
	clra
	sta	1,x
	sta	,x
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	lda	#0x68
	psha
	lda	#0x01
	psha
	deca
	psha
	psha
	jsr	__mullong
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#8
	lda	(_triggerState + 0x0008)
	sta	5,s
	lda	((_triggerState + 0x0008) + 1)
	sta	6,s
	lda	((_triggerState + 0x0008) + 2)
	sta	7,s
	lda	((_triggerState + 0x0008) + 3)
	sta	8,s
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	jsr	__divulong
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#8
	tsx
	lda	7,x
	sta	10,x
	lda	6,x
	sta	9,x
;decoders.c:77: if (dwellAngle > 180) {
	lda	9,x
	psha
	pulh
	ldx	11,s
	cphx	#0x00b4
	bls	00108$
;decoders.c:78: dwellAngle = 180;
	tsx
	clra
	sta	9,x
	lda	#0xb4
	sta	10,x
;decoders.c:79: dwellTime = (uint16_t)((180UL * triggerState.revolutionTime) / 360UL);
	lda	(_triggerState + 0x0008)
	sta	4,x
	lda	((_triggerState + 0x0008) + 1)
	sta	5,x
	lda	((_triggerState + 0x0008) + 2)
	sta	6,x
	lda	((_triggerState + 0x0008) + 3)
	sta	7,x
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	lda	#0xb4
	psha
	clra
	psha
	psha
	psha
	jsr	__mullong
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#8
	lda	#0x68
	psha
	lda	#0x01
	psha
	deca
	psha
	psha
	tsx
	lda	11,x
	psha
	lda	10,x
	psha
	lda	9,x
	psha
	lda	8,x
	psha
	jsr	__divulong
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#8
	tsx
	lda	7,x
	sta	12,x
	lda	6,x
	sta	11,x
00108$:
;decoders.c:82: sparkAngle = (advance > 0) ? (uint16_t)(360 - advance) : 360;
	lda	9,s
	cmp	#0x00
	ble	00117$
	tsx
	lda	8,x
	sta	5,x
	rola	
	clra	
	sbc	#0x00
	sta	4,x
	lda	#0x68
	sub	5,x
	psha
	lda	#0x01
	sbc	4,x
	tax
	pula
	bra	00118$
00117$:
	ldx	#0x01
	lda	#0x68
00118$:
	sta	15,s
	stx	14,s
;decoders.c:84: if (sparkAngle > dwellAngle) {
	tsx
	lda	10,x
	sub	14,x
	lda	9,x
	sbc	13,x
	bcc	00110$
;decoders.c:85: dwellStartAngle = sparkAngle - dwellAngle;
	lda	14,x
	sub	10,x
	tax
	lda	14,s
	sbc	10,s
	psha
	pulh
	jmp	00111$
00110$:
;decoders.c:87: dwellStartAngle = 0;
	clrh
	clrx
;decoders.c:89: dwellTime = (uint16_t)(((uint32_t)dwellAngle * triggerState.revolutionTime) / 360UL);
	lda	15,s
	sta	8,s
	lda	14,s
	sta	7,s
	stx	6,s
	stx	5,s
	lda	(_triggerState + 0x0008)
	sta	1,s
	lda	((_triggerState + 0x0008) + 1)
	sta	2,s
	lda	((_triggerState + 0x0008) + 2)
	sta	3,s
	lda	((_triggerState + 0x0008) + 3)
	sta	4,s
	pshx
	pshh
	lda	6,s
	psha
	lda	6,s
	psha
	lda	6,s
	psha
	lda	6,s
	psha
	lda	14,s
	psha
	lda	14,s
	psha
	lda	14,s
	psha
	lda	14,s
	psha
	jsr	__mullong
	sta	18,s
	stx	17,s
	lda	*___SDCC_hc08_ret2
	sta	16,s
	lda	*___SDCC_hc08_ret3
	sta	15,s
	ais	#8
	pulh
	pulx
	pshx
	pshh
	lda	#0x68
	psha
	lda	#0x01
	psha
	deca
	psha
	psha
	lda	14,s
	psha
	lda	14,s
	psha
	lda	14,s
	psha
	lda	14,s
	psha
	jsr	__divulong
	sta	18,s
	stx	17,s
	lda	*___SDCC_hc08_ret2
	sta	16,s
	lda	*___SDCC_hc08_ret3
	sta	15,s
	ais	#8
	pulh
	pulx
	lda	8,s
	sta	13,s
	lda	7,s
	sta	12,s
00111$:
;decoders.c:92: timeToDwell = ((uint32_t)dwellStartAngle * triggerState.revolutionTime) / 360UL;
	stx	8,s
	pshh
	pula
	sta	7,s
	clra
	sta	6,s
	sta	5,s
	lda	(_triggerState + 0x0008)
	sta	1,s
	lda	((_triggerState + 0x0008) + 1)
	sta	2,s
	lda	((_triggerState + 0x0008) + 2)
	sta	3,s
	lda	((_triggerState + 0x0008) + 3)
	sta	4,s
	tsx
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	jsr	__mullong
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#8
	lda	#0x68
	psha
	lda	#0x01
	psha
	deca
	psha
	psha
	tsx
	lda	11,x
	psha
	lda	10,x
	psha
	lda	9,x
	psha
	lda	8,x
	psha
;decoders.c:94: if (revolutionCounter == 0) {
	jsr	__divulong
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#8
	lda	_revolutionCounter
	bne	00113$
;decoders.c:95: setIgnitionSchedule(&ignitionSchedule1, timeToDwell, dwellTime, 1);
	lda	#0x01
	psha
	tsx
	lda	13,x
	psha
	lda	12,x
	psha
	lda	8,x
	psha
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	#_ignitionSchedule1
	ldx	#>_ignitionSchedule1
	jsr	_setIgnitionSchedule
	ais	#7
	bra	00115$
00113$:
;decoders.c:97: setIgnitionSchedule(&ignitionSchedule2, timeToDwell, dwellTime, 2);
	lda	#0x02
	psha
	tsx
	lda	13,x
	psha
	lda	12,x
	psha
	lda	8,x
	psha
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	#_ignitionSchedule2
	ldx	#>_ignitionSchedule2
	jsr	_setIgnitionSchedule
	ais	#7
00115$:
;decoders.c:99: }
	ais	#15
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'triggerPri_MissingTooth'
;------------------------------------------------------------
;curTime                   Allocated to stack - sp +18
;baseGap                   Allocated to stack - sp +14
;dynamicThreshold          Allocated to stack - sp +10
;isCranking                Allocated to stack - sp +21
;isGap                     Allocated to registers 
;expectedPulses            Allocated to stack - sp +19
;toleranceWindow           Allocated to stack - sp +17
;sloc0                     Allocated to stack - sp +9
;sloc1                     Allocated to stack - sp +1
;sloc2                     Allocated to stack - sp +13
;sloc3                     Allocated to stack - sp +5
;------------------------------------------------------------
;decoders.c:104: static void triggerPri_MissingTooth(void) {
;	-----------------------------------------
;	 function triggerPri_MissingTooth
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 21 bytes.
_triggerPri_MissingTooth:
	ais	#-21
;decoders.c:105: uint32_t curTime = micros();
	jsr	_micros
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
;decoders.c:109: triggerState.curGap = curTime - triggerState.toothLastToothTime;
	lda	_triggerState
	sta	1,s
	lda	(_triggerState + 1)
	sta	2,s
	lda	(_triggerState + 2)
	sta	3,s
	lda	(_triggerState + 3)
	sta	4,s
	tsx
	lda	11,x
	sub	3,x
	sta	3,x
	lda	10,x
	sbc	2,x
	sta	2,x
	lda	9,x
	sbc	1,x
	sta	1,x
	lda	8,x
	sbc	,x
	sta	,x
	lda	,x
	sta	(_triggerState + 0x0013)
	lda	1,x
	sta	((_triggerState + 0x0013) + 1)
	lda	2,x
	sta	((_triggerState + 0x0013) + 2)
	lda	3,x
	sta	((_triggerState + 0x0013) + 3)
;decoders.c:111: if (triggerState.curGap < 50) return;
	lda	(_triggerState + 0x0013)
	sta	,x
	lda	((_triggerState + 0x0013) + 1)
	sta	1,x
	lda	((_triggerState + 0x0013) + 2)
	sta	2,x
	lda	((_triggerState + 0x0013) + 3)
	sta	3,x
	lda	3,x
	sub	#0x32
	lda	2,x
	sbc	#0x00
	lda	1,x
	sbc	#0x00
	lda	,x
	sbc	#0x00
	bcc	00102$
	jmp	00120$
00102$:
;decoders.c:112: if (triggerState.lastGap > 0 && triggerState.curGap < (triggerState.lastGap / 3)) return;
	lda	(_triggerState + 0x0017)
	sta	1,s
	lda	((_triggerState + 0x0017) + 1)
	sta	2,s
	lda	((_triggerState + 0x0017) + 2)
	sta	3,s
	lda	((_triggerState + 0x0017) + 3)
	sta	4,s
	tsx
	lda	,x
	ora	1,x
	ora	2,x
	ora	3,x
	beq	00104$
	lda	(_triggerState + 0x0013)
	sta	,x
	lda	((_triggerState + 0x0013) + 1)
	sta	1,x
	lda	((_triggerState + 0x0013) + 2)
	sta	2,x
	lda	((_triggerState + 0x0013) + 3)
	sta	3,x
	lda	(_triggerState + 0x0017)
	sta	12,x
	lda	((_triggerState + 0x0017) + 1)
	sta	13,x
	lda	((_triggerState + 0x0017) + 2)
	sta	14,x
	lda	((_triggerState + 0x0017) + 3)
	sta	15,x
	lda	#0x03
	psha
	clra
	psha
	psha
	psha
	lda	15,x
	psha
	lda	14,x
	psha
	lda	13,x
	psha
	lda	12,x
	psha
	jsr	__divulong
	sta	24,s
	stx	23,s
	lda	*___SDCC_hc08_ret2
	sta	22,s
	lda	*___SDCC_hc08_ret3
	sta	21,s
	ais	#8
	tsx
	lda	3,x
	sub	15,x
	lda	2,x
	sbc	14,x
	lda	1,x
	sbc	13,x
	lda	,x
	sbc	12,x
	bcc	00104$
	jmp	00120$
00104$:
;decoders.c:114: triggerState.toothLastToothTime = curTime;
	lda	9,s
	sta	_triggerState
	lda	10,s
	sta	(_triggerState + 1)
	lda	11,s
	sta	(_triggerState + 2)
	lda	12,s
	sta	(_triggerState + 3)
;decoders.c:115: triggerState.toothCurrentCount++;
	lda	(_triggerState + 0x0010)
	inca
	sta	(_triggerState + 0x0010)
;decoders.c:117: if (triggerState.toothCurrentCount > (uint8_t)(triggerState.toothTotalCount * 2)) {
	ldx	(_triggerState + 0x0010)
	lda	(_triggerState + 0x0011)
	lsla	
	sta	13,s
	cpx	13,s
	bls	00107$
;decoders.c:118: triggerState.toothCurrentCount = 1;
	lda	#0x01
	sta	(_triggerState + 0x0010)
;decoders.c:119: triggerState.hasSync = false;
	deca
	sta	(_triggerState + 0x001b)
00107$:
;decoders.c:122: isCranking = (currentStatus.RPM > 0) &&
	lda	_currentStatus
	sta	13,s
	lda	(_currentStatus + 1)
	sta	14,s
	tsx
	lda	13,x
	ora	12,x
	beq	00122$
;decoders.c:123: (currentStatus.RPM < ((uint16_t)configPage1.crankRPM * 10));
	lda	(_configPage1 + 0x001d)
	clrx
	psha
	pshx
	lda	#0x0a
	jsr	__mulint
	sta	4,s
	stx	3,s
	ais	#2
	lda	14,s
	ldx	13,s
	sub	2,s
	txa
	sbc	1,s
	bcs	00123$
00122$:
	clra
	bra	00124$
00123$:
	lda	#0x01
00124$:
	sta	21,s
;decoders.c:125: baseGap = (triggerState.lastGap > 0) ? triggerState.lastGap : triggerState.curGap;
	lda	(_triggerState + 0x0017)
	sta	13,s
	lda	((_triggerState + 0x0017) + 1)
	sta	14,s
	lda	((_triggerState + 0x0017) + 2)
	sta	15,s
	lda	((_triggerState + 0x0017) + 3)
	sta	16,s
	tsx
	lda	12,x
	ora	13,x
	ora	14,x
	ora	15,x
	beq	00125$
	lda	(_triggerState + 0x0017)
	sta	12,x
	lda	((_triggerState + 0x0017) + 1)
	sta	13,x
	lda	((_triggerState + 0x0017) + 2)
	sta	14,x
	lda	((_triggerState + 0x0017) + 3)
	sta	15,x
	bra	00126$
00125$:
	lda	(_triggerState + 0x0013)
	sta	13,s
	lda	((_triggerState + 0x0013) + 1)
	sta	14,s
	lda	((_triggerState + 0x0013) + 2)
	sta	15,s
	lda	((_triggerState + 0x0013) + 3)
	sta	16,s
00126$:
;decoders.c:126: dynamicThreshold = isCranking ? (baseGap + ((baseGap * 2) / 5))
	tst	21,s
	beq	00127$
	tsx
	lda	15,x
	ldx	14,x
	lsla
	rolx
	sta	4,s
	stx	3,s
	lda	14,s
	ldx	13,s
	rola
	rolx
	sta	2,s
	stx	1,s
	lda	#0x05
	psha
	clra
	psha
	psha
	psha
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	jsr	__divulong
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#8
	tsx
	lda	15,x
	add	3,x
	sta	3,x
	lda	14,x
	adc	2,x
	sta	2,x
	lda	13,x
	adc	1,x
	sta	1,x
	lda	12,x
	adc	,x
	sta	,x
	bra	00128$
00127$:
;decoders.c:127: : (baseGap + (baseGap >> 1));
	tsx
	lda	13,x
	ldx	12,x
	lsrx
	rora
	sta	6,s
	stx	5,s
	lda	16,s
	ldx	15,s
	rorx
	rora
	sta	8,s
	stx	7,s
	tsx
	lda	15,x
	add	7,x
	sta	3,x
	lda	14,x
	adc	6,x
	sta	2,x
	lda	13,x
	adc	5,x
	sta	1,x
	lda	12,x
	adc	4,x
	sta	,x
00128$:
;decoders.c:128: isGap = (triggerState.curGap > dynamicThreshold);
	lda	(_triggerState + 0x0013)
	sta	5,s
	lda	((_triggerState + 0x0013) + 1)
	sta	6,s
	lda	((_triggerState + 0x0013) + 2)
	sta	7,s
	lda	((_triggerState + 0x0013) + 3)
	sta	8,s
	tsx
	lda	3,x
	sub	7,x
	lda	2,x
	sbc	6,x
	lda	1,x
	sbc	5,x
	lda	,x
	sbc	4,x
	bcs	00216$
	jmp	00119$
00216$:
;decoders.c:130: if (isGap) {
;decoders.c:131: uint16_t expectedPulses = (uint16_t)triggerState.triggerActualTeeth * triggerEdgesPerTooth;
	lda	(_triggerState + 0x0012)
	sta	5,x
	clrx
	stx	5,s
	lda	_triggerEdgesPerTooth
	psha
	pshx
	tsx
	lda	7,x
	ldx	6,x
	jsr	__mulint
	sta	22,s
	stx	21,s
	ais	#2
;decoders.c:132: uint16_t toleranceWindow = isCranking ? 20 : 10;
	tst	21,s
	beq	00129$
	clrx
	lda	#0x14
	bra	00130$
00129$:
	clrx
	lda	#0x0a
00130$:
	sta	18,s
	stx	17,s
;decoders.c:134: if (triggerState.toothCurrentCount >= (expectedPulses - toleranceWindow) &&
	ldx	(_triggerState + 0x0010)
	lda	20,s
	sub	18,s
	sta	6,s
	lda	19,s
	sbc	17,s
	sta	5,s
	txa
	clrx
	sub	6,s
	txa
	sbc	5,s
	bcc	00218$
	jmp	00115$
00218$:
;decoders.c:135: triggerState.toothCurrentCount <= (expectedPulses + toleranceWindow)) {
	lda	(_triggerState + 0x0010)
	psha
	lda	19,s
	add	21,s
	tax
	lda	18,s
	adc	20,s
	psha
	pulh
	pula
	sta	6,s
	psha
	clra
	sta	6,s
	pula
	txa
	sub	6,s
	pshh
	pula
	sbc	5,s
	bcc	00219$
	jmp	00115$
00219$:
;decoders.c:137: triggerState.hasSync = true;
	lda	#0x01
	sta	(_triggerState + 0x001b)
;decoders.c:138: triggerState.syncLossCounter = 0;
	deca
	sta	(_triggerState + 0x001c)
;decoders.c:139: triggerState.toothOneTime = curTime;
	lda	9,s
	sta	(_triggerState + 0x000c)
	lda	10,s
	sta	((_triggerState + 0x000c) + 1)
	lda	11,s
	sta	((_triggerState + 0x000c) + 2)
	lda	12,s
	sta	((_triggerState + 0x000c) + 3)
;decoders.c:141: if (triggerState.toothLastMinusOneTime > 0) {
	lda	(_triggerState + 0x0004)
	sta	5,s
	lda	((_triggerState + 0x0004) + 1)
	sta	6,s
	lda	((_triggerState + 0x0004) + 2)
	sta	7,s
	lda	((_triggerState + 0x0004) + 3)
	sta	8,s
	tsx
	lda	4,x
	ora	5,x
	ora	6,x
	ora	7,x
	beq	00109$
;decoders.c:142: triggerState.revolutionTime = curTime - triggerState.toothLastMinusOneTime;
	lda	(_triggerState + 0x0004)
	sta	4,x
	lda	((_triggerState + 0x0004) + 1)
	sta	5,x
	lda	((_triggerState + 0x0004) + 2)
	sta	6,x
	lda	((_triggerState + 0x0004) + 3)
	sta	7,x
	lda	11,x
	sub	7,x
	sta	7,x
	lda	10,x
	sbc	6,x
	sta	6,x
	lda	9,x
	sbc	5,x
	sta	5,x
	lda	8,x
	sbc	4,x
	sta	4,x
	lda	4,x
	sta	(_triggerState + 0x0008)
	lda	5,x
	sta	((_triggerState + 0x0008) + 1)
	lda	6,x
	sta	((_triggerState + 0x0008) + 2)
	lda	7,x
	sta	((_triggerState + 0x0008) + 3)
00109$:
;decoders.c:144: triggerState.toothLastMinusOneTime = curTime;
	lda	9,s
	sta	(_triggerState + 0x0004)
	lda	10,s
	sta	((_triggerState + 0x0004) + 1)
	lda	11,s
	sta	((_triggerState + 0x0004) + 2)
	lda	12,s
	sta	((_triggerState + 0x0004) + 3)
;decoders.c:145: triggerState.toothCurrentCount = 1;
	lda	#0x01
	sta	(_triggerState + 0x0010)
;decoders.c:146: revolutionCounter = (revolutionCounter == 0) ? 1 : 0;
	lda	_revolutionCounter
	bne	00131$
	clrx
	lda	#0x01
	bra	00132$
00131$:
	clrx
	txa
00132$:
	sta	_revolutionCounter
;decoders.c:148: if (triggerState.revolutionTime > 0) {
	lda	(_triggerState + 0x0008)
	sta	5,s
	lda	((_triggerState + 0x0008) + 1)
	sta	6,s
	lda	((_triggerState + 0x0008) + 2)
	sta	7,s
	lda	((_triggerState + 0x0008) + 3)
	sta	8,s
	tsx
	lda	4,x
	ora	5,x
	ora	6,x
	ora	7,x
	beq	00119$
;decoders.c:149: scheduleInjectionISR();
	jsr	_scheduleInjectionISR
;decoders.c:150: scheduleIgnitionISR();
	jsr	_scheduleIgnitionISR
	bra	00119$
00115$:
;decoders.c:153: triggerState.toothCurrentCount = 1;
	lda	#0x01
	sta	(_triggerState + 0x0010)
;decoders.c:154: triggerState.syncLossCounter++;
	lda	(_triggerState + 0x001c)
	inca
	sta	(_triggerState + 0x001c)
;decoders.c:155: if (triggerState.syncLossCounter > 10) {
	lda	(_triggerState + 0x001c)
	cmp	#0x0a
	bls	00119$
;decoders.c:156: triggerState.hasSync = false;
	clra
	sta	(_triggerState + 0x001b)
00119$:
;decoders.c:161: triggerState.lastGap = triggerState.curGap;
	lda	(_triggerState + 0x0013)
	sta	5,s
	lda	((_triggerState + 0x0013) + 1)
	sta	6,s
	lda	((_triggerState + 0x0013) + 2)
	sta	7,s
	lda	((_triggerState + 0x0013) + 3)
	sta	8,s
	lda	5,s
	sta	(_triggerState + 0x0017)
	lda	6,s
	sta	((_triggerState + 0x0017) + 1)
	lda	7,s
	sta	((_triggerState + 0x0017) + 2)
	lda	8,s
	sta	((_triggerState + 0x0017) + 3)
00120$:
;decoders.c:162: }
	ais	#21
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'triggerPri_BasicDistributor'
;------------------------------------------------------------
;curTime                   Allocated to stack - sp +9
;sloc0                     Allocated to stack - sp +9
;sloc1                     Allocated to stack - sp +1
;sloc2                     Allocated to stack - sp +5
;------------------------------------------------------------
;decoders.c:164: static void triggerPri_BasicDistributor(void) {
;	-----------------------------------------
;	 function triggerPri_BasicDistributor
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 12 bytes.
_triggerPri_BasicDistributor:
	ais	#-12
;decoders.c:165: uint32_t curTime = micros();
	jsr	_micros
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
;decoders.c:167: triggerState.curGap = curTime - triggerState.toothLastToothTime;
	lda	_triggerState
	sta	1,s
	lda	(_triggerState + 1)
	sta	2,s
	lda	(_triggerState + 2)
	sta	3,s
	lda	(_triggerState + 3)
	sta	4,s
	tsx
	lda	11,x
	sub	3,x
	sta	3,x
	lda	10,x
	sbc	2,x
	sta	2,x
	lda	9,x
	sbc	1,x
	sta	1,x
	lda	8,x
	sbc	,x
	sta	,x
	lda	,x
	sta	(_triggerState + 0x0013)
	lda	1,x
	sta	((_triggerState + 0x0013) + 1)
	lda	2,x
	sta	((_triggerState + 0x0013) + 2)
	lda	3,x
	sta	((_triggerState + 0x0013) + 3)
;decoders.c:168: if (triggerState.curGap < triggerState.triggerFilterTime) return;
	lda	(_triggerState + 0x0013)
	sta	,x
	lda	((_triggerState + 0x0013) + 1)
	sta	1,x
	lda	((_triggerState + 0x0013) + 2)
	sta	2,x
	lda	((_triggerState + 0x0013) + 3)
	sta	3,x
	lda	(_triggerState + 0x0025)
	psha
	pulh
	ldx	((_triggerState + 0x0025) + 1)
	stx	8,s
	pshh
	pula
	sta	7,s
	clra
	sta	6,s
	sta	5,s
	tsx
	lda	3,x
	sub	7,x
	lda	2,x
	sbc	6,x
	lda	1,x
	sbc	5,x
	lda	,x
	sbc	4,x
	bcc	00102$
	jmp	00103$
00102$:
;decoders.c:170: triggerState.hasSync = true;
	lda	#0x01
	sta	(_triggerState + 0x001b)
;decoders.c:171: triggerState.toothCurrentCount = 1;
	sta	(_triggerState + 0x0010)
;decoders.c:172: triggerState.toothOneTime = curTime;
	lda	9,s
	sta	(_triggerState + 0x000c)
	lda	10,s
	sta	((_triggerState + 0x000c) + 1)
	lda	11,s
	sta	((_triggerState + 0x000c) + 2)
	lda	12,s
	sta	((_triggerState + 0x000c) + 3)
;decoders.c:173: triggerState.revolutionTime = triggerState.curGap;
	lda	(_triggerState + 0x0013)
	sta	5,s
	lda	((_triggerState + 0x0013) + 1)
	sta	6,s
	lda	((_triggerState + 0x0013) + 2)
	sta	7,s
	lda	((_triggerState + 0x0013) + 3)
	sta	8,s
	lda	5,s
	sta	(_triggerState + 0x0008)
	lda	6,s
	sta	((_triggerState + 0x0008) + 1)
	lda	7,s
	sta	((_triggerState + 0x0008) + 2)
	lda	8,s
	sta	((_triggerState + 0x0008) + 3)
;decoders.c:174: triggerState.toothLastToothTime = curTime;
	lda	9,s
	sta	_triggerState
	lda	10,s
	sta	(_triggerState + 1)
	lda	11,s
	sta	(_triggerState + 2)
	lda	12,s
	sta	(_triggerState + 3)
;decoders.c:175: triggerState.toothLastMinusOneTime = curTime;
	lda	9,s
	sta	(_triggerState + 0x0004)
	lda	10,s
	sta	((_triggerState + 0x0004) + 1)
	lda	11,s
	sta	((_triggerState + 0x0004) + 2)
	lda	12,s
	sta	((_triggerState + 0x0004) + 3)
;decoders.c:176: revolutionCounter = (revolutionCounter == 0) ? 1 : 0;
	lda	_revolutionCounter
	bne	00105$
	clrx
	lda	#0x01
	bra	00106$
00105$:
	clrx
	txa
00106$:
	sta	_revolutionCounter
;decoders.c:178: scheduleInjectionISR();
	jsr	_scheduleInjectionISR
;decoders.c:179: scheduleIgnitionISR();
	jsr	_scheduleIgnitionISR
00103$:
;decoders.c:180: }
	ais	#12
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'triggerSetup_MissingTooth'
;------------------------------------------------------------
;decoders.c:185: void triggerSetup_MissingTooth(void) {
;	-----------------------------------------
;	 function triggerSetup_MissingTooth
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_triggerSetup_MissingTooth:
;decoders.c:186: triggerState.triggerTeeth = configPage2.triggerTeeth;
	lda	(_configPage2 + 0x0001)
	sta	(_triggerState + 0x0023)
;decoders.c:187: triggerState.triggerMissing = configPage2.triggerMissing;
	lda	(_configPage2 + 0x0002)
	sta	(_triggerState + 0x0024)
;decoders.c:194: if (triggerState.triggerTeeth == 0) {
	lda	(_triggerState + 0x0023)
	bne	00102$
;decoders.c:195: triggerState.triggerTeeth = 36;
	lda	#0x24
	sta	(_triggerState + 0x0023)
;decoders.c:196: triggerState.triggerMissing = 1;
	lda	#0x01
	sta	(_triggerState + 0x0024)
00102$:
;decoders.c:198: triggerState.triggerActualTeeth = triggerState.triggerTeeth - triggerState.triggerMissing;
	lda	(_triggerState + 0x0023)
	ldx	(_triggerState + 0x0024)
	pshx
	sub	1,s
	ais	#1
	sta	(_triggerState + 0x0012)
;decoders.c:199: triggerState.toothAngle = (uint16_t)(3600 / triggerState.triggerTeeth);
	lda	(_triggerState + 0x0023)
	clrx
	psha
	pshx
	lda	#0x10
	ldx	#0x0e
	jsr	__divsint
	ais	#2
	stx	(_triggerState + 0x0027)
	sta	((_triggerState + 0x0027) + 1)
;decoders.c:200: triggerState.triggerFilterTime = 50;
	clra
	sta	(_triggerState + 0x0025)
	lda	#0x32
	sta	((_triggerState + 0x0025) + 1)
;decoders.c:201: triggerState.toothTotalCount = triggerState.triggerTeeth;
	lda	(_triggerState + 0x0023)
	sta	(_triggerState + 0x0011)
;decoders.c:203: currentTriggerISR = triggerPri_MissingTooth;
	lda	#>_triggerPri_MissingTooth
	sta	_currentTriggerISR
	lda	#_triggerPri_MissingTooth
	sta	(_currentTriggerISR + 1)
;decoders.c:204: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'triggerSetup_BasicDistributor'
;------------------------------------------------------------
;decoders.c:206: void triggerSetup_BasicDistributor(void) {
;	-----------------------------------------
;	 function triggerSetup_BasicDistributor
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_triggerSetup_BasicDistributor:
;decoders.c:207: triggerState.triggerTeeth = 1;
	lda	#0x01
	sta	(_triggerState + 0x0023)
;decoders.c:208: triggerState.triggerMissing = 0;
	deca
	sta	(_triggerState + 0x0024)
;decoders.c:209: triggerState.triggerActualTeeth = 1;
	inca
	sta	(_triggerState + 0x0012)
;decoders.c:210: triggerState.toothAngle = 3600;
	lda	#0x0e
	sta	(_triggerState + 0x0027)
	lda	#0x10
	sta	((_triggerState + 0x0027) + 1)
;decoders.c:211: triggerState.triggerFilterTime = 500;
	lda	#0x01
	sta	(_triggerState + 0x0025)
	lda	#0xf4
	sta	((_triggerState + 0x0025) + 1)
;decoders.c:212: triggerState.toothTotalCount = 1;
	lda	#0x01
	sta	(_triggerState + 0x0011)
;decoders.c:214: currentTriggerISR = triggerPri_BasicDistributor;
	lda	#>_triggerPri_BasicDistributor
	sta	_currentTriggerISR
	lda	#_triggerPri_BasicDistributor
	sta	(_currentTriggerISR + 1)
;decoders.c:215: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'triggerInit'
;------------------------------------------------------------
;decoders.c:217: void triggerInit(void) {
;	-----------------------------------------
;	 function triggerInit
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_triggerInit:
;decoders.c:218: resetTriggerState();
	jsr	_resetTriggerState
;decoders.c:220: if (configPage2.triggerPattern == TRIGGER_BASIC_DIST) {
	lda	_configPage2
	cmp	#0x01
	bne	00102$
;decoders.c:221: triggerSetup_BasicDistributor();
	jsr	_triggerSetup_BasicDistributor
	bra	00103$
00102$:
;decoders.c:223: triggerSetup_MissingTooth();
	jsr	_triggerSetup_MissingTooth
00103$:
;decoders.c:226: attachTriggerInterrupt();
;decoders.c:227: }
	jmp	_attachTriggerInterrupt
;------------------------------------------------------------
;Allocation info for local variables in function 'calculateRPM'
;------------------------------------------------------------
;rpm                       Allocated to stack - sp +1
;sloc0                     Allocated to stack - sp +5
;------------------------------------------------------------
;decoders.c:229: void calculateRPM(void) {
;	-----------------------------------------
;	 function calculateRPM
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 8 bytes.
_calculateRPM:
	ais	#-8
;decoders.c:230: if (!triggerState.hasSync) {
	lda	(_triggerState + 0x001b)
	bne	00102$
;decoders.c:231: triggerState.RPM = 0;
	clra
	sta	(_triggerState + 0x001d)
	sta	((_triggerState + 0x001d) + 1)
;decoders.c:232: currentStatus.RPM = 0;
	sta	_currentStatus
	sta	(_currentStatus + 1)
;decoders.c:233: currentStatus.hasSync = false;
	sta	(_currentStatus + 0x0002)
;decoders.c:234: return;
	jmp	00110$
00102$:
;decoders.c:237: if (triggerState.revolutionTime > 0) {
	lda	(_triggerState + 0x0008)
	sta	5,s
	lda	((_triggerState + 0x0008) + 1)
	sta	6,s
	lda	((_triggerState + 0x0008) + 2)
	sta	7,s
	lda	((_triggerState + 0x0008) + 3)
	sta	8,s
	tsx
	lda	4,x
	ora	5,x
	ora	6,x
	ora	7,x
	bne	00133$
	jmp	00108$
00133$:
;decoders.c:238: uint32_t rpm = MICROS_PER_SEC * 60UL / triggerState.revolutionTime;
	lda	(_triggerState + 0x0008)
	sta	4,x
	lda	((_triggerState + 0x0008) + 1)
	sta	5,x
	lda	((_triggerState + 0x0008) + 2)
	sta	6,x
	lda	((_triggerState + 0x0008) + 3)
	sta	7,x
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	clra
	psha
	lda	#0x87
	psha
	lda	#0x93
	psha
	lda	#0x03
	psha
	jsr	__divulong
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#8
	tsx
	lda	4,x
	sta	,x
	lda	5,x
	sta	1,x
	lda	6,x
	sta	2,x
	lda	7,x
	sta	3,x
;decoders.c:239: if (rpm > 15000) rpm = 15000;
	lda	#0x98
	sub	7,x
	lda	#0x3a
	sbc	6,x
	clra
	sbc	5,x
	clra
	sbc	4,x
	bcc	00104$
	clra
	sta	,x
	sta	1,x
	lda	#0x3a
	sta	2,x
	lda	#0x98
	sta	3,x
00104$:
;decoders.c:240: if (rpm < 100) rpm = 0;
	tsx
	lda	3,x
	sub	#0x64
	lda	2,x
	sbc	#0x00
	lda	1,x
	sbc	#0x00
	lda	,x
	sbc	#0x00
	bcc	00106$
	clra
	sta	,x
	sta	1,x
	sta	2,x
	sta	3,x
00106$:
;decoders.c:242: triggerState.RPM = (uint16_t)rpm;
	lda	4,s
	ldx	3,s
	stx	(_triggerState + 0x001d)
	sta	((_triggerState + 0x001d) + 1)
;decoders.c:247: }
	tpa
	sei
	psha
;decoders.c:245: currentStatus.RPM = triggerState.RPM;
	ldx	(_triggerState + 0x001d)
	lda	((_triggerState + 0x001d) + 1)
	stx	_currentStatus
	sta	(_currentStatus + 1)
;decoders.c:246: currentStatus.hasSync = true;
	lda	#0x01
	sta	(_currentStatus + 0x0002)
	pula
	tap
	bra	00110$
00108$:
;decoders.c:249: triggerState.RPM = 0;
	clra
	sta	(_triggerState + 0x001d)
	sta	((_triggerState + 0x001d) + 1)
;decoders.c:250: currentStatus.RPM = 0;
	sta	_currentStatus
	sta	(_currentStatus + 1)
00110$:
;decoders.c:252: }
	ais	#8
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'checkSyncLoss'
;------------------------------------------------------------
;timeSinceLastTooth        Allocated to stack - sp +5
;sloc0                     Allocated to stack - sp +5
;sloc1                     Allocated to stack - sp +1
;------------------------------------------------------------
;decoders.c:254: void checkSyncLoss(void) {
;	-----------------------------------------
;	 function checkSyncLoss
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 8 bytes.
_checkSyncLoss:
	ais	#-8
;decoders.c:255: uint32_t timeSinceLastTooth = micros() - triggerState.toothLastToothTime;
	jsr	_micros
	sta	8,s
	stx	7,s
	lda	*___SDCC_hc08_ret2
	sta	6,s
	lda	*___SDCC_hc08_ret3
	sta	5,s
	lda	_triggerState
	sta	1,s
	lda	(_triggerState + 1)
	sta	2,s
	lda	(_triggerState + 2)
	sta	3,s
	lda	(_triggerState + 3)
	sta	4,s
	tsx
	lda	7,x
	sub	3,x
	sta	3,x
	lda	6,x
	sbc	2,x
	sta	2,x
	lda	5,x
	sbc	1,x
	sta	1,x
	lda	4,x
	sbc	,x
	sta	,x
;decoders.c:257: if (timeSinceLastTooth > (SYNC_TIMEOUT * 1000UL)) {
	lda	#0x40
	sub	3,x
	lda	#0x42
	sbc	2,x
	lda	#0x0f
	sbc	1,x
	clra
	sbc	,x
	bcc	00103$
;decoders.c:262: }
	tpa
	sei
	psha
;decoders.c:259: triggerState.hasSync = false;
	clra
	sta	(_triggerState + 0x001b)
;decoders.c:260: currentStatus.hasSync = false;
	sta	(_currentStatus + 0x0002)
;decoders.c:261: currentStatus.RPM = 0;
	sta	_currentStatus
	sta	(_currentStatus + 1)
	pula
	tap
00103$:
;decoders.c:264: }
	ais	#8
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'angleToTime'
;------------------------------------------------------------
;angle                     Allocated to registers x h 
;sloc0                     Allocated to stack - sp +1
;sloc1                     Allocated to stack - sp +5
;------------------------------------------------------------
;decoders.c:266: uint32_t angleToTime(uint16_t angle) {
;	-----------------------------------------
;	 function angleToTime
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 8 bytes.
_angleToTime:
	ais	#-8
	pshx
	tax
	pulh
;decoders.c:267: if (triggerState.revolutionTime == 0) return 0;
	lda	(_triggerState + 0x0008)
	sta	1,s
	lda	((_triggerState + 0x0008) + 1)
	sta	2,s
	lda	((_triggerState + 0x0008) + 2)
	sta	3,s
	lda	((_triggerState + 0x0008) + 3)
	sta	4,s
	lda	1,s
	ora	2,s
	ora	3,s
	ora	4,s
	bne	00102$
	clra
	tax
	sta	*___SDCC_hc08_ret2
	sta	*___SDCC_hc08_ret3
	jmp	00103$
00102$:
;decoders.c:268: return ((uint32_t)angle * triggerState.revolutionTime) / 360UL;
	stx	4,s
	pshh
	pula
	sta	3,s
	clra
	sta	2,s
	sta	1,s
	lda	(_triggerState + 0x0008)
	sta	5,s
	lda	((_triggerState + 0x0008) + 1)
	sta	6,s
	lda	((_triggerState + 0x0008) + 2)
	sta	7,s
	lda	((_triggerState + 0x0008) + 3)
	sta	8,s
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	jsr	__mullong
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#8
	lda	#0x68
	psha
	lda	#0x01
	psha
	deca
	psha
	psha
	tsx
	lda	11,x
	psha
	lda	10,x
	psha
	lda	9,x
	psha
	lda	8,x
	psha
	jsr	__divulong
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#8
	tsx
	lda	4,x
	sta	*___SDCC_hc08_ret3
	lda	5,x
	sta	*___SDCC_hc08_ret2
	ldx	6,x
	lda	8,s
00103$:
;decoders.c:269: }
	ais	#8
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'timeToAngle'
;------------------------------------------------------------
;time                      Allocated to stack - sp +11
;sloc0                     Allocated to stack - sp +5
;sloc1                     Allocated to stack - sp +1
;------------------------------------------------------------
;decoders.c:271: uint16_t timeToAngle(uint32_t time) {
;	-----------------------------------------
;	 function timeToAngle
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 8 bytes.
_timeToAngle:
	ais	#-8
;decoders.c:272: if (triggerState.revolutionTime == 0) return 0;
	lda	(_triggerState + 0x0008)
	sta	5,s
	lda	((_triggerState + 0x0008) + 1)
	sta	6,s
	lda	((_triggerState + 0x0008) + 2)
	sta	7,s
	lda	((_triggerState + 0x0008) + 3)
	sta	8,s
	tsx
	lda	4,x
	ora	5,x
	ora	6,x
	ora	7,x
	bne	00102$
	clra
	tax
	bra	00103$
00102$:
;decoders.c:273: return (uint16_t)((time * 360UL) / triggerState.revolutionTime);
	tsx
	lda	13,x
	psha
	lda	12,x
	psha
	lda	11,x
	psha
	lda	10,x
	psha
	lda	#0x68
	psha
	lda	#0x01
	psha
	deca
	psha
	psha
	jsr	__mullong
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#8
	lda	(_triggerState + 0x0008)
	sta	1,s
	lda	((_triggerState + 0x0008) + 1)
	sta	2,s
	lda	((_triggerState + 0x0008) + 2)
	sta	3,s
	lda	((_triggerState + 0x0008) + 3)
	sta	4,s
	tsx
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	jsr	__divulong
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#8
	lda	4,s
	ldx	3,s
00103$:
;decoders.c:274: }
	ais	#8
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'getCrankAngle'
;------------------------------------------------------------
;timeSinceToothOne         Allocated to stack - sp +1
;angle                     Allocated to registers a x 
;sloc0                     Allocated to stack - sp +5
;sloc1                     Allocated to stack - sp +9
;------------------------------------------------------------
;decoders.c:276: uint16_t getCrankAngle(void) {
;	-----------------------------------------
;	 function getCrankAngle
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 12 bytes.
_getCrankAngle:
	ais	#-12
;decoders.c:280: if (!triggerState.hasSync || triggerState.revolutionTime == 0) return 0;
	lda	(_triggerState + 0x001b)
	beq	00101$
	lda	(_triggerState + 0x0008)
	sta	5,s
	lda	((_triggerState + 0x0008) + 1)
	sta	6,s
	lda	((_triggerState + 0x0008) + 2)
	sta	7,s
	lda	((_triggerState + 0x0008) + 3)
	sta	8,s
	tsx
	lda	4,x
	ora	5,x
	ora	6,x
	ora	7,x
	bne	00102$
00101$:
	clra
	tax
	jmp	00106$
00102$:
;decoders.c:282: timeSinceToothOne = micros() - triggerState.toothOneTime;
	jsr	_micros
	sta	8,s
	stx	7,s
	lda	*___SDCC_hc08_ret2
	sta	6,s
	lda	*___SDCC_hc08_ret3
	sta	5,s
	lda	(_triggerState + 0x000c)
	sta	9,s
	lda	((_triggerState + 0x000c) + 1)
	sta	10,s
	lda	((_triggerState + 0x000c) + 2)
	sta	11,s
	lda	((_triggerState + 0x000c) + 3)
	sta	12,s
	tsx
	lda	7,x
	sub	11,x
	sta	11,x
	lda	6,x
	sbc	10,x
	sta	10,x
	lda	5,x
	sbc	9,x
	sta	9,x
	lda	4,x
	sbc	8,x
	sta	8,x
	lda	8,x
	sta	,x
	lda	9,x
	sta	1,x
	lda	10,x
	sta	2,x
	lda	11,x
	sta	3,x
;decoders.c:283: if (timeSinceToothOne >= triggerState.revolutionTime) {
	lda	(_triggerState + 0x0008)
	sta	4,x
	lda	((_triggerState + 0x0008) + 1)
	sta	5,x
	lda	((_triggerState + 0x0008) + 2)
	sta	6,x
	lda	((_triggerState + 0x0008) + 3)
	sta	7,x
	lda	11,x
	sub	7,x
	lda	10,x
	sbc	6,x
	lda	9,x
	sbc	5,x
	lda	8,x
	sbc	4,x
	bcs	00105$
;decoders.c:284: timeSinceToothOne = triggerState.revolutionTime - 1;
	lda	(_triggerState + 0x0008)
	sta	8,x
	lda	((_triggerState + 0x0008) + 1)
	sta	9,x
	lda	((_triggerState + 0x0008) + 2)
	sta	10,x
	lda	((_triggerState + 0x0008) + 3)
	sta	11,x
	lda	11,x
	sub	#0x01
	sta	3,x
	lda	10,x
	sbc	#0x00
	sta	2,x
	lda	9,x
	sbc	#0x00
	sta	1,x
	lda	8,x
	sbc	#0x00
	sta	,x
00105$:
;decoders.c:287: angle = (uint16_t)((timeSinceToothOne * 360UL) / triggerState.revolutionTime);
	tsx
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	lda	#0x68
	psha
	lda	#0x01
	psha
	deca
	psha
	psha
	jsr	__mullong
	sta	20,s
	stx	19,s
	lda	*___SDCC_hc08_ret2
	sta	18,s
	lda	*___SDCC_hc08_ret3
	sta	17,s
	ais	#8
	lda	(_triggerState + 0x0008)
	sta	5,s
	lda	((_triggerState + 0x0008) + 1)
	sta	6,s
	lda	((_triggerState + 0x0008) + 2)
	sta	7,s
	lda	((_triggerState + 0x0008) + 3)
	sta	8,s
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	lda	11,x
	psha
	lda	10,x
	psha
	lda	9,x
	psha
	lda	8,x
	psha
	jsr	__divulong
	sta	20,s
	stx	19,s
	lda	*___SDCC_hc08_ret2
	sta	18,s
	lda	*___SDCC_hc08_ret3
	sta	17,s
	ais	#8
	lda	12,s
	ldx	11,s
;decoders.c:288: return angle;
00106$:
;decoders.c:289: }
	ais	#12
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'attachTriggerInterrupt'
;------------------------------------------------------------
;decoders.c:294: void attachTriggerInterrupt(void) {
;	-----------------------------------------
;	 function attachTriggerInterrupt
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_attachTriggerInterrupt:
;decoders.c:298: INTSCR &= (uint8_t)~(1 << INTSCR_MODE);
	lda	*0x1d
	and	#0xfe
	sta	*0x1d
;decoders.c:301: INTSCR &= (uint8_t)~(1 << INTSCR_IMASK);
	lda	*0x1d
	and	#0xfd
	sta	*0x1d
;decoders.c:302: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'resetTriggerState'
;------------------------------------------------------------
;decoders.c:304: void resetTriggerState(void) {
;	-----------------------------------------
;	 function resetTriggerState
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_resetTriggerState:
;decoders.c:327: }
	tpa
	sei
	psha
;decoders.c:306: triggerState.toothLastToothTime = 0;
	clra
	sta	_triggerState
	sta	(_triggerState + 1)
	sta	(_triggerState + 2)
	sta	(_triggerState + 3)
;decoders.c:307: triggerState.toothLastMinusOneTime = 0;
	sta	(_triggerState + 0x0004)
	sta	((_triggerState + 0x0004) + 1)
	sta	((_triggerState + 0x0004) + 2)
	sta	((_triggerState + 0x0004) + 3)
;decoders.c:308: triggerState.revolutionTime = 0;
	sta	(_triggerState + 0x0008)
	sta	((_triggerState + 0x0008) + 1)
	sta	((_triggerState + 0x0008) + 2)
	sta	((_triggerState + 0x0008) + 3)
;decoders.c:309: triggerState.toothOneTime = 0;
	sta	(_triggerState + 0x000c)
	sta	((_triggerState + 0x000c) + 1)
	sta	((_triggerState + 0x000c) + 2)
	sta	((_triggerState + 0x000c) + 3)
;decoders.c:311: triggerState.toothCurrentCount = 0;
	sta	(_triggerState + 0x0010)
;decoders.c:312: triggerState.toothTotalCount = 0;
	sta	(_triggerState + 0x0011)
;decoders.c:313: triggerState.triggerActualTeeth = 0;
	sta	(_triggerState + 0x0012)
;decoders.c:315: triggerState.curGap = 0;
	sta	(_triggerState + 0x0013)
	sta	((_triggerState + 0x0013) + 1)
	sta	((_triggerState + 0x0013) + 2)
	sta	((_triggerState + 0x0013) + 3)
;decoders.c:316: triggerState.lastGap = 0;
	sta	(_triggerState + 0x0017)
	sta	((_triggerState + 0x0017) + 1)
	sta	((_triggerState + 0x0017) + 2)
	sta	((_triggerState + 0x0017) + 3)
;decoders.c:317: triggerState.hasSync = false;
	sta	(_triggerState + 0x001b)
;decoders.c:318: triggerState.syncLossCounter = 0;
	sta	(_triggerState + 0x001c)
;decoders.c:320: triggerState.RPM = 0;
	sta	(_triggerState + 0x001d)
	sta	((_triggerState + 0x001d) + 1)
;decoders.c:321: triggerState.toothPeriod = 0;
	sta	(_triggerState + 0x001f)
	sta	((_triggerState + 0x001f) + 1)
	sta	((_triggerState + 0x001f) + 2)
	sta	((_triggerState + 0x001f) + 3)
;decoders.c:323: currentStatus.hasSync = false;
	sta	(_currentStatus + 0x0002)
;decoders.c:324: currentStatus.RPM = 0;
	sta	_currentStatus
	sta	(_currentStatus + 1)
;decoders.c:326: revolutionCounter = 0;
	sta	_revolutionCounter
	pula
	tap
;decoders.c:328: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'isr_irq'
;------------------------------------------------------------
;decoders.c:334: void isr_irq(void) __interrupt(2) {
;	-----------------------------------------
;	 function isr_irq
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_isr_irq:
	pshh
;decoders.c:335: if (currentTriggerISR != 0) {
	lda	_currentTriggerISR
	ora	(_currentTriggerISR + 1)
	beq	00103$
;decoders.c:336: currentTriggerISR();
	bsr	00112$
	bra	00111$
00112$:
	lda	(_currentTriggerISR + 1)
	psha
	lda	_currentTriggerISR
	psha
	rts
00111$:
00103$:
;decoders.c:338: }
	pulh
	rti
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
__xinit__revolutionCounter:
	.db #0x00	; 0
__xinit__triggerEdgesPerTooth:
	.db #0x01	; 1
	.area CABS    (ABS,CODE)
