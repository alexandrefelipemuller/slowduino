                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 4.2.0 #13081 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module ignition
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
                             22 	.globl _lookupCurveI8
                             23 	.globl _getTableValue
                             24 	.globl _calculateAdvance
                             25 	.globl _getBaseAdvance
                             26 	.globl _applyAdvanceCorrections
                             27 	.globl _isIdleAdvanceActive
                             28 	.globl _correctionCLTAdvance
                             29 	.globl _correctionIdleAdvance
                             30 	.globl _applyRevLimiter
                             31 	.globl _calculateDwell
                             32 ;--------------------------------------------------------
                             33 ; ram data
                             34 ;--------------------------------------------------------
                             35 	.area DSEG    (PAG)
                             36 ;--------------------------------------------------------
                             37 ; overlayable items in ram
                             38 ;--------------------------------------------------------
                             39 ;--------------------------------------------------------
                             40 ; absolute ram data
                             41 ;--------------------------------------------------------
                             42 	.area IABS    (ABS)
                             43 	.area IABS    (ABS)
                             44 ;--------------------------------------------------------
                             45 ; absolute external ram data
                             46 ;--------------------------------------------------------
                             47 	.area XABS    (ABS)
                             48 ;--------------------------------------------------------
                             49 ; external initialized ram data
                             50 ;--------------------------------------------------------
                             51 	.area XISEG
                             52 ;--------------------------------------------------------
                             53 ; extended address mode data
                             54 ;--------------------------------------------------------
                             55 	.area XSEG
   0176                      56 _applyRevLimiter_cutState_131072_43:
   0176                      57 	.ds 1
                             58 ;--------------------------------------------------------
                             59 ; global & static initialisations
                             60 ;--------------------------------------------------------
                             61 	.area HOME    (CODE)
                             62 	.area GSINIT  (CODE)
                             63 	.area GSFINAL (CODE)
                             64 	.area GSINIT  (CODE)
                             65 ;------------------------------------------------------------
                             66 ;Allocation info for local variables in function 'applyRevLimiter'
                             67 ;------------------------------------------------------------
                             68 ;advance                   Allocated to registers h 
                             69 ;limitRPM                  Allocated to stack - sp +0
                             70 ;cutState                  Allocated with name '_applyRevLimiter_cutState_131072_43'
                             71 ;------------------------------------------------------------
                             72 ;ignition.c:91: static bool cutState = false;
   8023 4F            [ 1]   73 	clra
   8024 C7 01 76      [ 4]   74 	sta	_applyRevLimiter_cutState_131072_43
                             75 ;--------------------------------------------------------
                             76 ; Home
                             77 ;--------------------------------------------------------
                             78 	.area HOME    (CODE)
                             79 	.area HOME    (CODE)
                             80 ;--------------------------------------------------------
                             81 ; code
                             82 ;--------------------------------------------------------
                             83 	.area CSEG    (CODE)
                             84 ;------------------------------------------------------------
                             85 ;Allocation info for local variables in function 'noInterrupts'
                             86 ;------------------------------------------------------------
                             87 ;globals.h:100: static inline void noInterrupts(void) { __asm sei __endasm; }
                             88 ;	-----------------------------------------
                             89 ;	 function noInterrupts
                             90 ;	-----------------------------------------
                             91 ;	Register assignment is optimal.
                             92 ;	Stack space usage: 0 bytes.
   AEA3                      93 _noInterrupts:
   AEA3 9B            [ 2]   94 	 sei	
   AEA4 81            [ 4]   95 	rts
                             96 ;------------------------------------------------------------
                             97 ;Allocation info for local variables in function 'interrupts'
                             98 ;------------------------------------------------------------
                             99 ;globals.h:101: static inline void interrupts(void)   { __asm cli __endasm; }
                            100 ;	-----------------------------------------
                            101 ;	 function interrupts
                            102 ;	-----------------------------------------
                            103 ;	Register assignment is optimal.
                            104 ;	Stack space usage: 0 bytes.
   AEA5                     105 _interrupts:
   AEA5 9A            [ 2]  106 	 cli	
   AEA6 81            [ 4]  107 	rts
                            108 ;------------------------------------------------------------
                            109 ;Allocation info for local variables in function 'interpolate'
                            110 ;------------------------------------------------------------
                            111 ;x1                        Allocated to stack - sp +11
                            112 ;x2                        Allocated to stack - sp +13
                            113 ;y1                        Allocated to stack - sp +15
                            114 ;y2                        Allocated to stack - sp +17
                            115 ;x                         Allocated to registers a x 
                            116 ;sloc0                     Allocated to stack - sp +5
                            117 ;sloc1                     Allocated to stack - sp +1
                            118 ;------------------------------------------------------------
                            119 ;tables.h:33: static inline int16_t interpolate(int16_t x, int16_t x1, int16_t x2, int16_t y1, int16_t y2) {
                            120 ;	-----------------------------------------
                            121 ;	 function interpolate
                            122 ;	-----------------------------------------
                            123 ;	Register assignment might be sub-optimal.
                            124 ;	Stack space usage: 8 bytes.
   AEA7                     125 _interpolate:
   AEA7 A7 F8         [ 2]  126 	ais	#-8
                            127 ;tables.h:34: if (x2 == x1) return y1;
   AEA9 87            [ 2]  128 	psha
   AEAA 9E E6 0F      [ 4]  129 	lda	15,s
   AEAD 9E E1 0D      [ 4]  130 	cmp	13,s
   AEB0 86            [ 2]  131 	pula
   AEB1 26 0A         [ 3]  132 	bne	00110$
   AEB3 87            [ 2]  133 	psha
   AEB4 9E E6 0E      [ 4]  134 	lda	14,s
   AEB7 9E E1 0C      [ 4]  135 	cmp	12,s
   AEBA 86            [ 2]  136 	pula
   AEBB 27 02         [ 3]  137 	beq	00111$
   AEBD                     138 00110$:
   AEBD 20 09         [ 3]  139 	bra	00102$
   AEBF                     140 00111$:
   AEBF 95            [ 2]  141 	tsx
   AEC0 EE 0E         [ 3]  142 	ldx	14,x
   AEC2 9E E6 10      [ 4]  143 	lda	16,s
   AEC5 CC AF 8D      [ 3]  144 	jmp	00103$
   AEC8                     145 00102$:
                            146 ;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
   AEC8 9E E0 0C      [ 4]  147 	sub	12,s
   AECB 87            [ 2]  148 	psha
   AECC 9F            [ 1]  149 	txa
   AECD 9E E2 0C      [ 4]  150 	sbc	12,s
   AED0 97            [ 1]  151 	tax
   AED1 86            [ 2]  152 	pula
   AED2 9E E7 08      [ 4]  153 	sta	8,s
   AED5 9F            [ 1]  154 	txa
   AED6 9E E7 07      [ 4]  155 	sta	7,s
   AED9 49            [ 1]  156 	rola	
   AEDA 4F            [ 1]  157 	clra	
   AEDB A2 00         [ 2]  158 	sbc	#0x00
   AEDD 9E E7 06      [ 4]  159 	sta	6,s
   AEE0 9E E7 05      [ 4]  160 	sta	5,s
   AEE3 9E E6 12      [ 4]  161 	lda	18,s
   AEE6 9E E0 10      [ 4]  162 	sub	16,s
   AEE9 87            [ 2]  163 	psha
   AEEA 9E E6 12      [ 4]  164 	lda	18,s
   AEED 9E E2 10      [ 4]  165 	sbc	16,s
   AEF0 97            [ 1]  166 	tax
   AEF1 86            [ 2]  167 	pula
   AEF2 9E E7 04      [ 4]  168 	sta	4,s
   AEF5 9F            [ 1]  169 	txa
   AEF6 9E E7 03      [ 4]  170 	sta	3,s
   AEF9 49            [ 1]  171 	rola	
   AEFA 4F            [ 1]  172 	clra	
   AEFB A2 00         [ 2]  173 	sbc	#0x00
   AEFD 9E E7 02      [ 4]  174 	sta	2,s
   AF00 9E E7 01      [ 4]  175 	sta	1,s
   AF03 95            [ 2]  176 	tsx
   AF04 E6 03         [ 3]  177 	lda	3,x
   AF06 87            [ 2]  178 	psha
   AF07 E6 02         [ 3]  179 	lda	2,x
   AF09 87            [ 2]  180 	psha
   AF0A E6 01         [ 3]  181 	lda	1,x
   AF0C 87            [ 2]  182 	psha
   AF0D F6            [ 2]  183 	lda	,x
   AF0E 87            [ 2]  184 	psha
   AF0F E6 07         [ 3]  185 	lda	7,x
   AF11 87            [ 2]  186 	psha
   AF12 E6 06         [ 3]  187 	lda	6,x
   AF14 87            [ 2]  188 	psha
   AF15 E6 05         [ 3]  189 	lda	5,x
   AF17 87            [ 2]  190 	psha
   AF18 E6 04         [ 3]  191 	lda	4,x
   AF1A 87            [ 2]  192 	psha
   AF1B CD D0 87      [ 5]  193 	jsr	__mullong
   AF1E 9E E7 0C      [ 4]  194 	sta	12,s
   AF21 9E EF 0B      [ 4]  195 	stx	11,s
   AF24 B6 4A         [ 3]  196 	lda	*___SDCC_hc08_ret2
   AF26 9E E7 0A      [ 4]  197 	sta	10,s
   AF29 B6 4B         [ 3]  198 	lda	*___SDCC_hc08_ret3
   AF2B 9E E7 09      [ 4]  199 	sta	9,s
   AF2E A7 08         [ 2]  200 	ais	#8
   AF30 9E E6 0E      [ 4]  201 	lda	14,s
   AF33 9E E0 0C      [ 4]  202 	sub	12,s
   AF36 87            [ 2]  203 	psha
   AF37 9E E6 0E      [ 4]  204 	lda	14,s
   AF3A 9E E2 0C      [ 4]  205 	sbc	12,s
   AF3D 97            [ 1]  206 	tax
   AF3E 86            [ 2]  207 	pula
   AF3F 9E E7 08      [ 4]  208 	sta	8,s
   AF42 9F            [ 1]  209 	txa
   AF43 9E E7 07      [ 4]  210 	sta	7,s
   AF46 49            [ 1]  211 	rola	
   AF47 4F            [ 1]  212 	clra	
   AF48 A2 00         [ 2]  213 	sbc	#0x00
   AF4A 9E E7 06      [ 4]  214 	sta	6,s
   AF4D 9E E7 05      [ 4]  215 	sta	5,s
   AF50 95            [ 2]  216 	tsx
   AF51 E6 07         [ 3]  217 	lda	7,x
   AF53 87            [ 2]  218 	psha
   AF54 E6 06         [ 3]  219 	lda	6,x
   AF56 87            [ 2]  220 	psha
   AF57 E6 05         [ 3]  221 	lda	5,x
   AF59 87            [ 2]  222 	psha
   AF5A E6 04         [ 3]  223 	lda	4,x
   AF5C 87            [ 2]  224 	psha
   AF5D E6 03         [ 3]  225 	lda	3,x
   AF5F 87            [ 2]  226 	psha
   AF60 E6 02         [ 3]  227 	lda	2,x
   AF62 87            [ 2]  228 	psha
   AF63 E6 01         [ 3]  229 	lda	1,x
   AF65 87            [ 2]  230 	psha
   AF66 F6            [ 2]  231 	lda	,x
   AF67 87            [ 2]  232 	psha
   AF68 CD CE 92      [ 5]  233 	jsr	__divslong
   AF6B 9E E7 0C      [ 4]  234 	sta	12,s
   AF6E 9E EF 0B      [ 4]  235 	stx	11,s
   AF71 B6 4A         [ 3]  236 	lda	*___SDCC_hc08_ret2
   AF73 9E E7 0A      [ 4]  237 	sta	10,s
   AF76 B6 4B         [ 3]  238 	lda	*___SDCC_hc08_ret3
   AF78 9E E7 09      [ 4]  239 	sta	9,s
   AF7B A7 08         [ 2]  240 	ais	#8
   AF7D 9E E6 04      [ 4]  241 	lda	4,s
   AF80 9E EE 03      [ 4]  242 	ldx	3,s
   AF83 9E EB 10      [ 4]  243 	add	16,s
   AF86 87            [ 2]  244 	psha
   AF87 9F            [ 1]  245 	txa
   AF88 9E E9 10      [ 4]  246 	adc	16,s
   AF8B 97            [ 1]  247 	tax
   AF8C 86            [ 2]  248 	pula
   AF8D                     249 00103$:
                            250 ;tables.h:36: }
   AF8D A7 08         [ 2]  251 	ais	#8
   AF8F 81            [ 4]  252 	rts
                            253 ;------------------------------------------------------------
                            254 ;Allocation info for local variables in function 'calculateAdvance'
                            255 ;------------------------------------------------------------
                            256 ;advance                   Allocated to registers a 
                            257 ;------------------------------------------------------------
                            258 ;ignition.c:11: int8_t calculateAdvance(void) {
                            259 ;	-----------------------------------------
                            260 ;	 function calculateAdvance
                            261 ;	-----------------------------------------
                            262 ;	Register assignment is optimal.
                            263 ;	Stack space usage: 0 bytes.
   AF90                     264 _calculateAdvance:
                            265 ;ignition.c:14: if (BIT_CHECK(currentStatus.engineStatus, ENGINE_CRANK)) {
   AF90 C6 00 89      [ 4]  266 	lda	(_currentStatus + 0x002a)
   AF93 A5 01         [ 2]  267 	bit	#0x01
   AF95 27 04         [ 3]  268 	beq	00102$
                            269 ;ignition.c:15: return configPage2.crankAdvance;
   AF97 C6 00 C3      [ 4]  270 	lda	(_configPage2 + 0x0009)
   AF9A 81            [ 4]  271 	rts
   AF9B                     272 00102$:
                            273 ;ignition.c:18: advance = getBaseAdvance();
   AF9B CD AF B1      [ 5]  274 	jsr	_getBaseAdvance
                            275 ;ignition.c:19: advance = applyAdvanceCorrections(advance);
   AF9E CD AF C9      [ 5]  276 	jsr	_applyAdvanceCorrections
                            277 ;ignition.c:20: advance = applyRevLimiter(advance);
   AFA1 CD B2 02      [ 5]  278 	jsr	_applyRevLimiter
                            279 ;ignition.c:22: if (advance < IGN_MIN_ADVANCE) advance = IGN_MIN_ADVANCE;
   AFA4 A1 F6         [ 2]  280 	cmp	#0xf6
   AFA6 90 02         [ 3]  281 	bge	00104$
   AFA8 A6 F6         [ 2]  282 	lda	#0xf6
   AFAA                     283 00104$:
                            284 ;ignition.c:23: if (advance > IGN_MAX_ADVANCE) advance = IGN_MAX_ADVANCE;
   AFAA A1 2D         [ 2]  285 	cmp	#0x2d
   AFAC 93 02         [ 3]  286 	ble	00106$
   AFAE A6 2D         [ 2]  287 	lda	#0x2d
   AFB0                     288 00106$:
                            289 ;ignition.c:25: return advance;
                            290 ;ignition.c:26: }
   AFB0 81            [ 4]  291 	rts
                            292 ;------------------------------------------------------------
                            293 ;Allocation info for local variables in function 'getBaseAdvance'
                            294 ;------------------------------------------------------------
                            295 ;advance                   Allocated to registers a x 
                            296 ;------------------------------------------------------------
                            297 ;ignition.c:28: int8_t getBaseAdvance(void) {
                            298 ;	-----------------------------------------
                            299 ;	 function getBaseAdvance
                            300 ;	-----------------------------------------
                            301 ;	Register assignment is optimal.
                            302 ;	Stack space usage: 0 bytes.
   AFB1                     303 _getBaseAdvance:
                            304 ;ignition.c:29: int16_t advance = getTableValue(&ignTable, currentStatus.MAP, currentStatus.RPM);
   AFB1 C6 00 5F      [ 4]  305 	lda	_currentStatus
   AFB4 87            [ 2]  306 	psha
   AFB5 8A            [ 2]  307 	pulh
   AFB6 CE 00 60      [ 4]  308 	ldx	(_currentStatus + 1)
   AFB9 C6 00 72      [ 4]  309 	lda	(_currentStatus + 0x0013)
   AFBC 89            [ 2]  310 	pshx
   AFBD 8B            [ 2]  311 	pshh
   AFBE 87            [ 2]  312 	psha
   AFBF A6 4E         [ 2]  313 	lda	#_ignTable
   AFC1 AE 01         [ 2]  314 	ldx	#>_ignTable
   AFC3 CD 98 F5      [ 5]  315 	jsr	_getTableValue
   AFC6 A7 03         [ 2]  316 	ais	#3
                            317 ;ignition.c:30: return (int8_t)advance;
                            318 ;ignition.c:31: }
   AFC8 81            [ 4]  319 	rts
                            320 ;------------------------------------------------------------
                            321 ;Allocation info for local variables in function 'applyAdvanceCorrections'
                            322 ;------------------------------------------------------------
                            323 ;baseAdvance               Allocated to stack - sp +2
                            324 ;corrected                 Allocated to registers a 
                            325 ;sloc0                     Allocated to stack - sp +1
                            326 ;------------------------------------------------------------
                            327 ;ignition.c:33: int8_t applyAdvanceCorrections(int8_t baseAdvance) {
                            328 ;	-----------------------------------------
                            329 ;	 function applyAdvanceCorrections
                            330 ;	-----------------------------------------
                            331 ;	Register assignment is optimal.
                            332 ;	Stack space usage: 2 bytes.
   AFC9                     333 _applyAdvanceCorrections:
   AFC9 87            [ 2]  334 	psha
   AFCA 8B            [ 2]  335 	pshh
                            336 ;ignition.c:36: corrected = (int8_t)(corrected + correctionCLTAdvance());
   AFCB CD B0 46      [ 5]  337 	jsr	_correctionCLTAdvance
   AFCE 95            [ 2]  338 	tsx
   AFCF EB 01         [ 3]  339 	add	1,x
                            340 ;ignition.c:38: if (isIdleAdvanceActive()) {
   AFD1 87            [ 2]  341 	psha
   AFD2 CD AF F3      [ 5]  342 	jsr	_isIdleAdvanceActive
   AFD5 97            [ 1]  343 	tax
   AFD6 86            [ 2]  344 	pula
   AFD7 5D            [ 1]  345 	tstx
   AFD8 27 16         [ 3]  346 	beq	00105$
                            347 ;ignition.c:39: if (configPage2.idleAdvEnabled == IDLE_ADV_SWITCHED) {
   AFDA CE 00 CF      [ 4]  348 	ldx	(_configPage2 + 0x0015)
   AFDD A3 02         [ 2]  349 	cpx	#0x02
   AFDF 26 05         [ 3]  350 	bne	00102$
                            351 ;ignition.c:40: corrected = correctionIdleAdvance();
   AFE1 CD B1 A4      [ 5]  352 	jsr	_correctionIdleAdvance
   AFE4 20 0A         [ 3]  353 	bra	00105$
   AFE6                     354 00102$:
                            355 ;ignition.c:42: corrected = (int8_t)(corrected + correctionIdleAdvance());
   AFE6 87            [ 2]  356 	psha
   AFE7 CD B1 A4      [ 5]  357 	jsr	_correctionIdleAdvance
   AFEA 95            [ 2]  358 	tsx
   AFEB E7 01         [ 3]  359 	sta	1,x
   AFED 86            [ 2]  360 	pula
   AFEE EB 01         [ 3]  361 	add	1,x
   AFF0                     362 00105$:
                            363 ;ignition.c:46: return corrected;
                            364 ;ignition.c:47: }
   AFF0 A7 02         [ 2]  365 	ais	#2
   AFF2 81            [ 4]  366 	rts
                            367 ;------------------------------------------------------------
                            368 ;Allocation info for local variables in function 'isIdleAdvanceActive'
                            369 ;------------------------------------------------------------
                            370 ;sloc0                     Allocated to stack - sp +3
                            371 ;sloc1                     Allocated to stack - sp +1
                            372 ;------------------------------------------------------------
                            373 ;ignition.c:49: bool isIdleAdvanceActive(void) {
                            374 ;	-----------------------------------------
                            375 ;	 function isIdleAdvanceActive
                            376 ;	-----------------------------------------
                            377 ;	Register assignment is optimal.
                            378 ;	Stack space usage: 3 bytes.
   AFF3                     379 _isIdleAdvanceActive:
   AFF3 A7 FD         [ 2]  380 	ais	#-3
                            381 ;ignition.c:50: if (configPage2.idleAdvEnabled == IDLE_ADV_OFF) return false;
   AFF5 C6 00 CF      [ 4]  382 	lda	(_configPage2 + 0x0015)
   AFF8 26 03         [ 3]  383 	bne	00102$
   AFFA 4F            [ 1]  384 	clra
   AFFB 20 46         [ 3]  385 	bra	00109$
   AFFD                     386 00102$:
                            387 ;ignition.c:51: if (currentStatus.RPM == 0) return false;
   AFFD CE 00 5F      [ 4]  388 	ldx	_currentStatus
   B000 C6 00 60      [ 4]  389 	lda	(_currentStatus + 1)
   B003 26 01         [ 3]  390 	bne	00132$
   B005 5D            [ 1]  391 	tstx
   B006                     392 00132$:
   B006 26 03         [ 3]  393 	bne	00104$
   B008 4F            [ 1]  394 	clra
   B009 20 38         [ 3]  395 	bra	00109$
   B00B                     396 00104$:
                            397 ;ignition.c:53: if (currentStatus.TPS > configPage2.idleAdvTPS) return false;
   B00B C6 00 73      [ 4]  398 	lda	(_currentStatus + 0x0014)
   B00E CE 00 D0      [ 4]  399 	ldx	(_configPage2 + 0x0016)
   B011 9E EF 03      [ 4]  400 	stx	3,s
   B014 9E E1 03      [ 4]  401 	cmp	3,s
   B017 23 03         [ 3]  402 	bls	00106$
   B019 4F            [ 1]  403 	clra
   B01A 20 27         [ 3]  404 	bra	00109$
   B01C                     405 00106$:
                            406 ;ignition.c:54: if (currentStatus.RPM > ((uint16_t)configPage2.idleAdvRPM * 100U)) return false;
   B01C C6 00 5F      [ 4]  407 	lda	_currentStatus
   B01F 9E E7 01      [ 4]  408 	sta	1,s
   B022 C6 00 60      [ 4]  409 	lda	(_currentStatus + 1)
   B025 9E E7 02      [ 4]  410 	sta	2,s
   B028 C6 00 D1      [ 4]  411 	lda	(_configPage2 + 0x0017)
   B02B 5F            [ 1]  412 	clrx
   B02C 87            [ 2]  413 	psha
   B02D 89            [ 2]  414 	pshx
   B02E A6 64         [ 2]  415 	lda	#0x64
   B030 CD CE 65      [ 5]  416 	jsr	__mulint
   B033 A7 02         [ 2]  417 	ais	#2
   B035 9E E0 02      [ 4]  418 	sub	2,s
   B038 9F            [ 1]  419 	txa
   B039 9E E2 01      [ 4]  420 	sbc	1,s
   B03C 24 03         [ 3]  421 	bcc	00108$
   B03E 4F            [ 1]  422 	clra
   B03F 20 02         [ 3]  423 	bra	00109$
   B041                     424 00108$:
                            425 ;ignition.c:56: return true;
   B041 A6 01         [ 2]  426 	lda	#0x01
   B043                     427 00109$:
                            428 ;ignition.c:57: }
   B043 A7 03         [ 2]  429 	ais	#3
   B045 81            [ 4]  430 	rts
                            431 ;------------------------------------------------------------
                            432 ;Allocation info for local variables in function 'correctionCLTAdvance'
                            433 ;------------------------------------------------------------
                            434 ;temp                      Allocated to stack - sp +19
                            435 ;i                         Allocated to stack - sp +15
                            436 ;t1                        Allocated to registers a 
                            437 ;t2                        Allocated to stack - sp +18
                            438 ;v1                        Allocated to stack - sp +17
                            439 ;v2                        Allocated to stack - sp +16
                            440 ;sloc0                     Allocated to stack - sp +15
                            441 ;sloc1                     Allocated to stack - sp +5
                            442 ;sloc2                     Allocated to stack - sp +12
                            443 ;sloc3                     Allocated to stack - sp +13
                            444 ;sloc4                     Allocated to stack - sp +8
                            445 ;sloc5                     Allocated to stack - sp +6
                            446 ;sloc6                     Allocated to stack - sp +1
                            447 ;------------------------------------------------------------
                            448 ;ignition.c:59: int8_t correctionCLTAdvance(void) {
                            449 ;	-----------------------------------------
                            450 ;	 function correctionCLTAdvance
                            451 ;	-----------------------------------------
                            452 ;	Register assignment might be sub-optimal.
                            453 ;	Stack space usage: 19 bytes.
   B046                     454 _correctionCLTAdvance:
   B046 A7 ED         [ 2]  455 	ais	#-19
                            456 ;ignition.c:60: int8_t temp = currentStatus.coolant;
   B048 C6 00 74      [ 4]  457 	lda	(_currentStatus + 0x0015)
   B04B 9E E7 13      [ 4]  458 	sta	19,s
                            459 ;ignition.c:63: for (i = 0; i < 3; i++) {
   B04E 4F            [ 1]  460 	clra
   B04F 9E E7 0F      [ 4]  461 	sta	15,s
   B052                     462 00107$:
                            463 ;ignition.c:64: if (temp >= configPage2.cltAdvBins[i] && temp < configPage2.cltAdvBins[i + 1]) {
   B052 97            [ 1]  464 	tax
   B053 8C            [ 1]  465 	clrh
   B054 DE 00 C5      [ 4]  466 	ldx	((_configPage2 + 0x000b)),x
   B057 9E E3 13      [ 4]  467 	cpx	19,s
   B05A 93 03         [ 3]  468 	ble	00136$
   B05C CC B1 86      [ 3]  469 	jmp	00108$
   B05F                     470 00136$:
   B05F 97            [ 1]  471 	tax
   B060 AF 01         [ 2]  472 	aix	#1
   B062 9E EF 05      [ 4]  473 	stx	5,s
   B065 9E EE 05      [ 4]  474 	ldx	5,s
   B068 DE 00 C5      [ 4]  475 	ldx	((_configPage2 + 0x000b)),x
   B06B 9E EF 0C      [ 4]  476 	stx	12,s
   B06E 95            [ 2]  477 	tsx
   B06F 87            [ 2]  478 	psha
   B070 E6 12         [ 3]  479 	lda	18,x
   B072 E1 0B         [ 3]  480 	cmp	11,x
   B074 86            [ 2]  481 	pula
   B075 91 03         [ 3]  482 	blt	00137$
   B077 CC B1 86      [ 3]  483 	jmp	00108$
   B07A                     484 00137$:
                            485 ;ignition.c:65: int8_t t1 = configPage2.cltAdvBins[i];
   B07A EE 0E         [ 3]  486 	ldx	14,x
   B07C 8C            [ 1]  487 	clrh
   B07D D6 00 C5      [ 4]  488 	lda	((_configPage2 + 0x000b)),x
                            489 ;ignition.c:66: int8_t t2 = configPage2.cltAdvBins[i + 1];
   B080 95            [ 2]  490 	tsx
   B081 EE 0B         [ 3]  491 	ldx	11,x
   B083 9E EF 12      [ 4]  492 	stx	18,s
                            493 ;ignition.c:67: int8_t v1 = configPage2.cltAdvValues[i];
   B086 9E EE 0F      [ 4]  494 	ldx	15,s
   B089 8C            [ 1]  495 	clrh
   B08A DE 00 C9      [ 4]  496 	ldx	((_configPage2 + 0x000f)),x
   B08D 9E EF 11      [ 4]  497 	stx	17,s
                            498 ;ignition.c:68: int8_t v2 = configPage2.cltAdvValues[i + 1];
   B090 9E EE 05      [ 4]  499 	ldx	5,s
   B093 DE 00 C9      [ 4]  500 	ldx	((_configPage2 + 0x000f)),x
   B096 9E EF 10      [ 4]  501 	stx	16,s
                            502 ;ignition.c:70: return (int8_t)(v1 + (int32_t)(temp - t1) * (v2 - v1) / (t2 - t1));
   B099 9E EE 13      [ 4]  503 	ldx	19,s
   B09C 87            [ 2]  504 	psha
   B09D 9E E6 14      [ 4]  505 	lda	20,s
   B0A0 49            [ 1]  506 	rola	
   B0A1 4F            [ 1]  507 	clra	
   B0A2 A2 00         [ 2]  508 	sbc	#0x00
   B0A4 87            [ 2]  509 	psha
   B0A5 8A            [ 2]  510 	pulh
   B0A6 86            [ 2]  511 	pula
   B0A7 9E E7 0E      [ 4]  512 	sta	14,s
   B0AA 49            [ 1]  513 	rola	
   B0AB 4F            [ 1]  514 	clra	
   B0AC A2 00         [ 2]  515 	sbc	#0x00
   B0AE 9E E7 0D      [ 4]  516 	sta	13,s
   B0B1 9F            [ 1]  517 	txa
   B0B2 9E E0 0E      [ 4]  518 	sub	14,s
   B0B5 87            [ 2]  519 	psha
   B0B6 8B            [ 2]  520 	pshh
   B0B7 86            [ 2]  521 	pula
   B0B8 9E E2 0E      [ 4]  522 	sbc	14,s
   B0BB 97            [ 1]  523 	tax
   B0BC 86            [ 2]  524 	pula
   B0BD 9E E7 0B      [ 4]  525 	sta	11,s
   B0C0 9F            [ 1]  526 	txa
   B0C1 9E E7 0A      [ 4]  527 	sta	10,s
   B0C4 49            [ 1]  528 	rola	
   B0C5 4F            [ 1]  529 	clra	
   B0C6 A2 00         [ 2]  530 	sbc	#0x00
   B0C8 9E E7 09      [ 4]  531 	sta	9,s
   B0CB 9E E7 08      [ 4]  532 	sta	8,s
   B0CE 9E E6 10      [ 4]  533 	lda	16,s
   B0D1 87            [ 2]  534 	psha
   B0D2 49            [ 1]  535 	rola	
   B0D3 4F            [ 1]  536 	clra	
   B0D4 A2 00         [ 2]  537 	sbc	#0x00
   B0D6 97            [ 1]  538 	tax
   B0D7 9E E6 12      [ 4]  539 	lda	18,s
   B0DA 9E E7 08      [ 4]  540 	sta	8,s
   B0DD 49            [ 1]  541 	rola	
   B0DE 4F            [ 1]  542 	clra	
   B0DF A2 00         [ 2]  543 	sbc	#0x00
   B0E1 9E E7 07      [ 4]  544 	sta	7,s
   B0E4 86            [ 2]  545 	pula
   B0E5 9E E0 07      [ 4]  546 	sub	7,s
   B0E8 87            [ 2]  547 	psha
   B0E9 9F            [ 1]  548 	txa
   B0EA 9E E2 07      [ 4]  549 	sbc	7,s
   B0ED 97            [ 1]  550 	tax
   B0EE 86            [ 2]  551 	pula
   B0EF 9E E7 04      [ 4]  552 	sta	4,s
   B0F2 9F            [ 1]  553 	txa
   B0F3 9E E7 03      [ 4]  554 	sta	3,s
   B0F6 49            [ 1]  555 	rola	
   B0F7 4F            [ 1]  556 	clra	
   B0F8 A2 00         [ 2]  557 	sbc	#0x00
   B0FA 9E E7 02      [ 4]  558 	sta	2,s
   B0FD 9E E7 01      [ 4]  559 	sta	1,s
   B100 95            [ 2]  560 	tsx
   B101 E6 03         [ 3]  561 	lda	3,x
   B103 87            [ 2]  562 	psha
   B104 E6 02         [ 3]  563 	lda	2,x
   B106 87            [ 2]  564 	psha
   B107 E6 01         [ 3]  565 	lda	1,x
   B109 87            [ 2]  566 	psha
   B10A F6            [ 2]  567 	lda	,x
   B10B 87            [ 2]  568 	psha
   B10C E6 0A         [ 3]  569 	lda	10,x
   B10E 87            [ 2]  570 	psha
   B10F E6 09         [ 3]  571 	lda	9,x
   B111 87            [ 2]  572 	psha
   B112 E6 08         [ 3]  573 	lda	8,x
   B114 87            [ 2]  574 	psha
   B115 E6 07         [ 3]  575 	lda	7,x
   B117 87            [ 2]  576 	psha
   B118 CD D0 87      [ 5]  577 	jsr	__mullong
   B11B 9E E7 0C      [ 4]  578 	sta	12,s
   B11E 9E EF 0B      [ 4]  579 	stx	11,s
   B121 B6 4A         [ 3]  580 	lda	*___SDCC_hc08_ret2
   B123 9E E7 0A      [ 4]  581 	sta	10,s
   B126 B6 4B         [ 3]  582 	lda	*___SDCC_hc08_ret3
   B128 9E E7 09      [ 4]  583 	sta	9,s
   B12B A7 08         [ 2]  584 	ais	#8
   B12D 9E E6 12      [ 4]  585 	lda	18,s
   B130 87            [ 2]  586 	psha
   B131 49            [ 1]  587 	rola	
   B132 4F            [ 1]  588 	clra	
   B133 A2 00         [ 2]  589 	sbc	#0x00
   B135 97            [ 1]  590 	tax
   B136 86            [ 2]  591 	pula
   B137 9E E0 0E      [ 4]  592 	sub	14,s
   B13A 87            [ 2]  593 	psha
   B13B 9F            [ 1]  594 	txa
   B13C 9E E2 0E      [ 4]  595 	sbc	14,s
   B13F 97            [ 1]  596 	tax
   B140 86            [ 2]  597 	pula
   B141 9E E7 0B      [ 4]  598 	sta	11,s
   B144 9F            [ 1]  599 	txa
   B145 9E E7 0A      [ 4]  600 	sta	10,s
   B148 49            [ 1]  601 	rola	
   B149 4F            [ 1]  602 	clra	
   B14A A2 00         [ 2]  603 	sbc	#0x00
   B14C 9E E7 09      [ 4]  604 	sta	9,s
   B14F 9E E7 08      [ 4]  605 	sta	8,s
   B152 95            [ 2]  606 	tsx
   B153 E6 0A         [ 3]  607 	lda	10,x
   B155 87            [ 2]  608 	psha
   B156 E6 09         [ 3]  609 	lda	9,x
   B158 87            [ 2]  610 	psha
   B159 E6 08         [ 3]  611 	lda	8,x
   B15B 87            [ 2]  612 	psha
   B15C E6 07         [ 3]  613 	lda	7,x
   B15E 87            [ 2]  614 	psha
   B15F E6 03         [ 3]  615 	lda	3,x
   B161 87            [ 2]  616 	psha
   B162 E6 02         [ 3]  617 	lda	2,x
   B164 87            [ 2]  618 	psha
   B165 E6 01         [ 3]  619 	lda	1,x
   B167 87            [ 2]  620 	psha
   B168 F6            [ 2]  621 	lda	,x
   B169 87            [ 2]  622 	psha
   B16A CD CE 92      [ 5]  623 	jsr	__divslong
   B16D 9E E7 0C      [ 4]  624 	sta	12,s
   B170 9E EF 0B      [ 4]  625 	stx	11,s
   B173 B6 4A         [ 3]  626 	lda	*___SDCC_hc08_ret2
   B175 9E E7 0A      [ 4]  627 	sta	10,s
   B178 B6 4B         [ 3]  628 	lda	*___SDCC_hc08_ret3
   B17A 9E E7 09      [ 4]  629 	sta	9,s
   B17D A7 08         [ 2]  630 	ais	#8
   B17F 95            [ 2]  631 	tsx
   B180 E6 03         [ 3]  632 	lda	3,x
   B182 EB 10         [ 3]  633 	add	16,x
   B184 20 1B         [ 3]  634 	bra	00109$
   B186                     635 00108$:
                            636 ;ignition.c:63: for (i = 0; i < 3; i++) {
   B186 4C            [ 1]  637 	inca
   B187 9E E7 0F      [ 4]  638 	sta	15,s
   B18A A1 03         [ 2]  639 	cmp	#0x03
   B18C 24 03         [ 3]  640 	bcc	00138$
   B18E CC B0 52      [ 3]  641 	jmp	00107$
   B191                     642 00138$:
                            643 ;ignition.c:74: if (temp < configPage2.cltAdvBins[0]) {
   B191 C6 00 C5      [ 4]  644 	lda	(_configPage2 + 0x000b)
   B194 9E E1 13      [ 4]  645 	cmp	19,s
   B197 93 05         [ 3]  646 	ble	00106$
                            647 ;ignition.c:75: return configPage2.cltAdvValues[0];
   B199 C6 00 C9      [ 4]  648 	lda	(_configPage2 + 0x000f)
   B19C 20 03         [ 3]  649 	bra	00109$
   B19E                     650 00106$:
                            651 ;ignition.c:77: return configPage2.cltAdvValues[3];
   B19E C6 00 CC      [ 4]  652 	lda	(_configPage2 + 0x0012)
   B1A1                     653 00109$:
                            654 ;ignition.c:78: }
   B1A1 A7 13         [ 2]  655 	ais	#19
   B1A3 81            [ 4]  656 	rts
                            657 ;------------------------------------------------------------
                            658 ;Allocation info for local variables in function 'correctionIdleAdvance'
                            659 ;------------------------------------------------------------
                            660 ;delta                     Allocated to registers x h 
                            661 ;sloc0                     Allocated to stack - sp +3
                            662 ;sloc1                     Allocated to stack - sp +1
                            663 ;------------------------------------------------------------
                            664 ;ignition.c:80: int8_t correctionIdleAdvance(void) {
                            665 ;	-----------------------------------------
                            666 ;	 function correctionIdleAdvance
                            667 ;	-----------------------------------------
                            668 ;	Register assignment is optimal.
                            669 ;	Stack space usage: 4 bytes.
   B1A4                     670 _correctionIdleAdvance:
   B1A4 A7 FC         [ 2]  671 	ais	#-4
                            672 ;ignition.c:81: int16_t delta = (int16_t)currentStatus.CLIdleTarget - (int16_t)currentStatus.RPM;
   B1A6 CE 00 8E      [ 4]  673 	ldx	(_currentStatus + 0x002f)
   B1A9 C6 00 8F      [ 4]  674 	lda	((_currentStatus + 0x002f) + 1)
   B1AC 9E E7 04      [ 4]  675 	sta	4,s
   B1AF 9E EF 03      [ 4]  676 	stx	3,s
   B1B2 CE 00 5F      [ 4]  677 	ldx	_currentStatus
   B1B5 C6 00 60      [ 4]  678 	lda	(_currentStatus + 1)
   B1B8 9E E7 02      [ 4]  679 	sta	2,s
   B1BB 9E EF 01      [ 4]  680 	stx	1,s
   B1BE 9E E6 04      [ 4]  681 	lda	4,s
   B1C1 9E E0 02      [ 4]  682 	sub	2,s
   B1C4 97            [ 1]  683 	tax
   B1C5 9E E6 03      [ 4]  684 	lda	3,s
   B1C8 9E E2 01      [ 4]  685 	sbc	1,s
   B1CB 87            [ 2]  686 	psha
   B1CC 8A            [ 2]  687 	pulh
                            688 ;ignition.c:82: if (delta < 0) delta = 0;
   B1CD 9E EF 02      [ 4]  689 	stx	2,s
   B1D0 8B            [ 2]  690 	pshh
   B1D1 86            [ 2]  691 	pula
   B1D2 9E E7 01      [ 4]  692 	sta	1,s
   B1D5 9E E6 01      [ 4]  693 	lda	1,s
   B1D8 A0 00         [ 2]  694 	sub	#0x00
   B1DA 90 02         [ 3]  695 	bge	00102$
   B1DC 8C            [ 1]  696 	clrh
   B1DD 5F            [ 1]  697 	clrx
   B1DE                     698 00102$:
                            699 ;ignition.c:84: return lookupCurveI8(configPage2.idleAdvBins, configPage2.idleAdvValues, 4, (int16_t)(delta / 10));
   B1DE A6 0A         [ 2]  700 	lda	#0x0a
   B1E0 87            [ 2]  701 	psha
   B1E1 4F            [ 1]  702 	clra
   B1E2 87            [ 2]  703 	psha
   B1E3 9F            [ 1]  704 	txa
   B1E4 8B            [ 2]  705 	pshh
   B1E5 88            [ 2]  706 	pulx
   B1E6 CD D1 D3      [ 5]  707 	jsr	__divsint
   B1E9 A7 02         [ 2]  708 	ais	#2
   B1EB 87            [ 2]  709 	psha
   B1EC 89            [ 2]  710 	pshx
   B1ED A6 04         [ 2]  711 	lda	#0x04
   B1EF 87            [ 2]  712 	psha
   B1F0 A6 D6         [ 2]  713 	lda	#(_configPage2 + 0x001c)
   B1F2 87            [ 2]  714 	psha
   B1F3 A6 00         [ 2]  715 	lda	#>(_configPage2 + 0x001c)
   B1F5 87            [ 2]  716 	psha
   B1F6 A6 D2         [ 2]  717 	lda	#(_configPage2 + 0x0018)
   B1F8 AE 00         [ 2]  718 	ldx	#>(_configPage2 + 0x0018)
   B1FA CD A3 9A      [ 5]  719 	jsr	_lookupCurveI8
   B1FD A7 05         [ 2]  720 	ais	#5
                            721 ;ignition.c:85: }
   B1FF A7 04         [ 2]  722 	ais	#4
   B201 81            [ 4]  723 	rts
                            724 ;------------------------------------------------------------
                            725 ;Allocation info for local variables in function 'applyRevLimiter'
                            726 ;------------------------------------------------------------
                            727 ;advance                   Allocated to registers h 
                            728 ;limitRPM                  Allocated to stack - sp +1
                            729 ;cutState                  Allocated with name '_applyRevLimiter_cutState_131072_43'
                            730 ;------------------------------------------------------------
                            731 ;ignition.c:87: int8_t applyRevLimiter(int8_t advance) {
                            732 ;	-----------------------------------------
                            733 ;	 function applyRevLimiter
                            734 ;	-----------------------------------------
                            735 ;	Register assignment is optimal.
                            736 ;	Stack space usage: 2 bytes.
   B202                     737 _applyRevLimiter:
   B202 A7 FE         [ 2]  738 	ais	#-2
   B204 87            [ 2]  739 	psha
   B205 8A            [ 2]  740 	pulh
                            741 ;ignition.c:88: uint16_t limitRPM = (uint16_t)configPage2.revLimitRPM * 100;
   B206 C6 00 C4      [ 4]  742 	lda	(_configPage2 + 0x000a)
   B209 5F            [ 1]  743 	clrx
   B20A 8B            [ 2]  744 	pshh
   B20B 87            [ 2]  745 	psha
   B20C 89            [ 2]  746 	pshx
   B20D A6 64         [ 2]  747 	lda	#0x64
   B20F CD CE 65      [ 5]  748 	jsr	__mulint
   B212 A7 02         [ 2]  749 	ais	#2
   B214 8A            [ 2]  750 	pulh
   B215 9E E7 02      [ 4]  751 	sta	2,s
   B218 9E EF 01      [ 4]  752 	stx	1,s
                            753 ;ignition.c:90: if (currentStatus.RPM >= limitRPM) {
   B21B CE 00 5F      [ 4]  754 	ldx	_currentStatus
   B21E C6 00 60      [ 4]  755 	lda	(_currentStatus + 1)
   B221 9E E0 02      [ 4]  756 	sub	2,s
   B224 9F            [ 1]  757 	txa
   B225 9E E2 01      [ 4]  758 	sbc	1,s
   B228 25 11         [ 3]  759 	bcs	00104$
                            760 ;ignition.c:92: cutState = !cutState;
   B22A C6 01 76      [ 4]  761 	lda	_applyRevLimiter_cutState_131072_43
   B22D A8 01         [ 2]  762 	eor	#0x01
   B22F C7 01 76      [ 4]  763 	sta	_applyRevLimiter_cutState_131072_43
                            764 ;ignition.c:94: if (cutState) {
   B232 C6 01 76      [ 4]  765 	lda	_applyRevLimiter_cutState_131072_43
   B235 27 04         [ 3]  766 	beq	00104$
                            767 ;ignition.c:95: return IGN_MIN_ADVANCE;
   B237 A6 F6         [ 2]  768 	lda	#0xf6
   B239 20 02         [ 3]  769 	bra	00105$
   B23B                     770 00104$:
                            771 ;ignition.c:99: return advance;
   B23B 8B            [ 2]  772 	pshh
   B23C 86            [ 2]  773 	pula
   B23D                     774 00105$:
                            775 ;ignition.c:100: }
   B23D A7 02         [ 2]  776 	ais	#2
   B23F 81            [ 4]  777 	rts
                            778 ;------------------------------------------------------------
                            779 ;Allocation info for local variables in function 'calculateDwell'
                            780 ;------------------------------------------------------------
                            781 ;dwell                     Allocated to stack - sp +1
                            782 ;------------------------------------------------------------
                            783 ;ignition.c:102: uint16_t calculateDwell(void) {
                            784 ;	-----------------------------------------
                            785 ;	 function calculateDwell
                            786 ;	-----------------------------------------
                            787 ;	Register assignment is optimal.
                            788 ;	Stack space usage: 2 bytes.
   B240                     789 _calculateDwell:
   B240 A7 FE         [ 2]  790 	ais	#-2
                            791 ;ignition.c:105: if (BIT_CHECK(currentStatus.engineStatus, ENGINE_CRANK)) {
   B242 C6 00 89      [ 4]  792 	lda	(_currentStatus + 0x002a)
   B245 A5 01         [ 2]  793 	bit	#0x01
   B247 27 0E         [ 3]  794 	beq	00102$
                            795 ;ignition.c:106: dwell = configPage2.dwellCrank;
   B249 C6 00 BF      [ 4]  796 	lda	(_configPage2 + 0x0005)
   B24C 9E E7 01      [ 4]  797 	sta	1,s
   B24F C6 00 C0      [ 4]  798 	lda	((_configPage2 + 0x0005) + 1)
   B252 9E E7 02      [ 4]  799 	sta	2,s
   B255 20 0C         [ 3]  800 	bra	00103$
   B257                     801 00102$:
                            802 ;ignition.c:108: dwell = configPage2.dwellRun;
   B257 C6 00 BD      [ 4]  803 	lda	(_configPage2 + 0x0003)
   B25A 9E E7 01      [ 4]  804 	sta	1,s
   B25D C6 00 BE      [ 4]  805 	lda	((_configPage2 + 0x0003) + 1)
   B260 9E E7 02      [ 4]  806 	sta	2,s
   B263                     807 00103$:
                            808 ;ignition.c:111: if (dwell > configPage2.dwellLimit) {
   B263 CE 00 C1      [ 4]  809 	ldx	(_configPage2 + 0x0007)
   B266 C6 00 C2      [ 4]  810 	lda	((_configPage2 + 0x0007) + 1)
   B269 87            [ 2]  811 	psha
   B26A 9E E0 03      [ 4]  812 	sub	3,s
   B26D 9F            [ 1]  813 	txa
   B26E 9E E2 02      [ 4]  814 	sbc	2,s
   B271 86            [ 2]  815 	pula
   B272 24 06         [ 3]  816 	bcc	00105$
                            817 ;ignition.c:112: dwell = configPage2.dwellLimit;
   B274 9E EF 01      [ 4]  818 	stx	1,s
   B277 9E E7 02      [ 4]  819 	sta	2,s
   B27A                     820 00105$:
                            821 ;ignition.c:115: if (dwell < DWELL_MIN) dwell = DWELL_MIN;
   B27A 9E E6 02      [ 4]  822 	lda	2,s
   B27D 9E EE 01      [ 4]  823 	ldx	1,s
   B280 A0 E8         [ 2]  824 	sub	#0xe8
   B282 9F            [ 1]  825 	txa
   B283 A2 03         [ 2]  826 	sbc	#0x03
   B285 24 08         [ 3]  827 	bcc	00107$
   B287 95            [ 2]  828 	tsx
   B288 A6 03         [ 2]  829 	lda	#0x03
   B28A F7            [ 2]  830 	sta	,x
   B28B A6 E8         [ 2]  831 	lda	#0xe8
   B28D E7 01         [ 3]  832 	sta	1,x
   B28F                     833 00107$:
                            834 ;ignition.c:116: if (dwell > DWELL_MAX) dwell = DWELL_MAX;
   B28F 8A            [ 2]  835 	pulh
   B290 88            [ 2]  836 	pulx
   B291 89            [ 2]  837 	pshx
   B292 8B            [ 2]  838 	pshh
   B293 65 1F 40      [ 3]  839 	cphx	#0x1f40
   B296 23 08         [ 3]  840 	bls	00109$
   B298 95            [ 2]  841 	tsx
   B299 A6 1F         [ 2]  842 	lda	#0x1f
   B29B F7            [ 2]  843 	sta	,x
   B29C A6 40         [ 2]  844 	lda	#0x40
   B29E E7 01         [ 3]  845 	sta	1,x
   B2A0                     846 00109$:
                            847 ;ignition.c:118: return dwell;
   B2A0 95            [ 2]  848 	tsx
   B2A1 FE            [ 2]  849 	ldx	,x
   B2A2 9E E6 02      [ 4]  850 	lda	2,s
                            851 ;ignition.c:119: }
   B2A5 A7 02         [ 2]  852 	ais	#2
   B2A7 81            [ 4]  853 	rts
                            854 	.area CSEG    (CODE)
                            855 	.area CONST   (CODE)
                            856 	.area XINIT   (CODE)
                            857 	.area CABS    (ABS,CODE)
