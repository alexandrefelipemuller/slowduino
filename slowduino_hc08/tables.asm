;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.2.0 #13081 (Linux)
;--------------------------------------------------------
	.module tables
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
	.globl _eepromReadI8
	.globl _eepromReadByte
	.globl _ignTable
	.globl _veTable
	.globl _initTables
	.globl _getTableValue
	.globl _findTableXIndices
	.globl _findTableYIndices
	.globl _lookupCurveU8
	.globl _lookupCurveI8
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
_veTable::
	.ds 39
_ignTable::
	.ds 39
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
;Allocation info for local variables in function 'initTables'
;------------------------------------------------------------
;tables.c:17: void initTables(void) {
;	-----------------------------------------
;	 function initTables
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_initTables:
;tables.c:18: veTable.isSigned = false;
	clra
	sta	(_veTable + 0x0026)
;tables.c:19: ignTable.isSigned = true;
	inca
	sta	(_ignTable + 0x0026)
;tables.c:20: veTable.eepromValuesBase = EEPROM_VE_TABLE;
	deca
	sta	(_veTable + 0x0024)
	sta	((_veTable + 0x0024) + 1)
;tables.c:21: ignTable.eepromValuesBase = EEPROM_IGN_TABLE;
	sta	(_ignTable + 0x0024)
	lda	#0x90
	sta	((_ignTable + 0x0024) + 1)
;tables.c:22: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'readTableCell'
;------------------------------------------------------------
;y                         Allocated to stack - sp +9
;x                         Allocated to stack - sp +10
;table                     Allocated to stack - sp +5
;addr                      Allocated to registers a x 
;sloc0                     Allocated to stack - sp +3
;sloc1                     Allocated to stack - sp +1
;------------------------------------------------------------
;tables.c:24: static int16_t readTableCell(const struct Table3D *table, uint8_t y, uint8_t x) {
;	-----------------------------------------
;	 function readTableCell
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 6 bytes.
_readTableCell:
	psha
	pshx
	ais	#-4
;tables.c:25: uint16_t addr = table->eepromValuesBase + ((uint16_t)y * TABLE_SIZE_X) + x;
	tsx
	lda	4,x
	sta	2,x
	lda	5,x
	sta	3,x
	lda	2,x
	psha
	pulh
	ldx	4,s
	lda	36,x
	sta	3,s
	lda	37,x
	sta	4,s
	lda	9,s
	clrx
	psha
	pshx
	lda	#0x0c
	jsr	__mulint
	sta	4,s
	stx	3,s
	ais	#2
	lda	4,s
	ldx	3,s
	add	2,s
	sta	2,s
	txa
	adc	1,s
	sta	1,s
	lda	10,s
	clrx
	add	2,s
	psha
	txa
	adc	2,s
	tax
;tables.c:26: return table->isSigned ? (int16_t)eepromReadI8(addr) : (int16_t)eepromReadByte(addr);
	lda	6,s
	sta	2,s
	lda	7,s
	sta	3,s
	pula
	pshx
	ldx	2,s
	pshx
	pulh
	ldx	3,s
	psha
	lda	38,x
	pula
	pulx
	beq	00103$
	jsr	_eepromReadI8
	psha
	rola	
	clra	
	sbc	#0x00
	tax
	pula
	bra	00104$
00103$:
	jsr	_eepromReadByte
	clrx
00104$:
;tables.c:27: }
	ais	#6
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'getTableValue'
;------------------------------------------------------------
;valueY                    Allocated to stack - sp +81
;valueX                    Allocated to stack - sp +82
;table                     Allocated to stack - sp +62
;xLow                      Allocated to stack - sp +3
;xHigh                     Allocated to stack - sp +2
;yLow                      Allocated to stack - sp +1
;yHigh                     Allocated to stack - sp +4
;q11                       Allocated to stack - sp +77
;q21                       Allocated to stack - sp +75
;q12                       Allocated to stack - sp +73
;q22                       Allocated to stack - sp +71
;x1                        Allocated to stack - sp +69
;x2                        Allocated to stack - sp +67
;y1                        Allocated to stack - sp +66
;y2                        Allocated to registers x 
;result                    Allocated to stack - sp +64
;__1966080001              Allocated to stack - sp +11
;__1966080002              Allocated to stack - sp +58
;__1966080003              Allocated to stack - sp +56
;__1966080004              Allocated to stack - sp +54
;__1966080005              Allocated to registers 
;__1966080006              Allocated to registers 
;x                         Allocated to registers 
;x1                        Allocated to registers 
;x2                        Allocated to registers 
;y1                        Allocated to registers 
;y2                        Allocated to registers 
;__1966080008              Allocated to stack - sp +20
;__1966080009              Allocated to stack - sp +52
;__1966080010              Allocated to stack - sp +50
;__1966080011              Allocated to stack - sp +48
;__1966080012              Allocated to registers 
;__1966080013              Allocated to registers 
;x                         Allocated to registers 
;x1                        Allocated to registers 
;x2                        Allocated to registers 
;y1                        Allocated to registers 
;y2                        Allocated to registers 
;__1966080029              Allocated to stack - sp +34
;__1966080022              Allocated to stack - sp +22
;__1966080015              Allocated to stack - sp +34
;r1                        Allocated to stack - sp +60
;r2                        Allocated to registers 
;__1966080016              Allocated to stack - sp +20
;__1966080017              Allocated to stack - sp +26
;__1966080018              Allocated to stack - sp +36
;__1966080019              Allocated to registers 
;__1966080020              Allocated to registers 
;x                         Allocated to registers 
;x1                        Allocated to registers 
;x2                        Allocated to registers 
;y1                        Allocated to registers 
;y2                        Allocated to registers 
;__1966080023              Allocated to registers 
;__1966080024              Allocated to registers 
;__1966080025              Allocated to registers 
;__1966080026              Allocated to registers 
;__1966080027              Allocated to registers 
;x                         Allocated to registers 
;x1                        Allocated to registers 
;x2                        Allocated to registers 
;y1                        Allocated to registers 
;y2                        Allocated to registers 
;__1966080030              Allocated to stack - sp +46
;__1966080031              Allocated to stack - sp +44
;__1966080032              Allocated to stack - sp +42
;__1966080033              Allocated to registers 
;__1966080034              Allocated to registers 
;x                         Allocated to registers 
;x1                        Allocated to registers 
;x2                        Allocated to registers 
;y1                        Allocated to registers 
;y2                        Allocated to registers 
;sloc0                     Allocated to stack - sp +11
;sloc1                     Allocated to stack - sp +40
;sloc2                     Allocated to stack - sp +13
;sloc3                     Allocated to stack - sp +9
;sloc4                     Allocated to stack - sp +18
;sloc5                     Allocated to stack - sp +14
;sloc6                     Allocated to stack - sp +30
;sloc7                     Allocated to stack - sp +5
;sloc8                     Allocated to stack - sp +20
;sloc9                     Allocated to stack - sp +26
;sloc10                    Allocated to stack - sp +36
;sloc11                    Allocated to stack - sp +34
;sloc12                    Allocated to stack - sp +22
;------------------------------------------------------------
;tables.c:29: int16_t getTableValue(struct Table3D *table, uint8_t valueY, uint16_t valueX) {
;	-----------------------------------------
;	 function getTableValue
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 78 bytes.
_getTableValue:
	ais	#-78
	sta	63,s
	stx	62,s
;tables.c:36: findTableXIndices(table, valueX, &xLow, &xHigh);
	tsx
	aix	#1
	stx	12,s
	pshh
	pula
	sta	11,s
	tsx
	aix	#2
	lda	12,s
	psha
	lda	12,s
	psha
	pshx
	pshh
	tsx
	lda	86,x
	psha
	lda	85,x
	psha
	lda	66,x
	ldx	65,x
	jsr	_findTableXIndices
	ais	#6
;tables.c:37: findTableYIndices(table, valueY, &yLow, &yHigh);
	tsx
	aix	#3
	stx	12,s
	pshh
	pula
	sta	11,s
	tsx
	lda	12,s
	psha
	lda	12,s
	psha
	pshx
	pshh
	tsx
	lda	84,x
	psha
	lda	66,x
	ldx	65,x
	jsr	_findTableYIndices
	ais	#5
;tables.c:39: q11 = readTableCell(table, yLow, xLow);
	tsx
	lda	2,x
	psha
	lda	,x
	psha
	lda	62,x
	ldx	61,x
	jsr	_readTableCell
	sta	80,s
	stx	79,s
	ais	#2
;tables.c:40: q21 = readTableCell(table, yLow, xHigh);
	tsx
	lda	1,x
	psha
	lda	,x
	psha
	lda	62,x
	ldx	61,x
	jsr	_readTableCell
	sta	78,s
	stx	77,s
	ais	#2
;tables.c:41: q12 = readTableCell(table, yHigh, xLow);
	tsx
	lda	2,x
	psha
	lda	3,x
	psha
	lda	62,x
	ldx	61,x
	jsr	_readTableCell
	sta	76,s
	stx	75,s
	ais	#2
;tables.c:42: q22 = readTableCell(table, yHigh, xHigh);
	tsx
	lda	1,x
	psha
	lda	3,x
	psha
	lda	62,x
	ldx	61,x
	jsr	_readTableCell
	sta	74,s
	stx	73,s
	ais	#2
;tables.c:44: if (xLow == xHigh && yLow == yHigh) {
	tsx
	lda	2,x
	cmp	1,x
	beq	00173$
	clra
	bra	00172$
00173$:
	lda	#0x01
00172$:
	sta	10,x
	tst	10,x
	beq	00102$
	lda	,x
	cmp	3,x
	bne	00102$
;tables.c:45: return q11;
	ldx	76,x
	lda	78,s
	jmp	00125$
00102$:
;tables.c:48: x1 = table->axisX[xLow];
	lda	3,s
	lsla	
	add	63,s
	tax
	clra
	adc	62,s
	psha
	pulh
	lda	,x
	sta	69,s
	lda	1,x
	sta	70,s
;tables.c:49: x2 = table->axisX[xHigh];
	lda	2,s
	lsla	
	add	63,s
	tax
	clra
	adc	62,s
	psha
	pulh
	lda	,x
	sta	67,s
	lda	1,x
	sta	68,s
;tables.c:50: y1 = table->axisY[yLow];
	tsx
	lda	62,x
	add	#0x18
	sta	40,x
	lda	61,x
	adc	#0
	sta	39,x
	lda	,x
	sta	12,x
	lda	12,x
	add	40,x
	tax
	lda	#0x00
	adc	40,s
	psha
	pulh
	lda	,x
	sta	66,s
;tables.c:51: y2 = table->axisY[yHigh];
	lda	4,s
	psha
	pulh
	pshh
	pula
	add	41,s
	tax
	clra
	adc	40,s
	pshh
	psha
	pulh
	ldx	,x
	pulh
;tables.c:54: result = interpolate((int16_t)valueY, y1, y2, q11, q12);
	stx	41,s
	clra
	sta	40,s
	lda	66,s
	sta	10,s
	clra
	sta	9,s
	lda	81,s
	sta	19,s
	clra
	sta	18,s
;tables.c:53: if (xLow == xHigh) {
	tst	11,s
	bne	00176$
	jmp	00108$
00176$:
;tables.c:54: result = interpolate((int16_t)valueY, y1, y2, q11, q12);
	tsx
	lda	39,x
	sta	53,x
	lda	40,x
	sta	54,x
	lda	8,x
	sta	55,x
	lda	9,x
	sta	56,x
	lda	17,x
	sta	57,x
	lda	18,x
	sta	58,x
;tables.h:34: if (x2 == x1) return y1;
	lda	54,x
	cmp	56,x
	bne	00177$
	lda	53,x
	cmp	55,x
	beq	00178$
00177$:
	bra	00111$
00178$:
	lda	76,x
	sta	10,x
	lda	77,x
	sta	11,x
	jmp	00112$
00111$:
;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
	lda	59,s
	sub	57,s
	psha
	lda	59,s
	sbc	57,s
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
	lda	74,s
	sub	78,s
	psha
	lda	74,s
	sbc	78,s
	tax
	pula
	sta	33,s
	txa
	sta	32,s
	rola	
	clra	
	sbc	#0x00
	sta	31,s
	sta	30,s
	tsx
	lda	32,x
	psha
	lda	31,x
	psha
	lda	30,x
	psha
	lda	29,x
	psha
	lda	16,x
	psha
	lda	15,x
	psha
	lda	14,x
	psha
	lda	13,x
	psha
	jsr	__mullong
	sta	41,s
	stx	40,s
	lda	*___SDCC_hc08_ret2
	sta	39,s
	lda	*___SDCC_hc08_ret3
	sta	38,s
	ais	#8
	lda	55,s
	sub	57,s
	psha
	lda	55,s
	sbc	57,s
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
	lda	32,x
	psha
	lda	31,x
	psha
	lda	30,x
	psha
	lda	29,x
	psha
	jsr	__divslong
	sta	41,s
	stx	40,s
	lda	*___SDCC_hc08_ret2
	sta	39,s
	lda	*___SDCC_hc08_ret3
	sta	38,s
	ais	#8
	lda	33,s
	ldx	32,s
	add	78,s
	sta	12,s
	txa
	adc	77,s
	sta	11,s
;tables.c:54: result = interpolate((int16_t)valueY, y1, y2, q11, q12);
00112$:
	tsx
	lda	10,x
	sta	63,x
	lda	11,x
	sta	64,x
	jmp	00109$
00108$:
;tables.c:56: result = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q11, q21);
	lda	68,s
	sta	31,s
	lda	67,s
	sta	30,s
	lda	70,s
	sta	15,s
	lda	69,s
	sta	14,s
	lda	83,s
	sta	12,s
	lda	82,s
	sta	11,s
;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
	lda	76,s
	sub	78,s
	psha
	lda	76,s
	sbc	78,s
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
;tables.c:55: } else if (yLow == yHigh) {
	pshh
	pula
	cmp	13,s
	beq	00179$
	jmp	00105$
00179$:
;tables.c:56: result = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q11, q21);
	tsx
	lda	29,x
	sta	47,x
	lda	30,x
	sta	48,x
	lda	13,x
	sta	49,x
	lda	14,x
	sta	50,x
	lda	10,x
	sta	51,x
	lda	11,x
	sta	52,x
;tables.h:34: if (x2 == x1) return y1;
	lda	48,x
	cmp	50,x
	bne	00180$
	lda	47,x
	cmp	49,x
	beq	00181$
00180$:
	bra	00114$
00181$:
	lda	76,x
	sta	19,x
	lda	77,x
	sta	20,x
	jmp	00115$
00114$:
;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
	lda	53,s
	sub	51,s
	psha
	lda	53,s
	sbc	51,s
	tax
	pula
	sta	29,s
	txa
	sta	28,s
	rola	
	clra	
	sbc	#0x00
	sta	27,s
	sta	26,s
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	lda	28,x
	psha
	lda	27,x
	psha
	lda	26,x
	psha
	lda	25,x
	psha
	jsr	__mullong
	sta	37,s
	stx	36,s
	lda	*___SDCC_hc08_ret2
	sta	35,s
	lda	*___SDCC_hc08_ret3
	sta	34,s
	ais	#8
	lda	49,s
	sub	51,s
	psha
	lda	49,s
	sbc	51,s
	tax
	pula
	sta	39,s
	txa
	sta	38,s
	rola	
	clra	
	sbc	#0x00
	sta	37,s
	sta	36,s
	tsx
	lda	38,x
	psha
	lda	37,x
	psha
	lda	36,x
	psha
	lda	35,x
	psha
	lda	28,x
	psha
	lda	27,x
	psha
	lda	26,x
	psha
	lda	25,x
	psha
	jsr	__divslong
	sta	47,s
	stx	46,s
	lda	*___SDCC_hc08_ret2
	sta	45,s
	lda	*___SDCC_hc08_ret3
	sta	44,s
	ais	#8
	lda	39,s
	ldx	38,s
	add	78,s
	sta	21,s
	txa
	adc	77,s
	sta	20,s
;tables.c:56: result = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q11, q21);
00115$:
	tsx
	lda	19,x
	sta	63,x
	lda	20,x
	sta	64,x
	jmp	00109$
00105$:
;tables.c:58: int16_t r1 = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q11, q21);
	tsx
	lda	29,x
	sta	35,x
	lda	30,x
	sta	36,x
	lda	13,x
	sta	25,x
	lda	14,x
	sta	26,x
	lda	10,x
	sta	19,x
	lda	11,x
	sta	20,x
	lda	36,x
	cmp	26,x
	bne	00182$
	lda	35,x
	cmp	25,x
	beq	00183$
