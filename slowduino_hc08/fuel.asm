;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.2.0 #13081 (Linux)
;--------------------------------------------------------
	.module fuel
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
	.globl _getTableValue
	.globl _calculateInjection
	.globl _getVE
	.globl _calculateCorrections
	.globl _correctionWUE
	.globl _correctionASE
	.globl _startASE
	.globl _decrementASE
	.globl _correctionAE
	.globl _correctionCLT
	.globl _correctionBattery
	.globl _updateEngineStatus
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
_aseCounter:
	.ds 1
_aseValue:
	.ds 1
;--------------------------------------------------------
; extended address mode data
;--------------------------------------------------------
	.area XSEG
_updateEngineStatus_firstRun_65536_62:
	.ds 1
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'updateEngineStatus'
;------------------------------------------------------------
;sloc0                     Allocated to stack - sp +1
;firstRun                  Allocated with name '_updateEngineStatus_firstRun_65536_62'
;------------------------------------------------------------
;fuel.c:176: static bool firstRun = true;
	lda	#0x01
	sta	_updateEngineStatus_firstRun_65536_62
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
;Allocation info for local variables in function 'interpolate'
;------------------------------------------------------------
;x1                        Allocated to stack - sp +11
;x2                        Allocated to stack - sp +13
;y1                        Allocated to stack - sp +15
;y2                        Allocated to stack - sp +17
;x                         Allocated to registers a x 
;sloc0                     Allocated to stack - sp +1
;sloc1                     Allocated to stack - sp +5
;------------------------------------------------------------
;tables.h:33: static inline int16_t interpolate(int16_t x, int16_t x1, int16_t x2, int16_t y1, int16_t y2) {
;	-----------------------------------------
;	 function interpolate
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 8 bytes.
_interpolate:
	ais	#-8
;tables.h:34: if (x2 == x1) return y1;
	psha
	lda	15,s
	cmp	13,s
	pula
	bne	00110$
	psha
	lda	14,s
	cmp	12,s
	pula
	beq	00111$
00110$:
	bra	00102$
00111$:
	tsx
	ldx	14,x
	lda	16,s
	jmp	00103$
00102$:
;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
	sub	12,s
	psha
	txa
	sbc	12,s
	tax
	pula
	sta	4,s
	txa
	sta	3,s
	rola	
	clra	
	sbc	#0x00
	sta	2,s
	sta	1,s
	lda	18,s
	sub	16,s
	psha
	lda	18,s
	sbc	16,s
	tax
	pula
	sta	8,s
	txa
	sta	7,s
	rola	
	clra	
	sbc	#0x00
	sta	6,s
	sta	5,s
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
	lda	14,s
	sub	12,s
	psha
	lda	14,s
	sbc	12,s
	tax
	pula
	sta	4,s
	txa
	sta	3,s
	rola	
	clra	
	sbc	#0x00
	sta	2,s
	sta	1,s
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
	jsr	__divslong
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#8
	lda	8,s
	ldx	7,s
	add	16,s
	psha
	txa
	adc	16,s
	tax
	pula
00103$:
;tables.h:36: }
	ais	#8
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'calculateInjection'
;------------------------------------------------------------
;ve                        Allocated to registers h 
;corrections               Allocated to stack - sp +13
;pw                        Allocated to stack - sp +1
;sloc0                     Allocated to stack - sp +5
;sloc1                     Allocated to stack - sp +9
;------------------------------------------------------------
;fuel.c:14: uint16_t calculateInjection(void) {
;	-----------------------------------------
;	 function calculateInjection
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 14 bytes.
_calculateInjection:
	ais	#-14
;fuel.c:15: uint8_t ve = getVE();
	jsr	_getVE
	psha
	pulh
;fuel.c:19: currentStatus.VE = ve;
	pshh
	pula
	sta	(_currentStatus + 0x0022)
;fuel.c:21: corrections = calculateCorrections();
	pshh
	jsr	_calculateCorrections
	sta	15,s
	stx	14,s
	pulh
;fuel.c:22: currentStatus.corrections = corrections;
	lda	13,s
	sta	(_currentStatus + 0x0023)
	lda	14,s
	sta	((_currentStatus + 0x0023) + 1)
;fuel.c:24: pw = (uint32_t)configPage1.reqFuel;
	ldx	(_configPage1 + 0x0001)
	lda	((_configPage1 + 0x0001) + 1)
	sta	8,s
	stx	7,s
	psha
	clra
	sta	7,s
	clra
	sta	6,s
	pula
;fuel.c:25: pw = (pw * ve) / 100;
	pshh
	pula
	sta	12,s
	clra
	sta	11,s
	sta	10,s
	sta	9,s
	tsx
	lda	11,x
	psha
	lda	10,x
	psha
	lda	9,x
	psha
	lda	8,x
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
	sta	20,s
	stx	19,s
	lda	*___SDCC_hc08_ret2
	sta	18,s
	lda	*___SDCC_hc08_ret3
	sta	17,s
	ais	#8
	lda	#0x64
	psha
	clra
	psha
	psha
	psha
	tsx
	lda	15,x
	psha
	lda	14,x
	psha
	lda	13,x
	psha
	lda	12,x
	psha
;fuel.c:26: pw = (pw * currentStatus.MAP) / 100;
	jsr	__divulong
	sta	20,s
	stx	19,s
	lda	*___SDCC_hc08_ret2
	sta	18,s
	lda	*___SDCC_hc08_ret3
	sta	17,s
	ais	#8
	lda	(_currentStatus + 0x0013)
	tsx
	sta	7,x
	clrx
	stx	7,s
	stx	6,s
	stx	5,s
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
	jsr	__mullong
	sta	20,s
	stx	19,s
	lda	*___SDCC_hc08_ret2
	sta	18,s
	lda	*___SDCC_hc08_ret3
	sta	17,s
	ais	#8
	lda	#0x64
	psha
	clra
	psha
	psha
	psha
	tsx
	lda	15,x
	psha
	lda	14,x
	psha
	lda	13,x
	psha
	lda	12,x
	psha
;fuel.c:27: pw = (pw * corrections) / 100;
	jsr	__divulong
	sta	20,s
	stx	19,s
	lda	*___SDCC_hc08_ret2
	sta	18,s
	lda	*___SDCC_hc08_ret3
	sta	17,s
	ais	#8
	tsx
	lda	13,x
	sta	7,x
	lda	12,x
	sta	6,x
	clra
	sta	5,x
	sta	4,x
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
	jsr	__mullong
	sta	20,s
	stx	19,s
	lda	*___SDCC_hc08_ret2
	sta	18,s
	lda	*___SDCC_hc08_ret3
	sta	17,s
	ais	#8
	lda	#0x64
	psha
	clra
	psha
	psha
	psha
	tsx
	lda	15,x
	psha
	lda	14,x
	psha
	lda	13,x
	psha
	lda	12,x
	psha
;fuel.c:29: pw += configPage1.injOpen;
	jsr	__divulong
	sta	20,s
	stx	19,s
	lda	*___SDCC_hc08_ret2
	sta	18,s
	lda	*___SDCC_hc08_ret3
	sta	17,s
	ais	#8
	lda	(_configPage1 + 0x0003)
	psha
	pulh
	ldx	((_configPage1 + 0x0003) + 1)
	stx	8,s
	pshh
	pula
	sta	7,s
	clra
	sta	6,s
	sta	5,s
	tsx
	lda	11,x
	add	7,x
	sta	11,x
	lda	10,x
	adc	6,x
	sta	10,x
	lda	9,x
	adc	5,x
	sta	9,x
	lda	8,x
	adc	4,x
	sta	8,x
	lda	8,x
	sta	,x
	lda	9,x
	sta	1,x
	lda	10,x
	sta	2,x
	lda	11,x
	sta	3,x
;fuel.c:31: if (pw < INJ_MIN_PW) pw = INJ_MIN_PW;
	lda	11,x
	sub	#0xf4
	lda	10,x
	sbc	#0x01
	lda	9,x
	sbc	#0x00
	lda	8,x
	sbc	#0x00
	bcc	00102$
	clra
	sta	,x
	sta	1,x
	inca
	sta	2,x
	lda	#0xf4
	sta	3,x
00102$:
;fuel.c:32: if (pw > INJ_MAX_PW) pw = INJ_MAX_PW;
	tsx
	lda	#0x20
	sub	3,x
	lda	#0x4e
	sbc	2,x
	clra
	sbc	1,x
	clra
	sbc	,x
	bcc	00104$
	clra
	sta	,x
	sta	1,x
	lda	#0x4e
	sta	2,x
	lda	#0x20
	sta	3,x
00104$:
;fuel.c:34: currentStatus.PW1 = (uint16_t)pw;
	lda	4,s
	ldx	3,s
	stx	(_currentStatus + 0x001c)
	sta	((_currentStatus + 0x001c) + 1)
;fuel.c:35: currentStatus.PW2 = (uint16_t)pw;
	stx	(_currentStatus + 0x001e)
	sta	((_currentStatus + 0x001e) + 1)
;fuel.c:36: currentStatus.PW3 = (uint16_t)pw;
	stx	(_currentStatus + 0x0020)
	sta	((_currentStatus + 0x0020) + 1)
;fuel.c:38: return (uint16_t)pw;
;fuel.c:39: }
	ais	#14
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'getVE'
;------------------------------------------------------------
;ve                        Allocated to registers a x 
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;fuel.c:41: uint8_t getVE(void) {
;	-----------------------------------------
;	 function getVE
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_getVE:
	ais	#-2
;fuel.c:42: int16_t ve = getTableValue(&veTable, currentStatus.MAP, currentStatus.RPM);
	lda	_currentStatus
	psha
	pulh
	ldx	(_currentStatus + 1)
	lda	(_currentStatus + 0x0013)
	pshx
	pshh
	psha
	lda	#_veTable
	ldx	#>_veTable
	jsr	_getTableValue
	ais	#3
;fuel.c:43: if (ve < 0) ve = 0;
	sta	2,s
	stx	1,s
	psha
	lda	2,s
	sub	#0x00
	pula
	bge	00102$
	clrx
	txa
00102$:
;fuel.c:44: if (ve > 255) ve = 255;
	sta	2,s
	stx	1,s
	psha
	lda	#0xff
	sub	3,s
	clra
	sbc	2,s
	pula
	bge	00104$
	clrx
	lda	#0xff
00104$:
;fuel.c:45: return (uint8_t)ve;
;fuel.c:46: }
	ais	#2
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'calculateCorrections'
;------------------------------------------------------------
;total                     Allocated to registers x h 
;wue                       Allocated to registers a 
;ase                       Allocated to registers h 
;clt                       Allocated to registers h 
;bat                       Allocated to registers a 
;ae                        Allocated to registers a 
;sloc0                     Allocated to stack - sp +5
;sloc1                     Allocated to stack - sp +1
;------------------------------------------------------------
;fuel.c:48: uint16_t calculateCorrections(void) {
;	-----------------------------------------
;	 function calculateCorrections
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 8 bytes.
_calculateCorrections:
	ais	#-8
;fuel.c:52: wue = correctionWUE();
	jsr	_correctionWUE
;fuel.c:53: currentStatus.wueCorrection = wue;
	sta	(_currentStatus + 0x0028)
;fuel.c:54: total = (uint16_t)PERCENT(total, wue);
	tsx
	sta	7,x
	clrx
	stx	7,s
	stx	6,s
	stx	5,s
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	lda	#0x64
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
	lda	#0x64
	psha
	clra
	psha
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
	lda	8,s
	ldx	7,s
;fuel.c:56: ase = correctionASE();
	psha
	pshx
	jsr	_correctionASE
	psha
	pulh
	pulx
	pula
;fuel.c:57: total = (uint16_t)PERCENT(total, ase);
	sta	8,s
	stx	7,s
	psha
	clra
	sta	7,s
	clra
	sta	6,s
	pula
	pshh
	pula
	sta	4,s
	clra
	sta	3,s
	sta	2,s
	sta	1,s
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
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#8
	lda	#0x64
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
	lda	4,s
	ldx	3,s
;fuel.c:59: clt = correctionCLT();
	psha
	pshx
	jsr	_correctionCLT
	psha
	pulh
	pulx
	pula
;fuel.c:60: total = (uint16_t)PERCENT(total, clt);
	sta	4,s
	stx	3,s
	psha
	clra
	sta	3,s
	clra
	sta	2,s
	pula
	pshh
	pula
	sta	8,s
	clra
	sta	7,s
	sta	6,s
	sta	5,s
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
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#8
	lda	#0x64
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
	ldx	4,s
	lda	3,s
	psha
	pulh
;fuel.c:62: bat = correctionBattery();
	pshx
	pshh
	jsr	_correctionBattery
	pulh
	pulx
;fuel.c:63: currentStatus.batCorrection = bat;
	sta	(_currentStatus + 0x0029)
;fuel.c:64: total = (uint16_t)PERCENT(total, bat);
	stx	4,s
	psha
	pshh
	pula
	sta	4,s
	clra
	sta	3,s
	clra
	sta	2,s
	pula
	tsx
	sta	7,x
	clrx
	stx	7,s
	stx	6,s
	stx	5,s
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
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#8
	lda	#0x64
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
	lda	3,x
	sta	1,x
	lda	2,x
	sta	,x
;fuel.c:66: ae = correctionAE();
	jsr	_correctionAE
;fuel.c:67: total += ae;
	tax
	clrh
	lda	2,s
	sta	2,s
	lda	1,s
	sta	1,s
	txa
	add	2,s
	psha
	pshh
	pula
	adc	2,s
	tax
	pula
;fuel.c:69: if (total < CORR_MIN) total = CORR_MIN;
	sta	2,s
	stx	1,s
	psha
	lda	3,s
	sub	#0x32
	lda	2,s
	sbc	#0x00
	pula
	bcc	00102$
	clrx
	lda	#0x32
00102$:
;fuel.c:70: if (total > CORR_MAX) total = CORR_MAX;
	sta	2,s
	stx	1,s
	psha
	lda	#0xc8
	sub	3,s
	clra
	sbc	2,s
	pula
	bcc	00104$
	clrx
	lda	#0xc8
00104$:
;fuel.c:72: return total;
;fuel.c:73: }
	ais	#8
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'correctionWUE'
;------------------------------------------------------------
;temp                      Allocated to stack - sp +22
;i                         Allocated to stack - sp +18
;t1                        Allocated to registers a 
;t2                        Allocated to stack - sp +21
;v1                        Allocated to stack - sp +20
;v2                        Allocated to stack - sp +19
;sloc0                     Allocated to stack - sp +10
;sloc1                     Allocated to stack - sp +11
;sloc2                     Allocated to stack - sp +13
;sloc3                     Allocated to stack - sp +3
;sloc4                     Allocated to stack - sp +1
;sloc5                     Allocated to stack - sp +6
;sloc6                     Allocated to stack - sp +4
;sloc7                     Allocated to stack - sp +14
;------------------------------------------------------------
;fuel.c:75: uint8_t correctionWUE(void) {
;	-----------------------------------------
;	 function correctionWUE
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 22 bytes.
_correctionWUE:
	ais	#-22
;fuel.c:76: int8_t temp = currentStatus.coolant;
	lda	(_currentStatus + 0x0015)
	sta	22,s
;fuel.c:79: if (!BIT_CHECK(currentStatus.engineStatus, ENGINE_WARMUP)) {
	lda	(_currentStatus + 0x002a)
	bit	#0x08
	bne	00102$
;fuel.c:80: return 100;
	lda	#0x64
	jmp	00111$
00102$:
;fuel.c:83: for (i = 0; i < 5; i++) {
	tsx
	clra
	sta	9,x
	sta	17,x
00109$:
;fuel.c:84: if (temp >= configPage1.wueBins[i] && temp < configPage1.wueBins[i + 1]) {
	tsx
	lda	21,x
	sta	11,x
	rola	
	clra	
	sbc	#0x00
	sta	10,x
	ldx	17,x
	clrh
	lda	((_configPage1 + 0x000b)),x
	clrx
	psha
	lda	13,s
	sub	1, s
	pula
	lda	11,s
	pshx
	sbc	1,s
	ais	#1
	bge	00144$
	jmp	00110$
00144$:
	tsx
	lda	17,x
	add	#0x01
	sta	12,x
	ldx	12,x
	clrh
	lda	((_configPage1 + 0x000b)),x
	sta	3,s
	lda	3,s
	clrx
	psha
	lda	13,s
	sub	1, s
	pula
	lda	11,s
	pshx
	sbc	1,s
	ais	#1
	blt	00145$
	jmp	00110$
00145$:
;fuel.c:85: int8_t t1 = configPage1.wueBins[i];
	ldx	10,s
	lda	((_configPage1 + 0x000b)),x
;fuel.c:86: int8_t t2 = configPage1.wueBins[i + 1];
	tsx
	ldx	2,x
	stx	21,s
;fuel.c:87: uint8_t v1 = configPage1.wueValues[i];
	ldx	10,s
	clrh
	ldx	((_configPage1 + 0x0011)),x
	stx	20,s
;fuel.c:88: uint8_t v2 = configPage1.wueValues[i + 1];
	ldx	13,s
	ldx	((_configPage1 + 0x0011)),x
	stx	19,s
;fuel.c:89: return (uint8_t)(v1 + (int32_t)(temp - t1) * (v2 - v1) / (t2 - t1));
	tsx
	sta	1,x
	rola	
	clra	
	sbc	#0x00
	sta	,x
	lda	11,x
	sub	1,x
	psha
	lda	10,x
	sbc	,x
	tax
	pula
	sta	9,s
	txa
	sta	8,s
	rola	
	clra	
	sbc	#0x00
	sta	7,s
	sta	6,s
	ldx	19,s
	clrh
	lda	20,s
	sta	5,s
	clra
	sta	4,s
	txa
	sub	5,s
	psha
	pshh
	pula
	sbc	5,s
	tax
	pula
	sta	17,s
	txa
	sta	16,s
	rola	
	clra	
	sbc	#0x00
	sta	15,s
	sta	14,s
	tsx
	lda	16,x
	psha
	lda	15,x
	psha
	lda	14,x
	psha
	lda	13,x
	psha
	lda	8,x
	psha
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	jsr	__mullong
	sta	25,s
	stx	24,s
	lda	*___SDCC_hc08_ret2
	sta	23,s
	lda	*___SDCC_hc08_ret3
	sta	22,s
	ais	#8
	lda	21,s
	psha
	rola	
	clra	
	sbc	#0x00
	tax
	pula
	sub	2,s
	psha
	txa
	sbc	2,s
	tax
	pula
	sta	9,s
	txa
	sta	8,s
	rola	
	clra	
	sbc	#0x00
	sta	7,s
	sta	6,s
	tsx
	lda	8,x
	psha
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	16,x
	psha
	lda	15,x
	psha
	lda	14,x
	psha
	lda	13,x
	psha
	jsr	__divslong
	sta	25,s
	stx	24,s
	lda	*___SDCC_hc08_ret2
	sta	23,s
	lda	*___SDCC_hc08_ret3
	sta	22,s
	ais	#8
	tsx
	lda	16,x
	sta	13,x
	lda	19,x
	sta	3,x
	lda	13,x
	add	3,x
	bra	00111$
00110$:
;fuel.c:83: for (i = 0; i < 5; i++) {
	tsx
	inc	17,x
	lda	17,x
	sta	9,x
	lda	17,x
	cmp	#0x05
	bcc	00146$
	jmp	00109$
00146$:
;fuel.c:93: if (temp < configPage1.wueBins[0]) {
	lda	(_configPage1 + 0x000b)
	clrx
	psha
	lda	13,s
	sub	1, s
	pula
	lda	11,s
	pshx
	sbc	1,s
	ais	#1
	bge	00108$
;fuel.c:94: return configPage1.wueValues[0];
	lda	(_configPage1 + 0x0011)
	bra	00111$
00108$:
;fuel.c:96: return configPage1.wueValues[5];
	lda	(_configPage1 + 0x0016)
00111$:
;fuel.c:97: }
	ais	#22
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'correctionASE'
;------------------------------------------------------------
;fuel.c:99: uint8_t correctionASE(void) {
;	-----------------------------------------
;	 function correctionASE
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_correctionASE:
;fuel.c:100: if (!BIT_CHECK(currentStatus.engineStatus, ENGINE_ASE)) {
	lda	(_currentStatus + 0x002a)
	bit	#0x04
	bne	00102$
;fuel.c:101: return 100;
	lda	#0x64
	rts
00102$:
;fuel.c:103: return aseValue;
	lda	_aseValue
;fuel.c:104: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'startASE'
;------------------------------------------------------------
;fuel.c:106: void startASE(void) {
;	-----------------------------------------
;	 function startASE
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_startASE:
;fuel.c:107: aseCounter = configPage1.aseCount;
	lda	(_configPage1 + 0x0018)
	sta	_aseCounter
;fuel.c:108: aseValue = configPage1.asePct;
	lda	(_configPage1 + 0x0017)
	sta	_aseValue
;fuel.c:109: BIT_SET(currentStatus.engineStatus, ENGINE_ASE);
	lda	(_currentStatus + 0x002a)
	ora	#0x04
	sta	(_currentStatus + 0x002a)
;fuel.c:110: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'decrementASE'
;------------------------------------------------------------
;step                      Allocated to registers a x 
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;fuel.c:112: void decrementASE(void) {
;	-----------------------------------------
;	 function decrementASE
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_decrementASE:
	ais	#-2
;fuel.c:113: if (aseCounter > 0) {
	lda	_aseCounter
	beq	00106$
;fuel.c:114: aseCounter--;
	ldhx	#_aseCounter
	dec	,x
;fuel.c:116: if (configPage1.aseCount > 0) {
	lda	(_configPage1 + 0x0018)
	beq	00108$
;fuel.c:117: uint16_t step = (uint16_t)(configPage1.asePct - 100) / configPage1.aseCount;
	ldx	(_configPage1 + 0x0017)
	clrh
	aix	#-100
	stx	2,s
	psha
	pshh
	pula
	sta	2,s
	pula
	clrx
	psha
	pshx
	tsx
	lda	3,x
	ldx	2,x
	jsr	__divuint
	ais	#2
;fuel.c:118: aseValue = (uint8_t)(aseValue - step);
	ldhx	#_aseValue
	sub	,x
	nega	
	sta	,x
;fuel.c:120: if (aseValue <= 100) {
	lda	_aseValue
	cmp	#0x64
	bhi	00108$
;fuel.c:121: aseValue = 100;
	lda	#0x64
	sta	_aseValue
;fuel.c:122: BIT_CLEAR(currentStatus.engineStatus, ENGINE_ASE);
	lda	(_currentStatus + 0x002a)
	and	#0xfb
	sta	(_currentStatus + 0x002a)
	bra	00108$
00106$:
;fuel.c:126: aseValue = 100;
	lda	#0x64
	sta	_aseValue
;fuel.c:127: BIT_CLEAR(currentStatus.engineStatus, ENGINE_ASE);
	lda	(_currentStatus + 0x002a)
	and	#0xfb
	sta	(_currentStatus + 0x002a)
00108$:
;fuel.c:129: }
	ais	#2
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'correctionAE'
;------------------------------------------------------------
;ae                        Allocated to stack - sp +3
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;fuel.c:131: uint8_t correctionAE(void) {
;	-----------------------------------------
;	 function correctionAE
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 3 bytes.
_correctionAE:
	ais	#-3
;fuel.c:132: if (configPage1.aeMode != AE_MODE_TPS) {
	lda	(_configPage1 + 0x0019)
	beq	00102$
;fuel.c:133: return 0;
	clra
	bra	00107$
00102$:
;fuel.c:136: if (currentStatus.TPSdot > configPage1.aeThresh) {
	lda	(_currentStatus + 0x003a)
	sta	1,s
	lda	((_currentStatus + 0x003a) + 1)
	sta	2,s
	ldx	(_configPage1 + 0x001a)
	clrh
;fuel.c:138: BIT_SET(currentStatus.engineStatus, ENGINE_ACC);
	lda	(_currentStatus + 0x002a)
;fuel.c:136: if (currentStatus.TPSdot > configPage1.aeThresh) {
	psha
	txa
	sub	3,s
	pshh
	pula
	sbc	2,s
	pula
	bge	00106$
;fuel.c:138: BIT_SET(currentStatus.engineStatus, ENGINE_ACC);
	ora	#0x10
	sta	(_currentStatus + 0x002a)
;fuel.c:140: ae = (uint8_t)(configPage1.aePct - 100);
	lda	(_configPage1 + 0x001b)
	sub	#0x64
	sta	3,s
;fuel.c:142: if (currentStatus.TPSdot > ((int16_t)configPage1.aeThresh * 3)) {
	lda	(_currentStatus + 0x003a)
	sta	1,s
	lda	((_currentStatus + 0x003a) + 1)
	sta	2,s
	lda	(_configPage1 + 0x001a)
	clrx
	psha
	pshx
	lda	#0x03
	jsr	__mulint
	ais	#2
	sub	2,s
	txa
	sbc	1,s
	bge	00104$
;fuel.c:143: ae = (uint8_t)(ae * 2);
	tsx
	lda	2,x
	lsla	
	sta	2,x
00104$:
;fuel.c:146: return ae;
	lda	3,s
	bra	00107$
00106$:
;fuel.c:149: BIT_CLEAR(currentStatus.engineStatus, ENGINE_ACC);
	and	#0xef
	sta	(_currentStatus + 0x002a)
;fuel.c:150: return 0;
	clra
00107$:
;fuel.c:151: }
	ais	#3
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'correctionCLT'
;------------------------------------------------------------
;reduction                 Allocated to registers a 
;------------------------------------------------------------
;fuel.c:153: uint8_t correctionCLT(void) {
;	-----------------------------------------
;	 function correctionCLT
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_correctionCLT:
;fuel.c:154: if (currentStatus.coolant > 100) {
	lda	(_currentStatus + 0x0015)
	cmp	#0x64
	ble	00104$
;fuel.c:155: int8_t reduction = (int8_t)((currentStatus.coolant - 100) / 5);
	tax
	rola	
	clra	
	sbc	#0x00
	psha
	pulh
	aix	#-100
	lda	#0x05
	psha
	clra
	psha
	txa
	pshh
	pulx
	jsr	__divsint
	ais	#2
;fuel.c:156: if (reduction > 5) reduction = 5;
	cmp	#0x05
	ble	00102$
	lda	#0x05
00102$:
;fuel.c:157: return (uint8_t)(100 - reduction);
	sub	#0x64
	nega	
	rts
00104$:
;fuel.c:159: return 100;
	lda	#0x64
;fuel.c:160: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'correctionBattery'
;------------------------------------------------------------
;voltage                   Allocated to registers a 
;------------------------------------------------------------
;fuel.c:162: uint8_t correctionBattery(void) {
;	-----------------------------------------
;	 function correctionBattery
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_correctionBattery:
;fuel.c:163: uint8_t voltage = currentStatus.battery10;
	lda	(_currentStatus + 0x0019)
;fuel.c:165: if (voltage < 110) {
	cmp	#0x6e
	bcc	00107$
;fuel.c:166: return 110;
	lda	#0x6e
	rts
00107$:
;fuel.c:167: } else if (voltage < 120) {
	cmp	#0x78
	bcc	00104$
;fuel.c:168: return 105;
	lda	#0x69
	rts
00104$:
;fuel.c:169: } else if (voltage > 150) {
	cmp	#0x96
	bls	00108$
;fuel.c:170: return 97;
	lda	#0x61
	rts
00108$:
;fuel.c:172: return 100;
	lda	#0x64
;fuel.c:173: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'updateEngineStatus'
;------------------------------------------------------------
;sloc0                     Allocated to stack - sp +1
;firstRun                  Allocated with name '_updateEngineStatus_firstRun_65536_62'
;------------------------------------------------------------
;fuel.c:175: void updateEngineStatus(void) {
;	-----------------------------------------
;	 function updateEngineStatus
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_updateEngineStatus:
	ais	#-2
;fuel.c:178: if (currentStatus.RPM > 0 && currentStatus.RPM < ((uint16_t)configPage1.crankRPM * 10)) {
	ldx	_currentStatus
	lda	(_currentStatus + 1)
	sta	2,s
	stx	1,s
	tsta
	bne	00140$
	tstx
00140$:
	beq	00107$
	lda	(_configPage1 + 0x001d)
	clrx
	psha
	pshx
	lda	#0x0a
	jsr	__mulint
	ais	#2
	psha
	lda	3,s
	sub	1, s
	pula
	lda	1,s
	pshx
	sbc	1,s
	ais	#1
	bcc	00107$
;fuel.c:179: BIT_SET(currentStatus.engineStatus, ENGINE_CRANK);
	lda	(_currentStatus + 0x002a)
	ora	#0x01
	sta	(_currentStatus + 0x002a)
;fuel.c:180: BIT_CLEAR(currentStatus.engineStatus, ENGINE_RUN);
	and	#0xfd
	sta	(_currentStatus + 0x002a)
	bra	00108$
00107$:
;fuel.c:181: } else if (currentStatus.RPM >= ((uint16_t)configPage1.crankRPM * 10)) {
	lda	(_configPage1 + 0x001d)
	clrx
	psha
	pshx
	lda	#0x0a
	jsr	__mulint
	ais	#2
	psha
	lda	3,s
	sub	1, s
	pula
	lda	1,s
	pshx
	sbc	1,s
	ais	#1
	bcs	00104$
;fuel.c:182: BIT_CLEAR(currentStatus.engineStatus, ENGINE_CRANK);
	lda	(_currentStatus + 0x002a)
	and	#0xfe
	sta	(_currentStatus + 0x002a)
;fuel.c:183: BIT_SET(currentStatus.engineStatus, ENGINE_RUN);
	ora	#0x02
	sta	(_currentStatus + 0x002a)
;fuel.c:185: if (firstRun) {
	lda	_updateEngineStatus_firstRun_65536_62
	beq	00108$
;fuel.c:186: startASE();
	jsr	_startASE
;fuel.c:187: firstRun = false;
	clra
	sta	_updateEngineStatus_firstRun_65536_62
	bra	00108$
00104$:
;fuel.c:190: BIT_CLEAR(currentStatus.engineStatus, ENGINE_CRANK);
	lda	(_currentStatus + 0x002a)
	and	#0xfe
	sta	(_currentStatus + 0x002a)
;fuel.c:191: BIT_CLEAR(currentStatus.engineStatus, ENGINE_RUN);
	and	#0xfd
	sta	(_currentStatus + 0x002a)
00108$:
;fuel.c:194: if (currentStatus.coolant < 60) {
	ldx	(_currentStatus + 0x0015)
;fuel.c:195: BIT_SET(currentStatus.engineStatus, ENGINE_WARMUP);
	lda	(_currentStatus + 0x002a)
;fuel.c:194: if (currentStatus.coolant < 60) {
	cpx	#0x3c
	bge	00111$
;fuel.c:195: BIT_SET(currentStatus.engineStatus, ENGINE_WARMUP);
	ora	#0x08
	sta	(_currentStatus + 0x002a)
	bra	00113$
00111$:
;fuel.c:197: BIT_CLEAR(currentStatus.engineStatus, ENGINE_WARMUP);
	and	#0xf7
	sta	(_currentStatus + 0x002a)
00113$:
;fuel.c:199: }
	ais	#2
	rts
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
__xinit__aseCounter:
	.db #0x00	; 0
__xinit__aseValue:
	.db #0x64	; 100	'd'
	.area CABS    (ABS,CODE)
