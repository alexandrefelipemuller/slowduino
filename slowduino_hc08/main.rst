                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 4.2.0 #13081 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module main
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
                             19 	.area	CODEIVT (ABS)
   FFFE                      20 	.org	0xfffe
   FFFE 80 00                21 	.dw	__sdcc_gs_init_startup
                             22 
                             23 	.area GSINIT0
   8000                      24 __sdcc_gs_init_startup:
   8000 45 80 00      [ 3]   25 	ldhx	#0x8000
   8003 94            [ 2]   26 	txs
   8004 CD 85 A9      [ 5]   27 	jsr	__sdcc_external_startup
   8007 27 03         [ 3]   28 	beq	__sdcc_init_data
   8009 CC 84 F2      [ 3]   29 	jmp	__sdcc_program_startup
   800C                      30 __sdcc_init_data:
                             31 ; _hc08_genXINIT() start
   800C 45 00 00      [ 3]   32         ldhx #0
   800F                      33 00001$:
   800F 65 00 10      [ 3]   34         cphx #l_XINIT
   8012 27 0A         [ 3]   35         beq  00002$
   8014 D6 85 AB      [ 4]   36         lda  s_XINIT,x
   8017 D7 01 90      [ 4]   37         sta  s_XISEG,x
   801A AF 01         [ 2]   38         aix  #1
   801C 20 F1         [ 3]   39         bra  00001$
   801E                      40 00002$:
                             41 ; _hc08_genXINIT() end
                             42 	.area GSFINAL
   8029 CC 84 F2      [ 3]   43 	jmp	__sdcc_program_startup
                             44 
                             45 	.area CSEG
   84F2                      46 __sdcc_program_startup:
   84F2 CD 85 09      [ 5]   47 	jsr	_main
   84F5 20 FE         [ 3]   48 	bra	.
                             49 ;--------------------------------------------------------
                             50 ; Public variables in this module
                             51 ;--------------------------------------------------------
                             52 	.globl _main
                             53 	.globl _micros
                             54 	.globl _timebaseInit
                             55 	.globl _setIgnitionSchedule
                             56 	.globl _schedulerInit
                             57 ;--------------------------------------------------------
                             58 ; ram data
                             59 ;--------------------------------------------------------
                             60 	.area DSEG    (PAG)
   00A2                      61 _main_sloc0_1_0:
   00A2                      62 	.ds 4
   00A6                      63 _main_sloc1_1_0:
   00A6                      64 	.ds 4
                             65 ;--------------------------------------------------------
                             66 ; overlayable items in ram
                             67 ;--------------------------------------------------------
                             68 	.area	OSEG    (PAG, OVR)
   00B0                      69 _getTimer1Count_sloc0_1_0:
   00B0                      70 	.ds 2
                             71 ;--------------------------------------------------------
                             72 ; absolute ram data
                             73 ;--------------------------------------------------------
                             74 	.area IABS    (ABS)
                             75 	.area IABS    (ABS)
                             76 ;--------------------------------------------------------
                             77 ; absolute external ram data
                             78 ;--------------------------------------------------------
                             79 	.area XABS    (ABS)
                             80 ;--------------------------------------------------------
                             81 ; external initialized ram data
                             82 ;--------------------------------------------------------
                             83 	.area XISEG
                             84 ;--------------------------------------------------------
                             85 ; extended address mode data
                             86 ;--------------------------------------------------------
                             87 	.area XSEG
   018C                      88 _main_lastPulse_196608_11:
   018C                      89 	.ds 4
                             90 ;--------------------------------------------------------
                             91 ; global & static initialisations
                             92 ;--------------------------------------------------------
                             93 	.area HOME    (CODE)
                             94 	.area GSINIT  (CODE)
                             95 	.area GSFINAL (CODE)
                             96 	.area GSINIT  (CODE)
                             97 ;------------------------------------------------------------
                             98 ;Allocation info for local variables in function 'main'
                             99 ;------------------------------------------------------------
                            100 ;sloc0                     Allocated with name '_main_sloc0_1_0'
                            101 ;sloc1                     Allocated with name '_main_sloc1_1_0'
                            102 ;lastPulse                 Allocated with name '_main_lastPulse_196608_11'
                            103 ;now                       Allocated with name '_main_now_196608_11'
                            104 ;------------------------------------------------------------
                            105 ;main.c:25: static uint32_t lastPulse = 0;
   801E 45 01 8C      [ 3]  106 	ldhx	#_main_lastPulse_196608_11
   8021 4F            [ 1]  107 	clra
   8022 F7            [ 2]  108 	sta	,x
   8023 E7 01         [ 3]  109 	sta	1,x
   8025 E7 02         [ 3]  110 	sta	2,x
   8027 E7 03         [ 3]  111 	sta	3,x
                            112 ;--------------------------------------------------------
                            113 ; Home
                            114 ;--------------------------------------------------------
                            115 	.area HOME    (CODE)
                            116 	.area HOME    (CODE)
                            117 ;--------------------------------------------------------
                            118 ; code
                            119 ;--------------------------------------------------------
                            120 	.area CSEG    (CODE)
                            121 ;------------------------------------------------------------
                            122 ;Allocation info for local variables in function 'getTimer1Count'
                            123 ;------------------------------------------------------------
                            124 ;sloc0                     Allocated with name '_getTimer1Count_sloc0_1_0'
                            125 ;------------------------------------------------------------
                            126 ;scheduler.h:54: static inline uint16_t getTimer1Count(void) {
                            127 ;	-----------------------------------------
                            128 ;	 function getTimer1Count
                            129 ;	-----------------------------------------
                            130 ;	Register assignment is optimal.
                            131 ;	Stack space usage: 0 bytes.
   84F7                     132 _getTimer1Count:
                            133 ;scheduler.h:55: return (uint16_t)((T1CNTH << 8) | T1CNTL);
   84F7 B6 21         [ 3]  134 	lda	*0x21
   84F9 5F            [ 1]  135 	clrx
   84FA B7 B0         [ 3]  136 	sta	*_getTimer1Count_sloc0_1_0
   84FC BF B1         [ 3]  137 	stx	*(_getTimer1Count_sloc0_1_0 + 1)
   84FE B6 22         [ 3]  138 	lda	*0x22
   8500 BA B1         [ 3]  139 	ora	*(_getTimer1Count_sloc0_1_0 + 1)
   8502 87            [ 2]  140 	psha
   8503 9F            [ 1]  141 	txa
   8504 BA B0         [ 3]  142 	ora	*_getTimer1Count_sloc0_1_0
   8506 97            [ 1]  143 	tax
   8507 86            [ 2]  144 	pula
                            145 ;scheduler.h:56: }
   8508 81            [ 4]  146 	rts
                            147 ;------------------------------------------------------------
                            148 ;Allocation info for local variables in function 'main'
                            149 ;------------------------------------------------------------
                            150 ;sloc0                     Allocated with name '_main_sloc0_1_0'
                            151 ;sloc1                     Allocated with name '_main_sloc1_1_0'
                            152 ;lastPulse                 Allocated with name '_main_lastPulse_196608_11'
                            153 ;now                       Allocated with name '_main_now_196608_11'
                            154 ;------------------------------------------------------------
                            155 ;main.c:16: int main(void) {
                            156 ;	-----------------------------------------
                            157 ;	 function main
                            158 ;	-----------------------------------------
                            159 ;	Register assignment is optimal.
                            160 ;	Stack space usage: 0 bytes.
   8509                     161 _main:
                            162 ;main.c:17: timebaseInit();
   8509 CD 80 2C      [ 5]  163 	jsr	_timebaseInit
                            164 ;main.c:18: schedulerInit();
   850C CD 81 30      [ 5]  165 	jsr	_schedulerInit
                            166 ;main.c:20: __asm cli __endasm; /* habilita interrupcoes (equivalente a sei() do AVR) */
   850F 9A            [ 2]  167 	 cli	
                            168 ;main.c:22: currentStatus.RPM = 0;
   8510 4F            [ 1]  169 	clra
   8511 C7 00 BA      [ 4]  170 	sta	_currentStatus
   8514 C7 00 BB      [ 4]  171 	sta	(_currentStatus + 1)
   8517                     172 00104$:
                            173 ;main.c:26: uint32_t now = micros();
   8517 CD 80 3E      [ 5]  174 	jsr	_micros
   851A B7 A5         [ 3]  175 	sta	*(_main_sloc0_1_0 + 3)
   851C BF A4         [ 3]  176 	stx	*(_main_sloc0_1_0 + 2)
   851E 4E AA A3      [ 5]  177 	mov	*___SDCC_hc08_ret2,*(_main_sloc0_1_0 + 1)
   8521 4E AB A2      [ 5]  178 	mov	*___SDCC_hc08_ret3,*_main_sloc0_1_0
                            179 ;main.c:28: if ((uint32_t)(now - lastPulse) >= 20000UL) {  /* ~50Hz, so para teste */
   8524 45 01 8C      [ 3]  180 	ldhx	#_main_lastPulse_196608_11
   8527 B6 A5         [ 3]  181 	lda	*(_main_sloc0_1_0 + 3)
   8529 E0 03         [ 3]  182 	sub	3,x
   852B B7 A9         [ 3]  183 	sta	*(_main_sloc1_1_0 + 3)
   852D B6 A4         [ 3]  184 	lda	*(_main_sloc0_1_0 + 2)
   852F E2 02         [ 3]  185 	sbc	2,x
   8531 B7 A8         [ 3]  186 	sta	*(_main_sloc1_1_0 + 2)
   8533 B6 A3         [ 3]  187 	lda	*(_main_sloc0_1_0 + 1)
   8535 E2 01         [ 3]  188 	sbc	1,x
   8537 B7 A7         [ 3]  189 	sta	*(_main_sloc1_1_0 + 1)
   8539 B6 A2         [ 3]  190 	lda	*_main_sloc0_1_0
   853B F2            [ 2]  191 	sbc	,x
   853C B7 A6         [ 3]  192 	sta	*_main_sloc1_1_0
   853E B6 A9         [ 3]  193 	lda	*(_main_sloc1_1_0 + 3)
   8540 A0 20         [ 2]  194 	sub	#0x20
   8542 B6 A8         [ 3]  195 	lda	*(_main_sloc1_1_0 + 2)
   8544 A2 4E         [ 2]  196 	sbc	#0x4e
   8546 B6 A7         [ 3]  197 	lda	*(_main_sloc1_1_0 + 1)
   8548 A2 00         [ 2]  198 	sbc	#0x00
   854A B6 A6         [ 3]  199 	lda	*_main_sloc1_1_0
   854C A2 00         [ 2]  200 	sbc	#0x00
   854E 25 C7         [ 3]  201 	bcs	00104$
                            202 ;main.c:29: lastPulse = now;
   8550 45 01 8C      [ 3]  203 	ldhx	#_main_lastPulse_196608_11
   8553 5E A2         [ 4]  204 	mov	*_main_sloc0_1_0,x+
   8555 5E A3         [ 4]  205 	mov	*(_main_sloc0_1_0 + 1),x+
   8557 5E A4         [ 4]  206 	mov	*(_main_sloc0_1_0 + 2),x+
   8559 5E A5         [ 4]  207 	mov	*(_main_sloc0_1_0 + 3),x+
                            208 ;main.c:30: setIgnitionSchedule(&ignitionSchedule1, 2000, 2500, 1);
   855B 45 01 73      [ 3]  209 	ldhx	#_setIgnitionSchedule_PARM_2
   855E 4F            [ 1]  210 	clra
   855F F7            [ 2]  211 	sta	,x
   8560 E7 01         [ 3]  212 	sta	1,x
   8562 A6 07         [ 2]  213 	lda	#0x07
   8564 E7 02         [ 3]  214 	sta	2,x
   8566 A6 D0         [ 2]  215 	lda	#0xd0
   8568 E7 03         [ 3]  216 	sta	3,x
   856A A6 09         [ 2]  217 	lda	#0x09
   856C C7 01 77      [ 4]  218 	sta	_setIgnitionSchedule_PARM_3
   856F A6 C4         [ 2]  219 	lda	#0xc4
   8571 C7 01 78      [ 4]  220 	sta	(_setIgnitionSchedule_PARM_3 + 1)
   8574 A6 01         [ 2]  221 	lda	#0x01
   8576 C7 01 79      [ 4]  222 	sta	_setIgnitionSchedule_PARM_4
   8579 A6 90         [ 2]  223 	lda	#_ignitionSchedule1
   857B AE 01         [ 2]  224 	ldx	#>_ignitionSchedule1
   857D CD 82 6D      [ 5]  225 	jsr	_setIgnitionSchedule
                            226 ;main.c:31: setIgnitionSchedule(&ignitionSchedule2, 2000, 2500, 2);
   8580 45 01 73      [ 3]  227 	ldhx	#_setIgnitionSchedule_PARM_2
   8583 4F            [ 1]  228 	clra
   8584 F7            [ 2]  229 	sta	,x
   8585 E7 01         [ 3]  230 	sta	1,x
   8587 A6 07         [ 2]  231 	lda	#0x07
   8589 E7 02         [ 3]  232 	sta	2,x
   858B A6 D0         [ 2]  233 	lda	#0xd0
   858D E7 03         [ 3]  234 	sta	3,x
   858F A6 09         [ 2]  235 	lda	#0x09
   8591 C7 01 77      [ 4]  236 	sta	_setIgnitionSchedule_PARM_3
   8594 A6 C4         [ 2]  237 	lda	#0xc4
   8596 C7 01 78      [ 4]  238 	sta	(_setIgnitionSchedule_PARM_3 + 1)
   8599 A6 02         [ 2]  239 	lda	#0x02
   859B C7 01 79      [ 4]  240 	sta	_setIgnitionSchedule_PARM_4
   859E A6 98         [ 2]  241 	lda	#_ignitionSchedule2
   85A0 AE 01         [ 2]  242 	ldx	#>_ignitionSchedule2
   85A2 CD 82 6D      [ 5]  243 	jsr	_setIgnitionSchedule
   85A5 CC 85 17      [ 3]  244 	jmp	00104$
                            245 ;main.c:35: return 0;
                            246 ;main.c:36: }
   85A8 81            [ 4]  247 	rts
                            248 	.area CSEG    (CODE)
                            249 	.area CONST   (CODE)
                            250 	.area XINIT   (CODE)
                            251 	.area CABS    (ABS,CODE)