00182$:
	bra	00117$
00183$:
	lda	76,x
	sta	33,x
	lda	77,x
	sta	34,x
	jmp	00118$
00117$:
	lda	21,s
	sub	27,s
	psha
	lda	21,s
	sbc	27,s
	tax
	pula
	sta	25,s
	txa
	sta	24,s
	rola	
	clra	
	sbc	#0x00
	sta	23,s
	sta	22,s
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	lda	24,x
	psha
	lda	23,x
	psha
	lda	22,x
	psha
	lda	21,x
	psha
	jsr	__mullong
	sta	33,s
	stx	32,s
	lda	*___SDCC_hc08_ret2
	sta	31,s
	lda	*___SDCC_hc08_ret3
	sta	30,s
	ais	#8
	lda	37,s
	sub	27,s
	psha
	lda	37,s
	sbc	27,s
	tax
	pula
	sta	39,s
	txa
	sta	38,s
	rola	
	clra	
	sbc	#0x00
	sta	37,s
	sta	36,s
	tsx
	lda	38,x
	psha
	lda	37,x
	psha
	lda	36,x
	psha
	lda	35,x
	psha
	lda	24,x
	psha
	lda	23,x
	psha
	lda	22,x
	psha
	lda	21,x
	psha
	jsr	__divslong
	sta	33,s
	stx	32,s
	lda	*___SDCC_hc08_ret2
	sta	31,s
	lda	*___SDCC_hc08_ret3
	sta	30,s
	ais	#8
	lda	25,s
	ldx	24,s
	add	78,s
	sta	35,s
	txa
	adc	77,s
	sta	34,s
