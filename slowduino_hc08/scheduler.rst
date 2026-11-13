                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 4.2.0 #13081 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module scheduler
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
                             22 	.globl _isr_tim1_ch1
                             23 	.globl _isr_tim1_ch0
                             24 	.globl _micros
                             25 	.globl _ignitionSchedule2
                             26 	.globl _ignitionSchedule1
                             27 	.globl _injector3Polling
                             28 	.globl _injector2Polling
                             29 	.globl _injector1Polling
                             30 	.globl _scheduleInjectorPolling
                             31 	.globl _processInjectorPolling
                             32 	.globl _schedulerInit
                             33 	.globl _setIgnitionSchedule
                             34 	.globl _clearIgnitionSchedule
                             35 ;--------------------------------------------------------
                             36 ; ram data
                             37 ;--------------------------------------------------------
                             38 	.area DSEG    (PAG)
                             39 ;--------------------------------------------------------
                             40 ; overlayable items in ram
                             41 ;--------------------------------------------------------
                             42 ;--------------------------------------------------------
                             43 ; absolute ram data
                             44 ;--------------------------------------------------------
                             45 	.area IABS    (ABS)
                             46 	.area IABS    (ABS)
                             47 ;--------------------------------------------------------
                             48 ; absolute external ram data
                             49 ;--------------------------------------------------------
                             50 	.area XABS    (ABS)
                             51 ;--------------------------------------------------------
                             52 ; external initialized ram data
                             53 ;--------------------------------------------------------
                             54 	.area XISEG
   01C3                      55 _ignitionSchedule1::
   01C3                      56 	.ds 8
   01CB                      57 _ignitionSchedule2::
   01CB                      58 	.ds 8
                             59 ;--------------------------------------------------------
                             60 ; extended address mode data
                             61 ;--------------------------------------------------------
                             62 	.area XSEG
   00DE                      63 _injector1Polling::
   00DE                      64 	.ds 10
   00E8                      65 _injector2Polling::
   00E8                      66 	.ds 10
   00F2                      67 _injector3Polling::
   00F2                      68 	.ds 10
                             69 ;--------------------------------------------------------
                             70 ; global & static initialisations
                             71 ;--------------------------------------------------------
                             72 	.area HOME    (CODE)
                             73 	.area GSINIT  (CODE)
                             74 	.area GSFINAL (CODE)
                             75 	.area GSINIT  (CODE)
                             76 ;--------------------------------------------------------
                             77 ; Home
                             78 ;--------------------------------------------------------
                             79 	.area HOME    (CODE)
                             80 	.area HOME    (CODE)
                             81 ;--------------------------------------------------------
                             82 ; code
                             83 ;--------------------------------------------------------
                             84 	.area CSEG    (CODE)
                             85 ;------------------------------------------------------------
                             86 ;Allocation info for local variables in function 'getTimer1Count'
                             87 ;------------------------------------------------------------
                             88 ;sloc0                     Allocated to stack - sp +1
                             89 ;------------------------------------------------------------
                             90 ;scheduler.h:55: static inline uint16_t getTimer1Count(void) {
                             91 ;	-----------------------------------------
                             92 ;	 function getTimer1Count
                             93 ;	-----------------------------------------
                             94 ;	Register assignment is optimal.
                             95 ;	Stack space usage: 2 bytes.
   8140                      96 _getTimer1Count:
   8140 A7 FE         [ 2]   97 	ais	#-2
                             98 ;scheduler.h:56: return (uint16_t)((T1CNTH << 8) | T1CNTL);
   8142 B6 21         [ 3]   99 	lda	*0x21
   8144 5F            [ 1]  100 	clrx
   8145 9E E7 01      [ 4]  101 	sta	1,s
   8148 9E EF 02      [ 4]  102 	stx	2,s
   814B B6 22         [ 3]  103 	lda	*0x22
   814D 9E EA 02      [ 4]  104 	ora	2,s
   8150 87            [ 2]  105 	psha
   8151 9F            [ 1]  106 	txa
   8152 9E EA 02      [ 4]  107 	ora	2,s
   8155 97            [ 1]  108 	tax
   8156 86            [ 2]  109 	pula
                            110 ;scheduler.h:57: }
   8157 A7 02         [ 2]  111 	ais	#2
   8159 81            [ 4]  112 	rts
                            113 ;------------------------------------------------------------
                            114 ;Allocation info for local variables in function 'beginCoil1Charge'
                            115 ;------------------------------------------------------------
                            116 ;scheduler.c:28: static void beginCoil1Charge(void) { PTA |= COIL1_BIT; }
                            117 ;	-----------------------------------------
                            118 ;	 function beginCoil1Charge
                            119 ;	-----------------------------------------
                            120 ;	Register assignment is optimal.
                            121 ;	Stack space usage: 0 bytes.
   815A                     122 _beginCoil1Charge:
   815A B6 00         [ 3]  123 	lda	*0x00
   815C AA 01         [ 2]  124 	ora	#0x01
   815E B7 00         [ 3]  125 	sta	*0x00
   8160 81            [ 4]  126 	rts
                            127 ;------------------------------------------------------------
                            128 ;Allocation info for local variables in function 'endCoil1Charge'
                            129 ;------------------------------------------------------------
                            130 ;scheduler.c:29: static void endCoil1Charge(void)   { PTA &= (uint8_t)~COIL1_BIT; }
                            131 ;	-----------------------------------------
                            132 ;	 function endCoil1Charge
                            133 ;	-----------------------------------------
                            134 ;	Register assignment is optimal.
                            135 ;	Stack space usage: 0 bytes.
   8161                     136 _endCoil1Charge:
   8161 B6 00         [ 3]  137 	lda	*0x00
   8163 A4 FE         [ 2]  138 	and	#0xfe
   8165 B7 00         [ 3]  139 	sta	*0x00
   8167 81            [ 4]  140 	rts
                            141 ;------------------------------------------------------------
                            142 ;Allocation info for local variables in function 'beginCoil2Charge'
                            143 ;------------------------------------------------------------
                            144 ;scheduler.c:30: static void beginCoil2Charge(void) { PTA |= COIL2_BIT; }
                            145 ;	-----------------------------------------
                            146 ;	 function beginCoil2Charge
                            147 ;	-----------------------------------------
                            148 ;	Register assignment is optimal.
                            149 ;	Stack space usage: 0 bytes.
   8168                     150 _beginCoil2Charge:
   8168 B6 00         [ 3]  151 	lda	*0x00
   816A AA 02         [ 2]  152 	ora	#0x02
   816C B7 00         [ 3]  153 	sta	*0x00
   816E 81            [ 4]  154 	rts
                            155 ;------------------------------------------------------------
                            156 ;Allocation info for local variables in function 'endCoil2Charge'
                            157 ;------------------------------------------------------------
                            158 ;scheduler.c:31: static void endCoil2Charge(void)   { PTA &= (uint8_t)~COIL2_BIT; }
                            159 ;	-----------------------------------------
                            160 ;	 function endCoil2Charge
                            161 ;	-----------------------------------------
                            162 ;	Register assignment is optimal.
                            163 ;	Stack space usage: 0 bytes.
   816F                     164 _endCoil2Charge:
   816F B6 00         [ 3]  165 	lda	*0x00
   8171 A4 FD         [ 2]  166 	and	#0xfd
   8173 B7 00         [ 3]  167 	sta	*0x00
   8175 81            [ 4]  168 	rts
                            169 ;------------------------------------------------------------
                            170 ;Allocation info for local variables in function 'openInjector1'
                            171 ;------------------------------------------------------------
                            172 ;scheduler.c:39: static void openInjector1(void)  { PTB |= INJ1_BIT; }
                            173 ;	-----------------------------------------
                            174 ;	 function openInjector1
                            175 ;	-----------------------------------------
                            176 ;	Register assignment is optimal.
                            177 ;	Stack space usage: 0 bytes.
   8176                     178 _openInjector1:
   8176 B6 01         [ 3]  179 	lda	*0x01
   8178 AA 01         [ 2]  180 	ora	#0x01
   817A B7 01         [ 3]  181 	sta	*0x01
   817C 81            [ 4]  182 	rts
                            183 ;------------------------------------------------------------
                            184 ;Allocation info for local variables in function 'closeInjector1'
                            185 ;------------------------------------------------------------
                            186 ;scheduler.c:40: static void closeInjector1(void) { PTB &= (uint8_t)~INJ1_BIT; }
                            187 ;	-----------------------------------------
                            188 ;	 function closeInjector1
                            189 ;	-----------------------------------------
                            190 ;	Register assignment is optimal.
                            191 ;	Stack space usage: 0 bytes.
   817D                     192 _closeInjector1:
   817D B6 01         [ 3]  193 	lda	*0x01
   817F A4 FE         [ 2]  194 	and	#0xfe
   8181 B7 01         [ 3]  195 	sta	*0x01
   8183 81            [ 4]  196 	rts
                            197 ;------------------------------------------------------------
                            198 ;Allocation info for local variables in function 'openInjector2'
                            199 ;------------------------------------------------------------
                            200 ;scheduler.c:41: static void openInjector2(void)  { PTB |= INJ2_BIT; }
                            201 ;	-----------------------------------------
                            202 ;	 function openInjector2
                            203 ;	-----------------------------------------
                            204 ;	Register assignment is optimal.
                            205 ;	Stack space usage: 0 bytes.
   8184                     206 _openInjector2:
   8184 B6 01         [ 3]  207 	lda	*0x01
   8186 AA 02         [ 2]  208 	ora	#0x02
   8188 B7 01         [ 3]  209 	sta	*0x01
   818A 81            [ 4]  210 	rts
                            211 ;------------------------------------------------------------
                            212 ;Allocation info for local variables in function 'closeInjector2'
                            213 ;------------------------------------------------------------
                            214 ;scheduler.c:42: static void closeInjector2(void) { PTB &= (uint8_t)~INJ2_BIT; }
                            215 ;	-----------------------------------------
                            216 ;	 function closeInjector2
                            217 ;	-----------------------------------------
                            218 ;	Register assignment is optimal.
                            219 ;	Stack space usage: 0 bytes.
   818B                     220 _closeInjector2:
   818B B6 01         [ 3]  221 	lda	*0x01
   818D A4 FD         [ 2]  222 	and	#0xfd
   818F B7 01         [ 3]  223 	sta	*0x01
   8191 81            [ 4]  224 	rts
                            225 ;------------------------------------------------------------
                            226 ;Allocation info for local variables in function 'openInjector3'
                            227 ;------------------------------------------------------------
                            228 ;scheduler.c:43: static void openInjector3(void)  { PTB |= INJ3_BIT; }
                            229 ;	-----------------------------------------
                            230 ;	 function openInjector3
                            231 ;	-----------------------------------------
                            232 ;	Register assignment is optimal.
                            233 ;	Stack space usage: 0 bytes.
   8192                     234 _openInjector3:
   8192 B6 01         [ 3]  235 	lda	*0x01
   8194 AA 04         [ 2]  236 	ora	#0x04
   8196 B7 01         [ 3]  237 	sta	*0x01
   8198 81            [ 4]  238 	rts
                            239 ;------------------------------------------------------------
                            240 ;Allocation info for local variables in function 'closeInjector3'
                            241 ;------------------------------------------------------------
                            242 ;scheduler.c:44: static void closeInjector3(void) { PTB &= (uint8_t)~INJ3_BIT; }
                            243 ;	-----------------------------------------
                            244 ;	 function closeInjector3
                            245 ;	-----------------------------------------
                            246 ;	Register assignment is optimal.
                            247 ;	Stack space usage: 0 bytes.
   8199                     248 _closeInjector3:
   8199 B6 01         [ 3]  249 	lda	*0x01
   819B A4 FB         [ 2]  250 	and	#0xfb
   819D B7 01         [ 3]  251 	sta	*0x01
   819F 81            [ 4]  252 	rts
                            253 ;------------------------------------------------------------
                            254 ;Allocation info for local variables in function 'scheduleInjectorPolling'
                            255 ;------------------------------------------------------------
                            256 ;startDelay                Allocated to stack - sp +15
                            257 ;pulseWidth                Allocated to stack - sp +19
                            258 ;injState                  Allocated to stack - sp +11
                            259 ;now                       Allocated to stack - sp +7
                            260 ;sloc0                     Allocated to stack - sp +1
                            261 ;sloc1                     Allocated to stack - sp +9
                            262 ;sloc2                     Allocated to stack - sp +5
                            263 ;------------------------------------------------------------
                            264 ;scheduler.c:50: void scheduleInjectorPolling(InjectorPollingState *injState, uint32_t startDelay, uint16_t pulseWidth) {
                            265 ;	-----------------------------------------
                            266 ;	 function scheduleInjectorPolling
                            267 ;	-----------------------------------------
                            268 ;	Register assignment is optimal.
                            269 ;	Stack space usage: 12 bytes.
   81A0                     270 _scheduleInjectorPolling:
   81A0 87            [ 2]  271 	psha
   81A1 89            [ 2]  272 	pshx
   81A2 A7 F6         [ 2]  273 	ais	#-10
                            274 ;scheduler.c:51: uint32_t now = micros();
   81A4 CD 80 4F      [ 5]  275 	jsr	_micros
   81A7 9E E7 04      [ 4]  276 	sta	4,s
   81AA 9E EF 03      [ 4]  277 	stx	3,s
   81AD B6 4A         [ 3]  278 	lda	*___SDCC_hc08_ret2
   81AF 9E E7 02      [ 4]  279 	sta	2,s
   81B2 B6 4B         [ 3]  280 	lda	*___SDCC_hc08_ret3
   81B4 9E E7 01      [ 4]  281 	sta	1,s
                            282 ;scheduler.c:52: injState->openTime = now + startDelay;
   81B7 95            [ 2]  283 	tsx
   81B8 E6 0A         [ 3]  284 	lda	10,x
   81BA E7 08         [ 3]  285 	sta	8,x
   81BC E6 0B         [ 3]  286 	lda	11,x
   81BE E7 09         [ 3]  287 	sta	9,x
   81C0 E6 03         [ 3]  288 	lda	3,x
   81C2 EB 11         [ 3]  289 	add	17,x
   81C4 E7 03         [ 3]  290 	sta	3,x
   81C6 E6 02         [ 3]  291 	lda	2,x
   81C8 E9 10         [ 3]  292 	adc	16,x
   81CA E7 02         [ 3]  293 	sta	2,x
   81CC E6 01         [ 3]  294 	lda	1,x
   81CE E9 0F         [ 3]  295 	adc	15,x
   81D0 E7 01         [ 3]  296 	sta	1,x
   81D2 F6            [ 2]  297 	lda	,x
   81D3 E9 0E         [ 3]  298 	adc	14,x
   81D5 F7            [ 2]  299 	sta	,x
   81D6 E6 08         [ 3]  300 	lda	8,x
   81D8 87            [ 2]  301 	psha
   81D9 8A            [ 2]  302 	pulh
   81DA 9E EE 0A      [ 4]  303 	ldx	10,s
   81DD 9E E6 01      [ 4]  304 	lda	1,s
   81E0 E7 02         [ 3]  305 	sta	2,x
   81E2 9E E6 02      [ 4]  306 	lda	2,s
   81E5 E7 03         [ 3]  307 	sta	3,x
   81E7 9E E6 03      [ 4]  308 	lda	3,s
   81EA E7 04         [ 3]  309 	sta	4,x
   81EC 9E E6 04      [ 4]  310 	lda	4,s
   81EF E7 05         [ 3]  311 	sta	5,x
                            312 ;scheduler.c:53: injState->closeTime = injState->openTime + pulseWidth;
   81F1 95            [ 2]  313 	tsx
   81F2 E6 0A         [ 3]  314 	lda	10,x
   81F4 E7 08         [ 3]  315 	sta	8,x
   81F6 E6 0B         [ 3]  316 	lda	11,x
   81F8 E7 09         [ 3]  317 	sta	9,x
   81FA E6 13         [ 3]  318 	lda	19,x
   81FC E7 07         [ 3]  319 	sta	7,x
   81FE E6 12         [ 3]  320 	lda	18,x
   8200 E7 06         [ 3]  321 	sta	6,x
   8202 4F            [ 1]  322 	clra
   8203 E7 05         [ 3]  323 	sta	5,x
   8205 E7 04         [ 3]  324 	sta	4,x
   8207 E6 03         [ 3]  325 	lda	3,x
   8209 EB 07         [ 3]  326 	add	7,x
   820B E7 07         [ 3]  327 	sta	7,x
   820D E6 02         [ 3]  328 	lda	2,x
   820F E9 06         [ 3]  329 	adc	6,x
   8211 E7 06         [ 3]  330 	sta	6,x
   8213 E6 01         [ 3]  331 	lda	1,x
   8215 E9 05         [ 3]  332 	adc	5,x
   8217 E7 05         [ 3]  333 	sta	5,x
   8219 F6            [ 2]  334 	lda	,x
   821A E9 04         [ 3]  335 	adc	4,x
   821C E7 04         [ 3]  336 	sta	4,x
   821E E6 08         [ 3]  337 	lda	8,x
   8220 87            [ 2]  338 	psha
   8221 8A            [ 2]  339 	pulh
   8222 9E EE 0A      [ 4]  340 	ldx	10,s
   8225 9E E6 05      [ 4]  341 	lda	5,s
   8228 E7 06         [ 3]  342 	sta	6,x
   822A 9E E6 06      [ 4]  343 	lda	6,s
   822D E7 07         [ 3]  344 	sta	7,x
   822F 9E E6 07      [ 4]  345 	lda	7,s
   8232 E7 08         [ 3]  346 	sta	8,x
   8234 9E E6 08      [ 4]  347 	lda	8,s
   8237 E7 09         [ 3]  348 	sta	9,x
                            349 ;scheduler.c:54: injState->isScheduled = true;
   8239 9E E6 0B      [ 4]  350 	lda	11,s
   823C 87            [ 2]  351 	psha
   823D 8A            [ 2]  352 	pulh
   823E 9E EE 0C      [ 4]  353 	ldx	12,s
   8241 A6 01         [ 2]  354 	lda	#0x01
   8243 F7            [ 2]  355 	sta	,x
                            356 ;scheduler.c:55: injState->isOpen = false;
   8244 95            [ 2]  357 	tsx
   8245 E6 0A         [ 3]  358 	lda	10,x
   8247 E7 04         [ 3]  359 	sta	4,x
   8249 E6 0B         [ 3]  360 	lda	11,x
   824B E7 05         [ 3]  361 	sta	5,x
   824D E6 04         [ 3]  362 	lda	4,x
   824F 87            [ 2]  363 	psha
   8250 8A            [ 2]  364 	pulh
   8251 9E EE 06      [ 4]  365 	ldx	6,s
   8254 4F            [ 1]  366 	clra
   8255 E7 01         [ 3]  367 	sta	1,x
                            368 ;scheduler.c:56: }
   8257 A7 0C         [ 2]  369 	ais	#12
   8259 81            [ 4]  370 	rts
                            371 ;------------------------------------------------------------
                            372 ;Allocation info for local variables in function 'processInjectorPolling'
                            373 ;------------------------------------------------------------
                            374 ;now                       Allocated to stack - sp +5
                            375 ;sloc0                     Allocated to stack - sp +5
                            376 ;sloc1                     Allocated to stack - sp +1
                            377 ;------------------------------------------------------------
                            378 ;scheduler.c:58: void processInjectorPolling(void) {
                            379 ;	-----------------------------------------
                            380 ;	 function processInjectorPolling
                            381 ;	-----------------------------------------
                            382 ;	Register assignment is optimal.
                            383 ;	Stack space usage: 8 bytes.
   825A                     384 _processInjectorPolling:
   825A A7 F8         [ 2]  385 	ais	#-8
                            386 ;scheduler.c:59: uint32_t now = micros();
   825C CD 80 4F      [ 5]  387 	jsr	_micros
   825F 9E E7 08      [ 4]  388 	sta	8,s
   8262 9E EF 07      [ 4]  389 	stx	7,s
   8265 B6 4A         [ 3]  390 	lda	*___SDCC_hc08_ret2
   8267 9E E7 06      [ 4]  391 	sta	6,s
   826A B6 4B         [ 3]  392 	lda	*___SDCC_hc08_ret3
   826C 9E E7 05      [ 4]  393 	sta	5,s
                            394 ;scheduler.c:61: if (injector1Polling.isScheduled) {
   826F C6 00 DE      [ 4]  395 	lda	_injector1Polling
   8272 26 02         [ 3]  396 	bne	00205$
   8274 20 78         [ 3]  397 	bra	00109$
   8276                     398 00205$:
                            399 ;scheduler.c:62: if (!injector1Polling.isOpen && now >= injector1Polling.openTime) {
   8276 CE 00 DF      [ 4]  400 	ldx	(_injector1Polling + 0x0001)
   8279 26 3C         [ 3]  401 	bne	00105$
   827B C6 00 E0      [ 4]  402 	lda	(_injector1Polling + 0x0002)
   827E 9E E7 01      [ 4]  403 	sta	1,s
   8281 C6 00 E1      [ 4]  404 	lda	((_injector1Polling + 0x0002) + 1)
   8284 9E E7 02      [ 4]  405 	sta	2,s
   8287 C6 00 E2      [ 4]  406 	lda	((_injector1Polling + 0x0002) + 2)
   828A 9E E7 03      [ 4]  407 	sta	3,s
   828D C6 00 E3      [ 4]  408 	lda	((_injector1Polling + 0x0002) + 3)
   8290 9E E7 04      [ 4]  409 	sta	4,s
   8293 9E E6 08      [ 4]  410 	lda	8,s
   8296 9E E0 04      [ 4]  411 	sub	4,s
   8299 9E E6 07      [ 4]  412 	lda	7,s
   829C 9E E2 03      [ 4]  413 	sbc	3,s
   829F 9E E6 06      [ 4]  414 	lda	6,s
   82A2 9E E2 02      [ 4]  415 	sbc	2,s
   82A5 9E E6 05      [ 4]  416 	lda	5,s
   82A8 9E E2 01      [ 4]  417 	sbc	1,s
   82AB 25 0A         [ 3]  418 	bcs	00105$
                            419 ;scheduler.c:63: openInjector1();
   82AD CD 81 76      [ 5]  420 	jsr	_openInjector1
                            421 ;scheduler.c:64: injector1Polling.isOpen = true;
   82B0 A6 01         [ 2]  422 	lda	#0x01
   82B2 C7 00 DF      [ 4]  423 	sta	(_injector1Polling + 0x0001)
   82B5 20 37         [ 3]  424 	bra	00109$
   82B7                     425 00105$:
                            426 ;scheduler.c:65: } else if (injector1Polling.isOpen && now >= injector1Polling.closeTime) {
   82B7 5D            [ 1]  427 	tstx
   82B8 27 34         [ 3]  428 	beq	00109$
   82BA C6 00 E4      [ 4]  429 	lda	(_injector1Polling + 0x0006)
   82BD 9E E7 01      [ 4]  430 	sta	1,s
   82C0 C6 00 E5      [ 4]  431 	lda	((_injector1Polling + 0x0006) + 1)
   82C3 9E E7 02      [ 4]  432 	sta	2,s
   82C6 C6 00 E6      [ 4]  433 	lda	((_injector1Polling + 0x0006) + 2)
   82C9 9E E7 03      [ 4]  434 	sta	3,s
   82CC C6 00 E7      [ 4]  435 	lda	((_injector1Polling + 0x0006) + 3)
   82CF 9E E7 04      [ 4]  436 	sta	4,s
   82D2 95            [ 2]  437 	tsx
   82D3 E6 07         [ 3]  438 	lda	7,x
   82D5 E0 03         [ 3]  439 	sub	3,x
   82D7 E6 06         [ 3]  440 	lda	6,x
   82D9 E2 02         [ 3]  441 	sbc	2,x
   82DB E6 05         [ 3]  442 	lda	5,x
   82DD E2 01         [ 3]  443 	sbc	1,x
   82DF E6 04         [ 3]  444 	lda	4,x
   82E1 F2            [ 2]  445 	sbc	,x
   82E2 25 0A         [ 3]  446 	bcs	00109$
                            447 ;scheduler.c:66: closeInjector1();
   82E4 CD 81 7D      [ 5]  448 	jsr	_closeInjector1
                            449 ;scheduler.c:67: injector1Polling.isOpen = false;
   82E7 4F            [ 1]  450 	clra
   82E8 C7 00 DF      [ 4]  451 	sta	(_injector1Polling + 0x0001)
                            452 ;scheduler.c:68: injector1Polling.isScheduled = false;
   82EB C7 00 DE      [ 4]  453 	sta	_injector1Polling
   82EE                     454 00109$:
                            455 ;scheduler.c:72: if (injector2Polling.isScheduled) {
   82EE C6 00 E8      [ 4]  456 	lda	_injector2Polling
   82F1 26 02         [ 3]  457 	bne	00210$
   82F3 20 78         [ 3]  458 	bra	00118$
   82F5                     459 00210$:
                            460 ;scheduler.c:73: if (!injector2Polling.isOpen && now >= injector2Polling.openTime) {
   82F5 CE 00 E9      [ 4]  461 	ldx	(_injector2Polling + 0x0001)
   82F8 26 3C         [ 3]  462 	bne	00114$
   82FA C6 00 EA      [ 4]  463 	lda	(_injector2Polling + 0x0002)
   82FD 9E E7 01      [ 4]  464 	sta	1,s
   8300 C6 00 EB      [ 4]  465 	lda	((_injector2Polling + 0x0002) + 1)
   8303 9E E7 02      [ 4]  466 	sta	2,s
   8306 C6 00 EC      [ 4]  467 	lda	((_injector2Polling + 0x0002) + 2)
   8309 9E E7 03      [ 4]  468 	sta	3,s
   830C C6 00 ED      [ 4]  469 	lda	((_injector2Polling + 0x0002) + 3)
   830F 9E E7 04      [ 4]  470 	sta	4,s
   8312 9E E6 08      [ 4]  471 	lda	8,s
   8315 9E E0 04      [ 4]  472 	sub	4,s
   8318 9E E6 07      [ 4]  473 	lda	7,s
   831B 9E E2 03      [ 4]  474 	sbc	3,s
   831E 9E E6 06      [ 4]  475 	lda	6,s
   8321 9E E2 02      [ 4]  476 	sbc	2,s
   8324 9E E6 05      [ 4]  477 	lda	5,s
   8327 9E E2 01      [ 4]  478 	sbc	1,s
   832A 25 0A         [ 3]  479 	bcs	00114$
                            480 ;scheduler.c:74: openInjector2();
   832C CD 81 84      [ 5]  481 	jsr	_openInjector2
                            482 ;scheduler.c:75: injector2Polling.isOpen = true;
   832F A6 01         [ 2]  483 	lda	#0x01
   8331 C7 00 E9      [ 4]  484 	sta	(_injector2Polling + 0x0001)
   8334 20 37         [ 3]  485 	bra	00118$
   8336                     486 00114$:
                            487 ;scheduler.c:76: } else if (injector2Polling.isOpen && now >= injector2Polling.closeTime) {
   8336 5D            [ 1]  488 	tstx
   8337 27 34         [ 3]  489 	beq	00118$
   8339 C6 00 EE      [ 4]  490 	lda	(_injector2Polling + 0x0006)
   833C 9E E7 01      [ 4]  491 	sta	1,s
   833F C6 00 EF      [ 4]  492 	lda	((_injector2Polling + 0x0006) + 1)
   8342 9E E7 02      [ 4]  493 	sta	2,s
   8345 C6 00 F0      [ 4]  494 	lda	((_injector2Polling + 0x0006) + 2)
   8348 9E E7 03      [ 4]  495 	sta	3,s
   834B C6 00 F1      [ 4]  496 	lda	((_injector2Polling + 0x0006) + 3)
   834E 9E E7 04      [ 4]  497 	sta	4,s
   8351 95            [ 2]  498 	tsx
   8352 E6 07         [ 3]  499 	lda	7,x
   8354 E0 03         [ 3]  500 	sub	3,x
   8356 E6 06         [ 3]  501 	lda	6,x
   8358 E2 02         [ 3]  502 	sbc	2,x
   835A E6 05         [ 3]  503 	lda	5,x
   835C E2 01         [ 3]  504 	sbc	1,x
   835E E6 04         [ 3]  505 	lda	4,x
   8360 F2            [ 2]  506 	sbc	,x
   8361 25 0A         [ 3]  507 	bcs	00118$
                            508 ;scheduler.c:77: closeInjector2();
   8363 CD 81 8B      [ 5]  509 	jsr	_closeInjector2
                            510 ;scheduler.c:78: injector2Polling.isOpen = false;
   8366 4F            [ 1]  511 	clra
   8367 C7 00 E9      [ 4]  512 	sta	(_injector2Polling + 0x0001)
                            513 ;scheduler.c:79: injector2Polling.isScheduled = false;
   836A C7 00 E8      [ 4]  514 	sta	_injector2Polling
   836D                     515 00118$:
                            516 ;scheduler.c:83: if (injector3Polling.isScheduled) {
   836D C6 00 F2      [ 4]  517 	lda	_injector3Polling
   8370 26 02         [ 3]  518 	bne	00215$
   8372 20 78         [ 3]  519 	bra	00128$
   8374                     520 00215$:
                            521 ;scheduler.c:84: if (!injector3Polling.isOpen && now >= injector3Polling.openTime) {
   8374 CE 00 F3      [ 4]  522 	ldx	(_injector3Polling + 0x0001)
   8377 26 3C         [ 3]  523 	bne	00123$
   8379 C6 00 F4      [ 4]  524 	lda	(_injector3Polling + 0x0002)
   837C 9E E7 01      [ 4]  525 	sta	1,s
   837F C6 00 F5      [ 4]  526 	lda	((_injector3Polling + 0x0002) + 1)
   8382 9E E7 02      [ 4]  527 	sta	2,s
   8385 C6 00 F6      [ 4]  528 	lda	((_injector3Polling + 0x0002) + 2)
   8388 9E E7 03      [ 4]  529 	sta	3,s
   838B C6 00 F7      [ 4]  530 	lda	((_injector3Polling + 0x0002) + 3)
   838E 9E E7 04      [ 4]  531 	sta	4,s
   8391 9E E6 08      [ 4]  532 	lda	8,s
   8394 9E E0 04      [ 4]  533 	sub	4,s
   8397 9E E6 07      [ 4]  534 	lda	7,s
   839A 9E E2 03      [ 4]  535 	sbc	3,s
   839D 9E E6 06      [ 4]  536 	lda	6,s
   83A0 9E E2 02      [ 4]  537 	sbc	2,s
   83A3 9E E6 05      [ 4]  538 	lda	5,s
   83A6 9E E2 01      [ 4]  539 	sbc	1,s
   83A9 25 0A         [ 3]  540 	bcs	00123$
                            541 ;scheduler.c:85: openInjector3();
   83AB CD 81 92      [ 5]  542 	jsr	_openInjector3
                            543 ;scheduler.c:86: injector3Polling.isOpen = true;
   83AE A6 01         [ 2]  544 	lda	#0x01
   83B0 C7 00 F3      [ 4]  545 	sta	(_injector3Polling + 0x0001)
   83B3 20 37         [ 3]  546 	bra	00128$
   83B5                     547 00123$:
                            548 ;scheduler.c:87: } else if (injector3Polling.isOpen && now >= injector3Polling.closeTime) {
   83B5 5D            [ 1]  549 	tstx
   83B6 27 34         [ 3]  550 	beq	00128$
   83B8 C6 00 F8      [ 4]  551 	lda	(_injector3Polling + 0x0006)
   83BB 9E E7 01      [ 4]  552 	sta	1,s
   83BE C6 00 F9      [ 4]  553 	lda	((_injector3Polling + 0x0006) + 1)
   83C1 9E E7 02      [ 4]  554 	sta	2,s
   83C4 C6 00 FA      [ 4]  555 	lda	((_injector3Polling + 0x0006) + 2)
   83C7 9E E7 03      [ 4]  556 	sta	3,s
   83CA C6 00 FB      [ 4]  557 	lda	((_injector3Polling + 0x0006) + 3)
   83CD 9E E7 04      [ 4]  558 	sta	4,s
   83D0 95            [ 2]  559 	tsx
   83D1 E6 07         [ 3]  560 	lda	7,x
   83D3 E0 03         [ 3]  561 	sub	3,x
   83D5 E6 06         [ 3]  562 	lda	6,x
   83D7 E2 02         [ 3]  563 	sbc	2,x
   83D9 E6 05         [ 3]  564 	lda	5,x
   83DB E2 01         [ 3]  565 	sbc	1,x
   83DD E6 04         [ 3]  566 	lda	4,x
   83DF F2            [ 2]  567 	sbc	,x
   83E0 25 0A         [ 3]  568 	bcs	00128$
                            569 ;scheduler.c:88: closeInjector3();
   83E2 CD 81 99      [ 5]  570 	jsr	_closeInjector3
                            571 ;scheduler.c:89: injector3Polling.isOpen = false;
   83E5 4F            [ 1]  572 	clra
   83E6 C7 00 F3      [ 4]  573 	sta	(_injector3Polling + 0x0001)
                            574 ;scheduler.c:90: injector3Polling.isScheduled = false;
   83E9 C7 00 F2      [ 4]  575 	sta	_injector3Polling
   83EC                     576 00128$:
                            577 ;scheduler.c:93: }
   83EC A7 08         [ 2]  578 	ais	#8
   83EE 81            [ 4]  579 	rts
                            580 ;------------------------------------------------------------
                            581 ;Allocation info for local variables in function 'schedulerInit'
                            582 ;------------------------------------------------------------
                            583 ;scheduler.c:95: void schedulerInit(void) {
                            584 ;	-----------------------------------------
                            585 ;	 function schedulerInit
                            586 ;	-----------------------------------------
                            587 ;	Register assignment is optimal.
                            588 ;	Stack space usage: 0 bytes.
   83EF                     589 _schedulerInit:
                            590 ;scheduler.c:96: DDRA |= (COIL1_BIT | COIL2_BIT);  /* bobinas como saida */
   83EF B6 04         [ 3]  591 	lda	*0x04
   83F1 AA 03         [ 2]  592 	ora	#0x03
   83F3 B7 04         [ 3]  593 	sta	*0x04
                            594 ;scheduler.c:97: DDRB |= (INJ1_BIT | INJ2_BIT | INJ3_BIT);  /* injetores como saida */
   83F5 B6 05         [ 3]  595 	lda	*0x05
   83F7 AA 07         [ 2]  596 	ora	#0x07
   83F9 B7 05         [ 3]  597 	sta	*0x05
                            598 ;scheduler.c:98: endCoil1Charge();
   83FB CD 81 61      [ 5]  599 	jsr	_endCoil1Charge
                            600 ;scheduler.c:99: endCoil2Charge();
   83FE CD 81 6F      [ 5]  601 	jsr	_endCoil2Charge
                            602 ;scheduler.c:100: closeInjector1();
   8401 CD 81 7D      [ 5]  603 	jsr	_closeInjector1
                            604 ;scheduler.c:101: closeInjector2();
   8404 CD 81 8B      [ 5]  605 	jsr	_closeInjector2
                            606 ;scheduler.c:102: closeInjector3();
   8407 CD 81 99      [ 5]  607 	jsr	_closeInjector3
                            608 ;scheduler.c:107: T1SC = (1 << T1SC_TRST);
   840A 6E 10 20      [ 4]  609 	mov	#0x10,*0x20
                            610 ;scheduler.c:108: T1SC0 = (1 << TxSCx_MSxA);
   840D 6E 10 25      [ 4]  611 	mov	#0x10,*0x25
                            612 ;scheduler.c:109: T1SC0 |= (1 << TxSCx_CHxIE);
   8410 B6 25         [ 3]  613 	lda	*0x25
   8412 AA 40         [ 2]  614 	ora	#0x40
   8414 B7 25         [ 3]  615 	sta	*0x25
                            616 ;scheduler.c:110: T1SC1 = (1 << TxSCx_MSxA) | (1 << TxSCx_CHxIE);
   8416 6E 50 28      [ 4]  617 	mov	#0x50,*0x28
                            618 ;scheduler.c:111: T1SC = (6 << T1SC_PS0);  /* PS[2:0]=110 -> /64. Ver US_TO_TIMER1 em scheduler.h */
   8419 6E 06 20      [ 4]  619 	mov	#0x06,*0x20
                            620 ;scheduler.c:112: }
   841C 81            [ 4]  621 	rts
                            622 ;------------------------------------------------------------
                            623 ;Allocation info for local variables in function 'handleIgnitionChannel'
                            624 ;------------------------------------------------------------
                            625 ;beginCharge               Allocated to stack - sp +11
                            626 ;endCharge                 Allocated to stack - sp +13
                            627 ;compareReg                Allocated to stack - sp +15
                            628 ;schedule                  Allocated to stack - sp +7
                            629 ;__1966080003              Allocated to registers a x 
                            630 ;sloc0                     Allocated to stack - sp +5
                            631 ;sloc1                     Allocated to stack - sp +1
                            632 ;sloc2                     Allocated to stack - sp +3
                            633 ;------------------------------------------------------------
                            634 ;scheduler.c:114: static void handleIgnitionChannel(volatile IgnitionSchedule *schedule,
                            635 ;	-----------------------------------------
                            636 ;	 function handleIgnitionChannel
                            637 ;	-----------------------------------------
                            638 ;	Register assignment is optimal.
                            639 ;	Stack space usage: 8 bytes.
   841D                     640 _handleIgnitionChannel:
   841D 87            [ 2]  641 	psha
   841E 89            [ 2]  642 	pshx
   841F A7 FA         [ 2]  643 	ais	#-6
                            644 ;scheduler.c:118: if (schedule->status == SCHED_PENDING) {
   8421 95            [ 2]  645 	tsx
   8422 E6 06         [ 3]  646 	lda	6,x
   8424 E7 04         [ 3]  647 	sta	4,x
   8426 E6 07         [ 3]  648 	lda	7,x
   8428 E7 05         [ 3]  649 	sta	5,x
   842A E6 04         [ 3]  650 	lda	4,x
   842C 87            [ 2]  651 	psha
   842D 8A            [ 2]  652 	pulh
   842E 9E EE 06      [ 4]  653 	ldx	6,s
   8431 F6            [ 2]  654 	lda	,x
   8432 41 01 03      [ 4]  655 	cbeqa	#0x01,00125$
   8435 CC 84 CB      [ 3]  656 	jmp	00104$
   8438                     657 00125$:
                            658 ;scheduler.c:119: schedule->status = SCHED_RUNNING;
   8438 9E E6 05      [ 4]  659 	lda	5,s
   843B 87            [ 2]  660 	psha
   843C 8A            [ 2]  661 	pulh
   843D 9E EE 06      [ 4]  662 	ldx	6,s
   8440 A6 02         [ 2]  663 	lda	#0x02
   8442 F7            [ 2]  664 	sta	,x
                            665 ;scheduler.c:120: beginCharge();
   8443 AD 02         [ 4]  666 	bsr	00127$
   8445 20 09         [ 3]  667 	bra	00126$
   8447                     668 00127$:
   8447 9E E6 0E      [ 4]  669 	lda	14,s
   844A 87            [ 2]  670 	psha
   844B 9E E6 0E      [ 4]  671 	lda	14,s
   844E 87            [ 2]  672 	psha
   844F 81            [ 4]  673 	rts
   8450                     674 00126$:
                            675 ;scheduler.c:121: *compareReg = schedule->endCompare;
   8450 95            [ 2]  676 	tsx
   8451 E6 0E         [ 3]  677 	lda	14,x
   8453 F7            [ 2]  678 	sta	,x
   8454 E6 0F         [ 3]  679 	lda	15,x
   8456 E7 01         [ 3]  680 	sta	1,x
   8458 E6 04         [ 3]  681 	lda	4,x
   845A E7 02         [ 3]  682 	sta	2,x
   845C E6 05         [ 3]  683 	lda	5,x
   845E E7 03         [ 3]  684 	sta	3,x
   8460 E6 02         [ 3]  685 	lda	2,x
   8462 87            [ 2]  686 	psha
   8463 8A            [ 2]  687 	pulh
   8464 9E EE 04      [ 4]  688 	ldx	4,s
   8467 E6 04         [ 3]  689 	lda	4,x
   8469 EE 03         [ 3]  690 	ldx	3,x
   846B 89            [ 2]  691 	pshx
   846C 9E EE 02      [ 4]  692 	ldx	2,s
   846F 89            [ 2]  693 	pshx
   8470 8A            [ 2]  694 	pulh
   8471 9E EE 03      [ 4]  695 	ldx	3,s
   8474 E7 01         [ 3]  696 	sta	1,x
   8476 86            [ 2]  697 	pula
   8477 F7            [ 2]  698 	sta	,x
                            699 ;scheduler.h:56: return (uint16_t)((T1CNTH << 8) | T1CNTL);
   8478 B6 21         [ 3]  700 	lda	*0x21
   847A 5F            [ 1]  701 	clrx
   847B 9E E7 01      [ 4]  702 	sta	1,s
   847E 9E EF 02      [ 4]  703 	stx	2,s
   8481 B6 22         [ 3]  704 	lda	*0x22
   8483 9E EA 02      [ 4]  705 	ora	2,s
   8486 87            [ 2]  706 	psha
   8487 9F            [ 1]  707 	txa
   8488 9E EA 02      [ 4]  708 	ora	2,s
   848B 97            [ 1]  709 	tax
   848C 86            [ 2]  710 	pula
                            711 ;scheduler.c:123: if ((int16_t)(getTimer1Count() - schedule->endCompare) >= 0) {
   848D 89            [ 2]  712 	pshx
   848E 9E EE 04      [ 4]  713 	ldx	4,s
   8491 89            [ 2]  714 	pshx
   8492 8A            [ 2]  715 	pulh
   8493 9E EE 05      [ 4]  716 	ldx	5,s
   8496 87            [ 2]  717 	psha
   8497 E6 03         [ 3]  718 	lda	3,x
   8499 9E E7 05      [ 4]  719 	sta	5,s
   849C E6 04         [ 3]  720 	lda	4,x
   849E 9E E7 06      [ 4]  721 	sta	6,s
   84A1 86            [ 2]  722 	pula
   84A2 88            [ 2]  723 	pulx
   84A3 9E E0 04      [ 4]  724 	sub	4,s
   84A6 87            [ 2]  725 	psha
   84A7 9F            [ 1]  726 	txa
   84A8 9E E2 04      [ 4]  727 	sbc	4,s
   84AB 97            [ 1]  728 	tax
   84AC 86            [ 2]  729 	pula
   84AD 9F            [ 1]  730 	txa
   84AE A0 00         [ 2]  731 	sub	#0x00
   84B0 91 17         [ 3]  732 	blt	00102$
                            733 ;scheduler.c:124: schedule->status = SCHED_OFF;
   84B2 9E E6 05      [ 4]  734 	lda	5,s
   84B5 87            [ 2]  735 	psha
   84B6 8A            [ 2]  736 	pulh
   84B7 9E EE 06      [ 4]  737 	ldx	6,s
   84BA 4F            [ 1]  738 	clra
   84BB F7            [ 2]  739 	sta	,x
                            740 ;scheduler.c:125: endCharge();
   84BC AD 02         [ 4]  741 	bsr	00130$
   84BE 20 09         [ 3]  742 	bra	00129$
   84C0                     743 00130$:
   84C0 9E E6 10      [ 4]  744 	lda	16,s
   84C3 87            [ 2]  745 	psha
   84C4 9E E6 10      [ 4]  746 	lda	16,s
   84C7 87            [ 2]  747 	psha
   84C8 81            [ 4]  748 	rts
   84C9                     749 00129$:
   84C9                     750 00102$:
                            751 ;scheduler.c:127: return;
   84C9 20 24         [ 3]  752 	bra	00108$
   84CB                     753 00104$:
                            754 ;scheduler.c:130: if (schedule->status == SCHED_RUNNING) {
   84CB 9E E6 05      [ 4]  755 	lda	5,s
   84CE 87            [ 2]  756 	psha
   84CF 8A            [ 2]  757 	pulh
   84D0 9E EE 06      [ 4]  758 	ldx	6,s
   84D3 F6            [ 2]  759 	lda	,x
   84D4 A1 02         [ 2]  760 	cmp	#0x02
   84D6 26 17         [ 3]  761 	bne	00108$
                            762 ;scheduler.c:131: schedule->status = SCHED_OFF;
   84D8 9E E6 05      [ 4]  763 	lda	5,s
   84DB 87            [ 2]  764 	psha
   84DC 8A            [ 2]  765 	pulh
   84DD 9E EE 06      [ 4]  766 	ldx	6,s
   84E0 4F            [ 1]  767 	clra
   84E1 F7            [ 2]  768 	sta	,x
                            769 ;scheduler.c:132: endCharge();
   84E2 AD 02         [ 4]  770 	bsr	00133$
   84E4 20 09         [ 3]  771 	bra	00132$
   84E6                     772 00133$:
   84E6 9E E6 10      [ 4]  773 	lda	16,s
   84E9 87            [ 2]  774 	psha
   84EA 9E E6 10      [ 4]  775 	lda	16,s
   84ED 87            [ 2]  776 	psha
   84EE 81            [ 4]  777 	rts
   84EF                     778 00132$:
   84EF                     779 00108$:
                            780 ;scheduler.c:134: }
   84EF A7 08         [ 2]  781 	ais	#8
   84F1 81            [ 4]  782 	rts
                            783 ;------------------------------------------------------------
                            784 ;Allocation info for local variables in function 'armIgnitionCompare'
                            785 ;------------------------------------------------------------
                            786 ;beginCharge               Allocated to stack - sp +13
                            787 ;endCharge                 Allocated to stack - sp +15
                            788 ;compareReg                Allocated to stack - sp +17
                            789 ;schedule                  Allocated to stack - sp +9
                            790 ;__1310720005              Allocated to registers a x 
                            791 ;sloc0                     Allocated to stack - sp +5
                            792 ;sloc1                     Allocated to stack - sp +7
                            793 ;sloc2                     Allocated to stack - sp +3
                            794 ;sloc3                     Allocated to stack - sp +1
                            795 ;------------------------------------------------------------
                            796 ;scheduler.c:136: static void armIgnitionCompare(volatile IgnitionSchedule *schedule,
                            797 ;	-----------------------------------------
                            798 ;	 function armIgnitionCompare
                            799 ;	-----------------------------------------
                            800 ;	Register assignment is optimal.
                            801 ;	Stack space usage: 10 bytes.
   84F2                     802 _armIgnitionCompare:
   84F2 87            [ 2]  803 	psha
   84F3 89            [ 2]  804 	pshx
   84F4 A7 F8         [ 2]  805 	ais	#-8
                            806 ;scheduler.c:140: *compareReg = schedule->startCompare;
   84F6 95            [ 2]  807 	tsx
   84F7 E6 10         [ 3]  808 	lda	16,x
   84F9 E7 04         [ 3]  809 	sta	4,x
   84FB E6 11         [ 3]  810 	lda	17,x
   84FD E7 05         [ 3]  811 	sta	5,x
   84FF E6 08         [ 3]  812 	lda	8,x
   8501 E7 06         [ 3]  813 	sta	6,x
   8503 E6 09         [ 3]  814 	lda	9,x
   8505 E7 07         [ 3]  815 	sta	7,x
   8507 E6 06         [ 3]  816 	lda	6,x
   8509 E7 02         [ 3]  817 	sta	2,x
   850B E6 07         [ 3]  818 	lda	7,x
   850D E7 03         [ 3]  819 	sta	3,x
   850F E6 02         [ 3]  820 	lda	2,x
   8511 87            [ 2]  821 	psha
   8512 8A            [ 2]  822 	pulh
   8513 9E EE 04      [ 4]  823 	ldx	4,s
   8516 E6 02         [ 3]  824 	lda	2,x
   8518 EE 01         [ 3]  825 	ldx	1,x
   851A 89            [ 2]  826 	pshx
   851B 9E EE 06      [ 4]  827 	ldx	6,s
   851E 89            [ 2]  828 	pshx
   851F 8A            [ 2]  829 	pulh
   8520 9E EE 07      [ 4]  830 	ldx	7,s
   8523 E7 01         [ 3]  831 	sta	1,x
   8525 86            [ 2]  832 	pula
   8526 F7            [ 2]  833 	sta	,x
                            834 ;scheduler.h:56: return (uint16_t)((T1CNTH << 8) | T1CNTL);
   8527 B6 21         [ 3]  835 	lda	*0x21
   8529 5F            [ 1]  836 	clrx
   852A 9E E7 01      [ 4]  837 	sta	1,s
   852D 9E EF 02      [ 4]  838 	stx	2,s
   8530 B6 22         [ 3]  839 	lda	*0x22
   8532 9E EA 02      [ 4]  840 	ora	2,s
   8535 87            [ 2]  841 	psha
   8536 9F            [ 1]  842 	txa
   8537 9E EA 02      [ 4]  843 	ora	2,s
   853A 97            [ 1]  844 	tax
   853B 86            [ 2]  845 	pula
                            846 ;scheduler.c:142: if ((int16_t)(getTimer1Count() - schedule->startCompare) >= 0) {
   853C 89            [ 2]  847 	pshx
   853D 9E EE 04      [ 4]  848 	ldx	4,s
   8540 89            [ 2]  849 	pshx
   8541 8A            [ 2]  850 	pulh
   8542 9E EE 05      [ 4]  851 	ldx	5,s
   8545 87            [ 2]  852 	psha
   8546 E6 01         [ 3]  853 	lda	1,x
   8548 9E E7 03      [ 4]  854 	sta	3,s
   854B E6 02         [ 3]  855 	lda	2,x
   854D 9E E7 04      [ 4]  856 	sta	4,s
   8550 86            [ 2]  857 	pula
   8551 88            [ 2]  858 	pulx
   8552 9E E0 02      [ 4]  859 	sub	2,s
   8555 87            [ 2]  860 	psha
   8556 9F            [ 1]  861 	txa
   8557 9E E2 02      [ 4]  862 	sbc	2,s
   855A 97            [ 1]  863 	tax
   855B 86            [ 2]  864 	pula
   855C 9F            [ 1]  865 	txa
   855D A0 00         [ 2]  866 	sub	#0x00
   855F 91 1C         [ 3]  867 	blt	00104$
                            868 ;scheduler.c:143: handleIgnitionChannel(schedule, beginCharge, endCharge, compareReg);
   8561 95            [ 2]  869 	tsx
   8562 E6 05         [ 3]  870 	lda	5,x
   8564 87            [ 2]  871 	psha
   8565 E6 04         [ 3]  872 	lda	4,x
   8567 87            [ 2]  873 	psha
   8568 E6 0F         [ 3]  874 	lda	15,x
   856A 87            [ 2]  875 	psha
   856B E6 0E         [ 3]  876 	lda	14,x
   856D 87            [ 2]  877 	psha
   856E E6 0D         [ 3]  878 	lda	13,x
   8570 87            [ 2]  879 	psha
   8571 E6 0C         [ 3]  880 	lda	12,x
   8573 87            [ 2]  881 	psha
   8574 E6 07         [ 3]  882 	lda	7,x
   8576 EE 06         [ 3]  883 	ldx	6,x
   8578 CD 84 1D      [ 5]  884 	jsr	_handleIgnitionChannel
   857B A7 06         [ 2]  885 	ais	#6
   857D                     886 00104$:
                            887 ;scheduler.c:145: }
   857D A7 0A         [ 2]  888 	ais	#10
   857F 81            [ 4]  889 	rts
                            890 ;------------------------------------------------------------
                            891 ;Allocation info for local variables in function 'setIgnitionSchedule'
                            892 ;------------------------------------------------------------
                            893 ;startTime                 Allocated to stack - sp +33
                            894 ;duration                  Allocated to stack - sp +37
                            895 ;channel                   Allocated to stack - sp +39
                            896 ;schedule                  Allocated to stack - sp +27
                            897 ;__1310720007              Allocated to stack - sp +25
                            898 ;startTicks                Allocated to stack - sp +5
                            899 ;durationTicks             Allocated to stack - sp +1
                            900 ;totalTicks                Allocated to stack - sp +15
                            901 ;minTicks                  Allocated to stack - sp +11
                            902 ;currentCount              Allocated to registers 
                            903 ;startTicks16              Allocated to registers x h 
                            904 ;durationTicks16           Allocated to stack - sp +29
                            905 ;sloc0                     Allocated to stack - sp +17
                            906 ;sloc1                     Allocated to stack - sp +19
                            907 ;sloc2                     Allocated to stack - sp +13
                            908 ;sloc3                     Allocated to stack - sp +21
                            909 ;sloc4                     Allocated to stack - sp +9
                            910 ;------------------------------------------------------------
                            911 ;scheduler.c:147: void setIgnitionSchedule(volatile IgnitionSchedule *schedule, uint32_t startTime,
                            912 ;	-----------------------------------------
                            913 ;	 function setIgnitionSchedule
                            914 ;	-----------------------------------------
                            915 ;	Register assignment might be sub-optimal.
                            916 ;	Stack space usage: 30 bytes.
   8580                     917 _setIgnitionSchedule:
   8580 A7 E2         [ 2]  918 	ais	#-30
   8582 9E E7 1C      [ 4]  919 	sta	28,s
   8585 9E EF 1B      [ 4]  920 	stx	27,s
                            921 ;scheduler.c:153: schedule->status = SCHED_OFF;
   8588 95            [ 2]  922 	tsx
   8589 E6 1A         [ 3]  923 	lda	26,x
   858B E7 10         [ 3]  924 	sta	16,x
   858D E6 1B         [ 3]  925 	lda	27,x
   858F E7 11         [ 3]  926 	sta	17,x
                            927 ;scheduler.c:152: if (channel > 2) {
   8591 E6 26         [ 3]  928 	lda	38,x
   8593 A1 02         [ 2]  929 	cmp	#0x02
   8595 23 0C         [ 3]  930 	bls	00102$
                            931 ;scheduler.c:153: schedule->status = SCHED_OFF;
   8597 E6 10         [ 3]  932 	lda	16,x
   8599 87            [ 2]  933 	psha
   859A 8A            [ 2]  934 	pulh
   859B 9E EE 12      [ 4]  935 	ldx	18,s
   859E 4F            [ 1]  936 	clra
   859F F7            [ 2]  937 	sta	,x
                            938 ;scheduler.c:154: return;
   85A0 CC 87 FD      [ 3]  939 	jmp	00119$
   85A3                     940 00102$:
                            941 ;scheduler.c:157: if (schedule->status == SCHED_RUNNING) {
   85A3 9E E6 11      [ 4]  942 	lda	17,s
   85A6 87            [ 2]  943 	psha
   85A7 8A            [ 2]  944 	pulh
   85A8 9E EE 12      [ 4]  945 	ldx	18,s
   85AB F6            [ 2]  946 	lda	,x
                            947 ;scheduler.c:159: if (schedule->channel == 1) { endCoil1Charge(); } else { endCoil2Charge(); }
   85AC 95            [ 2]  948 	tsx
   85AD EE 10         [ 3]  949 	ldx	16,x
   85AF 9E EF 13      [ 4]  950 	stx	19,s
   85B2 87            [ 2]  951 	psha
   85B3 9E E6 13      [ 4]  952 	lda	19,s
   85B6 9E E7 15      [ 4]  953 	sta	21,s
   85B9 86            [ 2]  954 	pula
                            955 ;scheduler.c:157: if (schedule->status == SCHED_RUNNING) {
   85BA A1 02         [ 2]  956 	cmp	#0x02
   85BC 26 20         [ 3]  957 	bne	00107$
                            958 ;scheduler.c:158: schedule->status = SCHED_OFF;
   85BE 9E E6 11      [ 4]  959 	lda	17,s
   85C1 87            [ 2]  960 	psha
   85C2 8A            [ 2]  961 	pulh
   85C3 9E EE 12      [ 4]  962 	ldx	18,s
   85C6 4F            [ 1]  963 	clra
   85C7 F7            [ 2]  964 	sta	,x
                            965 ;scheduler.c:159: if (schedule->channel == 1) { endCoil1Charge(); } else { endCoil2Charge(); }
   85C8 9E E6 13      [ 4]  966 	lda	19,s
   85CB 87            [ 2]  967 	psha
   85CC 8A            [ 2]  968 	pulh
   85CD 9E EE 14      [ 4]  969 	ldx	20,s
   85D0 E6 07         [ 3]  970 	lda	7,x
   85D2 A1 01         [ 2]  971 	cmp	#0x01
   85D4 26 05         [ 3]  972 	bne	00104$
   85D6 CD 81 61      [ 5]  973 	jsr	_endCoil1Charge
   85D9 20 03         [ 3]  974 	bra	00107$
   85DB                     975 00104$:
   85DB CD 81 6F      [ 5]  976 	jsr	_endCoil2Charge
   85DE                     977 00107$:
                            978 ;scheduler.c:162: startTicks = US_TO_TIMER1(startTime);
   85DE 95            [ 2]  979 	tsx
   85DF E6 23         [ 3]  980 	lda	35,x
   85E1 EE 22         [ 3]  981 	ldx	34,x
   85E3 54            [ 1]  982 	lsrx
   85E4 46            [ 1]  983 	rora
   85E5 54            [ 1]  984 	lsrx
   85E6 46            [ 1]  985 	rora
   85E7 54            [ 1]  986 	lsrx
   85E8 46            [ 1]  987 	rora
   85E9 9E E7 10      [ 4]  988 	sta	16,s
   85EC 9E EF 0F      [ 4]  989 	stx	15,s
   85EF 9E E6 22      [ 4]  990 	lda	34,s
   85F2 62            [ 3]  991 	nsa	
   85F3 A4 F0         [ 2]  992 	and	#0xf0
   85F5 48            [ 1]  993 	lsla	
   85F6 9E EA 0F      [ 4]  994 	ora	15,s
   85F9 9E E7 0F      [ 4]  995 	sta	15,s
   85FC 9E E6 22      [ 4]  996 	lda	34,s
   85FF 9E EE 21      [ 4]  997 	ldx	33,s
   8602 54            [ 1]  998 	lsrx
   8603 46            [ 1]  999 	rora
   8604 54            [ 1] 1000 	lsrx
   8605 46            [ 1] 1001 	rora
   8606 54            [ 1] 1002 	lsrx
   8607 46            [ 1] 1003 	rora
   8608 9E E7 0E      [ 4] 1004 	sta	14,s
   860B 9E EF 0D      [ 4] 1005 	stx	13,s
   860E 9E EE 10      [ 4] 1006 	ldx	16,s
   8611 9E E6 0F      [ 4] 1007 	lda	15,s
   8614 87            [ 2] 1008 	psha
   8615 8A            [ 2] 1009 	pulh
   8616 9E EF 10      [ 4] 1010 	stx	16,s
   8619 8B            [ 2] 1011 	pshh
   861A 86            [ 2] 1012 	pula
   861B 9E E7 0F      [ 4] 1013 	sta	15,s
   861E 4F            [ 1] 1014 	clra
   861F 9E E7 0E      [ 4] 1015 	sta	14,s
   8622 9E E7 0D      [ 4] 1016 	sta	13,s
   8625 95            [ 2] 1017 	tsx
   8626 E6 0C         [ 3] 1018 	lda	12,x
   8628 E7 04         [ 3] 1019 	sta	4,x
   862A E6 0D         [ 3] 1020 	lda	13,x
   862C E7 05         [ 3] 1021 	sta	5,x
   862E E6 0E         [ 3] 1022 	lda	14,x
   8630 E7 06         [ 3] 1023 	sta	6,x
   8632 E6 0F         [ 3] 1024 	lda	15,x
   8634 E7 07         [ 3] 1025 	sta	7,x
                           1026 ;scheduler.c:163: durationTicks = US_TO_TIMER1(duration);
   8636 E6 25         [ 3] 1027 	lda	37,x
   8638 EE 24         [ 3] 1028 	ldx	36,x
   863A 54            [ 1] 1029 	lsrx
   863B 46            [ 1] 1030 	rora
   863C 54            [ 1] 1031 	lsrx
   863D 46            [ 1] 1032 	rora
   863E 54            [ 1] 1033 	lsrx
   863F 46            [ 1] 1034 	rora
   8640 9E E7 18      [ 4] 1035 	sta	24,s
   8643 9E EF 17      [ 4] 1036 	stx	23,s
   8646 87            [ 2] 1037 	psha
   8647 4F            [ 1] 1038 	clra
   8648 9E E7 17      [ 4] 1039 	sta	23,s
   864B 4F            [ 1] 1040 	clra
   864C 9E E7 16      [ 4] 1041 	sta	22,s
   864F 86            [ 2] 1042 	pula
   8650 95            [ 2] 1043 	tsx
   8651 E6 14         [ 3] 1044 	lda	20,x
   8653 F7            [ 2] 1045 	sta	,x
   8654 E6 15         [ 3] 1046 	lda	21,x
   8656 E7 01         [ 3] 1047 	sta	1,x
   8658 E6 16         [ 3] 1048 	lda	22,x
   865A E7 02         [ 3] 1049 	sta	2,x
   865C E6 17         [ 3] 1050 	lda	23,x
   865E E7 03         [ 3] 1051 	sta	3,x
                           1052 ;scheduler.c:164: if (durationTicks == 0) { durationTicks = 1; }
   8660 E6 14         [ 3] 1053 	lda	20,x
   8662 EA 15         [ 3] 1054 	ora	21,x
   8664 EA 16         [ 3] 1055 	ora	22,x
   8666 EA 17         [ 3] 1056 	ora	23,x
   8668 26 09         [ 3] 1057 	bne	00109$
   866A 4F            [ 1] 1058 	clra
   866B F7            [ 2] 1059 	sta	,x
   866C E7 01         [ 3] 1060 	sta	1,x
   866E E7 02         [ 3] 1061 	sta	2,x
   8670 4C            [ 1] 1062 	inca
   8671 E7 03         [ 3] 1063 	sta	3,x
   8673                    1064 00109$:
                           1065 ;scheduler.c:166: totalTicks = startTicks + durationTicks;
   8673 95            [ 2] 1066 	tsx
   8674 E6 0F         [ 3] 1067 	lda	15,x
   8676 EB 03         [ 3] 1068 	add	3,x
   8678 E7 17         [ 3] 1069 	sta	23,x
   867A E6 0E         [ 3] 1070 	lda	14,x
   867C E9 02         [ 3] 1071 	adc	2,x
   867E E7 16         [ 3] 1072 	sta	22,x
   8680 E6 0D         [ 3] 1073 	lda	13,x
   8682 E9 01         [ 3] 1074 	adc	1,x
   8684 E7 15         [ 3] 1075 	sta	21,x
   8686 E6 0C         [ 3] 1076 	lda	12,x
   8688 F9            [ 2] 1077 	adc	,x
   8689 E7 14         [ 3] 1078 	sta	20,x
                           1079 ;scheduler.c:167: minTicks = US_TO_TIMER1(IGNITION_MIN_DELAY_US);
   868B C6 D2 53      [ 4] 1080 	lda	(_IGNITION_MIN_DELAY_US + 1)
   868E CE D2 52      [ 4] 1081 	ldx	_IGNITION_MIN_DELAY_US
   8691 54            [ 1] 1082 	lsrx
   8692 46            [ 1] 1083 	rora
   8693 54            [ 1] 1084 	lsrx
   8694 46            [ 1] 1085 	rora
   8695 54            [ 1] 1086 	lsrx
   8696 46            [ 1] 1087 	rora
   8697 9E E7 0C      [ 4] 1088 	sta	12,s
   869A 9E EF 0B      [ 4] 1089 	stx	11,s
   869D 87            [ 2] 1090 	psha
   869E 4F            [ 1] 1091 	clra
   869F 9E E7 0B      [ 4] 1092 	sta	11,s
   86A2 4F            [ 1] 1093 	clra
   86A3 9E E7 0A      [ 4] 1094 	sta	10,s
   86A6 86            [ 2] 1095 	pula
                           1096 ;scheduler.c:169: if (startTicks < minTicks) {
   86A7 95            [ 2] 1097 	tsx
   86A8 E6 0F         [ 3] 1098 	lda	15,x
   86AA E0 0B         [ 3] 1099 	sub	11,x
   86AC E6 0E         [ 3] 1100 	lda	14,x
   86AE E2 0A         [ 3] 1101 	sbc	10,x
   86B0 E6 0D         [ 3] 1102 	lda	13,x
   86B2 E2 09         [ 3] 1103 	sbc	9,x
   86B4 E6 0C         [ 3] 1104 	lda	12,x
   86B6 E2 08         [ 3] 1105 	sbc	8,x
   86B8 24 45         [ 3] 1106 	bcc	00114$
                           1107 ;scheduler.c:170: startTicks = minTicks;
   86BA E6 08         [ 3] 1108 	lda	8,x
   86BC E7 04         [ 3] 1109 	sta	4,x
   86BE E6 09         [ 3] 1110 	lda	9,x
   86C0 E7 05         [ 3] 1111 	sta	5,x
   86C2 E6 0A         [ 3] 1112 	lda	10,x
   86C4 E7 06         [ 3] 1113 	sta	6,x
   86C6 E6 0B         [ 3] 1114 	lda	11,x
   86C8 E7 07         [ 3] 1115 	sta	7,x
                           1116 ;scheduler.c:171: if (totalTicks > startTicks) {
   86CA E6 0B         [ 3] 1117 	lda	11,x
   86CC E0 17         [ 3] 1118 	sub	23,x
   86CE E6 0A         [ 3] 1119 	lda	10,x
   86D0 E2 16         [ 3] 1120 	sbc	22,x
   86D2 E6 09         [ 3] 1121 	lda	9,x
   86D4 E2 15         [ 3] 1122 	sbc	21,x
   86D6 E6 08         [ 3] 1123 	lda	8,x
   86D8 E2 14         [ 3] 1124 	sbc	20,x
   86DA 24 19         [ 3] 1125 	bcc	00111$
                           1126 ;scheduler.c:172: durationTicks = totalTicks - startTicks;
   86DC E6 17         [ 3] 1127 	lda	23,x
   86DE E0 0B         [ 3] 1128 	sub	11,x
   86E0 E7 03         [ 3] 1129 	sta	3,x
   86E2 E6 16         [ 3] 1130 	lda	22,x
   86E4 E2 0A         [ 3] 1131 	sbc	10,x
   86E6 E7 02         [ 3] 1132 	sta	2,x
   86E8 E6 15         [ 3] 1133 	lda	21,x
   86EA E2 09         [ 3] 1134 	sbc	9,x
   86EC E7 01         [ 3] 1135 	sta	1,x
   86EE E6 14         [ 3] 1136 	lda	20,x
   86F0 E2 08         [ 3] 1137 	sbc	8,x
   86F2 F7            [ 2] 1138 	sta	,x
   86F3 20 0A         [ 3] 1139 	bra	00114$
   86F5                    1140 00111$:
                           1141 ;scheduler.c:174: durationTicks = 1;
   86F5 95            [ 2] 1142 	tsx
   86F6 4F            [ 1] 1143 	clra
   86F7 F7            [ 2] 1144 	sta	,x
   86F8 E7 01         [ 3] 1145 	sta	1,x
   86FA E7 02         [ 3] 1146 	sta	2,x
   86FC 4C            [ 1] 1147 	inca
   86FD E7 03         [ 3] 1148 	sta	3,x
   86FF                    1149 00114$:
                           1150 ;scheduler.h:56: return (uint16_t)((T1CNTH << 8) | T1CNTL);
   86FF B6 21         [ 3] 1151 	lda	*0x21
   8701 5F            [ 1] 1152 	clrx
   8702 9E E7 09      [ 4] 1153 	sta	9,s
   8705 9E EF 0A      [ 4] 1154 	stx	10,s
   8708 B6 22         [ 3] 1155 	lda	*0x22
   870A 9E EA 0A      [ 4] 1156 	ora	10,s
   870D 87            [ 2] 1157 	psha
   870E 9F            [ 1] 1158 	txa
   870F 9E EA 0A      [ 4] 1159 	ora	10,s
   8712 97            [ 1] 1160 	tax
   8713 86            [ 2] 1161 	pula
   8714 9E E7 1A      [ 4] 1162 	sta	26,s
   8717 9E EF 19      [ 4] 1163 	stx	25,s
                           1164 ;scheduler.c:179: startTicks16 = (uint16_t)startTicks;
   871A 9E EE 08      [ 4] 1165 	ldx	8,s
   871D 9E E6 07      [ 4] 1166 	lda	7,s
   8720 87            [ 2] 1167 	psha
   8721 8A            [ 2] 1168 	pulh
                           1169 ;scheduler.c:180: durationTicks16 = (uint16_t)durationTicks;
   8722 9E E6 04      [ 4] 1170 	lda	4,s
   8725 9E E7 1E      [ 4] 1171 	sta	30,s
   8728 9E E6 03      [ 4] 1172 	lda	3,s
   872B 9E E7 1D      [ 4] 1173 	sta	29,s
                           1174 ;scheduler.c:182: schedule->startCompare = currentCount + startTicks16;
   872E 9E E6 11      [ 4] 1175 	lda	17,s
   8731 9E E7 09      [ 4] 1176 	sta	9,s
   8734 9E E6 12      [ 4] 1177 	lda	18,s
   8737 9E E7 0A      [ 4] 1178 	sta	10,s
   873A 9F            [ 1] 1179 	txa
   873B 9E EB 1A      [ 4] 1180 	add	26,s
   873E 97            [ 1] 1181 	tax
   873F 8B            [ 2] 1182 	pshh
   8740 86            [ 2] 1183 	pula
   8741 9E E9 19      [ 4] 1184 	adc	25,s
   8744 89            [ 2] 1185 	pshx
   8745 87            [ 2] 1186 	psha
   8746 89            [ 2] 1187 	pshx
   8747 9E E6 0C      [ 4] 1188 	lda	12,s
   874A 87            [ 2] 1189 	psha
   874B 8A            [ 2] 1190 	pulh
   874C 9E EE 0D      [ 4] 1191 	ldx	13,s
   874F E7 01         [ 3] 1192 	sta	1,x
   8751 86            [ 2] 1193 	pula
   8752 E7 02         [ 3] 1194 	sta	2,x
   8754 86            [ 2] 1195 	pula
   8755 88            [ 2] 1196 	pulx
                           1197 ;scheduler.c:183: schedule->endCompare = schedule->startCompare + durationTicks16;
   8756 87            [ 2] 1198 	psha
   8757 9E E6 12      [ 4] 1199 	lda	18,s
   875A 9E E7 16      [ 4] 1200 	sta	22,s
   875D 9E E6 13      [ 4] 1201 	lda	19,s
   8760 9E E7 17      [ 4] 1202 	sta	23,s
   8763 86            [ 2] 1203 	pula
   8764 89            [ 2] 1204 	pshx
   8765 9E EE 0A      [ 4] 1205 	ldx	10,s
   8768 89            [ 2] 1206 	pshx
   8769 8A            [ 2] 1207 	pulh
   876A 9E EE 0B      [ 4] 1208 	ldx	11,s
   876D 87            [ 2] 1209 	psha
   876E E6 01         [ 3] 1210 	lda	1,x
   8770 E6 02         [ 3] 1211 	lda	2,x
   8772 86            [ 2] 1212 	pula
   8773 88            [ 2] 1213 	pulx
   8774 87            [ 2] 1214 	psha
   8775 9F            [ 1] 1215 	txa
   8776 9E EB 1F      [ 4] 1216 	add	31,s
   8779 97            [ 1] 1217 	tax
   877A 86            [ 2] 1218 	pula
   877B 9E E9 1D      [ 4] 1219 	adc	29,s
   877E 89            [ 2] 1220 	pshx
   877F 9E EE 16      [ 4] 1221 	ldx	22,s
   8782 89            [ 2] 1222 	pshx
   8783 8A            [ 2] 1223 	pulh
   8784 9E EE 17      [ 4] 1224 	ldx	23,s
   8787 E7 03         [ 3] 1225 	sta	3,x
   8789 86            [ 2] 1226 	pula
   878A E7 04         [ 3] 1227 	sta	4,x
                           1228 ;scheduler.c:184: schedule->duration = durationTicks16;
   878C 95            [ 2] 1229 	tsx
   878D E6 10         [ 3] 1230 	lda	16,x
   878F E7 08         [ 3] 1231 	sta	8,x
   8791 E6 11         [ 3] 1232 	lda	17,x
   8793 E7 09         [ 3] 1233 	sta	9,x
   8795 E6 08         [ 3] 1234 	lda	8,x
   8797 87            [ 2] 1235 	psha
   8798 8A            [ 2] 1236 	pulh
   8799 9E EE 0A      [ 4] 1237 	ldx	10,s
   879C 9E E6 1D      [ 4] 1238 	lda	29,s
   879F E7 05         [ 3] 1239 	sta	5,x
   87A1 9E E6 1E      [ 4] 1240 	lda	30,s
   87A4 E7 06         [ 3] 1241 	sta	6,x
                           1242 ;scheduler.c:185: schedule->channel = channel;
   87A6 9E E6 13      [ 4] 1243 	lda	19,s
   87A9 87            [ 2] 1244 	psha
   87AA 8A            [ 2] 1245 	pulh
   87AB 9E EE 14      [ 4] 1246 	ldx	20,s
   87AE 9E E6 27      [ 4] 1247 	lda	39,s
   87B1 E7 07         [ 3] 1248 	sta	7,x
                           1249 ;scheduler.c:186: schedule->status = SCHED_PENDING;
   87B3 9E E6 11      [ 4] 1250 	lda	17,s
   87B6 87            [ 2] 1251 	psha
   87B7 8A            [ 2] 1252 	pulh
   87B8 9E EE 12      [ 4] 1253 	ldx	18,s
   87BB A6 01         [ 2] 1254 	lda	#0x01
   87BD F7            [ 2] 1255 	sta	,x
                           1256 ;scheduler.c:188: if (channel == 1) {
   87BE 9E E6 27      [ 4] 1257 	lda	39,s
   87C1 A1 01         [ 2] 1258 	cmp	#0x01
   87C3 26 1D         [ 3] 1259 	bne	00116$
                           1260 ;scheduler.c:189: armIgnitionCompare(schedule, beginCoil1Charge, endCoil1Charge, (volatile uint16_t *)&T1CH0H);
   87C5 A6 26         [ 2] 1261 	lda	#0x26
   87C7 87            [ 2] 1262 	psha
   87C8 4F            [ 1] 1263 	clra
   87C9 87            [ 2] 1264 	psha
   87CA A6 61         [ 2] 1265 	lda	#_endCoil1Charge
   87CC 87            [ 2] 1266 	psha
   87CD A6 81         [ 2] 1267 	lda	#>_endCoil1Charge
   87CF 87            [ 2] 1268 	psha
   87D0 A6 5A         [ 2] 1269 	lda	#_beginCoil1Charge
   87D2 87            [ 2] 1270 	psha
   87D3 A6 81         [ 2] 1271 	lda	#>_beginCoil1Charge
   87D5 87            [ 2] 1272 	psha
   87D6 95            [ 2] 1273 	tsx
   87D7 E6 17         [ 3] 1274 	lda	23,x
   87D9 EE 16         [ 3] 1275 	ldx	22,x
   87DB CD 84 F2      [ 5] 1276 	jsr	_armIgnitionCompare
   87DE A7 06         [ 2] 1277 	ais	#6
   87E0 20 1B         [ 3] 1278 	bra	00119$
   87E2                    1279 00116$:
                           1280 ;scheduler.c:191: armIgnitionCompare(schedule, beginCoil2Charge, endCoil2Charge, (volatile uint16_t *)&T1CH1H);
   87E2 A6 29         [ 2] 1281 	lda	#0x29
   87E4 87            [ 2] 1282 	psha
   87E5 4F            [ 1] 1283 	clra
   87E6 87            [ 2] 1284 	psha
   87E7 A6 6F         [ 2] 1285 	lda	#_endCoil2Charge
   87E9 87            [ 2] 1286 	psha
   87EA A6 81         [ 2] 1287 	lda	#>_endCoil2Charge
   87EC 87            [ 2] 1288 	psha
   87ED A6 68         [ 2] 1289 	lda	#_beginCoil2Charge
   87EF 87            [ 2] 1290 	psha
   87F0 A6 81         [ 2] 1291 	lda	#>_beginCoil2Charge
   87F2 87            [ 2] 1292 	psha
   87F3 95            [ 2] 1293 	tsx
   87F4 E6 17         [ 3] 1294 	lda	23,x
   87F6 EE 16         [ 3] 1295 	ldx	22,x
   87F8 CD 84 F2      [ 5] 1296 	jsr	_armIgnitionCompare
   87FB A7 06         [ 2] 1297 	ais	#6
   87FD                    1298 00119$:
                           1299 ;scheduler.c:193: }
   87FD A7 1E         [ 2] 1300 	ais	#30
   87FF 81            [ 4] 1301 	rts
                           1302 ;------------------------------------------------------------
                           1303 ;Allocation info for local variables in function 'clearIgnitionSchedule'
                           1304 ;------------------------------------------------------------
                           1305 ;schedule                  Allocated to stack - sp +1
                           1306 ;------------------------------------------------------------
                           1307 ;scheduler.c:195: void clearIgnitionSchedule(volatile IgnitionSchedule *schedule) {
                           1308 ;	-----------------------------------------
                           1309 ;	 function clearIgnitionSchedule
                           1310 ;	-----------------------------------------
                           1311 ;	Register assignment is optimal.
                           1312 ;	Stack space usage: 2 bytes.
   8800                    1313 _clearIgnitionSchedule:
   8800 87            [ 2] 1314 	psha
   8801 89            [ 2] 1315 	pshx
                           1316 ;scheduler.c:196: schedule->status = SCHED_OFF;
   8802 8A            [ 2] 1317 	pulh
   8803 88            [ 2] 1318 	pulx
   8804 89            [ 2] 1319 	pshx
   8805 8B            [ 2] 1320 	pshh
   8806 89            [ 2] 1321 	pshx
   8807 8B            [ 2] 1322 	pshh
   8808 4F            [ 1] 1323 	clra
   8809 F7            [ 2] 1324 	sta	,x
   880A 8A            [ 2] 1325 	pulh
   880B 88            [ 2] 1326 	pulx
                           1327 ;scheduler.c:197: if (schedule->channel == 1) {
   880C E6 07         [ 3] 1328 	lda	7,x
   880E A1 01         [ 2] 1329 	cmp	#0x01
   8810 26 05         [ 3] 1330 	bne	00104$
                           1331 ;scheduler.c:198: endCoil1Charge();
   8812 CD 81 61      [ 5] 1332 	jsr	_endCoil1Charge
   8815 20 09         [ 3] 1333 	bra	00106$
   8817                    1334 00104$:
                           1335 ;scheduler.c:199: } else if (schedule->channel == 2) {
   8817 E6 07         [ 3] 1336 	lda	7,x
   8819 A1 02         [ 2] 1337 	cmp	#0x02
   881B 26 03         [ 3] 1338 	bne	00106$
                           1339 ;scheduler.c:200: endCoil2Charge();
   881D CD 81 6F      [ 5] 1340 	jsr	_endCoil2Charge
   8820                    1341 00106$:
                           1342 ;scheduler.c:202: }
   8820 A7 02         [ 2] 1343 	ais	#2
   8822 81            [ 4] 1344 	rts
                           1345 ;------------------------------------------------------------
                           1346 ;Allocation info for local variables in function 'isr_tim1_ch0'
                           1347 ;------------------------------------------------------------
                           1348 ;scheduler.c:205: void isr_tim1_ch0(void) __interrupt(4) {
                           1349 ;	-----------------------------------------
                           1350 ;	 function isr_tim1_ch0
                           1351 ;	-----------------------------------------
                           1352 ;	Register assignment is optimal.
                           1353 ;	Stack space usage: 0 bytes.
   8823                    1354 _isr_tim1_ch0:
   8823 8B            [ 2] 1355 	pshh
                           1356 ;scheduler.c:206: handleIgnitionChannel(&ignitionSchedule1, beginCoil1Charge, endCoil1Charge, (volatile uint16_t *)&T1CH0H);
   8824 A6 26         [ 2] 1357 	lda	#0x26
   8826 87            [ 2] 1358 	psha
   8827 4F            [ 1] 1359 	clra
   8828 87            [ 2] 1360 	psha
   8829 A6 61         [ 2] 1361 	lda	#_endCoil1Charge
   882B 87            [ 2] 1362 	psha
   882C A6 81         [ 2] 1363 	lda	#>_endCoil1Charge
   882E 87            [ 2] 1364 	psha
   882F A6 5A         [ 2] 1365 	lda	#_beginCoil1Charge
   8831 87            [ 2] 1366 	psha
   8832 A6 81         [ 2] 1367 	lda	#>_beginCoil1Charge
   8834 87            [ 2] 1368 	psha
   8835 A6 C3         [ 2] 1369 	lda	#_ignitionSchedule1
   8837 AE 01         [ 2] 1370 	ldx	#>_ignitionSchedule1
   8839 CD 84 1D      [ 5] 1371 	jsr	_handleIgnitionChannel
   883C A7 06         [ 2] 1372 	ais	#6
                           1373 ;scheduler.c:207: }
   883E 8A            [ 2] 1374 	pulh
   883F 80            [ 7] 1375 	rti
                           1376 ;------------------------------------------------------------
                           1377 ;Allocation info for local variables in function 'isr_tim1_ch1'
                           1378 ;------------------------------------------------------------
                           1379 ;scheduler.c:209: void isr_tim1_ch1(void) __interrupt(5) {
                           1380 ;	-----------------------------------------
                           1381 ;	 function isr_tim1_ch1
                           1382 ;	-----------------------------------------
                           1383 ;	Register assignment is optimal.
                           1384 ;	Stack space usage: 0 bytes.
   8840                    1385 _isr_tim1_ch1:
   8840 8B            [ 2] 1386 	pshh
                           1387 ;scheduler.c:210: handleIgnitionChannel(&ignitionSchedule2, beginCoil2Charge, endCoil2Charge, (volatile uint16_t *)&T1CH1H);
   8841 A6 29         [ 2] 1388 	lda	#0x29
   8843 87            [ 2] 1389 	psha
   8844 4F            [ 1] 1390 	clra
   8845 87            [ 2] 1391 	psha
   8846 A6 6F         [ 2] 1392 	lda	#_endCoil2Charge
   8848 87            [ 2] 1393 	psha
   8849 A6 81         [ 2] 1394 	lda	#>_endCoil2Charge
   884B 87            [ 2] 1395 	psha
   884C A6 68         [ 2] 1396 	lda	#_beginCoil2Charge
   884E 87            [ 2] 1397 	psha
   884F A6 81         [ 2] 1398 	lda	#>_beginCoil2Charge
   8851 87            [ 2] 1399 	psha
   8852 A6 CB         [ 2] 1400 	lda	#_ignitionSchedule2
   8854 AE 01         [ 2] 1401 	ldx	#>_ignitionSchedule2
   8856 CD 84 1D      [ 5] 1402 	jsr	_handleIgnitionChannel
   8859 A7 06         [ 2] 1403 	ais	#6
                           1404 ;scheduler.c:211: }
   885B 8A            [ 2] 1405 	pulh
   885C 80            [ 7] 1406 	rti
                           1407 	.area CSEG    (CODE)
                           1408 	.area CONST   (CODE)
   D252                    1409 _IGNITION_MIN_DELAY_US:
   D252 00 19              1410 	.dw #0x0019
                           1411 	.area XINIT   (CODE)
   D23B                    1412 __xinit__ignitionSchedule1:
   D23B 00                 1413 	.db #0x00	; 0
   D23C 00 00              1414 	.dw #0x0000
   D23E 00 00              1415 	.dw #0x0000
   D240 00 00              1416 	.dw #0x0000
   D242 01                 1417 	.db #0x01	; 1
   D243                    1418 __xinit__ignitionSchedule2:
   D243 00                 1419 	.db #0x00	; 0
   D244 00 00              1420 	.dw #0x0000
   D246 00 00              1421 	.dw #0x0000
   D248 00 00              1422 	.dw #0x0000
   D24A 02                 1423 	.db #0x02	; 2
                           1424 	.area CABS    (ABS,CODE)
