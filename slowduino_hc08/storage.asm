;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.2.0 #13081 (Linux)
;--------------------------------------------------------
	.module storage
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
	.globl _eepromReadByte
	.globl _eepromReadI8
	.globl _eepromWriteByte
	.globl _eepromWriteI8
	.globl _saveAllConfig
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
;Allocation info for local variables in function 'eepromReadByte'
;------------------------------------------------------------
;address                   Allocated to registers 
;------------------------------------------------------------
;storage.c:8: uint8_t eepromReadByte(uint16_t address) {
;	-----------------------------------------
;	 function eepromReadByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_eepromReadByte:
;storage.c:10: return 128;  /* placeholder neutro - nao e dado real de tabela */
	lda	#0x80
;storage.c:11: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'eepromReadI8'
;------------------------------------------------------------
;address                   Allocated to registers 
;------------------------------------------------------------
;storage.c:13: int8_t eepromReadI8(uint16_t address) {
;	-----------------------------------------
;	 function eepromReadI8
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_eepromReadI8:
;storage.c:15: return 0;  /* placeholder neutro */
	clra
;storage.c:16: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'eepromWriteByte'
;------------------------------------------------------------
;value                     Allocated to stack - sp +3
;address                   Allocated to registers 
;------------------------------------------------------------
;storage.c:18: bool eepromWriteByte(uint16_t address, uint8_t value) {
;	-----------------------------------------
;	 function eepromWriteByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_eepromWriteByte:
;storage.c:21: return false;  /* placeholder - nao escreve nada de verdade ainda */
	clra
;storage.c:22: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'eepromWriteI8'
;------------------------------------------------------------
;value                     Allocated to stack - sp +3
;address                   Allocated to registers 
;------------------------------------------------------------
;storage.c:24: void eepromWriteI8(uint16_t address, int8_t value) {
;	-----------------------------------------
;	 function eepromWriteI8
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_eepromWriteI8:
;storage.c:26: (void)value;
;storage.c:27: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'saveAllConfig'
;------------------------------------------------------------
;storage.c:29: void saveAllConfig(void) {
;	-----------------------------------------
;	 function saveAllConfig
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_saveAllConfig:
;storage.c:31: }
	rts
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