00118$:
	tsx
	lda	33,x
	sta	59,x
	lda	34,x
	sta	60,x
;tables.c:59: int16_t r2 = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q12, q22);
	lda	30,x
	cmp	14,x
	bne	00184$
	lda	29,x
	cmp	13,x
	beq	00185$
00184$:
	bra	00120$
00185$:
	lda	72,x
	sta	21,x
	lda	73,x
	sta	22,x
	jmp	00121$
00120$:
	lda	12,s
	sub	15,s
	psha
	lda	12,s
	sbc	15,s
	tax
	pula
	sta	39,s
	txa
	sta	38,s
	rola	
	clra	
	sbc	#0x00
	sta	37,s
	sta	36,s
	lda	72,s
	sub	74,s
	psha
	lda	72,s
	sbc	74,s
	tax
	pula
	sta	29,s
	txa
	sta	28,s
	rola	
	clra	
	sbc	#0x00
	sta	27,s
	sta	26,s
	tsx
	lda	28,x
	psha
	lda	27,x
	psha
	lda	26,x
	psha
	lda	25,x
	psha
	lda	38,x
	psha
	lda	37,x
	psha
	lda	36,x
	psha
	lda	35,x
	psha
	jsr	__mullong
	sta	47,s
	stx	46,s
	lda	*___SDCC_hc08_ret2
	sta	45,s
	lda	*___SDCC_hc08_ret3
	sta	44,s
	ais	#8
	lda	31,s
	sub	15,s
	psha
	lda	31,s
	sbc	15,s
	tax
	pula
	sta	29,s
	txa
	sta	28,s
	rola	
	clra	
	sbc	#0x00
	sta	27,s
	sta	26,s
	tsx
	lda	28,x
	psha
	lda	27,x
	psha
	lda	26,x
	psha
	lda	25,x
	psha
	lda	38,x
	psha
	lda	37,x
	psha
	lda	36,x
	psha
	lda	35,x
	psha
	jsr	__divslong
	sta	47,s
	stx	46,s
	lda	*___SDCC_hc08_ret2
	sta	45,s
	lda	*___SDCC_hc08_ret3
	sta	44,s
	ais	#8
	lda	39,s
	ldx	38,s
	add	74,s
	sta	23,s
	txa
	adc	73,s
	sta	22,s
