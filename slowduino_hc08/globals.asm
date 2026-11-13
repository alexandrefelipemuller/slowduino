;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.2.0 #13081 (Linux)
;--------------------------------------------------------
	.module globals
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
	.globl _configPage2
	.globl _configPage1
	.globl _currentStatus
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
_currentStatus::
	.ds 61
_configPage1::
	.ds 30
_configPage2::
	.ds 32
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
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
