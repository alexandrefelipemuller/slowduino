;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.2.0 #13081 (Linux)
;--------------------------------------------------------
	.module serial_hc08
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
	.globl _sciInit
	.globl _sciAvailable
	.globl _sciReadByte
	.globl _sciWriteByte
	.globl _sciWriteBytes
	.globl _sciPrintString
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
;Allocation info for local variables in function 'sciInit'
;------------------------------------------------------------
;serial_hc08.c:9: void sciInit(void) {
;	-----------------------------------------
;	 function sciInit
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sciInit:
;serial_hc08.c:16: SCBR = 0x00;
	mov	#0x00,*0x19
;serial_hc08.c:19: SCC2 |= (1 << SCC2_TE) | (1 << SCC2_RE);
	lda	*0x14
	ora	#0x0c
	sta	*0x14
;serial_hc08.c:22: SCC1 |= (1 << SCC1_ENSCI);
	lda	*0x13
	ora	#0x40
	sta	*0x13
;serial_hc08.c:23: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'sciAvailable'
;------------------------------------------------------------
;serial_hc08.c:25: bool sciAvailable(void) {
;	-----------------------------------------
;	 function sciAvailable
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sciAvailable:
;serial_hc08.c:26: return (SCS1 & (1 << SCS1_SCRF)) != 0;
	lda	*0x16
	and	#0x20
	nega
	clra
	rola
	eor	#0x01
	eor	#0x01
;serial_hc08.c:27: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'sciReadByte'
;------------------------------------------------------------
;serial_hc08.c:29: uint8_t sciReadByte(void) {
;	-----------------------------------------
;	 function sciReadByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sciReadByte:
;serial_hc08.c:33: return SCDR;
	lda	*0x18
;serial_hc08.c:34: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'sciWriteByte'
;------------------------------------------------------------
;data                      Allocated to registers a 
;------------------------------------------------------------
;serial_hc08.c:36: void sciWriteByte(uint8_t data) {
;	-----------------------------------------
;	 function sciWriteByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sciWriteByte:
;serial_hc08.c:39: while ((SCS1 & (1 << SCS1_SCTE)) == 0) {
00101$:
	ldx	*0x16
	bpl     00101$
;serial_hc08.c:42: SCDR = data;
	sta	*0x18
;serial_hc08.c:43: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'sciWriteBytes'
;------------------------------------------------------------
;length                    Allocated to stack - sp +7
;data                      Allocated to stack - sp +3
;i                         Allocated to registers x h 
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;serial_hc08.c:45: void sciWriteBytes(const uint8_t *data, uint16_t length) {
;	-----------------------------------------
;	 function sciWriteBytes
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 4 bytes.
_sciWriteBytes:
	psha
	pshx
	ais	#-2
;serial_hc08.c:47: for (i = 0; i < length; i++) {
	clrh
	clrx
00103$:
	txa
	sub	8,s
	pshh
	pula
	sbc	7,s
	bcc	00105$
;serial_hc08.c:48: sciWriteByte(data[i]);
	txa
	add	4,s
	sta	2,s
	pshh
	pula
	adc	3,s
	sta	1,s
	pshx
	pshh
	lda	3,s
	psha
	pulh
	ldx	4,s
	lda	,x
	pulh
	pulx
	pshx
	pshh
	jsr	_sciWriteByte
	pulh
	pulx
;serial_hc08.c:47: for (i = 0; i < length; i++) {
	aix	#1
	bra	00103$
00105$:
;serial_hc08.c:50: }
	ais	#4
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'sciPrintString'
;------------------------------------------------------------
;str                       Allocated to registers 
;------------------------------------------------------------
;serial_hc08.c:52: void sciPrintString(const char *str) {
;	-----------------------------------------
;	 function sciPrintString
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sciPrintString:
	pshx
	tax
	pulh
;serial_hc08.c:53: while (*str != '\0') {
00101$:
	lda	,x
	tsta
	beq	00104$
;serial_hc08.c:54: sciWriteByte((uint8_t)*str);
	pshx
	pshh
	jsr	_sciWriteByte
	pulh
	pulx
;serial_hc08.c:55: str++;
	aix	#1
	bra	00101$
00104$:
;serial_hc08.c:57: }
	rts
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
