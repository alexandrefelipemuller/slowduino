                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 4.2.0 #13081 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module storage
                              6 	.optsdcc -mhc08
                              7 	
                              8 	.area HOME    (CODE)
                              9 	.area GSINIT0 (CODE)
                             10 	.area GSINIT  (CODE)
                             11 	.area GSFINAL (CODE)
                             12 	.area CSEG    (CODE)
                             13 	.area XINIT   (CODE)
                             14 	.area CONST   (CODE)
                             15 	.area DSEG    (PAG)
                             16 	.area OSEG    (PAG, OVR)
                             17 	.area XSEG
                             18 	.area XISEG
                             19 ;--------------------------------------------------------
                             20 ; Public variables in this module
                             21 ;--------------------------------------------------------
                             22 	.globl _eepromReadByte
                             23 	.globl _eepromReadI8
                             24 	.globl _eepromWriteByte
                             25 	.globl _eepromWriteI8
                             26 	.globl _saveAllConfig
                             27 ;--------------------------------------------------------
                             28 ; ram data
                             29 ;--------------------------------------------------------
                             30 	.area DSEG    (PAG)
                             31 ;--------------------------------------------------------
                             32 ; overlayable items in ram
                             33 ;--------------------------------------------------------
                             34 ;--------------------------------------------------------
                             35 ; absolute ram data
                             36 ;--------------------------------------------------------
                             37 	.area IABS    (ABS)
                             38 	.area IABS    (ABS)
                             39 ;--------------------------------------------------------
                             40 ; absolute external ram data
                             41 ;--------------------------------------------------------
                             42 	.area XABS    (ABS)
                             43 ;--------------------------------------------------------
                             44 ; external initialized ram data
                             45 ;--------------------------------------------------------
                             46 	.area XISEG
                             47 ;--------------------------------------------------------
                             48 ; extended address mode data
                             49 ;--------------------------------------------------------
                             50 	.area XSEG
                             51 ;--------------------------------------------------------
                             52 ; global & static initialisations
                             53 ;--------------------------------------------------------
                             54 	.area HOME    (CODE)
                             55 	.area GSINIT  (CODE)
                             56 	.area GSFINAL (CODE)
                             57 	.area GSINIT  (CODE)
                             58 ;--------------------------------------------------------
                             59 ; Home
                             60 ;--------------------------------------------------------
                             61 	.area HOME    (CODE)
                             62 	.area HOME    (CODE)
                             63 ;--------------------------------------------------------
                             64 ; code
                             65 ;--------------------------------------------------------
                             66 	.area CSEG    (CODE)
                             67 ;------------------------------------------------------------
                             68 ;Allocation info for local variables in function 'eepromReadByte'
                             69 ;------------------------------------------------------------
                             70 ;address                   Allocated to registers 
                             71 ;------------------------------------------------------------
                             72 ;storage.c:8: uint8_t eepromReadByte(uint16_t address) {
                             73 ;	-----------------------------------------
                             74 ;	 function eepromReadByte
                             75 ;	-----------------------------------------
                             76 ;	Register assignment is optimal.
                             77 ;	Stack space usage: 0 bytes.
   976A                      78 _eepromReadByte:
                             79 ;storage.c:10: return 128;  /* placeholder neutro - nao e dado real de tabela */
   976A A6 80         [ 2]   80 	lda	#0x80
                             81 ;storage.c:11: }
   976C 81            [ 4]   82 	rts
                             83 ;------------------------------------------------------------
                             84 ;Allocation info for local variables in function 'eepromReadI8'
                             85 ;------------------------------------------------------------
                             86 ;address                   Allocated to registers 
                             87 ;------------------------------------------------------------
                             88 ;storage.c:13: int8_t eepromReadI8(uint16_t address) {
                             89 ;	-----------------------------------------
                             90 ;	 function eepromReadI8
                             91 ;	-----------------------------------------
                             92 ;	Register assignment is optimal.
                             93 ;	Stack space usage: 0 bytes.
   976D                      94 _eepromReadI8:
                             95 ;storage.c:15: return 0;  /* placeholder neutro */
   976D 4F            [ 1]   96 	clra
                             97 ;storage.c:16: }
   976E 81            [ 4]   98 	rts
                             99 ;------------------------------------------------------------
                            100 ;Allocation info for local variables in function 'eepromWriteByte'
                            101 ;------------------------------------------------------------
                            102 ;value                     Allocated to stack - sp +3
                            103 ;address                   Allocated to registers 
                            104 ;------------------------------------------------------------
                            105 ;storage.c:18: bool eepromWriteByte(uint16_t address, uint8_t value) {
                            106 ;	-----------------------------------------
                            107 ;	 function eepromWriteByte
                            108 ;	-----------------------------------------
                            109 ;	Register assignment is optimal.
                            110 ;	Stack space usage: 0 bytes.
   976F                     111 _eepromWriteByte:
                            112 ;storage.c:21: return false;  /* placeholder - nao escreve nada de verdade ainda */
   976F 4F            [ 1]  113 	clra
                            114 ;storage.c:22: }
   9770 81            [ 4]  115 	rts
                            116 ;------------------------------------------------------------
                            117 ;Allocation info for local variables in function 'eepromWriteI8'
                            118 ;------------------------------------------------------------
                            119 ;value                     Allocated to stack - sp +3
                            120 ;address                   Allocated to registers 
                            121 ;------------------------------------------------------------
                            122 ;storage.c:24: void eepromWriteI8(uint16_t address, int8_t value) {
                            123 ;	-----------------------------------------
                            124 ;	 function eepromWriteI8
                            125 ;	-----------------------------------------
                            126 ;	Register assignment is optimal.
                            127 ;	Stack space usage: 0 bytes.
   9771                     128 _eepromWriteI8:
                            129 ;storage.c:26: (void)value;
                            130 ;storage.c:27: }
   9771 81            [ 4]  131 	rts
                            132 ;------------------------------------------------------------
                            133 ;Allocation info for local variables in function 'saveAllConfig'
                            134 ;------------------------------------------------------------
                            135 ;storage.c:29: void saveAllConfig(void) {
                            136 ;	-----------------------------------------
                            137 ;	 function saveAllConfig
                            138 ;	-----------------------------------------
                            139 ;	Register assignment is optimal.
                            140 ;	Stack space usage: 0 bytes.
   9772                     141 _saveAllConfig:
                            142 ;storage.c:31: }
   9772 81            [ 4]  143 	rts
                            144 	.area CSEG    (CODE)
                            145 	.area CONST   (CODE)
                            146 	.area XINIT   (CODE)
                            147 	.area CABS    (ABS,CODE)
