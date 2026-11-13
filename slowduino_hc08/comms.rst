                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 4.2.0 #13081 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module comms
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
                             22 	.globl _pageSize
                             23 	.globl ___memcpy
                             24 	.globl _strlen
                             25 	.globl _sciPrintString
                             26 	.globl _sciWriteBytes
                             27 	.globl _sciWriteByte
                             28 	.globl _sciReadByte
                             29 	.globl _sciAvailable
                             30 	.globl _sciInit
                             31 	.globl _saveAllConfig
                             32 	.globl _eepromWriteI8
                             33 	.globl _eepromWriteByte
                             34 	.globl _eepromReadI8
                             35 	.globl _eepromReadByte
                             36 	.globl _commsInit
                             37 	.globl _calculateCRC32
                             38 	.globl _sendByte
                             39 	.globl _sendBytes
                             40 	.globl _sendU16
                             41 	.globl _sendU16BE
                             42 	.globl _sendU32BE
                             43 	.globl _commsProcess
                             44 	.globl _processLegacyCommand
                             45 	.globl _sendRealtimeData
                             46 	.globl _sendFirmwareVersion
                             47 	.globl _sendProductString
                             48 	.globl _sendProtocolVersion
                             49 	.globl _sendTestComm
                             50 	.globl _processModernCommand
                             51 	.globl _getPageSize
                             52 	.globl _sendPageValues
                             53 	.globl _writePageValues
                             54 	.globl _sendPageCRC32
                             55 	.globl _sendOutputChannels
                             56 	.globl _burnEEPROM
                             57 	.globl _realtimeByte
                             58 ;--------------------------------------------------------
                             59 ; ram data
                             60 ;--------------------------------------------------------
                             61 	.area DSEG    (PAG)
                             62 ;--------------------------------------------------------
                             63 ; overlayable items in ram
                             64 ;--------------------------------------------------------
                             65 ;--------------------------------------------------------
                             66 ; absolute ram data
                             67 ;--------------------------------------------------------
                             68 	.area IABS    (ABS)
                             69 	.area IABS    (ABS)
                             70 ;--------------------------------------------------------
                             71 ; absolute external ram data
                             72 ;--------------------------------------------------------
                             73 	.area XABS    (ABS)
                             74 ;--------------------------------------------------------
                             75 ; external initialized ram data
                             76 ;--------------------------------------------------------
                             77 	.area XISEG
   01D7                      78 _serialBytesReceived:
   01D7                      79 	.ds 1
   01D8                      80 _modernProtocol:
   01D8                      81 	.ds 1
   01D9                      82 _expectedLength:
   01D9                      83 	.ds 1
                             84 ;--------------------------------------------------------
                             85 ; extended address mode data
                             86 ;--------------------------------------------------------
                             87 	.area XSEG
   0177                      88 _serialBuffer:
   0177                      89 	.ds 24
                             90 ;--------------------------------------------------------
                             91 ; global & static initialisations
                             92 ;--------------------------------------------------------
                             93 	.area HOME    (CODE)
                             94 	.area GSINIT  (CODE)
                             95 	.area GSFINAL (CODE)
                             96 	.area GSINIT  (CODE)
                             97 ;--------------------------------------------------------
                             98 ; Home
                             99 ;--------------------------------------------------------
                            100 	.area HOME    (CODE)
                            101 	.area HOME    (CODE)
                            102 ;--------------------------------------------------------
                            103 ; code
                            104 ;--------------------------------------------------------
                            105 	.area CSEG    (CODE)
                            106 ;------------------------------------------------------------
                            107 ;Allocation info for local variables in function 'noInterrupts'
                            108 ;------------------------------------------------------------
                            109 ;globals.h:100: static inline void noInterrupts(void) { __asm sei __endasm; }
                            110 ;	-----------------------------------------
                            111 ;	 function noInterrupts
                            112 ;	-----------------------------------------
                            113 ;	Register assignment is optimal.
                            114 ;	Stack space usage: 0 bytes.
   B31C                     115 _noInterrupts:
   B31C 9B            [ 2]  116 	 sei	
   B31D 81            [ 4]  117 	rts
                            118 ;------------------------------------------------------------
                            119 ;Allocation info for local variables in function 'interrupts'
                            120 ;------------------------------------------------------------
                            121 ;globals.h:101: static inline void interrupts(void)   { __asm cli __endasm; }
                            122 ;	-----------------------------------------
                            123 ;	 function interrupts
                            124 ;	-----------------------------------------
                            125 ;	Register assignment is optimal.
                            126 ;	Stack space usage: 0 bytes.
   B31E                     127 _interrupts:
   B31E 9A            [ 2]  128 	 cli	
   B31F 81            [ 4]  129 	rts
                            130 ;------------------------------------------------------------
                            131 ;Allocation info for local variables in function 'interpolate'
                            132 ;------------------------------------------------------------
                            133 ;x1                        Allocated to stack - sp +11
                            134 ;x2                        Allocated to stack - sp +13
                            135 ;y1                        Allocated to stack - sp +15
                            136 ;y2                        Allocated to stack - sp +17
                            137 ;x                         Allocated to registers a x 
                            138 ;sloc0                     Allocated to stack - sp +1
                            139 ;sloc1                     Allocated to stack - sp +5
                            140 ;------------------------------------------------------------
                            141 ;tables.h:33: static inline int16_t interpolate(int16_t x, int16_t x1, int16_t x2, int16_t y1, int16_t y2) {
                            142 ;	-----------------------------------------
                            143 ;	 function interpolate
                            144 ;	-----------------------------------------
                            145 ;	Register assignment might be sub-optimal.
                            146 ;	Stack space usage: 8 bytes.
   B320                     147 _interpolate:
   B320 A7 F8         [ 2]  148 	ais	#-8
                            149 ;tables.h:34: if (x2 == x1) return y1;
   B322 87            [ 2]  150 	psha
   B323 9E E6 0F      [ 4]  151 	lda	15,s
   B326 9E E1 0D      [ 4]  152 	cmp	13,s
   B329 86            [ 2]  153 	pula
   B32A 26 0A         [ 3]  154 	bne	00110$
   B32C 87            [ 2]  155 	psha
   B32D 9E E6 0E      [ 4]  156 	lda	14,s
   B330 9E E1 0C      [ 4]  157 	cmp	12,s
   B333 86            [ 2]  158 	pula
   B334 27 02         [ 3]  159 	beq	00111$
   B336                     160 00110$:
   B336 20 09         [ 3]  161 	bra	00102$
   B338                     162 00111$:
   B338 95            [ 2]  163 	tsx
   B339 EE 0E         [ 3]  164 	ldx	14,x
   B33B 9E E6 10      [ 4]  165 	lda	16,s
   B33E CC B4 06      [ 3]  166 	jmp	00103$
   B341                     167 00102$:
                            168 ;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
   B341 9E E0 0C      [ 4]  169 	sub	12,s
   B344 87            [ 2]  170 	psha
   B345 9F            [ 1]  171 	txa
   B346 9E E2 0C      [ 4]  172 	sbc	12,s
   B349 97            [ 1]  173 	tax
   B34A 86            [ 2]  174 	pula
   B34B 9E E7 04      [ 4]  175 	sta	4,s
   B34E 9F            [ 1]  176 	txa
   B34F 9E E7 03      [ 4]  177 	sta	3,s
   B352 49            [ 1]  178 	rola	
   B353 4F            [ 1]  179 	clra	
   B354 A2 00         [ 2]  180 	sbc	#0x00
   B356 9E E7 02      [ 4]  181 	sta	2,s
   B359 9E E7 01      [ 4]  182 	sta	1,s
   B35C 9E E6 12      [ 4]  183 	lda	18,s
   B35F 9E E0 10      [ 4]  184 	sub	16,s
   B362 87            [ 2]  185 	psha
   B363 9E E6 12      [ 4]  186 	lda	18,s
   B366 9E E2 10      [ 4]  187 	sbc	16,s
   B369 97            [ 1]  188 	tax
   B36A 86            [ 2]  189 	pula
   B36B 9E E7 08      [ 4]  190 	sta	8,s
   B36E 9F            [ 1]  191 	txa
   B36F 9E E7 07      [ 4]  192 	sta	7,s
   B372 49            [ 1]  193 	rola	
   B373 4F            [ 1]  194 	clra	
   B374 A2 00         [ 2]  195 	sbc	#0x00
   B376 9E E7 06      [ 4]  196 	sta	6,s
   B379 9E E7 05      [ 4]  197 	sta	5,s
   B37C 95            [ 2]  198 	tsx
   B37D E6 07         [ 3]  199 	lda	7,x
   B37F 87            [ 2]  200 	psha
   B380 E6 06         [ 3]  201 	lda	6,x
   B382 87            [ 2]  202 	psha
   B383 E6 05         [ 3]  203 	lda	5,x
   B385 87            [ 2]  204 	psha
   B386 E6 04         [ 3]  205 	lda	4,x
   B388 87            [ 2]  206 	psha
   B389 E6 03         [ 3]  207 	lda	3,x
   B38B 87            [ 2]  208 	psha
   B38C E6 02         [ 3]  209 	lda	2,x
   B38E 87            [ 2]  210 	psha
   B38F E6 01         [ 3]  211 	lda	1,x
   B391 87            [ 2]  212 	psha
   B392 F6            [ 2]  213 	lda	,x
   B393 87            [ 2]  214 	psha
   B394 CD D0 87      [ 5]  215 	jsr	__mullong
   B397 9E E7 10      [ 4]  216 	sta	16,s
   B39A 9E EF 0F      [ 4]  217 	stx	15,s
   B39D B6 4A         [ 3]  218 	lda	*___SDCC_hc08_ret2
   B39F 9E E7 0E      [ 4]  219 	sta	14,s
   B3A2 B6 4B         [ 3]  220 	lda	*___SDCC_hc08_ret3
   B3A4 9E E7 0D      [ 4]  221 	sta	13,s
   B3A7 A7 08         [ 2]  222 	ais	#8
   B3A9 9E E6 0E      [ 4]  223 	lda	14,s
   B3AC 9E E0 0C      [ 4]  224 	sub	12,s
   B3AF 87            [ 2]  225 	psha
   B3B0 9E E6 0E      [ 4]  226 	lda	14,s
   B3B3 9E E2 0C      [ 4]  227 	sbc	12,s
   B3B6 97            [ 1]  228 	tax
   B3B7 86            [ 2]  229 	pula
   B3B8 9E E7 04      [ 4]  230 	sta	4,s
   B3BB 9F            [ 1]  231 	txa
   B3BC 9E E7 03      [ 4]  232 	sta	3,s
   B3BF 49            [ 1]  233 	rola	
   B3C0 4F            [ 1]  234 	clra	
   B3C1 A2 00         [ 2]  235 	sbc	#0x00
   B3C3 9E E7 02      [ 4]  236 	sta	2,s
   B3C6 9E E7 01      [ 4]  237 	sta	1,s
   B3C9 95            [ 2]  238 	tsx
   B3CA E6 03         [ 3]  239 	lda	3,x
   B3CC 87            [ 2]  240 	psha
   B3CD E6 02         [ 3]  241 	lda	2,x
   B3CF 87            [ 2]  242 	psha
   B3D0 E6 01         [ 3]  243 	lda	1,x
   B3D2 87            [ 2]  244 	psha
   B3D3 F6            [ 2]  245 	lda	,x
   B3D4 87            [ 2]  246 	psha
   B3D5 E6 07         [ 3]  247 	lda	7,x
   B3D7 87            [ 2]  248 	psha
   B3D8 E6 06         [ 3]  249 	lda	6,x
   B3DA 87            [ 2]  250 	psha
   B3DB E6 05         [ 3]  251 	lda	5,x
   B3DD 87            [ 2]  252 	psha
   B3DE E6 04         [ 3]  253 	lda	4,x
   B3E0 87            [ 2]  254 	psha
   B3E1 CD CE 92      [ 5]  255 	jsr	__divslong
   B3E4 9E E7 10      [ 4]  256 	sta	16,s
   B3E7 9E EF 0F      [ 4]  257 	stx	15,s
   B3EA B6 4A         [ 3]  258 	lda	*___SDCC_hc08_ret2
   B3EC 9E E7 0E      [ 4]  259 	sta	14,s
   B3EF B6 4B         [ 3]  260 	lda	*___SDCC_hc08_ret3
   B3F1 9E E7 0D      [ 4]  261 	sta	13,s
   B3F4 A7 08         [ 2]  262 	ais	#8
   B3F6 9E E6 08      [ 4]  263 	lda	8,s
   B3F9 9E EE 07      [ 4]  264 	ldx	7,s
   B3FC 9E EB 10      [ 4]  265 	add	16,s
   B3FF 87            [ 2]  266 	psha
   B400 9F            [ 1]  267 	txa
   B401 9E E9 10      [ 4]  268 	adc	16,s
   B404 97            [ 1]  269 	tax
   B405 86            [ 2]  270 	pula
   B406                     271 00103$:
                            272 ;tables.h:36: }
   B406 A7 08         [ 2]  273 	ais	#8
   B408 81            [ 4]  274 	rts
                            275 ;------------------------------------------------------------
                            276 ;Allocation info for local variables in function 'crc32Update'
                            277 ;------------------------------------------------------------
                            278 ;crc                       Allocated to stack - sp +11
                            279 ;dataByte                  Allocated to stack - sp +15
                            280 ;index                     Allocated to registers a 
                            281 ;sloc0                     Allocated to stack - sp +1
                            282 ;sloc1                     Allocated to stack - sp +5
                            283 ;------------------------------------------------------------
                            284 ;comms.c:95: static uint32_t crc32Update(uint32_t crc, uint8_t dataByte) {
                            285 ;	-----------------------------------------
                            286 ;	 function crc32Update
                            287 ;	-----------------------------------------
                            288 ;	Register assignment is optimal.
                            289 ;	Stack space usage: 8 bytes.
   B409                     290 _crc32Update:
   B409 A7 F8         [ 2]  291 	ais	#-8
                            292 ;comms.c:96: uint8_t index = (uint8_t)((crc ^ dataByte) & 0xFF);
   B40B 95            [ 2]  293 	tsx
   B40C E6 0D         [ 3]  294 	lda	13,x
   B40E E8 0E         [ 3]  295 	eor	14,x
                            296 ;comms.c:97: return (crc >> 8) ^ crc32_table[index];
   B410 87            [ 2]  297 	psha
   B411 E6 0C         [ 3]  298 	lda	12,x
   B413 E7 03         [ 3]  299 	sta	3,x
   B415 E6 0B         [ 3]  300 	lda	11,x
   B417 E7 02         [ 3]  301 	sta	2,x
   B419 E6 0A         [ 3]  302 	lda	10,x
   B41B E7 01         [ 3]  303 	sta	1,x
   B41D 5F            [ 1]  304 	clrx
   B41E 9E EF 02      [ 4]  305 	stx	2,s
   B421 86            [ 2]  306 	pula
   B422 AE 04         [ 2]  307 	ldx	#0x04
   B424 42            [ 5]  308 	mul
   B425 89            [ 2]  309 	pshx
   B426 8A            [ 2]  310 	pulh
   B427 97            [ 1]  311 	tax
   B428 D6 D2 54      [ 4]  312 	lda	(_crc32_table),x
   B42B 9E E7 05      [ 4]  313 	sta	5,s
   B42E D6 D2 55      [ 4]  314 	lda	(_crc32_table+1),x
   B431 9E E7 06      [ 4]  315 	sta	6,s
   B434 D6 D2 56      [ 4]  316 	lda	(_crc32_table+2),x
   B437 9E E7 07      [ 4]  317 	sta	7,s
   B43A D6 D2 57      [ 4]  318 	lda	(_crc32_table+3),x
   B43D 9E E7 08      [ 4]  319 	sta	8,s
   B440 95            [ 2]  320 	tsx
   B441 E6 03         [ 3]  321 	lda	3,x
   B443 E8 07         [ 3]  322 	eor	7,x
   B445 E7 07         [ 3]  323 	sta	7,x
   B447 E6 02         [ 3]  324 	lda	2,x
   B449 E8 06         [ 3]  325 	eor	6,x
   B44B E7 06         [ 3]  326 	sta	6,x
   B44D E6 01         [ 3]  327 	lda	1,x
   B44F E8 05         [ 3]  328 	eor	5,x
   B451 E7 05         [ 3]  329 	sta	5,x
   B453 F6            [ 2]  330 	lda	,x
   B454 E8 04         [ 3]  331 	eor	4,x
   B456 E7 04         [ 3]  332 	sta	4,x
   B458 E6 04         [ 3]  333 	lda	4,x
   B45A B7 4B         [ 3]  334 	sta	*___SDCC_hc08_ret3
   B45C E6 05         [ 3]  335 	lda	5,x
   B45E B7 4A         [ 3]  336 	sta	*___SDCC_hc08_ret2
   B460 EE 06         [ 3]  337 	ldx	6,x
   B462 9E E6 08      [ 4]  338 	lda	8,s
                            339 ;comms.c:98: }
   B465 A7 08         [ 2]  340 	ais	#8
   B467 81            [ 4]  341 	rts
                            342 ;------------------------------------------------------------
                            343 ;Allocation info for local variables in function 'clampU8'
                            344 ;------------------------------------------------------------
                            345 ;value                     Allocated to stack - sp +1
                            346 ;------------------------------------------------------------
                            347 ;comms.c:100: static uint8_t clampU8(int16_t value) {
                            348 ;	-----------------------------------------
                            349 ;	 function clampU8
                            350 ;	-----------------------------------------
                            351 ;	Register assignment is optimal.
                            352 ;	Stack space usage: 2 bytes.
   B468                     353 _clampU8:
   B468 87            [ 2]  354 	psha
   B469 89            [ 2]  355 	pshx
                            356 ;comms.c:101: if (value < 0) return 0;
   B46A 8A            [ 2]  357 	pulh
   B46B 88            [ 2]  358 	pulx
   B46C 89            [ 2]  359 	pshx
   B46D 8B            [ 2]  360 	pshh
   B46E 65 00 00      [ 3]  361 	cphx	#0x0000
   B471 90 03         [ 3]  362 	bge	00102$
   B473 4F            [ 1]  363 	clra
   B474 20 0C         [ 3]  364 	bra	00105$
   B476                     365 00102$:
                            366 ;comms.c:102: if (value > 255) return 255;
   B476 65 00 FF      [ 3]  367 	cphx	#0x00ff
   B479 93 04         [ 3]  368 	ble	00104$
   B47B A6 FF         [ 2]  369 	lda	#0xff
   B47D 20 03         [ 3]  370 	bra	00105$
   B47F                     371 00104$:
                            372 ;comms.c:103: return (uint8_t)value;
   B47F 95            [ 2]  373 	tsx
   B480 E6 01         [ 3]  374 	lda	1,x
   B482                     375 00105$:
                            376 ;comms.c:104: }
   B482 A7 02         [ 2]  377 	ais	#2
   B484 81            [ 4]  378 	rts
                            379 ;------------------------------------------------------------
                            380 ;Allocation info for local variables in function 'encodeIgnitionValue'
                            381 ;------------------------------------------------------------
                            382 ;advance                   Allocated to registers a 
                            383 ;------------------------------------------------------------
                            384 ;comms.c:106: static uint8_t encodeIgnitionValue(int8_t advance) {
                            385 ;	-----------------------------------------
                            386 ;	 function encodeIgnitionValue
                            387 ;	-----------------------------------------
                            388 ;	Register assignment is optimal.
                            389 ;	Stack space usage: 0 bytes.
   B485                     390 _encodeIgnitionValue:
                            391 ;comms.c:107: return clampU8((int16_t)advance + 40);
   B485 87            [ 2]  392 	psha
   B486 49            [ 1]  393 	rola	
   B487 4F            [ 1]  394 	clra	
   B488 A2 00         [ 2]  395 	sbc	#0x00
   B48A 97            [ 1]  396 	tax
   B48B 86            [ 2]  397 	pula
   B48C AB 28         [ 2]  398 	add	#0x28
   B48E 24 01         [ 3]  399 	bcc	00103$
   B490 5C            [ 1]  400 	incx
   B491                     401 00103$:
                            402 ;comms.c:108: }
   B491 CC B4 68      [ 3]  403 	jmp	_clampU8
                            404 ;------------------------------------------------------------
                            405 ;Allocation info for local variables in function 'decodeIgnitionValue'
                            406 ;------------------------------------------------------------
                            407 ;stored                    Allocated to registers a 
                            408 ;------------------------------------------------------------
                            409 ;comms.c:110: static int8_t decodeIgnitionValue(uint8_t stored) {
                            410 ;	-----------------------------------------
                            411 ;	 function decodeIgnitionValue
                            412 ;	-----------------------------------------
                            413 ;	Register assignment is optimal.
                            414 ;	Stack space usage: 0 bytes.
   B494                     415 _decodeIgnitionValue:
                            416 ;comms.c:111: return (int8_t)((int16_t)stored - 40);
   B494 A0 28         [ 2]  417 	sub	#0x28
                            418 ;comms.c:112: }
   B496 81            [ 4]  419 	rts
                            420 ;------------------------------------------------------------
                            421 ;Allocation info for local variables in function 'encodeRpmBin'
                            422 ;------------------------------------------------------------
                            423 ;rpm                       Allocated to registers x h 
                            424 ;------------------------------------------------------------
                            425 ;comms.c:114: static uint8_t encodeRpmBin(uint16_t rpm) {
                            426 ;	-----------------------------------------
                            427 ;	 function encodeRpmBin
                            428 ;	-----------------------------------------
                            429 ;	Register assignment is optimal.
                            430 ;	Stack space usage: 0 bytes.
   B497                     431 _encodeRpmBin:
   B497 89            [ 2]  432 	pshx
   B498 97            [ 1]  433 	tax
   B499 8A            [ 2]  434 	pulh
                            435 ;comms.c:115: return clampU8((int16_t)(rpm / 100));
   B49A A6 64         [ 2]  436 	lda	#0x64
   B49C 87            [ 2]  437 	psha
   B49D 4F            [ 1]  438 	clra
   B49E 87            [ 2]  439 	psha
   B49F 9F            [ 1]  440 	txa
   B4A0 8B            [ 2]  441 	pshh
   B4A1 88            [ 2]  442 	pulx
   B4A2 CD CE 04      [ 5]  443 	jsr	__divuint
   B4A5 A7 02         [ 2]  444 	ais	#2
                            445 ;comms.c:116: }
   B4A7 CC B4 68      [ 3]  446 	jmp	_clampU8
                            447 ;------------------------------------------------------------
                            448 ;Allocation info for local variables in function 'decodeRpmBin'
                            449 ;------------------------------------------------------------
                            450 ;stored                    Allocated to registers a 
                            451 ;------------------------------------------------------------
                            452 ;comms.c:118: static uint16_t decodeRpmBin(uint8_t stored) {
                            453 ;	-----------------------------------------
                            454 ;	 function decodeRpmBin
                            455 ;	-----------------------------------------
                            456 ;	Register assignment is optimal.
                            457 ;	Stack space usage: 0 bytes.
   B4AA                     458 _decodeRpmBin:
                            459 ;comms.c:119: return (uint16_t)stored * 100U;
   B4AA 5F            [ 1]  460 	clrx
   B4AB 87            [ 2]  461 	psha
   B4AC 89            [ 2]  462 	pshx
   B4AD A6 64         [ 2]  463 	lda	#0x64
   B4AF CD CE 65      [ 5]  464 	jsr	__mulint
   B4B2 A7 02         [ 2]  465 	ais	#2
                            466 ;comms.c:120: }
   B4B4 81            [ 4]  467 	rts
                            468 ;------------------------------------------------------------
                            469 ;Allocation info for local variables in function 'getFreeRam'
                            470 ;------------------------------------------------------------
                            471 ;comms.c:125: static uint16_t getFreeRam(void) {
                            472 ;	-----------------------------------------
                            473 ;	 function getFreeRam
                            474 ;	-----------------------------------------
                            475 ;	Register assignment is optimal.
                            476 ;	Stack space usage: 0 bytes.
   B4B5                     477 _getFreeRam:
                            478 ;comms.c:126: return 0;
   B4B5 4F            [ 1]  479 	clra
   B4B6 97            [ 1]  480 	tax
                            481 ;comms.c:127: }
   B4B7 81            [ 4]  482 	rts
                            483 ;------------------------------------------------------------
                            484 ;Allocation info for local variables in function 'commsInit'
                            485 ;------------------------------------------------------------
                            486 ;comms.c:135: void commsInit(void) {
                            487 ;	-----------------------------------------
                            488 ;	 function commsInit
                            489 ;	-----------------------------------------
                            490 ;	Register assignment is optimal.
                            491 ;	Stack space usage: 0 bytes.
   B4B8                     492 _commsInit:
                            493 ;comms.c:136: sciInit();
   B4B8 CD B2 A8      [ 5]  494 	jsr	_sciInit
                            495 ;comms.c:137: serialBytesReceived = 0;
   B4BB 4F            [ 1]  496 	clra
   B4BC C7 01 D7      [ 4]  497 	sta	_serialBytesReceived
                            498 ;comms.c:138: modernProtocol = false;
   B4BF C7 01 D8      [ 4]  499 	sta	_modernProtocol
                            500 ;comms.c:139: expectedLength = 0;
   B4C2 C7 01 D9      [ 4]  501 	sta	_expectedLength
                            502 ;comms.c:140: }
   B4C5 81            [ 4]  503 	rts
                            504 ;------------------------------------------------------------
                            505 ;Allocation info for local variables in function 'calculateCRC32'
                            506 ;------------------------------------------------------------
                            507 ;length                    Allocated to stack - sp +15
                            508 ;data                      Allocated to stack - sp +11
                            509 ;crc                       Allocated to stack - sp +1
                            510 ;i                         Allocated to registers x h 
                            511 ;sloc0                     Allocated to stack - sp +9
                            512 ;sloc1                     Allocated to stack - sp +5
                            513 ;------------------------------------------------------------
                            514 ;comms.c:145: uint32_t calculateCRC32(const uint8_t *data, uint16_t length) {
                            515 ;	-----------------------------------------
                            516 ;	 function calculateCRC32
                            517 ;	-----------------------------------------
                            518 ;	Register assignment is optimal.
                            519 ;	Stack space usage: 12 bytes.
   B4C6                     520 _calculateCRC32:
   B4C6 87            [ 2]  521 	psha
   B4C7 89            [ 2]  522 	pshx
   B4C8 A7 F6         [ 2]  523 	ais	#-10
                            524 ;comms.c:146: uint32_t crc = 0xFFFFFFFFUL;
   B4CA 95            [ 2]  525 	tsx
   B4CB A6 FF         [ 2]  526 	lda	#0xff
   B4CD F7            [ 2]  527 	sta	,x
   B4CE E7 01         [ 3]  528 	sta	1,x
   B4D0 E7 02         [ 3]  529 	sta	2,x
   B4D2 E7 03         [ 3]  530 	sta	3,x
                            531 ;comms.c:148: for (i = 0; i < length; i++) {
   B4D4 8C            [ 1]  532 	clrh
   B4D5 5F            [ 1]  533 	clrx
   B4D6                     534 00103$:
   B4D6 9F            [ 1]  535 	txa
   B4D7 9E E0 10      [ 4]  536 	sub	16,s
   B4DA 8B            [ 2]  537 	pshh
   B4DB 86            [ 2]  538 	pula
   B4DC 9E E2 0F      [ 4]  539 	sbc	15,s
   B4DF 24 4A         [ 3]  540 	bcc	00101$
                            541 ;comms.c:149: crc = crc32Update(crc, data[i]);
   B4E1 9F            [ 1]  542 	txa
   B4E2 9E EB 0C      [ 4]  543 	add	12,s
   B4E5 9E E7 0A      [ 4]  544 	sta	10,s
   B4E8 8B            [ 2]  545 	pshh
   B4E9 86            [ 2]  546 	pula
   B4EA 9E E9 0B      [ 4]  547 	adc	11,s
   B4ED 9E E7 09      [ 4]  548 	sta	9,s
   B4F0 89            [ 2]  549 	pshx
   B4F1 8B            [ 2]  550 	pshh
   B4F2 9E E6 0B      [ 4]  551 	lda	11,s
   B4F5 87            [ 2]  552 	psha
   B4F6 8A            [ 2]  553 	pulh
   B4F7 9E EE 0C      [ 4]  554 	ldx	12,s
   B4FA F6            [ 2]  555 	lda	,x
   B4FB 8A            [ 2]  556 	pulh
   B4FC 88            [ 2]  557 	pulx
   B4FD 89            [ 2]  558 	pshx
   B4FE 8B            [ 2]  559 	pshh
   B4FF 87            [ 2]  560 	psha
   B500 9E E6 07      [ 4]  561 	lda	7,s
   B503 87            [ 2]  562 	psha
   B504 9E E6 07      [ 4]  563 	lda	7,s
   B507 87            [ 2]  564 	psha
   B508 9E E6 07      [ 4]  565 	lda	7,s
   B50B 87            [ 2]  566 	psha
   B50C 9E E6 07      [ 4]  567 	lda	7,s
   B50F 87            [ 2]  568 	psha
   B510 CD B4 09      [ 5]  569 	jsr	_crc32Update
   B513 9E E7 0B      [ 4]  570 	sta	11,s
   B516 9E EF 0A      [ 4]  571 	stx	10,s
   B519 B6 4A         [ 3]  572 	lda	*___SDCC_hc08_ret2
   B51B 9E E7 09      [ 4]  573 	sta	9,s
   B51E B6 4B         [ 3]  574 	lda	*___SDCC_hc08_ret3
   B520 9E E7 08      [ 4]  575 	sta	8,s
   B523 A7 05         [ 2]  576 	ais	#5
   B525 8A            [ 2]  577 	pulh
   B526 88            [ 2]  578 	pulx
                            579 ;comms.c:148: for (i = 0; i < length; i++) {
   B527 AF 01         [ 2]  580 	aix	#1
   B529 20 AB         [ 3]  581 	bra	00103$
   B52B                     582 00101$:
                            583 ;comms.c:151: return ~crc;
   B52B 95            [ 2]  584 	tsx
   B52C E6 03         [ 3]  585 	lda	3,x
   B52E 43            [ 1]  586 	coma
   B52F E7 07         [ 3]  587 	sta	7,x
   B531 E6 02         [ 3]  588 	lda	2,x
   B533 43            [ 1]  589 	coma
   B534 E7 06         [ 3]  590 	sta	6,x
   B536 E6 01         [ 3]  591 	lda	1,x
   B538 43            [ 1]  592 	coma
   B539 E7 05         [ 3]  593 	sta	5,x
   B53B F6            [ 2]  594 	lda	,x
   B53C 43            [ 1]  595 	coma
   B53D E7 04         [ 3]  596 	sta	4,x
   B53F E6 04         [ 3]  597 	lda	4,x
   B541 B7 4B         [ 3]  598 	sta	*___SDCC_hc08_ret3
   B543 E6 05         [ 3]  599 	lda	5,x
   B545 B7 4A         [ 3]  600 	sta	*___SDCC_hc08_ret2
   B547 EE 06         [ 3]  601 	ldx	6,x
   B549 9E E6 08      [ 4]  602 	lda	8,s
                            603 ;comms.c:152: }
   B54C A7 0C         [ 2]  604 	ais	#12
   B54E 81            [ 4]  605 	rts
                            606 ;------------------------------------------------------------
                            607 ;Allocation info for local variables in function 'sendByte'
                            608 ;------------------------------------------------------------
                            609 ;data                      Allocated to registers a 
                            610 ;------------------------------------------------------------
                            611 ;comms.c:154: void sendByte(uint8_t data) {
                            612 ;	-----------------------------------------
                            613 ;	 function sendByte
                            614 ;	-----------------------------------------
                            615 ;	Register assignment is optimal.
                            616 ;	Stack space usage: 0 bytes.
   B54F                     617 _sendByte:
                            618 ;comms.c:155: sciWriteByte(data);
                            619 ;comms.c:156: }
   B54F CC B2 C7      [ 3]  620 	jmp	_sciWriteByte
                            621 ;------------------------------------------------------------
                            622 ;Allocation info for local variables in function 'sendBytes'
                            623 ;------------------------------------------------------------
                            624 ;length                    Allocated to stack - sp +3
                            625 ;data                      Allocated to registers x h 
                            626 ;------------------------------------------------------------
                            627 ;comms.c:158: void sendBytes(const uint8_t *data, uint16_t length) {
                            628 ;	-----------------------------------------
                            629 ;	 function sendBytes
                            630 ;	-----------------------------------------
                            631 ;	Register assignment is optimal.
                            632 ;	Stack space usage: 0 bytes.
   B552                     633 _sendBytes:
   B552 89            [ 2]  634 	pshx
   B553 97            [ 1]  635 	tax
   B554 8A            [ 2]  636 	pulh
                            637 ;comms.c:159: sciWriteBytes(data, length);
   B555 9E E6 04      [ 4]  638 	lda	4,s
   B558 87            [ 2]  639 	psha
   B559 9E E6 04      [ 4]  640 	lda	4,s
   B55C 87            [ 2]  641 	psha
   B55D 9F            [ 1]  642 	txa
   B55E 8B            [ 2]  643 	pshh
   B55F 88            [ 2]  644 	pulx
   B560 CD B2 CE      [ 5]  645 	jsr	_sciWriteBytes
   B563 A7 02         [ 2]  646 	ais	#2
                            647 ;comms.c:160: }
   B565 81            [ 4]  648 	rts
                            649 ;------------------------------------------------------------
                            650 ;Allocation info for local variables in function 'sendU16'
                            651 ;------------------------------------------------------------
                            652 ;value                     Allocated to registers a x 
                            653 ;------------------------------------------------------------
                            654 ;comms.c:162: void sendU16(uint16_t value) {
                            655 ;	-----------------------------------------
                            656 ;	 function sendU16
                            657 ;	-----------------------------------------
                            658 ;	Register assignment is optimal.
                            659 ;	Stack space usage: 0 bytes.
   B566                     660 _sendU16:
                            661 ;comms.c:163: sciWriteByte((uint8_t)(value & 0xFF));
   B566 87            [ 2]  662 	psha
   B567 8A            [ 2]  663 	pulh
   B568 87            [ 2]  664 	psha
   B569 89            [ 2]  665 	pshx
   B56A 8B            [ 2]  666 	pshh
   B56B 86            [ 2]  667 	pula
   B56C CD B2 C7      [ 5]  668 	jsr	_sciWriteByte
   B56F 88            [ 2]  669 	pulx
   B570 86            [ 2]  670 	pula
                            671 ;comms.c:164: sciWriteByte((uint8_t)((value >> 8) & 0xFF));
   B571 9F            [ 1]  672 	txa
                            673 ;comms.c:165: }
   B572 CC B2 C7      [ 3]  674 	jmp	_sciWriteByte
                            675 ;------------------------------------------------------------
                            676 ;Allocation info for local variables in function 'sendU16BE'
                            677 ;------------------------------------------------------------
                            678 ;value                     Allocated to registers a x 
                            679 ;------------------------------------------------------------
                            680 ;comms.c:167: void sendU16BE(uint16_t value) {
                            681 ;	-----------------------------------------
                            682 ;	 function sendU16BE
                            683 ;	-----------------------------------------
                            684 ;	Register assignment is optimal.
                            685 ;	Stack space usage: 0 bytes.
   B575                     686 _sendU16BE:
                            687 ;comms.c:168: sciWriteByte((uint8_t)((value >> 8) & 0xFF));
   B575 89            [ 2]  688 	pshx
   B576 8A            [ 2]  689 	pulh
   B577 87            [ 2]  690 	psha
   B578 89            [ 2]  691 	pshx
   B579 8B            [ 2]  692 	pshh
   B57A 86            [ 2]  693 	pula
   B57B CD B2 C7      [ 5]  694 	jsr	_sciWriteByte
   B57E 88            [ 2]  695 	pulx
   B57F 86            [ 2]  696 	pula
                            697 ;comms.c:169: sciWriteByte((uint8_t)(value & 0xFF));
                            698 ;comms.c:170: }
   B580 CC B2 C7      [ 3]  699 	jmp	_sciWriteByte
                            700 ;------------------------------------------------------------
                            701 ;Allocation info for local variables in function 'sendU32BE'
                            702 ;------------------------------------------------------------
                            703 ;value                     Allocated to stack - sp +3
                            704 ;------------------------------------------------------------
                            705 ;comms.c:172: void sendU32BE(uint32_t value) {
                            706 ;	-----------------------------------------
                            707 ;	 function sendU32BE
                            708 ;	-----------------------------------------
                            709 ;	Register assignment is optimal.
                            710 ;	Stack space usage: 0 bytes.
   B583                     711 _sendU32BE:
                            712 ;comms.c:173: sciWriteByte((uint8_t)((value >> 24) & 0xFF));
   B583 95            [ 2]  713 	tsx
   B584 E6 02         [ 3]  714 	lda	2,x
   B586 CD B2 C7      [ 5]  715 	jsr	_sciWriteByte
                            716 ;comms.c:174: sciWriteByte((uint8_t)((value >> 16) & 0xFF));
   B589 95            [ 2]  717 	tsx
   B58A E6 03         [ 3]  718 	lda	3,x
   B58C CD B2 C7      [ 5]  719 	jsr	_sciWriteByte
                            720 ;comms.c:175: sciWriteByte((uint8_t)((value >> 8) & 0xFF));
   B58F 95            [ 2]  721 	tsx
   B590 E6 04         [ 3]  722 	lda	4,x
   B592 CD B2 C7      [ 5]  723 	jsr	_sciWriteByte
                            724 ;comms.c:176: sciWriteByte((uint8_t)(value & 0xFF));
   B595 95            [ 2]  725 	tsx
   B596 E6 05         [ 3]  726 	lda	5,x
                            727 ;comms.c:177: }
   B598 CC B2 C7      [ 3]  728 	jmp	_sciWriteByte
                            729 ;------------------------------------------------------------
                            730 ;Allocation info for local variables in function 'commsProcess'
                            731 ;------------------------------------------------------------
                            732 ;firstByte                 Allocated to registers a 
                            733 ;parsedLength              Allocated to registers x h 
                            734 ;sloc0                     Allocated to stack - sp +1
                            735 ;------------------------------------------------------------
                            736 ;comms.c:182: void commsProcess(void) {
                            737 ;	-----------------------------------------
                            738 ;	 function commsProcess
                            739 ;	-----------------------------------------
                            740 ;	Register assignment is optimal.
                            741 ;	Stack space usage: 2 bytes.
   B59B                     742 _commsProcess:
   B59B A7 FE         [ 2]  743 	ais	#-2
                            744 ;comms.c:183: if (!sciAvailable()) {
   B59D CD B2 B8      [ 5]  745 	jsr	_sciAvailable
   B5A0 4D            [ 1]  746 	tsta
   B5A1 26 03         [ 3]  747 	bne	00102$
                            748 ;comms.c:184: return;
   B5A3 CC B6 6E      [ 3]  749 	jmp	00123$
   B5A6                     750 00102$:
                            751 ;comms.c:187: if (serialBytesReceived == 0) {
   B5A6 C6 01 D7      [ 4]  752 	lda	_serialBytesReceived
   B5A9 26 2A         [ 3]  753 	bne	00108$
                            754 ;comms.c:188: uint8_t firstByte = sciReadByte();
   B5AB CD B2 C4      [ 5]  755 	jsr	_sciReadByte
                            756 ;comms.c:189: serialBuffer[0] = firstByte;
   B5AE C7 01 77      [ 4]  757 	sta	_serialBuffer
                            758 ;comms.c:190: serialBytesReceived = 1;
   B5B1 AE 01         [ 2]  759 	ldx	#0x01
   B5B3 CF 01 D7      [ 4]  760 	stx	_serialBytesReceived
                            761 ;comms.c:192: if (firstByte >= 'A' && firstByte <= 'z') {
   B5B6 A1 41         [ 2]  762 	cmp	#0x41
   B5B8 25 12         [ 3]  763 	bcs	00104$
   B5BA A1 7A         [ 2]  764 	cmp	#0x7a
   B5BC 22 0E         [ 3]  765 	bhi	00104$
                            766 ;comms.c:193: modernProtocol = false;
   B5BE 5A            [ 1]  767 	decx
   B5BF CF 01 D8      [ 4]  768 	stx	_modernProtocol
                            769 ;comms.c:194: processLegacyCommand(firstByte);
   B5C2 CD B6 71      [ 5]  770 	jsr	_processLegacyCommand
                            771 ;comms.c:195: serialBytesReceived = 0;
   B5C5 4F            [ 1]  772 	clra
   B5C6 C7 01 D7      [ 4]  773 	sta	_serialBytesReceived
                            774 ;comms.c:196: return;
   B5C9 CC B6 6E      [ 3]  775 	jmp	00123$
   B5CC                     776 00104$:
                            777 ;comms.c:198: modernProtocol = true;
   B5CC A6 01         [ 2]  778 	lda	#0x01
   B5CE C7 01 D8      [ 4]  779 	sta	_modernProtocol
                            780 ;comms.c:199: expectedLength = 0;
   B5D1 4A            [ 1]  781 	deca
   B5D2 C7 01 D9      [ 4]  782 	sta	_expectedLength
   B5D5                     783 00108$:
                            784 ;comms.c:203: if (modernProtocol) {
   B5D5 C6 01 D8      [ 4]  785 	lda	_modernProtocol
   B5D8 26 03         [ 3]  786 	bne	00193$
   B5DA CC B6 6E      [ 3]  787 	jmp	00123$
   B5DD                     788 00193$:
                            789 ;comms.c:204: while (sciAvailable() && serialBytesReceived < SERIAL_BUFFER_SIZE) {
   B5DD                     790 00118$:
   B5DD CD B2 B8      [ 5]  791 	jsr	_sciAvailable
   B5E0 4D            [ 1]  792 	tsta
   B5E1 26 03         [ 3]  793 	bne	00194$
   B5E3 CC B6 6E      [ 3]  794 	jmp	00123$
   B5E6                     795 00194$:
   B5E6 C6 01 D7      [ 4]  796 	lda	_serialBytesReceived
   B5E9 A1 18         [ 2]  797 	cmp	#0x18
   B5EB 25 03         [ 3]  798 	bcs	00195$
   B5ED CC B6 6E      [ 3]  799 	jmp	00123$
   B5F0                     800 00195$:
                            801 ;comms.c:205: serialBuffer[serialBytesReceived++] = sciReadByte();
   B5F0 CE 01 D7      [ 4]  802 	ldx	_serialBytesReceived
   B5F3 9F            [ 1]  803 	txa
   B5F4 AB 01         [ 2]  804 	add	#0x01
   B5F6 C7 01 D7      [ 4]  805 	sta	_serialBytesReceived
   B5F9 8C            [ 1]  806 	clrh
   B5FA 89            [ 2]  807 	pshx
   B5FB 8B            [ 2]  808 	pshh
   B5FC CD B2 C4      [ 5]  809 	jsr	_sciReadByte
   B5FF 8A            [ 2]  810 	pulh
   B600 88            [ 2]  811 	pulx
   B601 D7 01 77      [ 4]  812 	sta	(_serialBuffer),x
                            813 ;comms.c:207: if (serialBytesReceived == 2 && expectedLength == 0) {
   B604 C6 01 D7      [ 4]  814 	lda	_serialBytesReceived
   B607 A1 02         [ 2]  815 	cmp	#0x02
   B609 26 33         [ 3]  816 	bne	00112$
   B60B C6 01 D9      [ 4]  817 	lda	_expectedLength
   B60E 26 2E         [ 3]  818 	bne	00112$
                            819 ;comms.c:208: uint16_t parsedLength = ((uint16_t)serialBuffer[0] << 8) | serialBuffer[1];
   B610 C6 01 77      [ 4]  820 	lda	_serialBuffer
   B613 5F            [ 1]  821 	clrx
   B614 9E E7 01      [ 4]  822 	sta	1,s
   B617 9E EF 02      [ 4]  823 	stx	2,s
   B61A CE 01 78      [ 4]  824 	ldx	(_serialBuffer + 0x0001)
   B61D 8C            [ 1]  825 	clrh
   B61E 9F            [ 1]  826 	txa
   B61F 9E EA 02      [ 4]  827 	ora	2,s
   B622 97            [ 1]  828 	tax
   B623 8B            [ 2]  829 	pshh
   B624 86            [ 2]  830 	pula
   B625 9E EA 01      [ 4]  831 	ora	1,s
   B628 87            [ 2]  832 	psha
   B629 8A            [ 2]  833 	pulh
                            834 ;comms.c:210: if (parsedLength > (SERIAL_BUFFER_SIZE - 6)) {
   B62A 65 00 12      [ 3]  835 	cphx	#0x0012
   B62D 23 0C         [ 3]  836 	bls	00110$
                            837 ;comms.c:211: serialBytesReceived = 0;
   B62F 4F            [ 1]  838 	clra
   B630 C7 01 D7      [ 4]  839 	sta	_serialBytesReceived
                            840 ;comms.c:212: expectedLength = 0;
   B633 C7 01 D9      [ 4]  841 	sta	_expectedLength
                            842 ;comms.c:213: modernProtocol = false;
   B636 C7 01 D8      [ 4]  843 	sta	_modernProtocol
                            844 ;comms.c:214: return;
   B639 20 33         [ 3]  845 	bra	00123$
   B63B                     846 00110$:
                            847 ;comms.c:217: expectedLength = (uint8_t)parsedLength;
   B63B CF 01 D9      [ 4]  848 	stx	_expectedLength
   B63E                     849 00112$:
                            850 ;comms.c:220: if (expectedLength > 0 && serialBytesReceived >= (2 + expectedLength + 4)) {
   B63E C6 01 D9      [ 4]  851 	lda	_expectedLength
   B641 27 9A         [ 3]  852 	beq	00118$
   B643 CE 01 D9      [ 4]  853 	ldx	_expectedLength
   B646 8C            [ 1]  854 	clrh
   B647 AF 06         [ 2]  855 	aix	#6
   B649 8B            [ 2]  856 	pshh
   B64A 86            [ 2]  857 	pula
   B64B 9E E7 01      [ 4]  858 	sta	1,s
   B64E 9E EF 02      [ 4]  859 	stx	2,s
   B651 C6 01 D7      [ 4]  860 	lda	_serialBytesReceived
   B654 5F            [ 1]  861 	clrx
   B655 9E E0 02      [ 4]  862 	sub	2,s
   B658 9F            [ 1]  863 	txa
   B659 9E E2 01      [ 4]  864 	sbc	1,s
   B65C 90 03         [ 3]  865 	bge	00200$
   B65E CC B5 DD      [ 3]  866 	jmp	00118$
   B661                     867 00200$:
                            868 ;comms.c:221: processModernCommand();
   B661 CD B6 F5      [ 5]  869 	jsr	_processModernCommand
                            870 ;comms.c:222: serialBytesReceived = 0;
   B664 4F            [ 1]  871 	clra
   B665 C7 01 D7      [ 4]  872 	sta	_serialBytesReceived
                            873 ;comms.c:223: expectedLength = 0;
   B668 C7 01 D9      [ 4]  874 	sta	_expectedLength
                            875 ;comms.c:224: modernProtocol = false;
   B66B C7 01 D8      [ 4]  876 	sta	_modernProtocol
                            877 ;comms.c:225: return;
   B66E                     878 00123$:
                            879 ;comms.c:229: }
   B66E A7 02         [ 2]  880 	ais	#2
   B670 81            [ 4]  881 	rts
                            882 ;------------------------------------------------------------
                            883 ;Allocation info for local variables in function 'processLegacyCommand'
                            884 ;------------------------------------------------------------
                            885 ;command                   Allocated to registers a 
                            886 ;------------------------------------------------------------
                            887 ;comms.c:234: void processLegacyCommand(uint8_t command) {
                            888 ;	-----------------------------------------
                            889 ;	 function processLegacyCommand
                            890 ;	-----------------------------------------
                            891 ;	Register assignment is optimal.
                            892 ;	Stack space usage: 0 bytes.
   B671                     893 _processLegacyCommand:
                            894 ;comms.c:235: switch (command) {
   B671 41 41 1F      [ 4]  895 	cbeqa	#0x41,00101$
   B674 41 42 32      [ 4]  896 	cbeqa	#0x42,00108$
   B677 41 43 2C      [ 4]  897 	cbeqa	#0x43,00106$
   B67A 41 46 26      [ 4]  898 	cbeqa	#0x46,00105$
   B67D 41 49 16      [ 4]  899 	cbeqa	#0x49,00102$
   B680 41 4E 36      [ 4]  900 	cbeqa	#0x4e,00111$
   B683 41 51 17      [ 4]  901 	cbeqa	#0x51,00103$
   B686 41 53 17      [ 4]  902 	cbeqa	#0x53,00104$
   B689 41 62 1D      [ 4]  903 	cbeqa	#0x62,00108$
   B68C 41 63 1D      [ 4]  904 	cbeqa	#0x63,00109$
   B68F 41 6D 21      [ 4]  905 	cbeqa	#0x6d,00110$
   B692 81            [ 4]  906 	rts
                            907 ;comms.c:236: case 'A': sendRealtimeData(); break;
   B693                     908 00101$:
   B693 CC B6 C0      [ 3]  909 	jmp	_sendRealtimeData
                            910 ;comms.c:237: case 'I': sciPrintString("speeduino 202402"); break;
   B696                     911 00102$:
   B696 A6 74         [ 2]  912 	lda	#___str_0
   B698 AE D6         [ 2]  913 	ldx	#>___str_0
   B69A CC B3 09      [ 3]  914 	jmp	_sciPrintString
                            915 ;comms.c:238: case 'Q': sendFirmwareVersion(); break;
   B69D                     916 00103$:
   B69D CC B6 D7      [ 3]  917 	jmp	_sendFirmwareVersion
                            918 ;comms.c:239: case 'S': sendProductString(); break;
   B6A0                     919 00104$:
   B6A0 CC B6 DE      [ 3]  920 	jmp	_sendProductString
                            921 ;comms.c:240: case 'F': sendProtocolVersion(); break;
   B6A3                     922 00105$:
   B6A3 CC B6 E5      [ 3]  923 	jmp	_sendProtocolVersion
                            924 ;comms.c:241: case 'C': sendTestComm(); break;
   B6A6                     925 00106$:
   B6A6 CC B6 EC      [ 3]  926 	jmp	_sendTestComm
                            927 ;comms.c:243: case 'b': burnEEPROM(); break;
   B6A9                     928 00108$:
   B6A9 CC CA 69      [ 3]  929 	jmp	_burnEEPROM
                            930 ;comms.c:244: case 'c': sendU16(2000); break;
   B6AC                     931 00109$:
   B6AC A6 D0         [ 2]  932 	lda	#0xd0
   B6AE AE 07         [ 2]  933 	ldx	#0x07
   B6B0 CC B5 66      [ 3]  934 	jmp	_sendU16
                            935 ;comms.c:245: case 'm': sendU16(getFreeRam()); break;
   B6B3                     936 00110$:
   B6B3 CD B4 B5      [ 5]  937 	jsr	_getFreeRam
   B6B6 CC B5 66      [ 3]  938 	jmp	_sendU16
                            939 ;comms.c:246: case 'N': sciPrintString("\r\n"); break;
   B6B9                     940 00111$:
   B6B9 A6 85         [ 2]  941 	lda	#___str_1
   B6BB AE D6         [ 2]  942 	ldx	#>___str_1
                            943 ;comms.c:248: }
                            944 ;comms.c:249: }
   B6BD CC B3 09      [ 3]  945 	jmp	_sciPrintString
                            946 ;------------------------------------------------------------
                            947 ;Allocation info for local variables in function 'sendRealtimeData'
                            948 ;------------------------------------------------------------
                            949 ;i                         Allocated to registers a 
                            950 ;------------------------------------------------------------
                            951 ;comms.c:251: void sendRealtimeData(void) {
                            952 ;	-----------------------------------------
                            953 ;	 function sendRealtimeData
                            954 ;	-----------------------------------------
                            955 ;	Register assignment is optimal.
                            956 ;	Stack space usage: 0 bytes.
   B6C0                     957 _sendRealtimeData:
                            958 ;comms.c:253: sciWriteByte(0x00);
   B6C0 4F            [ 1]  959 	clra
   B6C1 CD B2 C7      [ 5]  960 	jsr	_sciWriteByte
                            961 ;comms.c:254: for (i = 0; i < LOG_ENTRIES_COUNT; i++) {
   B6C4 4F            [ 1]  962 	clra
   B6C5                     963 00102$:
                            964 ;comms.c:255: sciWriteByte(realtimeByte(i));
   B6C5 87            [ 2]  965 	psha
   B6C6 CD CA 6C      [ 5]  966 	jsr	_realtimeByte
   B6C9 97            [ 1]  967 	tax
   B6CA 86            [ 2]  968 	pula
   B6CB 87            [ 2]  969 	psha
   B6CC 9F            [ 1]  970 	txa
   B6CD CD B2 C7      [ 5]  971 	jsr	_sciWriteByte
   B6D0 86            [ 2]  972 	pula
                            973 ;comms.c:254: for (i = 0; i < LOG_ENTRIES_COUNT; i++) {
   B6D1 4C            [ 1]  974 	inca
   B6D2 A1 7E         [ 2]  975 	cmp	#0x7e
   B6D4 25 EF         [ 3]  976 	bcs	00102$
                            977 ;comms.c:257: }
   B6D6 81            [ 4]  978 	rts
                            979 ;------------------------------------------------------------
                            980 ;Allocation info for local variables in function 'sendFirmwareVersion'
                            981 ;------------------------------------------------------------
                            982 ;comms.c:259: void sendFirmwareVersion(void) { sciPrintString("Speeduino 202402"); }
                            983 ;	-----------------------------------------
                            984 ;	 function sendFirmwareVersion
                            985 ;	-----------------------------------------
                            986 ;	Register assignment is optimal.
                            987 ;	Stack space usage: 0 bytes.
   B6D7                     988 _sendFirmwareVersion:
   B6D7 A6 88         [ 2]  989 	lda	#___str_2
   B6D9 AE D6         [ 2]  990 	ldx	#>___str_2
   B6DB CC B3 09      [ 3]  991 	jmp	_sciPrintString
                            992 ;------------------------------------------------------------
                            993 ;Allocation info for local variables in function 'sendProductString'
                            994 ;------------------------------------------------------------
                            995 ;comms.c:260: void sendProductString(void)   { sciPrintString("Speeduino 202402"); }
                            996 ;	-----------------------------------------
                            997 ;	 function sendProductString
                            998 ;	-----------------------------------------
                            999 ;	Register assignment is optimal.
                           1000 ;	Stack space usage: 0 bytes.
   B6DE                    1001 _sendProductString:
   B6DE A6 88         [ 2] 1002 	lda	#___str_2
   B6E0 AE D6         [ 2] 1003 	ldx	#>___str_2
   B6E2 CC B3 09      [ 3] 1004 	jmp	_sciPrintString
                           1005 ;------------------------------------------------------------
                           1006 ;Allocation info for local variables in function 'sendProtocolVersion'
                           1007 ;------------------------------------------------------------
                           1008 ;comms.c:261: void sendProtocolVersion(void) { sciPrintString("002"); }
                           1009 ;	-----------------------------------------
                           1010 ;	 function sendProtocolVersion
                           1011 ;	-----------------------------------------
                           1012 ;	Register assignment is optimal.
                           1013 ;	Stack space usage: 0 bytes.
   B6E5                    1014 _sendProtocolVersion:
   B6E5 A6 99         [ 2] 1015 	lda	#___str_3
   B6E7 AE D6         [ 2] 1016 	ldx	#>___str_3
   B6E9 CC B3 09      [ 3] 1017 	jmp	_sciPrintString
                           1018 ;------------------------------------------------------------
                           1019 ;Allocation info for local variables in function 'sendTestComm'
                           1020 ;------------------------------------------------------------
                           1021 ;comms.c:263: void sendTestComm(void) {
                           1022 ;	-----------------------------------------
                           1023 ;	 function sendTestComm
                           1024 ;	-----------------------------------------
                           1025 ;	Register assignment is optimal.
                           1026 ;	Stack space usage: 0 bytes.
   B6EC                    1027 _sendTestComm:
                           1028 ;comms.c:264: sendByte(0x00);
   B6EC 4F            [ 1] 1029 	clra
   B6ED CD B5 4F      [ 5] 1030 	jsr	_sendByte
                           1031 ;comms.c:265: sendByte(0xFF);
   B6F0 A6 FF         [ 2] 1032 	lda	#0xff
                           1033 ;comms.c:266: }
   B6F2 CC B5 4F      [ 3] 1034 	jmp	_sendByte
                           1035 ;------------------------------------------------------------
                           1036 ;Allocation info for local variables in function 'processModernCommand'
                           1037 ;------------------------------------------------------------
                           1038 ;payload                   Allocated to registers 
                           1039 ;payloadLength             Allocated to stack - sp +58
                           1040 ;receivedCRC               Allocated to stack - sp +33
                           1041 ;calculatedCRC             Allocated to stack - sp +48
                           1042 ;command                   Allocated to registers a 
                           1043 ;errorByte                 Allocated to stack - sp +32
                           1044 ;responseLength            Allocated to registers 
                           1045 ;crc                       Allocated to stack - sp +29
                           1046 ;i                         Allocated to registers x 
                           1047 ;b                         Allocated to registers a 
                           1048 ;testBuf                   Allocated to stack - sp +31
                           1049 ;tempBuf                   Allocated to stack - sp +27
                           1050 ;tempBuf                   Allocated to stack - sp +1
                           1051 ;len                       Allocated to registers x 
                           1052 ;iface                     Allocated to registers 
                           1053 ;ilen                      Allocated to stack - sp +57
                           1054 ;tempBuf                   Allocated to stack - sp +1
                           1055 ;len                       Allocated to registers x 
                           1056 ;ver                       Allocated to registers 
                           1057 ;vlen                      Allocated to stack - sp +56
                           1058 ;tempBuf                   Allocated to stack - sp +1
                           1059 ;len                       Allocated to registers x 
                           1060 ;prod                      Allocated to registers 
                           1061 ;plen                      Allocated to stack - sp +55
                           1062 ;tempBuf                   Allocated to stack - sp +29
                           1063 ;page                      Allocated to stack - sp +54
                           1064 ;offset                    Allocated to stack - sp +52
                           1065 ;length                    Allocated to registers a x 
                           1066 ;err                       Allocated to stack - sp +32
                           1067 ;page                      Allocated to stack - sp +51
                           1068 ;offset                    Allocated to stack - sp +49
                           1069 ;length                    Allocated to registers x h 
                           1070 ;data                      Allocated to registers 
                           1071 ;result                    Allocated to stack - sp +32
                           1072 ;page                      Allocated to registers a 
                           1073 ;err                       Allocated to stack - sp +32
                           1074 ;subcmd                    Allocated to stack - sp +48
                           1075 ;offset                    Allocated to stack - sp +46
                           1076 ;length                    Allocated to registers a x 
                           1077 ;err                       Allocated to stack - sp +32
                           1078 ;statusByte                Allocated to stack - sp +32
                           1079 ;err                       Allocated to stack - sp +32
                           1080 ;sloc0                     Allocated to stack - sp +45
                           1081 ;sloc1                     Allocated to stack - sp +37
                           1082 ;sloc2                     Allocated to stack - sp +41
                           1083 ;------------------------------------------------------------
                           1084 ;comms.c:271: void processModernCommand(void) {
                           1085 ;	-----------------------------------------
                           1086 ;	 function processModernCommand
                           1087 ;	-----------------------------------------
                           1088 ;	Register assignment might be sub-optimal.
                           1089 ;	Stack space usage: 59 bytes.
   B6F5                    1090 _processModernCommand:
   B6F5 A7 C5         [ 2] 1091 	ais	#-59
                           1092 ;comms.c:272: uint8_t *payload = &serialBuffer[2];
                           1093 ;comms.c:273: uint16_t payloadLength = expectedLength;
   B6F7 95            [ 2] 1094 	tsx
   B6F8 C6 01 D9      [ 4] 1095 	lda	_expectedLength
   B6FB E7 3A         [ 3] 1096 	sta	58,x
   B6FD 4F            [ 1] 1097 	clra
   B6FE E7 39         [ 3] 1098 	sta	57,x
                           1099 ;comms.c:277: receivedCRC = ((uint32_t)serialBuffer[2 + payloadLength] << 24) |
   B700 E6 3A         [ 3] 1100 	lda	58,x
   B702 E7 2C         [ 3] 1101 	sta	44,x
   B704 E6 2C         [ 3] 1102 	lda	44,x
   B706 AB 02         [ 2] 1103 	add	#0x02
   B708 97            [ 1] 1104 	tax
   B709 49            [ 1] 1105 	rola	
   B70A 4F            [ 1] 1106 	clra	
   B70B A2 00         [ 2] 1107 	sbc	#0x00
   B70D 87            [ 2] 1108 	psha
   B70E 8A            [ 2] 1109 	pulh
   B70F D6 01 77      [ 4] 1110 	lda	(_serialBuffer),x
   B712 95            [ 2] 1111 	tsx
   B713 E7 27         [ 3] 1112 	sta	39,x
   B715 5F            [ 1] 1113 	clrx
   B716 9E EF 27      [ 4] 1114 	stx	39,s
   B719 9E EF 26      [ 4] 1115 	stx	38,s
   B71C 9E EF 25      [ 4] 1116 	stx	37,s
   B71F 95            [ 2] 1117 	tsx
   B720 E6 27         [ 3] 1118 	lda	39,x
   B722 E7 24         [ 3] 1119 	sta	36,x
   B724 4F            [ 1] 1120 	clra
   B725 E7 27         [ 3] 1121 	sta	39,x
   B727 E7 26         [ 3] 1122 	sta	38,x
   B729 E7 25         [ 3] 1123 	sta	37,x
                           1124 ;comms.c:278: ((uint32_t)serialBuffer[2 + payloadLength + 1] << 16) |
   B72B E6 2C         [ 3] 1125 	lda	44,x
   B72D AB 03         [ 2] 1126 	add	#0x03
   B72F 97            [ 1] 1127 	tax
   B730 49            [ 1] 1128 	rola	
   B731 4F            [ 1] 1129 	clra	
   B732 A2 00         [ 2] 1130 	sbc	#0x00
   B734 87            [ 2] 1131 	psha
   B735 8A            [ 2] 1132 	pulh
   B736 D6 01 77      [ 4] 1133 	lda	(_serialBuffer),x
   B739 95            [ 2] 1134 	tsx
   B73A E7 2B         [ 3] 1135 	sta	43,x
   B73C 5F            [ 1] 1136 	clrx
   B73D 9E EF 2B      [ 4] 1137 	stx	43,s
   B740 9E EF 2A      [ 4] 1138 	stx	42,s
   B743 9E EF 29      [ 4] 1139 	stx	41,s
   B746 95            [ 2] 1140 	tsx
   B747 E6 2A         [ 3] 1141 	lda	42,x
   B749 E7 28         [ 3] 1142 	sta	40,x
   B74B E6 2B         [ 3] 1143 	lda	43,x
   B74D E7 29         [ 3] 1144 	sta	41,x
   B74F 4F            [ 1] 1145 	clra
   B750 E7 2B         [ 3] 1146 	sta	43,x
   B752 E7 2A         [ 3] 1147 	sta	42,x
   B754 E6 27         [ 3] 1148 	lda	39,x
   B756 EA 2B         [ 3] 1149 	ora	43,x
   B758 E7 2B         [ 3] 1150 	sta	43,x
   B75A E6 26         [ 3] 1151 	lda	38,x
   B75C EA 2A         [ 3] 1152 	ora	42,x
   B75E E7 2A         [ 3] 1153 	sta	42,x
   B760 E6 25         [ 3] 1154 	lda	37,x
   B762 EA 29         [ 3] 1155 	ora	41,x
   B764 E7 29         [ 3] 1156 	sta	41,x
   B766 E6 24         [ 3] 1157 	lda	36,x
   B768 EA 28         [ 3] 1158 	ora	40,x
   B76A E7 28         [ 3] 1159 	sta	40,x
                           1160 ;comms.c:279: ((uint32_t)serialBuffer[2 + payloadLength + 2] << 8) |
   B76C E6 2C         [ 3] 1161 	lda	44,x
   B76E AB 04         [ 2] 1162 	add	#0x04
   B770 97            [ 1] 1163 	tax
   B771 49            [ 1] 1164 	rola	
   B772 4F            [ 1] 1165 	clra	
   B773 A2 00         [ 2] 1166 	sbc	#0x00
   B775 87            [ 2] 1167 	psha
   B776 8A            [ 2] 1168 	pulh
   B777 D6 01 77      [ 4] 1169 	lda	(_serialBuffer),x
   B77A 95            [ 2] 1170 	tsx
   B77B E7 27         [ 3] 1171 	sta	39,x
   B77D 5F            [ 1] 1172 	clrx
   B77E 9E EF 27      [ 4] 1173 	stx	39,s
   B781 9E EF 26      [ 4] 1174 	stx	38,s
   B784 9E EF 25      [ 4] 1175 	stx	37,s
   B787 95            [ 2] 1176 	tsx
   B788 E6 25         [ 3] 1177 	lda	37,x
   B78A E7 24         [ 3] 1178 	sta	36,x
   B78C E6 26         [ 3] 1179 	lda	38,x
   B78E E7 25         [ 3] 1180 	sta	37,x
   B790 E6 27         [ 3] 1181 	lda	39,x
   B792 E7 26         [ 3] 1182 	sta	38,x
   B794 4F            [ 1] 1183 	clra
   B795 E7 27         [ 3] 1184 	sta	39,x
   B797 E6 2B         [ 3] 1185 	lda	43,x
   B799 EA 27         [ 3] 1186 	ora	39,x
   B79B E7 2B         [ 3] 1187 	sta	43,x
   B79D E6 2A         [ 3] 1188 	lda	42,x
   B79F EA 26         [ 3] 1189 	ora	38,x
   B7A1 E7 2A         [ 3] 1190 	sta	42,x
   B7A3 E6 29         [ 3] 1191 	lda	41,x
   B7A5 EA 25         [ 3] 1192 	ora	37,x
   B7A7 E7 29         [ 3] 1193 	sta	41,x
   B7A9 E6 28         [ 3] 1194 	lda	40,x
   B7AB EA 24         [ 3] 1195 	ora	36,x
   B7AD E7 28         [ 3] 1196 	sta	40,x
                           1197 ;comms.c:280: ((uint32_t)serialBuffer[2 + payloadLength + 3]);
   B7AF E6 2C         [ 3] 1198 	lda	44,x
   B7B1 AB 05         [ 2] 1199 	add	#0x05
   B7B3 97            [ 1] 1200 	tax
   B7B4 49            [ 1] 1201 	rola	
   B7B5 4F            [ 1] 1202 	clra	
   B7B6 A2 00         [ 2] 1203 	sbc	#0x00
   B7B8 87            [ 2] 1204 	psha
   B7B9 8A            [ 2] 1205 	pulh
   B7BA D6 01 77      [ 4] 1206 	lda	(_serialBuffer),x
   B7BD 95            [ 2] 1207 	tsx
   B7BE E7 27         [ 3] 1208 	sta	39,x
   B7C0 5F            [ 1] 1209 	clrx
   B7C1 9E EF 27      [ 4] 1210 	stx	39,s
   B7C4 9E EF 26      [ 4] 1211 	stx	38,s
   B7C7 9E EF 25      [ 4] 1212 	stx	37,s
   B7CA 95            [ 2] 1213 	tsx
   B7CB E6 2B         [ 3] 1214 	lda	43,x
   B7CD EA 27         [ 3] 1215 	ora	39,x
   B7CF E7 23         [ 3] 1216 	sta	35,x
   B7D1 E6 2A         [ 3] 1217 	lda	42,x
   B7D3 EA 26         [ 3] 1218 	ora	38,x
   B7D5 E7 22         [ 3] 1219 	sta	34,x
   B7D7 E6 29         [ 3] 1220 	lda	41,x
   B7D9 EA 25         [ 3] 1221 	ora	37,x
   B7DB E7 21         [ 3] 1222 	sta	33,x
   B7DD E6 28         [ 3] 1223 	lda	40,x
   B7DF EA 24         [ 3] 1224 	ora	36,x
   B7E1 E7 20         [ 3] 1225 	sta	32,x
                           1226 ;comms.c:282: calculatedCRC = calculateCRC32(payload, payloadLength);
   B7E3 E6 3A         [ 3] 1227 	lda	58,x
   B7E5 87            [ 2] 1228 	psha
   B7E6 E6 39         [ 3] 1229 	lda	57,x
   B7E8 87            [ 2] 1230 	psha
   B7E9 A6 79         [ 2] 1231 	lda	#(_serialBuffer + 0x0002)
   B7EB AE 01         [ 2] 1232 	ldx	#>(_serialBuffer + 0x0002)
   B7ED CD B4 C6      [ 5] 1233 	jsr	_calculateCRC32
   B7F0 9E E7 2E      [ 4] 1234 	sta	46,s
   B7F3 9E EF 2D      [ 4] 1235 	stx	45,s
   B7F6 B6 4A         [ 3] 1236 	lda	*___SDCC_hc08_ret2
   B7F8 9E E7 2C      [ 4] 1237 	sta	44,s
   B7FB B6 4B         [ 3] 1238 	lda	*___SDCC_hc08_ret3
   B7FD 9E E7 2B      [ 4] 1239 	sta	43,s
   B800 A7 02         [ 2] 1240 	ais	#2
                           1241 ;comms.c:284: if (receivedCRC != calculatedCRC) {
   B802 95            [ 2] 1242 	tsx
   B803 E6 23         [ 3] 1243 	lda	35,x
   B805 E1 2B         [ 3] 1244 	cmp	43,x
   B807 26 12         [ 3] 1245 	bne	00228$
   B809 E6 22         [ 3] 1246 	lda	34,x
   B80B E1 2A         [ 3] 1247 	cmp	42,x
   B80D 26 0C         [ 3] 1248 	bne	00228$
   B80F E6 21         [ 3] 1249 	lda	33,x
   B811 E1 29         [ 3] 1250 	cmp	41,x
   B813 26 06         [ 3] 1251 	bne	00228$
   B815 E6 20         [ 3] 1252 	lda	32,x
   B817 E1 28         [ 3] 1253 	cmp	40,x
   B819 27 45         [ 3] 1254 	beq	00102$
   B81B                    1255 00228$:
                           1256 ;comms.c:285: uint8_t errorByte = SERIAL_RC_CRC_ERR;
   B81B A6 82         [ 2] 1257 	lda	#0x82
   B81D E7 1F         [ 3] 1258 	sta	31,x
                           1259 ;comms.c:286: sendU16BE(1);
   B81F A6 01         [ 2] 1260 	lda	#0x01
   B821 5F            [ 1] 1261 	clrx
   B822 CD B5 75      [ 5] 1262 	jsr	_sendU16BE
                           1263 ;comms.c:287: sendByte(errorByte);
   B825 9E E6 20      [ 4] 1264 	lda	32,s
   B828 CD B5 4F      [ 5] 1265 	jsr	_sendByte
                           1266 ;comms.c:288: sendU32BE(calculateCRC32(&errorByte, 1));
   B82B 95            [ 2] 1267 	tsx
   B82C AF 1F         [ 2] 1268 	aix	#31
   B82E A6 01         [ 2] 1269 	lda	#0x01
   B830 87            [ 2] 1270 	psha
   B831 4A            [ 1] 1271 	deca
   B832 87            [ 2] 1272 	psha
   B833 9F            [ 1] 1273 	txa
   B834 8B            [ 2] 1274 	pshh
   B835 88            [ 2] 1275 	pulx
   B836 CD B4 C6      [ 5] 1276 	jsr	_calculateCRC32
   B839 9E E7 2E      [ 4] 1277 	sta	46,s
   B83C 9E EF 2D      [ 4] 1278 	stx	45,s
   B83F B6 4A         [ 3] 1279 	lda	*___SDCC_hc08_ret2
   B841 9E E7 2C      [ 4] 1280 	sta	44,s
   B844 B6 4B         [ 3] 1281 	lda	*___SDCC_hc08_ret3
   B846 9E E7 2B      [ 4] 1282 	sta	43,s
   B849 A7 02         [ 2] 1283 	ais	#2
   B84B 95            [ 2] 1284 	tsx
   B84C E6 2B         [ 3] 1285 	lda	43,x
   B84E 87            [ 2] 1286 	psha
   B84F E6 2A         [ 3] 1287 	lda	42,x
   B851 87            [ 2] 1288 	psha
   B852 E6 29         [ 3] 1289 	lda	41,x
   B854 87            [ 2] 1290 	psha
   B855 E6 28         [ 3] 1291 	lda	40,x
   B857 87            [ 2] 1292 	psha
   B858 CD B5 83      [ 5] 1293 	jsr	_sendU32BE
   B85B A7 04         [ 2] 1294 	ais	#4
                           1295 ;comms.c:289: return;
   B85D CC C0 99      [ 3] 1296 	jmp	00130$
   B860                    1297 00102$:
                           1298 ;comms.c:292: command = payload[0];
   B860 C6 01 79      [ 4] 1299 	lda	(_serialBuffer + 0x0002)
                           1300 ;comms.c:294: switch (command) {
   B863 41 41 57      [ 4] 1301 	cbeqa	#0x41,00103$
   B866 A1 42         [ 2] 1302 	cmp	#0x42
   B868 26 03         [ 3] 1303 	bne	00230$
   B86A CC C0 0E      [ 3] 1304 	jmp	00125$
   B86D                    1305 00230$:
   B86D A1 43         [ 2] 1306 	cmp	#0x43
   B86F 26 03         [ 3] 1307 	bne	00231$
   B871 CC B9 88      [ 3] 1308 	jmp	00105$
   B874                    1309 00231$:
   B874 A1 46         [ 2] 1310 	cmp	#0x46
   B876 26 03         [ 3] 1311 	bne	00232$
   B878 CC BD 10      [ 3] 1312 	jmp	00110$
   B87B                    1313 00232$:
   B87B A1 49         [ 2] 1314 	cmp	#0x49
   B87D 26 03         [ 3] 1315 	bne	00233$
   B87F CC BA E2      [ 3] 1316 	jmp	00107$
   B882                    1317 00233$:
   B882 A1 4D         [ 2] 1318 	cmp	#0x4d
   B884 26 03         [ 3] 1319 	bne	00234$
   B886 CC BE 68      [ 3] 1320 	jmp	00115$
   B889                    1321 00234$:
   B889 A1 51         [ 2] 1322 	cmp	#0x51
   B88B 26 03         [ 3] 1323 	bne	00235$
   B88D CC BB 9C      [ 3] 1324 	jmp	00108$
   B890                    1325 00235$:
   B890 A1 53         [ 2] 1326 	cmp	#0x53
   B892 26 03         [ 3] 1327 	bne	00236$
   B894 CC BC 56      [ 3] 1328 	jmp	00109$
   B897                    1329 00236$:
   B897 A1 62         [ 2] 1330 	cmp	#0x62
   B899 26 03         [ 3] 1331 	bne	00237$
   B89B CC C0 0E      [ 3] 1332 	jmp	00125$
   B89E                    1333 00237$:
   B89E A1 64         [ 2] 1334 	cmp	#0x64
   B8A0 26 03         [ 3] 1335 	bne	00238$
   B8A2 CC BF 08      [ 3] 1336 	jmp	00116$
   B8A5                    1337 00238$:
   B8A5 A1 66         [ 2] 1338 	cmp	#0x66
   B8A7 26 03         [ 3] 1339 	bne	00239$
   B8A9 CC BA 0E      [ 3] 1340 	jmp	00106$
   B8AC                    1341 00239$:
   B8AC A1 70         [ 2] 1342 	cmp	#0x70
   B8AE 26 03         [ 3] 1343 	bne	00240$
   B8B0 CC BD BE      [ 3] 1344 	jmp	00111$
   B8B3                    1345 00240$:
   B8B3 A1 72         [ 2] 1346 	cmp	#0x72
   B8B5 26 03         [ 3] 1347 	bne	00241$
   B8B7 CC BF 64      [ 3] 1348 	jmp	00120$
   B8BA                    1349 00241$:
   B8BA CC C0 56      [ 3] 1350 	jmp	00126$
                           1351 ;comms.c:295: case 'A': {
   B8BD                    1352 00103$:
                           1353 ;comms.c:300: sendU16BE(responseLength);
   B8BD A6 80         [ 2] 1354 	lda	#0x80
   B8BF 5F            [ 1] 1355 	clrx
   B8C0 CD B5 75      [ 5] 1356 	jsr	_sendU16BE
                           1357 ;comms.c:301: sendByte(SERIAL_RC_OK);
   B8C3 4F            [ 1] 1358 	clra
   B8C4 CD B5 4F      [ 5] 1359 	jsr	_sendByte
                           1360 ;comms.c:302: crc = crc32Update(crc, SERIAL_RC_OK);
   B8C7 4F            [ 1] 1361 	clra
   B8C8 87            [ 2] 1362 	psha
   B8C9 4A            [ 1] 1363 	deca
   B8CA 87            [ 2] 1364 	psha
   B8CB 87            [ 2] 1365 	psha
   B8CC 87            [ 2] 1366 	psha
   B8CD 87            [ 2] 1367 	psha
   B8CE CD B4 09      [ 5] 1368 	jsr	_crc32Update
   B8D1 9E E7 31      [ 4] 1369 	sta	49,s
   B8D4 9E EF 30      [ 4] 1370 	stx	48,s
   B8D7 B6 4A         [ 3] 1371 	lda	*___SDCC_hc08_ret2
   B8D9 9E E7 2F      [ 4] 1372 	sta	47,s
   B8DC B6 4B         [ 3] 1373 	lda	*___SDCC_hc08_ret3
   B8DE 9E E7 2E      [ 4] 1374 	sta	46,s
   B8E1 A7 05         [ 2] 1375 	ais	#5
                           1376 ;comms.c:303: sendByte(0x00);
   B8E3 4F            [ 1] 1377 	clra
   B8E4 CD B5 4F      [ 5] 1378 	jsr	_sendByte
                           1379 ;comms.c:304: crc = crc32Update(crc, 0x00);
   B8E7 4F            [ 1] 1380 	clra
   B8E8 87            [ 2] 1381 	psha
   B8E9 95            [ 2] 1382 	tsx
   B8EA E6 2C         [ 3] 1383 	lda	44,x
   B8EC 87            [ 2] 1384 	psha
   B8ED E6 2B         [ 3] 1385 	lda	43,x
   B8EF 87            [ 2] 1386 	psha
   B8F0 E6 2A         [ 3] 1387 	lda	42,x
   B8F2 87            [ 2] 1388 	psha
   B8F3 E6 29         [ 3] 1389 	lda	41,x
   B8F5 87            [ 2] 1390 	psha
   B8F6 CD B4 09      [ 5] 1391 	jsr	_crc32Update
   B8F9 9E E7 25      [ 4] 1392 	sta	37,s
   B8FC 9E EF 24      [ 4] 1393 	stx	36,s
   B8FF B6 4A         [ 3] 1394 	lda	*___SDCC_hc08_ret2
   B901 9E E7 23      [ 4] 1395 	sta	35,s
   B904 B6 4B         [ 3] 1396 	lda	*___SDCC_hc08_ret3
   B906 9E E7 22      [ 4] 1397 	sta	34,s
   B909 A7 05         [ 2] 1398 	ais	#5
                           1399 ;comms.c:305: for (i = 0; i < LOG_ENTRIES_COUNT; i++) {
   B90B 5F            [ 1] 1400 	clrx
   B90C                    1401 00128$:
                           1402 ;comms.c:306: uint8_t b = realtimeByte(i);
   B90C 89            [ 2] 1403 	pshx
   B90D 9F            [ 1] 1404 	txa
   B90E CD CA 6C      [ 5] 1405 	jsr	_realtimeByte
   B911 88            [ 2] 1406 	pulx
                           1407 ;comms.c:307: sendByte(b);
   B912 87            [ 2] 1408 	psha
   B913 89            [ 2] 1409 	pshx
   B914 CD B5 4F      [ 5] 1410 	jsr	_sendByte
   B917 88            [ 2] 1411 	pulx
   B918 86            [ 2] 1412 	pula
                           1413 ;comms.c:308: crc = crc32Update(crc, b);
   B919 89            [ 2] 1414 	pshx
   B91A 87            [ 2] 1415 	psha
   B91B 9E E6 22      [ 4] 1416 	lda	34,s
   B91E 87            [ 2] 1417 	psha
   B91F 9E E6 22      [ 4] 1418 	lda	34,s
   B922 87            [ 2] 1419 	psha
   B923 9E E6 22      [ 4] 1420 	lda	34,s
   B926 87            [ 2] 1421 	psha
   B927 9E E6 22      [ 4] 1422 	lda	34,s
   B92A 87            [ 2] 1423 	psha
   B92B CD B4 09      [ 5] 1424 	jsr	_crc32Update
   B92E 9E E7 32      [ 4] 1425 	sta	50,s
   B931 9E EF 31      [ 4] 1426 	stx	49,s
   B934 B6 4A         [ 3] 1427 	lda	*___SDCC_hc08_ret2
   B936 9E E7 30      [ 4] 1428 	sta	48,s
   B939 B6 4B         [ 3] 1429 	lda	*___SDCC_hc08_ret3
   B93B 9E E7 2F      [ 4] 1430 	sta	47,s
   B93E A7 05         [ 2] 1431 	ais	#5
   B940 88            [ 2] 1432 	pulx
   B941 9E E6 29      [ 4] 1433 	lda	41,s
   B944 9E E7 1D      [ 4] 1434 	sta	29,s
   B947 9E E6 2A      [ 4] 1435 	lda	42,s
   B94A 9E E7 1E      [ 4] 1436 	sta	30,s
   B94D 9E E6 2B      [ 4] 1437 	lda	43,s
   B950 9E E7 1F      [ 4] 1438 	sta	31,s
   B953 9E E6 2C      [ 4] 1439 	lda	44,s
   B956 9E E7 20      [ 4] 1440 	sta	32,s
                           1441 ;comms.c:305: for (i = 0; i < LOG_ENTRIES_COUNT; i++) {
   B959 AF 01         [ 2] 1442 	aix	#1
   B95B A3 7E         [ 2] 1443 	cpx	#0x7e
   B95D 25 AD         [ 3] 1444 	bcs	00128$
                           1445 ;comms.c:310: sendU32BE(~crc);
   B95F 95            [ 2] 1446 	tsx
   B960 E6 2B         [ 3] 1447 	lda	43,x
   B962 43            [ 1] 1448 	coma
   B963 E7 2B         [ 3] 1449 	sta	43,x
   B965 E6 2A         [ 3] 1450 	lda	42,x
   B967 43            [ 1] 1451 	coma
   B968 E7 2A         [ 3] 1452 	sta	42,x
   B96A E6 29         [ 3] 1453 	lda	41,x
   B96C 43            [ 1] 1454 	coma
   B96D E7 29         [ 3] 1455 	sta	41,x
   B96F E6 28         [ 3] 1456 	lda	40,x
   B971 43            [ 1] 1457 	coma
   B972 E7 28         [ 3] 1458 	sta	40,x
   B974 E6 2B         [ 3] 1459 	lda	43,x
   B976 87            [ 2] 1460 	psha
   B977 E6 2A         [ 3] 1461 	lda	42,x
   B979 87            [ 2] 1462 	psha
   B97A E6 29         [ 3] 1463 	lda	41,x
   B97C 87            [ 2] 1464 	psha
   B97D E6 28         [ 3] 1465 	lda	40,x
   B97F 87            [ 2] 1466 	psha
   B980 CD B5 83      [ 5] 1467 	jsr	_sendU32BE
   B983 A7 04         [ 2] 1468 	ais	#4
                           1469 ;comms.c:311: break;
   B985 CC C0 99      [ 3] 1470 	jmp	00130$
                           1471 ;comms.c:314: case 'C': {
   B988                    1472 00105$:
                           1473 ;comms.c:316: testBuf[0] = SERIAL_RC_OK;
   B988 95            [ 2] 1474 	tsx
   B989 AF 1E         [ 2] 1475 	aix	#30
   B98B 8B            [ 2] 1476 	pshh
   B98C 86            [ 2] 1477 	pula
   B98D 9E E7 29      [ 4] 1478 	sta	41,s
   B990 9E EF 2A      [ 4] 1479 	stx	42,s
   B993 9E E6 29      [ 4] 1480 	lda	41,s
   B996 87            [ 2] 1481 	psha
   B997 8A            [ 2] 1482 	pulh
   B998 9E EE 2A      [ 4] 1483 	ldx	42,s
   B99B 4F            [ 1] 1484 	clra
   B99C F7            [ 2] 1485 	sta	,x
                           1486 ;comms.c:317: testBuf[1] = 0xFF;
   B99D 95            [ 2] 1487 	tsx
   B99E E6 28         [ 3] 1488 	lda	40,x
   B9A0 E7 24         [ 3] 1489 	sta	36,x
   B9A2 E6 29         [ 3] 1490 	lda	41,x
   B9A4 E7 25         [ 3] 1491 	sta	37,x
   B9A6 E6 24         [ 3] 1492 	lda	36,x
   B9A8 87            [ 2] 1493 	psha
   B9A9 8A            [ 2] 1494 	pulh
   B9AA 9E EE 26      [ 4] 1495 	ldx	38,s
   B9AD A6 FF         [ 2] 1496 	lda	#0xff
   B9AF E7 01         [ 3] 1497 	sta	1,x
                           1498 ;comms.c:318: sendU16BE(2);
   B9B1 A6 02         [ 2] 1499 	lda	#0x02
   B9B3 5F            [ 1] 1500 	clrx
   B9B4 CD B5 75      [ 5] 1501 	jsr	_sendU16BE
                           1502 ;comms.c:319: sendBytes(testBuf, 2);
   B9B7 95            [ 2] 1503 	tsx
   B9B8 E6 28         [ 3] 1504 	lda	40,x
   B9BA E7 24         [ 3] 1505 	sta	36,x
   B9BC E6 29         [ 3] 1506 	lda	41,x
   B9BE E7 25         [ 3] 1507 	sta	37,x
   B9C0 E6 24         [ 3] 1508 	lda	36,x
   B9C2 87            [ 2] 1509 	psha
   B9C3 8A            [ 2] 1510 	pulh
   B9C4 9E EE 26      [ 4] 1511 	ldx	38,s
   B9C7 A6 02         [ 2] 1512 	lda	#0x02
   B9C9 87            [ 2] 1513 	psha
   B9CA 4F            [ 1] 1514 	clra
   B9CB 87            [ 2] 1515 	psha
   B9CC 9F            [ 1] 1516 	txa
   B9CD 8B            [ 2] 1517 	pshh
   B9CE 88            [ 2] 1518 	pulx
   B9CF CD B5 52      [ 5] 1519 	jsr	_sendBytes
   B9D2 A7 02         [ 2] 1520 	ais	#2
                           1521 ;comms.c:320: sendU32BE(calculateCRC32(testBuf, 2));
   B9D4 95            [ 2] 1522 	tsx
   B9D5 E6 28         [ 3] 1523 	lda	40,x
   B9D7 87            [ 2] 1524 	psha
   B9D8 8A            [ 2] 1525 	pulh
   B9D9 9E EE 2A      [ 4] 1526 	ldx	42,s
   B9DC A6 02         [ 2] 1527 	lda	#0x02
   B9DE 87            [ 2] 1528 	psha
   B9DF 4F            [ 1] 1529 	clra
   B9E0 87            [ 2] 1530 	psha
   B9E1 9F            [ 1] 1531 	txa
   B9E2 8B            [ 2] 1532 	pshh
   B9E3 88            [ 2] 1533 	pulx
   B9E4 CD B4 C6      [ 5] 1534 	jsr	_calculateCRC32
   B9E7 9E E7 2E      [ 4] 1535 	sta	46,s
   B9EA 9E EF 2D      [ 4] 1536 	stx	45,s
   B9ED B6 4A         [ 3] 1537 	lda	*___SDCC_hc08_ret2
   B9EF 9E E7 2C      [ 4] 1538 	sta	44,s
   B9F2 B6 4B         [ 3] 1539 	lda	*___SDCC_hc08_ret3
   B9F4 9E E7 2B      [ 4] 1540 	sta	43,s
   B9F7 A7 02         [ 2] 1541 	ais	#2
   B9F9 95            [ 2] 1542 	tsx
   B9FA E6 2B         [ 3] 1543 	lda	43,x
   B9FC 87            [ 2] 1544 	psha
   B9FD E6 2A         [ 3] 1545 	lda	42,x
   B9FF 87            [ 2] 1546 	psha
   BA00 E6 29         [ 3] 1547 	lda	41,x
   BA02 87            [ 2] 1548 	psha
   BA03 E6 28         [ 3] 1549 	lda	40,x
   BA05 87            [ 2] 1550 	psha
   BA06 CD B5 83      [ 5] 1551 	jsr	_sendU32BE
   BA09 A7 04         [ 2] 1552 	ais	#4
                           1553 ;comms.c:321: break;
   BA0B CC C0 99      [ 3] 1554 	jmp	00130$
                           1555 ;comms.c:324: case 'f': {
   BA0E                    1556 00106$:
                           1557 ;comms.c:326: tempBuf[0] = SERIAL_RC_OK;
   BA0E 95            [ 2] 1558 	tsx
   BA0F AF 1A         [ 2] 1559 	aix	#26
   BA11 8B            [ 2] 1560 	pshh
   BA12 86            [ 2] 1561 	pula
   BA13 9E E7 29      [ 4] 1562 	sta	41,s
   BA16 9E EF 2A      [ 4] 1563 	stx	42,s
   BA19 9E E6 29      [ 4] 1564 	lda	41,s
   BA1C 87            [ 2] 1565 	psha
   BA1D 8A            [ 2] 1566 	pulh
   BA1E 9E EE 2A      [ 4] 1567 	ldx	42,s
   BA21 4F            [ 1] 1568 	clra
   BA22 F7            [ 2] 1569 	sta	,x
                           1570 ;comms.c:327: tempBuf[1] = 2;
   BA23 95            [ 2] 1571 	tsx
   BA24 E6 28         [ 3] 1572 	lda	40,x
   BA26 E7 24         [ 3] 1573 	sta	36,x
   BA28 E6 29         [ 3] 1574 	lda	41,x
   BA2A E7 25         [ 3] 1575 	sta	37,x
   BA2C E6 24         [ 3] 1576 	lda	36,x
   BA2E 87            [ 2] 1577 	psha
   BA2F 8A            [ 2] 1578 	pulh
   BA30 9E EE 26      [ 4] 1579 	ldx	38,s
   BA33 A6 02         [ 2] 1580 	lda	#0x02
   BA35 E7 01         [ 3] 1581 	sta	1,x
                           1582 ;comms.c:328: tempBuf[2] = (BLOCKING_FACTOR >> 8) & 0xFF;
   BA37 95            [ 2] 1583 	tsx
   BA38 E6 28         [ 3] 1584 	lda	40,x
   BA3A E7 24         [ 3] 1585 	sta	36,x
   BA3C E6 29         [ 3] 1586 	lda	41,x
   BA3E E7 25         [ 3] 1587 	sta	37,x
   BA40 E6 24         [ 3] 1588 	lda	36,x
   BA42 87            [ 2] 1589 	psha
   BA43 8A            [ 2] 1590 	pulh
   BA44 9E EE 26      [ 4] 1591 	ldx	38,s
   BA47 4F            [ 1] 1592 	clra
   BA48 E7 02         [ 3] 1593 	sta	2,x
                           1594 ;comms.c:329: tempBuf[3] = BLOCKING_FACTOR & 0xFF;
   BA4A 95            [ 2] 1595 	tsx
   BA4B E6 28         [ 3] 1596 	lda	40,x
   BA4D E7 24         [ 3] 1597 	sta	36,x
   BA4F E6 29         [ 3] 1598 	lda	41,x
   BA51 E7 25         [ 3] 1599 	sta	37,x
   BA53 E6 24         [ 3] 1600 	lda	36,x
   BA55 87            [ 2] 1601 	psha
   BA56 8A            [ 2] 1602 	pulh
   BA57 9E EE 26      [ 4] 1603 	ldx	38,s
   BA5A A6 79         [ 2] 1604 	lda	#0x79
   BA5C E7 03         [ 3] 1605 	sta	3,x
                           1606 ;comms.c:330: tempBuf[4] = (TABLE_BLOCKING_FACTOR >> 8) & 0xFF;
   BA5E 95            [ 2] 1607 	tsx
   BA5F E6 28         [ 3] 1608 	lda	40,x
   BA61 E7 24         [ 3] 1609 	sta	36,x
   BA63 E6 29         [ 3] 1610 	lda	41,x
   BA65 E7 25         [ 3] 1611 	sta	37,x
   BA67 E6 24         [ 3] 1612 	lda	36,x
   BA69 87            [ 2] 1613 	psha
   BA6A 8A            [ 2] 1614 	pulh
   BA6B 9E EE 26      [ 4] 1615 	ldx	38,s
   BA6E 4F            [ 1] 1616 	clra
   BA6F E7 04         [ 3] 1617 	sta	4,x
                           1618 ;comms.c:331: tempBuf[5] = TABLE_BLOCKING_FACTOR & 0xFF;
   BA71 95            [ 2] 1619 	tsx
   BA72 E6 28         [ 3] 1620 	lda	40,x
   BA74 E7 24         [ 3] 1621 	sta	36,x
   BA76 E6 29         [ 3] 1622 	lda	41,x
   BA78 E7 25         [ 3] 1623 	sta	37,x
   BA7A E6 24         [ 3] 1624 	lda	36,x
   BA7C 87            [ 2] 1625 	psha
   BA7D 8A            [ 2] 1626 	pulh
   BA7E 9E EE 26      [ 4] 1627 	ldx	38,s
   BA81 A6 40         [ 2] 1628 	lda	#0x40
   BA83 E7 05         [ 3] 1629 	sta	5,x
                           1630 ;comms.c:332: sendU16BE(6);
   BA85 A6 06         [ 2] 1631 	lda	#0x06
   BA87 5F            [ 1] 1632 	clrx
   BA88 CD B5 75      [ 5] 1633 	jsr	_sendU16BE
                           1634 ;comms.c:333: sendBytes(tempBuf, 6);
   BA8B 95            [ 2] 1635 	tsx
   BA8C E6 28         [ 3] 1636 	lda	40,x
   BA8E E7 24         [ 3] 1637 	sta	36,x
   BA90 E6 29         [ 3] 1638 	lda	41,x
   BA92 E7 25         [ 3] 1639 	sta	37,x
   BA94 E6 24         [ 3] 1640 	lda	36,x
   BA96 87            [ 2] 1641 	psha
   BA97 8A            [ 2] 1642 	pulh
   BA98 9E EE 26      [ 4] 1643 	ldx	38,s
   BA9B A6 06         [ 2] 1644 	lda	#0x06
   BA9D 87            [ 2] 1645 	psha
   BA9E 4F            [ 1] 1646 	clra
   BA9F 87            [ 2] 1647 	psha
   BAA0 9F            [ 1] 1648 	txa
   BAA1 8B            [ 2] 1649 	pshh
   BAA2 88            [ 2] 1650 	pulx
   BAA3 CD B5 52      [ 5] 1651 	jsr	_sendBytes
   BAA6 A7 02         [ 2] 1652 	ais	#2
                           1653 ;comms.c:334: sendU32BE(calculateCRC32(tempBuf, 6));
   BAA8 95            [ 2] 1654 	tsx
   BAA9 E6 28         [ 3] 1655 	lda	40,x
   BAAB 87            [ 2] 1656 	psha
   BAAC 8A            [ 2] 1657 	pulh
   BAAD 9E EE 2A      [ 4] 1658 	ldx	42,s
   BAB0 A6 06         [ 2] 1659 	lda	#0x06
   BAB2 87            [ 2] 1660 	psha
   BAB3 4F            [ 1] 1661 	clra
   BAB4 87            [ 2] 1662 	psha
   BAB5 9F            [ 1] 1663 	txa
   BAB6 8B            [ 2] 1664 	pshh
   BAB7 88            [ 2] 1665 	pulx
   BAB8 CD B4 C6      [ 5] 1666 	jsr	_calculateCRC32
   BABB 9E E7 2E      [ 4] 1667 	sta	46,s
   BABE 9E EF 2D      [ 4] 1668 	stx	45,s
   BAC1 B6 4A         [ 3] 1669 	lda	*___SDCC_hc08_ret2
   BAC3 9E E7 2C      [ 4] 1670 	sta	44,s
   BAC6 B6 4B         [ 3] 1671 	lda	*___SDCC_hc08_ret3
   BAC8 9E E7 2B      [ 4] 1672 	sta	43,s
   BACB A7 02         [ 2] 1673 	ais	#2
   BACD 95            [ 2] 1674 	tsx
   BACE E6 2B         [ 3] 1675 	lda	43,x
   BAD0 87            [ 2] 1676 	psha
   BAD1 E6 2A         [ 3] 1677 	lda	42,x
   BAD3 87            [ 2] 1678 	psha
   BAD4 E6 29         [ 3] 1679 	lda	41,x
   BAD6 87            [ 2] 1680 	psha
   BAD7 E6 28         [ 3] 1681 	lda	40,x
   BAD9 87            [ 2] 1682 	psha
   BADA CD B5 83      [ 5] 1683 	jsr	_sendU32BE
   BADD A7 04         [ 2] 1684 	ais	#4
                           1685 ;comms.c:335: break;
   BADF CC C0 99      [ 3] 1686 	jmp	00130$
                           1687 ;comms.c:338: case 'I': {
   BAE2                    1688 00107$:
                           1689 ;comms.c:341: const char *iface = "speeduino 202402";
                           1690 ;comms.c:342: uint8_t ilen = (uint8_t)strlen(iface);
   BAE2 A6 74         [ 2] 1691 	lda	#___str_0
   BAE4 AE D6         [ 2] 1692 	ldx	#>___str_0
   BAE6 CD D0 69      [ 5] 1693 	jsr	_strlen
   BAE9 9E E7 39      [ 4] 1694 	sta	57,s
                           1695 ;comms.c:343: tempBuf[len++] = SERIAL_RC_OK;
   BAEC 95            [ 2] 1696 	tsx
   BAED 8B            [ 2] 1697 	pshh
   BAEE 86            [ 2] 1698 	pula
   BAEF 9E E7 29      [ 4] 1699 	sta	41,s
   BAF2 9E EF 2A      [ 4] 1700 	stx	42,s
   BAF5 9E E6 29      [ 4] 1701 	lda	41,s
   BAF8 87            [ 2] 1702 	psha
   BAF9 8A            [ 2] 1703 	pulh
   BAFA 9E EE 2A      [ 4] 1704 	ldx	42,s
   BAFD 4F            [ 1] 1705 	clra
   BAFE F7            [ 2] 1706 	sta	,x
                           1707 ;comms.c:344: memcpy(&tempBuf[len], iface, ilen);
   BAFF 95            [ 2] 1708 	tsx
   BB00 E6 38         [ 3] 1709 	lda	56,x
   BB02 E7 25         [ 3] 1710 	sta	37,x
   BB04 4F            [ 1] 1711 	clra
   BB05 E7 24         [ 3] 1712 	sta	36,x
   BB07 E6 28         [ 3] 1713 	lda	40,x
   BB09 87            [ 2] 1714 	psha
   BB0A 8A            [ 2] 1715 	pulh
   BB0B 9E EE 2A      [ 4] 1716 	ldx	42,s
   BB0E AF 01         [ 2] 1717 	aix	#1
   BB10 9E E6 26      [ 4] 1718 	lda	38,s
   BB13 87            [ 2] 1719 	psha
   BB14 9E E6 26      [ 4] 1720 	lda	38,s
   BB17 87            [ 2] 1721 	psha
   BB18 A6 74         [ 2] 1722 	lda	#___str_0
   BB1A 87            [ 2] 1723 	psha
   BB1B A6 D6         [ 2] 1724 	lda	#>___str_0
   BB1D 87            [ 2] 1725 	psha
   BB1E 9F            [ 1] 1726 	txa
   BB1F 8B            [ 2] 1727 	pshh
   BB20 88            [ 2] 1728 	pulx
   BB21 CD D0 19      [ 5] 1729 	jsr	___memcpy
   BB24 A7 04         [ 2] 1730 	ais	#4
                           1731 ;comms.c:345: len = (uint8_t)(len + ilen);
   BB26 9E EE 39      [ 4] 1732 	ldx	57,s
   BB29 AF 01         [ 2] 1733 	aix	#1
                           1734 ;comms.c:346: sendU16BE(len);
   BB2B 8C            [ 1] 1735 	clrh
   BB2C 89            [ 2] 1736 	pshx
   BB2D 8B            [ 2] 1737 	pshh
   BB2E 9F            [ 1] 1738 	txa
   BB2F 8B            [ 2] 1739 	pshh
   BB30 88            [ 2] 1740 	pulx
   BB31 CD B5 75      [ 5] 1741 	jsr	_sendU16BE
   BB34 8A            [ 2] 1742 	pulh
   BB35 88            [ 2] 1743 	pulx
                           1744 ;comms.c:347: sendBytes(tempBuf, len);
   BB36 9E E6 29      [ 4] 1745 	lda	41,s
   BB39 9E E7 25      [ 4] 1746 	sta	37,s
   BB3C 9E E6 2A      [ 4] 1747 	lda	42,s
   BB3F 9E E7 26      [ 4] 1748 	sta	38,s
   BB42 9E E6 26      [ 4] 1749 	lda	38,s
   BB45 9E E7 26      [ 4] 1750 	sta	38,s
   BB48 9E E6 25      [ 4] 1751 	lda	37,s
   BB4B 9E E7 25      [ 4] 1752 	sta	37,s
   BB4E 89            [ 2] 1753 	pshx
   BB4F 8B            [ 2] 1754 	pshh
   BB50 89            [ 2] 1755 	pshx
   BB51 8B            [ 2] 1756 	pshh
   BB52 9E E6 2A      [ 4] 1757 	lda	42,s
   BB55 9E EE 29      [ 4] 1758 	ldx	41,s
   BB58 CD B5 52      [ 5] 1759 	jsr	_sendBytes
   BB5B A7 02         [ 2] 1760 	ais	#2
   BB5D 8A            [ 2] 1761 	pulh
   BB5E 88            [ 2] 1762 	pulx
                           1763 ;comms.c:348: sendU32BE(calculateCRC32(tempBuf, len));
   BB5F 9E E6 2A      [ 4] 1764 	lda	42,s
   BB62 9E E7 2A      [ 4] 1765 	sta	42,s
   BB65 9E E6 29      [ 4] 1766 	lda	41,s
   BB68 9E E7 29      [ 4] 1767 	sta	41,s
   BB6B 89            [ 2] 1768 	pshx
   BB6C 8B            [ 2] 1769 	pshh
   BB6D 95            [ 2] 1770 	tsx
   BB6E E6 2B         [ 3] 1771 	lda	43,x
   BB70 EE 2A         [ 3] 1772 	ldx	42,x
   BB72 CD B4 C6      [ 5] 1773 	jsr	_calculateCRC32
   BB75 9E E7 2E      [ 4] 1774 	sta	46,s
   BB78 9E EF 2D      [ 4] 1775 	stx	45,s
   BB7B B6 4A         [ 3] 1776 	lda	*___SDCC_hc08_ret2
   BB7D 9E E7 2C      [ 4] 1777 	sta	44,s
   BB80 B6 4B         [ 3] 1778 	lda	*___SDCC_hc08_ret3
   BB82 9E E7 2B      [ 4] 1779 	sta	43,s
   BB85 A7 02         [ 2] 1780 	ais	#2
   BB87 95            [ 2] 1781 	tsx
   BB88 E6 2B         [ 3] 1782 	lda	43,x
   BB8A 87            [ 2] 1783 	psha
   BB8B E6 2A         [ 3] 1784 	lda	42,x
   BB8D 87            [ 2] 1785 	psha
   BB8E E6 29         [ 3] 1786 	lda	41,x
   BB90 87            [ 2] 1787 	psha
   BB91 E6 28         [ 3] 1788 	lda	40,x
   BB93 87            [ 2] 1789 	psha
   BB94 CD B5 83      [ 5] 1790 	jsr	_sendU32BE
   BB97 A7 04         [ 2] 1791 	ais	#4
                           1792 ;comms.c:349: break;
   BB99 CC C0 99      [ 3] 1793 	jmp	00130$
                           1794 ;comms.c:352: case 'Q': {
   BB9C                    1795 00108$:
                           1796 ;comms.c:355: const char *ver = "speeduino 202207";
                           1797 ;comms.c:356: uint8_t vlen = (uint8_t)strlen(ver);
   BB9C A6 9D         [ 2] 1798 	lda	#___str_4
   BB9E AE D6         [ 2] 1799 	ldx	#>___str_4
   BBA0 CD D0 69      [ 5] 1800 	jsr	_strlen
   BBA3 9E E7 38      [ 4] 1801 	sta	56,s
                           1802 ;comms.c:357: tempBuf[len++] = SERIAL_RC_OK;
   BBA6 95            [ 2] 1803 	tsx
   BBA7 8B            [ 2] 1804 	pshh
   BBA8 86            [ 2] 1805 	pula
   BBA9 9E E7 29      [ 4] 1806 	sta	41,s
   BBAC 9E EF 2A      [ 4] 1807 	stx	42,s
   BBAF 9E E6 29      [ 4] 1808 	lda	41,s
   BBB2 87            [ 2] 1809 	psha
   BBB3 8A            [ 2] 1810 	pulh
   BBB4 9E EE 2A      [ 4] 1811 	ldx	42,s
   BBB7 4F            [ 1] 1812 	clra
   BBB8 F7            [ 2] 1813 	sta	,x
                           1814 ;comms.c:358: memcpy(&tempBuf[len], ver, vlen);
   BBB9 95            [ 2] 1815 	tsx
   BBBA E6 37         [ 3] 1816 	lda	55,x
   BBBC E7 25         [ 3] 1817 	sta	37,x
   BBBE 4F            [ 1] 1818 	clra
   BBBF E7 24         [ 3] 1819 	sta	36,x
   BBC1 E6 28         [ 3] 1820 	lda	40,x
   BBC3 87            [ 2] 1821 	psha
   BBC4 8A            [ 2] 1822 	pulh
   BBC5 9E EE 2A      [ 4] 1823 	ldx	42,s
   BBC8 AF 01         [ 2] 1824 	aix	#1
   BBCA 9E E6 26      [ 4] 1825 	lda	38,s
   BBCD 87            [ 2] 1826 	psha
   BBCE 9E E6 26      [ 4] 1827 	lda	38,s
   BBD1 87            [ 2] 1828 	psha
   BBD2 A6 9D         [ 2] 1829 	lda	#___str_4
   BBD4 87            [ 2] 1830 	psha
   BBD5 A6 D6         [ 2] 1831 	lda	#>___str_4
   BBD7 87            [ 2] 1832 	psha
   BBD8 9F            [ 1] 1833 	txa
   BBD9 8B            [ 2] 1834 	pshh
   BBDA 88            [ 2] 1835 	pulx
   BBDB CD D0 19      [ 5] 1836 	jsr	___memcpy
   BBDE A7 04         [ 2] 1837 	ais	#4
                           1838 ;comms.c:359: len = (uint8_t)(len + vlen);
   BBE0 9E EE 38      [ 4] 1839 	ldx	56,s
   BBE3 AF 01         [ 2] 1840 	aix	#1
                           1841 ;comms.c:360: sendU16BE(len);
   BBE5 8C            [ 1] 1842 	clrh
   BBE6 89            [ 2] 1843 	pshx
   BBE7 8B            [ 2] 1844 	pshh
   BBE8 9F            [ 1] 1845 	txa
   BBE9 8B            [ 2] 1846 	pshh
   BBEA 88            [ 2] 1847 	pulx
   BBEB CD B5 75      [ 5] 1848 	jsr	_sendU16BE
   BBEE 8A            [ 2] 1849 	pulh
   BBEF 88            [ 2] 1850 	pulx
                           1851 ;comms.c:361: sendBytes(tempBuf, len);
   BBF0 9E E6 29      [ 4] 1852 	lda	41,s
   BBF3 9E E7 25      [ 4] 1853 	sta	37,s
   BBF6 9E E6 2A      [ 4] 1854 	lda	42,s
   BBF9 9E E7 26      [ 4] 1855 	sta	38,s
   BBFC 9E E6 26      [ 4] 1856 	lda	38,s
   BBFF 9E E7 26      [ 4] 1857 	sta	38,s
   BC02 9E E6 25      [ 4] 1858 	lda	37,s
   BC05 9E E7 25      [ 4] 1859 	sta	37,s
   BC08 89            [ 2] 1860 	pshx
   BC09 8B            [ 2] 1861 	pshh
   BC0A 89            [ 2] 1862 	pshx
   BC0B 8B            [ 2] 1863 	pshh
   BC0C 9E E6 2A      [ 4] 1864 	lda	42,s
   BC0F 9E EE 29      [ 4] 1865 	ldx	41,s
   BC12 CD B5 52      [ 5] 1866 	jsr	_sendBytes
   BC15 A7 02         [ 2] 1867 	ais	#2
   BC17 8A            [ 2] 1868 	pulh
   BC18 88            [ 2] 1869 	pulx
                           1870 ;comms.c:362: sendU32BE(calculateCRC32(tempBuf, len));
   BC19 9E E6 2A      [ 4] 1871 	lda	42,s
   BC1C 9E E7 2A      [ 4] 1872 	sta	42,s
   BC1F 9E E6 29      [ 4] 1873 	lda	41,s
   BC22 9E E7 29      [ 4] 1874 	sta	41,s
   BC25 89            [ 2] 1875 	pshx
   BC26 8B            [ 2] 1876 	pshh
   BC27 95            [ 2] 1877 	tsx
   BC28 E6 2B         [ 3] 1878 	lda	43,x
   BC2A EE 2A         [ 3] 1879 	ldx	42,x
   BC2C CD B4 C6      [ 5] 1880 	jsr	_calculateCRC32
   BC2F 9E E7 2E      [ 4] 1881 	sta	46,s
   BC32 9E EF 2D      [ 4] 1882 	stx	45,s
   BC35 B6 4A         [ 3] 1883 	lda	*___SDCC_hc08_ret2
   BC37 9E E7 2C      [ 4] 1884 	sta	44,s
   BC3A B6 4B         [ 3] 1885 	lda	*___SDCC_hc08_ret3
   BC3C 9E E7 2B      [ 4] 1886 	sta	43,s
   BC3F A7 02         [ 2] 1887 	ais	#2
   BC41 95            [ 2] 1888 	tsx
   BC42 E6 2B         [ 3] 1889 	lda	43,x
   BC44 87            [ 2] 1890 	psha
   BC45 E6 2A         [ 3] 1891 	lda	42,x
   BC47 87            [ 2] 1892 	psha
   BC48 E6 29         [ 3] 1893 	lda	41,x
   BC4A 87            [ 2] 1894 	psha
   BC4B E6 28         [ 3] 1895 	lda	40,x
   BC4D 87            [ 2] 1896 	psha
   BC4E CD B5 83      [ 5] 1897 	jsr	_sendU32BE
   BC51 A7 04         [ 2] 1898 	ais	#4
                           1899 ;comms.c:363: break;
   BC53 CC C0 99      [ 3] 1900 	jmp	00130$
                           1901 ;comms.c:366: case 'S': {
   BC56                    1902 00109$:
                           1903 ;comms.c:369: const char *prod = "Speeduino 2024.02.4";
                           1904 ;comms.c:370: uint8_t plen = (uint8_t)strlen(prod);
   BC56 A6 AE         [ 2] 1905 	lda	#___str_5
   BC58 AE D6         [ 2] 1906 	ldx	#>___str_5
   BC5A CD D0 69      [ 5] 1907 	jsr	_strlen
   BC5D 9E E7 37      [ 4] 1908 	sta	55,s
                           1909 ;comms.c:371: tempBuf[len++] = SERIAL_RC_OK;
   BC60 95            [ 2] 1910 	tsx
   BC61 8B            [ 2] 1911 	pshh
   BC62 86            [ 2] 1912 	pula
   BC63 9E E7 29      [ 4] 1913 	sta	41,s
   BC66 9E EF 2A      [ 4] 1914 	stx	42,s
   BC69 9E E6 29      [ 4] 1915 	lda	41,s
   BC6C 87            [ 2] 1916 	psha
   BC6D 8A            [ 2] 1917 	pulh
   BC6E 9E EE 2A      [ 4] 1918 	ldx	42,s
   BC71 4F            [ 1] 1919 	clra
   BC72 F7            [ 2] 1920 	sta	,x
                           1921 ;comms.c:372: memcpy(&tempBuf[len], prod, plen);
   BC73 95            [ 2] 1922 	tsx
   BC74 E6 36         [ 3] 1923 	lda	54,x
   BC76 E7 25         [ 3] 1924 	sta	37,x
   BC78 4F            [ 1] 1925 	clra
   BC79 E7 24         [ 3] 1926 	sta	36,x
   BC7B E6 28         [ 3] 1927 	lda	40,x
   BC7D 87            [ 2] 1928 	psha
   BC7E 8A            [ 2] 1929 	pulh
   BC7F 9E EE 2A      [ 4] 1930 	ldx	42,s
   BC82 AF 01         [ 2] 1931 	aix	#1
   BC84 9E E6 26      [ 4] 1932 	lda	38,s
   BC87 87            [ 2] 1933 	psha
   BC88 9E E6 26      [ 4] 1934 	lda	38,s
   BC8B 87            [ 2] 1935 	psha
   BC8C A6 AE         [ 2] 1936 	lda	#___str_5
   BC8E 87            [ 2] 1937 	psha
   BC8F A6 D6         [ 2] 1938 	lda	#>___str_5
   BC91 87            [ 2] 1939 	psha
   BC92 9F            [ 1] 1940 	txa
   BC93 8B            [ 2] 1941 	pshh
   BC94 88            [ 2] 1942 	pulx
   BC95 CD D0 19      [ 5] 1943 	jsr	___memcpy
   BC98 A7 04         [ 2] 1944 	ais	#4
                           1945 ;comms.c:373: len = (uint8_t)(len + plen);
   BC9A 9E EE 37      [ 4] 1946 	ldx	55,s
   BC9D AF 01         [ 2] 1947 	aix	#1
                           1948 ;comms.c:374: sendU16BE(len);
   BC9F 8C            [ 1] 1949 	clrh
   BCA0 89            [ 2] 1950 	pshx
   BCA1 8B            [ 2] 1951 	pshh
   BCA2 9F            [ 1] 1952 	txa
   BCA3 8B            [ 2] 1953 	pshh
   BCA4 88            [ 2] 1954 	pulx
   BCA5 CD B5 75      [ 5] 1955 	jsr	_sendU16BE
   BCA8 8A            [ 2] 1956 	pulh
   BCA9 88            [ 2] 1957 	pulx
                           1958 ;comms.c:375: sendBytes(tempBuf, len);
   BCAA 9E E6 29      [ 4] 1959 	lda	41,s
   BCAD 9E E7 25      [ 4] 1960 	sta	37,s
   BCB0 9E E6 2A      [ 4] 1961 	lda	42,s
   BCB3 9E E7 26      [ 4] 1962 	sta	38,s
   BCB6 9E E6 26      [ 4] 1963 	lda	38,s
   BCB9 9E E7 26      [ 4] 1964 	sta	38,s
   BCBC 9E E6 25      [ 4] 1965 	lda	37,s
   BCBF 9E E7 25      [ 4] 1966 	sta	37,s
   BCC2 89            [ 2] 1967 	pshx
   BCC3 8B            [ 2] 1968 	pshh
   BCC4 89            [ 2] 1969 	pshx
   BCC5 8B            [ 2] 1970 	pshh
   BCC6 9E E6 2A      [ 4] 1971 	lda	42,s
   BCC9 9E EE 29      [ 4] 1972 	ldx	41,s
   BCCC CD B5 52      [ 5] 1973 	jsr	_sendBytes
   BCCF A7 02         [ 2] 1974 	ais	#2
   BCD1 8A            [ 2] 1975 	pulh
   BCD2 88            [ 2] 1976 	pulx
                           1977 ;comms.c:376: sendU32BE(calculateCRC32(tempBuf, len));
   BCD3 9E E6 2A      [ 4] 1978 	lda	42,s
   BCD6 9E E7 2A      [ 4] 1979 	sta	42,s
   BCD9 9E E6 29      [ 4] 1980 	lda	41,s
   BCDC 9E E7 29      [ 4] 1981 	sta	41,s
   BCDF 89            [ 2] 1982 	pshx
   BCE0 8B            [ 2] 1983 	pshh
   BCE1 95            [ 2] 1984 	tsx
   BCE2 E6 2B         [ 3] 1985 	lda	43,x
   BCE4 EE 2A         [ 3] 1986 	ldx	42,x
   BCE6 CD B4 C6      [ 5] 1987 	jsr	_calculateCRC32
   BCE9 9E E7 2E      [ 4] 1988 	sta	46,s
   BCEC 9E EF 2D      [ 4] 1989 	stx	45,s
   BCEF B6 4A         [ 3] 1990 	lda	*___SDCC_hc08_ret2
   BCF1 9E E7 2C      [ 4] 1991 	sta	44,s
   BCF4 B6 4B         [ 3] 1992 	lda	*___SDCC_hc08_ret3
   BCF6 9E E7 2B      [ 4] 1993 	sta	43,s
   BCF9 A7 02         [ 2] 1994 	ais	#2
   BCFB 95            [ 2] 1995 	tsx
   BCFC E6 2B         [ 3] 1996 	lda	43,x
   BCFE 87            [ 2] 1997 	psha
   BCFF E6 2A         [ 3] 1998 	lda	42,x
   BD01 87            [ 2] 1999 	psha
   BD02 E6 29         [ 3] 2000 	lda	41,x
   BD04 87            [ 2] 2001 	psha
   BD05 E6 28         [ 3] 2002 	lda	40,x
   BD07 87            [ 2] 2003 	psha
   BD08 CD B5 83      [ 5] 2004 	jsr	_sendU32BE
   BD0B A7 04         [ 2] 2005 	ais	#4
                           2006 ;comms.c:377: break;
   BD0D CC C0 99      [ 3] 2007 	jmp	00130$
                           2008 ;comms.c:380: case 'F': {
   BD10                    2009 00110$:
                           2010 ;comms.c:382: tempBuf[0] = SERIAL_RC_OK;
   BD10 95            [ 2] 2011 	tsx
   BD11 AF 1C         [ 2] 2012 	aix	#28
   BD13 8B            [ 2] 2013 	pshh
   BD14 86            [ 2] 2014 	pula
   BD15 9E E7 29      [ 4] 2015 	sta	41,s
   BD18 9E EF 2A      [ 4] 2016 	stx	42,s
   BD1B 9E E6 29      [ 4] 2017 	lda	41,s
   BD1E 87            [ 2] 2018 	psha
   BD1F 8A            [ 2] 2019 	pulh
   BD20 9E EE 2A      [ 4] 2020 	ldx	42,s
   BD23 4F            [ 1] 2021 	clra
   BD24 F7            [ 2] 2022 	sta	,x
                           2023 ;comms.c:383: tempBuf[1] = '0';
   BD25 95            [ 2] 2024 	tsx
   BD26 E6 28         [ 3] 2025 	lda	40,x
   BD28 E7 24         [ 3] 2026 	sta	36,x
   BD2A E6 29         [ 3] 2027 	lda	41,x
   BD2C E7 25         [ 3] 2028 	sta	37,x
   BD2E E6 24         [ 3] 2029 	lda	36,x
   BD30 87            [ 2] 2030 	psha
   BD31 8A            [ 2] 2031 	pulh
   BD32 9E EE 26      [ 4] 2032 	ldx	38,s
   BD35 A6 30         [ 2] 2033 	lda	#0x30
   BD37 E7 01         [ 3] 2034 	sta	1,x
                           2035 ;comms.c:384: tempBuf[2] = '0';
   BD39 95            [ 2] 2036 	tsx
   BD3A E6 28         [ 3] 2037 	lda	40,x
   BD3C E7 24         [ 3] 2038 	sta	36,x
   BD3E E6 29         [ 3] 2039 	lda	41,x
   BD40 E7 25         [ 3] 2040 	sta	37,x
   BD42 E6 24         [ 3] 2041 	lda	36,x
   BD44 87            [ 2] 2042 	psha
   BD45 8A            [ 2] 2043 	pulh
   BD46 9E EE 26      [ 4] 2044 	ldx	38,s
   BD49 A6 30         [ 2] 2045 	lda	#0x30
   BD4B E7 02         [ 3] 2046 	sta	2,x
                           2047 ;comms.c:385: tempBuf[3] = '2';
   BD4D 95            [ 2] 2048 	tsx
   BD4E E6 28         [ 3] 2049 	lda	40,x
   BD50 E7 24         [ 3] 2050 	sta	36,x
   BD52 E6 29         [ 3] 2051 	lda	41,x
   BD54 E7 25         [ 3] 2052 	sta	37,x
   BD56 E6 24         [ 3] 2053 	lda	36,x
   BD58 87            [ 2] 2054 	psha
   BD59 8A            [ 2] 2055 	pulh
   BD5A 9E EE 26      [ 4] 2056 	ldx	38,s
   BD5D A6 32         [ 2] 2057 	lda	#0x32
   BD5F E7 03         [ 3] 2058 	sta	3,x
                           2059 ;comms.c:386: sendU16BE(4);
   BD61 A6 04         [ 2] 2060 	lda	#0x04
   BD63 5F            [ 1] 2061 	clrx
   BD64 CD B5 75      [ 5] 2062 	jsr	_sendU16BE
                           2063 ;comms.c:387: sendBytes(tempBuf, 4);
   BD67 95            [ 2] 2064 	tsx
   BD68 E6 28         [ 3] 2065 	lda	40,x
   BD6A E7 24         [ 3] 2066 	sta	36,x
   BD6C E6 29         [ 3] 2067 	lda	41,x
   BD6E E7 25         [ 3] 2068 	sta	37,x
   BD70 E6 24         [ 3] 2069 	lda	36,x
   BD72 87            [ 2] 2070 	psha
   BD73 8A            [ 2] 2071 	pulh
   BD74 9E EE 26      [ 4] 2072 	ldx	38,s
   BD77 A6 04         [ 2] 2073 	lda	#0x04
   BD79 87            [ 2] 2074 	psha
   BD7A 4F            [ 1] 2075 	clra
   BD7B 87            [ 2] 2076 	psha
   BD7C 9F            [ 1] 2077 	txa
   BD7D 8B            [ 2] 2078 	pshh
   BD7E 88            [ 2] 2079 	pulx
   BD7F CD B5 52      [ 5] 2080 	jsr	_sendBytes
   BD82 A7 02         [ 2] 2081 	ais	#2
                           2082 ;comms.c:388: sendU32BE(calculateCRC32(tempBuf, 4));
   BD84 95            [ 2] 2083 	tsx
   BD85 E6 28         [ 3] 2084 	lda	40,x
   BD87 87            [ 2] 2085 	psha
   BD88 8A            [ 2] 2086 	pulh
   BD89 9E EE 2A      [ 4] 2087 	ldx	42,s
   BD8C A6 04         [ 2] 2088 	lda	#0x04
   BD8E 87            [ 2] 2089 	psha
   BD8F 4F            [ 1] 2090 	clra
   BD90 87            [ 2] 2091 	psha
   BD91 9F            [ 1] 2092 	txa
   BD92 8B            [ 2] 2093 	pshh
   BD93 88            [ 2] 2094 	pulx
   BD94 CD B4 C6      [ 5] 2095 	jsr	_calculateCRC32
   BD97 9E E7 2E      [ 4] 2096 	sta	46,s
   BD9A 9E EF 2D      [ 4] 2097 	stx	45,s
   BD9D B6 4A         [ 3] 2098 	lda	*___SDCC_hc08_ret2
   BD9F 9E E7 2C      [ 4] 2099 	sta	44,s
   BDA2 B6 4B         [ 3] 2100 	lda	*___SDCC_hc08_ret3
   BDA4 9E E7 2B      [ 4] 2101 	sta	43,s
   BDA7 A7 02         [ 2] 2102 	ais	#2
   BDA9 95            [ 2] 2103 	tsx
   BDAA E6 2B         [ 3] 2104 	lda	43,x
   BDAC 87            [ 2] 2105 	psha
   BDAD E6 2A         [ 3] 2106 	lda	42,x
   BDAF 87            [ 2] 2107 	psha
   BDB0 E6 29         [ 3] 2108 	lda	41,x
   BDB2 87            [ 2] 2109 	psha
   BDB3 E6 28         [ 3] 2110 	lda	40,x
   BDB5 87            [ 2] 2111 	psha
   BDB6 CD B5 83      [ 5] 2112 	jsr	_sendU32BE
   BDB9 A7 04         [ 2] 2113 	ais	#4
                           2114 ;comms.c:389: break;
   BDBB CC C0 99      [ 3] 2115 	jmp	00130$
                           2116 ;comms.c:392: case 'p': {
   BDBE                    2117 00111$:
                           2118 ;comms.c:393: if (payloadLength >= 7) {
   BDBE 9E E6 3B      [ 4] 2119 	lda	59,s
   BDC1 9E EE 3A      [ 4] 2120 	ldx	58,s
   BDC4 A0 07         [ 2] 2121 	sub	#0x07
   BDC6 9F            [ 1] 2122 	txa
   BDC7 A2 00         [ 2] 2123 	sbc	#0x00
   BDC9 25 57         [ 3] 2124 	bcs	00113$
                           2125 ;comms.c:394: uint8_t page = payload[2];
   BDCB C6 01 7B      [ 4] 2126 	lda	(_serialBuffer + 0x0004)
   BDCE 9E E7 36      [ 4] 2127 	sta	54,s
                           2128 ;comms.c:395: uint16_t offset = payload[3] | ((uint16_t)payload[4] << 8);
   BDD1 C6 01 7C      [ 4] 2129 	lda	(_serialBuffer + 0x0005)
   BDD4 CE 01 7D      [ 4] 2130 	ldx	(_serialBuffer + 0x0006)
   BDD7 8C            [ 1] 2131 	clrh
   BDD8 87            [ 2] 2132 	psha
   BDD9 9F            [ 1] 2133 	txa
   BDDA 9E E7 2A      [ 4] 2134 	sta	42,s
   BDDD 87            [ 2] 2135 	psha
   BDDE 4F            [ 1] 2136 	clra
   BDDF 9E E7 2C      [ 4] 2137 	sta	44,s
   BDE2 86            [ 2] 2138 	pula
   BDE3 86            [ 2] 2139 	pula
   BDE4 5F            [ 1] 2140 	clrx
   BDE5 9E EA 2A      [ 4] 2141 	ora	42,s
   BDE8 9E E7 35      [ 4] 2142 	sta	53,s
   BDEB 9F            [ 1] 2143 	txa
   BDEC 9E EA 29      [ 4] 2144 	ora	41,s
   BDEF 9E E7 34      [ 4] 2145 	sta	52,s
                           2146 ;comms.c:396: uint16_t length = payload[5] | ((uint16_t)payload[6] << 8);
   BDF2 C6 01 7E      [ 4] 2147 	lda	(_serialBuffer + 0x0007)
   BDF5 CE 01 7F      [ 4] 2148 	ldx	(_serialBuffer + 0x0008)
   BDF8 87            [ 2] 2149 	psha
   BDF9 9F            [ 1] 2150 	txa
   BDFA 9E E7 2A      [ 4] 2151 	sta	42,s
   BDFD 87            [ 2] 2152 	psha
   BDFE 4F            [ 1] 2153 	clra
   BDFF 9E E7 2C      [ 4] 2154 	sta	44,s
   BE02 86            [ 2] 2155 	pula
   BE03 86            [ 2] 2156 	pula
   BE04 5F            [ 1] 2157 	clrx
   BE05 9E EA 2A      [ 4] 2158 	ora	42,s
   BE08 87            [ 2] 2159 	psha
   BE09 9F            [ 1] 2160 	txa
   BE0A 9E EA 2A      [ 4] 2161 	ora	42,s
   BE0D 97            [ 1] 2162 	tax
   BE0E 86            [ 2] 2163 	pula
                           2164 ;comms.c:397: sendPageValues(page, offset, length);
   BE0F 87            [ 2] 2165 	psha
   BE10 89            [ 2] 2166 	pshx
   BE11 95            [ 2] 2167 	tsx
   BE12 E6 36         [ 3] 2168 	lda	54,x
   BE14 87            [ 2] 2169 	psha
   BE15 E6 35         [ 3] 2170 	lda	53,x
   BE17 87            [ 2] 2171 	psha
   BE18 E6 37         [ 3] 2172 	lda	55,x
   BE1A CD C4 4B      [ 5] 2173 	jsr	_sendPageValues
   BE1D A7 04         [ 2] 2174 	ais	#4
   BE1F CC C0 99      [ 3] 2175 	jmp	00130$
   BE22                    2176 00113$:
                           2177 ;comms.c:399: uint8_t err = SERIAL_RC_UKWN_ERR;
   BE22 A6 83         [ 2] 2178 	lda	#0x83
   BE24 9E E7 20      [ 4] 2179 	sta	32,s
                           2180 ;comms.c:400: sendU16BE(1);
   BE27 A6 01         [ 2] 2181 	lda	#0x01
   BE29 5F            [ 1] 2182 	clrx
   BE2A CD B5 75      [ 5] 2183 	jsr	_sendU16BE
                           2184 ;comms.c:401: sendByte(err);
   BE2D 9E E6 20      [ 4] 2185 	lda	32,s
   BE30 CD B5 4F      [ 5] 2186 	jsr	_sendByte
                           2187 ;comms.c:402: sendU32BE(calculateCRC32(&err, 1));
   BE33 95            [ 2] 2188 	tsx
   BE34 AF 1F         [ 2] 2189 	aix	#31
   BE36 A6 01         [ 2] 2190 	lda	#0x01
   BE38 87            [ 2] 2191 	psha
   BE39 4A            [ 1] 2192 	deca
   BE3A 87            [ 2] 2193 	psha
   BE3B 9F            [ 1] 2194 	txa
   BE3C 8B            [ 2] 2195 	pshh
   BE3D 88            [ 2] 2196 	pulx
   BE3E CD B4 C6      [ 5] 2197 	jsr	_calculateCRC32
   BE41 9E E7 2E      [ 4] 2198 	sta	46,s
   BE44 9E EF 2D      [ 4] 2199 	stx	45,s
   BE47 B6 4A         [ 3] 2200 	lda	*___SDCC_hc08_ret2
   BE49 9E E7 2C      [ 4] 2201 	sta	44,s
   BE4C B6 4B         [ 3] 2202 	lda	*___SDCC_hc08_ret3
   BE4E 9E E7 2B      [ 4] 2203 	sta	43,s
   BE51 A7 02         [ 2] 2204 	ais	#2
   BE53 95            [ 2] 2205 	tsx
   BE54 E6 2B         [ 3] 2206 	lda	43,x
   BE56 87            [ 2] 2207 	psha
   BE57 E6 2A         [ 3] 2208 	lda	42,x
   BE59 87            [ 2] 2209 	psha
   BE5A E6 29         [ 3] 2210 	lda	41,x
   BE5C 87            [ 2] 2211 	psha
   BE5D E6 28         [ 3] 2212 	lda	40,x
   BE5F 87            [ 2] 2213 	psha
   BE60 CD B5 83      [ 5] 2214 	jsr	_sendU32BE
   BE63 A7 04         [ 2] 2215 	ais	#4
                           2216 ;comms.c:404: break;
   BE65 CC C0 99      [ 3] 2217 	jmp	00130$
                           2218 ;comms.c:407: case 'M': {
   BE68                    2219 00115$:
                           2220 ;comms.c:408: uint8_t page = payload[2];
   BE68 C6 01 7B      [ 4] 2221 	lda	(_serialBuffer + 0x0004)
   BE6B 9E E7 33      [ 4] 2222 	sta	51,s
                           2223 ;comms.c:409: uint16_t offset = payload[3] | ((uint16_t)payload[4] << 8);
   BE6E C6 01 7C      [ 4] 2224 	lda	(_serialBuffer + 0x0005)
   BE71 CE 01 7D      [ 4] 2225 	ldx	(_serialBuffer + 0x0006)
   BE74 8C            [ 1] 2226 	clrh
   BE75 87            [ 2] 2227 	psha
   BE76 9F            [ 1] 2228 	txa
   BE77 9E E7 2A      [ 4] 2229 	sta	42,s
   BE7A 87            [ 2] 2230 	psha
   BE7B 4F            [ 1] 2231 	clra
   BE7C 9E E7 2C      [ 4] 2232 	sta	44,s
   BE7F 86            [ 2] 2233 	pula
   BE80 86            [ 2] 2234 	pula
   BE81 5F            [ 1] 2235 	clrx
   BE82 9E EA 2A      [ 4] 2236 	ora	42,s
   BE85 9E E7 32      [ 4] 2237 	sta	50,s
   BE88 9F            [ 1] 2238 	txa
   BE89 9E EA 29      [ 4] 2239 	ora	41,s
   BE8C 9E E7 31      [ 4] 2240 	sta	49,s
                           2241 ;comms.c:410: uint16_t length = payload[5] | ((uint16_t)payload[6] << 8);
   BE8F C6 01 7E      [ 4] 2242 	lda	(_serialBuffer + 0x0007)
   BE92 CE 01 7F      [ 4] 2243 	ldx	(_serialBuffer + 0x0008)
   BE95 87            [ 2] 2244 	psha
   BE96 9F            [ 1] 2245 	txa
   BE97 9E E7 2A      [ 4] 2246 	sta	42,s
   BE9A 87            [ 2] 2247 	psha
   BE9B 4F            [ 1] 2248 	clra
   BE9C 9E E7 2C      [ 4] 2249 	sta	44,s
   BE9F 86            [ 2] 2250 	pula
   BEA0 86            [ 2] 2251 	pula
   BEA1 97            [ 1] 2252 	tax
   BEA2 9F            [ 1] 2253 	txa
   BEA3 9E EA 2A      [ 4] 2254 	ora	42,s
   BEA6 97            [ 1] 2255 	tax
   BEA7 8B            [ 2] 2256 	pshh
   BEA8 86            [ 2] 2257 	pula
   BEA9 9E EA 29      [ 4] 2258 	ora	41,s
   BEAC 87            [ 2] 2259 	psha
   BEAD 8A            [ 2] 2260 	pulh
                           2261 ;comms.c:411: uint8_t *data = &payload[7];
                           2262 ;comms.c:412: uint8_t result = writePageValues(page, offset, length, data);
   BEAE A6 80         [ 2] 2263 	lda	#(_serialBuffer + 0x0009)
   BEB0 87            [ 2] 2264 	psha
   BEB1 A6 01         [ 2] 2265 	lda	#>(_serialBuffer + 0x0009)
   BEB3 87            [ 2] 2266 	psha
   BEB4 89            [ 2] 2267 	pshx
   BEB5 8B            [ 2] 2268 	pshh
   BEB6 95            [ 2] 2269 	tsx
   BEB7 E6 35         [ 3] 2270 	lda	53,x
   BEB9 87            [ 2] 2271 	psha
   BEBA E6 34         [ 3] 2272 	lda	52,x
   BEBC 87            [ 2] 2273 	psha
   BEBD E6 36         [ 3] 2274 	lda	54,x
   BEBF CD C6 72      [ 5] 2275 	jsr	_writePageValues
   BEC2 9E E7 26      [ 4] 2276 	sta	38,s
   BEC5 A7 06         [ 2] 2277 	ais	#6
                           2278 ;comms.c:414: sendU16BE(1);
   BEC7 A6 01         [ 2] 2279 	lda	#0x01
   BEC9 5F            [ 1] 2280 	clrx
   BECA CD B5 75      [ 5] 2281 	jsr	_sendU16BE
                           2282 ;comms.c:415: sendByte(result);
   BECD 9E E6 20      [ 4] 2283 	lda	32,s
   BED0 CD B5 4F      [ 5] 2284 	jsr	_sendByte
                           2285 ;comms.c:416: sendU32BE(calculateCRC32(&result, 1));
   BED3 95            [ 2] 2286 	tsx
   BED4 AF 1F         [ 2] 2287 	aix	#31
   BED6 A6 01         [ 2] 2288 	lda	#0x01
   BED8 87            [ 2] 2289 	psha
   BED9 4A            [ 1] 2290 	deca
   BEDA 87            [ 2] 2291 	psha
   BEDB 9F            [ 1] 2292 	txa
   BEDC 8B            [ 2] 2293 	pshh
   BEDD 88            [ 2] 2294 	pulx
   BEDE CD B4 C6      [ 5] 2295 	jsr	_calculateCRC32
   BEE1 9E E7 2E      [ 4] 2296 	sta	46,s
   BEE4 9E EF 2D      [ 4] 2297 	stx	45,s
   BEE7 B6 4A         [ 3] 2298 	lda	*___SDCC_hc08_ret2
   BEE9 9E E7 2C      [ 4] 2299 	sta	44,s
   BEEC B6 4B         [ 3] 2300 	lda	*___SDCC_hc08_ret3
   BEEE 9E E7 2B      [ 4] 2301 	sta	43,s
   BEF1 A7 02         [ 2] 2302 	ais	#2
   BEF3 95            [ 2] 2303 	tsx
   BEF4 E6 2B         [ 3] 2304 	lda	43,x
   BEF6 87            [ 2] 2305 	psha
   BEF7 E6 2A         [ 3] 2306 	lda	42,x
   BEF9 87            [ 2] 2307 	psha
   BEFA E6 29         [ 3] 2308 	lda	41,x
   BEFC 87            [ 2] 2309 	psha
   BEFD E6 28         [ 3] 2310 	lda	40,x
   BEFF 87            [ 2] 2311 	psha
   BF00 CD B5 83      [ 5] 2312 	jsr	_sendU32BE
   BF03 A7 04         [ 2] 2313 	ais	#4
                           2314 ;comms.c:417: break;
   BF05 CC C0 99      [ 3] 2315 	jmp	00130$
                           2316 ;comms.c:420: case 'd': {
   BF08                    2317 00116$:
                           2318 ;comms.c:421: if (payloadLength >= 3) {
   BF08 9E E6 3B      [ 4] 2319 	lda	59,s
   BF0B 9E EE 3A      [ 4] 2320 	ldx	58,s
   BF0E A0 03         [ 2] 2321 	sub	#0x03
   BF10 9F            [ 1] 2322 	txa
   BF11 A2 00         [ 2] 2323 	sbc	#0x00
   BF13 25 09         [ 3] 2324 	bcs	00118$
                           2325 ;comms.c:422: uint8_t page = payload[2];
   BF15 C6 01 7B      [ 4] 2326 	lda	(_serialBuffer + 0x0004)
                           2327 ;comms.c:423: sendPageCRC32(page);
   BF18 CD C6 EF      [ 5] 2328 	jsr	_sendPageCRC32
   BF1B CC C0 99      [ 3] 2329 	jmp	00130$
   BF1E                    2330 00118$:
                           2331 ;comms.c:425: uint8_t err = SERIAL_RC_UKWN_ERR;
   BF1E A6 83         [ 2] 2332 	lda	#0x83
   BF20 9E E7 20      [ 4] 2333 	sta	32,s
                           2334 ;comms.c:426: sendU16BE(1);
   BF23 A6 01         [ 2] 2335 	lda	#0x01
   BF25 5F            [ 1] 2336 	clrx
   BF26 CD B5 75      [ 5] 2337 	jsr	_sendU16BE
                           2338 ;comms.c:427: sendByte(err);
   BF29 9E E6 20      [ 4] 2339 	lda	32,s
   BF2C CD B5 4F      [ 5] 2340 	jsr	_sendByte
                           2341 ;comms.c:428: sendU32BE(calculateCRC32(&err, 1));
   BF2F 95            [ 2] 2342 	tsx
   BF30 AF 1F         [ 2] 2343 	aix	#31
   BF32 A6 01         [ 2] 2344 	lda	#0x01
   BF34 87            [ 2] 2345 	psha
   BF35 4A            [ 1] 2346 	deca
   BF36 87            [ 2] 2347 	psha
   BF37 9F            [ 1] 2348 	txa
   BF38 8B            [ 2] 2349 	pshh
   BF39 88            [ 2] 2350 	pulx
   BF3A CD B4 C6      [ 5] 2351 	jsr	_calculateCRC32
   BF3D 9E E7 2E      [ 4] 2352 	sta	46,s
   BF40 9E EF 2D      [ 4] 2353 	stx	45,s
   BF43 B6 4A         [ 3] 2354 	lda	*___SDCC_hc08_ret2
   BF45 9E E7 2C      [ 4] 2355 	sta	44,s
   BF48 B6 4B         [ 3] 2356 	lda	*___SDCC_hc08_ret3
   BF4A 9E E7 2B      [ 4] 2357 	sta	43,s
   BF4D A7 02         [ 2] 2358 	ais	#2
   BF4F 95            [ 2] 2359 	tsx
   BF50 E6 2B         [ 3] 2360 	lda	43,x
   BF52 87            [ 2] 2361 	psha
   BF53 E6 2A         [ 3] 2362 	lda	42,x
   BF55 87            [ 2] 2363 	psha
   BF56 E6 29         [ 3] 2364 	lda	41,x
   BF58 87            [ 2] 2365 	psha
   BF59 E6 28         [ 3] 2366 	lda	40,x
   BF5B 87            [ 2] 2367 	psha
   BF5C CD B5 83      [ 5] 2368 	jsr	_sendU32BE
   BF5F A7 04         [ 2] 2369 	ais	#4
                           2370 ;comms.c:430: break;
   BF61 CC C0 99      [ 3] 2371 	jmp	00130$
                           2372 ;comms.c:433: case 'r': {
   BF64                    2373 00120$:
                           2374 ;comms.c:434: if (payloadLength >= 7) {
   BF64 9E E6 3B      [ 4] 2375 	lda	59,s
   BF67 9E EE 3A      [ 4] 2376 	ldx	58,s
   BF6A A0 07         [ 2] 2377 	sub	#0x07
   BF6C 9F            [ 1] 2378 	txa
   BF6D A2 00         [ 2] 2379 	sbc	#0x00
   BF6F 25 57         [ 3] 2380 	bcs	00122$
                           2381 ;comms.c:435: uint8_t subcmd = payload[2];
   BF71 C6 01 7B      [ 4] 2382 	lda	(_serialBuffer + 0x0004)
   BF74 9E E7 30      [ 4] 2383 	sta	48,s
                           2384 ;comms.c:436: uint16_t offset = payload[3] | ((uint16_t)payload[4] << 8);
   BF77 C6 01 7C      [ 4] 2385 	lda	(_serialBuffer + 0x0005)
   BF7A CE 01 7D      [ 4] 2386 	ldx	(_serialBuffer + 0x0006)
   BF7D 8C            [ 1] 2387 	clrh
   BF7E 87            [ 2] 2388 	psha
   BF7F 9F            [ 1] 2389 	txa
   BF80 9E E7 2A      [ 4] 2390 	sta	42,s
   BF83 87            [ 2] 2391 	psha
   BF84 4F            [ 1] 2392 	clra
   BF85 9E E7 2C      [ 4] 2393 	sta	44,s
   BF88 86            [ 2] 2394 	pula
   BF89 86            [ 2] 2395 	pula
   BF8A 5F            [ 1] 2396 	clrx
   BF8B 9E EA 2A      [ 4] 2397 	ora	42,s
   BF8E 9E E7 2F      [ 4] 2398 	sta	47,s
   BF91 9F            [ 1] 2399 	txa
   BF92 9E EA 29      [ 4] 2400 	ora	41,s
   BF95 9E E7 2E      [ 4] 2401 	sta	46,s
                           2402 ;comms.c:437: uint16_t length = payload[5] | ((uint16_t)payload[6] << 8);
   BF98 C6 01 7E      [ 4] 2403 	lda	(_serialBuffer + 0x0007)
   BF9B CE 01 7F      [ 4] 2404 	ldx	(_serialBuffer + 0x0008)
   BF9E 87            [ 2] 2405 	psha
   BF9F 9F            [ 1] 2406 	txa
   BFA0 9E E7 2A      [ 4] 2407 	sta	42,s
   BFA3 87            [ 2] 2408 	psha
   BFA4 4F            [ 1] 2409 	clra
   BFA5 9E E7 2C      [ 4] 2410 	sta	44,s
   BFA8 86            [ 2] 2411 	pula
   BFA9 86            [ 2] 2412 	pula
   BFAA 5F            [ 1] 2413 	clrx
   BFAB 9E EA 2A      [ 4] 2414 	ora	42,s
   BFAE 87            [ 2] 2415 	psha
   BFAF 9F            [ 1] 2416 	txa
   BFB0 9E EA 2A      [ 4] 2417 	ora	42,s
   BFB3 97            [ 1] 2418 	tax
   BFB4 86            [ 2] 2419 	pula
                           2420 ;comms.c:438: sendOutputChannels(subcmd, offset, length);
   BFB5 87            [ 2] 2421 	psha
   BFB6 89            [ 2] 2422 	pshx
   BFB7 95            [ 2] 2423 	tsx
   BFB8 E6 30         [ 3] 2424 	lda	48,x
   BFBA 87            [ 2] 2425 	psha
   BFBB E6 2F         [ 3] 2426 	lda	47,x
   BFBD 87            [ 2] 2427 	psha
   BFBE E6 31         [ 3] 2428 	lda	49,x
   BFC0 CD C9 39      [ 5] 2429 	jsr	_sendOutputChannels
   BFC3 A7 04         [ 2] 2430 	ais	#4
   BFC5 CC C0 99      [ 3] 2431 	jmp	00130$
   BFC8                    2432 00122$:
                           2433 ;comms.c:440: uint8_t err = SERIAL_RC_UKWN_ERR;
   BFC8 A6 83         [ 2] 2434 	lda	#0x83
   BFCA 9E E7 20      [ 4] 2435 	sta	32,s
                           2436 ;comms.c:441: sendU16BE(1);
   BFCD A6 01         [ 2] 2437 	lda	#0x01
   BFCF 5F            [ 1] 2438 	clrx
   BFD0 CD B5 75      [ 5] 2439 	jsr	_sendU16BE
                           2440 ;comms.c:442: sendByte(err);
   BFD3 9E E6 20      [ 4] 2441 	lda	32,s
   BFD6 CD B5 4F      [ 5] 2442 	jsr	_sendByte
                           2443 ;comms.c:443: sendU32BE(calculateCRC32(&err, 1));
   BFD9 95            [ 2] 2444 	tsx
   BFDA AF 1F         [ 2] 2445 	aix	#31
   BFDC A6 01         [ 2] 2446 	lda	#0x01
   BFDE 87            [ 2] 2447 	psha
   BFDF 4A            [ 1] 2448 	deca
   BFE0 87            [ 2] 2449 	psha
   BFE1 9F            [ 1] 2450 	txa
   BFE2 8B            [ 2] 2451 	pshh
   BFE3 88            [ 2] 2452 	pulx
   BFE4 CD B4 C6      [ 5] 2453 	jsr	_calculateCRC32
   BFE7 9E E7 2E      [ 4] 2454 	sta	46,s
   BFEA 9E EF 2D      [ 4] 2455 	stx	45,s
   BFED B6 4A         [ 3] 2456 	lda	*___SDCC_hc08_ret2
   BFEF 9E E7 2C      [ 4] 2457 	sta	44,s
   BFF2 B6 4B         [ 3] 2458 	lda	*___SDCC_hc08_ret3
   BFF4 9E E7 2B      [ 4] 2459 	sta	43,s
   BFF7 A7 02         [ 2] 2460 	ais	#2
   BFF9 95            [ 2] 2461 	tsx
   BFFA E6 2B         [ 3] 2462 	lda	43,x
   BFFC 87            [ 2] 2463 	psha
   BFFD E6 2A         [ 3] 2464 	lda	42,x
   BFFF 87            [ 2] 2465 	psha
   C000 E6 29         [ 3] 2466 	lda	41,x
   C002 87            [ 2] 2467 	psha
   C003 E6 28         [ 3] 2468 	lda	40,x
   C005 87            [ 2] 2469 	psha
   C006 CD B5 83      [ 5] 2470 	jsr	_sendU32BE
   C009 A7 04         [ 2] 2471 	ais	#4
                           2472 ;comms.c:445: break;
   C00B CC C0 99      [ 3] 2473 	jmp	00130$
                           2474 ;comms.c:449: case 'B': {
   C00E                    2475 00125$:
                           2476 ;comms.c:450: uint8_t statusByte = SERIAL_RC_BURN_OK;
   C00E A6 04         [ 2] 2477 	lda	#0x04
   C010 9E E7 20      [ 4] 2478 	sta	32,s
                           2479 ;comms.c:451: burnEEPROM();
   C013 CD CA 69      [ 5] 2480 	jsr	_burnEEPROM
                           2481 ;comms.c:452: sendU16BE(1);
   C016 A6 01         [ 2] 2482 	lda	#0x01
   C018 5F            [ 1] 2483 	clrx
   C019 CD B5 75      [ 5] 2484 	jsr	_sendU16BE
                           2485 ;comms.c:453: sendByte(statusByte);
   C01C 9E E6 20      [ 4] 2486 	lda	32,s
   C01F CD B5 4F      [ 5] 2487 	jsr	_sendByte
                           2488 ;comms.c:454: sendU32BE(calculateCRC32(&statusByte, 1));
   C022 95            [ 2] 2489 	tsx
   C023 AF 1F         [ 2] 2490 	aix	#31
   C025 A6 01         [ 2] 2491 	lda	#0x01
   C027 87            [ 2] 2492 	psha
   C028 4A            [ 1] 2493 	deca
   C029 87            [ 2] 2494 	psha
   C02A 9F            [ 1] 2495 	txa
   C02B 8B            [ 2] 2496 	pshh
   C02C 88            [ 2] 2497 	pulx
   C02D CD B4 C6      [ 5] 2498 	jsr	_calculateCRC32
   C030 9E E7 2E      [ 4] 2499 	sta	46,s
   C033 9E EF 2D      [ 4] 2500 	stx	45,s
   C036 B6 4A         [ 3] 2501 	lda	*___SDCC_hc08_ret2
   C038 9E E7 2C      [ 4] 2502 	sta	44,s
   C03B B6 4B         [ 3] 2503 	lda	*___SDCC_hc08_ret3
   C03D 9E E7 2B      [ 4] 2504 	sta	43,s
   C040 A7 02         [ 2] 2505 	ais	#2
   C042 95            [ 2] 2506 	tsx
   C043 E6 2B         [ 3] 2507 	lda	43,x
   C045 87            [ 2] 2508 	psha
   C046 E6 2A         [ 3] 2509 	lda	42,x
   C048 87            [ 2] 2510 	psha
   C049 E6 29         [ 3] 2511 	lda	41,x
   C04B 87            [ 2] 2512 	psha
   C04C E6 28         [ 3] 2513 	lda	40,x
   C04E 87            [ 2] 2514 	psha
   C04F CD B5 83      [ 5] 2515 	jsr	_sendU32BE
   C052 A7 04         [ 2] 2516 	ais	#4
                           2517 ;comms.c:455: break;
   C054 20 43         [ 3] 2518 	bra	00130$
                           2519 ;comms.c:458: default: {
   C056                    2520 00126$:
                           2521 ;comms.c:459: uint8_t err = SERIAL_RC_UKWN_ERR;
   C056 A6 83         [ 2] 2522 	lda	#0x83
   C058 9E E7 20      [ 4] 2523 	sta	32,s
                           2524 ;comms.c:460: sendU16BE(1);
   C05B A6 01         [ 2] 2525 	lda	#0x01
   C05D 5F            [ 1] 2526 	clrx
   C05E CD B5 75      [ 5] 2527 	jsr	_sendU16BE
                           2528 ;comms.c:461: sendByte(err);
   C061 9E E6 20      [ 4] 2529 	lda	32,s
   C064 CD B5 4F      [ 5] 2530 	jsr	_sendByte
                           2531 ;comms.c:462: sendU32BE(calculateCRC32(&err, 1));
   C067 95            [ 2] 2532 	tsx
   C068 AF 1F         [ 2] 2533 	aix	#31
   C06A A6 01         [ 2] 2534 	lda	#0x01
   C06C 87            [ 2] 2535 	psha
   C06D 4A            [ 1] 2536 	deca
   C06E 87            [ 2] 2537 	psha
   C06F 9F            [ 1] 2538 	txa
   C070 8B            [ 2] 2539 	pshh
   C071 88            [ 2] 2540 	pulx
   C072 CD B4 C6      [ 5] 2541 	jsr	_calculateCRC32
   C075 9E E7 2E      [ 4] 2542 	sta	46,s
   C078 9E EF 2D      [ 4] 2543 	stx	45,s
   C07B B6 4A         [ 3] 2544 	lda	*___SDCC_hc08_ret2
   C07D 9E E7 2C      [ 4] 2545 	sta	44,s
   C080 B6 4B         [ 3] 2546 	lda	*___SDCC_hc08_ret3
   C082 9E E7 2B      [ 4] 2547 	sta	43,s
   C085 A7 02         [ 2] 2548 	ais	#2
   C087 95            [ 2] 2549 	tsx
   C088 E6 2B         [ 3] 2550 	lda	43,x
   C08A 87            [ 2] 2551 	psha
   C08B E6 2A         [ 3] 2552 	lda	42,x
   C08D 87            [ 2] 2553 	psha
   C08E E6 29         [ 3] 2554 	lda	41,x
   C090 87            [ 2] 2555 	psha
   C091 E6 28         [ 3] 2556 	lda	40,x
   C093 87            [ 2] 2557 	psha
   C094 CD B5 83      [ 5] 2558 	jsr	_sendU32BE
   C097 A7 04         [ 2] 2559 	ais	#4
                           2560 ;comms.c:465: }
   C099                    2561 00130$:
                           2562 ;comms.c:466: }
   C099 A7 3B         [ 2] 2563 	ais	#59
   C09B 81            [ 4] 2564 	rts
                           2565 ;------------------------------------------------------------
                           2566 ;Allocation info for local variables in function 'getPageSize'
                           2567 ;------------------------------------------------------------
                           2568 ;page                      Allocated to registers a 
                           2569 ;------------------------------------------------------------
                           2570 ;comms.c:471: uint16_t getPageSize(uint8_t page) {
                           2571 ;	-----------------------------------------
                           2572 ;	 function getPageSize
                           2573 ;	-----------------------------------------
                           2574 ;	Register assignment is optimal.
                           2575 ;	Stack space usage: 0 bytes.
   C09C                    2576 _getPageSize:
                           2577 ;comms.c:472: if (page >= PAGE_COUNT) return 0;
   C09C A1 10         [ 2] 2578 	cmp	#0x10
   C09E 25 03         [ 3] 2579 	bcs	00102$
   C0A0 4F            [ 1] 2580 	clra
   C0A1 97            [ 1] 2581 	tax
   C0A2 81            [ 4] 2582 	rts
   C0A3                    2583 00102$:
                           2584 ;comms.c:473: return pageSize[page];
   C0A3 AE 02         [ 2] 2585 	ldx	#0x02
   C0A5 42            [ 5] 2586 	mul
   C0A6 89            [ 2] 2587 	pshx
   C0A7 8A            [ 2] 2588 	pulh
   C0A8 97            [ 1] 2589 	tax
   C0A9 D6 D6 55      [ 4] 2590 	lda	(_pageSize+1),x
   C0AC DE D6 54      [ 4] 2591 	ldx	(_pageSize),x
                           2592 ;comms.c:474: }
   C0AF 81            [ 4] 2593 	rts
                           2594 ;------------------------------------------------------------
                           2595 ;Allocation info for local variables in function 'readStructPageByte'
                           2596 ;------------------------------------------------------------
                           2597 ;size                      Allocated to stack - sp +5
                           2598 ;offset                    Allocated to stack - sp +7
                           2599 ;value                     Allocated to stack - sp +9
                           2600 ;base                      Allocated to registers x h 
                           2601 ;sloc0                     Allocated to stack - sp +1
                           2602 ;------------------------------------------------------------
                           2603 ;comms.c:476: static bool readStructPageByte(const uint8_t *base, uint16_t size, uint16_t offset, uint8_t *value) {
                           2604 ;	-----------------------------------------
                           2605 ;	 function readStructPageByte
                           2606 ;	-----------------------------------------
                           2607 ;	Register assignment is optimal.
                           2608 ;	Stack space usage: 2 bytes.
   C0B0                    2609 _readStructPageByte:
   C0B0 A7 FE         [ 2] 2610 	ais	#-2
   C0B2 89            [ 2] 2611 	pshx
   C0B3 97            [ 1] 2612 	tax
   C0B4 8A            [ 2] 2613 	pulh
                           2614 ;comms.c:477: if (offset >= size) return false;
   C0B5 9E E6 08      [ 4] 2615 	lda	8,s
   C0B8 9E E0 06      [ 4] 2616 	sub	6,s
   C0BB 9E E6 07      [ 4] 2617 	lda	7,s
   C0BE 9E E2 05      [ 4] 2618 	sbc	5,s
   C0C1 25 03         [ 3] 2619 	bcs	00102$
   C0C3 4F            [ 1] 2620 	clra
   C0C4 20 20         [ 3] 2621 	bra	00103$
   C0C6                    2622 00102$:
                           2623 ;comms.c:478: *value = base[offset];
   C0C6 9E E6 09      [ 4] 2624 	lda	9,s
   C0C9 9E E7 01      [ 4] 2625 	sta	1,s
   C0CC 9E E6 0A      [ 4] 2626 	lda	10,s
   C0CF 9E E7 02      [ 4] 2627 	sta	2,s
   C0D2 9F            [ 1] 2628 	txa
   C0D3 9E EB 08      [ 4] 2629 	add	8,s
   C0D6 97            [ 1] 2630 	tax
   C0D7 8B            [ 2] 2631 	pshh
   C0D8 86            [ 2] 2632 	pula
   C0D9 9E E9 07      [ 4] 2633 	adc	7,s
   C0DC 87            [ 2] 2634 	psha
   C0DD 8A            [ 2] 2635 	pulh
   C0DE F6            [ 2] 2636 	lda	,x
   C0DF 8A            [ 2] 2637 	pulh
   C0E0 88            [ 2] 2638 	pulx
   C0E1 89            [ 2] 2639 	pshx
   C0E2 8B            [ 2] 2640 	pshh
   C0E3 F7            [ 2] 2641 	sta	,x
                           2642 ;comms.c:479: return true;
   C0E4 A6 01         [ 2] 2643 	lda	#0x01
   C0E6                    2644 00103$:
                           2645 ;comms.c:480: }
   C0E6 A7 02         [ 2] 2646 	ais	#2
   C0E8 81            [ 4] 2647 	rts
                           2648 ;------------------------------------------------------------
                           2649 ;Allocation info for local variables in function 'writeStructPageByte'
                           2650 ;------------------------------------------------------------
                           2651 ;size                      Allocated to stack - sp +3
                           2652 ;offset                    Allocated to stack - sp +5
                           2653 ;value                     Allocated to stack - sp +7
                           2654 ;base                      Allocated to registers a x 
                           2655 ;------------------------------------------------------------
                           2656 ;comms.c:482: static PageWriteStatus writeStructPageByte(uint8_t *base, uint16_t size, uint16_t offset, uint8_t value) {
                           2657 ;	-----------------------------------------
                           2658 ;	 function writeStructPageByte
                           2659 ;	-----------------------------------------
                           2660 ;	Register assignment is optimal.
                           2661 ;	Stack space usage: 0 bytes.
   C0E9                    2662 _writeStructPageByte:
                           2663 ;comms.c:483: if (offset >= size) return PAGE_WRITE_FAIL;
   C0E9 87            [ 2] 2664 	psha
   C0EA 9E E6 07      [ 4] 2665 	lda	7,s
   C0ED 9E E0 05      [ 4] 2666 	sub	5,s
   C0F0 9E E6 06      [ 4] 2667 	lda	6,s
   C0F3 9E E2 04      [ 4] 2668 	sbc	4,s
   C0F6 86            [ 2] 2669 	pula
   C0F7 25 02         [ 3] 2670 	bcs	00102$
   C0F9 4F            [ 1] 2671 	clra
   C0FA 81            [ 4] 2672 	rts
   C0FB                    2673 00102$:
                           2674 ;comms.c:484: base[offset] = value;
   C0FB 9E EB 06      [ 4] 2675 	add	6,s
   C0FE 87            [ 2] 2676 	psha
   C0FF 9F            [ 1] 2677 	txa
   C100 9E E9 06      [ 4] 2678 	adc	6,s
   C103 97            [ 1] 2679 	tax
   C104 86            [ 2] 2680 	pula
   C105 89            [ 2] 2681 	pshx
   C106 8A            [ 2] 2682 	pulh
   C107 97            [ 1] 2683 	tax
   C108 9E E6 07      [ 4] 2684 	lda	7,s
   C10B F7            [ 2] 2685 	sta	,x
                           2686 ;comms.c:485: return PAGE_WRITE_OK;
   C10C A6 01         [ 2] 2687 	lda	#0x01
                           2688 ;comms.c:486: }
   C10E 81            [ 4] 2689 	rts
                           2690 ;------------------------------------------------------------
                           2691 ;Allocation info for local variables in function 'readStubPageByte'
                           2692 ;------------------------------------------------------------
                           2693 ;offset                    Allocated to stack - sp +3
                           2694 ;value                     Allocated to stack - sp +5
                           2695 ;page                      Allocated to registers a 
                           2696 ;size                      Allocated to registers a x 
                           2697 ;------------------------------------------------------------
                           2698 ;comms.c:488: static bool readStubPageByte(uint8_t page, uint16_t offset, uint8_t *value) {
                           2699 ;	-----------------------------------------
                           2700 ;	 function readStubPageByte
                           2701 ;	-----------------------------------------
                           2702 ;	Register assignment is optimal.
                           2703 ;	Stack space usage: 0 bytes.
   C10F                    2704 _readStubPageByte:
                           2705 ;comms.c:489: uint16_t size = getPageSize(page);
   C10F CD C0 9C      [ 5] 2706 	jsr	_getPageSize
                           2707 ;comms.c:490: if (offset >= size) return false;
   C112 87            [ 2] 2708 	psha
   C113 9E E6 05      [ 4] 2709 	lda	5,s
   C116 9E E0 01      [ 4] 2710 	sub	1, s
   C119 86            [ 2] 2711 	pula
   C11A 9E E6 03      [ 4] 2712 	lda	3,s
   C11D 89            [ 2] 2713 	pshx
   C11E 9E E2 01      [ 4] 2714 	sbc	1,s
   C121 A7 01         [ 2] 2715 	ais	#1
   C123 25 02         [ 3] 2716 	bcs	00102$
   C125 4F            [ 1] 2717 	clra
   C126 81            [ 4] 2718 	rts
   C127                    2719 00102$:
                           2720 ;comms.c:491: *value = 0;
   C127 9E E6 05      [ 4] 2721 	lda	5,s
   C12A 9E EE 06      [ 4] 2722 	ldx	6,s
   C12D 87            [ 2] 2723 	psha
   C12E 8A            [ 2] 2724 	pulh
   C12F 4F            [ 1] 2725 	clra
   C130 F7            [ 2] 2726 	sta	,x
                           2727 ;comms.c:492: return true;
   C131 4C            [ 1] 2728 	inca
                           2729 ;comms.c:493: }
   C132 81            [ 4] 2730 	rts
                           2731 ;------------------------------------------------------------
                           2732 ;Allocation info for local variables in function 'readVeTablePageByte'
                           2733 ;------------------------------------------------------------
                           2734 ;value                     Allocated to stack - sp +7
                           2735 ;offset                    Allocated to registers x h 
                           2736 ;idx                       Allocated to registers a 
                           2737 ;idx                       Allocated to registers a 
                           2738 ;sloc0                     Allocated to stack - sp +3
                           2739 ;sloc1                     Allocated to stack - sp +1
                           2740 ;------------------------------------------------------------
                           2741 ;comms.c:495: static bool readVeTablePageByte(uint16_t offset, uint8_t *value) {
                           2742 ;	-----------------------------------------
                           2743 ;	 function readVeTablePageByte
                           2744 ;	-----------------------------------------
                           2745 ;	Register assignment is optimal.
                           2746 ;	Stack space usage: 4 bytes.
   C133                    2747 _readVeTablePageByte:
   C133 A7 FC         [ 2] 2748 	ais	#-4
   C135 89            [ 2] 2749 	pshx
   C136 97            [ 1] 2750 	tax
   C137 8A            [ 2] 2751 	pulh
                           2752 ;comms.c:496: if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return false;
   C138 65 00 A8      [ 3] 2753 	cphx	#0x00a8
   C13B 25 03         [ 3] 2754 	bcs	00102$
   C13D 4F            [ 1] 2755 	clra
   C13E 20 6C         [ 3] 2756 	bra	00107$
   C140                    2757 00102$:
                           2758 ;comms.c:499: *value = eepromReadByte(veTable.eepromValuesBase + offset);
   C140 9E E6 07      [ 4] 2759 	lda	7,s
   C143 9E E7 03      [ 4] 2760 	sta	3,s
   C146 9E E6 08      [ 4] 2761 	lda	8,s
   C149 9E E7 04      [ 4] 2762 	sta	4,s
                           2763 ;comms.c:498: if (offset < SPEEDUINO_TABLE_CELLS) {
   C14C 65 00 90      [ 3] 2764 	cphx	#0x0090
   C14F 24 28         [ 3] 2765 	bcc	00104$
                           2766 ;comms.c:499: *value = eepromReadByte(veTable.eepromValuesBase + offset);
   C151 C6 01 4B      [ 4] 2767 	lda	(_veTable + 0x0024)
   C154 9E E7 01      [ 4] 2768 	sta	1,s
   C157 C6 01 4C      [ 4] 2769 	lda	((_veTable + 0x0024) + 1)
   C15A 9E E7 02      [ 4] 2770 	sta	2,s
   C15D 9F            [ 1] 2771 	txa
   C15E 9E EB 02      [ 4] 2772 	add	2,s
   C161 87            [ 2] 2773 	psha
   C162 8B            [ 2] 2774 	pshh
   C163 86            [ 2] 2775 	pula
   C164 9E E9 02      [ 4] 2776 	adc	2,s
   C167 97            [ 1] 2777 	tax
   C168 86            [ 2] 2778 	pula
   C169 CD 97 6A      [ 5] 2779 	jsr	_eepromReadByte
   C16C 9E EE 03      [ 4] 2780 	ldx	3,s
   C16F 89            [ 2] 2781 	pshx
   C170 8A            [ 2] 2782 	pulh
   C171 9E EE 04      [ 4] 2783 	ldx	4,s
   C174 F7            [ 2] 2784 	sta	,x
                           2785 ;comms.c:500: return true;
   C175 A6 01         [ 2] 2786 	lda	#0x01
   C177 20 33         [ 3] 2787 	bra	00107$
   C179                    2788 00104$:
                           2789 ;comms.c:503: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
   C179 9F            [ 1] 2790 	txa
                           2791 ;comms.c:502: if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
   C17A 65 00 9C      [ 3] 2792 	cphx	#0x009c
   C17D 24 1B         [ 3] 2793 	bcc	00106$
                           2794 ;comms.c:503: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
   C17F A0 90         [ 2] 2795 	sub	#0x90
                           2796 ;comms.c:504: *value = encodeRpmBin(veTable.axisX[idx]);
   C181 48            [ 1] 2797 	lsla	
   C182 97            [ 1] 2798 	tax
   C183 8C            [ 1] 2799 	clrh
   C184 D6 01 28      [ 4] 2800 	lda	(_veTable+1),x
   C187 DE 01 27      [ 4] 2801 	ldx	(_veTable),x
   C18A CD B4 97      [ 5] 2802 	jsr	_encodeRpmBin
   C18D 9E EE 03      [ 4] 2803 	ldx	3,s
   C190 89            [ 2] 2804 	pshx
   C191 8A            [ 2] 2805 	pulh
   C192 9E EE 04      [ 4] 2806 	ldx	4,s
   C195 F7            [ 2] 2807 	sta	,x
                           2808 ;comms.c:505: return true;
   C196 A6 01         [ 2] 2809 	lda	#0x01
   C198 20 12         [ 3] 2810 	bra	00107$
   C19A                    2811 00106$:
                           2812 ;comms.c:508: uint8_t idx = (uint8_t)(offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN));
   C19A A0 9C         [ 2] 2813 	sub	#0x9c
                           2814 ;comms.c:509: *value = veTable.axisY[idx];
   C19C 97            [ 1] 2815 	tax
   C19D 8C            [ 1] 2816 	clrh
   C19E D6 01 3F      [ 4] 2817 	lda	((_veTable + 0x0018)),x
   C1A1 9E EE 03      [ 4] 2818 	ldx	3,s
   C1A4 89            [ 2] 2819 	pshx
   C1A5 8A            [ 2] 2820 	pulh
   C1A6 9E EE 04      [ 4] 2821 	ldx	4,s
   C1A9 F7            [ 2] 2822 	sta	,x
                           2823 ;comms.c:510: return true;
   C1AA A6 01         [ 2] 2824 	lda	#0x01
   C1AC                    2825 00107$:
                           2826 ;comms.c:512: }
   C1AC A7 04         [ 2] 2827 	ais	#4
   C1AE 81            [ 4] 2828 	rts
                           2829 ;------------------------------------------------------------
                           2830 ;Allocation info for local variables in function 'writeVeTablePageByte'
                           2831 ;------------------------------------------------------------
                           2832 ;value                     Allocated to stack - sp +5
                           2833 ;offset                    Allocated to registers x h 
                           2834 ;idx                       Allocated to registers a 
                           2835 ;idx                       Allocated to registers a 
                           2836 ;sloc0                     Allocated to stack - sp +1
                           2837 ;------------------------------------------------------------
                           2838 ;comms.c:514: static PageWriteStatus writeVeTablePageByte(uint16_t offset, uint8_t value) {
                           2839 ;	-----------------------------------------
                           2840 ;	 function writeVeTablePageByte
                           2841 ;	-----------------------------------------
                           2842 ;	Register assignment is optimal.
                           2843 ;	Stack space usage: 2 bytes.
   C1AF                    2844 _writeVeTablePageByte:
   C1AF A7 FE         [ 2] 2845 	ais	#-2
   C1B1 89            [ 2] 2846 	pshx
   C1B2 97            [ 1] 2847 	tax
   C1B3 8A            [ 2] 2848 	pulh
                           2849 ;comms.c:515: if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return PAGE_WRITE_FAIL;
   C1B4 65 00 A8      [ 3] 2850 	cphx	#0x00a8
   C1B7 25 03         [ 3] 2851 	bcs	00102$
   C1B9 4F            [ 1] 2852 	clra
   C1BA 20 64         [ 3] 2853 	bra	00107$
   C1BC                    2854 00102$:
                           2855 ;comms.c:517: if (offset < SPEEDUINO_TABLE_CELLS) {
   C1BC 65 00 90      [ 3] 2856 	cphx	#0x0090
   C1BF 24 28         [ 3] 2857 	bcc	00104$
                           2858 ;comms.c:518: eepromWriteByte(veTable.eepromValuesBase + offset, value);
   C1C1 C6 01 4B      [ 4] 2859 	lda	(_veTable + 0x0024)
   C1C4 9E E7 01      [ 4] 2860 	sta	1,s
   C1C7 C6 01 4C      [ 4] 2861 	lda	((_veTable + 0x0024) + 1)
   C1CA 9E E7 02      [ 4] 2862 	sta	2,s
   C1CD 9F            [ 1] 2863 	txa
   C1CE 9E EB 02      [ 4] 2864 	add	2,s
   C1D1 97            [ 1] 2865 	tax
   C1D2 8B            [ 2] 2866 	pshh
   C1D3 86            [ 2] 2867 	pula
   C1D4 9E E9 01      [ 4] 2868 	adc	1,s
   C1D7 87            [ 2] 2869 	psha
   C1D8 8A            [ 2] 2870 	pulh
   C1D9 9E E6 05      [ 4] 2871 	lda	5,s
   C1DC 87            [ 2] 2872 	psha
   C1DD 9F            [ 1] 2873 	txa
   C1DE 8B            [ 2] 2874 	pshh
   C1DF 88            [ 2] 2875 	pulx
   C1E0 CD 97 6F      [ 5] 2876 	jsr	_eepromWriteByte
   C1E3 A7 01         [ 2] 2877 	ais	#1
                           2878 ;comms.c:519: return PAGE_WRITE_TABLE_CHANGED;
   C1E5 A6 02         [ 2] 2879 	lda	#0x02
   C1E7 20 37         [ 3] 2880 	bra	00107$
   C1E9                    2881 00104$:
                           2882 ;comms.c:522: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
   C1E9 9F            [ 1] 2883 	txa
                           2884 ;comms.c:521: if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
   C1EA 65 00 9C      [ 3] 2885 	cphx	#0x009c
   C1ED 24 25         [ 3] 2886 	bcc	00106$
                           2887 ;comms.c:522: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
   C1EF A0 90         [ 2] 2888 	sub	#0x90
                           2889 ;comms.c:523: veTable.axisX[idx] = decodeRpmBin(value);
   C1F1 48            [ 1] 2890 	lsla	
   C1F2 97            [ 1] 2891 	tax
   C1F3 8C            [ 1] 2892 	clrh
   C1F4 89            [ 2] 2893 	pshx
   C1F5 8B            [ 2] 2894 	pshh
   C1F6 9E E6 07      [ 4] 2895 	lda	7,s
   C1F9 CD B4 AA      [ 5] 2896 	jsr	_decodeRpmBin
   C1FC 9E E7 04      [ 4] 2897 	sta	4,s
   C1FF 9E EF 03      [ 4] 2898 	stx	3,s
   C202 8A            [ 2] 2899 	pulh
   C203 88            [ 2] 2900 	pulx
   C204 9E E6 01      [ 4] 2901 	lda	1,s
   C207 D7 01 27      [ 4] 2902 	sta	(_veTable),x
   C20A 9E E6 02      [ 4] 2903 	lda	2,s
   C20D D7 01 28      [ 4] 2904 	sta	(_veTable+1),x
                           2905 ;comms.c:524: return PAGE_WRITE_TABLE_CHANGED;
   C210 A6 02         [ 2] 2906 	lda	#0x02
   C212 20 0C         [ 3] 2907 	bra	00107$
   C214                    2908 00106$:
                           2909 ;comms.c:527: uint8_t idx = (uint8_t)(offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN));
   C214 A0 9C         [ 2] 2910 	sub	#0x9c
                           2911 ;comms.c:528: veTable.axisY[idx] = value;
   C216 97            [ 1] 2912 	tax
   C217 8C            [ 1] 2913 	clrh
   C218 9E E6 05      [ 4] 2914 	lda	5,s
   C21B D7 01 3F      [ 4] 2915 	sta	((_veTable + 0x0018)),x
                           2916 ;comms.c:529: return PAGE_WRITE_TABLE_CHANGED;
   C21E A6 02         [ 2] 2917 	lda	#0x02
   C220                    2918 00107$:
                           2919 ;comms.c:531: }
   C220 A7 02         [ 2] 2920 	ais	#2
   C222 81            [ 4] 2921 	rts
                           2922 ;------------------------------------------------------------
                           2923 ;Allocation info for local variables in function 'readIgnTablePageByte'
                           2924 ;------------------------------------------------------------
                           2925 ;value                     Allocated to stack - sp +7
                           2926 ;offset                    Allocated to registers x h 
                           2927 ;cellValue                 Allocated to registers a 
                           2928 ;idx                       Allocated to registers a 
                           2929 ;idx                       Allocated to registers a 
                           2930 ;sloc0                     Allocated to stack - sp +3
                           2931 ;sloc1                     Allocated to stack - sp +1
                           2932 ;------------------------------------------------------------
                           2933 ;comms.c:533: static bool readIgnTablePageByte(uint16_t offset, uint8_t *value) {
                           2934 ;	-----------------------------------------
                           2935 ;	 function readIgnTablePageByte
                           2936 ;	-----------------------------------------
                           2937 ;	Register assignment is optimal.
                           2938 ;	Stack space usage: 4 bytes.
   C223                    2939 _readIgnTablePageByte:
   C223 A7 FC         [ 2] 2940 	ais	#-4
   C225 89            [ 2] 2941 	pshx
   C226 97            [ 1] 2942 	tax
   C227 8A            [ 2] 2943 	pulh
                           2944 ;comms.c:534: if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return false;
   C228 65 00 A8      [ 3] 2945 	cphx	#0x00a8
   C22B 25 03         [ 3] 2946 	bcs	00102$
   C22D 4F            [ 1] 2947 	clra
   C22E 20 6F         [ 3] 2948 	bra	00107$
   C230                    2949 00102$:
                           2950 ;comms.c:538: *value = encodeIgnitionValue(cellValue);
   C230 9E E6 07      [ 4] 2951 	lda	7,s
   C233 9E E7 03      [ 4] 2952 	sta	3,s
   C236 9E E6 08      [ 4] 2953 	lda	8,s
   C239 9E E7 04      [ 4] 2954 	sta	4,s
                           2955 ;comms.c:536: if (offset < SPEEDUINO_TABLE_CELLS) {
   C23C 65 00 90      [ 3] 2956 	cphx	#0x0090
   C23F 24 2B         [ 3] 2957 	bcc	00104$
                           2958 ;comms.c:537: int8_t cellValue = eepromReadI8(ignTable.eepromValuesBase + offset);
   C241 C6 01 72      [ 4] 2959 	lda	(_ignTable + 0x0024)
   C244 9E E7 01      [ 4] 2960 	sta	1,s
   C247 C6 01 73      [ 4] 2961 	lda	((_ignTable + 0x0024) + 1)
   C24A 9E E7 02      [ 4] 2962 	sta	2,s
   C24D 9F            [ 1] 2963 	txa
   C24E 9E EB 02      [ 4] 2964 	add	2,s
   C251 87            [ 2] 2965 	psha
   C252 8B            [ 2] 2966 	pshh
   C253 86            [ 2] 2967 	pula
   C254 9E E9 02      [ 4] 2968 	adc	2,s
   C257 97            [ 1] 2969 	tax
   C258 86            [ 2] 2970 	pula
   C259 CD 97 6D      [ 5] 2971 	jsr	_eepromReadI8
                           2972 ;comms.c:538: *value = encodeIgnitionValue(cellValue);
   C25C CD B4 85      [ 5] 2973 	jsr	_encodeIgnitionValue
   C25F 9E EE 03      [ 4] 2974 	ldx	3,s
   C262 89            [ 2] 2975 	pshx
   C263 8A            [ 2] 2976 	pulh
   C264 9E EE 04      [ 4] 2977 	ldx	4,s
   C267 F7            [ 2] 2978 	sta	,x
                           2979 ;comms.c:539: return true;
   C268 A6 01         [ 2] 2980 	lda	#0x01
   C26A 20 33         [ 3] 2981 	bra	00107$
   C26C                    2982 00104$:
                           2983 ;comms.c:542: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
   C26C 9F            [ 1] 2984 	txa
                           2985 ;comms.c:541: if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
   C26D 65 00 9C      [ 3] 2986 	cphx	#0x009c
   C270 24 1B         [ 3] 2987 	bcc	00106$
                           2988 ;comms.c:542: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
   C272 A0 90         [ 2] 2989 	sub	#0x90
                           2990 ;comms.c:543: *value = encodeRpmBin(ignTable.axisX[idx]);
   C274 48            [ 1] 2991 	lsla	
   C275 97            [ 1] 2992 	tax
   C276 8C            [ 1] 2993 	clrh
   C277 D6 01 4F      [ 4] 2994 	lda	(_ignTable+1),x
   C27A DE 01 4E      [ 4] 2995 	ldx	(_ignTable),x
   C27D CD B4 97      [ 5] 2996 	jsr	_encodeRpmBin
   C280 9E EE 03      [ 4] 2997 	ldx	3,s
   C283 89            [ 2] 2998 	pshx
   C284 8A            [ 2] 2999 	pulh
   C285 9E EE 04      [ 4] 3000 	ldx	4,s
   C288 F7            [ 2] 3001 	sta	,x
                           3002 ;comms.c:544: return true;
   C289 A6 01         [ 2] 3003 	lda	#0x01
   C28B 20 12         [ 3] 3004 	bra	00107$
   C28D                    3005 00106$:
                           3006 ;comms.c:547: uint8_t idx = (uint8_t)(offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN));
   C28D A0 9C         [ 2] 3007 	sub	#0x9c
                           3008 ;comms.c:548: *value = ignTable.axisY[idx];
   C28F 97            [ 1] 3009 	tax
   C290 8C            [ 1] 3010 	clrh
   C291 D6 01 66      [ 4] 3011 	lda	((_ignTable + 0x0018)),x
   C294 9E EE 03      [ 4] 3012 	ldx	3,s
   C297 89            [ 2] 3013 	pshx
   C298 8A            [ 2] 3014 	pulh
   C299 9E EE 04      [ 4] 3015 	ldx	4,s
   C29C F7            [ 2] 3016 	sta	,x
                           3017 ;comms.c:549: return true;
   C29D A6 01         [ 2] 3018 	lda	#0x01
   C29F                    3019 00107$:
                           3020 ;comms.c:551: }
   C29F A7 04         [ 2] 3021 	ais	#4
   C2A1 81            [ 4] 3022 	rts
                           3023 ;------------------------------------------------------------
                           3024 ;Allocation info for local variables in function 'writeIgnTablePageByte'
                           3025 ;------------------------------------------------------------
                           3026 ;value                     Allocated to stack - sp +5
                           3027 ;offset                    Allocated to registers x h 
                           3028 ;idx                       Allocated to registers a 
                           3029 ;idx                       Allocated to registers a 
                           3030 ;sloc0                     Allocated to stack - sp +1
                           3031 ;------------------------------------------------------------
                           3032 ;comms.c:553: static PageWriteStatus writeIgnTablePageByte(uint16_t offset, uint8_t value) {
                           3033 ;	-----------------------------------------
                           3034 ;	 function writeIgnTablePageByte
                           3035 ;	-----------------------------------------
                           3036 ;	Register assignment is optimal.
                           3037 ;	Stack space usage: 2 bytes.
   C2A2                    3038 _writeIgnTablePageByte:
   C2A2 A7 FE         [ 2] 3039 	ais	#-2
   C2A4 89            [ 2] 3040 	pshx
   C2A5 97            [ 1] 3041 	tax
   C2A6 8A            [ 2] 3042 	pulh
                           3043 ;comms.c:554: if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return PAGE_WRITE_FAIL;
   C2A7 65 00 A8      [ 3] 3044 	cphx	#0x00a8
   C2AA 25 03         [ 3] 3045 	bcs	00102$
   C2AC 4F            [ 1] 3046 	clra
   C2AD 20 6F         [ 3] 3047 	bra	00107$
   C2AF                    3048 00102$:
                           3049 ;comms.c:556: if (offset < SPEEDUINO_TABLE_CELLS) {
   C2AF 65 00 90      [ 3] 3050 	cphx	#0x0090
   C2B2 24 33         [ 3] 3051 	bcc	00104$
                           3052 ;comms.c:557: eepromWriteI8(ignTable.eepromValuesBase + offset, decodeIgnitionValue(value));
   C2B4 89            [ 2] 3053 	pshx
   C2B5 8B            [ 2] 3054 	pshh
   C2B6 9E E6 07      [ 4] 3055 	lda	7,s
   C2B9 CD B4 94      [ 5] 3056 	jsr	_decodeIgnitionValue
   C2BC 8A            [ 2] 3057 	pulh
   C2BD 88            [ 2] 3058 	pulx
   C2BE 87            [ 2] 3059 	psha
   C2BF C6 01 72      [ 4] 3060 	lda	(_ignTable + 0x0024)
   C2C2 9E E7 02      [ 4] 3061 	sta	2,s
   C2C5 C6 01 73      [ 4] 3062 	lda	((_ignTable + 0x0024) + 1)
   C2C8 9E E7 03      [ 4] 3063 	sta	3,s
   C2CB 86            [ 2] 3064 	pula
   C2CC 87            [ 2] 3065 	psha
   C2CD 9F            [ 1] 3066 	txa
   C2CE 9E EB 03      [ 4] 3067 	add	3,s
   C2D1 97            [ 1] 3068 	tax
   C2D2 8B            [ 2] 3069 	pshh
   C2D3 86            [ 2] 3070 	pula
   C2D4 9E E9 02      [ 4] 3071 	adc	2,s
   C2D7 87            [ 2] 3072 	psha
   C2D8 8A            [ 2] 3073 	pulh
   C2D9 86            [ 2] 3074 	pula
   C2DA 87            [ 2] 3075 	psha
   C2DB 9F            [ 1] 3076 	txa
   C2DC 8B            [ 2] 3077 	pshh
   C2DD 88            [ 2] 3078 	pulx
   C2DE CD 97 71      [ 5] 3079 	jsr	_eepromWriteI8
   C2E1 A7 01         [ 2] 3080 	ais	#1
                           3081 ;comms.c:558: return PAGE_WRITE_TABLE_CHANGED;
   C2E3 A6 02         [ 2] 3082 	lda	#0x02
   C2E5 20 37         [ 3] 3083 	bra	00107$
   C2E7                    3084 00104$:
                           3085 ;comms.c:561: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
   C2E7 9F            [ 1] 3086 	txa
                           3087 ;comms.c:560: if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
   C2E8 65 00 9C      [ 3] 3088 	cphx	#0x009c
   C2EB 24 25         [ 3] 3089 	bcc	00106$
                           3090 ;comms.c:561: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
   C2ED A0 90         [ 2] 3091 	sub	#0x90
                           3092 ;comms.c:562: ignTable.axisX[idx] = decodeRpmBin(value);
   C2EF 48            [ 1] 3093 	lsla	
   C2F0 97            [ 1] 3094 	tax
   C2F1 8C            [ 1] 3095 	clrh
   C2F2 89            [ 2] 3096 	pshx
   C2F3 8B            [ 2] 3097 	pshh
   C2F4 9E E6 07      [ 4] 3098 	lda	7,s
   C2F7 CD B4 AA      [ 5] 3099 	jsr	_decodeRpmBin
   C2FA 9E E7 04      [ 4] 3100 	sta	4,s
   C2FD 9E EF 03      [ 4] 3101 	stx	3,s
   C300 8A            [ 2] 3102 	pulh
   C301 88            [ 2] 3103 	pulx
   C302 9E E6 01      [ 4] 3104 	lda	1,s
   C305 D7 01 4E      [ 4] 3105 	sta	(_ignTable),x
   C308 9E E6 02      [ 4] 3106 	lda	2,s
   C30B D7 01 4F      [ 4] 3107 	sta	(_ignTable+1),x
                           3108 ;comms.c:563: return PAGE_WRITE_TABLE_CHANGED;
   C30E A6 02         [ 2] 3109 	lda	#0x02
   C310 20 0C         [ 3] 3110 	bra	00107$
   C312                    3111 00106$:
                           3112 ;comms.c:566: uint8_t idx = (uint8_t)(offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN));
   C312 A0 9C         [ 2] 3113 	sub	#0x9c
                           3114 ;comms.c:567: ignTable.axisY[idx] = value;
   C314 97            [ 1] 3115 	tax
   C315 8C            [ 1] 3116 	clrh
   C316 9E E6 05      [ 4] 3117 	lda	5,s
   C319 D7 01 66      [ 4] 3118 	sta	((_ignTable + 0x0018)),x
                           3119 ;comms.c:568: return PAGE_WRITE_TABLE_CHANGED;
   C31C A6 02         [ 2] 3120 	lda	#0x02
   C31E                    3121 00107$:
                           3122 ;comms.c:570: }
   C31E A7 02         [ 2] 3123 	ais	#2
   C320 81            [ 4] 3124 	rts
                           3125 ;------------------------------------------------------------
                           3126 ;Allocation info for local variables in function 'readPageByte'
                           3127 ;------------------------------------------------------------
                           3128 ;offset                    Allocated to stack - sp +4
                           3129 ;value                     Allocated to stack - sp +6
                           3130 ;page                      Allocated to stack - sp +1
                           3131 ;------------------------------------------------------------
                           3132 ;comms.c:572: static bool readPageByte(uint8_t page, uint16_t offset, uint8_t *value) {
                           3133 ;	-----------------------------------------
                           3134 ;	 function readPageByte
                           3135 ;	-----------------------------------------
                           3136 ;	Register assignment is optimal.
                           3137 ;	Stack space usage: 1 bytes.
   C321                    3138 _readPageByte:
   C321 87            [ 2] 3139 	psha
                           3140 ;comms.c:573: switch (page) {
   C322 9E E6 01      [ 4] 3141 	lda	1,s
   C325 A1 04         [ 2] 3142 	cmp	#0x04
   C327 22 75         [ 3] 3143 	bhi	00105$
   C329 9E EE 01      [ 4] 3144 	ldx	1,s
   C32C 8C            [ 1] 3145 	clrh
   C32D D6 C3 3B      [ 4] 3146 	lda	00116$,x
   C330 DE C3 36      [ 4] 3147 	ldx	00115$,x
   C333 87            [ 2] 3148 	psha
   C334 8A            [ 2] 3149 	pulh
   C335 FC            [ 2] 3150 	jmp	,x
   C336                    3151 00115$:
   C336 9E                 3152 	.db	00105$
   C337 40                 3153 	.db	00101$
   C338 5D                 3154 	.db	00102$
   C339 6F                 3155 	.db	00103$
   C33A 81                 3156 	.db	00104$
   C33B                    3157 00116$:
   C33B C3                 3158 	.db	>00105$
   C33C C3                 3159 	.db	>00101$
   C33D C3                 3160 	.db	>00102$
   C33E C3                 3161 	.db	>00103$
   C33F C3                 3162 	.db	>00104$
                           3163 ;comms.c:574: case 1: return readStructPageByte((uint8_t *)&configPage1, sizeof(struct ConfigPage1), offset, value);
   C340                    3164 00101$:
   C340 95            [ 2] 3165 	tsx
   C341 E6 06         [ 3] 3166 	lda	6,x
   C343 87            [ 2] 3167 	psha
   C344 E6 05         [ 3] 3168 	lda	5,x
   C346 87            [ 2] 3169 	psha
   C347 E6 04         [ 3] 3170 	lda	4,x
   C349 87            [ 2] 3171 	psha
   C34A E6 03         [ 3] 3172 	lda	3,x
   C34C 87            [ 2] 3173 	psha
   C34D A6 1E         [ 2] 3174 	lda	#0x1e
   C34F 87            [ 2] 3175 	psha
   C350 4F            [ 1] 3176 	clra
   C351 87            [ 2] 3177 	psha
   C352 A6 9C         [ 2] 3178 	lda	#_configPage1
   C354 AE 00         [ 2] 3179 	ldx	#>_configPage1
   C356 CD C0 B0      [ 5] 3180 	jsr	_readStructPageByte
   C359 A7 06         [ 2] 3181 	ais	#6
   C35B 20 54         [ 3] 3182 	bra	00107$
                           3183 ;comms.c:575: case 2: return readVeTablePageByte(offset, value);
   C35D                    3184 00102$:
   C35D 95            [ 2] 3185 	tsx
   C35E E6 06         [ 3] 3186 	lda	6,x
   C360 87            [ 2] 3187 	psha
   C361 E6 05         [ 3] 3188 	lda	5,x
   C363 87            [ 2] 3189 	psha
   C364 E6 04         [ 3] 3190 	lda	4,x
   C366 EE 03         [ 3] 3191 	ldx	3,x
   C368 CD C1 33      [ 5] 3192 	jsr	_readVeTablePageByte
   C36B A7 02         [ 2] 3193 	ais	#2
   C36D 20 42         [ 3] 3194 	bra	00107$
                           3195 ;comms.c:576: case 3: return readIgnTablePageByte(offset, value);
   C36F                    3196 00103$:
   C36F 95            [ 2] 3197 	tsx
   C370 E6 06         [ 3] 3198 	lda	6,x
   C372 87            [ 2] 3199 	psha
   C373 E6 05         [ 3] 3200 	lda	5,x
   C375 87            [ 2] 3201 	psha
   C376 E6 04         [ 3] 3202 	lda	4,x
   C378 EE 03         [ 3] 3203 	ldx	3,x
   C37A CD C2 23      [ 5] 3204 	jsr	_readIgnTablePageByte
   C37D A7 02         [ 2] 3205 	ais	#2
   C37F 20 30         [ 3] 3206 	bra	00107$
                           3207 ;comms.c:577: case 4: return readStructPageByte((uint8_t *)&configPage2, sizeof(struct ConfigPage2), offset, value);
   C381                    3208 00104$:
   C381 95            [ 2] 3209 	tsx
   C382 E6 06         [ 3] 3210 	lda	6,x
   C384 87            [ 2] 3211 	psha
   C385 E6 05         [ 3] 3212 	lda	5,x
   C387 87            [ 2] 3213 	psha
   C388 E6 04         [ 3] 3214 	lda	4,x
   C38A 87            [ 2] 3215 	psha
   C38B E6 03         [ 3] 3216 	lda	3,x
   C38D 87            [ 2] 3217 	psha
   C38E A6 20         [ 2] 3218 	lda	#0x20
   C390 87            [ 2] 3219 	psha
   C391 4F            [ 1] 3220 	clra
   C392 87            [ 2] 3221 	psha
   C393 A6 BA         [ 2] 3222 	lda	#_configPage2
   C395 AE 00         [ 2] 3223 	ldx	#>_configPage2
   C397 CD C0 B0      [ 5] 3224 	jsr	_readStructPageByte
   C39A A7 06         [ 2] 3225 	ais	#6
   C39C 20 13         [ 3] 3226 	bra	00107$
                           3227 ;comms.c:578: default: return readStubPageByte(page, offset, value);
   C39E                    3228 00105$:
   C39E 95            [ 2] 3229 	tsx
   C39F E6 06         [ 3] 3230 	lda	6,x
   C3A1 87            [ 2] 3231 	psha
   C3A2 E6 05         [ 3] 3232 	lda	5,x
   C3A4 87            [ 2] 3233 	psha
   C3A5 E6 04         [ 3] 3234 	lda	4,x
   C3A7 87            [ 2] 3235 	psha
   C3A8 E6 03         [ 3] 3236 	lda	3,x
   C3AA 87            [ 2] 3237 	psha
   C3AB F6            [ 2] 3238 	lda	,x
   C3AC CD C1 0F      [ 5] 3239 	jsr	_readStubPageByte
   C3AF A7 04         [ 2] 3240 	ais	#4
                           3241 ;comms.c:579: }
   C3B1                    3242 00107$:
                           3243 ;comms.c:580: }
   C3B1 A7 01         [ 2] 3244 	ais	#1
   C3B3 81            [ 4] 3245 	rts
                           3246 ;------------------------------------------------------------
                           3247 ;Allocation info for local variables in function 'writePageByte'
                           3248 ;------------------------------------------------------------
                           3249 ;offset                    Allocated to stack - sp +6
                           3250 ;value                     Allocated to stack - sp +8
                           3251 ;page                      Allocated to stack - sp +3
                           3252 ;pageSz                    Allocated to stack - sp +1
                           3253 ;sloc0                     Allocated to stack - sp +1
                           3254 ;------------------------------------------------------------
                           3255 ;comms.c:582: static PageWriteStatus writePageByte(uint8_t page, uint16_t offset, uint8_t value) {
                           3256 ;	-----------------------------------------
                           3257 ;	 function writePageByte
                           3258 ;	-----------------------------------------
                           3259 ;	Register assignment is optimal.
                           3260 ;	Stack space usage: 3 bytes.
   C3B4                    3261 _writePageByte:
   C3B4 87            [ 2] 3262 	psha
   C3B5 A7 FE         [ 2] 3263 	ais	#-2
                           3264 ;comms.c:583: switch (page) {
   C3B7 9E E6 03      [ 4] 3265 	lda	3,s
   C3BA A1 04         [ 2] 3266 	cmp	#0x04
   C3BC 22 69         [ 3] 3267 	bhi	00105$
   C3BE 9E EE 03      [ 4] 3268 	ldx	3,s
   C3C1 8C            [ 1] 3269 	clrh
   C3C2 D6 C3 D0      [ 4] 3270 	lda	00124$,x
   C3C5 DE C3 CB      [ 4] 3271 	ldx	00123$,x
   C3C8 87            [ 2] 3272 	psha
   C3C9 8A            [ 2] 3273 	pulh
   C3CA FC            [ 2] 3274 	jmp	,x
   C3CB                    3275 00123$:
   C3CB 27                 3276 	.db	00105$
   C3CC D5                 3277 	.db	00101$
   C3CD EF                 3278 	.db	00102$
   C3CE FE                 3279 	.db	00103$
   C3CF 0D                 3280 	.db	00104$
   C3D0                    3281 00124$:
   C3D0 C4                 3282 	.db	>00105$
   C3D1 C3                 3283 	.db	>00101$
   C3D2 C3                 3284 	.db	>00102$
   C3D3 C3                 3285 	.db	>00103$
   C3D4 C4                 3286 	.db	>00104$
                           3287 ;comms.c:584: case 1: return writeStructPageByte((uint8_t *)&configPage1, sizeof(struct ConfigPage1), offset, value);
   C3D5                    3288 00101$:
   C3D5 95            [ 2] 3289 	tsx
   C3D6 E6 07         [ 3] 3290 	lda	7,x
   C3D8 87            [ 2] 3291 	psha
   C3D9 E6 06         [ 3] 3292 	lda	6,x
   C3DB 87            [ 2] 3293 	psha
   C3DC E6 05         [ 3] 3294 	lda	5,x
   C3DE 87            [ 2] 3295 	psha
   C3DF A6 1E         [ 2] 3296 	lda	#0x1e
   C3E1 87            [ 2] 3297 	psha
   C3E2 4F            [ 1] 3298 	clra
   C3E3 87            [ 2] 3299 	psha
   C3E4 A6 9C         [ 2] 3300 	lda	#_configPage1
   C3E6 AE 00         [ 2] 3301 	ldx	#>_configPage1
   C3E8 CD C0 E9      [ 5] 3302 	jsr	_writeStructPageByte
   C3EB A7 05         [ 2] 3303 	ais	#5
   C3ED 20 59         [ 3] 3304 	bra	00110$
                           3305 ;comms.c:585: case 2: return writeVeTablePageByte(offset, value);
   C3EF                    3306 00102$:
   C3EF 95            [ 2] 3307 	tsx
   C3F0 E6 07         [ 3] 3308 	lda	7,x
   C3F2 87            [ 2] 3309 	psha
   C3F3 E6 06         [ 3] 3310 	lda	6,x
   C3F5 EE 05         [ 3] 3311 	ldx	5,x
   C3F7 CD C1 AF      [ 5] 3312 	jsr	_writeVeTablePageByte
   C3FA A7 01         [ 2] 3313 	ais	#1
   C3FC 20 4A         [ 3] 3314 	bra	00110$
                           3315 ;comms.c:586: case 3: return writeIgnTablePageByte(offset, value);
   C3FE                    3316 00103$:
   C3FE 95            [ 2] 3317 	tsx
   C3FF E6 07         [ 3] 3318 	lda	7,x
   C401 87            [ 2] 3319 	psha
   C402 E6 06         [ 3] 3320 	lda	6,x
   C404 EE 05         [ 3] 3321 	ldx	5,x
   C406 CD C2 A2      [ 5] 3322 	jsr	_writeIgnTablePageByte
   C409 A7 01         [ 2] 3323 	ais	#1
   C40B 20 3B         [ 3] 3324 	bra	00110$
                           3325 ;comms.c:587: case 4: return writeStructPageByte((uint8_t *)&configPage2, sizeof(struct ConfigPage2), offset, value);
   C40D                    3326 00104$:
   C40D 95            [ 2] 3327 	tsx
   C40E E6 07         [ 3] 3328 	lda	7,x
   C410 87            [ 2] 3329 	psha
   C411 E6 06         [ 3] 3330 	lda	6,x
   C413 87            [ 2] 3331 	psha
   C414 E6 05         [ 3] 3332 	lda	5,x
   C416 87            [ 2] 3333 	psha
   C417 A6 20         [ 2] 3334 	lda	#0x20
   C419 87            [ 2] 3335 	psha
   C41A 4F            [ 1] 3336 	clra
   C41B 87            [ 2] 3337 	psha
   C41C A6 BA         [ 2] 3338 	lda	#_configPage2
   C41E AE 00         [ 2] 3339 	ldx	#>_configPage2
   C420 CD C0 E9      [ 5] 3340 	jsr	_writeStructPageByte
   C423 A7 05         [ 2] 3341 	ais	#5
   C425 20 21         [ 3] 3342 	bra	00110$
                           3343 ;comms.c:588: default: {
   C427                    3344 00105$:
                           3345 ;comms.c:589: uint16_t pageSz = getPageSize(page);
   C427 9E E6 03      [ 4] 3346 	lda	3,s
   C42A CD C0 9C      [ 5] 3347 	jsr	_getPageSize
   C42D 9E EF 01      [ 4] 3348 	stx	1,s
   C430 9E E7 02      [ 4] 3349 	sta	2,s
                           3350 ;comms.c:590: if (pageSz == 0 || offset >= pageSz) return PAGE_WRITE_FAIL;
   C433 4D            [ 1] 3351 	tsta
   C434 26 01         [ 3] 3352 	bne	00125$
   C436 5D            [ 1] 3353 	tstx
   C437                    3354 00125$:
   C437 27 0A         [ 3] 3355 	beq	00106$
   C439 95            [ 2] 3356 	tsx
   C43A E6 06         [ 3] 3357 	lda	6,x
   C43C E0 01         [ 3] 3358 	sub	1,x
   C43E E6 05         [ 3] 3359 	lda	5,x
   C440 F2            [ 2] 3360 	sbc	,x
   C441 25 03         [ 3] 3361 	bcs	00107$
   C443                    3362 00106$:
   C443 4F            [ 1] 3363 	clra
   C444 20 02         [ 3] 3364 	bra	00110$
   C446                    3365 00107$:
                           3366 ;comms.c:591: return PAGE_WRITE_OK;
   C446 A6 01         [ 2] 3367 	lda	#0x01
                           3368 ;comms.c:593: }
   C448                    3369 00110$:
                           3370 ;comms.c:594: }
   C448 A7 03         [ 2] 3371 	ais	#3
   C44A 81            [ 4] 3372 	rts
                           3373 ;------------------------------------------------------------
                           3374 ;Allocation info for local variables in function 'sendPageValues'
                           3375 ;------------------------------------------------------------
                           3376 ;offset                    Allocated to stack - sp +63
                           3377 ;length                    Allocated to stack - sp +65
                           3378 ;page                      Allocated to stack - sp +60
                           3379 ;pageSz                    Allocated to registers a x 
                           3380 ;available                 Allocated to stack - sp +58
                           3381 ;actualLength              Allocated to stack - sp +56
                           3382 ;responseLength            Allocated to registers a x 
                           3383 ;remaining                 Allocated to stack - sp +54
                           3384 ;pos                       Allocated to stack - sp +52
                           3385 ;tempBuf                   Allocated to stack - sp +6
                           3386 ;crc                       Allocated to stack - sp +2
                           3387 ;err                       Allocated to stack - sp +1
                           3388 ;blockSize                 Allocated to stack - sp +50
                           3389 ;i                         Allocated to stack - sp +48
                           3390 ;byteValue                 Allocated to stack - sp +1
                           3391 ;sloc0                     Allocated to stack - sp +42
                           3392 ;sloc1                     Allocated to stack - sp +38
                           3393 ;sloc2                     Allocated to stack - sp +40
                           3394 ;sloc3                     Allocated to stack - sp +46
                           3395 ;------------------------------------------------------------
                           3396 ;comms.c:596: void sendPageValues(uint8_t page, uint16_t offset, uint16_t length) {
                           3397 ;	-----------------------------------------
                           3398 ;	 function sendPageValues
                           3399 ;	-----------------------------------------
                           3400 ;	Register assignment might be sub-optimal.
                           3401 ;	Stack space usage: 60 bytes.
   C44B                    3402 _sendPageValues:
   C44B 87            [ 2] 3403 	psha
   C44C A7 C5         [ 2] 3404 	ais	#-59
                           3405 ;comms.c:597: uint16_t pageSz = getPageSize(page);
   C44E 9E E6 3C      [ 4] 3406 	lda	60,s
   C451 CD C0 9C      [ 5] 3407 	jsr	_getPageSize
                           3408 ;comms.c:602: if (pageSz == 0) {
   C454 4D            [ 1] 3409 	tsta
   C455 26 01         [ 3] 3410 	bne	00181$
   C457 5D            [ 1] 3411 	tstx
   C458                    3412 00181$:
   C458 26 44         [ 3] 3413 	bne	00102$
                           3414 ;comms.c:603: uint8_t err = SERIAL_RC_RANGE_ERR;
   C45A A6 80         [ 2] 3415 	lda	#0x80
   C45C 9E E7 01      [ 4] 3416 	sta	1,s
                           3417 ;comms.c:604: sendU16BE(1);
   C45F A6 01         [ 2] 3418 	lda	#0x01
   C461 5F            [ 1] 3419 	clrx
   C462 CD B5 75      [ 5] 3420 	jsr	_sendU16BE
                           3421 ;comms.c:605: sendByte(err);
   C465 9E E6 01      [ 4] 3422 	lda	1,s
   C468 CD B5 4F      [ 5] 3423 	jsr	_sendByte
                           3424 ;comms.c:606: sendU32BE(calculateCRC32(&err, 1));
   C46B 95            [ 2] 3425 	tsx
   C46C A6 01         [ 2] 3426 	lda	#0x01
   C46E 87            [ 2] 3427 	psha
   C46F 4A            [ 1] 3428 	deca
   C470 87            [ 2] 3429 	psha
   C471 9F            [ 1] 3430 	txa
   C472 8B            [ 2] 3431 	pshh
   C473 88            [ 2] 3432 	pulx
   C474 CD B4 C6      [ 5] 3433 	jsr	_calculateCRC32
   C477 9E E7 2F      [ 4] 3434 	sta	47,s
   C47A 9E EF 2E      [ 4] 3435 	stx	46,s
   C47D B6 4A         [ 3] 3436 	lda	*___SDCC_hc08_ret2
   C47F 9E E7 2D      [ 4] 3437 	sta	45,s
   C482 B6 4B         [ 3] 3438 	lda	*___SDCC_hc08_ret3
   C484 9E E7 2C      [ 4] 3439 	sta	44,s
   C487 A7 02         [ 2] 3440 	ais	#2
   C489 95            [ 2] 3441 	tsx
   C48A E6 2C         [ 3] 3442 	lda	44,x
   C48C 87            [ 2] 3443 	psha
   C48D E6 2B         [ 3] 3444 	lda	43,x
   C48F 87            [ 2] 3445 	psha
   C490 E6 2A         [ 3] 3446 	lda	42,x
   C492 87            [ 2] 3447 	psha
   C493 E6 29         [ 3] 3448 	lda	41,x
   C495 87            [ 2] 3449 	psha
   C496 CD B5 83      [ 5] 3450 	jsr	_sendU32BE
   C499 A7 04         [ 2] 3451 	ais	#4
                           3452 ;comms.c:607: return;
   C49B CC C6 6F      [ 3] 3453 	jmp	00116$
   C49E                    3454 00102$:
                           3455 ;comms.c:610: available = (offset < pageSz) ? (uint16_t)(pageSz - offset) : 0;
   C49E 87            [ 2] 3456 	psha
   C49F 87            [ 2] 3457 	psha
   C4A0 9E E6 42      [ 4] 3458 	lda	66,s
   C4A3 9E E0 01      [ 4] 3459 	sub	1, s
   C4A6 86            [ 2] 3460 	pula
   C4A7 9E E6 40      [ 4] 3461 	lda	64,s
   C4AA 89            [ 2] 3462 	pshx
   C4AB 9E E2 01      [ 4] 3463 	sbc	1,s
   C4AE A7 01         [ 2] 3464 	ais	#1
   C4B0 86            [ 2] 3465 	pula
   C4B1 24 0C         [ 3] 3466 	bcc	00118$
   C4B3 9E E0 40      [ 4] 3467 	sub	64,s
   C4B6 87            [ 2] 3468 	psha
   C4B7 9F            [ 1] 3469 	txa
   C4B8 9E E2 40      [ 4] 3470 	sbc	64,s
   C4BB 97            [ 1] 3471 	tax
   C4BC 86            [ 2] 3472 	pula
   C4BD 20 02         [ 3] 3473 	bra	00119$
   C4BF                    3474 00118$:
   C4BF 5F            [ 1] 3475 	clrx
   C4C0 9F            [ 1] 3476 	txa
   C4C1                    3477 00119$:
   C4C1 9E E7 3B      [ 4] 3478 	sta	59,s
   C4C4 9E EF 3A      [ 4] 3479 	stx	58,s
                           3480 ;comms.c:611: actualLength = (length < available) ? length : available;
   C4C7 95            [ 2] 3481 	tsx
   C4C8 E6 41         [ 3] 3482 	lda	65,x
   C4CA E0 3A         [ 3] 3483 	sub	58,x
   C4CC E6 40         [ 3] 3484 	lda	64,x
   C4CE E2 39         [ 3] 3485 	sbc	57,x
   C4D0 24 0A         [ 3] 3486 	bcc	00120$
   C4D2 E6 40         [ 3] 3487 	lda	64,x
   C4D4 E7 37         [ 3] 3488 	sta	55,x
   C4D6 E6 41         [ 3] 3489 	lda	65,x
   C4D8 E7 38         [ 3] 3490 	sta	56,x
   C4DA 20 09         [ 3] 3491 	bra	00121$
   C4DC                    3492 00120$:
   C4DC 95            [ 2] 3493 	tsx
   C4DD E6 39         [ 3] 3494 	lda	57,x
   C4DF E7 37         [ 3] 3495 	sta	55,x
   C4E1 E6 3A         [ 3] 3496 	lda	58,x
   C4E3 E7 38         [ 3] 3497 	sta	56,x
   C4E5                    3498 00121$:
   C4E5 95            [ 2] 3499 	tsx
                           3500 ;comms.c:612: responseLength = (uint16_t)(1 + actualLength);
   C4E6 E6 38         [ 3] 3501 	lda	56,x
   C4E8 EE 37         [ 3] 3502 	ldx	55,x
   C4EA 4C            [ 1] 3503 	inca
   C4EB 26 01         [ 3] 3504 	bne	00185$
   C4ED 5C            [ 1] 3505 	incx
   C4EE                    3506 00185$:
                           3507 ;comms.c:614: sendU16BE(responseLength);
   C4EE CD B5 75      [ 5] 3508 	jsr	_sendU16BE
                           3509 ;comms.c:616: sendByte(SERIAL_RC_OK);
   C4F1 4F            [ 1] 3510 	clra
   C4F2 CD B5 4F      [ 5] 3511 	jsr	_sendByte
                           3512 ;comms.c:617: crc = crc32Update(crc, SERIAL_RC_OK);
   C4F5 4F            [ 1] 3513 	clra
   C4F6 87            [ 2] 3514 	psha
   C4F7 4A            [ 1] 3515 	deca
   C4F8 87            [ 2] 3516 	psha
   C4F9 87            [ 2] 3517 	psha
   C4FA 87            [ 2] 3518 	psha
   C4FB 87            [ 2] 3519 	psha
   C4FC CD B4 09      [ 5] 3520 	jsr	_crc32Update
   C4FF 9E E7 0A      [ 4] 3521 	sta	10,s
   C502 9E EF 09      [ 4] 3522 	stx	9,s
   C505 B6 4A         [ 3] 3523 	lda	*___SDCC_hc08_ret2
   C507 9E E7 08      [ 4] 3524 	sta	8,s
   C50A B6 4B         [ 3] 3525 	lda	*___SDCC_hc08_ret3
   C50C 9E E7 07      [ 4] 3526 	sta	7,s
   C50F A7 05         [ 2] 3527 	ais	#5
                           3528 ;comms.c:619: remaining = actualLength;
   C511 95            [ 2] 3529 	tsx
   C512 E6 37         [ 3] 3530 	lda	55,x
   C514 E7 35         [ 3] 3531 	sta	53,x
   C516 E6 38         [ 3] 3532 	lda	56,x
   C518 E7 36         [ 3] 3533 	sta	54,x
                           3534 ;comms.c:620: pos = 0;
   C51A 4F            [ 1] 3535 	clra
   C51B E7 33         [ 3] 3536 	sta	51,x
   C51D E7 34         [ 3] 3537 	sta	52,x
                           3538 ;comms.c:622: while (remaining > 0) {
   C51F 95            [ 2] 3539 	tsx
   C520 AF 05         [ 2] 3540 	aix	#5
   C522 8B            [ 2] 3541 	pshh
   C523 86            [ 2] 3542 	pula
   C524 9E E7 2A      [ 4] 3543 	sta	42,s
   C527 9E EF 2B      [ 4] 3544 	stx	43,s
   C52A 95            [ 2] 3545 	tsx
   C52B E6 29         [ 3] 3546 	lda	41,x
   C52D E7 25         [ 3] 3547 	sta	37,x
   C52F E6 2A         [ 3] 3548 	lda	42,x
   C531 E7 26         [ 3] 3549 	sta	38,x
   C533                    3550 00107$:
   C533 95            [ 2] 3551 	tsx
   C534 E6 36         [ 3] 3552 	lda	54,x
   C536 EA 35         [ 3] 3553 	ora	53,x
   C538 26 03         [ 3] 3554 	bne	00186$
   C53A CC C6 49      [ 3] 3555 	jmp	00109$
   C53D                    3556 00186$:
                           3557 ;comms.c:623: uint16_t blockSize = (remaining < sizeof(tempBuf)) ? remaining : (uint16_t)sizeof(tempBuf);
   C53D E6 36         [ 3] 3558 	lda	54,x
   C53F A0 20         [ 2] 3559 	sub	#0x20
   C541 E6 35         [ 3] 3560 	lda	53,x
   C543 A2 00         [ 2] 3561 	sbc	#0x00
   C545 24 0A         [ 3] 3562 	bcc	00122$
   C547 E6 35         [ 3] 3563 	lda	53,x
   C549 E7 31         [ 3] 3564 	sta	49,x
   C54B E6 36         [ 3] 3565 	lda	54,x
   C54D E7 32         [ 3] 3566 	sta	50,x
   C54F 20 08         [ 3] 3567 	bra	00123$
   C551                    3568 00122$:
   C551 95            [ 2] 3569 	tsx
   C552 4F            [ 1] 3570 	clra
   C553 E7 31         [ 3] 3571 	sta	49,x
   C555 A6 20         [ 2] 3572 	lda	#0x20
   C557 E7 32         [ 3] 3573 	sta	50,x
   C559                    3574 00123$:
   C559 95            [ 2] 3575 	tsx
                           3576 ;comms.c:626: for (i = 0; i < blockSize; i++) {
   C55A E6 34         [ 3] 3577 	lda	52,x
   C55C EB 3F         [ 3] 3578 	add	63,x
   C55E E7 28         [ 3] 3579 	sta	40,x
   C560 E6 33         [ 3] 3580 	lda	51,x
   C562 E9 3E         [ 3] 3581 	adc	62,x
   C564 E7 27         [ 3] 3582 	sta	39,x
   C566 4F            [ 1] 3583 	clra
   C567 E7 2F         [ 3] 3584 	sta	47,x
   C569 E7 30         [ 3] 3585 	sta	48,x
   C56B                    3586 00111$:
   C56B 95            [ 2] 3587 	tsx
   C56C E6 30         [ 3] 3588 	lda	48,x
   C56E E0 32         [ 3] 3589 	sub	50,x
   C570 E6 2F         [ 3] 3590 	lda	47,x
   C572 E2 31         [ 3] 3591 	sbc	49,x
   C574 24 48         [ 3] 3592 	bcc	00105$
                           3593 ;comms.c:627: uint8_t byteValue = 0;
   C576 4F            [ 1] 3594 	clra
   C577 F7            [ 2] 3595 	sta	,x
                           3596 ;comms.c:628: if (!readPageByte(page, (uint16_t)(offset + pos + i), &byteValue)) {
   C578 95            [ 2] 3597 	tsx
   C579 9E E6 31      [ 4] 3598 	lda	49,s
   C57C 9E EB 29      [ 4] 3599 	add	41,s
   C57F 9E E7 2F      [ 4] 3600 	sta	47,s
   C582 9E E6 30      [ 4] 3601 	lda	48,s
   C585 9E E9 28      [ 4] 3602 	adc	40,s
   C588 9E E7 2E      [ 4] 3603 	sta	46,s
   C58B 89            [ 2] 3604 	pshx
   C58C 8B            [ 2] 3605 	pshh
   C58D 95            [ 2] 3606 	tsx
   C58E E6 30         [ 3] 3607 	lda	48,x
   C590 87            [ 2] 3608 	psha
   C591 E6 2F         [ 3] 3609 	lda	47,x
   C593 87            [ 2] 3610 	psha
   C594 E6 3D         [ 3] 3611 	lda	61,x
   C596 CD C3 21      [ 5] 3612 	jsr	_readPageByte
   C599 A7 04         [ 2] 3613 	ais	#4
   C59B 4D            [ 1] 3614 	tsta
   C59C 26 04         [ 3] 3615 	bne	00104$
                           3616 ;comms.c:629: byteValue = 0;
   C59E 4F            [ 1] 3617 	clra
   C59F 9E E7 01      [ 4] 3618 	sta	1,s
   C5A2                    3619 00104$:
                           3620 ;comms.c:631: tempBuf[i] = byteValue;
   C5A2 9E E6 31      [ 4] 3621 	lda	49,s
   C5A5 9E EB 2B      [ 4] 3622 	add	43,s
   C5A8 97            [ 1] 3623 	tax
   C5A9 9E E6 30      [ 4] 3624 	lda	48,s
   C5AC 9E E9 2A      [ 4] 3625 	adc	42,s
   C5AF 87            [ 2] 3626 	psha
   C5B0 8A            [ 2] 3627 	pulh
   C5B1 9E E6 01      [ 4] 3628 	lda	1,s
   C5B4 F7            [ 2] 3629 	sta	,x
                           3630 ;comms.c:626: for (i = 0; i < blockSize; i++) {
   C5B5 95            [ 2] 3631 	tsx
   C5B6 6C 30         [ 4] 3632 	inc	48,x
   C5B8 26 02         [ 3] 3633 	bne	00190$
   C5BA 6C 2F         [ 4] 3634 	inc	47,x
   C5BC                    3635 00190$:
   C5BC 20 AD         [ 3] 3636 	bra	00111$
   C5BE                    3637 00105$:
                           3638 ;comms.c:634: sendBytes(tempBuf, blockSize);
   C5BE 9E E6 26      [ 4] 3639 	lda	38,s
   C5C1 87            [ 2] 3640 	psha
   C5C2 8A            [ 2] 3641 	pulh
   C5C3 9E EE 27      [ 4] 3642 	ldx	39,s
   C5C6 9E E6 33      [ 4] 3643 	lda	51,s
   C5C9 87            [ 2] 3644 	psha
   C5CA 9E E6 33      [ 4] 3645 	lda	51,s
   C5CD 87            [ 2] 3646 	psha
   C5CE 9F            [ 1] 3647 	txa
   C5CF 8B            [ 2] 3648 	pshh
   C5D0 88            [ 2] 3649 	pulx
   C5D1 CD B5 52      [ 5] 3650 	jsr	_sendBytes
   C5D4 A7 02         [ 2] 3651 	ais	#2
                           3652 ;comms.c:636: for (i = 0; i < blockSize; i++) {
   C5D6 8C            [ 1] 3653 	clrh
   C5D7 5F            [ 1] 3654 	clrx
   C5D8                    3655 00114$:
   C5D8 9F            [ 1] 3656 	txa
   C5D9 9E E0 33      [ 4] 3657 	sub	51,s
   C5DC 8B            [ 2] 3658 	pshh
   C5DD 86            [ 2] 3659 	pula
   C5DE 9E E2 32      [ 4] 3660 	sbc	50,s
   C5E1 24 4A         [ 3] 3661 	bcc	00106$
                           3662 ;comms.c:637: crc = crc32Update(crc, tempBuf[i]);
   C5E3 9F            [ 1] 3663 	txa
   C5E4 9E EB 27      [ 4] 3664 	add	39,s
   C5E7 9E E7 2F      [ 4] 3665 	sta	47,s
   C5EA 8B            [ 2] 3666 	pshh
   C5EB 86            [ 2] 3667 	pula
   C5EC 9E E9 26      [ 4] 3668 	adc	38,s
   C5EF 9E E7 2E      [ 4] 3669 	sta	46,s
   C5F2 89            [ 2] 3670 	pshx
   C5F3 8B            [ 2] 3671 	pshh
   C5F4 9E E6 30      [ 4] 3672 	lda	48,s
   C5F7 87            [ 2] 3673 	psha
   C5F8 8A            [ 2] 3674 	pulh
   C5F9 9E EE 31      [ 4] 3675 	ldx	49,s
   C5FC F6            [ 2] 3676 	lda	,x
   C5FD 8A            [ 2] 3677 	pulh
   C5FE 88            [ 2] 3678 	pulx
   C5FF 89            [ 2] 3679 	pshx
   C600 8B            [ 2] 3680 	pshh
   C601 87            [ 2] 3681 	psha
   C602 9E E6 08      [ 4] 3682 	lda	8,s
   C605 87            [ 2] 3683 	psha
   C606 9E E6 08      [ 4] 3684 	lda	8,s
   C609 87            [ 2] 3685 	psha
   C60A 9E E6 08      [ 4] 3686 	lda	8,s
   C60D 87            [ 2] 3687 	psha
   C60E 9E E6 08      [ 4] 3688 	lda	8,s
   C611 87            [ 2] 3689 	psha
   C612 CD B4 09      [ 5] 3690 	jsr	_crc32Update
   C615 9E E7 0C      [ 4] 3691 	sta	12,s
   C618 9E EF 0B      [ 4] 3692 	stx	11,s
   C61B B6 4A         [ 3] 3693 	lda	*___SDCC_hc08_ret2
   C61D 9E E7 0A      [ 4] 3694 	sta	10,s
   C620 B6 4B         [ 3] 3695 	lda	*___SDCC_hc08_ret3
   C622 9E E7 09      [ 4] 3696 	sta	9,s
   C625 A7 05         [ 2] 3697 	ais	#5
   C627 8A            [ 2] 3698 	pulh
   C628 88            [ 2] 3699 	pulx
                           3700 ;comms.c:636: for (i = 0; i < blockSize; i++) {
   C629 AF 01         [ 2] 3701 	aix	#1
   C62B 20 AB         [ 3] 3702 	bra	00114$
   C62D                    3703 00106$:
                           3704 ;comms.c:640: pos = (uint16_t)(pos + blockSize);
   C62D 95            [ 2] 3705 	tsx
   C62E E6 32         [ 3] 3706 	lda	50,x
   C630 EB 34         [ 3] 3707 	add	52,x
   C632 E7 34         [ 3] 3708 	sta	52,x
   C634 E6 31         [ 3] 3709 	lda	49,x
   C636 E9 33         [ 3] 3710 	adc	51,x
   C638 E7 33         [ 3] 3711 	sta	51,x
                           3712 ;comms.c:641: remaining = (uint16_t)(remaining - blockSize);
   C63A E6 36         [ 3] 3713 	lda	54,x
   C63C E0 32         [ 3] 3714 	sub	50,x
   C63E E7 36         [ 3] 3715 	sta	54,x
   C640 E6 35         [ 3] 3716 	lda	53,x
   C642 E2 31         [ 3] 3717 	sbc	49,x
   C644 E7 35         [ 3] 3718 	sta	53,x
   C646 CC C5 33      [ 3] 3719 	jmp	00107$
   C649                    3720 00109$:
                           3721 ;comms.c:644: crc = ~crc;
   C649 95            [ 2] 3722 	tsx
   C64A E6 04         [ 3] 3723 	lda	4,x
   C64C 43            [ 1] 3724 	coma
   C64D E7 04         [ 3] 3725 	sta	4,x
   C64F E6 03         [ 3] 3726 	lda	3,x
   C651 43            [ 1] 3727 	coma
   C652 E7 03         [ 3] 3728 	sta	3,x
   C654 E6 02         [ 3] 3729 	lda	2,x
   C656 43            [ 1] 3730 	coma
   C657 E7 02         [ 3] 3731 	sta	2,x
   C659 E6 01         [ 3] 3732 	lda	1,x
   C65B 43            [ 1] 3733 	coma
   C65C E7 01         [ 3] 3734 	sta	1,x
                           3735 ;comms.c:645: sendU32BE(crc);
   C65E E6 04         [ 3] 3736 	lda	4,x
   C660 87            [ 2] 3737 	psha
   C661 E6 03         [ 3] 3738 	lda	3,x
   C663 87            [ 2] 3739 	psha
   C664 E6 02         [ 3] 3740 	lda	2,x
   C666 87            [ 2] 3741 	psha
   C667 E6 01         [ 3] 3742 	lda	1,x
   C669 87            [ 2] 3743 	psha
   C66A CD B5 83      [ 5] 3744 	jsr	_sendU32BE
   C66D A7 04         [ 2] 3745 	ais	#4
   C66F                    3746 00116$:
                           3747 ;comms.c:646: }
   C66F A7 3C         [ 2] 3748 	ais	#60
   C671 81            [ 4] 3749 	rts
                           3750 ;------------------------------------------------------------
                           3751 ;Allocation info for local variables in function 'writePageValues'
                           3752 ;------------------------------------------------------------
                           3753 ;offset                    Allocated to stack - sp +10
                           3754 ;length                    Allocated to stack - sp +12
                           3755 ;data                      Allocated to stack - sp +14
                           3756 ;page                      Allocated to stack - sp +5
                           3757 ;pageSz                    Allocated to stack - sp +3
                           3758 ;i                         Allocated to stack - sp +6
                           3759 ;status                    Allocated to registers a 
                           3760 ;sloc0                     Allocated to stack - sp +3
                           3761 ;sloc1                     Allocated to stack - sp +1
                           3762 ;------------------------------------------------------------
                           3763 ;comms.c:648: uint8_t writePageValues(uint8_t page, uint16_t offset, uint16_t length, const uint8_t *data) {
                           3764 ;	-----------------------------------------
                           3765 ;	 function writePageValues
                           3766 ;	-----------------------------------------
                           3767 ;	Register assignment is optimal.
                           3768 ;	Stack space usage: 7 bytes.
   C672                    3769 _writePageValues:
   C672 A7 F9         [ 2] 3770 	ais	#-7
   C674 9E E7 05      [ 4] 3771 	sta	5,s
                           3772 ;comms.c:649: uint16_t pageSz = getPageSize(page);
   C677 9E E6 05      [ 4] 3773 	lda	5,s
   C67A CD C0 9C      [ 5] 3774 	jsr	_getPageSize
   C67D 9E EF 03      [ 4] 3775 	stx	3,s
   C680 9E E7 04      [ 4] 3776 	sta	4,s
                           3777 ;comms.c:652: if (pageSz == 0 || (offset + length) > pageSz) {
   C683 4D            [ 1] 3778 	tsta
   C684 26 01         [ 3] 3779 	bne	00132$
   C686 5D            [ 1] 3780 	tstx
   C687                    3781 00132$:
   C687 27 15         [ 3] 3782 	beq	00101$
   C689 95            [ 2] 3783 	tsx
   C68A E6 0A         [ 3] 3784 	lda	10,x
   C68C EB 0C         [ 3] 3785 	add	12,x
   C68E E7 01         [ 3] 3786 	sta	1,x
   C690 E6 09         [ 3] 3787 	lda	9,x
   C692 E9 0B         [ 3] 3788 	adc	11,x
   C694 F7            [ 2] 3789 	sta	,x
   C695 E6 03         [ 3] 3790 	lda	3,x
   C697 E0 01         [ 3] 3791 	sub	1,x
   C699 E6 02         [ 3] 3792 	lda	2,x
   C69B F2            [ 2] 3793 	sbc	,x
   C69C 24 04         [ 3] 3794 	bcc	00115$
   C69E                    3795 00101$:
                           3796 ;comms.c:653: return SERIAL_RC_RANGE_ERR;
   C69E A6 80         [ 2] 3797 	lda	#0x80
   C6A0 20 4A         [ 3] 3798 	bra	00110$
                           3799 ;comms.c:656: for (i = 0; i < length; i++) {
   C6A2                    3800 00115$:
   C6A2 95            [ 2] 3801 	tsx
   C6A3 4F            [ 1] 3802 	clra
   C6A4 E7 05         [ 3] 3803 	sta	5,x
   C6A6 E7 06         [ 3] 3804 	sta	6,x
   C6A8                    3805 00108$:
   C6A8 95            [ 2] 3806 	tsx
   C6A9 E6 06         [ 3] 3807 	lda	6,x
   C6AB E0 0C         [ 3] 3808 	sub	12,x
   C6AD E6 05         [ 3] 3809 	lda	5,x
   C6AF E2 0B         [ 3] 3810 	sbc	11,x
   C6B1 24 38         [ 3] 3811 	bcc	00106$
                           3812 ;comms.c:657: PageWriteStatus status = writePageByte(page, (uint16_t)(offset + i), data[i]);
   C6B3 E6 06         [ 3] 3813 	lda	6,x
   C6B5 EB 0E         [ 3] 3814 	add	14,x
   C6B7 97            [ 1] 3815 	tax
   C6B8 9E E6 06      [ 4] 3816 	lda	6,s
   C6BB 9E E9 0E      [ 4] 3817 	adc	14,s
   C6BE 87            [ 2] 3818 	psha
   C6BF 8A            [ 2] 3819 	pulh
   C6C0 F6            [ 2] 3820 	lda	,x
   C6C1 87            [ 2] 3821 	psha
   C6C2 8A            [ 2] 3822 	pulh
   C6C3 9E E6 07      [ 4] 3823 	lda	7,s
   C6C6 9E EB 0B      [ 4] 3824 	add	11,s
   C6C9 97            [ 1] 3825 	tax
   C6CA 9E E6 06      [ 4] 3826 	lda	6,s
   C6CD 9E E9 0A      [ 4] 3827 	adc	10,s
   C6D0 8B            [ 2] 3828 	pshh
   C6D1 89            [ 2] 3829 	pshx
   C6D2 87            [ 2] 3830 	psha
   C6D3 9E E6 08      [ 4] 3831 	lda	8,s
   C6D6 CD C3 B4      [ 5] 3832 	jsr	_writePageByte
   C6D9 A7 03         [ 2] 3833 	ais	#3
                           3834 ;comms.c:658: if (status == PAGE_WRITE_FAIL) {
   C6DB 4D            [ 1] 3835 	tsta
   C6DC 26 04         [ 3] 3836 	bne	00109$
                           3837 ;comms.c:659: return SERIAL_RC_RANGE_ERR;
   C6DE A6 80         [ 2] 3838 	lda	#0x80
   C6E0 20 0A         [ 3] 3839 	bra	00110$
   C6E2                    3840 00109$:
                           3841 ;comms.c:656: for (i = 0; i < length; i++) {
   C6E2 95            [ 2] 3842 	tsx
   C6E3 6C 06         [ 4] 3843 	inc	6,x
   C6E5 26 02         [ 3] 3844 	bne	00137$
   C6E7 6C 05         [ 4] 3845 	inc	5,x
   C6E9                    3846 00137$:
   C6E9 20 BD         [ 3] 3847 	bra	00108$
   C6EB                    3848 00106$:
                           3849 ;comms.c:663: return SERIAL_RC_OK;
   C6EB 4F            [ 1] 3850 	clra
   C6EC                    3851 00110$:
                           3852 ;comms.c:664: }
   C6EC A7 07         [ 2] 3853 	ais	#7
   C6EE 81            [ 4] 3854 	rts
                           3855 ;------------------------------------------------------------
                           3856 ;Allocation info for local variables in function 'sendPageCRC32'
                           3857 ;------------------------------------------------------------
                           3858 ;page                      Allocated to stack - sp +23
                           3859 ;pageSz                    Allocated to stack - sp +24
                           3860 ;crc                       Allocated to stack - sp +2
                           3861 ;pageCRC                   Allocated to stack - sp +17
                           3862 ;reversedCRC               Allocated to stack - sp +13
                           3863 ;i                         Allocated to stack - sp +26
                           3864 ;response                  Allocated to stack - sp +6
                           3865 ;err                       Allocated to stack - sp +1
                           3866 ;byteValue                 Allocated to stack - sp +1
                           3867 ;sloc0                     Allocated to stack - sp +19
                           3868 ;sloc1                     Allocated to stack - sp +15
                           3869 ;sloc2                     Allocated to stack - sp +11
                           3870 ;------------------------------------------------------------
                           3871 ;comms.c:666: void sendPageCRC32(uint8_t page) {
                           3872 ;	-----------------------------------------
                           3873 ;	 function sendPageCRC32
                           3874 ;	-----------------------------------------
                           3875 ;	Register assignment might be sub-optimal.
                           3876 ;	Stack space usage: 27 bytes.
   C6EF                    3877 _sendPageCRC32:
   C6EF A7 E5         [ 2] 3878 	ais	#-27
   C6F1 9E E7 17      [ 4] 3879 	sta	23,s
                           3880 ;comms.c:667: uint16_t pageSz = getPageSize(page);
   C6F4 9E E6 17      [ 4] 3881 	lda	23,s
   C6F7 CD C0 9C      [ 5] 3882 	jsr	_getPageSize
   C6FA 9E E7 19      [ 4] 3883 	sta	25,s
   C6FD 9E EF 18      [ 4] 3884 	stx	24,s
                           3885 ;comms.c:668: uint32_t crc = 0xFFFFFFFFUL, pageCRC, reversedCRC;
   C700 95            [ 2] 3886 	tsx
   C701 A6 FF         [ 2] 3887 	lda	#0xff
   C703 E7 01         [ 3] 3888 	sta	1,x
   C705 E7 02         [ 3] 3889 	sta	2,x
   C707 E7 03         [ 3] 3890 	sta	3,x
   C709 E7 04         [ 3] 3891 	sta	4,x
                           3892 ;comms.c:672: if (pageSz == 0) {
   C70B E6 18         [ 3] 3893 	lda	24,x
   C70D EA 17         [ 3] 3894 	ora	23,x
   C70F 26 42         [ 3] 3895 	bne	00114$
                           3896 ;comms.c:673: uint8_t err = SERIAL_RC_RANGE_ERR;
   C711 A6 80         [ 2] 3897 	lda	#0x80
   C713 F7            [ 2] 3898 	sta	,x
                           3899 ;comms.c:674: sendU16BE(1);
   C714 A6 01         [ 2] 3900 	lda	#0x01
   C716 5F            [ 1] 3901 	clrx
   C717 CD B5 75      [ 5] 3902 	jsr	_sendU16BE
                           3903 ;comms.c:675: sendByte(err);
   C71A 9E E6 01      [ 4] 3904 	lda	1,s
   C71D CD B5 4F      [ 5] 3905 	jsr	_sendByte
                           3906 ;comms.c:676: sendU32BE(calculateCRC32(&err, 1));
   C720 95            [ 2] 3907 	tsx
   C721 A6 01         [ 2] 3908 	lda	#0x01
   C723 87            [ 2] 3909 	psha
   C724 4A            [ 1] 3910 	deca
   C725 87            [ 2] 3911 	psha
   C726 9F            [ 1] 3912 	txa
   C727 8B            [ 2] 3913 	pshh
   C728 88            [ 2] 3914 	pulx
   C729 CD B4 C6      [ 5] 3915 	jsr	_calculateCRC32
   C72C 9E E7 18      [ 4] 3916 	sta	24,s
   C72F 9E EF 17      [ 4] 3917 	stx	23,s
   C732 B6 4A         [ 3] 3918 	lda	*___SDCC_hc08_ret2
   C734 9E E7 16      [ 4] 3919 	sta	22,s
   C737 B6 4B         [ 3] 3920 	lda	*___SDCC_hc08_ret3
   C739 9E E7 15      [ 4] 3921 	sta	21,s
   C73C A7 02         [ 2] 3922 	ais	#2
   C73E 95            [ 2] 3923 	tsx
   C73F E6 15         [ 3] 3924 	lda	21,x
   C741 87            [ 2] 3925 	psha
   C742 E6 14         [ 3] 3926 	lda	20,x
   C744 87            [ 2] 3927 	psha
   C745 E6 13         [ 3] 3928 	lda	19,x
   C747 87            [ 2] 3929 	psha
   C748 E6 12         [ 3] 3930 	lda	18,x
   C74A 87            [ 2] 3931 	psha
   C74B CD B5 83      [ 5] 3932 	jsr	_sendU32BE
   C74E A7 04         [ 2] 3933 	ais	#4
                           3934 ;comms.c:677: return;
   C750 CC C9 36      [ 3] 3935 	jmp	00109$
                           3936 ;comms.c:680: for (i = 0; i < pageSz; i++) {
   C753                    3937 00114$:
   C753 95            [ 2] 3938 	tsx
   C754 4F            [ 1] 3939 	clra
   C755 E7 19         [ 3] 3940 	sta	25,x
   C757 E7 1A         [ 3] 3941 	sta	26,x
   C759                    3942 00107$:
   C759 95            [ 2] 3943 	tsx
   C75A E6 1A         [ 3] 3944 	lda	26,x
   C75C E0 18         [ 3] 3945 	sub	24,x
   C75E E6 19         [ 3] 3946 	lda	25,x
   C760 E2 17         [ 3] 3947 	sbc	23,x
   C762 24 47         [ 3] 3948 	bcc	00105$
                           3949 ;comms.c:681: uint8_t byteValue = 0;
   C764 4F            [ 1] 3950 	clra
   C765 F7            [ 2] 3951 	sta	,x
                           3952 ;comms.c:682: if (!readPageByte(page, i, &byteValue)) {
   C766 95            [ 2] 3953 	tsx
   C767 89            [ 2] 3954 	pshx
   C768 8B            [ 2] 3955 	pshh
   C769 95            [ 2] 3956 	tsx
   C76A E6 1C         [ 3] 3957 	lda	28,x
   C76C 87            [ 2] 3958 	psha
   C76D E6 1B         [ 3] 3959 	lda	27,x
   C76F 87            [ 2] 3960 	psha
   C770 E6 18         [ 3] 3961 	lda	24,x
   C772 CD C3 21      [ 5] 3962 	jsr	_readPageByte
   C775 A7 04         [ 2] 3963 	ais	#4
   C777 4D            [ 1] 3964 	tsta
   C778 26 04         [ 3] 3965 	bne	00104$
                           3966 ;comms.c:683: byteValue = 0;
   C77A 4F            [ 1] 3967 	clra
   C77B 9E E7 01      [ 4] 3968 	sta	1,s
   C77E                    3969 00104$:
                           3970 ;comms.c:685: crc = crc32Update(crc, byteValue);
   C77E 95            [ 2] 3971 	tsx
   C77F F6            [ 2] 3972 	lda	,x
   C780 87            [ 2] 3973 	psha
   C781 E6 04         [ 3] 3974 	lda	4,x
   C783 87            [ 2] 3975 	psha
   C784 E6 03         [ 3] 3976 	lda	3,x
   C786 87            [ 2] 3977 	psha
   C787 E6 02         [ 3] 3978 	lda	2,x
   C789 87            [ 2] 3979 	psha
   C78A E6 01         [ 3] 3980 	lda	1,x
   C78C 87            [ 2] 3981 	psha
   C78D CD B4 09      [ 5] 3982 	jsr	_crc32Update
   C790 9E E7 0A      [ 4] 3983 	sta	10,s
   C793 9E EF 09      [ 4] 3984 	stx	9,s
   C796 B6 4A         [ 3] 3985 	lda	*___SDCC_hc08_ret2
   C798 9E E7 08      [ 4] 3986 	sta	8,s
   C79B B6 4B         [ 3] 3987 	lda	*___SDCC_hc08_ret3
   C79D 9E E7 07      [ 4] 3988 	sta	7,s
   C7A0 A7 05         [ 2] 3989 	ais	#5
                           3990 ;comms.c:680: for (i = 0; i < pageSz; i++) {
   C7A2 95            [ 2] 3991 	tsx
   C7A3 6C 1A         [ 4] 3992 	inc	26,x
   C7A5 26 02         [ 3] 3993 	bne	00135$
   C7A7 6C 19         [ 4] 3994 	inc	25,x
   C7A9                    3995 00135$:
   C7A9 20 AE         [ 3] 3996 	bra	00107$
   C7AB                    3997 00105$:
                           3998 ;comms.c:688: pageCRC = ~crc;
   C7AB 95            [ 2] 3999 	tsx
   C7AC E6 04         [ 3] 4000 	lda	4,x
   C7AE 43            [ 1] 4001 	coma
   C7AF E7 15         [ 3] 4002 	sta	21,x
   C7B1 E6 03         [ 3] 4003 	lda	3,x
   C7B3 43            [ 1] 4004 	coma
   C7B4 E7 14         [ 3] 4005 	sta	20,x
   C7B6 E6 02         [ 3] 4006 	lda	2,x
   C7B8 43            [ 1] 4007 	coma
   C7B9 E7 13         [ 3] 4008 	sta	19,x
   C7BB E6 01         [ 3] 4009 	lda	1,x
   C7BD 43            [ 1] 4010 	coma
   C7BE E7 12         [ 3] 4011 	sta	18,x
                           4012 ;comms.c:689: reversedCRC = ((pageCRC & 0xFFUL) << 24) | ((pageCRC & 0xFF00UL) << 8) |
   C7C0 E6 15         [ 3] 4013 	lda	21,x
   C7C2 E7 11         [ 3] 4014 	sta	17,x
   C7C4 4F            [ 1] 4015 	clra
   C7C5 E7 10         [ 3] 4016 	sta	16,x
   C7C7 E7 0F         [ 3] 4017 	sta	15,x
   C7C9 E7 0E         [ 3] 4018 	sta	14,x
   C7CB E6 11         [ 3] 4019 	lda	17,x
   C7CD E7 0E         [ 3] 4020 	sta	14,x
   C7CF 4F            [ 1] 4021 	clra
   C7D0 E7 11         [ 3] 4022 	sta	17,x
   C7D2 E7 10         [ 3] 4023 	sta	16,x
   C7D4 E7 0F         [ 3] 4024 	sta	15,x
   C7D6 E7 0D         [ 3] 4025 	sta	13,x
   C7D8 E6 14         [ 3] 4026 	lda	20,x
   C7DA E7 0C         [ 3] 4027 	sta	12,x
   C7DC 4F            [ 1] 4028 	clra
   C7DD E7 0B         [ 3] 4029 	sta	11,x
   C7DF E7 0A         [ 3] 4030 	sta	10,x
   C7E1 E6 0B         [ 3] 4031 	lda	11,x
   C7E3 E7 0A         [ 3] 4032 	sta	10,x
   C7E5 E6 0C         [ 3] 4033 	lda	12,x
   C7E7 E7 0B         [ 3] 4034 	sta	11,x
   C7E9 E6 0D         [ 3] 4035 	lda	13,x
   C7EB E7 0C         [ 3] 4036 	sta	12,x
   C7ED 4F            [ 1] 4037 	clra
   C7EE E7 0D         [ 3] 4038 	sta	13,x
   C7F0 E6 11         [ 3] 4039 	lda	17,x
   C7F2 EA 0D         [ 3] 4040 	ora	13,x
   C7F4 E7 0D         [ 3] 4041 	sta	13,x
   C7F6 E6 10         [ 3] 4042 	lda	16,x
   C7F8 EA 0C         [ 3] 4043 	ora	12,x
   C7FA E7 0C         [ 3] 4044 	sta	12,x
   C7FC E6 0F         [ 3] 4045 	lda	15,x
   C7FE EA 0B         [ 3] 4046 	ora	11,x
   C800 E7 0B         [ 3] 4047 	sta	11,x
   C802 E6 0E         [ 3] 4048 	lda	14,x
   C804 EA 0A         [ 3] 4049 	ora	10,x
   C806 E7 0A         [ 3] 4050 	sta	10,x
                           4051 ;comms.c:690: ((pageCRC & 0xFF0000UL) >> 8) | ((pageCRC & 0xFF000000UL) >> 24);
   C808 4F            [ 1] 4052 	clra
   C809 E7 11         [ 3] 4053 	sta	17,x
   C80B E7 10         [ 3] 4054 	sta	16,x
   C80D E6 13         [ 3] 4055 	lda	19,x
   C80F E7 0F         [ 3] 4056 	sta	15,x
   C811 4F            [ 1] 4057 	clra
   C812 E7 0E         [ 3] 4058 	sta	14,x
   C814 E6 10         [ 3] 4059 	lda	16,x
   C816 E7 11         [ 3] 4060 	sta	17,x
   C818 E6 0F         [ 3] 4061 	lda	15,x
   C81A E7 10         [ 3] 4062 	sta	16,x
   C81C E6 0E         [ 3] 4063 	lda	14,x
   C81E E7 0F         [ 3] 4064 	sta	15,x
   C820 5F            [ 1] 4065 	clrx
   C821 9E EF 0F      [ 4] 4066 	stx	15,s
   C824 95            [ 2] 4067 	tsx
   C825 E6 0D         [ 3] 4068 	lda	13,x
   C827 EA 11         [ 3] 4069 	ora	17,x
   C829 E7 0D         [ 3] 4070 	sta	13,x
   C82B E6 0C         [ 3] 4071 	lda	12,x
   C82D EA 10         [ 3] 4072 	ora	16,x
   C82F E7 0C         [ 3] 4073 	sta	12,x
   C831 E6 0B         [ 3] 4074 	lda	11,x
   C833 EA 0F         [ 3] 4075 	ora	15,x
   C835 E7 0B         [ 3] 4076 	sta	11,x
   C837 E6 0A         [ 3] 4077 	lda	10,x
   C839 EA 0E         [ 3] 4078 	ora	14,x
   C83B E7 0A         [ 3] 4079 	sta	10,x
   C83D 4F            [ 1] 4080 	clra
   C83E E7 11         [ 3] 4081 	sta	17,x
   C840 E7 10         [ 3] 4082 	sta	16,x
   C842 E7 0F         [ 3] 4083 	sta	15,x
   C844 E6 12         [ 3] 4084 	lda	18,x
   C846 E7 0E         [ 3] 4085 	sta	14,x
   C848 E6 0E         [ 3] 4086 	lda	14,x
   C84A E7 11         [ 3] 4087 	sta	17,x
   C84C 5F            [ 1] 4088 	clrx
   C84D 9E EF 11      [ 4] 4089 	stx	17,s
   C850 9E EF 10      [ 4] 4090 	stx	16,s
   C853 9E EF 0F      [ 4] 4091 	stx	15,s
   C856 95            [ 2] 4092 	tsx
   C857 E6 0D         [ 3] 4093 	lda	13,x
   C859 EA 11         [ 3] 4094 	ora	17,x
   C85B E7 0D         [ 3] 4095 	sta	13,x
   C85D E6 0C         [ 3] 4096 	lda	12,x
   C85F EA 10         [ 3] 4097 	ora	16,x
   C861 E7 0C         [ 3] 4098 	sta	12,x
   C863 E6 0B         [ 3] 4099 	lda	11,x
   C865 EA 0F         [ 3] 4100 	ora	15,x
   C867 E7 0B         [ 3] 4101 	sta	11,x
   C869 E6 0A         [ 3] 4102 	lda	10,x
   C86B EA 0E         [ 3] 4103 	ora	14,x
   C86D E7 0A         [ 3] 4104 	sta	10,x
                           4105 ;comms.c:692: response[0] = SERIAL_RC_OK;
   C86F 95            [ 2] 4106 	tsx
   C870 AF 05         [ 2] 4107 	aix	#5
   C872 8B            [ 2] 4108 	pshh
   C873 86            [ 2] 4109 	pula
   C874 9E E7 0F      [ 4] 4110 	sta	15,s
   C877 9E EF 10      [ 4] 4111 	stx	16,s
   C87A 9E E6 0F      [ 4] 4112 	lda	15,s
   C87D 87            [ 2] 4113 	psha
   C87E 8A            [ 2] 4114 	pulh
   C87F 9E EE 10      [ 4] 4115 	ldx	16,s
   C882 4F            [ 1] 4116 	clra
   C883 F7            [ 2] 4117 	sta	,x
                           4118 ;comms.c:693: response[1] = (uint8_t)(reversedCRC & 0xFF);
   C884 95            [ 2] 4119 	tsx
   C885 E6 0E         [ 3] 4120 	lda	14,x
   C887 E7 12         [ 3] 4121 	sta	18,x
   C889 E6 0F         [ 3] 4122 	lda	15,x
   C88B E7 13         [ 3] 4123 	sta	19,x
   C88D E6 0D         [ 3] 4124 	lda	13,x
   C88F EE 12         [ 3] 4125 	ldx	18,x
   C891 89            [ 2] 4126 	pshx
   C892 8A            [ 2] 4127 	pulh
   C893 9E EE 14      [ 4] 4128 	ldx	20,s
   C896 E7 01         [ 3] 4129 	sta	1,x
                           4130 ;comms.c:694: response[2] = (uint8_t)((reversedCRC >> 8) & 0xFF);
   C898 95            [ 2] 4131 	tsx
   C899 E6 0E         [ 3] 4132 	lda	14,x
   C89B E7 12         [ 3] 4133 	sta	18,x
   C89D E6 0F         [ 3] 4134 	lda	15,x
   C89F E7 13         [ 3] 4135 	sta	19,x
   C8A1 E6 0C         [ 3] 4136 	lda	12,x
   C8A3 EE 12         [ 3] 4137 	ldx	18,x
   C8A5 89            [ 2] 4138 	pshx
   C8A6 8A            [ 2] 4139 	pulh
   C8A7 9E EE 14      [ 4] 4140 	ldx	20,s
   C8AA E7 02         [ 3] 4141 	sta	2,x
                           4142 ;comms.c:695: response[3] = (uint8_t)((reversedCRC >> 16) & 0xFF);
   C8AC 95            [ 2] 4143 	tsx
   C8AD E6 0E         [ 3] 4144 	lda	14,x
   C8AF E7 12         [ 3] 4145 	sta	18,x
   C8B1 E6 0F         [ 3] 4146 	lda	15,x
   C8B3 E7 13         [ 3] 4147 	sta	19,x
   C8B5 E6 0B         [ 3] 4148 	lda	11,x
   C8B7 EE 12         [ 3] 4149 	ldx	18,x
   C8B9 89            [ 2] 4150 	pshx
   C8BA 8A            [ 2] 4151 	pulh
   C8BB 9E EE 14      [ 4] 4152 	ldx	20,s
   C8BE E7 03         [ 3] 4153 	sta	3,x
                           4154 ;comms.c:696: response[4] = (uint8_t)((reversedCRC >> 24) & 0xFF);
   C8C0 95            [ 2] 4155 	tsx
   C8C1 E6 0E         [ 3] 4156 	lda	14,x
   C8C3 E7 12         [ 3] 4157 	sta	18,x
   C8C5 E6 0F         [ 3] 4158 	lda	15,x
   C8C7 E7 13         [ 3] 4159 	sta	19,x
   C8C9 E6 0A         [ 3] 4160 	lda	10,x
   C8CB EE 12         [ 3] 4161 	ldx	18,x
   C8CD 89            [ 2] 4162 	pshx
   C8CE 8A            [ 2] 4163 	pulh
   C8CF 9E EE 14      [ 4] 4164 	ldx	20,s
   C8D2 E7 04         [ 3] 4165 	sta	4,x
                           4166 ;comms.c:698: sendU16BE(5);
   C8D4 A6 05         [ 2] 4167 	lda	#0x05
   C8D6 5F            [ 1] 4168 	clrx
   C8D7 CD B5 75      [ 5] 4169 	jsr	_sendU16BE
                           4170 ;comms.c:699: sendBytes(response, 5);
   C8DA 95            [ 2] 4171 	tsx
   C8DB E6 0E         [ 3] 4172 	lda	14,x
   C8DD E7 0A         [ 3] 4173 	sta	10,x
   C8DF E6 0F         [ 3] 4174 	lda	15,x
   C8E1 E7 0B         [ 3] 4175 	sta	11,x
   C8E3 E6 0A         [ 3] 4176 	lda	10,x
   C8E5 87            [ 2] 4177 	psha
   C8E6 8A            [ 2] 4178 	pulh
   C8E7 9E EE 0C      [ 4] 4179 	ldx	12,s
   C8EA A6 05         [ 2] 4180 	lda	#0x05
   C8EC 87            [ 2] 4181 	psha
   C8ED 4F            [ 1] 4182 	clra
   C8EE 87            [ 2] 4183 	psha
   C8EF 9F            [ 1] 4184 	txa
   C8F0 8B            [ 2] 4185 	pshh
   C8F1 88            [ 2] 4186 	pulx
   C8F2 CD B5 52      [ 5] 4187 	jsr	_sendBytes
   C8F5 A7 02         [ 2] 4188 	ais	#2
                           4189 ;comms.c:700: sendU32BE(calculateCRC32(response, 5));
   C8F7 95            [ 2] 4190 	tsx
   C8F8 E6 0E         [ 3] 4191 	lda	14,x
   C8FA E7 0A         [ 3] 4192 	sta	10,x
   C8FC E6 0F         [ 3] 4193 	lda	15,x
   C8FE E7 0B         [ 3] 4194 	sta	11,x
   C900 E6 0A         [ 3] 4195 	lda	10,x
   C902 87            [ 2] 4196 	psha
   C903 8A            [ 2] 4197 	pulh
   C904 9E EE 0C      [ 4] 4198 	ldx	12,s
   C907 A6 05         [ 2] 4199 	lda	#0x05
   C909 87            [ 2] 4200 	psha
   C90A 4F            [ 1] 4201 	clra
   C90B 87            [ 2] 4202 	psha
   C90C 9F            [ 1] 4203 	txa
   C90D 8B            [ 2] 4204 	pshh
   C90E 88            [ 2] 4205 	pulx
   C90F CD B4 C6      [ 5] 4206 	jsr	_calculateCRC32
   C912 9E E7 10      [ 4] 4207 	sta	16,s
   C915 9E EF 0F      [ 4] 4208 	stx	15,s
   C918 B6 4A         [ 3] 4209 	lda	*___SDCC_hc08_ret2
   C91A 9E E7 0E      [ 4] 4210 	sta	14,s
   C91D B6 4B         [ 3] 4211 	lda	*___SDCC_hc08_ret3
   C91F 9E E7 0D      [ 4] 4212 	sta	13,s
   C922 A7 02         [ 2] 4213 	ais	#2
   C924 95            [ 2] 4214 	tsx
   C925 E6 0D         [ 3] 4215 	lda	13,x
   C927 87            [ 2] 4216 	psha
   C928 E6 0C         [ 3] 4217 	lda	12,x
   C92A 87            [ 2] 4218 	psha
   C92B E6 0B         [ 3] 4219 	lda	11,x
   C92D 87            [ 2] 4220 	psha
   C92E E6 0A         [ 3] 4221 	lda	10,x
   C930 87            [ 2] 4222 	psha
   C931 CD B5 83      [ 5] 4223 	jsr	_sendU32BE
   C934 A7 04         [ 2] 4224 	ais	#4
   C936                    4225 00109$:
                           4226 ;comms.c:701: }
   C936 A7 1B         [ 2] 4227 	ais	#27
   C938 81            [ 4] 4228 	rts
                           4229 ;------------------------------------------------------------
                           4230 ;Allocation info for local variables in function 'sendOutputChannels'
                           4231 ;------------------------------------------------------------
                           4232 ;offset                    Allocated to stack - sp +13
                           4233 ;length                    Allocated to stack - sp +15
                           4234 ;subcmd                    Allocated to registers a 
                           4235 ;fullBufferSize            Allocated to registers 
                           4236 ;crc                       Allocated to stack - sp +1
                           4237 ;responseLength            Allocated to registers a x 
                           4238 ;i                         Allocated to stack - sp +9
                           4239 ;idx                       Allocated to registers a x 
                           4240 ;b                         Allocated to registers a 
                           4241 ;err                       Allocated to stack - sp +4
                           4242 ;sloc0                     Allocated to stack - sp +5
                           4243 ;------------------------------------------------------------
                           4244 ;comms.c:703: void sendOutputChannels(uint8_t subcmd, uint16_t offset, uint16_t length) {
                           4245 ;	-----------------------------------------
                           4246 ;	 function sendOutputChannels
                           4247 ;	-----------------------------------------
                           4248 ;	Register assignment is optimal.
                           4249 ;	Stack space usage: 10 bytes.
   C939                    4250 _sendOutputChannels:
   C939 A7 F6         [ 2] 4251 	ais	#-10
                           4252 ;comms.c:704: if (subcmd == 0x30) {
   C93B 41 30 03      [ 4] 4253 	cbeqa	#0x30,00147$
   C93E CC CA 23      [ 3] 4254 	jmp	00107$
   C941                    4255 00147$:
                           4256 ;comms.c:709: if (offset >= fullBufferSize) {
   C941 95            [ 2] 4257 	tsx
   C942 E6 0D         [ 3] 4258 	lda	13,x
   C944 A0 7F         [ 2] 4259 	sub	#0x7f
   C946 E6 0C         [ 3] 4260 	lda	12,x
   C948 A2 00         [ 2] 4261 	sbc	#0x00
   C94A 25 09         [ 3] 4262 	bcs	00102$
                           4263 ;comms.c:710: offset = 0;
   C94C 4F            [ 1] 4264 	clra
   C94D E7 0C         [ 3] 4265 	sta	12,x
   C94F E7 0D         [ 3] 4266 	sta	13,x
                           4267 ;comms.c:711: length = 0;
   C951 E7 0E         [ 3] 4268 	sta	14,x
   C953 E7 0F         [ 3] 4269 	sta	15,x
   C955                    4270 00102$:
                           4271 ;comms.c:713: if ((uint16_t)(offset + length) > fullBufferSize) {
   C955 9E E6 0E      [ 4] 4272 	lda	14,s
   C958 9E EB 10      [ 4] 4273 	add	16,s
   C95B 97            [ 1] 4274 	tax
   C95C 9E E6 0D      [ 4] 4275 	lda	13,s
   C95F 9E E9 0F      [ 4] 4276 	adc	15,s
   C962 87            [ 2] 4277 	psha
   C963 8A            [ 2] 4278 	pulh
   C964 65 00 7F      [ 3] 4279 	cphx	#0x007f
   C967 23 0C         [ 3] 4280 	bls	00104$
                           4281 ;comms.c:714: length = (uint16_t)(fullBufferSize - offset);
   C969 95            [ 2] 4282 	tsx
   C96A A6 7F         [ 2] 4283 	lda	#0x7f
   C96C E0 0D         [ 3] 4284 	sub	13,x
   C96E E7 0F         [ 3] 4285 	sta	15,x
   C970 4F            [ 1] 4286 	clra
   C971 E2 0C         [ 3] 4287 	sbc	12,x
   C973 E7 0E         [ 3] 4288 	sta	14,x
   C975                    4289 00104$:
                           4290 ;comms.c:717: responseLength = (uint16_t)(1 + length);
   C975 9E E6 10      [ 4] 4291 	lda	16,s
   C978 9E EE 0F      [ 4] 4292 	ldx	15,s
   C97B 4C            [ 1] 4293 	inca
   C97C 26 01         [ 3] 4294 	bne	00150$
   C97E 5C            [ 1] 4295 	incx
   C97F                    4296 00150$:
                           4297 ;comms.c:718: sendU16BE(responseLength);
   C97F CD B5 75      [ 5] 4298 	jsr	_sendU16BE
                           4299 ;comms.c:719: sendByte(SERIAL_RC_OK);
   C982 4F            [ 1] 4300 	clra
   C983 CD B5 4F      [ 5] 4301 	jsr	_sendByte
                           4302 ;comms.c:720: crc = crc32Update(crc, SERIAL_RC_OK);
   C986 4F            [ 1] 4303 	clra
   C987 87            [ 2] 4304 	psha
   C988 4A            [ 1] 4305 	deca
   C989 87            [ 2] 4306 	psha
   C98A 87            [ 2] 4307 	psha
   C98B 87            [ 2] 4308 	psha
   C98C 87            [ 2] 4309 	psha
   C98D CD B4 09      [ 5] 4310 	jsr	_crc32Update
   C990 9E E7 09      [ 4] 4311 	sta	9,s
   C993 9E EF 08      [ 4] 4312 	stx	8,s
   C996 B6 4A         [ 3] 4313 	lda	*___SDCC_hc08_ret2
   C998 9E E7 07      [ 4] 4314 	sta	7,s
   C99B B6 4B         [ 3] 4315 	lda	*___SDCC_hc08_ret3
   C99D 9E E7 06      [ 4] 4316 	sta	6,s
   C9A0 A7 05         [ 2] 4317 	ais	#5
                           4318 ;comms.c:722: for (i = 0; i < length; i++) {
   C9A2 95            [ 2] 4319 	tsx
   C9A3 4F            [ 1] 4320 	clra
   C9A4 E7 08         [ 3] 4321 	sta	8,x
   C9A6 E7 09         [ 3] 4322 	sta	9,x
   C9A8                    4323 00110$:
   C9A8 95            [ 2] 4324 	tsx
   C9A9 E6 09         [ 3] 4325 	lda	9,x
   C9AB E0 0F         [ 3] 4326 	sub	15,x
   C9AD E6 08         [ 3] 4327 	lda	8,x
   C9AF E2 0E         [ 3] 4328 	sbc	14,x
   C9B1 24 4B         [ 3] 4329 	bcc	00105$
                           4330 ;comms.c:723: uint16_t idx = (uint16_t)(offset + i);
   C9B3 E6 09         [ 3] 4331 	lda	9,x
   C9B5 EB 0D         [ 3] 4332 	add	13,x
   C9B7 87            [ 2] 4333 	psha
   C9B8 E6 08         [ 3] 4334 	lda	8,x
   C9BA E9 0C         [ 3] 4335 	adc	12,x
   C9BC 97            [ 1] 4336 	tax
   C9BD 86            [ 2] 4337 	pula
                           4338 ;comms.c:724: uint8_t b = (idx == 0) ? 0x00 : realtimeByte((uint8_t)(idx - 1));
   C9BE 4D            [ 1] 4339 	tsta
   C9BF 26 01         [ 3] 4340 	bne	00152$
   C9C1 5D            [ 1] 4341 	tstx
   C9C2                    4342 00152$:
   C9C2 26 04         [ 3] 4343 	bne	00114$
   C9C4 5F            [ 1] 4344 	clrx
   C9C5 9F            [ 1] 4345 	txa
   C9C6 20 05         [ 3] 4346 	bra	00115$
   C9C8                    4347 00114$:
   C9C8 4A            [ 1] 4348 	deca
   C9C9 CD CA 6C      [ 5] 4349 	jsr	_realtimeByte
   C9CC 5F            [ 1] 4350 	clrx
   C9CD                    4351 00115$:
                           4352 ;comms.c:725: sendByte(b);
   C9CD 87            [ 2] 4353 	psha
   C9CE CD B5 4F      [ 5] 4354 	jsr	_sendByte
   C9D1 86            [ 2] 4355 	pula
                           4356 ;comms.c:726: crc = crc32Update(crc, b);
   C9D2 87            [ 2] 4357 	psha
   C9D3 95            [ 2] 4358 	tsx
   C9D4 E6 04         [ 3] 4359 	lda	4,x
   C9D6 87            [ 2] 4360 	psha
   C9D7 E6 03         [ 3] 4361 	lda	3,x
   C9D9 87            [ 2] 4362 	psha
   C9DA E6 02         [ 3] 4363 	lda	2,x
   C9DC 87            [ 2] 4364 	psha
   C9DD E6 01         [ 3] 4365 	lda	1,x
   C9DF 87            [ 2] 4366 	psha
   C9E0 CD B4 09      [ 5] 4367 	jsr	_crc32Update
   C9E3 9E E7 09      [ 4] 4368 	sta	9,s
   C9E6 9E EF 08      [ 4] 4369 	stx	8,s
   C9E9 B6 4A         [ 3] 4370 	lda	*___SDCC_hc08_ret2
   C9EB 9E E7 07      [ 4] 4371 	sta	7,s
   C9EE B6 4B         [ 3] 4372 	lda	*___SDCC_hc08_ret3
   C9F0 9E E7 06      [ 4] 4373 	sta	6,s
   C9F3 A7 05         [ 2] 4374 	ais	#5
                           4375 ;comms.c:722: for (i = 0; i < length; i++) {
   C9F5 95            [ 2] 4376 	tsx
   C9F6 6C 09         [ 4] 4377 	inc	9,x
   C9F8 26 02         [ 3] 4378 	bne	00154$
   C9FA 6C 08         [ 4] 4379 	inc	8,x
   C9FC                    4380 00154$:
   C9FC 20 AA         [ 3] 4381 	bra	00110$
   C9FE                    4382 00105$:
                           4383 ;comms.c:728: crc = ~crc;
   C9FE 95            [ 2] 4384 	tsx
   C9FF E6 03         [ 3] 4385 	lda	3,x
   CA01 43            [ 1] 4386 	coma
   CA02 E7 03         [ 3] 4387 	sta	3,x
   CA04 E6 02         [ 3] 4388 	lda	2,x
   CA06 43            [ 1] 4389 	coma
   CA07 E7 02         [ 3] 4390 	sta	2,x
   CA09 E6 01         [ 3] 4391 	lda	1,x
   CA0B 43            [ 1] 4392 	coma
   CA0C E7 01         [ 3] 4393 	sta	1,x
   CA0E F6            [ 2] 4394 	lda	,x
   CA0F 43            [ 1] 4395 	coma
   CA10 F7            [ 2] 4396 	sta	,x
                           4397 ;comms.c:729: sendU32BE(crc);
   CA11 E6 03         [ 3] 4398 	lda	3,x
   CA13 87            [ 2] 4399 	psha
   CA14 E6 02         [ 3] 4400 	lda	2,x
   CA16 87            [ 2] 4401 	psha
   CA17 E6 01         [ 3] 4402 	lda	1,x
   CA19 87            [ 2] 4403 	psha
   CA1A F6            [ 2] 4404 	lda	,x
   CA1B 87            [ 2] 4405 	psha
   CA1C CD B5 83      [ 5] 4406 	jsr	_sendU32BE
   CA1F A7 04         [ 2] 4407 	ais	#4
   CA21 20 43         [ 3] 4408 	bra	00112$
   CA23                    4409 00107$:
                           4410 ;comms.c:731: uint8_t err = SERIAL_RC_UKWN_ERR;
   CA23 A6 83         [ 2] 4411 	lda	#0x83
   CA25 9E E7 04      [ 4] 4412 	sta	4,s
                           4413 ;comms.c:732: sendU16BE(1);
   CA28 A6 01         [ 2] 4414 	lda	#0x01
   CA2A 5F            [ 1] 4415 	clrx
   CA2B CD B5 75      [ 5] 4416 	jsr	_sendU16BE
                           4417 ;comms.c:733: sendByte(err);
   CA2E 9E E6 04      [ 4] 4418 	lda	4,s
   CA31 CD B5 4F      [ 5] 4419 	jsr	_sendByte
                           4420 ;comms.c:734: sendU32BE(calculateCRC32(&err, 1));
   CA34 95            [ 2] 4421 	tsx
   CA35 AF 03         [ 2] 4422 	aix	#3
   CA37 A6 01         [ 2] 4423 	lda	#0x01
   CA39 87            [ 2] 4424 	psha
   CA3A 4A            [ 1] 4425 	deca
   CA3B 87            [ 2] 4426 	psha
   CA3C 9F            [ 1] 4427 	txa
   CA3D 8B            [ 2] 4428 	pshh
   CA3E 88            [ 2] 4429 	pulx
   CA3F CD B4 C6      [ 5] 4430 	jsr	_calculateCRC32
   CA42 9E E7 0A      [ 4] 4431 	sta	10,s
   CA45 9E EF 09      [ 4] 4432 	stx	9,s
   CA48 B6 4A         [ 3] 4433 	lda	*___SDCC_hc08_ret2
   CA4A 9E E7 08      [ 4] 4434 	sta	8,s
   CA4D B6 4B         [ 3] 4435 	lda	*___SDCC_hc08_ret3
   CA4F 9E E7 07      [ 4] 4436 	sta	7,s
   CA52 A7 02         [ 2] 4437 	ais	#2
   CA54 95            [ 2] 4438 	tsx
   CA55 E6 07         [ 3] 4439 	lda	7,x
   CA57 87            [ 2] 4440 	psha
   CA58 E6 06         [ 3] 4441 	lda	6,x
   CA5A 87            [ 2] 4442 	psha
   CA5B E6 05         [ 3] 4443 	lda	5,x
   CA5D 87            [ 2] 4444 	psha
   CA5E E6 04         [ 3] 4445 	lda	4,x
   CA60 87            [ 2] 4446 	psha
   CA61 CD B5 83      [ 5] 4447 	jsr	_sendU32BE
   CA64 A7 04         [ 2] 4448 	ais	#4
   CA66                    4449 00112$:
                           4450 ;comms.c:736: }
   CA66 A7 0A         [ 2] 4451 	ais	#10
   CA68 81            [ 4] 4452 	rts
                           4453 ;------------------------------------------------------------
                           4454 ;Allocation info for local variables in function 'burnEEPROM'
                           4455 ;------------------------------------------------------------
                           4456 ;comms.c:738: void burnEEPROM(void) {
                           4457 ;	-----------------------------------------
                           4458 ;	 function burnEEPROM
                           4459 ;	-----------------------------------------
                           4460 ;	Register assignment is optimal.
                           4461 ;	Stack space usage: 0 bytes.
   CA69                    4462 _burnEEPROM:
                           4463 ;comms.c:739: saveAllConfig();
                           4464 ;comms.c:740: }
   CA69 CC 97 72      [ 3] 4465 	jmp	_saveAllConfig
                           4466 ;------------------------------------------------------------
                           4467 ;Allocation info for local variables in function 'realtimeByte'
                           4468 ;------------------------------------------------------------
                           4469 ;index                     Allocated to registers a 
                           4470 ;------------------------------------------------------------
                           4471 ;comms.c:751: uint8_t realtimeByte(uint8_t index) {
                           4472 ;	-----------------------------------------
                           4473 ;	 function realtimeByte
                           4474 ;	-----------------------------------------
                           4475 ;	Register assignment is optimal.
                           4476 ;	Stack space usage: 0 bytes.
   CA6C                    4477 _realtimeByte:
                           4478 ;comms.c:752: switch (index) {
   CA6C A1 66         [ 2] 4479 	cmp	#0x66
   CA6E 23 03         [ 3] 4480 	bls	00164$
   CA70 CC CC 1F      [ 3] 4481 	jmp	00134$
   CA73                    4482 00164$:
   CA73 97            [ 1] 4483 	tax
   CA74 8C            [ 1] 4484 	clrh
   CA75 D6 CA E5      [ 4] 4485 	lda	00166$,x
   CA78 DE CA 7E      [ 4] 4486 	ldx	00165$,x
   CA7B 87            [ 2] 4487 	psha
   CA7C 8A            [ 2] 4488 	pulh
   CA7D FC            [ 2] 4489 	jmp	,x
   CA7E                    4490 00165$:
   CA7E 4C                 4491 	.db	00101$
   CA7F 50                 4492 	.db	00102$
   CA80 62                 4493 	.db	00103$
   CA81 66                 4494 	.db	00104$
   CA82 72                 4495 	.db	00105$
   CA83 79                 4496 	.db	00106$
   CA84 88                 4497 	.db	00107$
   CA85 8E                 4498 	.db	00108$
   CA86 94                 4499 	.db	00109$
   CA87 98                 4500 	.db	00110$
   CA88 9C                 4501 	.db	00111$
   CA89 A0                 4502 	.db	00112$
   CA8A A3                 4503 	.db	00113$
   CA8B A6                 4504 	.db	00114$
   CA8C AA                 4505 	.db	00115$
   CA8D AE                 4506 	.db	00116$
   CA8E 1F                 4507 	.db	00134$
   CA8F 1F                 4508 	.db	00134$
   CA90 1F                 4509 	.db	00134$
   CA91 1F                 4510 	.db	00134$
   CA92 1F                 4511 	.db	00134$
   CA93 1F                 4512 	.db	00134$
   CA94 1F                 4513 	.db	00134$
   CA95 1F                 4514 	.db	00134$
   CA96 B6                 4515 	.db	00117$
   CA97 BC                 4516 	.db	00118$
   CA98 C0                 4517 	.db	00119$
   CA99 C3                 4518 	.db	00120$
   CA9A C6                 4519 	.db	00121$
   CA9B C9                 4520 	.db	00122$
   CA9C 1F                 4521 	.db	00134$
   CA9D 1F                 4522 	.db	00134$
   CA9E CE                 4523 	.db	00123$
   CA9F 1F                 4524 	.db	00134$
   CAA0 1F                 4525 	.db	00134$
   CAA1 1F                 4526 	.db	00134$
   CAA2 1F                 4527 	.db	00134$
   CAA3 1F                 4528 	.db	00134$
   CAA4 DA                 4529 	.db	00124$
   CAA5 1F                 4530 	.db	00134$
   CAA6 1F                 4531 	.db	00134$
   CAA7 DE                 4532 	.db	00125$
   CAA8 1F                 4533 	.db	00134$
   CAA9 1F                 4534 	.db	00134$
   CAAA 1F                 4535 	.db	00134$
   CAAB 1F                 4536 	.db	00134$
   CAAC 1F                 4537 	.db	00134$
   CAAD 1F                 4538 	.db	00134$
   CAAE 1F                 4539 	.db	00134$
   CAAF 1F                 4540 	.db	00134$
   CAB0 1F                 4541 	.db	00134$
   CAB1 1F                 4542 	.db	00134$
   CAB2 1F                 4543 	.db	00134$
   CAB3 1F                 4544 	.db	00134$
   CAB4 1F                 4545 	.db	00134$
   CAB5 1F                 4546 	.db	00134$
   CAB6 1F                 4547 	.db	00134$
   CAB7 1F                 4548 	.db	00134$
   CAB8 1F                 4549 	.db	00134$
   CAB9 1F                 4550 	.db	00134$
   CABA 1F                 4551 	.db	00134$
   CABB 1F                 4552 	.db	00134$
   CABC 1F                 4553 	.db	00134$
   CABD 1F                 4554 	.db	00134$
   CABE 1F                 4555 	.db	00134$
   CABF 1F                 4556 	.db	00134$
   CAC0 1F                 4557 	.db	00134$
   CAC1 1F                 4558 	.db	00134$
   CAC2 1F                 4559 	.db	00134$
   CAC3 1F                 4560 	.db	00134$
   CAC4 1F                 4561 	.db	00134$
   CAC5 1F                 4562 	.db	00134$
   CAC6 1F                 4563 	.db	00134$
   CAC7 1F                 4564 	.db	00134$
   CAC8 1F                 4565 	.db	00134$
   CAC9 1F                 4566 	.db	00134$
   CACA E1                 4567 	.db	00126$
   CACB E5                 4568 	.db	00127$
   CACC ED                 4569 	.db	00128$
   CACD F1                 4570 	.db	00129$
   CACE F9                 4571 	.db	00130$
   CACF FD                 4572 	.db	00131$
   CAD0 1F                 4573 	.db	00134$
   CAD1 1F                 4574 	.db	00134$
   CAD2 1F                 4575 	.db	00134$
   CAD3 1F                 4576 	.db	00134$
   CAD4 1F                 4577 	.db	00134$
   CAD5 1F                 4578 	.db	00134$
   CAD6 1F                 4579 	.db	00134$
   CAD7 1F                 4580 	.db	00134$
   CAD8 1F                 4581 	.db	00134$
   CAD9 1F                 4582 	.db	00134$
   CADA 05                 4583 	.db	00132$
   CADB 1F                 4584 	.db	00134$
   CADC 1F                 4585 	.db	00134$
   CADD 1F                 4586 	.db	00134$
   CADE 1F                 4587 	.db	00134$
   CADF 1F                 4588 	.db	00134$
   CAE0 1F                 4589 	.db	00134$
   CAE1 1F                 4590 	.db	00134$
   CAE2 1F                 4591 	.db	00134$
   CAE3 1F                 4592 	.db	00134$
   CAE4 1B                 4593 	.db	00133$
   CAE5                    4594 00166$:
   CAE5 CB                 4595 	.db	>00101$
   CAE6 CB                 4596 	.db	>00102$
   CAE7 CB                 4597 	.db	>00103$
   CAE8 CB                 4598 	.db	>00104$
   CAE9 CB                 4599 	.db	>00105$
   CAEA CB                 4600 	.db	>00106$
   CAEB CB                 4601 	.db	>00107$
   CAEC CB                 4602 	.db	>00108$
   CAED CB                 4603 	.db	>00109$
   CAEE CB                 4604 	.db	>00110$
   CAEF CB                 4605 	.db	>00111$
   CAF0 CB                 4606 	.db	>00112$
   CAF1 CB                 4607 	.db	>00113$
   CAF2 CB                 4608 	.db	>00114$
   CAF3 CB                 4609 	.db	>00115$
   CAF4 CB                 4610 	.db	>00116$
   CAF5 CC                 4611 	.db	>00134$
   CAF6 CC                 4612 	.db	>00134$
   CAF7 CC                 4613 	.db	>00134$
   CAF8 CC                 4614 	.db	>00134$
   CAF9 CC                 4615 	.db	>00134$
   CAFA CC                 4616 	.db	>00134$
   CAFB CC                 4617 	.db	>00134$
   CAFC CC                 4618 	.db	>00134$
   CAFD CB                 4619 	.db	>00117$
   CAFE CB                 4620 	.db	>00118$
   CAFF CB                 4621 	.db	>00119$
   CB00 CB                 4622 	.db	>00120$
   CB01 CB                 4623 	.db	>00121$
   CB02 CB                 4624 	.db	>00122$
   CB03 CC                 4625 	.db	>00134$
   CB04 CC                 4626 	.db	>00134$
   CB05 CB                 4627 	.db	>00123$
   CB06 CC                 4628 	.db	>00134$
   CB07 CC                 4629 	.db	>00134$
   CB08 CC                 4630 	.db	>00134$
   CB09 CC                 4631 	.db	>00134$
   CB0A CC                 4632 	.db	>00134$
   CB0B CB                 4633 	.db	>00124$
   CB0C CC                 4634 	.db	>00134$
   CB0D CC                 4635 	.db	>00134$
   CB0E CB                 4636 	.db	>00125$
   CB0F CC                 4637 	.db	>00134$
   CB10 CC                 4638 	.db	>00134$
   CB11 CC                 4639 	.db	>00134$
   CB12 CC                 4640 	.db	>00134$
   CB13 CC                 4641 	.db	>00134$
   CB14 CC                 4642 	.db	>00134$
   CB15 CC                 4643 	.db	>00134$
   CB16 CC                 4644 	.db	>00134$
   CB17 CC                 4645 	.db	>00134$
   CB18 CC                 4646 	.db	>00134$
   CB19 CC                 4647 	.db	>00134$
   CB1A CC                 4648 	.db	>00134$
   CB1B CC                 4649 	.db	>00134$
   CB1C CC                 4650 	.db	>00134$
   CB1D CC                 4651 	.db	>00134$
   CB1E CC                 4652 	.db	>00134$
   CB1F CC                 4653 	.db	>00134$
   CB20 CC                 4654 	.db	>00134$
   CB21 CC                 4655 	.db	>00134$
   CB22 CC                 4656 	.db	>00134$
   CB23 CC                 4657 	.db	>00134$
   CB24 CC                 4658 	.db	>00134$
   CB25 CC                 4659 	.db	>00134$
   CB26 CC                 4660 	.db	>00134$
   CB27 CC                 4661 	.db	>00134$
   CB28 CC                 4662 	.db	>00134$
   CB29 CC                 4663 	.db	>00134$
   CB2A CC                 4664 	.db	>00134$
   CB2B CC                 4665 	.db	>00134$
   CB2C CC                 4666 	.db	>00134$
   CB2D CC                 4667 	.db	>00134$
   CB2E CC                 4668 	.db	>00134$
   CB2F CC                 4669 	.db	>00134$
   CB30 CC                 4670 	.db	>00134$
   CB31 CB                 4671 	.db	>00126$
   CB32 CB                 4672 	.db	>00127$
   CB33 CB                 4673 	.db	>00128$
   CB34 CB                 4674 	.db	>00129$
   CB35 CB                 4675 	.db	>00130$
   CB36 CB                 4676 	.db	>00131$
   CB37 CC                 4677 	.db	>00134$
   CB38 CC                 4678 	.db	>00134$
   CB39 CC                 4679 	.db	>00134$
   CB3A CC                 4680 	.db	>00134$
   CB3B CC                 4681 	.db	>00134$
   CB3C CC                 4682 	.db	>00134$
   CB3D CC                 4683 	.db	>00134$
   CB3E CC                 4684 	.db	>00134$
   CB3F CC                 4685 	.db	>00134$
   CB40 CC                 4686 	.db	>00134$
   CB41 CC                 4687 	.db	>00132$
   CB42 CC                 4688 	.db	>00134$
   CB43 CC                 4689 	.db	>00134$
   CB44 CC                 4690 	.db	>00134$
   CB45 CC                 4691 	.db	>00134$
   CB46 CC                 4692 	.db	>00134$
   CB47 CC                 4693 	.db	>00134$
   CB48 CC                 4694 	.db	>00134$
   CB49 CC                 4695 	.db	>00134$
   CB4A CC                 4696 	.db	>00134$
   CB4B CC                 4697 	.db	>00133$
                           4698 ;comms.c:753: case 0:   return (uint8_t)(currentStatus.secl & 0xFF);
   CB4C                    4699 00101$:
   CB4C C6 00 94      [ 4] 4700 	lda	((_currentStatus + 0x0032)+3)
   CB4F 81            [ 4] 4701 	rts
                           4702 ;comms.c:754: case 1:   return (currentStatus.RPM > 0) ? 0x01 : 0x00;
   CB50                    4703 00102$:
   CB50 CE 00 5F      [ 4] 4704 	ldx	_currentStatus
   CB53 C6 00 60      [ 4] 4705 	lda	(_currentStatus + 1)
   CB56 26 01         [ 3] 4706 	bne	00167$
   CB58 5D            [ 1] 4707 	tstx
   CB59                    4708 00167$:
   CB59 27 04         [ 3] 4709 	beq	00138$
   CB5B 5F            [ 1] 4710 	clrx
   CB5C A6 01         [ 2] 4711 	lda	#0x01
   CB5E 81            [ 4] 4712 	rts
   CB5F                    4713 00138$:
   CB5F 5F            [ 1] 4714 	clrx
   CB60 9F            [ 1] 4715 	txa
   CB61 81            [ 4] 4716 	rts
                           4717 ;comms.c:755: case 2:   return currentStatus.engineStatus;
   CB62                    4718 00103$:
   CB62 C6 00 89      [ 4] 4719 	lda	(_currentStatus + 0x002a)
   CB65 81            [ 4] 4720 	rts
                           4721 ;comms.c:756: case 3:   return currentStatus.hasSync ? 0 : 1;
   CB66                    4722 00104$:
   CB66 C6 00 61      [ 4] 4723 	lda	(_currentStatus + 0x0002)
   CB69 27 03         [ 3] 4724 	beq	00140$
   CB6B 5F            [ 1] 4725 	clrx
   CB6C 9F            [ 1] 4726 	txa
   CB6D 81            [ 4] 4727 	rts
   CB6E                    4728 00140$:
   CB6E 5F            [ 1] 4729 	clrx
   CB6F A6 01         [ 2] 4730 	lda	#0x01
   CB71 81            [ 4] 4731 	rts
                           4732 ;comms.c:757: case 4:   return (uint8_t)(((uint16_t)(currentStatus.MAP * 10)) & 0xFF);
   CB72                    4733 00105$:
   CB72 C6 00 72      [ 4] 4734 	lda	(_currentStatus + 0x0013)
   CB75 AE 0A         [ 2] 4735 	ldx	#0x0a
   CB77 42            [ 5] 4736 	mul
   CB78 81            [ 4] 4737 	rts
                           4738 ;comms.c:758: case 5:   return (uint8_t)((((uint16_t)(currentStatus.MAP * 10)) >> 8) & 0xFF);
   CB79                    4739 00106$:
   CB79 C6 00 72      [ 4] 4740 	lda	(_currentStatus + 0x0013)
   CB7C 5F            [ 1] 4741 	clrx
   CB7D 87            [ 2] 4742 	psha
   CB7E 89            [ 2] 4743 	pshx
   CB7F A6 0A         [ 2] 4744 	lda	#0x0a
   CB81 CD CE 65      [ 5] 4745 	jsr	__mulint
   CB84 A7 02         [ 2] 4746 	ais	#2
   CB86 9F            [ 1] 4747 	txa
   CB87 81            [ 4] 4748 	rts
                           4749 ;comms.c:759: case 6:   return (uint8_t)(currentStatus.IAT + 40);
   CB88                    4750 00107$:
   CB88 C6 00 75      [ 4] 4751 	lda	(_currentStatus + 0x0016)
   CB8B AB 28         [ 2] 4752 	add	#0x28
   CB8D 81            [ 4] 4753 	rts
                           4754 ;comms.c:760: case 7:   return (uint8_t)(currentStatus.coolant + 40);
   CB8E                    4755 00108$:
   CB8E C6 00 74      [ 4] 4756 	lda	(_currentStatus + 0x0015)
   CB91 AB 28         [ 2] 4757 	add	#0x28
   CB93 81            [ 4] 4758 	rts
                           4759 ;comms.c:761: case 8:   return currentStatus.batCorrection;
   CB94                    4760 00109$:
   CB94 C6 00 88      [ 4] 4761 	lda	(_currentStatus + 0x0029)
   CB97 81            [ 4] 4762 	rts
                           4763 ;comms.c:762: case 9:   return currentStatus.battery10;
   CB98                    4764 00110$:
   CB98 C6 00 78      [ 4] 4765 	lda	(_currentStatus + 0x0019)
   CB9B 81            [ 4] 4766 	rts
                           4767 ;comms.c:763: case 10:  return currentStatus.O2;
   CB9C                    4768 00111$:
   CB9C C6 00 76      [ 4] 4769 	lda	(_currentStatus + 0x0017)
   CB9F 81            [ 4] 4770 	rts
                           4771 ;comms.c:764: case 11:  return 100;
   CBA0                    4772 00112$:
   CBA0 A6 64         [ 2] 4773 	lda	#0x64
   CBA2 81            [ 4] 4774 	rts
                           4775 ;comms.c:765: case 12:  return 100;
   CBA3                    4776 00113$:
   CBA3 A6 64         [ 2] 4777 	lda	#0x64
   CBA5 81            [ 4] 4778 	rts
                           4779 ;comms.c:766: case 13:  return currentStatus.wueCorrection;
   CBA6                    4780 00114$:
   CBA6 C6 00 87      [ 4] 4781 	lda	(_currentStatus + 0x0028)
   CBA9 81            [ 4] 4782 	rts
                           4783 ;comms.c:767: case 14:  return (uint8_t)(currentStatus.RPM & 0xFF);
   CBAA                    4784 00115$:
   CBAA C6 00 60      [ 4] 4785 	lda	(_currentStatus+1)
   CBAD 81            [ 4] 4786 	rts
                           4787 ;comms.c:768: case 15:  return (uint8_t)((currentStatus.RPM >> 8) & 0xFF);
   CBAE                    4788 00116$:
   CBAE CE 00 5F      [ 4] 4789 	ldx	_currentStatus
   CBB1 C6 00 60      [ 4] 4790 	lda	(_currentStatus + 1)
   CBB4 9F            [ 1] 4791 	txa
   CBB5 81            [ 4] 4792 	rts
                           4793 ;comms.c:769: case 24:  return (uint8_t)(currentStatus.advance + 40);
   CBB6                    4794 00117$:
   CBB6 C6 00 84      [ 4] 4795 	lda	(_currentStatus + 0x0025)
   CBB9 AB 28         [ 2] 4796 	add	#0x28
   CBBB 81            [ 4] 4797 	rts
                           4798 ;comms.c:770: case 25:  return currentStatus.TPS;
   CBBC                    4799 00118$:
   CBBC C6 00 73      [ 4] 4800 	lda	(_currentStatus + 0x0014)
   CBBF 81            [ 4] 4801 	rts
                           4802 ;comms.c:771: case 26:  return (uint8_t)(2000U & 0xFF);
   CBC0                    4803 00119$:
   CBC0 A6 D0         [ 2] 4804 	lda	#0xd0
   CBC2 81            [ 4] 4805 	rts
                           4806 ;comms.c:772: case 27:  return (uint8_t)((2000U >> 8) & 0xFF);
   CBC3                    4807 00120$:
   CBC3 A6 07         [ 2] 4808 	lda	#0x07
   CBC5 81            [ 4] 4809 	rts
                           4810 ;comms.c:773: case 28:  return (uint8_t)(getFreeRam() & 0xFF);
   CBC6                    4811 00121$:
   CBC6 CC B4 B5      [ 3] 4812 	jmp	_getFreeRam
                           4813 ;comms.c:774: case 29:  return (uint8_t)((getFreeRam() >> 8) & 0xFF);
   CBC9                    4814 00122$:
   CBC9 CD B4 B5      [ 5] 4815 	jsr	_getFreeRam
   CBCC 9F            [ 1] 4816 	txa
   CBCD 81            [ 4] 4817 	rts
                           4818 ;comms.c:775: case 32:  return currentStatus.hasSync ? 0x01 : 0x00;
   CBCE                    4819 00123$:
   CBCE C6 00 61      [ 4] 4820 	lda	(_currentStatus + 0x0002)
   CBD1 27 04         [ 3] 4821 	beq	00142$
   CBD3 5F            [ 1] 4822 	clrx
   CBD4 A6 01         [ 2] 4823 	lda	#0x01
   CBD6 81            [ 4] 4824 	rts
   CBD7                    4825 00142$:
   CBD7 5F            [ 1] 4826 	clrx
   CBD8 9F            [ 1] 4827 	txa
   CBD9 81            [ 4] 4828 	rts
                           4829 ;comms.c:776: case 38:  return currentStatus.idleValveDuty;
   CBDA                    4830 00124$:
   CBDA C6 00 8D      [ 4] 4831 	lda	(_currentStatus + 0x002e)
   CBDD 81            [ 4] 4832 	rts
                           4833 ;comms.c:777: case 41:  return 100;
   CBDE                    4834 00125$:
   CBDE A6 64         [ 2] 4835 	lda	#0x64
   CBE0 81            [ 4] 4836 	rts
                           4837 ;comms.c:778: case 76:  return (uint8_t)(currentStatus.PW1 & 0xFF);
   CBE1                    4838 00126$:
   CBE1 C6 00 7C      [ 4] 4839 	lda	((_currentStatus + 0x001c)+1)
   CBE4 81            [ 4] 4840 	rts
                           4841 ;comms.c:779: case 77:  return (uint8_t)((currentStatus.PW1 >> 8) & 0xFF);
   CBE5                    4842 00127$:
   CBE5 CE 00 7B      [ 4] 4843 	ldx	(_currentStatus + 0x001c)
   CBE8 C6 00 7C      [ 4] 4844 	lda	((_currentStatus + 0x001c) + 1)
   CBEB 9F            [ 1] 4845 	txa
   CBEC 81            [ 4] 4846 	rts
                           4847 ;comms.c:780: case 78:  return (uint8_t)(currentStatus.PW2 & 0xFF);
   CBED                    4848 00128$:
   CBED C6 00 7E      [ 4] 4849 	lda	((_currentStatus + 0x001e)+1)
   CBF0 81            [ 4] 4850 	rts
                           4851 ;comms.c:781: case 79:  return (uint8_t)((currentStatus.PW2 >> 8) & 0xFF);
   CBF1                    4852 00129$:
   CBF1 CE 00 7D      [ 4] 4853 	ldx	(_currentStatus + 0x001e)
   CBF4 C6 00 7E      [ 4] 4854 	lda	((_currentStatus + 0x001e) + 1)
   CBF7 9F            [ 1] 4855 	txa
   CBF8 81            [ 4] 4856 	rts
                           4857 ;comms.c:782: case 80:  return (uint8_t)(currentStatus.PW3 & 0xFF);
   CBF9                    4858 00130$:
   CBF9 C6 00 80      [ 4] 4859 	lda	((_currentStatus + 0x0020)+1)
   CBFC 81            [ 4] 4860 	rts
                           4861 ;comms.c:783: case 81:  return (uint8_t)((currentStatus.PW3 >> 8) & 0xFF);
   CBFD                    4862 00131$:
   CBFD CE 00 7F      [ 4] 4863 	ldx	(_currentStatus + 0x0020)
   CC00 C6 00 80      [ 4] 4864 	lda	((_currentStatus + 0x0020) + 1)
   CC03 9F            [ 1] 4865 	txa
   CC04 81            [ 4] 4866 	rts
                           4867 ;comms.c:784: case 92:  return (uint8_t)(currentStatus.CLIdleTarget / 10U);
   CC05                    4868 00132$:
   CC05 C6 00 8E      [ 4] 4869 	lda	(_currentStatus + 0x002f)
   CC08 87            [ 2] 4870 	psha
   CC09 8A            [ 2] 4871 	pulh
   CC0A CE 00 8F      [ 4] 4872 	ldx	((_currentStatus + 0x002f) + 1)
   CC0D A6 0A         [ 2] 4873 	lda	#0x0a
   CC0F 87            [ 2] 4874 	psha
   CC10 4F            [ 1] 4875 	clra
   CC11 87            [ 2] 4876 	psha
   CC12 9F            [ 1] 4877 	txa
   CC13 8B            [ 2] 4878 	pshh
   CC14 88            [ 2] 4879 	pulx
   CC15 CD CE 04      [ 5] 4880 	jsr	__divuint
   CC18 A7 02         [ 2] 4881 	ais	#2
   CC1A 81            [ 4] 4882 	rts
                           4883 ;comms.c:785: case 102: return currentStatus.VE;
   CC1B                    4884 00133$:
   CC1B C6 00 81      [ 4] 4885 	lda	(_currentStatus + 0x0022)
   CC1E 81            [ 4] 4886 	rts
                           4887 ;comms.c:786: default:  return 0;
   CC1F                    4888 00134$:
   CC1F 4F            [ 1] 4889 	clra
                           4890 ;comms.c:787: }
                           4891 ;comms.c:788: }
   CC20 81            [ 4] 4892 	rts
                           4893 	.area CSEG    (CODE)
                           4894 	.area CONST   (CODE)
   D254                    4895 _crc32_table:
   D254 00 00 00 00        4896 	.byte #0x00, #0x00, #0x00, #0x00	; 0
   D258 77 07 30 96        4897 	.byte #0x77, #0x07, #0x30, #0x96	; 1996959894
   D25C EE 0E 61 2C        4898 	.byte #0xee, #0x0e, #0x61, #0x2c	; 3993919788
   D260 99 09 51 BA        4899 	.byte #0x99, #0x09, #0x51, #0xba	; 2567524794
   D264 07 6D C4 19        4900 	.byte #0x07, #0x6d, #0xc4, #0x19	; 124634137
   D268 70 6A F4 8F        4901 	.byte #0x70, #0x6a, #0xf4, #0x8f	; 1886057615
   D26C E9 63 A5 35        4902 	.byte #0xe9, #0x63, #0xa5, #0x35	; 3915621685
   D270 9E 64 95 A3        4903 	.byte #0x9e, #0x64, #0x95, #0xa3	; 2657392035
   D274 0E DB 88 32        4904 	.byte #0x0e, #0xdb, #0x88, #0x32	; 249268274
   D278 79 DC B8 A4        4905 	.byte #0x79, #0xdc, #0xb8, #0xa4	; 2044508324
   D27C E0 D5 E9 1E        4906 	.byte #0xe0, #0xd5, #0xe9, #0x1e	; 3772115230
   D280 97 D2 D9 88        4907 	.byte #0x97, #0xd2, #0xd9, #0x88	; 2547177864
   D284 09 B6 4C 2B        4908 	.byte #0x09, #0xb6, #0x4c, #0x2b	; 162941995
   D288 7E B1 7C BD        4909 	.byte #0x7e, #0xb1, #0x7c, #0xbd	; 2125561021
   D28C E7 B8 2D 07        4910 	.byte #0xe7, #0xb8, #0x2d, #0x07	; 3887607047
   D290 90 BF 1D 91        4911 	.byte #0x90, #0xbf, #0x1d, #0x91	; 2428444049
   D294 1D B7 10 64        4912 	.byte #0x1d, #0xb7, #0x10, #0x64	; 498536548
   D298 6A B0 20 F2        4913 	.byte #0x6a, #0xb0, #0x20, #0xf2	; 1789927666
   D29C F3 B9 71 48        4914 	.byte #0xf3, #0xb9, #0x71, #0x48	; 4089016648
   D2A0 84 BE 41 DE        4915 	.byte #0x84, #0xbe, #0x41, #0xde	; 2227061214
   D2A4 1A DA D4 7D        4916 	.byte #0x1a, #0xda, #0xd4, #0x7d	; 450548861
   D2A8 6D DD E4 EB        4917 	.byte #0x6d, #0xdd, #0xe4, #0xeb	; 1843258603
   D2AC F4 D4 B5 51        4918 	.byte #0xf4, #0xd4, #0xb5, #0x51	; 4107580753
   D2B0 83 D3 85 C7        4919 	.byte #0x83, #0xd3, #0x85, #0xc7	; 2211677639
   D2B4 13 6C 98 56        4920 	.byte #0x13, #0x6c, #0x98, #0x56	; 325883990
   D2B8 64 6B A8 C0        4921 	.byte #0x64, #0x6b, #0xa8, #0xc0	; 1684777152
   D2BC FD 62 F9 7A        4922 	.byte #0xfd, #0x62, #0xf9, #0x7a	; 4251122042
   D2C0 8A 65 C9 EC        4923 	.byte #0x8a, #0x65, #0xc9, #0xec	; 2321926636
   D2C4 14 01 5C 4F        4924 	.byte #0x14, #0x01, #0x5c, #0x4f	; 335633487
   D2C8 63 06 6C D9        4925 	.byte #0x63, #0x06, #0x6c, #0xd9	; 1661365465
   D2CC FA 0F 3D 63        4926 	.byte #0xfa, #0x0f, #0x3d, #0x63	; 4195302755
   D2D0 8D 08 0D F5        4927 	.byte #0x8d, #0x08, #0x0d, #0xf5	; 2366115317
   D2D4 3B 6E 20 C8        4928 	.byte #0x3b, #0x6e, #0x20, #0xc8	; 997073096
   D2D8 4C 69 10 5E        4929 	.byte #0x4c, #0x69, #0x10, #0x5e	; 1281953886
   D2DC D5 60 41 E4        4930 	.byte #0xd5, #0x60, #0x41, #0xe4	; 3579855332
   D2E0 A2 67 71 72        4931 	.byte #0xa2, #0x67, #0x71, #0x72	; 2724688242
   D2E4 3C 03 E4 D1        4932 	.byte #0x3c, #0x03, #0xe4, #0xd1	; 1006888145
   D2E8 4B 04 D4 47        4933 	.byte #0x4b, #0x04, #0xd4, #0x47	; 1258607687
   D2EC D2 0D 85 FD        4934 	.byte #0xd2, #0x0d, #0x85, #0xfd	; 3524101629
   D2F0 A5 0A B5 6B        4935 	.byte #0xa5, #0x0a, #0xb5, #0x6b	; 2768942443
   D2F4 35 B5 A8 FA        4936 	.byte #0x35, #0xb5, #0xa8, #0xfa	; 901097722
   D2F8 42 B2 98 6C        4937 	.byte #0x42, #0xb2, #0x98, #0x6c	; 1119000684
   D2FC DB BB C9 D6        4938 	.byte #0xdb, #0xbb, #0xc9, #0xd6	; 3686517206
   D300 AC BC F9 40        4939 	.byte #0xac, #0xbc, #0xf9, #0x40	; 2898065728
   D304 32 D8 6C E3        4940 	.byte #0x32, #0xd8, #0x6c, #0xe3	; 853044451
   D308 45 DF 5C 75        4941 	.byte #0x45, #0xdf, #0x5c, #0x75	; 1172266101
   D30C DC D6 0D CF        4942 	.byte #0xdc, #0xd6, #0x0d, #0xcf	; 3705015759
   D310 AB D1 3D 59        4943 	.byte #0xab, #0xd1, #0x3d, #0x59	; 2882616665
   D314 26 D9 30 AC        4944 	.byte #0x26, #0xd9, #0x30, #0xac	; 651767980
   D318 51 DE 00 3A        4945 	.byte #0x51, #0xde, #0x00, #0x3a	; 1373503546
   D31C C8 D7 51 80        4946 	.byte #0xc8, #0xd7, #0x51, #0x80	; 3369554304
   D320 BF D0 61 16        4947 	.byte #0xbf, #0xd0, #0x61, #0x16	; 3218104598
   D324 21 B4 F4 B5        4948 	.byte #0x21, #0xb4, #0xf4, #0xb5	; 565507253
   D328 56 B3 C4 23        4949 	.byte #0x56, #0xb3, #0xc4, #0x23	; 1454621731
   D32C CF BA 95 99        4950 	.byte #0xcf, #0xba, #0x95, #0x99	; 3485111705
   D330 B8 BD A5 0F        4951 	.byte #0xb8, #0xbd, #0xa5, #0x0f	; 3099436303
   D334 28 02 B8 9E        4952 	.byte #0x28, #0x02, #0xb8, #0x9e	; 671266974
   D338 5F 05 88 08        4953 	.byte #0x5f, #0x05, #0x88, #0x08	; 1594198024
   D33C C6 0C D9 B2        4954 	.byte #0xc6, #0x0c, #0xd9, #0xb2	; 3322730930
   D340 B1 0B E9 24        4955 	.byte #0xb1, #0x0b, #0xe9, #0x24	; 2970347812
   D344 2F 6F 7C 87        4956 	.byte #0x2f, #0x6f, #0x7c, #0x87	; 795835527
   D348 58 68 4C 11        4957 	.byte #0x58, #0x68, #0x4c, #0x11	; 1483230225
   D34C C1 61 1D AB        4958 	.byte #0xc1, #0x61, #0x1d, #0xab	; 3244367275
   D350 B6 66 2D 3D        4959 	.byte #0xb6, #0x66, #0x2d, #0x3d	; 3060149565
   D354 76 DC 41 90        4960 	.byte #0x76, #0xdc, #0x41, #0x90	; 1994146192
   D358 01 DB 71 06        4961 	.byte #0x01, #0xdb, #0x71, #0x06	; 31158534
   D35C 98 D2 20 BC        4962 	.byte #0x98, #0xd2, #0x20, #0xbc	; 2563907772
   D360 EF D5 10 2A        4963 	.byte #0xef, #0xd5, #0x10, #0x2a	; 4023717930
   D364 71 B1 85 89        4964 	.byte #0x71, #0xb1, #0x85, #0x89	; 1907459465
   D368 06 B6 B5 1F        4965 	.byte #0x06, #0xb6, #0xb5, #0x1f	; 112637215
   D36C 9F BF E4 A5        4966 	.byte #0x9f, #0xbf, #0xe4, #0xa5	; 2680153253
   D370 E8 B8 D4 33        4967 	.byte #0xe8, #0xb8, #0xd4, #0x33	; 3904427059
   D374 78 07 C9 A2        4968 	.byte #0x78, #0x07, #0xc9, #0xa2	; 2013776290
   D378 0F 00 F9 34        4969 	.byte #0x0f, #0x00, #0xf9, #0x34	; 251722036
   D37C 96 09 A8 8E        4970 	.byte #0x96, #0x09, #0xa8, #0x8e	; 2517215374
   D380 E1 0E 98 18        4971 	.byte #0xe1, #0x0e, #0x98, #0x18	; 3775830040
   D384 7F 6A 0D BB        4972 	.byte #0x7f, #0x6a, #0x0d, #0xbb	; 2137656763
   D388 08 6D 3D 2D        4973 	.byte #0x08, #0x6d, #0x3d, #0x2d	; 141376813
   D38C 91 64 6C 97        4974 	.byte #0x91, #0x64, #0x6c, #0x97	; 2439277719
   D390 E6 63 5C 01        4975 	.byte #0xe6, #0x63, #0x5c, #0x01	; 3865271297
   D394 6B 6B 51 F4        4976 	.byte #0x6b, #0x6b, #0x51, #0xf4	; 1802195444
   D398 1C 6C 61 62        4977 	.byte #0x1c, #0x6c, #0x61, #0x62	; 476864866
   D39C 85 65 30 D8        4978 	.byte #0x85, #0x65, #0x30, #0xd8	; 2238001368
   D3A0 F2 62 00 4E        4979 	.byte #0xf2, #0x62, #0x00, #0x4e	; 4066508878
   D3A4 6C 06 95 ED        4980 	.byte #0x6c, #0x06, #0x95, #0xed	; 1812370925
   D3A8 1B 01 A5 7B        4981 	.byte #0x1b, #0x01, #0xa5, #0x7b	; 453092731
   D3AC 82 08 F4 C1        4982 	.byte #0x82, #0x08, #0xf4, #0xc1	; 2181625025
   D3B0 F5 0F C4 57        4983 	.byte #0xf5, #0x0f, #0xc4, #0x57	; 4111451223
   D3B4 65 B0 D9 C6        4984 	.byte #0x65, #0xb0, #0xd9, #0xc6	; 1706088902
   D3B8 12 B7 E9 50        4985 	.byte #0x12, #0xb7, #0xe9, #0x50	; 314042704
   D3BC 8B BE B8 EA        4986 	.byte #0x8b, #0xbe, #0xb8, #0xea	; 2344532202
   D3C0 FC B9 88 7C        4987 	.byte #0xfc, #0xb9, #0x88, #0x7c	; 4240017532
   D3C4 62 DD 1D DF        4988 	.byte #0x62, #0xdd, #0x1d, #0xdf	; 1658658271
   D3C8 15 DA 2D 49        4989 	.byte #0x15, #0xda, #0x2d, #0x49	; 366619977
   D3CC 8C D3 7C F3        4990 	.byte #0x8c, #0xd3, #0x7c, #0xf3	; 2362670323
   D3D0 FB D4 4C 65        4991 	.byte #0xfb, #0xd4, #0x4c, #0x65	; 4224994405
   D3D4 4D B2 61 58        4992 	.byte #0x4d, #0xb2, #0x61, #0x58	; 1303535960
   D3D8 3A B5 51 CE        4993 	.byte #0x3a, #0xb5, #0x51, #0xce	; 984961486
   D3DC A3 BC 00 74        4994 	.byte #0xa3, #0xbc, #0x00, #0x74	; 2747007092
   D3E0 D4 BB 30 E2        4995 	.byte #0xd4, #0xbb, #0x30, #0xe2	; 3569037538
   D3E4 4A DF A5 41        4996 	.byte #0x4a, #0xdf, #0xa5, #0x41	; 1256170817
   D3E8 3D D8 95 D7        4997 	.byte #0x3d, #0xd8, #0x95, #0xd7	; 1037604311
   D3EC A4 D1 C4 6D        4998 	.byte #0xa4, #0xd1, #0xc4, #0x6d	; 2765210733
   D3F0 D3 D6 F4 FB        4999 	.byte #0xd3, #0xd6, #0xf4, #0xfb	; 3554079995
   D3F4 43 69 E9 6A        5000 	.byte #0x43, #0x69, #0xe9, #0x6a	; 1131014506
   D3F8 34 6E D9 FC        5001 	.byte #0x34, #0x6e, #0xd9, #0xfc	; 879679996
   D3FC AD 67 88 46        5002 	.byte #0xad, #0x67, #0x88, #0x46	; 2909243462
   D400 DA 60 B8 D0        5003 	.byte #0xda, #0x60, #0xb8, #0xd0	; 3663771856
   D404 44 04 2D 73        5004 	.byte #0x44, #0x04, #0x2d, #0x73	; 1141124467
   D408 33 03 1D E5        5005 	.byte #0x33, #0x03, #0x1d, #0xe5	; 855842277
   D40C AA 0A 4C 5F        5006 	.byte #0xaa, #0x0a, #0x4c, #0x5f	; 2852801631
   D410 DD 0D 7C C9        5007 	.byte #0xdd, #0x0d, #0x7c, #0xc9	; 3708648649
   D414 50 05 71 3C        5008 	.byte #0x50, #0x05, #0x71, #0x3c	; 1342533948
   D418 27 02 41 AA        5009 	.byte #0x27, #0x02, #0x41, #0xaa	; 654459306
   D41C BE 0B 10 10        5010 	.byte #0xbe, #0x0b, #0x10, #0x10	; 3188396048
   D420 C9 0C 20 86        5011 	.byte #0xc9, #0x0c, #0x20, #0x86	; 3373015174
   D424 57 68 B5 25        5012 	.byte #0x57, #0x68, #0xb5, #0x25	; 1466479909
   D428 20 6F 85 B3        5013 	.byte #0x20, #0x6f, #0x85, #0xb3	; 544179635
   D42C B9 66 D4 09        5014 	.byte #0xb9, #0x66, #0xd4, #0x09	; 3110523913
   D430 CE 61 E4 9F        5015 	.byte #0xce, #0x61, #0xe4, #0x9f	; 3462522015
   D434 5E DE F9 0E        5016 	.byte #0x5e, #0xde, #0xf9, #0x0e	; 1591671054
   D438 29 D9 C9 98        5017 	.byte #0x29, #0xd9, #0xc9, #0x98	; 702138776
   D43C B0 D0 98 22        5018 	.byte #0xb0, #0xd0, #0x98, #0x22	; 2966460450
   D440 C7 D7 A8 B4        5019 	.byte #0xc7, #0xd7, #0xa8, #0xb4	; 3352799412
   D444 59 B3 3D 17        5020 	.byte #0x59, #0xb3, #0x3d, #0x17	; 1504918807
   D448 2E B4 0D 81        5021 	.byte #0x2e, #0xb4, #0x0d, #0x81	; 783551873
   D44C B7 BD 5C 3B        5022 	.byte #0xb7, #0xbd, #0x5c, #0x3b	; 3082640443
   D450 C0 BA 6C AD        5023 	.byte #0xc0, #0xba, #0x6c, #0xad	; 3233442989
   D454 ED B8 83 20        5024 	.byte #0xed, #0xb8, #0x83, #0x20	; 3988292384
   D458 9A BF B3 B6        5025 	.byte #0x9a, #0xbf, #0xb3, #0xb6	; 2596254646
   D45C 03 B6 E2 0C        5026 	.byte #0x03, #0xb6, #0xe2, #0x0c	; 62317068
   D460 74 B1 D2 9A        5027 	.byte #0x74, #0xb1, #0xd2, #0x9a	; 1957810842
   D464 EA D5 47 39        5028 	.byte #0xea, #0xd5, #0x47, #0x39	; 3939845945
   D468 9D D2 77 AF        5029 	.byte #0x9d, #0xd2, #0x77, #0xaf	; 2647816111
   D46C 04 DB 26 15        5030 	.byte #0x04, #0xdb, #0x26, #0x15	; 81470997
   D470 73 DC 16 83        5031 	.byte #0x73, #0xdc, #0x16, #0x83	; 1943803523
   D474 E3 63 0B 12        5032 	.byte #0xe3, #0x63, #0x0b, #0x12	; 3814918930
   D478 94 64 3B 84        5033 	.byte #0x94, #0x64, #0x3b, #0x84	; 2489596804
   D47C 0D 6D 6A 3E        5034 	.byte #0x0d, #0x6d, #0x6a, #0x3e	; 225274430
   D480 7A 6A 5A A8        5035 	.byte #0x7a, #0x6a, #0x5a, #0xa8	; 2053790376
   D484 E4 0E CF 0B        5036 	.byte #0xe4, #0x0e, #0xcf, #0x0b	; 3826175755
   D488 93 09 FF 9D        5037 	.byte #0x93, #0x09, #0xff, #0x9d	; 2466906013
   D48C 0A 00 AE 27        5038 	.byte #0x0a, #0x00, #0xae, #0x27	; 167816743
   D490 7D 07 9E B1        5039 	.byte #0x7d, #0x07, #0x9e, #0xb1	; 2097651377
   D494 F0 0F 93 44        5040 	.byte #0xf0, #0x0f, #0x93, #0x44	; 4027552580
   D498 87 08 A3 D2        5041 	.byte #0x87, #0x08, #0xa3, #0xd2	; 2265490386
   D49C 1E 01 F2 68        5042 	.byte #0x1e, #0x01, #0xf2, #0x68	; 503444072
   D4A0 69 06 C2 FE        5043 	.byte #0x69, #0x06, #0xc2, #0xfe	; 1762050814
   D4A4 F7 62 57 5D        5044 	.byte #0xf7, #0x62, #0x57, #0x5d	; 4150417245
   D4A8 80 65 67 CB        5045 	.byte #0x80, #0x65, #0x67, #0xcb	; 2154129355
   D4AC 19 6C 36 71        5046 	.byte #0x19, #0x6c, #0x36, #0x71	; 426522225
   D4B0 6E 6B 06 E7        5047 	.byte #0x6e, #0x6b, #0x06, #0xe7	; 1852507879
   D4B4 FE D4 1B 76        5048 	.byte #0xfe, #0xd4, #0x1b, #0x76	; 4275313526
   D4B8 89 D3 2B E0        5049 	.byte #0x89, #0xd3, #0x2b, #0xe0	; 2312317920
   D4BC 10 DA 7A 5A        5050 	.byte #0x10, #0xda, #0x7a, #0x5a	; 282753626
   D4C0 67 DD 4A CC        5051 	.byte #0x67, #0xdd, #0x4a, #0xcc	; 1742555852
   D4C4 F9 B9 DF 6F        5052 	.byte #0xf9, #0xb9, #0xdf, #0x6f	; 4189708143
   D4C8 8E BE EF F9        5053 	.byte #0x8e, #0xbe, #0xef, #0xf9	; 2394877945
   D4CC 17 B7 BE 43        5054 	.byte #0x17, #0xb7, #0xbe, #0x43	; 397917763
   D4D0 60 B0 8E D5        5055 	.byte #0x60, #0xb0, #0x8e, #0xd5	; 1622183637
   D4D4 D6 D6 A3 E8        5056 	.byte #0xd6, #0xd6, #0xa3, #0xe8	; 3604390888
   D4D8 A1 D1 93 7E        5057 	.byte #0xa1, #0xd1, #0x93, #0x7e	; 2714866558
   D4DC 38 D8 C2 C4        5058 	.byte #0x38, #0xd8, #0xc2, #0xc4	; 953729732
   D4E0 4F DF F2 52        5059 	.byte #0x4f, #0xdf, #0xf2, #0x52	; 1340076626
   D4E4 D1 BB 67 F1        5060 	.byte #0xd1, #0xbb, #0x67, #0xf1	; 3518719985
   D4E8 A6 BC 57 67        5061 	.byte #0xa6, #0xbc, #0x57, #0x67	; 2797360999
   D4EC 3F B5 06 DD        5062 	.byte #0x3f, #0xb5, #0x06, #0xdd	; 1068828381
   D4F0 48 B2 36 4B        5063 	.byte #0x48, #0xb2, #0x36, #0x4b	; 1219638859
   D4F4 D8 0D 2B DA        5064 	.byte #0xd8, #0x0d, #0x2b, #0xda	; 3624741850
   D4F8 AF 0A 1B 4C        5065 	.byte #0xaf, #0x0a, #0x1b, #0x4c	; 2936675148
   D4FC 36 03 4A F6        5066 	.byte #0x36, #0x03, #0x4a, #0xf6	; 906185462
   D500 41 04 7A 60        5067 	.byte #0x41, #0x04, #0x7a, #0x60	; 1090812512
   D504 DF 60 EF C3        5068 	.byte #0xdf, #0x60, #0xef, #0xc3	; 3747672003
   D508 A8 67 DF 55        5069 	.byte #0xa8, #0x67, #0xdf, #0x55	; 2825379669
   D50C 31 6E 8E EF        5070 	.byte #0x31, #0x6e, #0x8e, #0xef	; 829329135
   D510 46 69 BE 79        5071 	.byte #0x46, #0x69, #0xbe, #0x79	; 1181335161
   D514 CB 61 B3 8C        5072 	.byte #0xcb, #0x61, #0xb3, #0x8c	; 3412177804
   D518 BC 66 83 1A        5073 	.byte #0xbc, #0x66, #0x83, #0x1a	; 3160834842
   D51C 25 6F D2 A0        5074 	.byte #0x25, #0x6f, #0xd2, #0xa0	; 628085408
   D520 52 68 E2 36        5075 	.byte #0x52, #0x68, #0xe2, #0x36	; 1382605366
   D524 CC 0C 77 95        5076 	.byte #0xcc, #0x0c, #0x77, #0x95	; 3423369109
   D528 BB 0B 47 03        5077 	.byte #0xbb, #0x0b, #0x47, #0x03	; 3138078467
   D52C 22 02 16 B9        5078 	.byte #0x22, #0x02, #0x16, #0xb9	; 570562233
   D530 55 05 26 2F        5079 	.byte #0x55, #0x05, #0x26, #0x2f	; 1426400815
   D534 C5 BA 3B BE        5080 	.byte #0xc5, #0xba, #0x3b, #0xbe	; 3317316542
   D538 B2 BD 0B 28        5081 	.byte #0xb2, #0xbd, #0x0b, #0x28	; 2998733608
   D53C 2B B4 5A 92        5082 	.byte #0x2b, #0xb4, #0x5a, #0x92	; 733239954
   D540 5C B3 6A 04        5083 	.byte #0x5c, #0xb3, #0x6a, #0x04	; 1555261956
   D544 C2 D7 FF A7        5084 	.byte #0xc2, #0xd7, #0xff, #0xa7	; 3268935591
   D548 B5 D0 CF 31        5085 	.byte #0xb5, #0xd0, #0xcf, #0x31	; 3050360625
   D54C 2C D9 9E 8B        5086 	.byte #0x2c, #0xd9, #0x9e, #0x8b	; 752459403
   D550 5B DE AE 1D        5087 	.byte #0x5b, #0xde, #0xae, #0x1d	; 1541320221
   D554 9B 64 C2 B0        5088 	.byte #0x9b, #0x64, #0xc2, #0xb0	; 2607071920
   D558 EC 63 F2 26        5089 	.byte #0xec, #0x63, #0xf2, #0x26	; 3965973030
   D55C 75 6A A3 9C        5090 	.byte #0x75, #0x6a, #0xa3, #0x9c	; 1969922972
   D560 02 6D 93 0A        5091 	.byte #0x02, #0x6d, #0x93, #0x0a	; 40735498
   D564 9C 09 06 A9        5092 	.byte #0x9c, #0x09, #0x06, #0xa9	; 2617837225
   D568 EB 0E 36 3F        5093 	.byte #0xeb, #0x0e, #0x36, #0x3f	; 3943577151
   D56C 72 07 67 85        5094 	.byte #0x72, #0x07, #0x67, #0x85	; 1913087877
   D570 05 00 57 13        5095 	.byte #0x05, #0x00, #0x57, #0x13	; 83908371
   D574 95 BF 4A 82        5096 	.byte #0x95, #0xbf, #0x4a, #0x82	; 2512341634
   D578 E2 B8 7A 14        5097 	.byte #0xe2, #0xb8, #0x7a, #0x14	; 3803740692
   D57C 7B B1 2B AE        5098 	.byte #0x7b, #0xb1, #0x2b, #0xae	; 2075208622
   D580 0C B6 1B 38        5099 	.byte #0x0c, #0xb6, #0x1b, #0x38	; 213261112
   D584 92 D2 8E 9B        5100 	.byte #0x92, #0xd2, #0x8e, #0x9b	; 2463272603
   D588 E5 D5 BE 0D        5101 	.byte #0xe5, #0xd5, #0xbe, #0x0d	; 3855990285
   D58C 7C DC EF B7        5102 	.byte #0x7c, #0xdc, #0xef, #0xb7	; 2094854071
   D590 0B DB DF 21        5103 	.byte #0x0b, #0xdb, #0xdf, #0x21	; 198958881
   D594 86 D3 D2 D4        5104 	.byte #0x86, #0xd3, #0xd2, #0xd4	; 2262029012
   D598 F1 D4 E2 42        5105 	.byte #0xf1, #0xd4, #0xe2, #0x42	; 4057260610
   D59C 68 DD B3 F8        5106 	.byte #0x68, #0xdd, #0xb3, #0xf8	; 1759359992
   D5A0 1F DA 83 6E        5107 	.byte #0x1f, #0xda, #0x83, #0x6e	; 534414190
   D5A4 81 BE 16 CD        5108 	.byte #0x81, #0xbe, #0x16, #0xcd	; 2176718541
   D5A8 F6 B9 26 5B        5109 	.byte #0xf6, #0xb9, #0x26, #0x5b	; 4139329115
   D5AC 6F B0 77 E1        5110 	.byte #0x6f, #0xb0, #0x77, #0xe1	; 1873836001
   D5B0 18 B7 47 77        5111 	.byte #0x18, #0xb7, #0x47, #0x77	; 414664567
   D5B4 88 08 5A E6        5112 	.byte #0x88, #0x08, #0x5a, #0xe6	; 2282248934
   D5B8 FF 0F 6A 70        5113 	.byte #0xff, #0x0f, #0x6a, #0x70	; 4279200368
   D5BC 66 06 3B CA        5114 	.byte #0x66, #0x06, #0x3b, #0xca	; 1711684554
   D5C0 11 01 0B 5C        5115 	.byte #0x11, #0x01, #0x0b, #0x5c	; 285281116
   D5C4 8F 65 9E FF        5116 	.byte #0x8f, #0x65, #0x9e, #0xff	; 2405801727
   D5C8 F8 62 AE 69        5117 	.byte #0xf8, #0x62, #0xae, #0x69	; 4167216745
   D5CC 61 6B FF D3        5118 	.byte #0x61, #0x6b, #0xff, #0xd3	; 1634467795
   D5D0 16 6C CF 45        5119 	.byte #0x16, #0x6c, #0xcf, #0x45	; 376229701
   D5D4 A0 0A E2 78        5120 	.byte #0xa0, #0x0a, #0xe2, #0x78	; 2685067896
   D5D8 D7 0D D2 EE        5121 	.byte #0xd7, #0x0d, #0xd2, #0xee	; 3608007406
   D5DC 4E 04 83 54        5122 	.byte #0x4e, #0x04, #0x83, #0x54	; 1308918612
   D5E0 39 03 B3 C2        5123 	.byte #0x39, #0x03, #0xb3, #0xc2	; 956543938
   D5E4 A7 67 26 61        5124 	.byte #0xa7, #0x67, #0x26, #0x61	; 2808555105
   D5E8 D0 60 16 F7        5125 	.byte #0xd0, #0x60, #0x16, #0xf7	; 3495958263
   D5EC 49 69 47 4D        5126 	.byte #0x49, #0x69, #0x47, #0x4d	; 1231636301
   D5F0 3E 6E 77 DB        5127 	.byte #0x3e, #0x6e, #0x77, #0xdb	; 1047427035
   D5F4 AE D1 6A 4A        5128 	.byte #0xae, #0xd1, #0x6a, #0x4a	; 2932959818
   D5F8 D9 D6 5A DC        5129 	.byte #0xd9, #0xd6, #0x5a, #0xdc	; 3654703836
   D5FC 40 DF 0B 66        5130 	.byte #0x40, #0xdf, #0x0b, #0x66	; 1088359270
   D600 37 D8 3B F0        5131 	.byte #0x37, #0xd8, #0x3b, #0xf0	; 936918000
   D604 A9 BC AE 53        5132 	.byte #0xa9, #0xbc, #0xae, #0x53	; 2847714899
   D608 DE BB 9E C5        5133 	.byte #0xde, #0xbb, #0x9e, #0xc5	; 3736837829
   D60C 47 B2 CF 7F        5134 	.byte #0x47, #0xb2, #0xcf, #0x7f	; 1202900863
   D610 30 B5 FF E9        5135 	.byte #0x30, #0xb5, #0xff, #0xe9	; 817233897
   D614 BD BD F2 1C        5136 	.byte #0xbd, #0xbd, #0xf2, #0x1c	; 3183342108
   D618 CA BA C2 8A        5137 	.byte #0xca, #0xba, #0xc2, #0x8a	; 3401237130
   D61C 53 B3 93 30        5138 	.byte #0x53, #0xb3, #0x93, #0x30	; 1404277552
   D620 24 B4 A3 A6        5139 	.byte #0x24, #0xb4, #0xa3, #0xa6	; 615818150
   D624 BA D0 36 05        5140 	.byte #0xba, #0xd0, #0x36, #0x05	; 3134207493
   D628 CD D7 06 93        5141 	.byte #0xcd, #0xd7, #0x06, #0x93	; 3453421203
   D62C 54 DE 57 29        5142 	.byte #0x54, #0xde, #0x57, #0x29	; 1423857449
   D630 23 D9 67 BF        5143 	.byte #0x23, #0xd9, #0x67, #0xbf	; 601450431
   D634 B3 66 7A 2E        5144 	.byte #0xb3, #0x66, #0x7a, #0x2e	; 3009837614
   D638 C4 61 4A B8        5145 	.byte #0xc4, #0x61, #0x4a, #0xb8	; 3294710456
   D63C 5D 68 1B 02        5146 	.byte #0x5d, #0x68, #0x1b, #0x02	; 1567103746
   D640 2A 6F 2B 94        5147 	.byte #0x2a, #0x6f, #0x2b, #0x94	; 711928724
   D644 B4 0B BE 37        5148 	.byte #0xb4, #0x0b, #0xbe, #0x37	; 3020668471
   D648 C3 0C 8E A1        5149 	.byte #0xc3, #0x0c, #0x8e, #0xa1	; 3272380065
   D64C 5A 05 DF 1B        5150 	.byte #0x5a, #0x05, #0xdf, #0x1b	; 1510334235
   D650 2D 02 EF 8D        5151 	.byte #0x2d, #0x02, #0xef, #0x8d	; 755167117
   D654                    5152 _pageSize:
   D654 00 00              5153 	.dw #0x0000
   D656 00 1E              5154 	.dw #0x001e
   D658 00 A8              5155 	.dw #0x00a8
   D65A 00 A8              5156 	.dw #0x00a8
   D65C 00 20              5157 	.dw #0x0020
   D65E 01 20              5158 	.dw #0x0120
   D660 00 80              5159 	.dw #0x0080
   D662 00 F0              5160 	.dw #0x00f0
   D664 01 80              5161 	.dw #0x0180
   D666 00 C0              5162 	.dw #0x00c0
   D668 00 C0              5163 	.dw #0x00c0
   D66A 01 20              5164 	.dw #0x0120
   D66C 00 C0              5165 	.dw #0x00c0
   D66E 00 80              5166 	.dw #0x0080
   D670 01 20              5167 	.dw #0x0120
   D672 01 00              5168 	.dw #0x0100
                           5169 	.area CONST   (CODE)
   D674                    5170 ___str_0:
   D674 73 70 65 65 64 75  5171 	.ascii "speeduino 202402"
        69 6E 6F 20 32 30
        32 34 30 32
   D684 00                 5172 	.db 0x00
                           5173 	.area CSEG    (CODE)
                           5174 	.area CONST   (CODE)
   D685                    5175 ___str_1:
   D685 0D                 5176 	.db 0x0d
   D686 0A                 5177 	.db 0x0a
   D687 00                 5178 	.db 0x00
                           5179 	.area CSEG    (CODE)
                           5180 	.area CONST   (CODE)
   D688                    5181 ___str_2:
   D688 53 70 65 65 64 75  5182 	.ascii "Speeduino 202402"
        69 6E 6F 20 32 30
        32 34 30 32
   D698 00                 5183 	.db 0x00
                           5184 	.area CSEG    (CODE)
                           5185 	.area CONST   (CODE)
   D699                    5186 ___str_3:
   D699 30 30 32           5187 	.ascii "002"
   D69C 00                 5188 	.db 0x00
                           5189 	.area CSEG    (CODE)
                           5190 	.area CONST   (CODE)
   D69D                    5191 ___str_4:
   D69D 73 70 65 65 64 75  5192 	.ascii "speeduino 202207"
        69 6E 6F 20 32 30
        32 32 30 37
   D6AD 00                 5193 	.db 0x00
                           5194 	.area CSEG    (CODE)
                           5195 	.area CONST   (CODE)
   D6AE                    5196 ___str_5:
   D6AE 53 70 65 65 64 75  5197 	.ascii "Speeduino 2024.02.4"
        69 6E 6F 20 32 30
        32 34 2E 30 32 2E
        34
   D6C1 00                 5198 	.db 0x00
                           5199 	.area CSEG    (CODE)
                           5200 	.area XINIT   (CODE)
   D24F                    5201 __xinit__serialBytesReceived:
   D24F 00                 5202 	.db #0x00	; 0
   D250                    5203 __xinit__modernProtocol:
   D250 00                 5204 	.db #0x00	;  0
   D251                    5205 __xinit__expectedLength:
   D251 00                 5206 	.db #0x00	; 0
                           5207 	.area CABS    (ABS,CODE)