00121$:
;tables.c:60: result = interpolate((int16_t)valueY, y1, y2, r1, r2);
	tsx
	lda	39,x
	sta	41,x
	lda	40,x
	sta	42,x
	lda	8,x
	sta	43,x
	lda	9,x
	sta	44,x
	lda	17,x
	sta	45,x
	lda	18,x
	sta	46,x
;tables.h:34: if (x2 == x1) return y1;
	lda	42,x
	cmp	44,x
	bne	00186$
	lda	41,x
	cmp	43,x
	beq	00187$
00186$:
	bra	00123$
00187$:
	lda	59,x
	sta	33,x
	lda	60,x
	sta	34,x
	jmp	00124$
00123$:
;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
	lda	47,s
	sub	45,s
	psha
	lda	47,s
	sbc	45,s
	tax
	pula
	sta	39,s
	txa
	sta	38,s
	rola	
	clra	
	sbc	#0x00
	sta	37,s
	sta	36,s
	lda	23,s
	sub	61,s
	psha
	lda	23,s
	sbc	61,s
	tax
	pula
	sta	25,s
	txa
	sta	24,s
	rola	
	clra	
	sbc	#0x00
	sta	23,s
	sta	22,s
	tsx
	lda	24,x
	psha
	lda	23,x
	psha
	lda	22,x
	psha
	lda	21,x
	psha
	lda	38,x
	psha
	lda	37,x
	psha
	lda	36,x
	psha
	lda	35,x
	psha
	jsr	__mullong
	sta	33,s
	stx	32,s
	lda	*___SDCC_hc08_ret2
	sta	31,s
	lda	*___SDCC_hc08_ret3
	sta	30,s
	ais	#8
	lda	43,s
	sub	45,s
	psha
	lda	43,s
	sbc	45,s
	tax
	pula
	sta	39,s
	txa
	sta	38,s
	rola	
	clra	
	sbc	#0x00
	sta	37,s
	sta	36,s
	tsx
	lda	38,x
	psha
	lda	37,x
	psha
	lda	36,x
	psha
	lda	35,x
	psha
	lda	24,x
	psha
	lda	23,x
	psha
	lda	22,x
	psha
	lda	21,x
	psha
	jsr	__divslong
	sta	33,s
	stx	32,s
	lda	*___SDCC_hc08_ret2
	sta	31,s
	lda	*___SDCC_hc08_ret3
	sta	30,s
	ais	#8
	lda	25,s
	ldx	24,s
	add	61,s
	sta	35,s
	txa
	adc	60,s
	sta	34,s
