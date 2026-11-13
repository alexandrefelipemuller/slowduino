;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.2.0 #13081 (Linux)
;--------------------------------------------------------
	.module ignition
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
	.globl _lookupCurveI8
	.globl _getTableValue
	.globl _calculateAdvance
	.globl _getBaseAdvance
	.globl _applyAdvanceCorrections
	.globl _isIdleAdvanceActive
	.globl _correctionCLTAdvance
	.globl _correctionIdleAdvance
	.globl _applyRevLimiter
	.globl _calculateDwell
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
_applyRevLimiter_cutState_131072_43:
	.ds 1
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'applyRevLimiter'
;------------------------------------------------------------
;advance                   Allocated to registers h 
;limitRPM                  Allocated to stack - sp +0
;cutState                  Allocated with name '_applyRevLimiter_cutState_131072_43'
;------------------------------------------------------------
;ignition.c:91: static bool cutState = false;
	clra
	sta	_applyRevLimiter_cutState_131072_43
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
;sloc0                     Allocated to stack - sp +5
;sloc1                     Allocated to stack - sp +1
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
	sta	8,s
	txa
	sta	7,s
	rola	
	clra	
	sbc	#0x00
	sta	6,s
	sta	5,s
	lda	18,s
	sub	16,s
	psha
	lda	18,s
	sbc	16,s
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
	jsr	__mullong
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#8
	lda	14,s
	sub	12,s
	psha
	lda	14,s
	sbc	12,s
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
	jsr	__divslong
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#8
	lda	4,s
	ldx	3,s
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
;Allocation info for local variables in function 'calculateAdvance'
;------------------------------------------------------------
;advance                   Allocated to registers a 
;------------------------------------------------------------
;ignition.c:11: int8_t calculateAdvance(void) {
;	-----------------------------------------
;	 function calculateAdvance
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_calculateAdvance:
;ignition.c:14: if (BIT_CHECK(currentStatus.engineStatus, ENGINE_CRANK)) {
	lda	(_currentStatus + 0x002a)
	bit	#0x01
	beq	00102$
;ignition.c:15: return configPage2.crankAdvance;
	lda	(_configPage2 + 0x0009)
	rts
00102$:
;ignition.c:18: advance = getBaseAdvance();
	jsr	_getBaseAdvance
;ignition.c:19: advance = applyAdvanceCorrections(advance);
	jsr	_applyAdvanceCorrections
;ignition.c:20: advance = applyRevLimiter(advance);
	jsr	_applyRevLimiter
;ignition.c:22: if (advance < IGN_MIN_ADVANCE) advance = IGN_MIN_ADVANCE;
	cmp	#0xf6
	bge	00104$
	lda	#0xf6
00104$:
;ignition.c:23: if (advance > IGN_MAX_ADVANCE) advance = IGN_MAX_ADVANCE;
	cmp	#0x2d
	ble	00106$
	lda	#0x2d
00106$:
;ignition.c:25: return advance;
;ignition.c:26: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'getBaseAdvance'
;------------------------------------------------------------
;advance                   Allocated to registers a x 
;------------------------------------------------------------
;ignition.c:28: int8_t getBaseAdvance(void) {
;	-----------------------------------------
;	 function getBaseAdvance
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_getBaseAdvance:
;ignition.c:29: int16_t advance = getTableValue(&ignTable, currentStatus.MAP, currentStatus.RPM);
	lda	_currentStatus
	psha
	pulh
	ldx	(_currentStatus + 1)
	lda	(_currentStatus + 0x0013)
	pshx
	pshh
	psha
	lda	#_ignTable
	ldx	#>_ignTable
	jsr	_getTableValue
	ais	#3
;ignition.c:30: return (int8_t)advance;
;ignition.c:31: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'applyAdvanceCorrections'
;------------------------------------------------------------
;baseAdvance               Allocated to stack - sp +2
;corrected                 Allocated to registers a 
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;ignition.c:33: int8_t applyAdvanceCorrections(int8_t baseAdvance) {
;	-----------------------------------------
;	 function applyAdvanceCorrections
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_applyAdvanceCorrections:
	psha
	pshh
;ignition.c:36: corrected = (int8_t)(corrected + correctionCLTAdvance());
	jsr	_correctionCLTAdvance
	tsx
	add	1,x
;ignition.c:38: if (isIdleAdvanceActive()) {
	psha
	jsr	_isIdleAdvanceActive
	tax
	pula
	tstx
	beq	00105$
;ignition.c:39: if (configPage2.idleAdvEnabled == IDLE_ADV_SWITCHED) {
	ldx	(_configPage2 + 0x0015)
	cpx	#0x02
	bne	00102$
;ignition.c:40: corrected = correctionIdleAdvance();
	jsr	_correctionIdleAdvance
	bra	00105$
00102$:
;ignition.c:42: corrected = (int8_t)(corrected + correctionIdleAdvance());
	psha
	jsr	_correctionIdleAdvance
	tsx
	sta	1,x
	pula
	add	1,x
00105$:
;ignition.c:46: return corrected;
;ignition.c:47: }
	ais	#2
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'isIdleAdvanceActive'
;------------------------------------------------------------
;sloc0                     Allocated to stack - sp +3
;sloc1                     Allocated to stack - sp +1
;------------------------------------------------------------
;ignition.c:49: bool isIdleAdvanceActive(void) {
;	-----------------------------------------
;	 function isIdleAdvanceActive
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 3 bytes.
_isIdleAdvanceActive:
	ais	#-3
;ignition.c:50: if (configPage2.idleAdvEnabled == IDLE_ADV_OFF) return false;
	lda	(_configPage2 + 0x0015)
	bne	00102$
	clra
	bra	00109$
00102$:
;ignition.c:51: if (currentStatus.RPM == 0) return false;
	ldx	_currentStatus
	lda	(_currentStatus + 1)
	bne	00132$
	tstx
00132$:
	bne	00104$
	clra
	bra	00109$
00104$:
;ignition.c:53: if (currentStatus.TPS > configPage2.idleAdvTPS) return false;
	lda	(_currentStatus + 0x0014)
	ldx	(_configPage2 + 0x0016)
	stx	3,s
	cmp	3,s
	bls	00106$
	clra
	bra	00109$
00106$:
;ignition.c:54: if (currentStatus.RPM > ((uint16_t)configPage2.idleAdvRPM * 100U)) return false;
	lda	_currentStatus
	sta	1,s
	lda	(_currentStatus + 1)
	sta	2,s
	lda	(_configPage2 + 0x0017)
	clrx
	psha
	pshx
	lda	#0x64
	jsr	__mulint
	ais	#2
	sub	2,s
	txa
	sbc	1,s
	bcc	00108$
	clra
	bra	00109$
00108$:
;ignition.c:56: return true;
	lda	#0x01
00109$:
;ignition.c:57: }
	ais	#3
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'correctionCLTAdvance'
;------------------------------------------------------------
;temp                      Allocated to stack - sp +19
;i                         Allocated to stack - sp +15
;t1                        Allocated to registers a 
;t2                        Allocated to stack - sp +18
;v1                        Allocated to stack - sp +17
;v2                        Allocated to stack - sp +16
;sloc0                     Allocated to stack - sp +15
;sloc1                     Allocated to stack - sp +5
;sloc2                     Allocated to stack - sp +12
;sloc3                     Allocated to stack - sp +13
;sloc4                     Allocated to stack - sp +8
;sloc5                     Allocated to stack - sp +6
;sloc6                     Allocated to stack - sp +1
;------------------------------------------------------------
;ignition.c:59: int8_t correctionCLTAdvance(void) {
;	-----------------------------------------
;	 function correctionCLTAdvance
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 19 bytes.
_correctionCLTAdvance:
	ais	#-19
;ignition.c:60: int8_t temp = currentStatus.coolant;
	lda	(_currentStatus + 0x0015)
	sta	19,s
;ignition.c:63: for (i = 0; i < 3; i++) {
	clra
	sta	15,s
00107$:
;ignition.c:64: if (temp >= configPage2.cltAdvBins[i] && temp < configPage2.cltAdvBins[i + 1]) {
	tax
	clrh
	ldx	((_configPage2 + 0x000b)),x
	cpx	19,s
	ble	00136$
	jmp	00108$
00136$:
	tax
	aix	#1
	stx	5,s
	ldx	5,s
	ldx	((_configPage2 + 0x000b)),x
	stx	12,s
	tsx
	psha
	lda	18,x
	cmp	11,x
	pula
	blt	00137$
	jmp	00108$
00137$:
;ignition.c:65: int8_t t1 = configPage2.cltAdvBins[i];
	ldx	14,x
	clrh
	lda	((_configPage2 + 0x000b)),x
;ignition.c:66: int8_t t2 = configPage2.cltAdvBins[i + 1];
	tsx
	ldx	11,x
	stx	18,s
;ignition.c:67: int8_t v1 = configPage2.cltAdvValues[i];
	ldx	15,s
	clrh
	ldx	((_configPage2 + 0x000f)),x
	stx	17,s
;ignition.c:68: int8_t v2 = configPage2.cltAdvValues[i + 1];
	ldx	5,s
	ldx	((_configPage2 + 0x000f)),x
	stx	16,s
;ignition.c:70: return (int8_t)(v1 + (int32_t)(temp - t1) * (v2 - v1) / (t2 - t1));
	ldx	19,s
	psha
	lda	20,s
	rola	
	clra	
	sbc	#0x00
	psha
	pulh
	pula
	sta	14,s
	rola	
	clra	
	sbc	#0x00
	sta	13,s
	txa
	sub	14,s
	psha
	pshh
	pula
	sbc	14,s
	tax
	pula
	sta	11,s
	txa
	sta	10,s
	rola	
	clra	
	sbc	#0x00
	sta	9,s
	sta	8,s
	lda	16,s
	psha
	rola	
	clra	
	sbc	#0x00
	tax
	lda	18,s
	sta	8,s
	rola	
	clra	
	sbc	#0x00
	sta	7,s
	pula
	sub	7,s
	psha
	txa
	sbc	7,s
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
	lda	10,x
	psha
	lda	9,x
	psha
	lda	8,x
	psha
	lda	7,x
	psha
	jsr	__mullong
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#8
	lda	18,s
	psha
	rola	
	clra	
	sbc	#0x00
	tax
	pula
	sub	14,s
	psha
	txa
	sbc	14,s
	tax
	pula
	sta	11,s
	txa
	sta	10,s
	rola	
	clra	
	sbc	#0x00
	sta	9,s
	sta	8,s
	tsx
	lda	10,x
	psha
	lda	9,x
	psha
	lda	8,x
	psha
	lda	7,x
	psha
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	jsr	__divslong
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#8
	tsx
	lda	3,x
	add	16,x
	bra	00109$
00108$:
;ignition.c:63: for (i = 0; i < 3; i++) {
	inca
	sta	15,s
	cmp	#0x03
	bcc	00138$
	jmp	00107$
00138$:
;ignition.c:74: if (temp < configPage2.cltAdvBins[0]) {
	lda	(_configPage2 + 0x000b)
	cmp	19,s
	ble	00106$
;ignition.c:75: return configPage2.cltAdvValues[0];
	lda	(_configPage2 + 0x000f)
	bra	00109$
00106$:
;ignition.c:77: return configPage2.cltAdvValues[3];
	lda	(_configPage2 + 0x0012)
00109$:
;ignition.c:78: }
	ais	#19
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'correctionIdleAdvance'
;------------------------------------------------------------
;delta                     Allocated to registers x h 
;sloc0                     Allocated to stack - sp +3
;sloc1                     Allocated to stack - sp +1
;------------------------------------------------------------
;ignition.c:80: int8_t correctionIdleAdvance(void) {
;	-----------------------------------------
;	 function correctionIdleAdvance
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 4 bytes.
_correctionIdleAdvance:
	ais	#-4
;ignition.c:81: int16_t delta = (int16_t)currentStatus.CLIdleTarget - (int16_t)currentStatus.RPM;
	ldx	(_currentStatus + 0x002f)
	lda	((_currentStatus + 0x002f) + 1)
	sta	4,s
	stx	3,s
	ldx	_currentStatus
	lda	(_currentStatus + 1)
	sta	2,s
	stx	1,s
	lda	4,s
	sub	2,s
	tax
	lda	3,s
	sbc	1,s
	psha
	pulh
;ignition.c:82: if (delta < 0) delta = 0;
	stx	2,s
	pshh
	pula
	sta	1,s
	lda	1,s
	sub	#0x00
	bge	00102$
	clrh
	clrx
00102$:
;ignition.c:84: return lookupCurveI8(configPage2.idleAdvBins, configPage2.idleAdvValues, 4, (int16_t)(delta / 10));
	lda	#0x0a
	psha
	clra
	psha
	txa
	pshh
	pulx
	jsr	__divsint
	ais	#2
	psha
	pshx
	lda	#0x04
	psha
	lda	#(_configPage2 + 0x001c)
	psha
	lda	#>(_configPage2 + 0x001c)
	psha
	lda	#(_configPage2 + 0x0018)
	ldx	#>(_configPage2 + 0x0018)
	jsr	_lookupCurveI8
	ais	#5
;ignition.c:85: }
	ais	#4
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'applyRevLimiter'
;------------------------------------------------------------
;advance                   Allocated to registers h 
;limitRPM                  Allocated to stack - sp +1
;cutState                  Allocated with name '_applyRevLimiter_cutState_131072_43'
;------------------------------------------------------------
;ignition.c:87: int8_t applyRevLimiter(int8_t advance) {
;	-----------------------------------------
;	 function applyRevLimiter
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_applyRevLimiter:
	ais	#-2
	psha
	pulh
;ignition.c:88: uint16_t limitRPM = (uint16_t)configPage2.revLimitRPM * 100;
	lda	(_configPage2 + 0x000a)
	clrx
	pshh
	psha
	pshx
	lda	#0x64
	jsr	__mulint
	ais	#2
	pulh
	sta	2,s
	stx	1,s
;ignition.c:90: if (currentStatus.RPM >= limitRPM) {
	ldx	_currentStatus
	lda	(_currentStatus + 1)
	sub	2,s
	txa
	sbc	1,s
	bcs	00104$
;ignition.c:92: cutState = !cutState;
	lda	_applyRevLimiter_cutState_131072_43
	eor	#0x01
	sta	_applyRevLimiter_cutState_131072_43
;ignition.c:94: if (cutState) {
	lda	_applyRevLimiter_cutState_131072_43
	beq	00104$
;ignition.c:95: return IGN_MIN_ADVANCE;
	lda	#0xf6
	bra	00105$
00104$:
;ignition.c:99: return advance;
	pshh
	pula
00105$:
;ignition.c:100: }
	ais	#2
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'calculateDwell'
;------------------------------------------------------------
;dwell                     Allocated to stack - sp +1
;------------------------------------------------------------
;ignition.c:102: uint16_t calculateDwell(void) {
;	-----------------------------------------
;	 function calculateDwell
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_calculateDwell:
	ais	#-2
;ignition.c:105: if (BIT_CHECK(currentStatus.engineStatus, ENGINE_CRANK)) {
	lda	(_currentStatus + 0x002a)
	bit	#0x01
	beq	00102$
;ignition.c:106: dwell = configPage2.dwellCrank;
	lda	(_configPage2 + 0x0005)
	sta	1,s
	lda	((_configPage2 + 0x0005) + 1)
	sta	2,s
	bra	00103$
00102$:
;ignition.c:108: dwell = configPage2.dwellRun;
	lda	(_configPage2 + 0x0003)
	sta	1,s
	lda	((_configPage2 + 0x0003) + 1)
	sta	2,s
00103$:
;ignition.c:111: if (dwell > configPage2.dwellLimit) {
	ldx	(_configPage2 + 0x0007)
	lda	((_configPage2 + 0x0007) + 1)
	psha
	sub	3,s
	txa
	sbc	2,s
	pula
	bcc	00105$
;ignition.c:112: dwell = configPage2.dwellLimit;
	stx	1,s
	sta	2,s
00105$:
;ignition.c:115: if (dwell < DWELL_MIN) dwell = DWELL_MIN;
	lda	2,s
	ldx	1,s
	sub	#0xe8
	txa
	sbc	#0x03
	bcc	00107$
	tsx
	lda	#0x03
	sta	,x
	lda	#0xe8
	sta	1,x
00107$:
;ignition.c:116: if (dwell > DWELL_MAX) dwell = DWELL_MAX;
	pulh
	pulx
	pshx
	pshh
	cphx	#0x1f40
	bls	00109$
	tsx
	lda	#0x1f
	sta	,x
	lda	#0x40
	sta	1,x
00109$:
;ignition.c:118: return dwell;
	tsx
	ldx	,x
	lda	2,s
;ignition.c:119: }
	ais	#2
	rts
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
