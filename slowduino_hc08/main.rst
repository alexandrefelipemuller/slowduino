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
   8000 45 02 40      [ 3]   25 	ldhx	#0x0240
   8003 94            [ 2]   26 	txs
   8004 CD CE 63      [ 5]   27 	jsr	__sdcc_external_startup
   8007 27 03         [ 3]   28 	beq	__sdcc_init_data
   8009 CC CC 21      [ 3]   29 	jmp	__sdcc_program_startup
   800C                      30 __sdcc_init_data:
                             31 ; _hc08_genXINIT() start
   800C 45 00 00      [ 3]   32         ldhx #0
   800F                      33 00001$:
   800F 65 00 17      [ 3]   34         cphx #l_XINIT
   8012 27 0A         [ 3]   35         beq  00002$
   8014 D6 D2 3B      [ 4]   36         lda  s_XINIT,x
   8017 D7 01 C3      [ 4]   37         sta  s_XISEG,x
   801A AF 01         [ 2]   38         aix  #1
   801C 20 F1         [ 3]   39         bra  00001$
   801E                      40 00002$:
                             41 ; _hc08_genXINIT() end
                             42 	.area GSFINAL
   8032 CC CC 21      [ 3]   43 	jmp	__sdcc_program_startup
                             44 
                             45 	.area CSEG
   CC21                      46 __sdcc_program_startup:
   CC21 CD CD 2D      [ 5]   47 	jsr	_main
   CC24 20 FE         [ 3]   48 	bra	.
                             49 ;--------------------------------------------------------
                             50 ; Public variables in this module
                             51 ;--------------------------------------------------------
                             52 	.globl _main
                             53 	.globl _commsProcess
                             54 	.globl _commsInit
                             55 	.globl _calculateDwell
                             56 	.globl _calculateAdvance
                             57 	.globl _updateEngineStatus
                             58 	.globl _calculateInjection
                             59 	.globl _initTables
                             60 	.globl _micros
                             61 	.globl _timebaseInit
                             62 	.globl _checkSyncLoss
                             63 	.globl _calculateRPM
                             64 	.globl _triggerInit
                             65 	.globl _processInjectorPolling
                             66 	.globl _schedulerInit
                             67 ;--------------------------------------------------------
                             68 ; ram data
                             69 ;--------------------------------------------------------
                             70 	.area DSEG    (PAG)
                             71 ;--------------------------------------------------------
                             72 ; overlayable items in ram
                             73 ;--------------------------------------------------------
                             74 ;--------------------------------------------------------
                             75 ; absolute ram data
                             76 ;--------------------------------------------------------
                             77 	.area IABS    (ABS)
                             78 	.area IABS    (ABS)
                             79 ;--------------------------------------------------------
                             80 ; absolute external ram data
                             81 ;--------------------------------------------------------
                             82 	.area XABS    (ABS)
                             83 ;--------------------------------------------------------
                             84 ; external initialized ram data
                             85 ;--------------------------------------------------------
                             86 	.area XISEG
                             87 ;--------------------------------------------------------
                             88 ; extended address mode data
                             89 ;--------------------------------------------------------
                             90 	.area XSEG
   018F                      91 _main_lastLoop67Hz_196608_76:
   018F                      92 	.ds 4
                             93 ;--------------------------------------------------------
                             94 ; global & static initialisations
                             95 ;--------------------------------------------------------
                             96 	.area HOME    (CODE)
                             97 	.area GSINIT  (CODE)
                             98 	.area GSFINAL (CODE)
                             99 	.area GSINIT  (CODE)
                            100 ;------------------------------------------------------------
                            101 ;Allocation info for local variables in function 'main'
                            102 ;------------------------------------------------------------
                            103 ;now                       Allocated to stack - sp +2
                            104 ;newPW1                    Allocated to stack - sp +4
                            105 ;newAdvance                Allocated to stack - sp +3
                            106 ;newDwell                  Allocated to registers x h 
                            107 ;sloc0                     Allocated to stack - sp -5
                            108 ;sloc1                     Allocated to stack - sp -1
                            109 ;lastLoop67Hz              Allocated with name '_main_lastLoop67Hz_196608_76'
                            110 ;------------------------------------------------------------
                            111 ;main.c:29: static uint32_t lastLoop67Hz = 0;
   8027 45 01 8F      [ 3]  112 	ldhx	#_main_lastLoop67Hz_196608_76
   802A 4F            [ 1]  113 	clra
   802B F7            [ 2]  114 	sta	,x
   802C E7 01         [ 3]  115 	sta	1,x
   802E E7 02         [ 3]  116 	sta	2,x
   8030 E7 03         [ 3]  117 	sta	3,x
                            118 ;--------------------------------------------------------
                            119 ; Home
                            120 ;--------------------------------------------------------
                            121 	.area HOME    (CODE)
                            122 	.area HOME    (CODE)
                            123 ;--------------------------------------------------------
                            124 ; code
                            125 ;--------------------------------------------------------
                            126 	.area CSEG    (CODE)
                            127 ;------------------------------------------------------------
                            128 ;Allocation info for local variables in function 'noInterrupts'
                            129 ;------------------------------------------------------------
                            130 ;globals.h:100: static inline void noInterrupts(void) { __asm sei __endasm; }
                            131 ;	-----------------------------------------
                            132 ;	 function noInterrupts
                            133 ;	-----------------------------------------
                            134 ;	Register assignment is optimal.
                            135 ;	Stack space usage: 0 bytes.
   CC26                     136 _noInterrupts:
   CC26 9B            [ 2]  137 	 sei	
   CC27 81            [ 4]  138 	rts
                            139 ;------------------------------------------------------------
                            140 ;Allocation info for local variables in function 'interrupts'
                            141 ;------------------------------------------------------------
                            142 ;globals.h:101: static inline void interrupts(void)   { __asm cli __endasm; }
                            143 ;	-----------------------------------------
                            144 ;	 function interrupts
                            145 ;	-----------------------------------------
                            146 ;	Register assignment is optimal.
                            147 ;	Stack space usage: 0 bytes.
   CC28                     148 _interrupts:
   CC28 9A            [ 2]  149 	 cli	
   CC29 81            [ 4]  150 	rts
                            151 ;------------------------------------------------------------
                            152 ;Allocation info for local variables in function 'getTimer1Count'
                            153 ;------------------------------------------------------------
                            154 ;sloc0                     Allocated to stack - sp +1
                            155 ;------------------------------------------------------------
                            156 ;scheduler.h:55: static inline uint16_t getTimer1Count(void) {
                            157 ;	-----------------------------------------
                            158 ;	 function getTimer1Count
                            159 ;	-----------------------------------------
                            160 ;	Register assignment is optimal.
                            161 ;	Stack space usage: 2 bytes.
   CC2A                     162 _getTimer1Count:
   CC2A A7 FE         [ 2]  163 	ais	#-2
                            164 ;scheduler.h:56: return (uint16_t)((T1CNTH << 8) | T1CNTL);
   CC2C B6 21         [ 3]  165 	lda	*0x21
   CC2E 5F            [ 1]  166 	clrx
   CC2F 9E E7 01      [ 4]  167 	sta	1,s
   CC32 9E EF 02      [ 4]  168 	stx	2,s
   CC35 B6 22         [ 3]  169 	lda	*0x22
   CC37 9E EA 02      [ 4]  170 	ora	2,s
   CC3A 87            [ 2]  171 	psha
   CC3B 9F            [ 1]  172 	txa
   CC3C 9E EA 02      [ 4]  173 	ora	2,s
   CC3F 97            [ 1]  174 	tax
   CC40 86            [ 2]  175 	pula
                            176 ;scheduler.h:57: }
   CC41 A7 02         [ 2]  177 	ais	#2
   CC43 81            [ 4]  178 	rts
                            179 ;------------------------------------------------------------
                            180 ;Allocation info for local variables in function 'interpolate'
                            181 ;------------------------------------------------------------
                            182 ;x1                        Allocated to stack - sp +11
                            183 ;x2                        Allocated to stack - sp +13
                            184 ;y1                        Allocated to stack - sp +15
                            185 ;y2                        Allocated to stack - sp +17
                            186 ;x                         Allocated to registers a x 
                            187 ;sloc0                     Allocated to stack - sp +5
                            188 ;sloc1                     Allocated to stack - sp +1
                            189 ;------------------------------------------------------------
                            190 ;tables.h:33: static inline int16_t interpolate(int16_t x, int16_t x1, int16_t x2, int16_t y1, int16_t y2) {
                            191 ;	-----------------------------------------
                            192 ;	 function interpolate
                            193 ;	-----------------------------------------
                            194 ;	Register assignment might be sub-optimal.
                            195 ;	Stack space usage: 8 bytes.
   CC44                     196 _interpolate:
   CC44 A7 F8         [ 2]  197 	ais	#-8
                            198 ;tables.h:34: if (x2 == x1) return y1;
   CC46 87            [ 2]  199 	psha
   CC47 9E E6 0F      [ 4]  200 	lda	15,s
   CC4A 9E E1 0D      [ 4]  201 	cmp	13,s
   CC4D 86            [ 2]  202 	pula
   CC4E 26 0A         [ 3]  203 	bne	00110$
   CC50 87            [ 2]  204 	psha
   CC51 9E E6 0E      [ 4]  205 	lda	14,s
   CC54 9E E1 0C      [ 4]  206 	cmp	12,s
   CC57 86            [ 2]  207 	pula
   CC58 27 02         [ 3]  208 	beq	00111$
   CC5A                     209 00110$:
   CC5A 20 09         [ 3]  210 	bra	00102$
   CC5C                     211 00111$:
   CC5C 95            [ 2]  212 	tsx
   CC5D EE 0E         [ 3]  213 	ldx	14,x
   CC5F 9E E6 10      [ 4]  214 	lda	16,s
   CC62 CC CD 2A      [ 3]  215 	jmp	00103$
   CC65                     216 00102$:
                            217 ;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
   CC65 9E E0 0C      [ 4]  218 	sub	12,s
   CC68 87            [ 2]  219 	psha
   CC69 9F            [ 1]  220 	txa
   CC6A 9E E2 0C      [ 4]  221 	sbc	12,s
   CC6D 97            [ 1]  222 	tax
   CC6E 86            [ 2]  223 	pula
   CC6F 9E E7 08      [ 4]  224 	sta	8,s
   CC72 9F            [ 1]  225 	txa
   CC73 9E E7 07      [ 4]  226 	sta	7,s
   CC76 49            [ 1]  227 	rola	
   CC77 4F            [ 1]  228 	clra	
   CC78 A2 00         [ 2]  229 	sbc	#0x00
   CC7A 9E E7 06      [ 4]  230 	sta	6,s
   CC7D 9E E7 05      [ 4]  231 	sta	5,s
   CC80 9E E6 12      [ 4]  232 	lda	18,s
   CC83 9E E0 10      [ 4]  233 	sub	16,s
   CC86 87            [ 2]  234 	psha
   CC87 9E E6 12      [ 4]  235 	lda	18,s
   CC8A 9E E2 10      [ 4]  236 	sbc	16,s
   CC8D 97            [ 1]  237 	tax
   CC8E 86            [ 2]  238 	pula
   CC8F 9E E7 04      [ 4]  239 	sta	4,s
   CC92 9F            [ 1]  240 	txa
   CC93 9E E7 03      [ 4]  241 	sta	3,s
   CC96 49            [ 1]  242 	rola	
   CC97 4F            [ 1]  243 	clra	
   CC98 A2 00         [ 2]  244 	sbc	#0x00
   CC9A 9E E7 02      [ 4]  245 	sta	2,s
   CC9D 9E E7 01      [ 4]  246 	sta	1,s
   CCA0 95            [ 2]  247 	tsx
   CCA1 E6 03         [ 3]  248 	lda	3,x
   CCA3 87            [ 2]  249 	psha
   CCA4 E6 02         [ 3]  250 	lda	2,x
   CCA6 87            [ 2]  251 	psha
   CCA7 E6 01         [ 3]  252 	lda	1,x
   CCA9 87            [ 2]  253 	psha
   CCAA F6            [ 2]  254 	lda	,x
   CCAB 87            [ 2]  255 	psha
   CCAC E6 07         [ 3]  256 	lda	7,x
   CCAE 87            [ 2]  257 	psha
   CCAF E6 06         [ 3]  258 	lda	6,x
   CCB1 87            [ 2]  259 	psha
   CCB2 E6 05         [ 3]  260 	lda	5,x
   CCB4 87            [ 2]  261 	psha
   CCB5 E6 04         [ 3]  262 	lda	4,x
   CCB7 87            [ 2]  263 	psha
   CCB8 CD D0 87      [ 5]  264 	jsr	__mullong
   CCBB 9E E7 0C      [ 4]  265 	sta	12,s
   CCBE 9E EF 0B      [ 4]  266 	stx	11,s
   CCC1 B6 4A         [ 3]  267 	lda	*___SDCC_hc08_ret2
   CCC3 9E E7 0A      [ 4]  268 	sta	10,s
   CCC6 B6 4B         [ 3]  269 	lda	*___SDCC_hc08_ret3
   CCC8 9E E7 09      [ 4]  270 	sta	9,s
   CCCB A7 08         [ 2]  271 	ais	#8
   CCCD 9E E6 0E      [ 4]  272 	lda	14,s
   CCD0 9E E0 0C      [ 4]  273 	sub	12,s
   CCD3 87            [ 2]  274 	psha
   CCD4 9E E6 0E      [ 4]  275 	lda	14,s
   CCD7 9E E2 0C      [ 4]  276 	sbc	12,s
   CCDA 97            [ 1]  277 	tax
   CCDB 86            [ 2]  278 	pula
   CCDC 9E E7 08      [ 4]  279 	sta	8,s
   CCDF 9F            [ 1]  280 	txa
   CCE0 9E E7 07      [ 4]  281 	sta	7,s
   CCE3 49            [ 1]  282 	rola	
   CCE4 4F            [ 1]  283 	clra	
   CCE5 A2 00         [ 2]  284 	sbc	#0x00
   CCE7 9E E7 06      [ 4]  285 	sta	6,s
   CCEA 9E E7 05      [ 4]  286 	sta	5,s
   CCED 95            [ 2]  287 	tsx
   CCEE E6 07         [ 3]  288 	lda	7,x
   CCF0 87            [ 2]  289 	psha
   CCF1 E6 06         [ 3]  290 	lda	6,x
   CCF3 87            [ 2]  291 	psha
   CCF4 E6 05         [ 3]  292 	lda	5,x
   CCF6 87            [ 2]  293 	psha
   CCF7 E6 04         [ 3]  294 	lda	4,x
   CCF9 87            [ 2]  295 	psha
   CCFA E6 03         [ 3]  296 	lda	3,x
   CCFC 87            [ 2]  297 	psha
   CCFD E6 02         [ 3]  298 	lda	2,x
   CCFF 87            [ 2]  299 	psha
   CD00 E6 01         [ 3]  300 	lda	1,x
   CD02 87            [ 2]  301 	psha
   CD03 F6            [ 2]  302 	lda	,x
   CD04 87            [ 2]  303 	psha
   CD05 CD CE 92      [ 5]  304 	jsr	__divslong
   CD08 9E E7 0C      [ 4]  305 	sta	12,s
   CD0B 9E EF 0B      [ 4]  306 	stx	11,s
   CD0E B6 4A         [ 3]  307 	lda	*___SDCC_hc08_ret2
   CD10 9E E7 0A      [ 4]  308 	sta	10,s
   CD13 B6 4B         [ 3]  309 	lda	*___SDCC_hc08_ret3
   CD15 9E E7 09      [ 4]  310 	sta	9,s
   CD18 A7 08         [ 2]  311 	ais	#8
   CD1A 9E E6 04      [ 4]  312 	lda	4,s
   CD1D 9E EE 03      [ 4]  313 	ldx	3,s
   CD20 9E EB 10      [ 4]  314 	add	16,s
   CD23 87            [ 2]  315 	psha
   CD24 9F            [ 1]  316 	txa
   CD25 9E E9 10      [ 4]  317 	adc	16,s
   CD28 97            [ 1]  318 	tax
   CD29 86            [ 2]  319 	pula
   CD2A                     320 00103$:
                            321 ;tables.h:36: }
   CD2A A7 08         [ 2]  322 	ais	#8
   CD2C 81            [ 4]  323 	rts
                            324 ;------------------------------------------------------------
                            325 ;Allocation info for local variables in function 'main'
                            326 ;------------------------------------------------------------
                            327 ;now                       Allocated to stack - sp +8
                            328 ;newPW1                    Allocated to stack - sp +10
                            329 ;newAdvance                Allocated to stack - sp +9
                            330 ;newDwell                  Allocated to registers x h 
                            331 ;sloc0                     Allocated to stack - sp +1
                            332 ;sloc1                     Allocated to stack - sp +5
                            333 ;lastLoop67Hz              Allocated with name '_main_lastLoop67Hz_196608_76'
                            334 ;------------------------------------------------------------
                            335 ;main.c:19: int main(void) {
                            336 ;	-----------------------------------------
                            337 ;	 function main
                            338 ;	-----------------------------------------
                            339 ;	Register assignment is optimal.
                            340 ;	Stack space usage: 11 bytes.
   CD2D                     341 _main:
   CD2D A7 F5         [ 2]  342 	ais	#-11
                            343 ;main.c:20: timebaseInit();
   CD2F CD 80 3D      [ 5]  344 	jsr	_timebaseInit
                            345 ;main.c:21: schedulerInit();
   CD32 CD 83 EF      [ 5]  346 	jsr	_schedulerInit
                            347 ;main.c:22: initTables();
   CD35 CD 98 5C      [ 5]  348 	jsr	_initTables
                            349 ;main.c:23: triggerInit();
   CD38 CD 92 9F      [ 5]  350 	jsr	_triggerInit
                            351 ;main.c:24: commsInit();
   CD3B CD B4 B8      [ 5]  352 	jsr	_commsInit
                            353 ;globals.h:101: static inline void interrupts(void)   { __asm cli __endasm; }
   CD3E 9A            [ 2]  354 	 cli	
                            355 ;main.c:26: interrupts();
   CD3F                     356 00108$:
                            357 ;main.c:30: uint32_t now = micros();
   CD3F CD 80 4F      [ 5]  358 	jsr	_micros
   CD42 9E E7 04      [ 4]  359 	sta	4,s
   CD45 9E EF 03      [ 4]  360 	stx	3,s
   CD48 B6 4A         [ 3]  361 	lda	*___SDCC_hc08_ret2
   CD4A 9E E7 02      [ 4]  362 	sta	2,s
   CD4D B6 4B         [ 3]  363 	lda	*___SDCC_hc08_ret3
   CD4F 9E E7 01      [ 4]  364 	sta	1,s
                            365 ;main.c:33: commsProcess();
   CD52 CD B5 9B      [ 5]  366 	jsr	_commsProcess
                            367 ;main.c:36: processInjectorPolling();
   CD55 CD 82 5A      [ 5]  368 	jsr	_processInjectorPolling
                            369 ;main.c:38: if ((uint32_t)(now - lastLoop67Hz) >= 67000UL) {
   CD58 95            [ 2]  370 	tsx
   CD59 45 01 8F      [ 3]  371 	ldhx	#_main_lastLoop67Hz_196608_76
   CD5C 9E E6 04      [ 4]  372 	lda	4,s
   CD5F E0 03         [ 3]  373 	sub	3,x
   CD61 9E E7 08      [ 4]  374 	sta	8,s
   CD64 9E E6 03      [ 4]  375 	lda	3,s
   CD67 E2 02         [ 3]  376 	sbc	2,x
   CD69 9E E7 07      [ 4]  377 	sta	7,s
   CD6C 9E E6 02      [ 4]  378 	lda	2,s
   CD6F E2 01         [ 3]  379 	sbc	1,x
   CD71 9E E7 06      [ 4]  380 	sta	6,s
   CD74 9E E6 01      [ 4]  381 	lda	1,s
   CD77 F2            [ 2]  382 	sbc	,x
   CD78 9E E7 05      [ 4]  383 	sta	5,s
   CD7B 95            [ 2]  384 	tsx
   CD7C E6 07         [ 3]  385 	lda	7,x
   CD7E A0 B8         [ 2]  386 	sub	#0xb8
   CD80 E6 06         [ 3]  387 	lda	6,x
   CD82 A2 05         [ 2]  388 	sbc	#0x05
   CD84 E6 05         [ 3]  389 	lda	5,x
   CD86 A2 01         [ 2]  390 	sbc	#0x01
   CD88 E6 04         [ 3]  391 	lda	4,x
   CD8A A2 00         [ 2]  392 	sbc	#0x00
   CD8C 25 B1         [ 3]  393 	bcs	00108$
                            394 ;main.c:39: lastLoop67Hz = now;
   CD8E 45 01 8F      [ 3]  395 	ldhx	#_main_lastLoop67Hz_196608_76
   CD91 9E E6 01      [ 4]  396 	lda	1,s
   CD94 F7            [ 2]  397 	sta	,x
   CD95 9E E6 02      [ 4]  398 	lda	2,s
   CD98 E7 01         [ 3]  399 	sta	1,x
   CD9A 9E E6 03      [ 4]  400 	lda	3,s
   CD9D E7 02         [ 3]  401 	sta	2,x
   CD9F 9E E6 04      [ 4]  402 	lda	4,s
   CDA2 E7 03         [ 3]  403 	sta	3,x
                            404 ;main.c:40: calculateRPM();
   CDA4 CD 92 B4      [ 5]  405 	jsr	_calculateRPM
                            406 ;main.c:41: checkSyncLoss();
   CDA7 CD 93 AE      [ 5]  407 	jsr	_checkSyncLoss
                            408 ;main.c:42: updateEngineStatus();
   CDAA CD AD FF      [ 5]  409 	jsr	_updateEngineStatus
                            410 ;main.c:44: if (currentStatus.hasSync && currentStatus.RPM > 0) {
   CDAD C6 00 61      [ 4]  411 	lda	(_currentStatus + 0x0002)
   CDB0 27 8D         [ 3]  412 	beq	00108$
   CDB2 CE 00 5F      [ 4]  413 	ldx	_currentStatus
   CDB5 C6 00 60      [ 4]  414 	lda	(_currentStatus + 1)
   CDB8 26 01         [ 3]  415 	bne	00134$
   CDBA 5D            [ 1]  416 	tstx
   CDBB                     417 00134$:
   CDBB 27 82         [ 3]  418 	beq	00108$
                            419 ;main.c:49: uint16_t newPW1 = calculateInjection();
   CDBD CD A6 AB      [ 5]  420 	jsr	_calculateInjection
   CDC0 9E E7 0B      [ 4]  421 	sta	11,s
   CDC3 9E EF 0A      [ 4]  422 	stx	10,s
                            423 ;main.c:50: int8_t newAdvance = calculateAdvance();
   CDC6 CD AF 90      [ 5]  424 	jsr	_calculateAdvance
   CDC9 9E E7 09      [ 4]  425 	sta	9,s
                            426 ;main.c:51: uint16_t newDwell = calculateDwell();
   CDCC CD B2 40      [ 5]  427 	jsr	_calculateDwell
   CDCF 87            [ 2]  428 	psha
   CDD0 89            [ 2]  429 	pshx
   CDD1 8A            [ 2]  430 	pulh
   CDD2 88            [ 2]  431 	pulx
                            432 ;main.c:58: }
   CDD3 85            [ 1]  433 	tpa
   CDD4 9B            [ 2]  434 	sei
   CDD5 87            [ 2]  435 	psha
                            436 ;main.c:54: currentStatus.PW1 = newPW1;
   CDD6 9E E6 0B      [ 4]  437 	lda	11,s
   CDD9 C7 00 7B      [ 4]  438 	sta	(_currentStatus + 0x001c)
   CDDC 9E E6 0C      [ 4]  439 	lda	12,s
   CDDF C7 00 7C      [ 4]  440 	sta	((_currentStatus + 0x001c) + 1)
                            441 ;main.c:55: currentStatus.PW2 = newPW1;
   CDE2 9E E6 0B      [ 4]  442 	lda	11,s
   CDE5 C7 00 7D      [ 4]  443 	sta	(_currentStatus + 0x001e)
   CDE8 9E E6 0C      [ 4]  444 	lda	12,s
   CDEB C7 00 7E      [ 4]  445 	sta	((_currentStatus + 0x001e) + 1)
                            446 ;main.c:56: currentStatus.advance = newAdvance;
   CDEE 9E E6 0A      [ 4]  447 	lda	10,s
   CDF1 C7 00 84      [ 4]  448 	sta	(_currentStatus + 0x0025)
                            449 ;main.c:57: currentStatus.dwell = newDwell;
   CDF4 8B            [ 2]  450 	pshh
   CDF5 86            [ 2]  451 	pula
   CDF6 C7 00 85      [ 4]  452 	sta	(_currentStatus + 0x0026)
   CDF9 CF 00 86      [ 4]  453 	stx	((_currentStatus + 0x0026) + 1)
   CDFC 86            [ 2]  454 	pula
   CDFD 84            [ 2]  455 	tap
   CDFE CC CD 3F      [ 3]  456 	jmp	00108$
                            457 ;main.c:63: return 0;
                            458 ;main.c:64: }
   CE01 A7 0B         [ 2]  459 	ais	#11
   CE03 81            [ 4]  460 	rts
                            461 	.area CSEG    (CODE)
                            462 	.area CONST   (CODE)
                            463 	.area XINIT   (CODE)
                            464 	.area CABS    (ABS,CODE)