;tables.c:60: result = interpolate((int16_t)valueY, y1, y2, r1, r2);
00124$:
	tsx
	lda	33,x
	sta	63,x
	lda	34,x
	sta	64,x
00109$:
;tables.c:63: return result;
	tsx
	ldx	63,x
	lda	65,s
00125$:
;tables.c:64: }
	ais	#78
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'findTableXIndices'
;------------------------------------------------------------
;value                     Allocated to stack - sp +13
;idxLow                    Allocated to stack - sp +15
;idxHigh                   Allocated to stack - sp +17
;table                     Allocated to stack - sp +9
;i                         Allocated to stack - sp +8
;sloc0                     Allocated to stack - sp +6
;sloc1                     Allocated to stack - sp +4
;sloc2                     Allocated to stack - sp +2
;sloc3                     Allocated to stack - sp +1
;------------------------------------------------------------
;tables.c:66: void findTableXIndices(struct Table3D *table, uint16_t value, uint8_t *idxLow, uint8_t *idxHigh) {
;	-----------------------------------------
;	 function findTableXIndices
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 10 bytes.
_findTableXIndices:
	psha
	pshx
	ais	#-8
;tables.c:69: if (value <= table->axisX[0]) {
	lda	9,s
	psha
	pulh
	ldx	10,s
	lda	,x
	psha
	ldx	1,x
	pulh
;tables.c:70: *idxLow = 0;
	lda	15,s
	sta	6,s
	lda	16,s
	sta	7,s
;tables.c:71: *idxHigh = 0;
	lda	17,s
	sta	4,s
	lda	18,s
	sta	5,s
;tables.c:69: if (value <= table->axisX[0]) {
	txa
	sub	14,s
	pshh
	pula
	sbc	13,s
	bcs	00102$
;tables.c:70: *idxLow = 0;
	lda	6,s
	psha
	pulh
	ldx	7,s
	clra
	sta	,x
;tables.c:71: *idxHigh = 0;
	lda	4,s
	psha
	pulh
	ldx	5,s
	clra
	sta	,x
;tables.c:72: return;
	jmp	00111$
00102$:
;tables.c:74: if (value >= table->axisX[TABLE_SIZE_X - 1]) {
	tsx
	lda	8,x
	sta	1,x
	lda	9,x
	sta	2,x
	lda	1,x
	psha
	pulh
	ldx	3,s
	lda	23,x
	ldx	22,x
	psha
	lda	15,s
	sub	1, s
	pula
	lda	13,s
	pshx
	sbc	1,s
	ais	#1
	bcs	00104$
;tables.c:75: *idxLow = TABLE_SIZE_X - 1;
	lda	6,s
	psha
	pulh
	ldx	7,s
	lda	#0x0b
	sta	,x
;tables.c:76: *idxHigh = TABLE_SIZE_X - 1;
	lda	4,s
	psha
	pulh
	ldx	5,s
	lda	#0x0b
	sta	,x
;tables.c:77: return;
	jmp	00111$
00104$:
;tables.c:80: for (i = 0; i < TABLE_SIZE_X - 1; i++) {
	tsx
	clra
	sta	1,x
	sta	7,x
00109$:
;tables.c:81: if (value >= table->axisX[i] && value < table->axisX[i + 1]) {
	lda	8,s
	lsla	
	add	10,s
	tax
	clra
	adc	9,s
	psha
	pulh
	lda	1,x
	ldx	,x
	psha
	lda	15,s
	sub	1, s
	pula
	lda	13,s
	pshx
	sbc	1,s
	ais	#1
	bcs	00110$
	tsx
	lda	7,x
	add	#0x01
	sta	,x
	lda	,x
	lsla	
	add	9,x
	tax
	clra
	adc	9,s
	psha
	pulh
	lda	1,x
	ldx	,x
	psha
	lda	15,s
	sub	1, s
	pula
	lda	13,s
	pshx
	sbc	1,s
	ais	#1
	bcc	00110$
;tables.c:82: *idxLow = i;
	lda	6,s
	psha
	pulh
	ldx	7,s
	lda	2,s
	sta	,x
;tables.c:83: *idxHigh = i + 1;
	lda	4,s
	psha
	pulh
	ldx	5,s
	lda	1,s
	sta	,x
;tables.c:84: return;
	bra	00111$
00110$:
;tables.c:80: for (i = 0; i < TABLE_SIZE_X - 1; i++) {
	tsx
	inc	7,x
	lda	7,x
	sta	1,x
	lda	7,x
	cmp	#0x0b
	bcs	00109$
;tables.c:88: *idxLow = TABLE_SIZE_X - 2;
	lda	5,x
	psha
	pulh
	ldx	7,s
	lda	#0x0a
	sta	,x
;tables.c:89: *idxHigh = TABLE_SIZE_X - 1;
	lda	4,s
	psha
	pulh
	ldx	5,s
	lda	#0x0b
	sta	,x
00111$:
;tables.c:90: }
	ais	#10
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'findTableYIndices'
;------------------------------------------------------------
;value                     Allocated to stack - sp +16
;idxLow                    Allocated to stack - sp +17
;idxHigh                   Allocated to stack - sp +19
;table                     Allocated to stack - sp +5
;i                         Allocated to stack - sp +7
;sloc0                     Allocated to stack - sp +12
;sloc1                     Allocated to stack - sp +1
;sloc2                     Allocated to stack - sp +3
;sloc3                     Allocated to stack - sp +10
;sloc4                     Allocated to stack - sp +8
;------------------------------------------------------------
;tables.c:92: void findTableYIndices(struct Table3D *table, uint8_t value, uint8_t *idxLow, uint8_t *idxHigh) {
;	-----------------------------------------
;	 function findTableYIndices
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 13 bytes.
_findTableYIndices:
	ais	#-13
	sta	6,s
	stx	5,s
;tables.c:95: if (value <= table->axisY[0]) {
	lda	5,s
	ldx	6,s
	psha
	pulh
	ldx	24,x
;tables.c:96: *idxLow = 0;
	lda	17,s
	sta	12,s
	lda	18,s
	sta	13,s
;tables.c:97: *idxHigh = 0;
	lda	19,s
	sta	1,s
	lda	20,s
	sta	2,s
;tables.c:95: if (value <= table->axisY[0]) {
	cpx	16,s
	bcs	00102$
;tables.c:96: *idxLow = 0;
	lda	12,s
	psha
	pulh
	ldx	13,s
	clra
	sta	,x
;tables.c:97: *idxHigh = 0;
	pulh
	pulx
	pshx
	pshh
	sta	,x
;tables.c:98: return;
	jmp	00111$
00102$:
;tables.c:100: if (value >= table->axisY[TABLE_SIZE_Y - 1]) {
	tsx
	lda	5,x
	add	#0x18
	sta	3,x
	lda	4,x
	adc	#0
	sta	2,x
	lda	2,x
	sta	9,x
	lda	3,x
	sta	10,x
	lda	9,x
	psha
	pulh
	ldx	11,s
	lda	11,x
	cmp	16,s
	bhi	00104$
;tables.c:101: *idxLow = TABLE_SIZE_Y - 1;
	lda	12,s
	psha
	pulh
	ldx	13,s
	lda	#0x0b
	sta	,x
;tables.c:102: *idxHigh = TABLE_SIZE_Y - 1;
	pulh
	pulx
	pshx
	pshh
	sta	,x
;tables.c:103: return;
	bra	00111$
00104$:
;tables.c:106: for (i = 0; i < TABLE_SIZE_Y - 1; i++) {
	tsx
	clra
	sta	9,x
	lda	2,x
	sta	7,x
	lda	3,x
	sta	8,x
	clra
	sta	6,x
00109$:
;tables.c:107: if (value >= table->axisY[i] && value < table->axisY[i + 1]) {
	lda	7,s
	add	4,s
	tax
	lda	#0x00
	adc	3,s
	psha
	pulh
	ldx	,x
	cpx	16,s
	bhi	00110$
	lda	7,s
	inca
	psha
	add	10,s
	tax
	clra
	adc	9,s
	psha
	pulh
	pula
	ldx	,x
	cpx	16,s
	bls	00110$
;tables.c:108: *idxLow = i;
	psha
	lda	13,s
	psha
	pulh
	ldx	14,s
	lda	11,s
	sta	,x
	pula
;tables.c:109: *idxHigh = i + 1;
	pulh
	pulx
	pshx
	pshh
	sta	,x
;tables.c:110: return;
	bra	00111$
00110$:
;tables.c:106: for (i = 0; i < TABLE_SIZE_Y - 1; i++) {
	tsx
	inc	6,x
	lda	6,x
	sta	9,x
	lda	6,x
	cmp	#0x0b
	bcs	00109$
;tables.c:114: *idxLow = TABLE_SIZE_Y - 2;
	lda	11,x
	psha
	pulh
	ldx	13,s
	lda	#0x0a
	sta	,x
;tables.c:115: *idxHigh = TABLE_SIZE_Y - 1;
	pulh
	pulx
	pshx
	pshh
	inca
	sta	,x
00111$:
;tables.c:116: }
	ais	#13
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'lookupCurveU8'
;------------------------------------------------------------
;values                    Allocated to stack - sp +34
;size                      Allocated to stack - sp +36
;x                         Allocated to stack - sp +37
;bins                      Allocated to stack - sp +29
;i                         Allocated to stack - sp +31
;__3276800036              Allocated to stack - sp +19
;__3276800037              Allocated to registers a x 
;__3276800038              Allocated to stack - sp +27
;__3276800039              Allocated to stack - sp +25
;__3276800040              Allocated to stack - sp +23
;__3276800041              Allocated to stack - sp +21
;x                         Allocated to registers 
;x1                        Allocated to registers 
;x2                        Allocated to registers 
;y1                        Allocated to registers 
;y2                        Allocated to registers 
;sloc0                     Allocated to stack - sp +1
;sloc1                     Allocated to stack - sp +11
;sloc2                     Allocated to stack - sp +13
;sloc3                     Allocated to stack - sp +15
;sloc4                     Allocated to stack - sp +17
;sloc5                     Allocated to stack - sp +19
;sloc6                     Allocated to stack - sp +3
;sloc7                     Allocated to stack - sp +7
;------------------------------------------------------------
;tables.c:118: uint8_t lookupCurveU8(const int8_t *bins, const uint8_t *values, uint8_t size, int16_t x) {
;	-----------------------------------------
;	 function lookupCurveU8
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 31 bytes.
_lookupCurveU8:
	ais	#-31
	sta	30,s
	stx	29,s
;tables.c:120: if (size == 0) return 0;
	tst	36,s
	bne	00102$
	clra
	jmp	00117$
00102$:
;tables.c:121: if (x <= bins[0]) return values[0];
	lda	29,s
	psha
	pulh
	ldx	30,s
	lda	,x
	psha
	rola	
	clra	
	sbc	#0x00
	tax
	pula
	sub	38,s
	txa
	sbc	37,s
	blt	00104$
	tsx
	lda	33,x
	psha
	pulh
	ldx	35,s
	lda	,x
	jmp	00117$
00104$:
;tables.c:122: if (x >= bins[size - 1]) return values[size - 1];
	ldx	36,s
	clrh
	aix	#-1
	pshh
	pula
	sta	1,s
	stx	2,s
	lda	2,s
	add	30,s
	tax
	lda	1,s
	adc	29,s
	psha
	pulh
	lda	,x
	tsx
	sta	11,x
	rola	
	clra	
	sbc	#0x00
	sta	10,x
	lda	1,x
	add	34,x
	sta	13,x
	lda	,x
	adc	33,x
	sta	12,x
	lda	37,x
	sub	11,x
	lda	36,x
	sbc	10,x
	blt	00106$
	lda	12,x
	psha
	pulh
	ldx	14,s
	lda	,x
	jmp	00117$
00106$:
;tables.c:124: for (i = 0; i < size - 1; i++) {
	tsx
	clra
	sta	10,x
	sta	30,x
00115$:
	tsx
	lda	30,x
	sta	15,x
	clra
	sta	14,x
	lda	15,x
	sub	1,x
	lda	14,x
	sbc	,x
	blt	00162$
	jmp	00110$
00162$:
;tables.c:125: if (x >= bins[i] && x < bins[i + 1]) {
	lda	30,x
	add	29,x
	tax
	lda	#0x00
	adc	29,s
	psha
	pulh
	lda	,x
	tsx
	sta	17,x
	rola	
	clra	
	sbc	#0x00
	sta	16,x
	lda	37,x
	sub	17,x
	lda	36,x
	sbc	16,x
	bge	00163$
	jmp	00116$
00163$:
	inc	15,x
	bne	00164$
	inc	14,x
00164$:
	lda	15,x
	add	29,x
	tax
	lda	15,s
	adc	29,s
	psha
	pulh
	lda	,x
	tsx
	sta	19,x
	rola	
	clra	
	sbc	#0x00
	sta	18,x
	lda	37,x
	sub	19,x
	lda	36,x
	sbc	18,x
	blt	00165$
	jmp	00116$
00165$:
;tables.c:126: return (uint8_t)interpolate(x, bins[i], bins[i + 1], values[i], values[i + 1]);
	lda	15,x
	add	34,x
	tax
	lda	15,s
	adc	34,s
	psha
	pulh
	lda	,x
	tsx
	sta	21,x
	clrx
	stx	21,s
	lda	11,s
	add	35,s
	tax
	lda	#0x00
	adc	34,s
	psha
	pulh
	lda	,x
	tsx
	sta	23,x
	clrx
	stx	23,s
	tsx
	lda	18,x
	sta	24,x
	lda	19,x
	sta	25,x
	lda	16,x
	sta	26,x
	lda	17,x
	sta	27,x
	ldx	36,x
	lda	38,s
;tables.h:34: if (x2 == x1) return y1;
	psha
	lda	27,s
	cmp	29,s
	pula
	bne	00166$
	psha
	lda	26,s
	cmp	28,s
	pula
	beq	00167$
00166$:
	bra	00112$
00167$:
	tsx
	lda	22,x
	sta	18,x
	lda	23,x
	sta	19,x
	jmp	00113$
00112$:
;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
	sub	28,s
	psha
	txa
	sbc	28,s
	tax
	pula
	sta	6,s
	txa
	sta	5,s
	rola	
	clra	
	sbc	#0x00
	sta	4,s
	sta	3,s
	lda	22,s
	sub	24,s
	psha
	lda	22,s
	sbc	24,s
	tax
	pula
	sta	10,s
	txa
	sta	9,s
	rola	
	clra	
	sbc	#0x00
	sta	8,s
	sta	7,s
	tsx
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
	lda	3,x
	psha
	lda	2,x
	psha
	jsr	__mullong
	sta	18,s
	stx	17,s
	lda	*___SDCC_hc08_ret2
	sta	16,s
	lda	*___SDCC_hc08_ret3
	sta	15,s
	ais	#8
	lda	26,s
	sub	28,s
	psha
	lda	26,s
	sbc	28,s
	tax
	pula
	sta	6,s
	txa
	sta	5,s
	rola	
	clra	
	sbc	#0x00
	sta	4,s
	sta	3,s
	tsx
	lda	5,x
	psha
	lda	4,x
	psha
	lda	3,x
	psha
	lda	2,x
	psha
	lda	9,x
	psha
	lda	8,x
	psha
	lda	7,x
	psha
	lda	6,x
	psha
	jsr	__divslong
	sta	18,s
	stx	17,s
	lda	*___SDCC_hc08_ret2
	sta	16,s
	lda	*___SDCC_hc08_ret3
	sta	15,s
	ais	#8
	lda	10,s
	ldx	9,s
	add	24,s
	sta	20,s
	txa
	adc	23,s
	sta	19,s
;tables.c:126: return (uint8_t)interpolate(x, bins[i], bins[i + 1], values[i], values[i + 1]);
00113$:
	tsx
	lda	19,x
	bra	00117$
00116$:
;tables.c:124: for (i = 0; i < size - 1; i++) {
	tsx
	inc	30,x
	lda	30,x
	sta	10,x
	jmp	00115$
00110$:
;tables.c:129: return values[size - 1];
	lda	13,s
	psha
	pulh
	ldx	14,s
	lda	,x
00117$:
;tables.c:130: }
	ais	#31
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'lookupCurveI8'
;------------------------------------------------------------
;values                    Allocated to stack - sp +34
;size                      Allocated to stack - sp +36
;x                         Allocated to stack - sp +37
;bins                      Allocated to stack - sp +24
;i                         Allocated to stack - sp +23
;__3276800043              Allocated to stack - sp +19
;__3276800044              Allocated to registers a x 
;__3276800045              Allocated to stack - sp +26
;__3276800046              Allocated to stack - sp +21
;__3276800047              Allocated to stack - sp +28
;__3276800048              Allocated to stack - sp +30
;x                         Allocated to registers 
;x1                        Allocated to registers 
;x2                        Allocated to registers 
;y1                        Allocated to registers 
;y2                        Allocated to registers 
;sloc0                     Allocated to stack - sp +17
;sloc1                     Allocated to stack - sp +15
;sloc2                     Allocated to stack - sp +13
;sloc3                     Allocated to stack - sp +9
;sloc4                     Allocated to stack - sp +11
;sloc5                     Allocated to stack - sp +19
;sloc6                     Allocated to stack - sp +5
;sloc7                     Allocated to stack - sp +1
;------------------------------------------------------------
;tables.c:132: int8_t lookupCurveI8(const uint8_t *bins, const int8_t *values, uint8_t size, int16_t x) {
;	-----------------------------------------
;	 function lookupCurveI8
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 31 bytes.
_lookupCurveI8:
	ais	#-31
	sta	25,s
	stx	24,s
;tables.c:134: if (size == 0) return 0;
	tst	36,s
	bne	00102$
	clra
	jmp	00117$
00102$:
;tables.c:135: if (x <= (int16_t)bins[0]) return values[0];
	lda	24,s
	psha
	pulh
	ldx	25,s
	lda	,x
	clrx
	sub	38,s
	txa
	sbc	37,s
	blt	00104$
	tsx
	lda	33,x
	psha
	pulh
	ldx	35,s
	lda	,x
	jmp	00117$
00104$:
;tables.c:136: if (x >= (int16_t)bins[size - 1]) return values[size - 1];
	ldx	36,s
	clrh
	aix	#-1
	pshh
	pula
	sta	17,s
	stx	18,s
	lda	18,s
	add	25,s
	tax
	lda	17,s
	adc	24,s
	psha
	pulh
	lda	,x
	tsx
	sta	15,x
	clrx
	stx	15,s
	tsx
	lda	17,x
	add	34,x
	sta	13,x
	lda	16,x
	adc	33,x
	sta	12,x
	lda	37,x
	sub	15,x
	lda	36,x
	sbc	14,x
	blt	00106$
	lda	12,x
	psha
	pulh
	ldx	14,s
	lda	,x
	jmp	00117$
00106$:
;tables.c:138: for (i = 0; i < size - 1; i++) {
	tsx
	clra
	sta	14,x
	sta	22,x
00115$:
	tsx
	lda	22,x
	sta	9,x
	clra
	sta	8,x
	lda	9,x
	sub	17,x
	lda	8,x
	sbc	16,x
	blt	00162$
	jmp	00110$
00162$:
;tables.c:139: if (x >= (int16_t)bins[i] && x < (int16_t)bins[i + 1]) {
	lda	22,x
	add	24,x
	tax
	lda	#0x00
	adc	24,s
	psha
	pulh
	lda	,x
	tsx
	sta	11,x
	clrx
	stx	11,s
	tsx
	lda	37,x
	sub	11,x
	lda	36,x
	sbc	10,x
	bge	00163$
	jmp	00116$
00163$:
	inc	9,x
	bne	00164$
	inc	8,x
00164$:
	lda	9,x
	add	24,x
	tax
	lda	9,s
	adc	24,s
	psha
	pulh
	lda	,x
	tsx
	sta	19,x
	clrx
	stx	19,s
	tsx
	lda	37,x
	sub	19,x
	lda	36,x
	sbc	18,x
	blt	00165$
	jmp	00116$
00165$:
;tables.c:140: return (int8_t)interpolate(x, bins[i], bins[i + 1], values[i], values[i + 1]);
	lda	9,x
	add	34,x
	tax
	lda	9,s
	adc	34,s
	psha
	pulh
	lda	,x
	tsx
	sta	30,x
	rola	
	clra	
	sbc	#0x00
	sta	29,x
	lda	14,x
	add	34,x
	tax
	lda	#0x00
	adc	34,s
	psha
	pulh
	lda	,x
	tsx
	sta	28,x
	rola	
	clra	
	sbc	#0x00
	sta	27,x
	lda	18,x
	sta	20,x
	lda	19,x
	sta	21,x
	lda	10,x
	sta	25,x
	lda	11,x
	sta	26,x
	ldx	36,x
	lda	38,s
;tables.h:34: if (x2 == x1) return y1;
	psha
	lda	23,s
	cmp	28,s
	pula
	bne	00166$
	psha
	lda	22,s
	cmp	27,s
	pula
	beq	00167$
00166$:
	bra	00112$
00167$:
	tsx
	lda	27,x
	sta	18,x
	lda	28,x
	sta	19,x
	jmp	00113$
00112$:
;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
	sub	27,s
	psha
	txa
	sbc	27,s
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
	lda	31,s
	sub	29,s
	psha
	lda	31,s
	sbc	29,s
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
	lda	22,s
	sub	27,s
	psha
	lda	22,s
	sbc	27,s
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
	add	29,s
	sta	20,s
	txa
	adc	28,s
	sta	19,s
;tables.c:140: return (int8_t)interpolate(x, bins[i], bins[i + 1], values[i], values[i + 1]);
00113$:
	tsx
	lda	19,x
	bra	00117$
00116$:
;tables.c:138: for (i = 0; i < size - 1; i++) {
	tsx
	inc	22,x
	lda	22,x
	sta	14,x
	jmp	00115$
00110$:
;tables.c:143: return values[size - 1];
	lda	13,s
	psha
	pulh
	ldx	14,s
	lda	,x
00117$:
;tables.c:144: }
	ais	#31
	rts
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
