                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 4.2.0 #13081 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module decoders
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
                             22 	.globl _isr_irq
                             23 	.globl _micros
                             24 	.globl _scheduleInjectorPolling
                             25 	.globl _setIgnitionSchedule
                             26 	.globl _revolutionCounter
                             27 	.globl _triggerState
                             28 	.globl _triggerSetup_MissingTooth
                             29 	.globl _triggerSetup_BasicDistributor
                             30 	.globl _triggerInit
                             31 	.globl _calculateRPM
                             32 	.globl _checkSyncLoss
                             33 	.globl _angleToTime
                             34 	.globl _timeToAngle
                             35 	.globl _getCrankAngle
                             36 	.globl _attachTriggerInterrupt
                             37 	.globl _resetTriggerState
                             38 ;--------------------------------------------------------
                             39 ; ram data
                             40 ;--------------------------------------------------------
                             41 	.area DSEG    (PAG)
                             42 ;--------------------------------------------------------
                             43 ; overlayable items in ram
                             44 ;--------------------------------------------------------
                             45 ;--------------------------------------------------------
                             46 ; absolute ram data
                             47 ;--------------------------------------------------------
                             48 	.area IABS    (ABS)
                             49 	.area IABS    (ABS)
                             50 ;--------------------------------------------------------
                             51 ; absolute external ram data
                             52 ;--------------------------------------------------------
                             53 	.area XABS    (ABS)
                             54 ;--------------------------------------------------------
                             55 ; external initialized ram data
                             56 ;--------------------------------------------------------
                             57 	.area XISEG
   01D3                      58 _revolutionCounter::
   01D3                      59 	.ds 1
   01D4                      60 _triggerEdgesPerTooth:
   01D4                      61 	.ds 1
                             62 ;--------------------------------------------------------
                             63 ; extended address mode data
                             64 ;--------------------------------------------------------
                             65 	.area XSEG
   00FC                      66 _triggerState::
   00FC                      67 	.ds 41
   0125                      68 _currentTriggerISR:
   0125                      69 	.ds 2
                             70 ;--------------------------------------------------------
                             71 ; global & static initialisations
                             72 ;--------------------------------------------------------
                             73 	.area HOME    (CODE)
                             74 	.area GSINIT  (CODE)
                             75 	.area GSFINAL (CODE)
                             76 	.area GSINIT  (CODE)
                             77 ;--------------------------------------------------------
                             78 ; Home
                             79 ;--------------------------------------------------------
                             80 	.area HOME    (CODE)
                             81 	.area HOME    (CODE)
                             82 ;--------------------------------------------------------
                             83 ; code
                             84 ;--------------------------------------------------------
                             85 	.area CSEG    (CODE)
                             86 ;------------------------------------------------------------
                             87 ;Allocation info for local variables in function 'noInterrupts'
                             88 ;------------------------------------------------------------
                             89 ;globals.h:100: static inline void noInterrupts(void) { __asm sei __endasm; }
                             90 ;	-----------------------------------------
                             91 ;	 function noInterrupts
                             92 ;	-----------------------------------------
                             93 ;	Register assignment is optimal.
                             94 ;	Stack space usage: 0 bytes.
   885D                      95 _noInterrupts:
   885D 9B            [ 2]   96 	 sei	
   885E 81            [ 4]   97 	rts
                             98 ;------------------------------------------------------------
                             99 ;Allocation info for local variables in function 'interrupts'
                            100 ;------------------------------------------------------------
                            101 ;globals.h:101: static inline void interrupts(void)   { __asm cli __endasm; }
                            102 ;	-----------------------------------------
                            103 ;	 function interrupts
                            104 ;	-----------------------------------------
                            105 ;	Register assignment is optimal.
                            106 ;	Stack space usage: 0 bytes.
   885F                     107 _interrupts:
   885F 9A            [ 2]  108 	 cli	
   8860 81            [ 4]  109 	rts
                            110 ;------------------------------------------------------------
                            111 ;Allocation info for local variables in function 'getTimer1Count'
                            112 ;------------------------------------------------------------
                            113 ;sloc0                     Allocated to stack - sp +1
                            114 ;------------------------------------------------------------
                            115 ;scheduler.h:55: static inline uint16_t getTimer1Count(void) {
                            116 ;	-----------------------------------------
                            117 ;	 function getTimer1Count
                            118 ;	-----------------------------------------
                            119 ;	Register assignment is optimal.
                            120 ;	Stack space usage: 2 bytes.
   8861                     121 _getTimer1Count:
   8861 A7 FE         [ 2]  122 	ais	#-2
                            123 ;scheduler.h:56: return (uint16_t)((T1CNTH << 8) | T1CNTL);
   8863 B6 21         [ 3]  124 	lda	*0x21
   8865 5F            [ 1]  125 	clrx
   8866 9E E7 01      [ 4]  126 	sta	1,s
   8869 9E EF 02      [ 4]  127 	stx	2,s
   886C B6 22         [ 3]  128 	lda	*0x22
   886E 9E EA 02      [ 4]  129 	ora	2,s
   8871 87            [ 2]  130 	psha
   8872 9F            [ 1]  131 	txa
   8873 9E EA 02      [ 4]  132 	ora	2,s
   8876 97            [ 1]  133 	tax
   8877 86            [ 2]  134 	pula
                            135 ;scheduler.h:57: }
   8878 A7 02         [ 2]  136 	ais	#2
   887A 81            [ 4]  137 	rts
                            138 ;------------------------------------------------------------
                            139 ;Allocation info for local variables in function 'scheduleInjectionISR'
                            140 ;------------------------------------------------------------
                            141 ;timeToInjection           Allocated to stack - sp +5
                            142 ;pw1                       Allocated to stack - sp +7
                            143 ;pw2                       Allocated to stack - sp +5
                            144 ;sloc0                     Allocated to stack - sp +1
                            145 ;------------------------------------------------------------
                            146 ;decoders.c:43: static void scheduleInjectionISR(void) {
                            147 ;	-----------------------------------------
                            148 ;	 function scheduleInjectionISR
                            149 ;	-----------------------------------------
                            150 ;	Register assignment might be sub-optimal.
                            151 ;	Stack space usage: 8 bytes.
   887B                     152 _scheduleInjectionISR:
   887B A7 F8         [ 2]  153 	ais	#-8
                            154 ;decoders.c:47: if (triggerState.revolutionTime == 0) return;
   887D C6 01 04      [ 4]  155 	lda	(_triggerState + 0x0008)
   8880 9E E7 01      [ 4]  156 	sta	1,s
   8883 C6 01 05      [ 4]  157 	lda	((_triggerState + 0x0008) + 1)
   8886 9E E7 02      [ 4]  158 	sta	2,s
   8889 C6 01 06      [ 4]  159 	lda	((_triggerState + 0x0008) + 2)
   888C 9E E7 03      [ 4]  160 	sta	3,s
   888F C6 01 07      [ 4]  161 	lda	((_triggerState + 0x0008) + 3)
   8892 9E E7 04      [ 4]  162 	sta	4,s
   8895 95            [ 2]  163 	tsx
   8896 F6            [ 2]  164 	lda	,x
   8897 EA 01         [ 3]  165 	ora	1,x
   8899 EA 02         [ 3]  166 	ora	2,x
   889B EA 03         [ 3]  167 	ora	3,x
   889D 26 03         [ 3]  168 	bne	00102$
   889F CC 89 9A      [ 3]  169 	jmp	00112$
   88A2                     170 00102$:
                            171 ;decoders.c:49: timeToInjection = ((uint32_t)INJECTION_ANGLE * triggerState.revolutionTime) / 360UL;
   88A2 C6 01 04      [ 4]  172 	lda	(_triggerState + 0x0008)
   88A5 9E E7 01      [ 4]  173 	sta	1,s
   88A8 C6 01 05      [ 4]  174 	lda	((_triggerState + 0x0008) + 1)
   88AB 9E E7 02      [ 4]  175 	sta	2,s
   88AE C6 01 06      [ 4]  176 	lda	((_triggerState + 0x0008) + 2)
   88B1 9E E7 03      [ 4]  177 	sta	3,s
   88B4 C6 01 07      [ 4]  178 	lda	((_triggerState + 0x0008) + 3)
   88B7 9E E7 04      [ 4]  179 	sta	4,s
   88BA 95            [ 2]  180 	tsx
   88BB E6 03         [ 3]  181 	lda	3,x
   88BD 87            [ 2]  182 	psha
   88BE E6 02         [ 3]  183 	lda	2,x
   88C0 87            [ 2]  184 	psha
   88C1 E6 01         [ 3]  185 	lda	1,x
   88C3 87            [ 2]  186 	psha
   88C4 F6            [ 2]  187 	lda	,x
   88C5 87            [ 2]  188 	psha
   88C6 A6 0E         [ 2]  189 	lda	#0x0e
   88C8 87            [ 2]  190 	psha
   88C9 A6 01         [ 2]  191 	lda	#0x01
   88CB 87            [ 2]  192 	psha
   88CC 4A            [ 1]  193 	deca
   88CD 87            [ 2]  194 	psha
   88CE 87            [ 2]  195 	psha
   88CF CD D0 87      [ 5]  196 	jsr	__mullong
   88D2 9E E7 0C      [ 4]  197 	sta	12,s
   88D5 9E EF 0B      [ 4]  198 	stx	11,s
   88D8 B6 4A         [ 3]  199 	lda	*___SDCC_hc08_ret2
   88DA 9E E7 0A      [ 4]  200 	sta	10,s
   88DD B6 4B         [ 3]  201 	lda	*___SDCC_hc08_ret3
   88DF 9E E7 09      [ 4]  202 	sta	9,s
   88E2 A7 08         [ 2]  203 	ais	#8
   88E4 A6 68         [ 2]  204 	lda	#0x68
   88E6 87            [ 2]  205 	psha
   88E7 A6 01         [ 2]  206 	lda	#0x01
   88E9 87            [ 2]  207 	psha
   88EA 4A            [ 1]  208 	deca
   88EB 87            [ 2]  209 	psha
   88EC 87            [ 2]  210 	psha
   88ED 95            [ 2]  211 	tsx
   88EE E6 07         [ 3]  212 	lda	7,x
   88F0 87            [ 2]  213 	psha
   88F1 E6 06         [ 3]  214 	lda	6,x
   88F3 87            [ 2]  215 	psha
   88F4 E6 05         [ 3]  216 	lda	5,x
   88F6 87            [ 2]  217 	psha
   88F7 E6 04         [ 3]  218 	lda	4,x
   88F9 87            [ 2]  219 	psha
                            220 ;decoders.c:51: pw1 = currentStatus.PW1;
   88FA CD CF 5C      [ 5]  221 	jsr	__divulong
   88FD 9E E7 0C      [ 4]  222 	sta	12,s
   8900 9E EF 0B      [ 4]  223 	stx	11,s
   8903 B6 4A         [ 3]  224 	lda	*___SDCC_hc08_ret2
   8905 9E E7 0A      [ 4]  225 	sta	10,s
   8908 B6 4B         [ 3]  226 	lda	*___SDCC_hc08_ret3
   890A 9E E7 09      [ 4]  227 	sta	9,s
   890D A7 08         [ 2]  228 	ais	#8
   890F C6 00 7B      [ 4]  229 	lda	(_currentStatus + 0x001c)
   8912 9E E7 07      [ 4]  230 	sta	7,s
   8915 C6 00 7C      [ 4]  231 	lda	((_currentStatus + 0x001c) + 1)
   8918 9E E7 08      [ 4]  232 	sta	8,s
                            233 ;decoders.c:52: pw2 = currentStatus.PW2;
   891B C6 00 7D      [ 4]  234 	lda	(_currentStatus + 0x001e)
   891E 9E E7 05      [ 4]  235 	sta	5,s
   8921 C6 00 7E      [ 4]  236 	lda	((_currentStatus + 0x001e) + 1)
   8924 9E E7 06      [ 4]  237 	sta	6,s
                            238 ;decoders.c:53: if (pw1 < INJ_MIN_PW || pw1 > INJ_MAX_PW) pw1 = INJ_MIN_PW;
   8927 9E E6 07      [ 4]  239 	lda	7,s
   892A 87            [ 2]  240 	psha
   892B 8A            [ 2]  241 	pulh
   892C 9E EE 08      [ 4]  242 	ldx	8,s
   892F 65 01 F4      [ 3]  243 	cphx	#0x01f4
   8932 25 05         [ 3]  244 	bcs	00103$
   8934 65 4E 20      [ 3]  245 	cphx	#0x4e20
   8937 23 09         [ 3]  246 	bls	00104$
   8939                     247 00103$:
   8939 95            [ 2]  248 	tsx
   893A A6 01         [ 2]  249 	lda	#0x01
   893C E7 06         [ 3]  250 	sta	6,x
   893E A6 F4         [ 2]  251 	lda	#0xf4
   8940 E7 07         [ 3]  252 	sta	7,x
   8942                     253 00104$:
                            254 ;decoders.c:54: if (pw2 < INJ_MIN_PW || pw2 > INJ_MAX_PW) pw2 = INJ_MIN_PW;
   8942 9E E6 05      [ 4]  255 	lda	5,s
   8945 87            [ 2]  256 	psha
   8946 8A            [ 2]  257 	pulh
   8947 9E EE 06      [ 4]  258 	ldx	6,s
   894A 65 01 F4      [ 3]  259 	cphx	#0x01f4
   894D 25 05         [ 3]  260 	bcs	00106$
   894F 65 4E 20      [ 3]  261 	cphx	#0x4e20
   8952 23 09         [ 3]  262 	bls	00107$
   8954                     263 00106$:
   8954 95            [ 2]  264 	tsx
   8955 A6 01         [ 2]  265 	lda	#0x01
   8957 E7 04         [ 3]  266 	sta	4,x
   8959 A6 F4         [ 2]  267 	lda	#0xf4
   895B E7 05         [ 3]  268 	sta	5,x
   895D                     269 00107$:
                            270 ;decoders.c:56: if (revolutionCounter == 0) {
   895D C6 01 D3      [ 4]  271 	lda	_revolutionCounter
   8960 26 1D         [ 3]  272 	bne	00110$
                            273 ;decoders.c:57: scheduleInjectorPolling(&injector1Polling, timeToInjection, pw1);
   8962 95            [ 2]  274 	tsx
   8963 E6 07         [ 3]  275 	lda	7,x
   8965 87            [ 2]  276 	psha
   8966 E6 06         [ 3]  277 	lda	6,x
   8968 87            [ 2]  278 	psha
   8969 E6 03         [ 3]  279 	lda	3,x
   896B 87            [ 2]  280 	psha
   896C E6 02         [ 3]  281 	lda	2,x
   896E 87            [ 2]  282 	psha
   896F E6 01         [ 3]  283 	lda	1,x
   8971 87            [ 2]  284 	psha
   8972 F6            [ 2]  285 	lda	,x
   8973 87            [ 2]  286 	psha
   8974 A6 DE         [ 2]  287 	lda	#_injector1Polling
   8976 AE 00         [ 2]  288 	ldx	#>_injector1Polling
   8978 CD 81 A0      [ 5]  289 	jsr	_scheduleInjectorPolling
   897B A7 06         [ 2]  290 	ais	#6
   897D 20 1B         [ 3]  291 	bra	00112$
   897F                     292 00110$:
                            293 ;decoders.c:59: scheduleInjectorPolling(&injector2Polling, timeToInjection, pw2);
   897F 95            [ 2]  294 	tsx
   8980 E6 05         [ 3]  295 	lda	5,x
   8982 87            [ 2]  296 	psha
   8983 E6 04         [ 3]  297 	lda	4,x
   8985 87            [ 2]  298 	psha
   8986 E6 03         [ 3]  299 	lda	3,x
   8988 87            [ 2]  300 	psha
   8989 E6 02         [ 3]  301 	lda	2,x
   898B 87            [ 2]  302 	psha
   898C E6 01         [ 3]  303 	lda	1,x
   898E 87            [ 2]  304 	psha
   898F F6            [ 2]  305 	lda	,x
   8990 87            [ 2]  306 	psha
   8991 A6 E8         [ 2]  307 	lda	#_injector2Polling
   8993 AE 00         [ 2]  308 	ldx	#>_injector2Polling
   8995 CD 81 A0      [ 5]  309 	jsr	_scheduleInjectorPolling
   8998 A7 06         [ 2]  310 	ais	#6
   899A                     311 00112$:
                            312 ;decoders.c:61: }
   899A A7 08         [ 2]  313 	ais	#8
   899C 81            [ 4]  314 	rts
                            315 ;------------------------------------------------------------
                            316 ;Allocation info for local variables in function 'scheduleIgnitionISR'
                            317 ;------------------------------------------------------------
                            318 ;advance                   Allocated to stack - sp +9
                            319 ;dwellTime                 Allocated to stack - sp +12
                            320 ;dwellAngle                Allocated to stack - sp +10
                            321 ;sparkAngle                Allocated to stack - sp +14
                            322 ;dwellStartAngle           Allocated to registers x h 
                            323 ;timeToDwell               Allocated to stack - sp +3
                            324 ;sloc0                     Allocated to stack - sp +1
                            325 ;sloc1                     Allocated to stack - sp +5
                            326 ;------------------------------------------------------------
                            327 ;decoders.c:63: static void scheduleIgnitionISR(void) {
                            328 ;	-----------------------------------------
                            329 ;	 function scheduleIgnitionISR
                            330 ;	-----------------------------------------
                            331 ;	Register assignment might be sub-optimal.
                            332 ;	Stack space usage: 15 bytes.
   899D                     333 _scheduleIgnitionISR:
   899D A7 F1         [ 2]  334 	ais	#-15
                            335 ;decoders.c:68: if (triggerState.revolutionTime == 0) return;
   899F C6 01 04      [ 4]  336 	lda	(_triggerState + 0x0008)
   89A2 9E E7 01      [ 4]  337 	sta	1,s
   89A5 C6 01 05      [ 4]  338 	lda	((_triggerState + 0x0008) + 1)
   89A8 9E E7 02      [ 4]  339 	sta	2,s
   89AB C6 01 06      [ 4]  340 	lda	((_triggerState + 0x0008) + 2)
   89AE 9E E7 03      [ 4]  341 	sta	3,s
   89B1 C6 01 07      [ 4]  342 	lda	((_triggerState + 0x0008) + 3)
   89B4 9E E7 04      [ 4]  343 	sta	4,s
   89B7 95            [ 2]  344 	tsx
   89B8 F6            [ 2]  345 	lda	,x
   89B9 EA 01         [ 3]  346 	ora	1,x
   89BB EA 02         [ 3]  347 	ora	2,x
   89BD EA 03         [ 3]  348 	ora	3,x
   89BF 26 03         [ 3]  349 	bne	00102$
   89C1 CC 8C B5      [ 3]  350 	jmp	00115$
   89C4                     351 00102$:
                            352 ;decoders.c:70: advance = currentStatus.advance;
   89C4 C6 00 84      [ 4]  353 	lda	(_currentStatus + 0x0025)
   89C7 9E E7 09      [ 4]  354 	sta	9,s
                            355 ;decoders.c:71: dwellTime = currentStatus.dwell;
   89CA C6 00 85      [ 4]  356 	lda	(_currentStatus + 0x0026)
   89CD 9E E7 0C      [ 4]  357 	sta	12,s
   89D0 C6 00 86      [ 4]  358 	lda	((_currentStatus + 0x0026) + 1)
   89D3 9E E7 0D      [ 4]  359 	sta	13,s
                            360 ;decoders.c:72: if (dwellTime < DWELL_MIN) dwellTime = DWELL_MIN;
   89D6 9E E6 0D      [ 4]  361 	lda	13,s
   89D9 9E EE 0C      [ 4]  362 	ldx	12,s
   89DC A0 E8         [ 2]  363 	sub	#0xe8
   89DE 9F            [ 1]  364 	txa
   89DF A2 03         [ 2]  365 	sbc	#0x03
   89E1 24 09         [ 3]  366 	bcc	00104$
   89E3 95            [ 2]  367 	tsx
   89E4 A6 03         [ 2]  368 	lda	#0x03
   89E6 E7 0B         [ 3]  369 	sta	11,x
   89E8 A6 E8         [ 2]  370 	lda	#0xe8
   89EA E7 0C         [ 3]  371 	sta	12,x
   89EC                     372 00104$:
                            373 ;decoders.c:73: if (dwellTime > DWELL_MAX) dwellTime = DWELL_MAX;
   89EC 9E E6 0C      [ 4]  374 	lda	12,s
   89EF 87            [ 2]  375 	psha
   89F0 8A            [ 2]  376 	pulh
   89F1 9E EE 0D      [ 4]  377 	ldx	13,s
   89F4 65 1F 40      [ 3]  378 	cphx	#0x1f40
   89F7 23 09         [ 3]  379 	bls	00106$
   89F9 95            [ 2]  380 	tsx
   89FA A6 1F         [ 2]  381 	lda	#0x1f
   89FC E7 0B         [ 3]  382 	sta	11,x
   89FE A6 40         [ 2]  383 	lda	#0x40
   8A00 E7 0C         [ 3]  384 	sta	12,x
   8A02                     385 00106$:
                            386 ;decoders.c:75: dwellAngle = (uint16_t)(((uint32_t)dwellTime * 360UL) / triggerState.revolutionTime);
   8A02 95            [ 2]  387 	tsx
   8A03 E6 0C         [ 3]  388 	lda	12,x
   8A05 E7 03         [ 3]  389 	sta	3,x
   8A07 E6 0B         [ 3]  390 	lda	11,x
   8A09 E7 02         [ 3]  391 	sta	2,x
   8A0B 4F            [ 1]  392 	clra
   8A0C E7 01         [ 3]  393 	sta	1,x
   8A0E F7            [ 2]  394 	sta	,x
   8A0F E6 03         [ 3]  395 	lda	3,x
   8A11 87            [ 2]  396 	psha
   8A12 E6 02         [ 3]  397 	lda	2,x
   8A14 87            [ 2]  398 	psha
   8A15 E6 01         [ 3]  399 	lda	1,x
   8A17 87            [ 2]  400 	psha
   8A18 F6            [ 2]  401 	lda	,x
   8A19 87            [ 2]  402 	psha
   8A1A A6 68         [ 2]  403 	lda	#0x68
   8A1C 87            [ 2]  404 	psha
   8A1D A6 01         [ 2]  405 	lda	#0x01
   8A1F 87            [ 2]  406 	psha
   8A20 4A            [ 1]  407 	deca
   8A21 87            [ 2]  408 	psha
   8A22 87            [ 2]  409 	psha
   8A23 CD D0 87      [ 5]  410 	jsr	__mullong
   8A26 9E E7 0C      [ 4]  411 	sta	12,s
   8A29 9E EF 0B      [ 4]  412 	stx	11,s
   8A2C B6 4A         [ 3]  413 	lda	*___SDCC_hc08_ret2
   8A2E 9E E7 0A      [ 4]  414 	sta	10,s
   8A31 B6 4B         [ 3]  415 	lda	*___SDCC_hc08_ret3
   8A33 9E E7 09      [ 4]  416 	sta	9,s
   8A36 A7 08         [ 2]  417 	ais	#8
   8A38 C6 01 04      [ 4]  418 	lda	(_triggerState + 0x0008)
   8A3B 9E E7 05      [ 4]  419 	sta	5,s
   8A3E C6 01 05      [ 4]  420 	lda	((_triggerState + 0x0008) + 1)
   8A41 9E E7 06      [ 4]  421 	sta	6,s
   8A44 C6 01 06      [ 4]  422 	lda	((_triggerState + 0x0008) + 2)
   8A47 9E E7 07      [ 4]  423 	sta	7,s
   8A4A C6 01 07      [ 4]  424 	lda	((_triggerState + 0x0008) + 3)
   8A4D 9E E7 08      [ 4]  425 	sta	8,s
   8A50 95            [ 2]  426 	tsx
   8A51 E6 07         [ 3]  427 	lda	7,x
   8A53 87            [ 2]  428 	psha
   8A54 E6 06         [ 3]  429 	lda	6,x
   8A56 87            [ 2]  430 	psha
   8A57 E6 05         [ 3]  431 	lda	5,x
   8A59 87            [ 2]  432 	psha
   8A5A E6 04         [ 3]  433 	lda	4,x
   8A5C 87            [ 2]  434 	psha
   8A5D E6 03         [ 3]  435 	lda	3,x
   8A5F 87            [ 2]  436 	psha
   8A60 E6 02         [ 3]  437 	lda	2,x
   8A62 87            [ 2]  438 	psha
   8A63 E6 01         [ 3]  439 	lda	1,x
   8A65 87            [ 2]  440 	psha
   8A66 F6            [ 2]  441 	lda	,x
   8A67 87            [ 2]  442 	psha
   8A68 CD CF 5C      [ 5]  443 	jsr	__divulong
   8A6B 9E E7 10      [ 4]  444 	sta	16,s
   8A6E 9E EF 0F      [ 4]  445 	stx	15,s
   8A71 B6 4A         [ 3]  446 	lda	*___SDCC_hc08_ret2
   8A73 9E E7 0E      [ 4]  447 	sta	14,s
   8A76 B6 4B         [ 3]  448 	lda	*___SDCC_hc08_ret3
   8A78 9E E7 0D      [ 4]  449 	sta	13,s
   8A7B A7 08         [ 2]  450 	ais	#8
   8A7D 95            [ 2]  451 	tsx
   8A7E E6 07         [ 3]  452 	lda	7,x
   8A80 E7 0A         [ 3]  453 	sta	10,x
   8A82 E6 06         [ 3]  454 	lda	6,x
   8A84 E7 09         [ 3]  455 	sta	9,x
                            456 ;decoders.c:77: if (dwellAngle > 180) {
   8A86 E6 09         [ 3]  457 	lda	9,x
   8A88 87            [ 2]  458 	psha
   8A89 8A            [ 2]  459 	pulh
   8A8A 9E EE 0B      [ 4]  460 	ldx	11,s
   8A8D 65 00 B4      [ 3]  461 	cphx	#0x00b4
   8A90 23 78         [ 3]  462 	bls	00108$
                            463 ;decoders.c:78: dwellAngle = 180;
   8A92 95            [ 2]  464 	tsx
   8A93 4F            [ 1]  465 	clra
   8A94 E7 09         [ 3]  466 	sta	9,x
   8A96 A6 B4         [ 2]  467 	lda	#0xb4
   8A98 E7 0A         [ 3]  468 	sta	10,x
                            469 ;decoders.c:79: dwellTime = (uint16_t)((180UL * triggerState.revolutionTime) / 360UL);
   8A9A C6 01 04      [ 4]  470 	lda	(_triggerState + 0x0008)
   8A9D E7 04         [ 3]  471 	sta	4,x
   8A9F C6 01 05      [ 4]  472 	lda	((_triggerState + 0x0008) + 1)
   8AA2 E7 05         [ 3]  473 	sta	5,x
   8AA4 C6 01 06      [ 4]  474 	lda	((_triggerState + 0x0008) + 2)
   8AA7 E7 06         [ 3]  475 	sta	6,x
   8AA9 C6 01 07      [ 4]  476 	lda	((_triggerState + 0x0008) + 3)
   8AAC E7 07         [ 3]  477 	sta	7,x
   8AAE E6 07         [ 3]  478 	lda	7,x
   8AB0 87            [ 2]  479 	psha
   8AB1 E6 06         [ 3]  480 	lda	6,x
   8AB3 87            [ 2]  481 	psha
   8AB4 E6 05         [ 3]  482 	lda	5,x
   8AB6 87            [ 2]  483 	psha
   8AB7 E6 04         [ 3]  484 	lda	4,x
   8AB9 87            [ 2]  485 	psha
   8ABA A6 B4         [ 2]  486 	lda	#0xb4
   8ABC 87            [ 2]  487 	psha
   8ABD 4F            [ 1]  488 	clra
   8ABE 87            [ 2]  489 	psha
   8ABF 87            [ 2]  490 	psha
   8AC0 87            [ 2]  491 	psha
   8AC1 CD D0 87      [ 5]  492 	jsr	__mullong
   8AC4 9E E7 10      [ 4]  493 	sta	16,s
   8AC7 9E EF 0F      [ 4]  494 	stx	15,s
   8ACA B6 4A         [ 3]  495 	lda	*___SDCC_hc08_ret2
   8ACC 9E E7 0E      [ 4]  496 	sta	14,s
   8ACF B6 4B         [ 3]  497 	lda	*___SDCC_hc08_ret3
   8AD1 9E E7 0D      [ 4]  498 	sta	13,s
   8AD4 A7 08         [ 2]  499 	ais	#8
   8AD6 A6 68         [ 2]  500 	lda	#0x68
   8AD8 87            [ 2]  501 	psha
   8AD9 A6 01         [ 2]  502 	lda	#0x01
   8ADB 87            [ 2]  503 	psha
   8ADC 4A            [ 1]  504 	deca
   8ADD 87            [ 2]  505 	psha
   8ADE 87            [ 2]  506 	psha
   8ADF 95            [ 2]  507 	tsx
   8AE0 E6 0B         [ 3]  508 	lda	11,x
   8AE2 87            [ 2]  509 	psha
   8AE3 E6 0A         [ 3]  510 	lda	10,x
   8AE5 87            [ 2]  511 	psha
   8AE6 E6 09         [ 3]  512 	lda	9,x
   8AE8 87            [ 2]  513 	psha
   8AE9 E6 08         [ 3]  514 	lda	8,x
   8AEB 87            [ 2]  515 	psha
   8AEC CD CF 5C      [ 5]  516 	jsr	__divulong
   8AEF 9E E7 10      [ 4]  517 	sta	16,s
   8AF2 9E EF 0F      [ 4]  518 	stx	15,s
   8AF5 B6 4A         [ 3]  519 	lda	*___SDCC_hc08_ret2
   8AF7 9E E7 0E      [ 4]  520 	sta	14,s
   8AFA B6 4B         [ 3]  521 	lda	*___SDCC_hc08_ret3
   8AFC 9E E7 0D      [ 4]  522 	sta	13,s
   8AFF A7 08         [ 2]  523 	ais	#8
   8B01 95            [ 2]  524 	tsx
   8B02 E6 07         [ 3]  525 	lda	7,x
   8B04 E7 0C         [ 3]  526 	sta	12,x
   8B06 E6 06         [ 3]  527 	lda	6,x
   8B08 E7 0B         [ 3]  528 	sta	11,x
   8B0A                     529 00108$:
                            530 ;decoders.c:82: sparkAngle = (advance > 0) ? (uint16_t)(360 - advance) : 360;
   8B0A 9E E6 09      [ 4]  531 	lda	9,s
   8B0D A1 00         [ 2]  532 	cmp	#0x00
   8B0F 93 18         [ 3]  533 	ble	00117$
   8B11 95            [ 2]  534 	tsx
   8B12 E6 08         [ 3]  535 	lda	8,x
   8B14 E7 05         [ 3]  536 	sta	5,x
   8B16 49            [ 1]  537 	rola	
   8B17 4F            [ 1]  538 	clra	
   8B18 A2 00         [ 2]  539 	sbc	#0x00
   8B1A E7 04         [ 3]  540 	sta	4,x
   8B1C A6 68         [ 2]  541 	lda	#0x68
   8B1E E0 05         [ 3]  542 	sub	5,x
   8B20 87            [ 2]  543 	psha
   8B21 A6 01         [ 2]  544 	lda	#0x01
   8B23 E2 04         [ 3]  545 	sbc	4,x
   8B25 97            [ 1]  546 	tax
   8B26 86            [ 2]  547 	pula
   8B27 20 04         [ 3]  548 	bra	00118$
   8B29                     549 00117$:
   8B29 AE 01         [ 2]  550 	ldx	#0x01
   8B2B A6 68         [ 2]  551 	lda	#0x68
   8B2D                     552 00118$:
   8B2D 9E E7 0F      [ 4]  553 	sta	15,s
   8B30 9E EF 0E      [ 4]  554 	stx	14,s
                            555 ;decoders.c:84: if (sparkAngle > dwellAngle) {
   8B33 95            [ 2]  556 	tsx
   8B34 E6 0A         [ 3]  557 	lda	10,x
   8B36 E0 0E         [ 3]  558 	sub	14,x
   8B38 E6 09         [ 3]  559 	lda	9,x
   8B3A E2 0D         [ 3]  560 	sbc	13,x
   8B3C 24 10         [ 3]  561 	bcc	00110$
                            562 ;decoders.c:85: dwellStartAngle = sparkAngle - dwellAngle;
   8B3E E6 0E         [ 3]  563 	lda	14,x
   8B40 E0 0A         [ 3]  564 	sub	10,x
   8B42 97            [ 1]  565 	tax
   8B43 9E E6 0E      [ 4]  566 	lda	14,s
   8B46 9E E2 0A      [ 4]  567 	sbc	10,s
   8B49 87            [ 2]  568 	psha
   8B4A 8A            [ 2]  569 	pulh
   8B4B CC 8B F1      [ 3]  570 	jmp	00111$
   8B4E                     571 00110$:
                            572 ;decoders.c:87: dwellStartAngle = 0;
   8B4E 8C            [ 1]  573 	clrh
   8B4F 5F            [ 1]  574 	clrx
                            575 ;decoders.c:89: dwellTime = (uint16_t)(((uint32_t)dwellAngle * triggerState.revolutionTime) / 360UL);
   8B50 9E E6 0F      [ 4]  576 	lda	15,s
   8B53 9E E7 08      [ 4]  577 	sta	8,s
   8B56 9E E6 0E      [ 4]  578 	lda	14,s
   8B59 9E E7 07      [ 4]  579 	sta	7,s
   8B5C 9E EF 06      [ 4]  580 	stx	6,s
   8B5F 9E EF 05      [ 4]  581 	stx	5,s
   8B62 C6 01 04      [ 4]  582 	lda	(_triggerState + 0x0008)
   8B65 9E E7 01      [ 4]  583 	sta	1,s
   8B68 C6 01 05      [ 4]  584 	lda	((_triggerState + 0x0008) + 1)
   8B6B 9E E7 02      [ 4]  585 	sta	2,s
   8B6E C6 01 06      [ 4]  586 	lda	((_triggerState + 0x0008) + 2)
   8B71 9E E7 03      [ 4]  587 	sta	3,s
   8B74 C6 01 07      [ 4]  588 	lda	((_triggerState + 0x0008) + 3)
   8B77 9E E7 04      [ 4]  589 	sta	4,s
   8B7A 89            [ 2]  590 	pshx
   8B7B 8B            [ 2]  591 	pshh
   8B7C 9E E6 06      [ 4]  592 	lda	6,s
   8B7F 87            [ 2]  593 	psha
   8B80 9E E6 06      [ 4]  594 	lda	6,s
   8B83 87            [ 2]  595 	psha
   8B84 9E E6 06      [ 4]  596 	lda	6,s
   8B87 87            [ 2]  597 	psha
   8B88 9E E6 06      [ 4]  598 	lda	6,s
   8B8B 87            [ 2]  599 	psha
   8B8C 9E E6 0E      [ 4]  600 	lda	14,s
   8B8F 87            [ 2]  601 	psha
   8B90 9E E6 0E      [ 4]  602 	lda	14,s
   8B93 87            [ 2]  603 	psha
   8B94 9E E6 0E      [ 4]  604 	lda	14,s
   8B97 87            [ 2]  605 	psha
   8B98 9E E6 0E      [ 4]  606 	lda	14,s
   8B9B 87            [ 2]  607 	psha
   8B9C CD D0 87      [ 5]  608 	jsr	__mullong
   8B9F 9E E7 12      [ 4]  609 	sta	18,s
   8BA2 9E EF 11      [ 4]  610 	stx	17,s
   8BA5 B6 4A         [ 3]  611 	lda	*___SDCC_hc08_ret2
   8BA7 9E E7 10      [ 4]  612 	sta	16,s
   8BAA B6 4B         [ 3]  613 	lda	*___SDCC_hc08_ret3
   8BAC 9E E7 0F      [ 4]  614 	sta	15,s
   8BAF A7 08         [ 2]  615 	ais	#8
   8BB1 8A            [ 2]  616 	pulh
   8BB2 88            [ 2]  617 	pulx
   8BB3 89            [ 2]  618 	pshx
   8BB4 8B            [ 2]  619 	pshh
   8BB5 A6 68         [ 2]  620 	lda	#0x68
   8BB7 87            [ 2]  621 	psha
   8BB8 A6 01         [ 2]  622 	lda	#0x01
   8BBA 87            [ 2]  623 	psha
   8BBB 4A            [ 1]  624 	deca
   8BBC 87            [ 2]  625 	psha
   8BBD 87            [ 2]  626 	psha
   8BBE 9E E6 0E      [ 4]  627 	lda	14,s
   8BC1 87            [ 2]  628 	psha
   8BC2 9E E6 0E      [ 4]  629 	lda	14,s
   8BC5 87            [ 2]  630 	psha
   8BC6 9E E6 0E      [ 4]  631 	lda	14,s
   8BC9 87            [ 2]  632 	psha
   8BCA 9E E6 0E      [ 4]  633 	lda	14,s
   8BCD 87            [ 2]  634 	psha
   8BCE CD CF 5C      [ 5]  635 	jsr	__divulong
   8BD1 9E E7 12      [ 4]  636 	sta	18,s
   8BD4 9E EF 11      [ 4]  637 	stx	17,s
   8BD7 B6 4A         [ 3]  638 	lda	*___SDCC_hc08_ret2
   8BD9 9E E7 10      [ 4]  639 	sta	16,s
   8BDC B6 4B         [ 3]  640 	lda	*___SDCC_hc08_ret3
   8BDE 9E E7 0F      [ 4]  641 	sta	15,s
   8BE1 A7 08         [ 2]  642 	ais	#8
   8BE3 8A            [ 2]  643 	pulh
   8BE4 88            [ 2]  644 	pulx
   8BE5 9E E6 08      [ 4]  645 	lda	8,s
   8BE8 9E E7 0D      [ 4]  646 	sta	13,s
   8BEB 9E E6 07      [ 4]  647 	lda	7,s
   8BEE 9E E7 0C      [ 4]  648 	sta	12,s
   8BF1                     649 00111$:
                            650 ;decoders.c:92: timeToDwell = ((uint32_t)dwellStartAngle * triggerState.revolutionTime) / 360UL;
   8BF1 9E EF 08      [ 4]  651 	stx	8,s
   8BF4 8B            [ 2]  652 	pshh
   8BF5 86            [ 2]  653 	pula
   8BF6 9E E7 07      [ 4]  654 	sta	7,s
   8BF9 4F            [ 1]  655 	clra
   8BFA 9E E7 06      [ 4]  656 	sta	6,s
   8BFD 9E E7 05      [ 4]  657 	sta	5,s
   8C00 C6 01 04      [ 4]  658 	lda	(_triggerState + 0x0008)
   8C03 9E E7 01      [ 4]  659 	sta	1,s
   8C06 C6 01 05      [ 4]  660 	lda	((_triggerState + 0x0008) + 1)
   8C09 9E E7 02      [ 4]  661 	sta	2,s
   8C0C C6 01 06      [ 4]  662 	lda	((_triggerState + 0x0008) + 2)
   8C0F 9E E7 03      [ 4]  663 	sta	3,s
   8C12 C6 01 07      [ 4]  664 	lda	((_triggerState + 0x0008) + 3)
   8C15 9E E7 04      [ 4]  665 	sta	4,s
   8C18 95            [ 2]  666 	tsx
   8C19 E6 03         [ 3]  667 	lda	3,x
   8C1B 87            [ 2]  668 	psha
   8C1C E6 02         [ 3]  669 	lda	2,x
   8C1E 87            [ 2]  670 	psha
   8C1F E6 01         [ 3]  671 	lda	1,x
   8C21 87            [ 2]  672 	psha
   8C22 F6            [ 2]  673 	lda	,x
   8C23 87            [ 2]  674 	psha
   8C24 E6 07         [ 3]  675 	lda	7,x
   8C26 87            [ 2]  676 	psha
   8C27 E6 06         [ 3]  677 	lda	6,x
   8C29 87            [ 2]  678 	psha
   8C2A E6 05         [ 3]  679 	lda	5,x
   8C2C 87            [ 2]  680 	psha
   8C2D E6 04         [ 3]  681 	lda	4,x
   8C2F 87            [ 2]  682 	psha
   8C30 CD D0 87      [ 5]  683 	jsr	__mullong
   8C33 9E E7 10      [ 4]  684 	sta	16,s
   8C36 9E EF 0F      [ 4]  685 	stx	15,s
   8C39 B6 4A         [ 3]  686 	lda	*___SDCC_hc08_ret2
   8C3B 9E E7 0E      [ 4]  687 	sta	14,s
   8C3E B6 4B         [ 3]  688 	lda	*___SDCC_hc08_ret3
   8C40 9E E7 0D      [ 4]  689 	sta	13,s
   8C43 A7 08         [ 2]  690 	ais	#8
   8C45 A6 68         [ 2]  691 	lda	#0x68
   8C47 87            [ 2]  692 	psha
   8C48 A6 01         [ 2]  693 	lda	#0x01
   8C4A 87            [ 2]  694 	psha
   8C4B 4A            [ 1]  695 	deca
   8C4C 87            [ 2]  696 	psha
   8C4D 87            [ 2]  697 	psha
   8C4E 95            [ 2]  698 	tsx
   8C4F E6 0B         [ 3]  699 	lda	11,x
   8C51 87            [ 2]  700 	psha
   8C52 E6 0A         [ 3]  701 	lda	10,x
   8C54 87            [ 2]  702 	psha
   8C55 E6 09         [ 3]  703 	lda	9,x
   8C57 87            [ 2]  704 	psha
   8C58 E6 08         [ 3]  705 	lda	8,x
   8C5A 87            [ 2]  706 	psha
                            707 ;decoders.c:94: if (revolutionCounter == 0) {
   8C5B CD CF 5C      [ 5]  708 	jsr	__divulong
   8C5E 9E E7 10      [ 4]  709 	sta	16,s
   8C61 9E EF 0F      [ 4]  710 	stx	15,s
   8C64 B6 4A         [ 3]  711 	lda	*___SDCC_hc08_ret2
   8C66 9E E7 0E      [ 4]  712 	sta	14,s
   8C69 B6 4B         [ 3]  713 	lda	*___SDCC_hc08_ret3
   8C6B 9E E7 0D      [ 4]  714 	sta	13,s
   8C6E A7 08         [ 2]  715 	ais	#8
   8C70 C6 01 D3      [ 4]  716 	lda	_revolutionCounter
   8C73 26 21         [ 3]  717 	bne	00113$
                            718 ;decoders.c:95: setIgnitionSchedule(&ignitionSchedule1, timeToDwell, dwellTime, 1);
   8C75 A6 01         [ 2]  719 	lda	#0x01
   8C77 87            [ 2]  720 	psha
   8C78 95            [ 2]  721 	tsx
   8C79 E6 0D         [ 3]  722 	lda	13,x
   8C7B 87            [ 2]  723 	psha
   8C7C E6 0C         [ 3]  724 	lda	12,x
   8C7E 87            [ 2]  725 	psha
   8C7F E6 08         [ 3]  726 	lda	8,x
   8C81 87            [ 2]  727 	psha
   8C82 E6 07         [ 3]  728 	lda	7,x
   8C84 87            [ 2]  729 	psha
   8C85 E6 06         [ 3]  730 	lda	6,x
   8C87 87            [ 2]  731 	psha
   8C88 E6 05         [ 3]  732 	lda	5,x
   8C8A 87            [ 2]  733 	psha
   8C8B A6 C3         [ 2]  734 	lda	#_ignitionSchedule1
   8C8D AE 01         [ 2]  735 	ldx	#>_ignitionSchedule1
   8C8F CD 85 80      [ 5]  736 	jsr	_setIgnitionSchedule
   8C92 A7 07         [ 2]  737 	ais	#7
   8C94 20 1F         [ 3]  738 	bra	00115$
   8C96                     739 00113$:
                            740 ;decoders.c:97: setIgnitionSchedule(&ignitionSchedule2, timeToDwell, dwellTime, 2);
   8C96 A6 02         [ 2]  741 	lda	#0x02
   8C98 87            [ 2]  742 	psha
   8C99 95            [ 2]  743 	tsx
   8C9A E6 0D         [ 3]  744 	lda	13,x
   8C9C 87            [ 2]  745 	psha
   8C9D E6 0C         [ 3]  746 	lda	12,x
   8C9F 87            [ 2]  747 	psha
   8CA0 E6 08         [ 3]  748 	lda	8,x
   8CA2 87            [ 2]  749 	psha
   8CA3 E6 07         [ 3]  750 	lda	7,x
   8CA5 87            [ 2]  751 	psha
   8CA6 E6 06         [ 3]  752 	lda	6,x
   8CA8 87            [ 2]  753 	psha
   8CA9 E6 05         [ 3]  754 	lda	5,x
   8CAB 87            [ 2]  755 	psha
   8CAC A6 CB         [ 2]  756 	lda	#_ignitionSchedule2
   8CAE AE 01         [ 2]  757 	ldx	#>_ignitionSchedule2
   8CB0 CD 85 80      [ 5]  758 	jsr	_setIgnitionSchedule
   8CB3 A7 07         [ 2]  759 	ais	#7
   8CB5                     760 00115$:
                            761 ;decoders.c:99: }
   8CB5 A7 0F         [ 2]  762 	ais	#15
   8CB7 81            [ 4]  763 	rts
                            764 ;------------------------------------------------------------
                            765 ;Allocation info for local variables in function 'triggerPri_MissingTooth'
                            766 ;------------------------------------------------------------
                            767 ;curTime                   Allocated to stack - sp +18
                            768 ;baseGap                   Allocated to stack - sp +14
                            769 ;dynamicThreshold          Allocated to stack - sp +10
                            770 ;isCranking                Allocated to stack - sp +21
                            771 ;isGap                     Allocated to registers 
                            772 ;expectedPulses            Allocated to stack - sp +19
                            773 ;toleranceWindow           Allocated to stack - sp +17
                            774 ;sloc0                     Allocated to stack - sp +9
                            775 ;sloc1                     Allocated to stack - sp +1
                            776 ;sloc2                     Allocated to stack - sp +13
                            777 ;sloc3                     Allocated to stack - sp +5
                            778 ;------------------------------------------------------------
                            779 ;decoders.c:104: static void triggerPri_MissingTooth(void) {
                            780 ;	-----------------------------------------
                            781 ;	 function triggerPri_MissingTooth
                            782 ;	-----------------------------------------
                            783 ;	Register assignment might be sub-optimal.
                            784 ;	Stack space usage: 21 bytes.
   8CB8                     785 _triggerPri_MissingTooth:
   8CB8 A7 EB         [ 2]  786 	ais	#-21
                            787 ;decoders.c:105: uint32_t curTime = micros();
   8CBA CD 80 4F      [ 5]  788 	jsr	_micros
   8CBD 9E E7 0C      [ 4]  789 	sta	12,s
   8CC0 9E EF 0B      [ 4]  790 	stx	11,s
   8CC3 B6 4A         [ 3]  791 	lda	*___SDCC_hc08_ret2
   8CC5 9E E7 0A      [ 4]  792 	sta	10,s
   8CC8 B6 4B         [ 3]  793 	lda	*___SDCC_hc08_ret3
   8CCA 9E E7 09      [ 4]  794 	sta	9,s
                            795 ;decoders.c:109: triggerState.curGap = curTime - triggerState.toothLastToothTime;
   8CCD C6 00 FC      [ 4]  796 	lda	_triggerState
   8CD0 9E E7 01      [ 4]  797 	sta	1,s
   8CD3 C6 00 FD      [ 4]  798 	lda	(_triggerState + 1)
   8CD6 9E E7 02      [ 4]  799 	sta	2,s
   8CD9 C6 00 FE      [ 4]  800 	lda	(_triggerState + 2)
   8CDC 9E E7 03      [ 4]  801 	sta	3,s
   8CDF C6 00 FF      [ 4]  802 	lda	(_triggerState + 3)
   8CE2 9E E7 04      [ 4]  803 	sta	4,s
   8CE5 95            [ 2]  804 	tsx
   8CE6 E6 0B         [ 3]  805 	lda	11,x
   8CE8 E0 03         [ 3]  806 	sub	3,x
   8CEA E7 03         [ 3]  807 	sta	3,x
   8CEC E6 0A         [ 3]  808 	lda	10,x
   8CEE E2 02         [ 3]  809 	sbc	2,x
   8CF0 E7 02         [ 3]  810 	sta	2,x
   8CF2 E6 09         [ 3]  811 	lda	9,x
   8CF4 E2 01         [ 3]  812 	sbc	1,x
   8CF6 E7 01         [ 3]  813 	sta	1,x
   8CF8 E6 08         [ 3]  814 	lda	8,x
   8CFA F2            [ 2]  815 	sbc	,x
   8CFB F7            [ 2]  816 	sta	,x
   8CFC F6            [ 2]  817 	lda	,x
   8CFD C7 01 0F      [ 4]  818 	sta	(_triggerState + 0x0013)
   8D00 E6 01         [ 3]  819 	lda	1,x
   8D02 C7 01 10      [ 4]  820 	sta	((_triggerState + 0x0013) + 1)
   8D05 E6 02         [ 3]  821 	lda	2,x
   8D07 C7 01 11      [ 4]  822 	sta	((_triggerState + 0x0013) + 2)
   8D0A E6 03         [ 3]  823 	lda	3,x
   8D0C C7 01 12      [ 4]  824 	sta	((_triggerState + 0x0013) + 3)
                            825 ;decoders.c:111: if (triggerState.curGap < 50) return;
   8D0F C6 01 0F      [ 4]  826 	lda	(_triggerState + 0x0013)
   8D12 F7            [ 2]  827 	sta	,x
   8D13 C6 01 10      [ 4]  828 	lda	((_triggerState + 0x0013) + 1)
   8D16 E7 01         [ 3]  829 	sta	1,x
   8D18 C6 01 11      [ 4]  830 	lda	((_triggerState + 0x0013) + 2)
   8D1B E7 02         [ 3]  831 	sta	2,x
   8D1D C6 01 12      [ 4]  832 	lda	((_triggerState + 0x0013) + 3)
   8D20 E7 03         [ 3]  833 	sta	3,x
   8D22 E6 03         [ 3]  834 	lda	3,x
   8D24 A0 32         [ 2]  835 	sub	#0x32
   8D26 E6 02         [ 3]  836 	lda	2,x
   8D28 A2 00         [ 2]  837 	sbc	#0x00
   8D2A E6 01         [ 3]  838 	lda	1,x
   8D2C A2 00         [ 2]  839 	sbc	#0x00
   8D2E F6            [ 2]  840 	lda	,x
   8D2F A2 00         [ 2]  841 	sbc	#0x00
   8D31 24 03         [ 3]  842 	bcc	00102$
   8D33 CC 90 E4      [ 3]  843 	jmp	00120$
   8D36                     844 00102$:
                            845 ;decoders.c:112: if (triggerState.lastGap > 0 && triggerState.curGap < (triggerState.lastGap / 3)) return;
   8D36 C6 01 13      [ 4]  846 	lda	(_triggerState + 0x0017)
   8D39 9E E7 01      [ 4]  847 	sta	1,s
   8D3C C6 01 14      [ 4]  848 	lda	((_triggerState + 0x0017) + 1)
   8D3F 9E E7 02      [ 4]  849 	sta	2,s
   8D42 C6 01 15      [ 4]  850 	lda	((_triggerState + 0x0017) + 2)
   8D45 9E E7 03      [ 4]  851 	sta	3,s
   8D48 C6 01 16      [ 4]  852 	lda	((_triggerState + 0x0017) + 3)
   8D4B 9E E7 04      [ 4]  853 	sta	4,s
   8D4E 95            [ 2]  854 	tsx
   8D4F F6            [ 2]  855 	lda	,x
   8D50 EA 01         [ 3]  856 	ora	1,x
   8D52 EA 02         [ 3]  857 	ora	2,x
   8D54 EA 03         [ 3]  858 	ora	3,x
   8D56 27 64         [ 3]  859 	beq	00104$
   8D58 C6 01 0F      [ 4]  860 	lda	(_triggerState + 0x0013)
   8D5B F7            [ 2]  861 	sta	,x
   8D5C C6 01 10      [ 4]  862 	lda	((_triggerState + 0x0013) + 1)
   8D5F E7 01         [ 3]  863 	sta	1,x
   8D61 C6 01 11      [ 4]  864 	lda	((_triggerState + 0x0013) + 2)
   8D64 E7 02         [ 3]  865 	sta	2,x
   8D66 C6 01 12      [ 4]  866 	lda	((_triggerState + 0x0013) + 3)
   8D69 E7 03         [ 3]  867 	sta	3,x
   8D6B C6 01 13      [ 4]  868 	lda	(_triggerState + 0x0017)
   8D6E E7 0C         [ 3]  869 	sta	12,x
   8D70 C6 01 14      [ 4]  870 	lda	((_triggerState + 0x0017) + 1)
   8D73 E7 0D         [ 3]  871 	sta	13,x
   8D75 C6 01 15      [ 4]  872 	lda	((_triggerState + 0x0017) + 2)
   8D78 E7 0E         [ 3]  873 	sta	14,x
   8D7A C6 01 16      [ 4]  874 	lda	((_triggerState + 0x0017) + 3)
   8D7D E7 0F         [ 3]  875 	sta	15,x
   8D7F A6 03         [ 2]  876 	lda	#0x03
   8D81 87            [ 2]  877 	psha
   8D82 4F            [ 1]  878 	clra
   8D83 87            [ 2]  879 	psha
   8D84 87            [ 2]  880 	psha
   8D85 87            [ 2]  881 	psha
   8D86 E6 0F         [ 3]  882 	lda	15,x
   8D88 87            [ 2]  883 	psha
   8D89 E6 0E         [ 3]  884 	lda	14,x
   8D8B 87            [ 2]  885 	psha
   8D8C E6 0D         [ 3]  886 	lda	13,x
   8D8E 87            [ 2]  887 	psha
   8D8F E6 0C         [ 3]  888 	lda	12,x
   8D91 87            [ 2]  889 	psha
   8D92 CD CF 5C      [ 5]  890 	jsr	__divulong
   8D95 9E E7 18      [ 4]  891 	sta	24,s
   8D98 9E EF 17      [ 4]  892 	stx	23,s
   8D9B B6 4A         [ 3]  893 	lda	*___SDCC_hc08_ret2
   8D9D 9E E7 16      [ 4]  894 	sta	22,s
   8DA0 B6 4B         [ 3]  895 	lda	*___SDCC_hc08_ret3
   8DA2 9E E7 15      [ 4]  896 	sta	21,s
   8DA5 A7 08         [ 2]  897 	ais	#8
   8DA7 95            [ 2]  898 	tsx
   8DA8 E6 03         [ 3]  899 	lda	3,x
   8DAA E0 0F         [ 3]  900 	sub	15,x
   8DAC E6 02         [ 3]  901 	lda	2,x
   8DAE E2 0E         [ 3]  902 	sbc	14,x
   8DB0 E6 01         [ 3]  903 	lda	1,x
   8DB2 E2 0D         [ 3]  904 	sbc	13,x
   8DB4 F6            [ 2]  905 	lda	,x
   8DB5 E2 0C         [ 3]  906 	sbc	12,x
   8DB7 24 03         [ 3]  907 	bcc	00104$
   8DB9 CC 90 E4      [ 3]  908 	jmp	00120$
   8DBC                     909 00104$:
                            910 ;decoders.c:114: triggerState.toothLastToothTime = curTime;
   8DBC 9E E6 09      [ 4]  911 	lda	9,s
   8DBF C7 00 FC      [ 4]  912 	sta	_triggerState
   8DC2 9E E6 0A      [ 4]  913 	lda	10,s
   8DC5 C7 00 FD      [ 4]  914 	sta	(_triggerState + 1)
   8DC8 9E E6 0B      [ 4]  915 	lda	11,s
   8DCB C7 00 FE      [ 4]  916 	sta	(_triggerState + 2)
   8DCE 9E E6 0C      [ 4]  917 	lda	12,s
   8DD1 C7 00 FF      [ 4]  918 	sta	(_triggerState + 3)
                            919 ;decoders.c:115: triggerState.toothCurrentCount++;
   8DD4 C6 01 0C      [ 4]  920 	lda	(_triggerState + 0x0010)
   8DD7 4C            [ 1]  921 	inca
   8DD8 C7 01 0C      [ 4]  922 	sta	(_triggerState + 0x0010)
                            923 ;decoders.c:117: if (triggerState.toothCurrentCount > (uint8_t)(triggerState.toothTotalCount * 2)) {
   8DDB CE 01 0C      [ 4]  924 	ldx	(_triggerState + 0x0010)
   8DDE C6 01 0D      [ 4]  925 	lda	(_triggerState + 0x0011)
   8DE1 48            [ 1]  926 	lsla	
   8DE2 9E E7 0D      [ 4]  927 	sta	13,s
   8DE5 9E E3 0D      [ 4]  928 	cpx	13,s
   8DE8 23 09         [ 3]  929 	bls	00107$
                            930 ;decoders.c:118: triggerState.toothCurrentCount = 1;
   8DEA A6 01         [ 2]  931 	lda	#0x01
   8DEC C7 01 0C      [ 4]  932 	sta	(_triggerState + 0x0010)
                            933 ;decoders.c:119: triggerState.hasSync = false;
   8DEF 4A            [ 1]  934 	deca
   8DF0 C7 01 17      [ 4]  935 	sta	(_triggerState + 0x001b)
   8DF3                     936 00107$:
                            937 ;decoders.c:122: isCranking = (currentStatus.RPM > 0) &&
   8DF3 C6 00 5F      [ 4]  938 	lda	_currentStatus
   8DF6 9E E7 0D      [ 4]  939 	sta	13,s
   8DF9 C6 00 60      [ 4]  940 	lda	(_currentStatus + 1)
   8DFC 9E E7 0E      [ 4]  941 	sta	14,s
   8DFF 95            [ 2]  942 	tsx
   8E00 E6 0D         [ 3]  943 	lda	13,x
   8E02 EA 0C         [ 3]  944 	ora	12,x
   8E04 27 22         [ 3]  945 	beq	00122$
                            946 ;decoders.c:123: (currentStatus.RPM < ((uint16_t)configPage1.crankRPM * 10));
   8E06 C6 00 B9      [ 4]  947 	lda	(_configPage1 + 0x001d)
   8E09 5F            [ 1]  948 	clrx
   8E0A 87            [ 2]  949 	psha
   8E0B 89            [ 2]  950 	pshx
   8E0C A6 0A         [ 2]  951 	lda	#0x0a
   8E0E CD CE 65      [ 5]  952 	jsr	__mulint
   8E11 9E E7 04      [ 4]  953 	sta	4,s
   8E14 9E EF 03      [ 4]  954 	stx	3,s
   8E17 A7 02         [ 2]  955 	ais	#2
   8E19 9E E6 0E      [ 4]  956 	lda	14,s
   8E1C 9E EE 0D      [ 4]  957 	ldx	13,s
   8E1F 9E E0 02      [ 4]  958 	sub	2,s
   8E22 9F            [ 1]  959 	txa
   8E23 9E E2 01      [ 4]  960 	sbc	1,s
   8E26 25 03         [ 3]  961 	bcs	00123$
   8E28                     962 00122$:
   8E28 4F            [ 1]  963 	clra
   8E29 20 02         [ 3]  964 	bra	00124$
   8E2B                     965 00123$:
   8E2B A6 01         [ 2]  966 	lda	#0x01
   8E2D                     967 00124$:
   8E2D 9E E7 15      [ 4]  968 	sta	21,s
                            969 ;decoders.c:125: baseGap = (triggerState.lastGap > 0) ? triggerState.lastGap : triggerState.curGap;
   8E30 C6 01 13      [ 4]  970 	lda	(_triggerState + 0x0017)
   8E33 9E E7 0D      [ 4]  971 	sta	13,s
   8E36 C6 01 14      [ 4]  972 	lda	((_triggerState + 0x0017) + 1)
   8E39 9E E7 0E      [ 4]  973 	sta	14,s
   8E3C C6 01 15      [ 4]  974 	lda	((_triggerState + 0x0017) + 2)
   8E3F 9E E7 0F      [ 4]  975 	sta	15,s
   8E42 C6 01 16      [ 4]  976 	lda	((_triggerState + 0x0017) + 3)
   8E45 9E E7 10      [ 4]  977 	sta	16,s
   8E48 95            [ 2]  978 	tsx
   8E49 E6 0C         [ 3]  979 	lda	12,x
   8E4B EA 0D         [ 3]  980 	ora	13,x
   8E4D EA 0E         [ 3]  981 	ora	14,x
   8E4F EA 0F         [ 3]  982 	ora	15,x
   8E51 27 16         [ 3]  983 	beq	00125$
   8E53 C6 01 13      [ 4]  984 	lda	(_triggerState + 0x0017)
   8E56 E7 0C         [ 3]  985 	sta	12,x
   8E58 C6 01 14      [ 4]  986 	lda	((_triggerState + 0x0017) + 1)
   8E5B E7 0D         [ 3]  987 	sta	13,x
   8E5D C6 01 15      [ 4]  988 	lda	((_triggerState + 0x0017) + 2)
   8E60 E7 0E         [ 3]  989 	sta	14,x
   8E62 C6 01 16      [ 4]  990 	lda	((_triggerState + 0x0017) + 3)
   8E65 E7 0F         [ 3]  991 	sta	15,x
   8E67 20 18         [ 3]  992 	bra	00126$
   8E69                     993 00125$:
   8E69 C6 01 0F      [ 4]  994 	lda	(_triggerState + 0x0013)
   8E6C 9E E7 0D      [ 4]  995 	sta	13,s
   8E6F C6 01 10      [ 4]  996 	lda	((_triggerState + 0x0013) + 1)
   8E72 9E E7 0E      [ 4]  997 	sta	14,s
   8E75 C6 01 11      [ 4]  998 	lda	((_triggerState + 0x0013) + 2)
   8E78 9E E7 0F      [ 4]  999 	sta	15,s
   8E7B C6 01 12      [ 4] 1000 	lda	((_triggerState + 0x0013) + 3)
   8E7E 9E E7 10      [ 4] 1001 	sta	16,s
   8E81                    1002 00126$:
                           1003 ;decoders.c:126: dynamicThreshold = isCranking ? (baseGap + ((baseGap * 2) / 5))
   8E81 9E 6D 15      [ 4] 1004 	tst	21,s
   8E84 27 5D         [ 3] 1005 	beq	00127$
   8E86 95            [ 2] 1006 	tsx
   8E87 E6 0F         [ 3] 1007 	lda	15,x
   8E89 EE 0E         [ 3] 1008 	ldx	14,x
   8E8B 48            [ 1] 1009 	lsla
   8E8C 59            [ 1] 1010 	rolx
   8E8D 9E E7 04      [ 4] 1011 	sta	4,s
   8E90 9E EF 03      [ 4] 1012 	stx	3,s
   8E93 9E E6 0E      [ 4] 1013 	lda	14,s
   8E96 9E EE 0D      [ 4] 1014 	ldx	13,s
   8E99 49            [ 1] 1015 	rola
   8E9A 59            [ 1] 1016 	rolx
   8E9B 9E E7 02      [ 4] 1017 	sta	2,s
   8E9E 9E EF 01      [ 4] 1018 	stx	1,s
   8EA1 A6 05         [ 2] 1019 	lda	#0x05
   8EA3 87            [ 2] 1020 	psha
   8EA4 4F            [ 1] 1021 	clra
   8EA5 87            [ 2] 1022 	psha
   8EA6 87            [ 2] 1023 	psha
   8EA7 87            [ 2] 1024 	psha
   8EA8 95            [ 2] 1025 	tsx
   8EA9 E6 07         [ 3] 1026 	lda	7,x
   8EAB 87            [ 2] 1027 	psha
   8EAC E6 06         [ 3] 1028 	lda	6,x
   8EAE 87            [ 2] 1029 	psha
   8EAF E6 05         [ 3] 1030 	lda	5,x
   8EB1 87            [ 2] 1031 	psha
   8EB2 E6 04         [ 3] 1032 	lda	4,x
   8EB4 87            [ 2] 1033 	psha
   8EB5 CD CF 5C      [ 5] 1034 	jsr	__divulong
   8EB8 9E E7 0C      [ 4] 1035 	sta	12,s
   8EBB 9E EF 0B      [ 4] 1036 	stx	11,s
   8EBE B6 4A         [ 3] 1037 	lda	*___SDCC_hc08_ret2
   8EC0 9E E7 0A      [ 4] 1038 	sta	10,s
   8EC3 B6 4B         [ 3] 1039 	lda	*___SDCC_hc08_ret3
   8EC5 9E E7 09      [ 4] 1040 	sta	9,s
   8EC8 A7 08         [ 2] 1041 	ais	#8
   8ECA 95            [ 2] 1042 	tsx
   8ECB E6 0F         [ 3] 1043 	lda	15,x
   8ECD EB 03         [ 3] 1044 	add	3,x
   8ECF E7 03         [ 3] 1045 	sta	3,x
   8ED1 E6 0E         [ 3] 1046 	lda	14,x
   8ED3 E9 02         [ 3] 1047 	adc	2,x
   8ED5 E7 02         [ 3] 1048 	sta	2,x
   8ED7 E6 0D         [ 3] 1049 	lda	13,x
   8ED9 E9 01         [ 3] 1050 	adc	1,x
   8EDB E7 01         [ 3] 1051 	sta	1,x
   8EDD E6 0C         [ 3] 1052 	lda	12,x
   8EDF F9            [ 2] 1053 	adc	,x
   8EE0 F7            [ 2] 1054 	sta	,x
   8EE1 20 33         [ 3] 1055 	bra	00128$
   8EE3                    1056 00127$:
                           1057 ;decoders.c:127: : (baseGap + (baseGap >> 1));
   8EE3 95            [ 2] 1058 	tsx
   8EE4 E6 0D         [ 3] 1059 	lda	13,x
   8EE6 EE 0C         [ 3] 1060 	ldx	12,x
   8EE8 54            [ 1] 1061 	lsrx
   8EE9 46            [ 1] 1062 	rora
   8EEA 9E E7 06      [ 4] 1063 	sta	6,s
   8EED 9E EF 05      [ 4] 1064 	stx	5,s
   8EF0 9E E6 10      [ 4] 1065 	lda	16,s
   8EF3 9E EE 0F      [ 4] 1066 	ldx	15,s
   8EF6 56            [ 1] 1067 	rorx
   8EF7 46            [ 1] 1068 	rora
   8EF8 9E E7 08      [ 4] 1069 	sta	8,s
   8EFB 9E EF 07      [ 4] 1070 	stx	7,s
   8EFE 95            [ 2] 1071 	tsx
   8EFF E6 0F         [ 3] 1072 	lda	15,x
   8F01 EB 07         [ 3] 1073 	add	7,x
   8F03 E7 03         [ 3] 1074 	sta	3,x
   8F05 E6 0E         [ 3] 1075 	lda	14,x
   8F07 E9 06         [ 3] 1076 	adc	6,x
   8F09 E7 02         [ 3] 1077 	sta	2,x
   8F0B E6 0D         [ 3] 1078 	lda	13,x
   8F0D E9 05         [ 3] 1079 	adc	5,x
   8F0F E7 01         [ 3] 1080 	sta	1,x
   8F11 E6 0C         [ 3] 1081 	lda	12,x
   8F13 E9 04         [ 3] 1082 	adc	4,x
   8F15 F7            [ 2] 1083 	sta	,x
   8F16                    1084 00128$:
                           1085 ;decoders.c:128: isGap = (triggerState.curGap > dynamicThreshold);
   8F16 C6 01 0F      [ 4] 1086 	lda	(_triggerState + 0x0013)
   8F19 9E E7 05      [ 4] 1087 	sta	5,s
   8F1C C6 01 10      [ 4] 1088 	lda	((_triggerState + 0x0013) + 1)
   8F1F 9E E7 06      [ 4] 1089 	sta	6,s
   8F22 C6 01 11      [ 4] 1090 	lda	((_triggerState + 0x0013) + 2)
   8F25 9E E7 07      [ 4] 1091 	sta	7,s
   8F28 C6 01 12      [ 4] 1092 	lda	((_triggerState + 0x0013) + 3)
   8F2B 9E E7 08      [ 4] 1093 	sta	8,s
   8F2E 95            [ 2] 1094 	tsx
   8F2F E6 03         [ 3] 1095 	lda	3,x
   8F31 E0 07         [ 3] 1096 	sub	7,x
   8F33 E6 02         [ 3] 1097 	lda	2,x
   8F35 E2 06         [ 3] 1098 	sbc	6,x
   8F37 E6 01         [ 3] 1099 	lda	1,x
   8F39 E2 05         [ 3] 1100 	sbc	5,x
   8F3B F6            [ 2] 1101 	lda	,x
   8F3C E2 04         [ 3] 1102 	sbc	4,x
   8F3E 25 03         [ 3] 1103 	bcs	00216$
   8F40 CC 90 B4      [ 3] 1104 	jmp	00119$
   8F43                    1105 00216$:
                           1106 ;decoders.c:130: if (isGap) {
                           1107 ;decoders.c:131: uint16_t expectedPulses = (uint16_t)triggerState.triggerActualTeeth * triggerEdgesPerTooth;
   8F43 C6 01 0E      [ 4] 1108 	lda	(_triggerState + 0x0012)
   8F46 E7 05         [ 3] 1109 	sta	5,x
   8F48 5F            [ 1] 1110 	clrx
   8F49 9E EF 05      [ 4] 1111 	stx	5,s
   8F4C C6 01 D4      [ 4] 1112 	lda	_triggerEdgesPerTooth
   8F4F 87            [ 2] 1113 	psha
   8F50 89            [ 2] 1114 	pshx
   8F51 95            [ 2] 1115 	tsx
   8F52 E6 07         [ 3] 1116 	lda	7,x
   8F54 EE 06         [ 3] 1117 	ldx	6,x
   8F56 CD CE 65      [ 5] 1118 	jsr	__mulint
   8F59 9E E7 16      [ 4] 1119 	sta	22,s
   8F5C 9E EF 15      [ 4] 1120 	stx	21,s
   8F5F A7 02         [ 2] 1121 	ais	#2
                           1122 ;decoders.c:132: uint16_t toleranceWindow = isCranking ? 20 : 10;
   8F61 9E 6D 15      [ 4] 1123 	tst	21,s
   8F64 27 05         [ 3] 1124 	beq	00129$
   8F66 5F            [ 1] 1125 	clrx
   8F67 A6 14         [ 2] 1126 	lda	#0x14
   8F69 20 03         [ 3] 1127 	bra	00130$
   8F6B                    1128 00129$:
   8F6B 5F            [ 1] 1129 	clrx
   8F6C A6 0A         [ 2] 1130 	lda	#0x0a
   8F6E                    1131 00130$:
   8F6E 9E E7 12      [ 4] 1132 	sta	18,s
   8F71 9E EF 11      [ 4] 1133 	stx	17,s
                           1134 ;decoders.c:134: if (triggerState.toothCurrentCount >= (expectedPulses - toleranceWindow) &&
   8F74 CE 01 0C      [ 4] 1135 	ldx	(_triggerState + 0x0010)
   8F77 9E E6 14      [ 4] 1136 	lda	20,s
   8F7A 9E E0 12      [ 4] 1137 	sub	18,s
   8F7D 9E E7 06      [ 4] 1138 	sta	6,s
   8F80 9E E6 13      [ 4] 1139 	lda	19,s
   8F83 9E E2 11      [ 4] 1140 	sbc	17,s
   8F86 9E E7 05      [ 4] 1141 	sta	5,s
   8F89 9F            [ 1] 1142 	txa
   8F8A 5F            [ 1] 1143 	clrx
   8F8B 9E E0 06      [ 4] 1144 	sub	6,s
   8F8E 9F            [ 1] 1145 	txa
   8F8F 9E E2 05      [ 4] 1146 	sbc	5,s
   8F92 24 03         [ 3] 1147 	bcc	00218$
   8F94 CC 90 9D      [ 3] 1148 	jmp	00115$
   8F97                    1149 00218$:
                           1150 ;decoders.c:135: triggerState.toothCurrentCount <= (expectedPulses + toleranceWindow)) {
   8F97 C6 01 0C      [ 4] 1151 	lda	(_triggerState + 0x0010)
   8F9A 87            [ 2] 1152 	psha
   8F9B 9E E6 13      [ 4] 1153 	lda	19,s
   8F9E 9E EB 15      [ 4] 1154 	add	21,s
   8FA1 97            [ 1] 1155 	tax
   8FA2 9E E6 12      [ 4] 1156 	lda	18,s
   8FA5 9E E9 14      [ 4] 1157 	adc	20,s
   8FA8 87            [ 2] 1158 	psha
   8FA9 8A            [ 2] 1159 	pulh
   8FAA 86            [ 2] 1160 	pula
   8FAB 9E E7 06      [ 4] 1161 	sta	6,s
   8FAE 87            [ 2] 1162 	psha
   8FAF 4F            [ 1] 1163 	clra
   8FB0 9E E7 06      [ 4] 1164 	sta	6,s
   8FB3 86            [ 2] 1165 	pula
   8FB4 9F            [ 1] 1166 	txa
   8FB5 9E E0 06      [ 4] 1167 	sub	6,s
   8FB8 8B            [ 2] 1168 	pshh
   8FB9 86            [ 2] 1169 	pula
   8FBA 9E E2 05      [ 4] 1170 	sbc	5,s
   8FBD 24 03         [ 3] 1171 	bcc	00219$
   8FBF CC 90 9D      [ 3] 1172 	jmp	00115$
   8FC2                    1173 00219$:
                           1174 ;decoders.c:137: triggerState.hasSync = true;
   8FC2 A6 01         [ 2] 1175 	lda	#0x01
   8FC4 C7 01 17      [ 4] 1176 	sta	(_triggerState + 0x001b)
                           1177 ;decoders.c:138: triggerState.syncLossCounter = 0;
   8FC7 4A            [ 1] 1178 	deca
   8FC8 C7 01 18      [ 4] 1179 	sta	(_triggerState + 0x001c)
                           1180 ;decoders.c:139: triggerState.toothOneTime = curTime;
   8FCB 9E E6 09      [ 4] 1181 	lda	9,s
   8FCE C7 01 08      [ 4] 1182 	sta	(_triggerState + 0x000c)
   8FD1 9E E6 0A      [ 4] 1183 	lda	10,s
   8FD4 C7 01 09      [ 4] 1184 	sta	((_triggerState + 0x000c) + 1)
   8FD7 9E E6 0B      [ 4] 1185 	lda	11,s
   8FDA C7 01 0A      [ 4] 1186 	sta	((_triggerState + 0x000c) + 2)
   8FDD 9E E6 0C      [ 4] 1187 	lda	12,s
   8FE0 C7 01 0B      [ 4] 1188 	sta	((_triggerState + 0x000c) + 3)
                           1189 ;decoders.c:141: if (triggerState.toothLastMinusOneTime > 0) {
   8FE3 C6 01 00      [ 4] 1190 	lda	(_triggerState + 0x0004)
   8FE6 9E E7 05      [ 4] 1191 	sta	5,s
   8FE9 C6 01 01      [ 4] 1192 	lda	((_triggerState + 0x0004) + 1)
   8FEC 9E E7 06      [ 4] 1193 	sta	6,s
   8FEF C6 01 02      [ 4] 1194 	lda	((_triggerState + 0x0004) + 2)
   8FF2 9E E7 07      [ 4] 1195 	sta	7,s
   8FF5 C6 01 03      [ 4] 1196 	lda	((_triggerState + 0x0004) + 3)
   8FF8 9E E7 08      [ 4] 1197 	sta	8,s
   8FFB 95            [ 2] 1198 	tsx
   8FFC E6 04         [ 3] 1199 	lda	4,x
   8FFE EA 05         [ 3] 1200 	ora	5,x
   9000 EA 06         [ 3] 1201 	ora	6,x
   9002 EA 07         [ 3] 1202 	ora	7,x
   9004 27 40         [ 3] 1203 	beq	00109$
                           1204 ;decoders.c:142: triggerState.revolutionTime = curTime - triggerState.toothLastMinusOneTime;
   9006 C6 01 00      [ 4] 1205 	lda	(_triggerState + 0x0004)
   9009 E7 04         [ 3] 1206 	sta	4,x
   900B C6 01 01      [ 4] 1207 	lda	((_triggerState + 0x0004) + 1)
   900E E7 05         [ 3] 1208 	sta	5,x
   9010 C6 01 02      [ 4] 1209 	lda	((_triggerState + 0x0004) + 2)
   9013 E7 06         [ 3] 1210 	sta	6,x
   9015 C6 01 03      [ 4] 1211 	lda	((_triggerState + 0x0004) + 3)
   9018 E7 07         [ 3] 1212 	sta	7,x
   901A E6 0B         [ 3] 1213 	lda	11,x
   901C E0 07         [ 3] 1214 	sub	7,x
   901E E7 07         [ 3] 1215 	sta	7,x
   9020 E6 0A         [ 3] 1216 	lda	10,x
   9022 E2 06         [ 3] 1217 	sbc	6,x
   9024 E7 06         [ 3] 1218 	sta	6,x
   9026 E6 09         [ 3] 1219 	lda	9,x
   9028 E2 05         [ 3] 1220 	sbc	5,x
   902A E7 05         [ 3] 1221 	sta	5,x
   902C E6 08         [ 3] 1222 	lda	8,x
   902E E2 04         [ 3] 1223 	sbc	4,x
   9030 E7 04         [ 3] 1224 	sta	4,x
   9032 E6 04         [ 3] 1225 	lda	4,x
   9034 C7 01 04      [ 4] 1226 	sta	(_triggerState + 0x0008)
   9037 E6 05         [ 3] 1227 	lda	5,x
   9039 C7 01 05      [ 4] 1228 	sta	((_triggerState + 0x0008) + 1)
   903C E6 06         [ 3] 1229 	lda	6,x
   903E C7 01 06      [ 4] 1230 	sta	((_triggerState + 0x0008) + 2)
   9041 E6 07         [ 3] 1231 	lda	7,x
   9043 C7 01 07      [ 4] 1232 	sta	((_triggerState + 0x0008) + 3)
   9046                    1233 00109$:
                           1234 ;decoders.c:144: triggerState.toothLastMinusOneTime = curTime;
   9046 9E E6 09      [ 4] 1235 	lda	9,s
   9049 C7 01 00      [ 4] 1236 	sta	(_triggerState + 0x0004)
   904C 9E E6 0A      [ 4] 1237 	lda	10,s
   904F C7 01 01      [ 4] 1238 	sta	((_triggerState + 0x0004) + 1)
   9052 9E E6 0B      [ 4] 1239 	lda	11,s
   9055 C7 01 02      [ 4] 1240 	sta	((_triggerState + 0x0004) + 2)
   9058 9E E6 0C      [ 4] 1241 	lda	12,s
   905B C7 01 03      [ 4] 1242 	sta	((_triggerState + 0x0004) + 3)
                           1243 ;decoders.c:145: triggerState.toothCurrentCount = 1;
   905E A6 01         [ 2] 1244 	lda	#0x01
   9060 C7 01 0C      [ 4] 1245 	sta	(_triggerState + 0x0010)
                           1246 ;decoders.c:146: revolutionCounter = (revolutionCounter == 0) ? 1 : 0;
   9063 C6 01 D3      [ 4] 1247 	lda	_revolutionCounter
   9066 26 05         [ 3] 1248 	bne	00131$
   9068 5F            [ 1] 1249 	clrx
   9069 A6 01         [ 2] 1250 	lda	#0x01
   906B 20 02         [ 3] 1251 	bra	00132$
   906D                    1252 00131$:
   906D 5F            [ 1] 1253 	clrx
   906E 9F            [ 1] 1254 	txa
   906F                    1255 00132$:
   906F C7 01 D3      [ 4] 1256 	sta	_revolutionCounter
                           1257 ;decoders.c:148: if (triggerState.revolutionTime > 0) {
   9072 C6 01 04      [ 4] 1258 	lda	(_triggerState + 0x0008)
   9075 9E E7 05      [ 4] 1259 	sta	5,s
   9078 C6 01 05      [ 4] 1260 	lda	((_triggerState + 0x0008) + 1)
   907B 9E E7 06      [ 4] 1261 	sta	6,s
   907E C6 01 06      [ 4] 1262 	lda	((_triggerState + 0x0008) + 2)
   9081 9E E7 07      [ 4] 1263 	sta	7,s
   9084 C6 01 07      [ 4] 1264 	lda	((_triggerState + 0x0008) + 3)
   9087 9E E7 08      [ 4] 1265 	sta	8,s
   908A 95            [ 2] 1266 	tsx
   908B E6 04         [ 3] 1267 	lda	4,x
   908D EA 05         [ 3] 1268 	ora	5,x
   908F EA 06         [ 3] 1269 	ora	6,x
   9091 EA 07         [ 3] 1270 	ora	7,x
   9093 27 1F         [ 3] 1271 	beq	00119$
                           1272 ;decoders.c:149: scheduleInjectionISR();
   9095 CD 88 7B      [ 5] 1273 	jsr	_scheduleInjectionISR
                           1274 ;decoders.c:150: scheduleIgnitionISR();
   9098 CD 89 9D      [ 5] 1275 	jsr	_scheduleIgnitionISR
   909B 20 17         [ 3] 1276 	bra	00119$
   909D                    1277 00115$:
                           1278 ;decoders.c:153: triggerState.toothCurrentCount = 1;
   909D A6 01         [ 2] 1279 	lda	#0x01
   909F C7 01 0C      [ 4] 1280 	sta	(_triggerState + 0x0010)
                           1281 ;decoders.c:154: triggerState.syncLossCounter++;
   90A2 C6 01 18      [ 4] 1282 	lda	(_triggerState + 0x001c)
   90A5 4C            [ 1] 1283 	inca
   90A6 C7 01 18      [ 4] 1284 	sta	(_triggerState + 0x001c)
                           1285 ;decoders.c:155: if (triggerState.syncLossCounter > 10) {
   90A9 C6 01 18      [ 4] 1286 	lda	(_triggerState + 0x001c)
   90AC A1 0A         [ 2] 1287 	cmp	#0x0a
   90AE 23 04         [ 3] 1288 	bls	00119$
                           1289 ;decoders.c:156: triggerState.hasSync = false;
   90B0 4F            [ 1] 1290 	clra
   90B1 C7 01 17      [ 4] 1291 	sta	(_triggerState + 0x001b)
   90B4                    1292 00119$:
                           1293 ;decoders.c:161: triggerState.lastGap = triggerState.curGap;
   90B4 C6 01 0F      [ 4] 1294 	lda	(_triggerState + 0x0013)
   90B7 9E E7 05      [ 4] 1295 	sta	5,s
   90BA C6 01 10      [ 4] 1296 	lda	((_triggerState + 0x0013) + 1)
   90BD 9E E7 06      [ 4] 1297 	sta	6,s
   90C0 C6 01 11      [ 4] 1298 	lda	((_triggerState + 0x0013) + 2)
   90C3 9E E7 07      [ 4] 1299 	sta	7,s
   90C6 C6 01 12      [ 4] 1300 	lda	((_triggerState + 0x0013) + 3)
   90C9 9E E7 08      [ 4] 1301 	sta	8,s
   90CC 9E E6 05      [ 4] 1302 	lda	5,s
   90CF C7 01 13      [ 4] 1303 	sta	(_triggerState + 0x0017)
   90D2 9E E6 06      [ 4] 1304 	lda	6,s
   90D5 C7 01 14      [ 4] 1305 	sta	((_triggerState + 0x0017) + 1)
   90D8 9E E6 07      [ 4] 1306 	lda	7,s
   90DB C7 01 15      [ 4] 1307 	sta	((_triggerState + 0x0017) + 2)
   90DE 9E E6 08      [ 4] 1308 	lda	8,s
   90E1 C7 01 16      [ 4] 1309 	sta	((_triggerState + 0x0017) + 3)
   90E4                    1310 00120$:
                           1311 ;decoders.c:162: }
   90E4 A7 15         [ 2] 1312 	ais	#21
   90E6 81            [ 4] 1313 	rts
                           1314 ;------------------------------------------------------------
                           1315 ;Allocation info for local variables in function 'triggerPri_BasicDistributor'
                           1316 ;------------------------------------------------------------
                           1317 ;curTime                   Allocated to stack - sp +9
                           1318 ;sloc0                     Allocated to stack - sp +9
                           1319 ;sloc1                     Allocated to stack - sp +1
                           1320 ;sloc2                     Allocated to stack - sp +5
                           1321 ;------------------------------------------------------------
                           1322 ;decoders.c:164: static void triggerPri_BasicDistributor(void) {
                           1323 ;	-----------------------------------------
                           1324 ;	 function triggerPri_BasicDistributor
                           1325 ;	-----------------------------------------
                           1326 ;	Register assignment is optimal.
                           1327 ;	Stack space usage: 12 bytes.
   90E7                    1328 _triggerPri_BasicDistributor:
   90E7 A7 F4         [ 2] 1329 	ais	#-12
                           1330 ;decoders.c:165: uint32_t curTime = micros();
   90E9 CD 80 4F      [ 5] 1331 	jsr	_micros
   90EC 9E E7 0C      [ 4] 1332 	sta	12,s
   90EF 9E EF 0B      [ 4] 1333 	stx	11,s
   90F2 B6 4A         [ 3] 1334 	lda	*___SDCC_hc08_ret2
   90F4 9E E7 0A      [ 4] 1335 	sta	10,s
   90F7 B6 4B         [ 3] 1336 	lda	*___SDCC_hc08_ret3
   90F9 9E E7 09      [ 4] 1337 	sta	9,s
                           1338 ;decoders.c:167: triggerState.curGap = curTime - triggerState.toothLastToothTime;
   90FC C6 00 FC      [ 4] 1339 	lda	_triggerState
   90FF 9E E7 01      [ 4] 1340 	sta	1,s
   9102 C6 00 FD      [ 4] 1341 	lda	(_triggerState + 1)
   9105 9E E7 02      [ 4] 1342 	sta	2,s
   9108 C6 00 FE      [ 4] 1343 	lda	(_triggerState + 2)
   910B 9E E7 03      [ 4] 1344 	sta	3,s
   910E C6 00 FF      [ 4] 1345 	lda	(_triggerState + 3)
   9111 9E E7 04      [ 4] 1346 	sta	4,s
   9114 95            [ 2] 1347 	tsx
   9115 E6 0B         [ 3] 1348 	lda	11,x
   9117 E0 03         [ 3] 1349 	sub	3,x
   9119 E7 03         [ 3] 1350 	sta	3,x
   911B E6 0A         [ 3] 1351 	lda	10,x
   911D E2 02         [ 3] 1352 	sbc	2,x
   911F E7 02         [ 3] 1353 	sta	2,x
   9121 E6 09         [ 3] 1354 	lda	9,x
   9123 E2 01         [ 3] 1355 	sbc	1,x
   9125 E7 01         [ 3] 1356 	sta	1,x
   9127 E6 08         [ 3] 1357 	lda	8,x
   9129 F2            [ 2] 1358 	sbc	,x
   912A F7            [ 2] 1359 	sta	,x
   912B F6            [ 2] 1360 	lda	,x
   912C C7 01 0F      [ 4] 1361 	sta	(_triggerState + 0x0013)
   912F E6 01         [ 3] 1362 	lda	1,x
   9131 C7 01 10      [ 4] 1363 	sta	((_triggerState + 0x0013) + 1)
   9134 E6 02         [ 3] 1364 	lda	2,x
   9136 C7 01 11      [ 4] 1365 	sta	((_triggerState + 0x0013) + 2)
   9139 E6 03         [ 3] 1366 	lda	3,x
   913B C7 01 12      [ 4] 1367 	sta	((_triggerState + 0x0013) + 3)
                           1368 ;decoders.c:168: if (triggerState.curGap < triggerState.triggerFilterTime) return;
   913E C6 01 0F      [ 4] 1369 	lda	(_triggerState + 0x0013)
   9141 F7            [ 2] 1370 	sta	,x
   9142 C6 01 10      [ 4] 1371 	lda	((_triggerState + 0x0013) + 1)
   9145 E7 01         [ 3] 1372 	sta	1,x
   9147 C6 01 11      [ 4] 1373 	lda	((_triggerState + 0x0013) + 2)
   914A E7 02         [ 3] 1374 	sta	2,x
   914C C6 01 12      [ 4] 1375 	lda	((_triggerState + 0x0013) + 3)
   914F E7 03         [ 3] 1376 	sta	3,x
   9151 C6 01 21      [ 4] 1377 	lda	(_triggerState + 0x0025)
   9154 87            [ 2] 1378 	psha
   9155 8A            [ 2] 1379 	pulh
   9156 CE 01 22      [ 4] 1380 	ldx	((_triggerState + 0x0025) + 1)
   9159 9E EF 08      [ 4] 1381 	stx	8,s
   915C 8B            [ 2] 1382 	pshh
   915D 86            [ 2] 1383 	pula
   915E 9E E7 07      [ 4] 1384 	sta	7,s
   9161 4F            [ 1] 1385 	clra
   9162 9E E7 06      [ 4] 1386 	sta	6,s
   9165 9E E7 05      [ 4] 1387 	sta	5,s
   9168 95            [ 2] 1388 	tsx
   9169 E6 03         [ 3] 1389 	lda	3,x
   916B E0 07         [ 3] 1390 	sub	7,x
   916D E6 02         [ 3] 1391 	lda	2,x
   916F E2 06         [ 3] 1392 	sbc	6,x
   9171 E6 01         [ 3] 1393 	lda	1,x
   9173 E2 05         [ 3] 1394 	sbc	5,x
   9175 F6            [ 2] 1395 	lda	,x
   9176 E2 04         [ 3] 1396 	sbc	4,x
   9178 24 03         [ 3] 1397 	bcc	00102$
   917A CC 92 12      [ 3] 1398 	jmp	00103$
   917D                    1399 00102$:
                           1400 ;decoders.c:170: triggerState.hasSync = true;
   917D A6 01         [ 2] 1401 	lda	#0x01
   917F C7 01 17      [ 4] 1402 	sta	(_triggerState + 0x001b)
                           1403 ;decoders.c:171: triggerState.toothCurrentCount = 1;
   9182 C7 01 0C      [ 4] 1404 	sta	(_triggerState + 0x0010)
                           1405 ;decoders.c:172: triggerState.toothOneTime = curTime;
   9185 9E E6 09      [ 4] 1406 	lda	9,s
   9188 C7 01 08      [ 4] 1407 	sta	(_triggerState + 0x000c)
   918B 9E E6 0A      [ 4] 1408 	lda	10,s
   918E C7 01 09      [ 4] 1409 	sta	((_triggerState + 0x000c) + 1)
   9191 9E E6 0B      [ 4] 1410 	lda	11,s
   9194 C7 01 0A      [ 4] 1411 	sta	((_triggerState + 0x000c) + 2)
   9197 9E E6 0C      [ 4] 1412 	lda	12,s
   919A C7 01 0B      [ 4] 1413 	sta	((_triggerState + 0x000c) + 3)
                           1414 ;decoders.c:173: triggerState.revolutionTime = triggerState.curGap;
   919D C6 01 0F      [ 4] 1415 	lda	(_triggerState + 0x0013)
   91A0 9E E7 05      [ 4] 1416 	sta	5,s
   91A3 C6 01 10      [ 4] 1417 	lda	((_triggerState + 0x0013) + 1)
   91A6 9E E7 06      [ 4] 1418 	sta	6,s
   91A9 C6 01 11      [ 4] 1419 	lda	((_triggerState + 0x0013) + 2)
   91AC 9E E7 07      [ 4] 1420 	sta	7,s
   91AF C6 01 12      [ 4] 1421 	lda	((_triggerState + 0x0013) + 3)
   91B2 9E E7 08      [ 4] 1422 	sta	8,s
   91B5 9E E6 05      [ 4] 1423 	lda	5,s
   91B8 C7 01 04      [ 4] 1424 	sta	(_triggerState + 0x0008)
   91BB 9E E6 06      [ 4] 1425 	lda	6,s
   91BE C7 01 05      [ 4] 1426 	sta	((_triggerState + 0x0008) + 1)
   91C1 9E E6 07      [ 4] 1427 	lda	7,s
   91C4 C7 01 06      [ 4] 1428 	sta	((_triggerState + 0x0008) + 2)
   91C7 9E E6 08      [ 4] 1429 	lda	8,s
   91CA C7 01 07      [ 4] 1430 	sta	((_triggerState + 0x0008) + 3)
                           1431 ;decoders.c:174: triggerState.toothLastToothTime = curTime;
   91CD 9E E6 09      [ 4] 1432 	lda	9,s
   91D0 C7 00 FC      [ 4] 1433 	sta	_triggerState
   91D3 9E E6 0A      [ 4] 1434 	lda	10,s
   91D6 C7 00 FD      [ 4] 1435 	sta	(_triggerState + 1)
   91D9 9E E6 0B      [ 4] 1436 	lda	11,s
   91DC C7 00 FE      [ 4] 1437 	sta	(_triggerState + 2)
   91DF 9E E6 0C      [ 4] 1438 	lda	12,s
   91E2 C7 00 FF      [ 4] 1439 	sta	(_triggerState + 3)
                           1440 ;decoders.c:175: triggerState.toothLastMinusOneTime = curTime;
   91E5 9E E6 09      [ 4] 1441 	lda	9,s
   91E8 C7 01 00      [ 4] 1442 	sta	(_triggerState + 0x0004)
   91EB 9E E6 0A      [ 4] 1443 	lda	10,s
   91EE C7 01 01      [ 4] 1444 	sta	((_triggerState + 0x0004) + 1)
   91F1 9E E6 0B      [ 4] 1445 	lda	11,s
   91F4 C7 01 02      [ 4] 1446 	sta	((_triggerState + 0x0004) + 2)
   91F7 9E E6 0C      [ 4] 1447 	lda	12,s
   91FA C7 01 03      [ 4] 1448 	sta	((_triggerState + 0x0004) + 3)
                           1449 ;decoders.c:176: revolutionCounter = (revolutionCounter == 0) ? 1 : 0;
   91FD C6 01 D3      [ 4] 1450 	lda	_revolutionCounter
   9200 26 05         [ 3] 1451 	bne	00105$
   9202 5F            [ 1] 1452 	clrx
   9203 A6 01         [ 2] 1453 	lda	#0x01
   9205 20 02         [ 3] 1454 	bra	00106$
   9207                    1455 00105$:
   9207 5F            [ 1] 1456 	clrx
   9208 9F            [ 1] 1457 	txa
   9209                    1458 00106$:
   9209 C7 01 D3      [ 4] 1459 	sta	_revolutionCounter
                           1460 ;decoders.c:178: scheduleInjectionISR();
   920C CD 88 7B      [ 5] 1461 	jsr	_scheduleInjectionISR
                           1462 ;decoders.c:179: scheduleIgnitionISR();
   920F CD 89 9D      [ 5] 1463 	jsr	_scheduleIgnitionISR
   9212                    1464 00103$:
                           1465 ;decoders.c:180: }
   9212 A7 0C         [ 2] 1466 	ais	#12
   9214 81            [ 4] 1467 	rts
                           1468 ;------------------------------------------------------------
                           1469 ;Allocation info for local variables in function 'triggerSetup_MissingTooth'
                           1470 ;------------------------------------------------------------
                           1471 ;decoders.c:185: void triggerSetup_MissingTooth(void) {
                           1472 ;	-----------------------------------------
                           1473 ;	 function triggerSetup_MissingTooth
                           1474 ;	-----------------------------------------
                           1475 ;	Register assignment is optimal.
                           1476 ;	Stack space usage: 0 bytes.
   9215                    1477 _triggerSetup_MissingTooth:
                           1478 ;decoders.c:186: triggerState.triggerTeeth = configPage2.triggerTeeth;
   9215 C6 00 BB      [ 4] 1479 	lda	(_configPage2 + 0x0001)
   9218 C7 01 1F      [ 4] 1480 	sta	(_triggerState + 0x0023)
                           1481 ;decoders.c:187: triggerState.triggerMissing = configPage2.triggerMissing;
   921B C6 00 BC      [ 4] 1482 	lda	(_configPage2 + 0x0002)
   921E C7 01 20      [ 4] 1483 	sta	(_triggerState + 0x0024)
                           1484 ;decoders.c:194: if (triggerState.triggerTeeth == 0) {
   9221 C6 01 1F      [ 4] 1485 	lda	(_triggerState + 0x0023)
   9224 26 0A         [ 3] 1486 	bne	00102$
                           1487 ;decoders.c:195: triggerState.triggerTeeth = 36;
   9226 A6 24         [ 2] 1488 	lda	#0x24
   9228 C7 01 1F      [ 4] 1489 	sta	(_triggerState + 0x0023)
                           1490 ;decoders.c:196: triggerState.triggerMissing = 1;
   922B A6 01         [ 2] 1491 	lda	#0x01
   922D C7 01 20      [ 4] 1492 	sta	(_triggerState + 0x0024)
   9230                    1493 00102$:
                           1494 ;decoders.c:198: triggerState.triggerActualTeeth = triggerState.triggerTeeth - triggerState.triggerMissing;
   9230 C6 01 1F      [ 4] 1495 	lda	(_triggerState + 0x0023)
   9233 CE 01 20      [ 4] 1496 	ldx	(_triggerState + 0x0024)
   9236 89            [ 2] 1497 	pshx
   9237 9E E0 01      [ 4] 1498 	sub	1,s
   923A A7 01         [ 2] 1499 	ais	#1
   923C C7 01 0E      [ 4] 1500 	sta	(_triggerState + 0x0012)
                           1501 ;decoders.c:199: triggerState.toothAngle = (uint16_t)(3600 / triggerState.triggerTeeth);
   923F C6 01 1F      [ 4] 1502 	lda	(_triggerState + 0x0023)
   9242 5F            [ 1] 1503 	clrx
   9243 87            [ 2] 1504 	psha
   9244 89            [ 2] 1505 	pshx
   9245 A6 10         [ 2] 1506 	lda	#0x10
   9247 AE 0E         [ 2] 1507 	ldx	#0x0e
   9249 CD D1 D3      [ 5] 1508 	jsr	__divsint
   924C A7 02         [ 2] 1509 	ais	#2
   924E CF 01 23      [ 4] 1510 	stx	(_triggerState + 0x0027)
   9251 C7 01 24      [ 4] 1511 	sta	((_triggerState + 0x0027) + 1)
                           1512 ;decoders.c:200: triggerState.triggerFilterTime = 50;
   9254 4F            [ 1] 1513 	clra
   9255 C7 01 21      [ 4] 1514 	sta	(_triggerState + 0x0025)
   9258 A6 32         [ 2] 1515 	lda	#0x32
   925A C7 01 22      [ 4] 1516 	sta	((_triggerState + 0x0025) + 1)
                           1517 ;decoders.c:201: triggerState.toothTotalCount = triggerState.triggerTeeth;
   925D C6 01 1F      [ 4] 1518 	lda	(_triggerState + 0x0023)
   9260 C7 01 0D      [ 4] 1519 	sta	(_triggerState + 0x0011)
                           1520 ;decoders.c:203: currentTriggerISR = triggerPri_MissingTooth;
   9263 A6 8C         [ 2] 1521 	lda	#>_triggerPri_MissingTooth
   9265 C7 01 25      [ 4] 1522 	sta	_currentTriggerISR
   9268 A6 B8         [ 2] 1523 	lda	#_triggerPri_MissingTooth
   926A C7 01 26      [ 4] 1524 	sta	(_currentTriggerISR + 1)
                           1525 ;decoders.c:204: }
   926D 81            [ 4] 1526 	rts
                           1527 ;------------------------------------------------------------
                           1528 ;Allocation info for local variables in function 'triggerSetup_BasicDistributor'
                           1529 ;------------------------------------------------------------
                           1530 ;decoders.c:206: void triggerSetup_BasicDistributor(void) {
                           1531 ;	-----------------------------------------
                           1532 ;	 function triggerSetup_BasicDistributor
                           1533 ;	-----------------------------------------
                           1534 ;	Register assignment is optimal.
                           1535 ;	Stack space usage: 0 bytes.
   926E                    1536 _triggerSetup_BasicDistributor:
                           1537 ;decoders.c:207: triggerState.triggerTeeth = 1;
   926E A6 01         [ 2] 1538 	lda	#0x01
   9270 C7 01 1F      [ 4] 1539 	sta	(_triggerState + 0x0023)
                           1540 ;decoders.c:208: triggerState.triggerMissing = 0;
   9273 4A            [ 1] 1541 	deca
   9274 C7 01 20      [ 4] 1542 	sta	(_triggerState + 0x0024)
                           1543 ;decoders.c:209: triggerState.triggerActualTeeth = 1;
   9277 4C            [ 1] 1544 	inca
   9278 C7 01 0E      [ 4] 1545 	sta	(_triggerState + 0x0012)
                           1546 ;decoders.c:210: triggerState.toothAngle = 3600;
   927B A6 0E         [ 2] 1547 	lda	#0x0e
   927D C7 01 23      [ 4] 1548 	sta	(_triggerState + 0x0027)
   9280 A6 10         [ 2] 1549 	lda	#0x10
   9282 C7 01 24      [ 4] 1550 	sta	((_triggerState + 0x0027) + 1)
                           1551 ;decoders.c:211: triggerState.triggerFilterTime = 500;
   9285 A6 01         [ 2] 1552 	lda	#0x01
   9287 C7 01 21      [ 4] 1553 	sta	(_triggerState + 0x0025)
   928A A6 F4         [ 2] 1554 	lda	#0xf4
   928C C7 01 22      [ 4] 1555 	sta	((_triggerState + 0x0025) + 1)
                           1556 ;decoders.c:212: triggerState.toothTotalCount = 1;
   928F A6 01         [ 2] 1557 	lda	#0x01
   9291 C7 01 0D      [ 4] 1558 	sta	(_triggerState + 0x0011)
                           1559 ;decoders.c:214: currentTriggerISR = triggerPri_BasicDistributor;
   9294 A6 90         [ 2] 1560 	lda	#>_triggerPri_BasicDistributor
   9296 C7 01 25      [ 4] 1561 	sta	_currentTriggerISR
   9299 A6 E7         [ 2] 1562 	lda	#_triggerPri_BasicDistributor
   929B C7 01 26      [ 4] 1563 	sta	(_currentTriggerISR + 1)
                           1564 ;decoders.c:215: }
   929E 81            [ 4] 1565 	rts
                           1566 ;------------------------------------------------------------
                           1567 ;Allocation info for local variables in function 'triggerInit'
                           1568 ;------------------------------------------------------------
                           1569 ;decoders.c:217: void triggerInit(void) {
                           1570 ;	-----------------------------------------
                           1571 ;	 function triggerInit
                           1572 ;	-----------------------------------------
                           1573 ;	Register assignment is optimal.
                           1574 ;	Stack space usage: 0 bytes.
   929F                    1575 _triggerInit:
                           1576 ;decoders.c:218: resetTriggerState();
   929F CD 96 D6      [ 5] 1577 	jsr	_resetTriggerState
                           1578 ;decoders.c:220: if (configPage2.triggerPattern == TRIGGER_BASIC_DIST) {
   92A2 C6 00 BA      [ 4] 1579 	lda	_configPage2
   92A5 A1 01         [ 2] 1580 	cmp	#0x01
   92A7 26 05         [ 3] 1581 	bne	00102$
                           1582 ;decoders.c:221: triggerSetup_BasicDistributor();
   92A9 CD 92 6E      [ 5] 1583 	jsr	_triggerSetup_BasicDistributor
   92AC 20 03         [ 3] 1584 	bra	00103$
   92AE                    1585 00102$:
                           1586 ;decoders.c:223: triggerSetup_MissingTooth();
   92AE CD 92 15      [ 5] 1587 	jsr	_triggerSetup_MissingTooth
   92B1                    1588 00103$:
                           1589 ;decoders.c:226: attachTriggerInterrupt();
                           1590 ;decoders.c:227: }
   92B1 CC 96 C9      [ 3] 1591 	jmp	_attachTriggerInterrupt
                           1592 ;------------------------------------------------------------
                           1593 ;Allocation info for local variables in function 'calculateRPM'
                           1594 ;------------------------------------------------------------
                           1595 ;rpm                       Allocated to stack - sp +1
                           1596 ;sloc0                     Allocated to stack - sp +5
                           1597 ;------------------------------------------------------------
                           1598 ;decoders.c:229: void calculateRPM(void) {
                           1599 ;	-----------------------------------------
                           1600 ;	 function calculateRPM
                           1601 ;	-----------------------------------------
                           1602 ;	Register assignment is optimal.
                           1603 ;	Stack space usage: 8 bytes.
   92B4                    1604 _calculateRPM:
   92B4 A7 F8         [ 2] 1605 	ais	#-8
                           1606 ;decoders.c:230: if (!triggerState.hasSync) {
   92B6 C6 01 17      [ 4] 1607 	lda	(_triggerState + 0x001b)
   92B9 26 13         [ 3] 1608 	bne	00102$
                           1609 ;decoders.c:231: triggerState.RPM = 0;
   92BB 4F            [ 1] 1610 	clra
   92BC C7 01 19      [ 4] 1611 	sta	(_triggerState + 0x001d)
   92BF C7 01 1A      [ 4] 1612 	sta	((_triggerState + 0x001d) + 1)
                           1613 ;decoders.c:232: currentStatus.RPM = 0;
   92C2 C7 00 5F      [ 4] 1614 	sta	_currentStatus
   92C5 C7 00 60      [ 4] 1615 	sta	(_currentStatus + 1)
                           1616 ;decoders.c:233: currentStatus.hasSync = false;
   92C8 C7 00 61      [ 4] 1617 	sta	(_currentStatus + 0x0002)
                           1618 ;decoders.c:234: return;
   92CB CC 93 AB      [ 3] 1619 	jmp	00110$
   92CE                    1620 00102$:
                           1621 ;decoders.c:237: if (triggerState.revolutionTime > 0) {
   92CE C6 01 04      [ 4] 1622 	lda	(_triggerState + 0x0008)
   92D1 9E E7 05      [ 4] 1623 	sta	5,s
   92D4 C6 01 05      [ 4] 1624 	lda	((_triggerState + 0x0008) + 1)
   92D7 9E E7 06      [ 4] 1625 	sta	6,s
   92DA C6 01 06      [ 4] 1626 	lda	((_triggerState + 0x0008) + 2)
   92DD 9E E7 07      [ 4] 1627 	sta	7,s
   92E0 C6 01 07      [ 4] 1628 	lda	((_triggerState + 0x0008) + 3)
   92E3 9E E7 08      [ 4] 1629 	sta	8,s
   92E6 95            [ 2] 1630 	tsx
   92E7 E6 04         [ 3] 1631 	lda	4,x
   92E9 EA 05         [ 3] 1632 	ora	5,x
   92EB EA 06         [ 3] 1633 	ora	6,x
   92ED EA 07         [ 3] 1634 	ora	7,x
   92EF 26 03         [ 3] 1635 	bne	00133$
   92F1 CC 93 9E      [ 3] 1636 	jmp	00108$
   92F4                    1637 00133$:
                           1638 ;decoders.c:238: uint32_t rpm = MICROS_PER_SEC * 60UL / triggerState.revolutionTime;
   92F4 C6 01 04      [ 4] 1639 	lda	(_triggerState + 0x0008)
   92F7 E7 04         [ 3] 1640 	sta	4,x
   92F9 C6 01 05      [ 4] 1641 	lda	((_triggerState + 0x0008) + 1)
   92FC E7 05         [ 3] 1642 	sta	5,x
   92FE C6 01 06      [ 4] 1643 	lda	((_triggerState + 0x0008) + 2)
   9301 E7 06         [ 3] 1644 	sta	6,x
   9303 C6 01 07      [ 4] 1645 	lda	((_triggerState + 0x0008) + 3)
   9306 E7 07         [ 3] 1646 	sta	7,x
   9308 E6 07         [ 3] 1647 	lda	7,x
   930A 87            [ 2] 1648 	psha
   930B E6 06         [ 3] 1649 	lda	6,x
   930D 87            [ 2] 1650 	psha
   930E E6 05         [ 3] 1651 	lda	5,x
   9310 87            [ 2] 1652 	psha
   9311 E6 04         [ 3] 1653 	lda	4,x
   9313 87            [ 2] 1654 	psha
   9314 4F            [ 1] 1655 	clra
   9315 87            [ 2] 1656 	psha
   9316 A6 87         [ 2] 1657 	lda	#0x87
   9318 87            [ 2] 1658 	psha
   9319 A6 93         [ 2] 1659 	lda	#0x93
   931B 87            [ 2] 1660 	psha
   931C A6 03         [ 2] 1661 	lda	#0x03
   931E 87            [ 2] 1662 	psha
   931F CD CF 5C      [ 5] 1663 	jsr	__divulong
   9322 9E E7 10      [ 4] 1664 	sta	16,s
   9325 9E EF 0F      [ 4] 1665 	stx	15,s
   9328 B6 4A         [ 3] 1666 	lda	*___SDCC_hc08_ret2
   932A 9E E7 0E      [ 4] 1667 	sta	14,s
   932D B6 4B         [ 3] 1668 	lda	*___SDCC_hc08_ret3
   932F 9E E7 0D      [ 4] 1669 	sta	13,s
   9332 A7 08         [ 2] 1670 	ais	#8
   9334 95            [ 2] 1671 	tsx
   9335 E6 04         [ 3] 1672 	lda	4,x
   9337 F7            [ 2] 1673 	sta	,x
   9338 E6 05         [ 3] 1674 	lda	5,x
   933A E7 01         [ 3] 1675 	sta	1,x
   933C E6 06         [ 3] 1676 	lda	6,x
   933E E7 02         [ 3] 1677 	sta	2,x
   9340 E6 07         [ 3] 1678 	lda	7,x
   9342 E7 03         [ 3] 1679 	sta	3,x
                           1680 ;decoders.c:239: if (rpm > 15000) rpm = 15000;
   9344 A6 98         [ 2] 1681 	lda	#0x98
   9346 E0 07         [ 3] 1682 	sub	7,x
   9348 A6 3A         [ 2] 1683 	lda	#0x3a
   934A E2 06         [ 3] 1684 	sbc	6,x
   934C 4F            [ 1] 1685 	clra
   934D E2 05         [ 3] 1686 	sbc	5,x
   934F 4F            [ 1] 1687 	clra
   9350 E2 04         [ 3] 1688 	sbc	4,x
   9352 24 0C         [ 3] 1689 	bcc	00104$
   9354 4F            [ 1] 1690 	clra
   9355 F7            [ 2] 1691 	sta	,x
   9356 E7 01         [ 3] 1692 	sta	1,x
   9358 A6 3A         [ 2] 1693 	lda	#0x3a
   935A E7 02         [ 3] 1694 	sta	2,x
   935C A6 98         [ 2] 1695 	lda	#0x98
   935E E7 03         [ 3] 1696 	sta	3,x
   9360                    1697 00104$:
                           1698 ;decoders.c:240: if (rpm < 100) rpm = 0;
   9360 95            [ 2] 1699 	tsx
   9361 E6 03         [ 3] 1700 	lda	3,x
   9363 A0 64         [ 2] 1701 	sub	#0x64
   9365 E6 02         [ 3] 1702 	lda	2,x
   9367 A2 00         [ 2] 1703 	sbc	#0x00
   9369 E6 01         [ 3] 1704 	lda	1,x
   936B A2 00         [ 2] 1705 	sbc	#0x00
   936D F6            [ 2] 1706 	lda	,x
   936E A2 00         [ 2] 1707 	sbc	#0x00
   9370 24 08         [ 3] 1708 	bcc	00106$
   9372 4F            [ 1] 1709 	clra
   9373 F7            [ 2] 1710 	sta	,x
   9374 E7 01         [ 3] 1711 	sta	1,x
   9376 E7 02         [ 3] 1712 	sta	2,x
   9378 E7 03         [ 3] 1713 	sta	3,x
   937A                    1714 00106$:
                           1715 ;decoders.c:242: triggerState.RPM = (uint16_t)rpm;
   937A 9E E6 04      [ 4] 1716 	lda	4,s
   937D 9E EE 03      [ 4] 1717 	ldx	3,s
   9380 CF 01 19      [ 4] 1718 	stx	(_triggerState + 0x001d)
   9383 C7 01 1A      [ 4] 1719 	sta	((_triggerState + 0x001d) + 1)
                           1720 ;decoders.c:247: }
   9386 85            [ 1] 1721 	tpa
   9387 9B            [ 2] 1722 	sei
   9388 87            [ 2] 1723 	psha
                           1724 ;decoders.c:245: currentStatus.RPM = triggerState.RPM;
   9389 CE 01 19      [ 4] 1725 	ldx	(_triggerState + 0x001d)
   938C C6 01 1A      [ 4] 1726 	lda	((_triggerState + 0x001d) + 1)
   938F CF 00 5F      [ 4] 1727 	stx	_currentStatus
   9392 C7 00 60      [ 4] 1728 	sta	(_currentStatus + 1)
                           1729 ;decoders.c:246: currentStatus.hasSync = true;
   9395 A6 01         [ 2] 1730 	lda	#0x01
   9397 C7 00 61      [ 4] 1731 	sta	(_currentStatus + 0x0002)
   939A 86            [ 2] 1732 	pula
   939B 84            [ 2] 1733 	tap
   939C 20 0D         [ 3] 1734 	bra	00110$
   939E                    1735 00108$:
                           1736 ;decoders.c:249: triggerState.RPM = 0;
   939E 4F            [ 1] 1737 	clra
   939F C7 01 19      [ 4] 1738 	sta	(_triggerState + 0x001d)
   93A2 C7 01 1A      [ 4] 1739 	sta	((_triggerState + 0x001d) + 1)
                           1740 ;decoders.c:250: currentStatus.RPM = 0;
   93A5 C7 00 5F      [ 4] 1741 	sta	_currentStatus
   93A8 C7 00 60      [ 4] 1742 	sta	(_currentStatus + 1)
   93AB                    1743 00110$:
                           1744 ;decoders.c:252: }
   93AB A7 08         [ 2] 1745 	ais	#8
   93AD 81            [ 4] 1746 	rts
                           1747 ;------------------------------------------------------------
                           1748 ;Allocation info for local variables in function 'checkSyncLoss'
                           1749 ;------------------------------------------------------------
                           1750 ;timeSinceLastTooth        Allocated to stack - sp +5
                           1751 ;sloc0                     Allocated to stack - sp +5
                           1752 ;sloc1                     Allocated to stack - sp +1
                           1753 ;------------------------------------------------------------
                           1754 ;decoders.c:254: void checkSyncLoss(void) {
                           1755 ;	-----------------------------------------
                           1756 ;	 function checkSyncLoss
                           1757 ;	-----------------------------------------
                           1758 ;	Register assignment is optimal.
                           1759 ;	Stack space usage: 8 bytes.
   93AE                    1760 _checkSyncLoss:
   93AE A7 F8         [ 2] 1761 	ais	#-8
                           1762 ;decoders.c:255: uint32_t timeSinceLastTooth = micros() - triggerState.toothLastToothTime;
   93B0 CD 80 4F      [ 5] 1763 	jsr	_micros
   93B3 9E E7 08      [ 4] 1764 	sta	8,s
   93B6 9E EF 07      [ 4] 1765 	stx	7,s
   93B9 B6 4A         [ 3] 1766 	lda	*___SDCC_hc08_ret2
   93BB 9E E7 06      [ 4] 1767 	sta	6,s
   93BE B6 4B         [ 3] 1768 	lda	*___SDCC_hc08_ret3
   93C0 9E E7 05      [ 4] 1769 	sta	5,s
   93C3 C6 00 FC      [ 4] 1770 	lda	_triggerState
   93C6 9E E7 01      [ 4] 1771 	sta	1,s
   93C9 C6 00 FD      [ 4] 1772 	lda	(_triggerState + 1)
   93CC 9E E7 02      [ 4] 1773 	sta	2,s
   93CF C6 00 FE      [ 4] 1774 	lda	(_triggerState + 2)
   93D2 9E E7 03      [ 4] 1775 	sta	3,s
   93D5 C6 00 FF      [ 4] 1776 	lda	(_triggerState + 3)
   93D8 9E E7 04      [ 4] 1777 	sta	4,s
   93DB 95            [ 2] 1778 	tsx
   93DC E6 07         [ 3] 1779 	lda	7,x
   93DE E0 03         [ 3] 1780 	sub	3,x
   93E0 E7 03         [ 3] 1781 	sta	3,x
   93E2 E6 06         [ 3] 1782 	lda	6,x
   93E4 E2 02         [ 3] 1783 	sbc	2,x
   93E6 E7 02         [ 3] 1784 	sta	2,x
   93E8 E6 05         [ 3] 1785 	lda	5,x
   93EA E2 01         [ 3] 1786 	sbc	1,x
   93EC E7 01         [ 3] 1787 	sta	1,x
   93EE E6 04         [ 3] 1788 	lda	4,x
   93F0 F2            [ 2] 1789 	sbc	,x
   93F1 F7            [ 2] 1790 	sta	,x
                           1791 ;decoders.c:257: if (timeSinceLastTooth > (SYNC_TIMEOUT * 1000UL)) {
   93F2 A6 40         [ 2] 1792 	lda	#0x40
   93F4 E0 03         [ 3] 1793 	sub	3,x
   93F6 A6 42         [ 2] 1794 	lda	#0x42
   93F8 E2 02         [ 3] 1795 	sbc	2,x
   93FA A6 0F         [ 2] 1796 	lda	#0x0f
   93FC E2 01         [ 3] 1797 	sbc	1,x
   93FE 4F            [ 1] 1798 	clra
   93FF F2            [ 2] 1799 	sbc	,x
   9400 24 12         [ 3] 1800 	bcc	00103$
                           1801 ;decoders.c:262: }
   9402 85            [ 1] 1802 	tpa
   9403 9B            [ 2] 1803 	sei
   9404 87            [ 2] 1804 	psha
                           1805 ;decoders.c:259: triggerState.hasSync = false;
   9405 4F            [ 1] 1806 	clra
   9406 C7 01 17      [ 4] 1807 	sta	(_triggerState + 0x001b)
                           1808 ;decoders.c:260: currentStatus.hasSync = false;
   9409 C7 00 61      [ 4] 1809 	sta	(_currentStatus + 0x0002)
                           1810 ;decoders.c:261: currentStatus.RPM = 0;
   940C C7 00 5F      [ 4] 1811 	sta	_currentStatus
   940F C7 00 60      [ 4] 1812 	sta	(_currentStatus + 1)
   9412 86            [ 2] 1813 	pula
   9413 84            [ 2] 1814 	tap
   9414                    1815 00103$:
                           1816 ;decoders.c:264: }
   9414 A7 08         [ 2] 1817 	ais	#8
   9416 81            [ 4] 1818 	rts
                           1819 ;------------------------------------------------------------
                           1820 ;Allocation info for local variables in function 'angleToTime'
                           1821 ;------------------------------------------------------------
                           1822 ;angle                     Allocated to registers x h 
                           1823 ;sloc0                     Allocated to stack - sp +1
                           1824 ;sloc1                     Allocated to stack - sp +5
                           1825 ;------------------------------------------------------------
                           1826 ;decoders.c:266: uint32_t angleToTime(uint16_t angle) {
                           1827 ;	-----------------------------------------
                           1828 ;	 function angleToTime
                           1829 ;	-----------------------------------------
                           1830 ;	Register assignment is optimal.
                           1831 ;	Stack space usage: 8 bytes.
   9417                    1832 _angleToTime:
   9417 A7 F8         [ 2] 1833 	ais	#-8
   9419 89            [ 2] 1834 	pshx
   941A 97            [ 1] 1835 	tax
   941B 8A            [ 2] 1836 	pulh
                           1837 ;decoders.c:267: if (triggerState.revolutionTime == 0) return 0;
   941C C6 01 04      [ 4] 1838 	lda	(_triggerState + 0x0008)
   941F 9E E7 01      [ 4] 1839 	sta	1,s
   9422 C6 01 05      [ 4] 1840 	lda	((_triggerState + 0x0008) + 1)
   9425 9E E7 02      [ 4] 1841 	sta	2,s
   9428 C6 01 06      [ 4] 1842 	lda	((_triggerState + 0x0008) + 2)
   942B 9E E7 03      [ 4] 1843 	sta	3,s
   942E C6 01 07      [ 4] 1844 	lda	((_triggerState + 0x0008) + 3)
   9431 9E E7 04      [ 4] 1845 	sta	4,s
   9434 9E E6 01      [ 4] 1846 	lda	1,s
   9437 9E EA 02      [ 4] 1847 	ora	2,s
   943A 9E EA 03      [ 4] 1848 	ora	3,s
   943D 9E EA 04      [ 4] 1849 	ora	4,s
   9440 26 09         [ 3] 1850 	bne	00102$
   9442 4F            [ 1] 1851 	clra
   9443 97            [ 1] 1852 	tax
   9444 B7 4A         [ 3] 1853 	sta	*___SDCC_hc08_ret2
   9446 B7 4B         [ 3] 1854 	sta	*___SDCC_hc08_ret3
   9448 CC 94 D8      [ 3] 1855 	jmp	00103$
   944B                    1856 00102$:
                           1857 ;decoders.c:268: return ((uint32_t)angle * triggerState.revolutionTime) / 360UL;
   944B 9E EF 04      [ 4] 1858 	stx	4,s
   944E 8B            [ 2] 1859 	pshh
   944F 86            [ 2] 1860 	pula
   9450 9E E7 03      [ 4] 1861 	sta	3,s
   9453 4F            [ 1] 1862 	clra
   9454 9E E7 02      [ 4] 1863 	sta	2,s
   9457 9E E7 01      [ 4] 1864 	sta	1,s
   945A C6 01 04      [ 4] 1865 	lda	(_triggerState + 0x0008)
   945D 9E E7 05      [ 4] 1866 	sta	5,s
   9460 C6 01 05      [ 4] 1867 	lda	((_triggerState + 0x0008) + 1)
   9463 9E E7 06      [ 4] 1868 	sta	6,s
   9466 C6 01 06      [ 4] 1869 	lda	((_triggerState + 0x0008) + 2)
   9469 9E E7 07      [ 4] 1870 	sta	7,s
   946C C6 01 07      [ 4] 1871 	lda	((_triggerState + 0x0008) + 3)
   946F 9E E7 08      [ 4] 1872 	sta	8,s
   9472 95            [ 2] 1873 	tsx
   9473 E6 07         [ 3] 1874 	lda	7,x
   9475 87            [ 2] 1875 	psha
   9476 E6 06         [ 3] 1876 	lda	6,x
   9478 87            [ 2] 1877 	psha
   9479 E6 05         [ 3] 1878 	lda	5,x
   947B 87            [ 2] 1879 	psha
   947C E6 04         [ 3] 1880 	lda	4,x
   947E 87            [ 2] 1881 	psha
   947F E6 03         [ 3] 1882 	lda	3,x
   9481 87            [ 2] 1883 	psha
   9482 E6 02         [ 3] 1884 	lda	2,x
   9484 87            [ 2] 1885 	psha
   9485 E6 01         [ 3] 1886 	lda	1,x
   9487 87            [ 2] 1887 	psha
   9488 F6            [ 2] 1888 	lda	,x
   9489 87            [ 2] 1889 	psha
   948A CD D0 87      [ 5] 1890 	jsr	__mullong
   948D 9E E7 10      [ 4] 1891 	sta	16,s
   9490 9E EF 0F      [ 4] 1892 	stx	15,s
   9493 B6 4A         [ 3] 1893 	lda	*___SDCC_hc08_ret2
   9495 9E E7 0E      [ 4] 1894 	sta	14,s
   9498 B6 4B         [ 3] 1895 	lda	*___SDCC_hc08_ret3
   949A 9E E7 0D      [ 4] 1896 	sta	13,s
   949D A7 08         [ 2] 1897 	ais	#8
   949F A6 68         [ 2] 1898 	lda	#0x68
   94A1 87            [ 2] 1899 	psha
   94A2 A6 01         [ 2] 1900 	lda	#0x01
   94A4 87            [ 2] 1901 	psha
   94A5 4A            [ 1] 1902 	deca
   94A6 87            [ 2] 1903 	psha
   94A7 87            [ 2] 1904 	psha
   94A8 95            [ 2] 1905 	tsx
   94A9 E6 0B         [ 3] 1906 	lda	11,x
   94AB 87            [ 2] 1907 	psha
   94AC E6 0A         [ 3] 1908 	lda	10,x
   94AE 87            [ 2] 1909 	psha
   94AF E6 09         [ 3] 1910 	lda	9,x
   94B1 87            [ 2] 1911 	psha
   94B2 E6 08         [ 3] 1912 	lda	8,x
   94B4 87            [ 2] 1913 	psha
   94B5 CD CF 5C      [ 5] 1914 	jsr	__divulong
   94B8 9E E7 10      [ 4] 1915 	sta	16,s
   94BB 9E EF 0F      [ 4] 1916 	stx	15,s
   94BE B6 4A         [ 3] 1917 	lda	*___SDCC_hc08_ret2
   94C0 9E E7 0E      [ 4] 1918 	sta	14,s
   94C3 B6 4B         [ 3] 1919 	lda	*___SDCC_hc08_ret3
   94C5 9E E7 0D      [ 4] 1920 	sta	13,s
   94C8 A7 08         [ 2] 1921 	ais	#8
   94CA 95            [ 2] 1922 	tsx
   94CB E6 04         [ 3] 1923 	lda	4,x
   94CD B7 4B         [ 3] 1924 	sta	*___SDCC_hc08_ret3
   94CF E6 05         [ 3] 1925 	lda	5,x
   94D1 B7 4A         [ 3] 1926 	sta	*___SDCC_hc08_ret2
   94D3 EE 06         [ 3] 1927 	ldx	6,x
   94D5 9E E6 08      [ 4] 1928 	lda	8,s
   94D8                    1929 00103$:
                           1930 ;decoders.c:269: }
   94D8 A7 08         [ 2] 1931 	ais	#8
   94DA 81            [ 4] 1932 	rts
                           1933 ;------------------------------------------------------------
                           1934 ;Allocation info for local variables in function 'timeToAngle'
                           1935 ;------------------------------------------------------------
                           1936 ;time                      Allocated to stack - sp +11
                           1937 ;sloc0                     Allocated to stack - sp +5
                           1938 ;sloc1                     Allocated to stack - sp +1
                           1939 ;------------------------------------------------------------
                           1940 ;decoders.c:271: uint16_t timeToAngle(uint32_t time) {
                           1941 ;	-----------------------------------------
                           1942 ;	 function timeToAngle
                           1943 ;	-----------------------------------------
                           1944 ;	Register assignment is optimal.
                           1945 ;	Stack space usage: 8 bytes.
   94DB                    1946 _timeToAngle:
   94DB A7 F8         [ 2] 1947 	ais	#-8
                           1948 ;decoders.c:272: if (triggerState.revolutionTime == 0) return 0;
   94DD C6 01 04      [ 4] 1949 	lda	(_triggerState + 0x0008)
   94E0 9E E7 05      [ 4] 1950 	sta	5,s
   94E3 C6 01 05      [ 4] 1951 	lda	((_triggerState + 0x0008) + 1)
   94E6 9E E7 06      [ 4] 1952 	sta	6,s
   94E9 C6 01 06      [ 4] 1953 	lda	((_triggerState + 0x0008) + 2)
   94EC 9E E7 07      [ 4] 1954 	sta	7,s
   94EF C6 01 07      [ 4] 1955 	lda	((_triggerState + 0x0008) + 3)
   94F2 9E E7 08      [ 4] 1956 	sta	8,s
   94F5 95            [ 2] 1957 	tsx
   94F6 E6 04         [ 3] 1958 	lda	4,x
   94F8 EA 05         [ 3] 1959 	ora	5,x
   94FA EA 06         [ 3] 1960 	ora	6,x
   94FC EA 07         [ 3] 1961 	ora	7,x
   94FE 26 04         [ 3] 1962 	bne	00102$
   9500 4F            [ 1] 1963 	clra
   9501 97            [ 1] 1964 	tax
   9502 20 76         [ 3] 1965 	bra	00103$
   9504                    1966 00102$:
                           1967 ;decoders.c:273: return (uint16_t)((time * 360UL) / triggerState.revolutionTime);
   9504 95            [ 2] 1968 	tsx
   9505 E6 0D         [ 3] 1969 	lda	13,x
   9507 87            [ 2] 1970 	psha
   9508 E6 0C         [ 3] 1971 	lda	12,x
   950A 87            [ 2] 1972 	psha
   950B E6 0B         [ 3] 1973 	lda	11,x
   950D 87            [ 2] 1974 	psha
   950E E6 0A         [ 3] 1975 	lda	10,x
   9510 87            [ 2] 1976 	psha
   9511 A6 68         [ 2] 1977 	lda	#0x68
   9513 87            [ 2] 1978 	psha
   9514 A6 01         [ 2] 1979 	lda	#0x01
   9516 87            [ 2] 1980 	psha
   9517 4A            [ 1] 1981 	deca
   9518 87            [ 2] 1982 	psha
   9519 87            [ 2] 1983 	psha
   951A CD D0 87      [ 5] 1984 	jsr	__mullong
   951D 9E E7 10      [ 4] 1985 	sta	16,s
   9520 9E EF 0F      [ 4] 1986 	stx	15,s
   9523 B6 4A         [ 3] 1987 	lda	*___SDCC_hc08_ret2
   9525 9E E7 0E      [ 4] 1988 	sta	14,s
   9528 B6 4B         [ 3] 1989 	lda	*___SDCC_hc08_ret3
   952A 9E E7 0D      [ 4] 1990 	sta	13,s
   952D A7 08         [ 2] 1991 	ais	#8
   952F C6 01 04      [ 4] 1992 	lda	(_triggerState + 0x0008)
   9532 9E E7 01      [ 4] 1993 	sta	1,s
   9535 C6 01 05      [ 4] 1994 	lda	((_triggerState + 0x0008) + 1)
   9538 9E E7 02      [ 4] 1995 	sta	2,s
   953B C6 01 06      [ 4] 1996 	lda	((_triggerState + 0x0008) + 2)
   953E 9E E7 03      [ 4] 1997 	sta	3,s
   9541 C6 01 07      [ 4] 1998 	lda	((_triggerState + 0x0008) + 3)
   9544 9E E7 04      [ 4] 1999 	sta	4,s
   9547 95            [ 2] 2000 	tsx
   9548 E6 03         [ 3] 2001 	lda	3,x
   954A 87            [ 2] 2002 	psha
   954B E6 02         [ 3] 2003 	lda	2,x
   954D 87            [ 2] 2004 	psha
   954E E6 01         [ 3] 2005 	lda	1,x
   9550 87            [ 2] 2006 	psha
   9551 F6            [ 2] 2007 	lda	,x
   9552 87            [ 2] 2008 	psha
   9553 E6 07         [ 3] 2009 	lda	7,x
   9555 87            [ 2] 2010 	psha
   9556 E6 06         [ 3] 2011 	lda	6,x
   9558 87            [ 2] 2012 	psha
   9559 E6 05         [ 3] 2013 	lda	5,x
   955B 87            [ 2] 2014 	psha
   955C E6 04         [ 3] 2015 	lda	4,x
   955E 87            [ 2] 2016 	psha
   955F CD CF 5C      [ 5] 2017 	jsr	__divulong
   9562 9E E7 0C      [ 4] 2018 	sta	12,s
   9565 9E EF 0B      [ 4] 2019 	stx	11,s
   9568 B6 4A         [ 3] 2020 	lda	*___SDCC_hc08_ret2
   956A 9E E7 0A      [ 4] 2021 	sta	10,s
   956D B6 4B         [ 3] 2022 	lda	*___SDCC_hc08_ret3
   956F 9E E7 09      [ 4] 2023 	sta	9,s
   9572 A7 08         [ 2] 2024 	ais	#8
   9574 9E E6 04      [ 4] 2025 	lda	4,s
   9577 9E EE 03      [ 4] 2026 	ldx	3,s
   957A                    2027 00103$:
                           2028 ;decoders.c:274: }
   957A A7 08         [ 2] 2029 	ais	#8
   957C 81            [ 4] 2030 	rts
                           2031 ;------------------------------------------------------------
                           2032 ;Allocation info for local variables in function 'getCrankAngle'
                           2033 ;------------------------------------------------------------
                           2034 ;timeSinceToothOne         Allocated to stack - sp +1
                           2035 ;angle                     Allocated to registers a x 
                           2036 ;sloc0                     Allocated to stack - sp +5
                           2037 ;sloc1                     Allocated to stack - sp +9
                           2038 ;------------------------------------------------------------
                           2039 ;decoders.c:276: uint16_t getCrankAngle(void) {
                           2040 ;	-----------------------------------------
                           2041 ;	 function getCrankAngle
                           2042 ;	-----------------------------------------
                           2043 ;	Register assignment is optimal.
                           2044 ;	Stack space usage: 12 bytes.
   957D                    2045 _getCrankAngle:
   957D A7 F4         [ 2] 2046 	ais	#-12
                           2047 ;decoders.c:280: if (!triggerState.hasSync || triggerState.revolutionTime == 0) return 0;
   957F C6 01 17      [ 4] 2048 	lda	(_triggerState + 0x001b)
   9582 27 23         [ 3] 2049 	beq	00101$
   9584 C6 01 04      [ 4] 2050 	lda	(_triggerState + 0x0008)
   9587 9E E7 05      [ 4] 2051 	sta	5,s
   958A C6 01 05      [ 4] 2052 	lda	((_triggerState + 0x0008) + 1)
   958D 9E E7 06      [ 4] 2053 	sta	6,s
   9590 C6 01 06      [ 4] 2054 	lda	((_triggerState + 0x0008) + 2)
   9593 9E E7 07      [ 4] 2055 	sta	7,s
   9596 C6 01 07      [ 4] 2056 	lda	((_triggerState + 0x0008) + 3)
   9599 9E E7 08      [ 4] 2057 	sta	8,s
   959C 95            [ 2] 2058 	tsx
   959D E6 04         [ 3] 2059 	lda	4,x
   959F EA 05         [ 3] 2060 	ora	5,x
   95A1 EA 06         [ 3] 2061 	ora	6,x
   95A3 EA 07         [ 3] 2062 	ora	7,x
   95A5 26 05         [ 3] 2063 	bne	00102$
   95A7                    2064 00101$:
   95A7 4F            [ 1] 2065 	clra
   95A8 97            [ 1] 2066 	tax
   95A9 CC 96 C6      [ 3] 2067 	jmp	00106$
   95AC                    2068 00102$:
                           2069 ;decoders.c:282: timeSinceToothOne = micros() - triggerState.toothOneTime;
   95AC CD 80 4F      [ 5] 2070 	jsr	_micros
   95AF 9E E7 08      [ 4] 2071 	sta	8,s
   95B2 9E EF 07      [ 4] 2072 	stx	7,s
   95B5 B6 4A         [ 3] 2073 	lda	*___SDCC_hc08_ret2
   95B7 9E E7 06      [ 4] 2074 	sta	6,s
   95BA B6 4B         [ 3] 2075 	lda	*___SDCC_hc08_ret3
   95BC 9E E7 05      [ 4] 2076 	sta	5,s
   95BF C6 01 08      [ 4] 2077 	lda	(_triggerState + 0x000c)
   95C2 9E E7 09      [ 4] 2078 	sta	9,s
   95C5 C6 01 09      [ 4] 2079 	lda	((_triggerState + 0x000c) + 1)
   95C8 9E E7 0A      [ 4] 2080 	sta	10,s
   95CB C6 01 0A      [ 4] 2081 	lda	((_triggerState + 0x000c) + 2)
   95CE 9E E7 0B      [ 4] 2082 	sta	11,s
   95D1 C6 01 0B      [ 4] 2083 	lda	((_triggerState + 0x000c) + 3)
   95D4 9E E7 0C      [ 4] 2084 	sta	12,s
   95D7 95            [ 2] 2085 	tsx
   95D8 E6 07         [ 3] 2086 	lda	7,x
   95DA E0 0B         [ 3] 2087 	sub	11,x
   95DC E7 0B         [ 3] 2088 	sta	11,x
   95DE E6 06         [ 3] 2089 	lda	6,x
   95E0 E2 0A         [ 3] 2090 	sbc	10,x
   95E2 E7 0A         [ 3] 2091 	sta	10,x
   95E4 E6 05         [ 3] 2092 	lda	5,x
   95E6 E2 09         [ 3] 2093 	sbc	9,x
   95E8 E7 09         [ 3] 2094 	sta	9,x
   95EA E6 04         [ 3] 2095 	lda	4,x
   95EC E2 08         [ 3] 2096 	sbc	8,x
   95EE E7 08         [ 3] 2097 	sta	8,x
   95F0 E6 08         [ 3] 2098 	lda	8,x
   95F2 F7            [ 2] 2099 	sta	,x
   95F3 E6 09         [ 3] 2100 	lda	9,x
   95F5 E7 01         [ 3] 2101 	sta	1,x
   95F7 E6 0A         [ 3] 2102 	lda	10,x
   95F9 E7 02         [ 3] 2103 	sta	2,x
   95FB E6 0B         [ 3] 2104 	lda	11,x
   95FD E7 03         [ 3] 2105 	sta	3,x
                           2106 ;decoders.c:283: if (timeSinceToothOne >= triggerState.revolutionTime) {
   95FF C6 01 04      [ 4] 2107 	lda	(_triggerState + 0x0008)
   9602 E7 04         [ 3] 2108 	sta	4,x
   9604 C6 01 05      [ 4] 2109 	lda	((_triggerState + 0x0008) + 1)
   9607 E7 05         [ 3] 2110 	sta	5,x
   9609 C6 01 06      [ 4] 2111 	lda	((_triggerState + 0x0008) + 2)
   960C E7 06         [ 3] 2112 	sta	6,x
   960E C6 01 07      [ 4] 2113 	lda	((_triggerState + 0x0008) + 3)
   9611 E7 07         [ 3] 2114 	sta	7,x
   9613 E6 0B         [ 3] 2115 	lda	11,x
   9615 E0 07         [ 3] 2116 	sub	7,x
   9617 E6 0A         [ 3] 2117 	lda	10,x
   9619 E2 06         [ 3] 2118 	sbc	6,x
   961B E6 09         [ 3] 2119 	lda	9,x
   961D E2 05         [ 3] 2120 	sbc	5,x
   961F E6 08         [ 3] 2121 	lda	8,x
   9621 E2 04         [ 3] 2122 	sbc	4,x
   9623 25 2B         [ 3] 2123 	bcs	00105$
                           2124 ;decoders.c:284: timeSinceToothOne = triggerState.revolutionTime - 1;
   9625 C6 01 04      [ 4] 2125 	lda	(_triggerState + 0x0008)
   9628 E7 08         [ 3] 2126 	sta	8,x
   962A C6 01 05      [ 4] 2127 	lda	((_triggerState + 0x0008) + 1)
   962D E7 09         [ 3] 2128 	sta	9,x
   962F C6 01 06      [ 4] 2129 	lda	((_triggerState + 0x0008) + 2)
   9632 E7 0A         [ 3] 2130 	sta	10,x
   9634 C6 01 07      [ 4] 2131 	lda	((_triggerState + 0x0008) + 3)
   9637 E7 0B         [ 3] 2132 	sta	11,x
   9639 E6 0B         [ 3] 2133 	lda	11,x
   963B A0 01         [ 2] 2134 	sub	#0x01
   963D E7 03         [ 3] 2135 	sta	3,x
   963F E6 0A         [ 3] 2136 	lda	10,x
   9641 A2 00         [ 2] 2137 	sbc	#0x00
   9643 E7 02         [ 3] 2138 	sta	2,x
   9645 E6 09         [ 3] 2139 	lda	9,x
   9647 A2 00         [ 2] 2140 	sbc	#0x00
   9649 E7 01         [ 3] 2141 	sta	1,x
   964B E6 08         [ 3] 2142 	lda	8,x
   964D A2 00         [ 2] 2143 	sbc	#0x00
   964F F7            [ 2] 2144 	sta	,x
   9650                    2145 00105$:
                           2146 ;decoders.c:287: angle = (uint16_t)((timeSinceToothOne * 360UL) / triggerState.revolutionTime);
   9650 95            [ 2] 2147 	tsx
   9651 E6 03         [ 3] 2148 	lda	3,x
   9653 87            [ 2] 2149 	psha
   9654 E6 02         [ 3] 2150 	lda	2,x
   9656 87            [ 2] 2151 	psha
   9657 E6 01         [ 3] 2152 	lda	1,x
   9659 87            [ 2] 2153 	psha
   965A F6            [ 2] 2154 	lda	,x
   965B 87            [ 2] 2155 	psha
   965C A6 68         [ 2] 2156 	lda	#0x68
   965E 87            [ 2] 2157 	psha
   965F A6 01         [ 2] 2158 	lda	#0x01
   9661 87            [ 2] 2159 	psha
   9662 4A            [ 1] 2160 	deca
   9663 87            [ 2] 2161 	psha
   9664 87            [ 2] 2162 	psha
   9665 CD D0 87      [ 5] 2163 	jsr	__mullong
   9668 9E E7 14      [ 4] 2164 	sta	20,s
   966B 9E EF 13      [ 4] 2165 	stx	19,s
   966E B6 4A         [ 3] 2166 	lda	*___SDCC_hc08_ret2
   9670 9E E7 12      [ 4] 2167 	sta	18,s
   9673 B6 4B         [ 3] 2168 	lda	*___SDCC_hc08_ret3
   9675 9E E7 11      [ 4] 2169 	sta	17,s
   9678 A7 08         [ 2] 2170 	ais	#8
   967A C6 01 04      [ 4] 2171 	lda	(_triggerState + 0x0008)
   967D 9E E7 05      [ 4] 2172 	sta	5,s
   9680 C6 01 05      [ 4] 2173 	lda	((_triggerState + 0x0008) + 1)
   9683 9E E7 06      [ 4] 2174 	sta	6,s
   9686 C6 01 06      [ 4] 2175 	lda	((_triggerState + 0x0008) + 2)
   9689 9E E7 07      [ 4] 2176 	sta	7,s
   968C C6 01 07      [ 4] 2177 	lda	((_triggerState + 0x0008) + 3)
   968F 9E E7 08      [ 4] 2178 	sta	8,s
   9692 95            [ 2] 2179 	tsx
   9693 E6 07         [ 3] 2180 	lda	7,x
   9695 87            [ 2] 2181 	psha
   9696 E6 06         [ 3] 2182 	lda	6,x
   9698 87            [ 2] 2183 	psha
   9699 E6 05         [ 3] 2184 	lda	5,x
   969B 87            [ 2] 2185 	psha
   969C E6 04         [ 3] 2186 	lda	4,x
   969E 87            [ 2] 2187 	psha
   969F E6 0B         [ 3] 2188 	lda	11,x
   96A1 87            [ 2] 2189 	psha
   96A2 E6 0A         [ 3] 2190 	lda	10,x
   96A4 87            [ 2] 2191 	psha
   96A5 E6 09         [ 3] 2192 	lda	9,x
   96A7 87            [ 2] 2193 	psha
   96A8 E6 08         [ 3] 2194 	lda	8,x
   96AA 87            [ 2] 2195 	psha
   96AB CD CF 5C      [ 5] 2196 	jsr	__divulong
   96AE 9E E7 14      [ 4] 2197 	sta	20,s
   96B1 9E EF 13      [ 4] 2198 	stx	19,s
   96B4 B6 4A         [ 3] 2199 	lda	*___SDCC_hc08_ret2
   96B6 9E E7 12      [ 4] 2200 	sta	18,s
   96B9 B6 4B         [ 3] 2201 	lda	*___SDCC_hc08_ret3
   96BB 9E E7 11      [ 4] 2202 	sta	17,s
   96BE A7 08         [ 2] 2203 	ais	#8
   96C0 9E E6 0C      [ 4] 2204 	lda	12,s
   96C3 9E EE 0B      [ 4] 2205 	ldx	11,s
                           2206 ;decoders.c:288: return angle;
   96C6                    2207 00106$:
                           2208 ;decoders.c:289: }
   96C6 A7 0C         [ 2] 2209 	ais	#12
   96C8 81            [ 4] 2210 	rts
                           2211 ;------------------------------------------------------------
                           2212 ;Allocation info for local variables in function 'attachTriggerInterrupt'
                           2213 ;------------------------------------------------------------
                           2214 ;decoders.c:294: void attachTriggerInterrupt(void) {
                           2215 ;	-----------------------------------------
                           2216 ;	 function attachTriggerInterrupt
                           2217 ;	-----------------------------------------
                           2218 ;	Register assignment is optimal.
                           2219 ;	Stack space usage: 0 bytes.
   96C9                    2220 _attachTriggerInterrupt:
                           2221 ;decoders.c:298: INTSCR &= (uint8_t)~(1 << INTSCR_MODE);
   96C9 B6 1D         [ 3] 2222 	lda	*0x1d
   96CB A4 FE         [ 2] 2223 	and	#0xfe
   96CD B7 1D         [ 3] 2224 	sta	*0x1d
                           2225 ;decoders.c:301: INTSCR &= (uint8_t)~(1 << INTSCR_IMASK);
   96CF B6 1D         [ 3] 2226 	lda	*0x1d
   96D1 A4 FD         [ 2] 2227 	and	#0xfd
   96D3 B7 1D         [ 3] 2228 	sta	*0x1d
                           2229 ;decoders.c:302: }
   96D5 81            [ 4] 2230 	rts
                           2231 ;------------------------------------------------------------
                           2232 ;Allocation info for local variables in function 'resetTriggerState'
                           2233 ;------------------------------------------------------------
                           2234 ;decoders.c:304: void resetTriggerState(void) {
                           2235 ;	-----------------------------------------
                           2236 ;	 function resetTriggerState
                           2237 ;	-----------------------------------------
                           2238 ;	Register assignment is optimal.
                           2239 ;	Stack space usage: 0 bytes.
   96D6                    2240 _resetTriggerState:
                           2241 ;decoders.c:327: }
   96D6 85            [ 1] 2242 	tpa
   96D7 9B            [ 2] 2243 	sei
   96D8 87            [ 2] 2244 	psha
                           2245 ;decoders.c:306: triggerState.toothLastToothTime = 0;
   96D9 4F            [ 1] 2246 	clra
   96DA C7 00 FC      [ 4] 2247 	sta	_triggerState
   96DD C7 00 FD      [ 4] 2248 	sta	(_triggerState + 1)
   96E0 C7 00 FE      [ 4] 2249 	sta	(_triggerState + 2)
   96E3 C7 00 FF      [ 4] 2250 	sta	(_triggerState + 3)
                           2251 ;decoders.c:307: triggerState.toothLastMinusOneTime = 0;
   96E6 C7 01 00      [ 4] 2252 	sta	(_triggerState + 0x0004)
   96E9 C7 01 01      [ 4] 2253 	sta	((_triggerState + 0x0004) + 1)
   96EC C7 01 02      [ 4] 2254 	sta	((_triggerState + 0x0004) + 2)
   96EF C7 01 03      [ 4] 2255 	sta	((_triggerState + 0x0004) + 3)
                           2256 ;decoders.c:308: triggerState.revolutionTime = 0;
   96F2 C7 01 04      [ 4] 2257 	sta	(_triggerState + 0x0008)
   96F5 C7 01 05      [ 4] 2258 	sta	((_triggerState + 0x0008) + 1)
   96F8 C7 01 06      [ 4] 2259 	sta	((_triggerState + 0x0008) + 2)
   96FB C7 01 07      [ 4] 2260 	sta	((_triggerState + 0x0008) + 3)
                           2261 ;decoders.c:309: triggerState.toothOneTime = 0;
   96FE C7 01 08      [ 4] 2262 	sta	(_triggerState + 0x000c)
   9701 C7 01 09      [ 4] 2263 	sta	((_triggerState + 0x000c) + 1)
   9704 C7 01 0A      [ 4] 2264 	sta	((_triggerState + 0x000c) + 2)
   9707 C7 01 0B      [ 4] 2265 	sta	((_triggerState + 0x000c) + 3)
                           2266 ;decoders.c:311: triggerState.toothCurrentCount = 0;
   970A C7 01 0C      [ 4] 2267 	sta	(_triggerState + 0x0010)
                           2268 ;decoders.c:312: triggerState.toothTotalCount = 0;
   970D C7 01 0D      [ 4] 2269 	sta	(_triggerState + 0x0011)
                           2270 ;decoders.c:313: triggerState.triggerActualTeeth = 0;
   9710 C7 01 0E      [ 4] 2271 	sta	(_triggerState + 0x0012)
                           2272 ;decoders.c:315: triggerState.curGap = 0;
   9713 C7 01 0F      [ 4] 2273 	sta	(_triggerState + 0x0013)
   9716 C7 01 10      [ 4] 2274 	sta	((_triggerState + 0x0013) + 1)
   9719 C7 01 11      [ 4] 2275 	sta	((_triggerState + 0x0013) + 2)
   971C C7 01 12      [ 4] 2276 	sta	((_triggerState + 0x0013) + 3)
                           2277 ;decoders.c:316: triggerState.lastGap = 0;
   971F C7 01 13      [ 4] 2278 	sta	(_triggerState + 0x0017)
   9722 C7 01 14      [ 4] 2279 	sta	((_triggerState + 0x0017) + 1)
   9725 C7 01 15      [ 4] 2280 	sta	((_triggerState + 0x0017) + 2)
   9728 C7 01 16      [ 4] 2281 	sta	((_triggerState + 0x0017) + 3)
                           2282 ;decoders.c:317: triggerState.hasSync = false;
   972B C7 01 17      [ 4] 2283 	sta	(_triggerState + 0x001b)
                           2284 ;decoders.c:318: triggerState.syncLossCounter = 0;
   972E C7 01 18      [ 4] 2285 	sta	(_triggerState + 0x001c)
                           2286 ;decoders.c:320: triggerState.RPM = 0;
   9731 C7 01 19      [ 4] 2287 	sta	(_triggerState + 0x001d)
   9734 C7 01 1A      [ 4] 2288 	sta	((_triggerState + 0x001d) + 1)
                           2289 ;decoders.c:321: triggerState.toothPeriod = 0;
   9737 C7 01 1B      [ 4] 2290 	sta	(_triggerState + 0x001f)
   973A C7 01 1C      [ 4] 2291 	sta	((_triggerState + 0x001f) + 1)
   973D C7 01 1D      [ 4] 2292 	sta	((_triggerState + 0x001f) + 2)
   9740 C7 01 1E      [ 4] 2293 	sta	((_triggerState + 0x001f) + 3)
                           2294 ;decoders.c:323: currentStatus.hasSync = false;
   9743 C7 00 61      [ 4] 2295 	sta	(_currentStatus + 0x0002)
                           2296 ;decoders.c:324: currentStatus.RPM = 0;
   9746 C7 00 5F      [ 4] 2297 	sta	_currentStatus
   9749 C7 00 60      [ 4] 2298 	sta	(_currentStatus + 1)
                           2299 ;decoders.c:326: revolutionCounter = 0;
   974C C7 01 D3      [ 4] 2300 	sta	_revolutionCounter
   974F 86            [ 2] 2301 	pula
   9750 84            [ 2] 2302 	tap
                           2303 ;decoders.c:328: }
   9751 81            [ 4] 2304 	rts
                           2305 ;------------------------------------------------------------
                           2306 ;Allocation info for local variables in function 'isr_irq'
                           2307 ;------------------------------------------------------------
                           2308 ;decoders.c:334: void isr_irq(void) __interrupt(2) {
                           2309 ;	-----------------------------------------
                           2310 ;	 function isr_irq
                           2311 ;	-----------------------------------------
                           2312 ;	Register assignment is optimal.
                           2313 ;	Stack space usage: 0 bytes.
   9752                    2314 _isr_irq:
   9752 8B            [ 2] 2315 	pshh
                           2316 ;decoders.c:335: if (currentTriggerISR != 0) {
   9753 C6 01 25      [ 4] 2317 	lda	_currentTriggerISR
   9756 CA 01 26      [ 4] 2318 	ora	(_currentTriggerISR + 1)
   9759 27 0D         [ 3] 2319 	beq	00103$
                           2320 ;decoders.c:336: currentTriggerISR();
   975B AD 02         [ 4] 2321 	bsr	00112$
   975D 20 09         [ 3] 2322 	bra	00111$
   975F                    2323 00112$:
   975F C6 01 26      [ 4] 2324 	lda	(_currentTriggerISR + 1)
   9762 87            [ 2] 2325 	psha
   9763 C6 01 25      [ 4] 2326 	lda	_currentTriggerISR
   9766 87            [ 2] 2327 	psha
   9767 81            [ 4] 2328 	rts
   9768                    2329 00111$:
   9768                    2330 00103$:
                           2331 ;decoders.c:338: }
   9768 8A            [ 2] 2332 	pulh
   9769 80            [ 7] 2333 	rti
                           2334 	.area CSEG    (CODE)
                           2335 	.area CONST   (CODE)
                           2336 	.area XINIT   (CODE)
   D24B                    2337 __xinit__revolutionCounter:
   D24B 00                 2338 	.db #0x00	; 0
   D24C                    2339 __xinit__triggerEdgesPerTooth:
   D24C 01                 2340 	.db #0x01	; 1
                           2341 	.area CABS    (ABS,CODE)
