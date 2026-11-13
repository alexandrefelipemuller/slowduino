;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.2.0 #13081 (Linux)
;--------------------------------------------------------
	.module main
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
	.area	CODEIVT (ABS)
	.org	0xfffe
	.dw	__sdcc_gs_init_startup

	.area GSINIT0
__sdcc_gs_init_startup:
	ldhx	#0x0240
	txs
	jsr	__sdcc_external_startup
	beq	__sdcc_init_data
	jmp	__sdcc_program_startup
__sdcc_init_data:
; _hc08_genXINIT() start
        ldhx #0
00001$:
        cphx #l_XINIT
        beq  00002$
        lda  s_XINIT,x
        sta  s_XISEG,x
        aix  #1
        bra  00001$
00002$:
; _hc08_genXINIT() end
	.area GSFINAL
	jmp	__sdcc_program_startup

	.area CSEG
__sdcc_program_startup:
	jsr	_main
	bra	.
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _commsProcess
	.globl _commsInit
	.globl _calculateDwell
	.globl _calculateAdvance
	.globl _updateEngineStatus
	.globl _calculateInjection
	.globl _initTables
	.globl _micros
	.globl _timebaseInit
	.globl _checkSyncLoss
	.globl _calculateRPM
	.globl _triggerInit
	.globl _processInjectorPolling
	.globl _schedulerInit
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
_main_lastLoop67Hz_196608_76:
	.ds 4
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;now                       Allocated to stack - sp +2
;newPW1                    Allocated to stack - sp +4
;newAdvance                Allocated to stack - sp +3
;newDwell                  Allocated to registers x h 
;sloc0                     Allocated to stack - sp -5
;sloc1                     Allocated to stack - sp -1
;lastLoop67Hz              Allocated with name '_main_lastLoop67Hz_196608_76'
;------------------------------------------------------------
;main.c:29: static uint32_t lastLoop67Hz = 0;
	ldhx	#_main_lastLoop67Hz_196608_76
	clra
	sta	,x
	sta	1,x
	sta	2,x
	sta	3,x
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
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;now                       Allocated to stack - sp +8
;newPW1                    Allocated to stack - sp +10
;newAdvance                Allocated to stack - sp +9
;newDwell                  Allocated to registers x h 
;sloc0                     Allocated to stack - sp +1
;sloc1                     Allocated to stack - sp +5
;lastLoop67Hz              Allocated with name '_main_lastLoop67Hz_196608_76'
;------------------------------------------------------------
;main.c:19: int main(void) {
;	-----------------------------------------
;	 function main
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 11 bytes.
_main:
	ais	#-11
;main.c:20: timebaseInit();
	jsr	_timebaseInit
;main.c:21: schedulerInit();
	jsr	_schedulerInit
;main.c:22: initTables();
	jsr	_initTables
;main.c:23: triggerInit();
	jsr	_triggerInit
;main.c:24: commsInit();
	jsr	_commsInit
;globals.h:101: static inline void interrupts(void)   { __asm cli __endasm; }
	 cli	
;main.c:26: interrupts();
00108$:
;main.c:30: uint32_t now = micros();
	jsr	_micros
	sta	4,s
	stx	3,s
	lda	*___SDCC_hc08_ret2
	sta	2,s
	lda	*___SDCC_hc08_ret3
	sta	1,s
;main.c:33: commsProcess();
	jsr	_commsProcess
;main.c:36: processInjectorPolling();
	jsr	_processInjectorPolling
;main.c:38: if ((uint32_t)(now - lastLoop67Hz) >= 67000UL) {
	tsx
	ldhx	#_main_lastLoop67Hz_196608_76
	lda	4,s
	sub	3,x
	sta	8,s
	lda	3,s
	sbc	2,x
	sta	7,s
	lda	2,s
	sbc	1,x
	sta	6,s
	lda	1,s
	sbc	,x
	sta	5,s
	tsx
	lda	7,x
	sub	#0xb8
	lda	6,x
	sbc	#0x05
	lda	5,x
	sbc	#0x01
	lda	4,x
	sbc	#0x00
	bcs	00108$
;main.c:39: lastLoop67Hz = now;
	ldhx	#_main_lastLoop67Hz_196608_76
	lda	1,s
	sta	,x
	lda	2,s
	sta	1,x
	lda	3,s
	sta	2,x
	lda	4,s
	sta	3,x
;main.c:40: calculateRPM();
	jsr	_calculateRPM
;main.c:41: checkSyncLoss();
	jsr	_checkSyncLoss
;main.c:42: updateEngineStatus();
	jsr	_updateEngineStatus
;main.c:44: if (currentStatus.hasSync && currentStatus.RPM > 0) {
	lda	(_currentStatus + 0x0002)
	beq	00108$
	ldx	_currentStatus
	lda	(_currentStatus + 1)
	bne	00134$
	tstx
00134$:
	beq	00108$
;main.c:49: uint16_t newPW1 = calculateInjection();
	jsr	_calculateInjection
	sta	11,s
	stx	10,s
;main.c:50: int8_t newAdvance = calculateAdvance();
	jsr	_calculateAdvance
	sta	9,s
;main.c:51: uint16_t newDwell = calculateDwell();
	jsr	_calculateDwell
	psha
	pshx
	pulh
	pulx
;main.c:58: }
	tpa
	sei
	psha
;main.c:54: currentStatus.PW1 = newPW1;
	lda	11,s
	sta	(_currentStatus + 0x001c)
	lda	12,s
	sta	((_currentStatus + 0x001c) + 1)
;main.c:55: currentStatus.PW2 = newPW1;
	lda	11,s
	sta	(_currentStatus + 0x001e)
	lda	12,s
	sta	((_currentStatus + 0x001e) + 1)
;main.c:56: currentStatus.advance = newAdvance;
	lda	10,s
	sta	(_currentStatus + 0x0025)
;main.c:57: currentStatus.dwell = newDwell;
	pshh
	pula
	sta	(_currentStatus + 0x0026)
	stx	((_currentStatus + 0x0026) + 1)
	pula
	tap
	jmp	00108$
;main.c:63: return 0;
;main.c:64: }
	ais	#11
	rts
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
