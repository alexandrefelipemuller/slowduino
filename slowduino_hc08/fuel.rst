                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 4.2.0 #13081 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module fuel
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
                             22 	.globl _getTableValue
                             23 	.globl _calculateInjection
                             24 	.globl _getVE
                             25 	.globl _calculateCorrections
                             26 	.globl _correctionWUE
                             27 	.globl _correctionASE
                             28 	.globl _startASE
                             29 	.globl _decrementASE
                             30 	.globl _correctionAE
                             31 	.globl _correctionCLT
                             32 	.globl _correctionBattery
                             33 	.globl _updateEngineStatus
                             34 ;--------------------------------------------------------
                             35 ; ram data
                             36 ;--------------------------------------------------------
                             37 	.area DSEG    (PAG)
                             38 ;--------------------------------------------------------
                             39 ; overlayable items in ram
                             40 ;--------------------------------------------------------
                             41 ;--------------------------------------------------------
                             42 ; absolute ram data
                             43 ;--------------------------------------------------------
                             44 	.area IABS    (ABS)
                             45 	.area IABS    (ABS)
                             46 ;--------------------------------------------------------
                             47 ; absolute external ram data
                             48 ;--------------------------------------------------------
                             49 	.area XABS    (ABS)
                             50 ;--------------------------------------------------------
                             51 ; external initialized ram data
                             52 ;--------------------------------------------------------
                             53 	.area XISEG
   01D5                      54 _aseCounter:
   01D5                      55 	.ds 1
   01D6                      56 _aseValue:
   01D6                      57 	.ds 1
                             58 ;--------------------------------------------------------
                             59 ; extended address mode data
                             60 ;--------------------------------------------------------
                             61 	.area XSEG
   0175                      62 _updateEngineStatus_firstRun_65536_62:
   0175                      63 	.ds 1
                             64 ;--------------------------------------------------------
                             65 ; global & static initialisations
                             66 ;--------------------------------------------------------
                             67 	.area HOME    (CODE)
                             68 	.area GSINIT  (CODE)
                             69 	.area GSFINAL (CODE)
                             70 	.area GSINIT  (CODE)
                             71 ;------------------------------------------------------------
                             72 ;Allocation info for local variables in function 'updateEngineStatus'
                             73 ;------------------------------------------------------------
                             74 ;sloc0                     Allocated to stack - sp +1
                             75 ;firstRun                  Allocated with name '_updateEngineStatus_firstRun_65536_62'
                             76 ;------------------------------------------------------------
                             77 ;fuel.c:176: static bool firstRun = true;
   801E A6 01         [ 2]   78 	lda	#0x01
   8020 C7 01 75      [ 4]   79 	sta	_updateEngineStatus_firstRun_65536_62
                             80 ;--------------------------------------------------------
                             81 ; Home
                             82 ;--------------------------------------------------------
                             83 	.area HOME    (CODE)
                             84 	.area HOME    (CODE)
                             85 ;--------------------------------------------------------
                             86 ; code
                             87 ;--------------------------------------------------------
                             88 	.area CSEG    (CODE)
                             89 ;------------------------------------------------------------
                             90 ;Allocation info for local variables in function 'noInterrupts'
                             91 ;------------------------------------------------------------
                             92 ;globals.h:100: static inline void noInterrupts(void) { __asm sei __endasm; }
                             93 ;	-----------------------------------------
                             94 ;	 function noInterrupts
                             95 ;	-----------------------------------------
                             96 ;	Register assignment is optimal.
                             97 ;	Stack space usage: 0 bytes.
   A5BE                      98 _noInterrupts:
   A5BE 9B            [ 2]   99 	 sei	
   A5BF 81            [ 4]  100 	rts
                            101 ;------------------------------------------------------------
                            102 ;Allocation info for local variables in function 'interrupts'
                            103 ;------------------------------------------------------------
                            104 ;globals.h:101: static inline void interrupts(void)   { __asm cli __endasm; }
                            105 ;	-----------------------------------------
                            106 ;	 function interrupts
                            107 ;	-----------------------------------------
                            108 ;	Register assignment is optimal.
                            109 ;	Stack space usage: 0 bytes.
   A5C0                     110 _interrupts:
   A5C0 9A            [ 2]  111 	 cli	
   A5C1 81            [ 4]  112 	rts
                            113 ;------------------------------------------------------------
                            114 ;Allocation info for local variables in function 'interpolate'
                            115 ;------------------------------------------------------------
                            116 ;x1                        Allocated to stack - sp +11
                            117 ;x2                        Allocated to stack - sp +13
                            118 ;y1                        Allocated to stack - sp +15
                            119 ;y2                        Allocated to stack - sp +17
                            120 ;x                         Allocated to registers a x 
                            121 ;sloc0                     Allocated to stack - sp +1
                            122 ;sloc1                     Allocated to stack - sp +5
                            123 ;------------------------------------------------------------
                            124 ;tables.h:33: static inline int16_t interpolate(int16_t x, int16_t x1, int16_t x2, int16_t y1, int16_t y2) {
                            125 ;	-----------------------------------------
                            126 ;	 function interpolate
                            127 ;	-----------------------------------------
                            128 ;	Register assignment might be sub-optimal.
                            129 ;	Stack space usage: 8 bytes.
   A5C2                     130 _interpolate:
   A5C2 A7 F8         [ 2]  131 	ais	#-8
                            132 ;tables.h:34: if (x2 == x1) return y1;
   A5C4 87            [ 2]  133 	psha
   A5C5 9E E6 0F      [ 4]  134 	lda	15,s
   A5C8 9E E1 0D      [ 4]  135 	cmp	13,s
   A5CB 86            [ 2]  136 	pula
   A5CC 26 0A         [ 3]  137 	bne	00110$
   A5CE 87            [ 2]  138 	psha
   A5CF 9E E6 0E      [ 4]  139 	lda	14,s
   A5D2 9E E1 0C      [ 4]  140 	cmp	12,s
   A5D5 86            [ 2]  141 	pula
   A5D6 27 02         [ 3]  142 	beq	00111$
   A5D8                     143 00110$:
   A5D8 20 09         [ 3]  144 	bra	00102$
   A5DA                     145 00111$:
   A5DA 95            [ 2]  146 	tsx
   A5DB EE 0E         [ 3]  147 	ldx	14,x
   A5DD 9E E6 10      [ 4]  148 	lda	16,s
   A5E0 CC A6 A8      [ 3]  149 	jmp	00103$
   A5E3                     150 00102$:
                            151 ;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
   A5E3 9E E0 0C      [ 4]  152 	sub	12,s
   A5E6 87            [ 2]  153 	psha
   A5E7 9F            [ 1]  154 	txa
   A5E8 9E E2 0C      [ 4]  155 	sbc	12,s
   A5EB 97            [ 1]  156 	tax
   A5EC 86            [ 2]  157 	pula
   A5ED 9E E7 04      [ 4]  158 	sta	4,s
   A5F0 9F            [ 1]  159 	txa
   A5F1 9E E7 03      [ 4]  160 	sta	3,s
   A5F4 49            [ 1]  161 	rola	
   A5F5 4F            [ 1]  162 	clra	
   A5F6 A2 00         [ 2]  163 	sbc	#0x00
   A5F8 9E E7 02      [ 4]  164 	sta	2,s
   A5FB 9E E7 01      [ 4]  165 	sta	1,s
   A5FE 9E E6 12      [ 4]  166 	lda	18,s
   A601 9E E0 10      [ 4]  167 	sub	16,s
   A604 87            [ 2]  168 	psha
   A605 9E E6 12      [ 4]  169 	lda	18,s
   A608 9E E2 10      [ 4]  170 	sbc	16,s
   A60B 97            [ 1]  171 	tax
   A60C 86            [ 2]  172 	pula
   A60D 9E E7 08      [ 4]  173 	sta	8,s
   A610 9F            [ 1]  174 	txa
   A611 9E E7 07      [ 4]  175 	sta	7,s
   A614 49            [ 1]  176 	rola	
   A615 4F            [ 1]  177 	clra	
   A616 A2 00         [ 2]  178 	sbc	#0x00
   A618 9E E7 06      [ 4]  179 	sta	6,s
   A61B 9E E7 05      [ 4]  180 	sta	5,s
   A61E 95            [ 2]  181 	tsx
   A61F E6 07         [ 3]  182 	lda	7,x
   A621 87            [ 2]  183 	psha
   A622 E6 06         [ 3]  184 	lda	6,x
   A624 87            [ 2]  185 	psha
   A625 E6 05         [ 3]  186 	lda	5,x
   A627 87            [ 2]  187 	psha
   A628 E6 04         [ 3]  188 	lda	4,x
   A62A 87            [ 2]  189 	psha
   A62B E6 03         [ 3]  190 	lda	3,x
   A62D 87            [ 2]  191 	psha
   A62E E6 02         [ 3]  192 	lda	2,x
   A630 87            [ 2]  193 	psha
   A631 E6 01         [ 3]  194 	lda	1,x
   A633 87            [ 2]  195 	psha
   A634 F6            [ 2]  196 	lda	,x
   A635 87            [ 2]  197 	psha
   A636 CD D0 87      [ 5]  198 	jsr	__mullong
   A639 9E E7 10      [ 4]  199 	sta	16,s
   A63C 9E EF 0F      [ 4]  200 	stx	15,s
   A63F B6 4A         [ 3]  201 	lda	*___SDCC_hc08_ret2
   A641 9E E7 0E      [ 4]  202 	sta	14,s
   A644 B6 4B         [ 3]  203 	lda	*___SDCC_hc08_ret3
   A646 9E E7 0D      [ 4]  204 	sta	13,s
   A649 A7 08         [ 2]  205 	ais	#8
   A64B 9E E6 0E      [ 4]  206 	lda	14,s
   A64E 9E E0 0C      [ 4]  207 	sub	12,s
   A651 87            [ 2]  208 	psha
   A652 9E E6 0E      [ 4]  209 	lda	14,s
   A655 9E E2 0C      [ 4]  210 	sbc	12,s
   A658 97            [ 1]  211 	tax
   A659 86            [ 2]  212 	pula
   A65A 9E E7 04      [ 4]  213 	sta	4,s
   A65D 9F            [ 1]  214 	txa
   A65E 9E E7 03      [ 4]  215 	sta	3,s
   A661 49            [ 1]  216 	rola	
   A662 4F            [ 1]  217 	clra	
   A663 A2 00         [ 2]  218 	sbc	#0x00
   A665 9E E7 02      [ 4]  219 	sta	2,s
   A668 9E E7 01      [ 4]  220 	sta	1,s
   A66B 95            [ 2]  221 	tsx
   A66C E6 03         [ 3]  222 	lda	3,x
   A66E 87            [ 2]  223 	psha
   A66F E6 02         [ 3]  224 	lda	2,x
   A671 87            [ 2]  225 	psha
   A672 E6 01         [ 3]  226 	lda	1,x
   A674 87            [ 2]  227 	psha
   A675 F6            [ 2]  228 	lda	,x
   A676 87            [ 2]  229 	psha
   A677 E6 07         [ 3]  230 	lda	7,x
   A679 87            [ 2]  231 	psha
   A67A E6 06         [ 3]  232 	lda	6,x
   A67C 87            [ 2]  233 	psha
   A67D E6 05         [ 3]  234 	lda	5,x
   A67F 87            [ 2]  235 	psha
   A680 E6 04         [ 3]  236 	lda	4,x
   A682 87            [ 2]  237 	psha
   A683 CD CE 92      [ 5]  238 	jsr	__divslong
   A686 9E E7 10      [ 4]  239 	sta	16,s
   A689 9E EF 0F      [ 4]  240 	stx	15,s
   A68C B6 4A         [ 3]  241 	lda	*___SDCC_hc08_ret2
   A68E 9E E7 0E      [ 4]  242 	sta	14,s
   A691 B6 4B         [ 3]  243 	lda	*___SDCC_hc08_ret3
   A693 9E E7 0D      [ 4]  244 	sta	13,s
   A696 A7 08         [ 2]  245 	ais	#8
   A698 9E E6 08      [ 4]  246 	lda	8,s
   A69B 9E EE 07      [ 4]  247 	ldx	7,s
   A69E 9E EB 10      [ 4]  248 	add	16,s
   A6A1 87            [ 2]  249 	psha
   A6A2 9F            [ 1]  250 	txa
   A6A3 9E E9 10      [ 4]  251 	adc	16,s
   A6A6 97            [ 1]  252 	tax
   A6A7 86            [ 2]  253 	pula
   A6A8                     254 00103$:
                            255 ;tables.h:36: }
   A6A8 A7 08         [ 2]  256 	ais	#8
   A6AA 81            [ 4]  257 	rts
                            258 ;------------------------------------------------------------
                            259 ;Allocation info for local variables in function 'calculateInjection'
                            260 ;------------------------------------------------------------
                            261 ;ve                        Allocated to registers h 
                            262 ;corrections               Allocated to stack - sp +13
                            263 ;pw                        Allocated to stack - sp +1
                            264 ;sloc0                     Allocated to stack - sp +5
                            265 ;sloc1                     Allocated to stack - sp +9
                            266 ;------------------------------------------------------------
                            267 ;fuel.c:14: uint16_t calculateInjection(void) {
                            268 ;	-----------------------------------------
                            269 ;	 function calculateInjection
                            270 ;	-----------------------------------------
                            271 ;	Register assignment is optimal.
                            272 ;	Stack space usage: 14 bytes.
   A6AB                     273 _calculateInjection:
   A6AB A7 F2         [ 2]  274 	ais	#-14
                            275 ;fuel.c:15: uint8_t ve = getVE();
   A6AD CD A8 A8      [ 5]  276 	jsr	_getVE
   A6B0 87            [ 2]  277 	psha
   A6B1 8A            [ 2]  278 	pulh
                            279 ;fuel.c:19: currentStatus.VE = ve;
   A6B2 8B            [ 2]  280 	pshh
   A6B3 86            [ 2]  281 	pula
   A6B4 C7 00 81      [ 4]  282 	sta	(_currentStatus + 0x0022)
                            283 ;fuel.c:21: corrections = calculateCorrections();
   A6B7 8B            [ 2]  284 	pshh
   A6B8 CD A8 EB      [ 5]  285 	jsr	_calculateCorrections
   A6BB 9E E7 0F      [ 4]  286 	sta	15,s
   A6BE 9E EF 0E      [ 4]  287 	stx	14,s
   A6C1 8A            [ 2]  288 	pulh
                            289 ;fuel.c:22: currentStatus.corrections = corrections;
   A6C2 9E E6 0D      [ 4]  290 	lda	13,s
   A6C5 C7 00 82      [ 4]  291 	sta	(_currentStatus + 0x0023)
   A6C8 9E E6 0E      [ 4]  292 	lda	14,s
   A6CB C7 00 83      [ 4]  293 	sta	((_currentStatus + 0x0023) + 1)
                            294 ;fuel.c:24: pw = (uint32_t)configPage1.reqFuel;
   A6CE CE 00 9D      [ 4]  295 	ldx	(_configPage1 + 0x0001)
   A6D1 C6 00 9E      [ 4]  296 	lda	((_configPage1 + 0x0001) + 1)
   A6D4 9E E7 08      [ 4]  297 	sta	8,s
   A6D7 9E EF 07      [ 4]  298 	stx	7,s
   A6DA 87            [ 2]  299 	psha
   A6DB 4F            [ 1]  300 	clra
   A6DC 9E E7 07      [ 4]  301 	sta	7,s
   A6DF 4F            [ 1]  302 	clra
   A6E0 9E E7 06      [ 4]  303 	sta	6,s
   A6E3 86            [ 2]  304 	pula
                            305 ;fuel.c:25: pw = (pw * ve) / 100;
   A6E4 8B            [ 2]  306 	pshh
   A6E5 86            [ 2]  307 	pula
   A6E6 9E E7 0C      [ 4]  308 	sta	12,s
   A6E9 4F            [ 1]  309 	clra
   A6EA 9E E7 0B      [ 4]  310 	sta	11,s
   A6ED 9E E7 0A      [ 4]  311 	sta	10,s
   A6F0 9E E7 09      [ 4]  312 	sta	9,s
   A6F3 95            [ 2]  313 	tsx
   A6F4 E6 0B         [ 3]  314 	lda	11,x
   A6F6 87            [ 2]  315 	psha
   A6F7 E6 0A         [ 3]  316 	lda	10,x
   A6F9 87            [ 2]  317 	psha
   A6FA E6 09         [ 3]  318 	lda	9,x
   A6FC 87            [ 2]  319 	psha
   A6FD E6 08         [ 3]  320 	lda	8,x
   A6FF 87            [ 2]  321 	psha
   A700 E6 07         [ 3]  322 	lda	7,x
   A702 87            [ 2]  323 	psha
   A703 E6 06         [ 3]  324 	lda	6,x
   A705 87            [ 2]  325 	psha
   A706 E6 05         [ 3]  326 	lda	5,x
   A708 87            [ 2]  327 	psha
   A709 E6 04         [ 3]  328 	lda	4,x
   A70B 87            [ 2]  329 	psha
   A70C CD D0 87      [ 5]  330 	jsr	__mullong
   A70F 9E E7 14      [ 4]  331 	sta	20,s
   A712 9E EF 13      [ 4]  332 	stx	19,s
   A715 B6 4A         [ 3]  333 	lda	*___SDCC_hc08_ret2
   A717 9E E7 12      [ 4]  334 	sta	18,s
   A71A B6 4B         [ 3]  335 	lda	*___SDCC_hc08_ret3
   A71C 9E E7 11      [ 4]  336 	sta	17,s
   A71F A7 08         [ 2]  337 	ais	#8
   A721 A6 64         [ 2]  338 	lda	#0x64
   A723 87            [ 2]  339 	psha
   A724 4F            [ 1]  340 	clra
   A725 87            [ 2]  341 	psha
   A726 87            [ 2]  342 	psha
   A727 87            [ 2]  343 	psha
   A728 95            [ 2]  344 	tsx
   A729 E6 0F         [ 3]  345 	lda	15,x
   A72B 87            [ 2]  346 	psha
   A72C E6 0E         [ 3]  347 	lda	14,x
   A72E 87            [ 2]  348 	psha
   A72F E6 0D         [ 3]  349 	lda	13,x
   A731 87            [ 2]  350 	psha
   A732 E6 0C         [ 3]  351 	lda	12,x
   A734 87            [ 2]  352 	psha
                            353 ;fuel.c:26: pw = (pw * currentStatus.MAP) / 100;
   A735 CD CF 5C      [ 5]  354 	jsr	__divulong
   A738 9E E7 14      [ 4]  355 	sta	20,s
   A73B 9E EF 13      [ 4]  356 	stx	19,s
   A73E B6 4A         [ 3]  357 	lda	*___SDCC_hc08_ret2
   A740 9E E7 12      [ 4]  358 	sta	18,s
   A743 B6 4B         [ 3]  359 	lda	*___SDCC_hc08_ret3
   A745 9E E7 11      [ 4]  360 	sta	17,s
   A748 A7 08         [ 2]  361 	ais	#8
   A74A C6 00 72      [ 4]  362 	lda	(_currentStatus + 0x0013)
   A74D 95            [ 2]  363 	tsx
   A74E E7 07         [ 3]  364 	sta	7,x
   A750 5F            [ 1]  365 	clrx
   A751 9E EF 07      [ 4]  366 	stx	7,s
   A754 9E EF 06      [ 4]  367 	stx	6,s
   A757 9E EF 05      [ 4]  368 	stx	5,s
   A75A 95            [ 2]  369 	tsx
   A75B E6 07         [ 3]  370 	lda	7,x
   A75D 87            [ 2]  371 	psha
   A75E E6 06         [ 3]  372 	lda	6,x
   A760 87            [ 2]  373 	psha
   A761 E6 05         [ 3]  374 	lda	5,x
   A763 87            [ 2]  375 	psha
   A764 E6 04         [ 3]  376 	lda	4,x
   A766 87            [ 2]  377 	psha
   A767 E6 0B         [ 3]  378 	lda	11,x
   A769 87            [ 2]  379 	psha
   A76A E6 0A         [ 3]  380 	lda	10,x
   A76C 87            [ 2]  381 	psha
   A76D E6 09         [ 3]  382 	lda	9,x
   A76F 87            [ 2]  383 	psha
   A770 E6 08         [ 3]  384 	lda	8,x
   A772 87            [ 2]  385 	psha
   A773 CD D0 87      [ 5]  386 	jsr	__mullong
   A776 9E E7 14      [ 4]  387 	sta	20,s
   A779 9E EF 13      [ 4]  388 	stx	19,s
   A77C B6 4A         [ 3]  389 	lda	*___SDCC_hc08_ret2
   A77E 9E E7 12      [ 4]  390 	sta	18,s
   A781 B6 4B         [ 3]  391 	lda	*___SDCC_hc08_ret3
   A783 9E E7 11      [ 4]  392 	sta	17,s
   A786 A7 08         [ 2]  393 	ais	#8
   A788 A6 64         [ 2]  394 	lda	#0x64
   A78A 87            [ 2]  395 	psha
   A78B 4F            [ 1]  396 	clra
   A78C 87            [ 2]  397 	psha
   A78D 87            [ 2]  398 	psha
   A78E 87            [ 2]  399 	psha
   A78F 95            [ 2]  400 	tsx
   A790 E6 0F         [ 3]  401 	lda	15,x
   A792 87            [ 2]  402 	psha
   A793 E6 0E         [ 3]  403 	lda	14,x
   A795 87            [ 2]  404 	psha
   A796 E6 0D         [ 3]  405 	lda	13,x
   A798 87            [ 2]  406 	psha
   A799 E6 0C         [ 3]  407 	lda	12,x
   A79B 87            [ 2]  408 	psha
                            409 ;fuel.c:27: pw = (pw * corrections) / 100;
   A79C CD CF 5C      [ 5]  410 	jsr	__divulong
   A79F 9E E7 14      [ 4]  411 	sta	20,s
   A7A2 9E EF 13      [ 4]  412 	stx	19,s
   A7A5 B6 4A         [ 3]  413 	lda	*___SDCC_hc08_ret2
   A7A7 9E E7 12      [ 4]  414 	sta	18,s
   A7AA B6 4B         [ 3]  415 	lda	*___SDCC_hc08_ret3
   A7AC 9E E7 11      [ 4]  416 	sta	17,s
   A7AF A7 08         [ 2]  417 	ais	#8
   A7B1 95            [ 2]  418 	tsx
   A7B2 E6 0D         [ 3]  419 	lda	13,x
   A7B4 E7 07         [ 3]  420 	sta	7,x
   A7B6 E6 0C         [ 3]  421 	lda	12,x
   A7B8 E7 06         [ 3]  422 	sta	6,x
   A7BA 4F            [ 1]  423 	clra
   A7BB E7 05         [ 3]  424 	sta	5,x
   A7BD E7 04         [ 3]  425 	sta	4,x
   A7BF E6 07         [ 3]  426 	lda	7,x
   A7C1 87            [ 2]  427 	psha
   A7C2 E6 06         [ 3]  428 	lda	6,x
   A7C4 87            [ 2]  429 	psha
   A7C5 E6 05         [ 3]  430 	lda	5,x
   A7C7 87            [ 2]  431 	psha
   A7C8 E6 04         [ 3]  432 	lda	4,x
   A7CA 87            [ 2]  433 	psha
   A7CB E6 0B         [ 3]  434 	lda	11,x
   A7CD 87            [ 2]  435 	psha
   A7CE E6 0A         [ 3]  436 	lda	10,x
   A7D0 87            [ 2]  437 	psha
   A7D1 E6 09         [ 3]  438 	lda	9,x
   A7D3 87            [ 2]  439 	psha
   A7D4 E6 08         [ 3]  440 	lda	8,x
   A7D6 87            [ 2]  441 	psha
   A7D7 CD D0 87      [ 5]  442 	jsr	__mullong
   A7DA 9E E7 14      [ 4]  443 	sta	20,s
   A7DD 9E EF 13      [ 4]  444 	stx	19,s
   A7E0 B6 4A         [ 3]  445 	lda	*___SDCC_hc08_ret2
   A7E2 9E E7 12      [ 4]  446 	sta	18,s
   A7E5 B6 4B         [ 3]  447 	lda	*___SDCC_hc08_ret3
   A7E7 9E E7 11      [ 4]  448 	sta	17,s
   A7EA A7 08         [ 2]  449 	ais	#8
   A7EC A6 64         [ 2]  450 	lda	#0x64
   A7EE 87            [ 2]  451 	psha
   A7EF 4F            [ 1]  452 	clra
   A7F0 87            [ 2]  453 	psha
   A7F1 87            [ 2]  454 	psha
   A7F2 87            [ 2]  455 	psha
   A7F3 95            [ 2]  456 	tsx
   A7F4 E6 0F         [ 3]  457 	lda	15,x
   A7F6 87            [ 2]  458 	psha
   A7F7 E6 0E         [ 3]  459 	lda	14,x
   A7F9 87            [ 2]  460 	psha
   A7FA E6 0D         [ 3]  461 	lda	13,x
   A7FC 87            [ 2]  462 	psha
   A7FD E6 0C         [ 3]  463 	lda	12,x
   A7FF 87            [ 2]  464 	psha
                            465 ;fuel.c:29: pw += configPage1.injOpen;
   A800 CD CF 5C      [ 5]  466 	jsr	__divulong
   A803 9E E7 14      [ 4]  467 	sta	20,s
   A806 9E EF 13      [ 4]  468 	stx	19,s
   A809 B6 4A         [ 3]  469 	lda	*___SDCC_hc08_ret2
   A80B 9E E7 12      [ 4]  470 	sta	18,s
   A80E B6 4B         [ 3]  471 	lda	*___SDCC_hc08_ret3
   A810 9E E7 11      [ 4]  472 	sta	17,s
   A813 A7 08         [ 2]  473 	ais	#8
   A815 C6 00 9F      [ 4]  474 	lda	(_configPage1 + 0x0003)
   A818 87            [ 2]  475 	psha
   A819 8A            [ 2]  476 	pulh
   A81A CE 00 A0      [ 4]  477 	ldx	((_configPage1 + 0x0003) + 1)
   A81D 9E EF 08      [ 4]  478 	stx	8,s
   A820 8B            [ 2]  479 	pshh
   A821 86            [ 2]  480 	pula
   A822 9E E7 07      [ 4]  481 	sta	7,s
   A825 4F            [ 1]  482 	clra
   A826 9E E7 06      [ 4]  483 	sta	6,s
   A829 9E E7 05      [ 4]  484 	sta	5,s
   A82C 95            [ 2]  485 	tsx
   A82D E6 0B         [ 3]  486 	lda	11,x
   A82F EB 07         [ 3]  487 	add	7,x
   A831 E7 0B         [ 3]  488 	sta	11,x
   A833 E6 0A         [ 3]  489 	lda	10,x
   A835 E9 06         [ 3]  490 	adc	6,x
   A837 E7 0A         [ 3]  491 	sta	10,x
   A839 E6 09         [ 3]  492 	lda	9,x
   A83B E9 05         [ 3]  493 	adc	5,x
   A83D E7 09         [ 3]  494 	sta	9,x
   A83F E6 08         [ 3]  495 	lda	8,x
   A841 E9 04         [ 3]  496 	adc	4,x
   A843 E7 08         [ 3]  497 	sta	8,x
   A845 E6 08         [ 3]  498 	lda	8,x
   A847 F7            [ 2]  499 	sta	,x
   A848 E6 09         [ 3]  500 	lda	9,x
   A84A E7 01         [ 3]  501 	sta	1,x
   A84C E6 0A         [ 3]  502 	lda	10,x
   A84E E7 02         [ 3]  503 	sta	2,x
   A850 E6 0B         [ 3]  504 	lda	11,x
   A852 E7 03         [ 3]  505 	sta	3,x
                            506 ;fuel.c:31: if (pw < INJ_MIN_PW) pw = INJ_MIN_PW;
   A854 E6 0B         [ 3]  507 	lda	11,x
   A856 A0 F4         [ 2]  508 	sub	#0xf4
   A858 E6 0A         [ 3]  509 	lda	10,x
   A85A A2 01         [ 2]  510 	sbc	#0x01
   A85C E6 09         [ 3]  511 	lda	9,x
   A85E A2 00         [ 2]  512 	sbc	#0x00
   A860 E6 08         [ 3]  513 	lda	8,x
   A862 A2 00         [ 2]  514 	sbc	#0x00
   A864 24 0B         [ 3]  515 	bcc	00102$
   A866 4F            [ 1]  516 	clra
   A867 F7            [ 2]  517 	sta	,x
   A868 E7 01         [ 3]  518 	sta	1,x
   A86A 4C            [ 1]  519 	inca
   A86B E7 02         [ 3]  520 	sta	2,x
   A86D A6 F4         [ 2]  521 	lda	#0xf4
   A86F E7 03         [ 3]  522 	sta	3,x
   A871                     523 00102$:
                            524 ;fuel.c:32: if (pw > INJ_MAX_PW) pw = INJ_MAX_PW;
   A871 95            [ 2]  525 	tsx
   A872 A6 20         [ 2]  526 	lda	#0x20
   A874 E0 03         [ 3]  527 	sub	3,x
   A876 A6 4E         [ 2]  528 	lda	#0x4e
   A878 E2 02         [ 3]  529 	sbc	2,x
   A87A 4F            [ 1]  530 	clra
   A87B E2 01         [ 3]  531 	sbc	1,x
   A87D 4F            [ 1]  532 	clra
   A87E F2            [ 2]  533 	sbc	,x
   A87F 24 0C         [ 3]  534 	bcc	00104$
   A881 4F            [ 1]  535 	clra
   A882 F7            [ 2]  536 	sta	,x
   A883 E7 01         [ 3]  537 	sta	1,x
   A885 A6 4E         [ 2]  538 	lda	#0x4e
   A887 E7 02         [ 3]  539 	sta	2,x
   A889 A6 20         [ 2]  540 	lda	#0x20
   A88B E7 03         [ 3]  541 	sta	3,x
   A88D                     542 00104$:
                            543 ;fuel.c:34: currentStatus.PW1 = (uint16_t)pw;
   A88D 9E E6 04      [ 4]  544 	lda	4,s
   A890 9E EE 03      [ 4]  545 	ldx	3,s
   A893 CF 00 7B      [ 4]  546 	stx	(_currentStatus + 0x001c)
   A896 C7 00 7C      [ 4]  547 	sta	((_currentStatus + 0x001c) + 1)
                            548 ;fuel.c:35: currentStatus.PW2 = (uint16_t)pw;
   A899 CF 00 7D      [ 4]  549 	stx	(_currentStatus + 0x001e)
   A89C C7 00 7E      [ 4]  550 	sta	((_currentStatus + 0x001e) + 1)
                            551 ;fuel.c:36: currentStatus.PW3 = (uint16_t)pw;
   A89F CF 00 7F      [ 4]  552 	stx	(_currentStatus + 0x0020)
   A8A2 C7 00 80      [ 4]  553 	sta	((_currentStatus + 0x0020) + 1)
                            554 ;fuel.c:38: return (uint16_t)pw;
                            555 ;fuel.c:39: }
   A8A5 A7 0E         [ 2]  556 	ais	#14
   A8A7 81            [ 4]  557 	rts
                            558 ;------------------------------------------------------------
                            559 ;Allocation info for local variables in function 'getVE'
                            560 ;------------------------------------------------------------
                            561 ;ve                        Allocated to registers a x 
                            562 ;sloc0                     Allocated to stack - sp +1
                            563 ;------------------------------------------------------------
                            564 ;fuel.c:41: uint8_t getVE(void) {
                            565 ;	-----------------------------------------
                            566 ;	 function getVE
                            567 ;	-----------------------------------------
                            568 ;	Register assignment is optimal.
                            569 ;	Stack space usage: 2 bytes.
   A8A8                     570 _getVE:
   A8A8 A7 FE         [ 2]  571 	ais	#-2
                            572 ;fuel.c:42: int16_t ve = getTableValue(&veTable, currentStatus.MAP, currentStatus.RPM);
   A8AA C6 00 5F      [ 4]  573 	lda	_currentStatus
   A8AD 87            [ 2]  574 	psha
   A8AE 8A            [ 2]  575 	pulh
   A8AF CE 00 60      [ 4]  576 	ldx	(_currentStatus + 1)
   A8B2 C6 00 72      [ 4]  577 	lda	(_currentStatus + 0x0013)
   A8B5 89            [ 2]  578 	pshx
   A8B6 8B            [ 2]  579 	pshh
   A8B7 87            [ 2]  580 	psha
   A8B8 A6 27         [ 2]  581 	lda	#_veTable
   A8BA AE 01         [ 2]  582 	ldx	#>_veTable
   A8BC CD 98 F5      [ 5]  583 	jsr	_getTableValue
   A8BF A7 03         [ 2]  584 	ais	#3
                            585 ;fuel.c:43: if (ve < 0) ve = 0;
   A8C1 9E E7 02      [ 4]  586 	sta	2,s
   A8C4 9E EF 01      [ 4]  587 	stx	1,s
   A8C7 87            [ 2]  588 	psha
   A8C8 9E E6 02      [ 4]  589 	lda	2,s
   A8CB A0 00         [ 2]  590 	sub	#0x00
   A8CD 86            [ 2]  591 	pula
   A8CE 90 02         [ 3]  592 	bge	00102$
   A8D0 5F            [ 1]  593 	clrx
   A8D1 9F            [ 1]  594 	txa
   A8D2                     595 00102$:
                            596 ;fuel.c:44: if (ve > 255) ve = 255;
   A8D2 9E E7 02      [ 4]  597 	sta	2,s
   A8D5 9E EF 01      [ 4]  598 	stx	1,s
   A8D8 87            [ 2]  599 	psha
   A8D9 A6 FF         [ 2]  600 	lda	#0xff
   A8DB 9E E0 03      [ 4]  601 	sub	3,s
   A8DE 4F            [ 1]  602 	clra
   A8DF 9E E2 02      [ 4]  603 	sbc	2,s
   A8E2 86            [ 2]  604 	pula
   A8E3 90 03         [ 3]  605 	bge	00104$
   A8E5 5F            [ 1]  606 	clrx
   A8E6 A6 FF         [ 2]  607 	lda	#0xff
   A8E8                     608 00104$:
                            609 ;fuel.c:45: return (uint8_t)ve;
                            610 ;fuel.c:46: }
   A8E8 A7 02         [ 2]  611 	ais	#2
   A8EA 81            [ 4]  612 	rts
                            613 ;------------------------------------------------------------
                            614 ;Allocation info for local variables in function 'calculateCorrections'
                            615 ;------------------------------------------------------------
                            616 ;total                     Allocated to registers x h 
                            617 ;wue                       Allocated to registers a 
                            618 ;ase                       Allocated to registers h 
                            619 ;clt                       Allocated to registers h 
                            620 ;bat                       Allocated to registers a 
                            621 ;ae                        Allocated to registers a 
                            622 ;sloc0                     Allocated to stack - sp +5
                            623 ;sloc1                     Allocated to stack - sp +1
                            624 ;------------------------------------------------------------
                            625 ;fuel.c:48: uint16_t calculateCorrections(void) {
                            626 ;	-----------------------------------------
                            627 ;	 function calculateCorrections
                            628 ;	-----------------------------------------
                            629 ;	Register assignment is optimal.
                            630 ;	Stack space usage: 8 bytes.
   A8EB                     631 _calculateCorrections:
   A8EB A7 F8         [ 2]  632 	ais	#-8
                            633 ;fuel.c:52: wue = correctionWUE();
   A8ED CD AB 36      [ 5]  634 	jsr	_correctionWUE
                            635 ;fuel.c:53: currentStatus.wueCorrection = wue;
   A8F0 C7 00 87      [ 4]  636 	sta	(_currentStatus + 0x0028)
                            637 ;fuel.c:54: total = (uint16_t)PERCENT(total, wue);
   A8F3 95            [ 2]  638 	tsx
   A8F4 E7 07         [ 3]  639 	sta	7,x
   A8F6 5F            [ 1]  640 	clrx
   A8F7 9E EF 07      [ 4]  641 	stx	7,s
   A8FA 9E EF 06      [ 4]  642 	stx	6,s
   A8FD 9E EF 05      [ 4]  643 	stx	5,s
   A900 95            [ 2]  644 	tsx
   A901 E6 07         [ 3]  645 	lda	7,x
   A903 87            [ 2]  646 	psha
   A904 E6 06         [ 3]  647 	lda	6,x
   A906 87            [ 2]  648 	psha
   A907 E6 05         [ 3]  649 	lda	5,x
   A909 87            [ 2]  650 	psha
   A90A E6 04         [ 3]  651 	lda	4,x
   A90C 87            [ 2]  652 	psha
   A90D A6 64         [ 2]  653 	lda	#0x64
   A90F 87            [ 2]  654 	psha
   A910 4F            [ 1]  655 	clra
   A911 87            [ 2]  656 	psha
   A912 87            [ 2]  657 	psha
   A913 87            [ 2]  658 	psha
   A914 CD D0 87      [ 5]  659 	jsr	__mullong
   A917 9E E7 10      [ 4]  660 	sta	16,s
   A91A 9E EF 0F      [ 4]  661 	stx	15,s
   A91D B6 4A         [ 3]  662 	lda	*___SDCC_hc08_ret2
   A91F 9E E7 0E      [ 4]  663 	sta	14,s
   A922 B6 4B         [ 3]  664 	lda	*___SDCC_hc08_ret3
   A924 9E E7 0D      [ 4]  665 	sta	13,s
   A927 A7 08         [ 2]  666 	ais	#8
   A929 A6 64         [ 2]  667 	lda	#0x64
   A92B 87            [ 2]  668 	psha
   A92C 4F            [ 1]  669 	clra
   A92D 87            [ 2]  670 	psha
   A92E 87            [ 2]  671 	psha
   A92F 87            [ 2]  672 	psha
   A930 95            [ 2]  673 	tsx
   A931 E6 0B         [ 3]  674 	lda	11,x
   A933 87            [ 2]  675 	psha
   A934 E6 0A         [ 3]  676 	lda	10,x
   A936 87            [ 2]  677 	psha
   A937 E6 09         [ 3]  678 	lda	9,x
   A939 87            [ 2]  679 	psha
   A93A E6 08         [ 3]  680 	lda	8,x
   A93C 87            [ 2]  681 	psha
   A93D CD CF 5C      [ 5]  682 	jsr	__divulong
   A940 9E E7 10      [ 4]  683 	sta	16,s
   A943 9E EF 0F      [ 4]  684 	stx	15,s
   A946 B6 4A         [ 3]  685 	lda	*___SDCC_hc08_ret2
   A948 9E E7 0E      [ 4]  686 	sta	14,s
   A94B B6 4B         [ 3]  687 	lda	*___SDCC_hc08_ret3
   A94D 9E E7 0D      [ 4]  688 	sta	13,s
   A950 A7 08         [ 2]  689 	ais	#8
   A952 9E E6 08      [ 4]  690 	lda	8,s
   A955 9E EE 07      [ 4]  691 	ldx	7,s
                            692 ;fuel.c:56: ase = correctionASE();
   A958 87            [ 2]  693 	psha
   A959 89            [ 2]  694 	pshx
   A95A CD AC D1      [ 5]  695 	jsr	_correctionASE
   A95D 87            [ 2]  696 	psha
   A95E 8A            [ 2]  697 	pulh
   A95F 88            [ 2]  698 	pulx
   A960 86            [ 2]  699 	pula
                            700 ;fuel.c:57: total = (uint16_t)PERCENT(total, ase);
   A961 9E E7 08      [ 4]  701 	sta	8,s
   A964 9E EF 07      [ 4]  702 	stx	7,s
   A967 87            [ 2]  703 	psha
   A968 4F            [ 1]  704 	clra
   A969 9E E7 07      [ 4]  705 	sta	7,s
   A96C 4F            [ 1]  706 	clra
   A96D 9E E7 06      [ 4]  707 	sta	6,s
   A970 86            [ 2]  708 	pula
   A971 8B            [ 2]  709 	pshh
   A972 86            [ 2]  710 	pula
   A973 9E E7 04      [ 4]  711 	sta	4,s
   A976 4F            [ 1]  712 	clra
   A977 9E E7 03      [ 4]  713 	sta	3,s
   A97A 9E E7 02      [ 4]  714 	sta	2,s
   A97D 9E E7 01      [ 4]  715 	sta	1,s
   A980 95            [ 2]  716 	tsx
   A981 E6 03         [ 3]  717 	lda	3,x
   A983 87            [ 2]  718 	psha
   A984 E6 02         [ 3]  719 	lda	2,x
   A986 87            [ 2]  720 	psha
   A987 E6 01         [ 3]  721 	lda	1,x
   A989 87            [ 2]  722 	psha
   A98A F6            [ 2]  723 	lda	,x
   A98B 87            [ 2]  724 	psha
   A98C E6 07         [ 3]  725 	lda	7,x
   A98E 87            [ 2]  726 	psha
   A98F E6 06         [ 3]  727 	lda	6,x
   A991 87            [ 2]  728 	psha
   A992 E6 05         [ 3]  729 	lda	5,x
   A994 87            [ 2]  730 	psha
   A995 E6 04         [ 3]  731 	lda	4,x
   A997 87            [ 2]  732 	psha
   A998 CD D0 87      [ 5]  733 	jsr	__mullong
   A99B 9E E7 0C      [ 4]  734 	sta	12,s
   A99E 9E EF 0B      [ 4]  735 	stx	11,s
   A9A1 B6 4A         [ 3]  736 	lda	*___SDCC_hc08_ret2
   A9A3 9E E7 0A      [ 4]  737 	sta	10,s
   A9A6 B6 4B         [ 3]  738 	lda	*___SDCC_hc08_ret3
   A9A8 9E E7 09      [ 4]  739 	sta	9,s
   A9AB A7 08         [ 2]  740 	ais	#8
   A9AD A6 64         [ 2]  741 	lda	#0x64
   A9AF 87            [ 2]  742 	psha
   A9B0 4F            [ 1]  743 	clra
   A9B1 87            [ 2]  744 	psha
   A9B2 87            [ 2]  745 	psha
   A9B3 87            [ 2]  746 	psha
   A9B4 95            [ 2]  747 	tsx
   A9B5 E6 07         [ 3]  748 	lda	7,x
   A9B7 87            [ 2]  749 	psha
   A9B8 E6 06         [ 3]  750 	lda	6,x
   A9BA 87            [ 2]  751 	psha
   A9BB E6 05         [ 3]  752 	lda	5,x
   A9BD 87            [ 2]  753 	psha
   A9BE E6 04         [ 3]  754 	lda	4,x
   A9C0 87            [ 2]  755 	psha
   A9C1 CD CF 5C      [ 5]  756 	jsr	__divulong
   A9C4 9E E7 0C      [ 4]  757 	sta	12,s
   A9C7 9E EF 0B      [ 4]  758 	stx	11,s
   A9CA B6 4A         [ 3]  759 	lda	*___SDCC_hc08_ret2
   A9CC 9E E7 0A      [ 4]  760 	sta	10,s
   A9CF B6 4B         [ 3]  761 	lda	*___SDCC_hc08_ret3
   A9D1 9E E7 09      [ 4]  762 	sta	9,s
   A9D4 A7 08         [ 2]  763 	ais	#8
   A9D6 9E E6 04      [ 4]  764 	lda	4,s
   A9D9 9E EE 03      [ 4]  765 	ldx	3,s
                            766 ;fuel.c:59: clt = correctionCLT();
   A9DC 87            [ 2]  767 	psha
   A9DD 89            [ 2]  768 	pshx
   A9DE CD AD BA      [ 5]  769 	jsr	_correctionCLT
   A9E1 87            [ 2]  770 	psha
   A9E2 8A            [ 2]  771 	pulh
   A9E3 88            [ 2]  772 	pulx
   A9E4 86            [ 2]  773 	pula
                            774 ;fuel.c:60: total = (uint16_t)PERCENT(total, clt);
   A9E5 9E E7 04      [ 4]  775 	sta	4,s
   A9E8 9E EF 03      [ 4]  776 	stx	3,s
   A9EB 87            [ 2]  777 	psha
   A9EC 4F            [ 1]  778 	clra
   A9ED 9E E7 03      [ 4]  779 	sta	3,s
   A9F0 4F            [ 1]  780 	clra
   A9F1 9E E7 02      [ 4]  781 	sta	2,s
   A9F4 86            [ 2]  782 	pula
   A9F5 8B            [ 2]  783 	pshh
   A9F6 86            [ 2]  784 	pula
   A9F7 9E E7 08      [ 4]  785 	sta	8,s
   A9FA 4F            [ 1]  786 	clra
   A9FB 9E E7 07      [ 4]  787 	sta	7,s
   A9FE 9E E7 06      [ 4]  788 	sta	6,s
   AA01 9E E7 05      [ 4]  789 	sta	5,s
   AA04 95            [ 2]  790 	tsx
   AA05 E6 07         [ 3]  791 	lda	7,x
   AA07 87            [ 2]  792 	psha
   AA08 E6 06         [ 3]  793 	lda	6,x
   AA0A 87            [ 2]  794 	psha
   AA0B E6 05         [ 3]  795 	lda	5,x
   AA0D 87            [ 2]  796 	psha
   AA0E E6 04         [ 3]  797 	lda	4,x
   AA10 87            [ 2]  798 	psha
   AA11 E6 03         [ 3]  799 	lda	3,x
   AA13 87            [ 2]  800 	psha
   AA14 E6 02         [ 3]  801 	lda	2,x
   AA16 87            [ 2]  802 	psha
   AA17 E6 01         [ 3]  803 	lda	1,x
   AA19 87            [ 2]  804 	psha
   AA1A F6            [ 2]  805 	lda	,x
   AA1B 87            [ 2]  806 	psha
   AA1C CD D0 87      [ 5]  807 	jsr	__mullong
   AA1F 9E E7 0C      [ 4]  808 	sta	12,s
   AA22 9E EF 0B      [ 4]  809 	stx	11,s
   AA25 B6 4A         [ 3]  810 	lda	*___SDCC_hc08_ret2
   AA27 9E E7 0A      [ 4]  811 	sta	10,s
   AA2A B6 4B         [ 3]  812 	lda	*___SDCC_hc08_ret3
   AA2C 9E E7 09      [ 4]  813 	sta	9,s
   AA2F A7 08         [ 2]  814 	ais	#8
   AA31 A6 64         [ 2]  815 	lda	#0x64
   AA33 87            [ 2]  816 	psha
   AA34 4F            [ 1]  817 	clra
   AA35 87            [ 2]  818 	psha
   AA36 87            [ 2]  819 	psha
   AA37 87            [ 2]  820 	psha
   AA38 95            [ 2]  821 	tsx
   AA39 E6 07         [ 3]  822 	lda	7,x
   AA3B 87            [ 2]  823 	psha
   AA3C E6 06         [ 3]  824 	lda	6,x
   AA3E 87            [ 2]  825 	psha
   AA3F E6 05         [ 3]  826 	lda	5,x
   AA41 87            [ 2]  827 	psha
   AA42 E6 04         [ 3]  828 	lda	4,x
   AA44 87            [ 2]  829 	psha
   AA45 CD CF 5C      [ 5]  830 	jsr	__divulong
   AA48 9E E7 0C      [ 4]  831 	sta	12,s
   AA4B 9E EF 0B      [ 4]  832 	stx	11,s
   AA4E B6 4A         [ 3]  833 	lda	*___SDCC_hc08_ret2
   AA50 9E E7 0A      [ 4]  834 	sta	10,s
   AA53 B6 4B         [ 3]  835 	lda	*___SDCC_hc08_ret3
   AA55 9E E7 09      [ 4]  836 	sta	9,s
   AA58 A7 08         [ 2]  837 	ais	#8
   AA5A 9E EE 04      [ 4]  838 	ldx	4,s
   AA5D 9E E6 03      [ 4]  839 	lda	3,s
   AA60 87            [ 2]  840 	psha
   AA61 8A            [ 2]  841 	pulh
                            842 ;fuel.c:62: bat = correctionBattery();
   AA62 89            [ 2]  843 	pshx
   AA63 8B            [ 2]  844 	pshh
   AA64 CD AD E4      [ 5]  845 	jsr	_correctionBattery
   AA67 8A            [ 2]  846 	pulh
   AA68 88            [ 2]  847 	pulx
                            848 ;fuel.c:63: currentStatus.batCorrection = bat;
   AA69 C7 00 88      [ 4]  849 	sta	(_currentStatus + 0x0029)
                            850 ;fuel.c:64: total = (uint16_t)PERCENT(total, bat);
   AA6C 9E EF 04      [ 4]  851 	stx	4,s
   AA6F 87            [ 2]  852 	psha
   AA70 8B            [ 2]  853 	pshh
   AA71 86            [ 2]  854 	pula
   AA72 9E E7 04      [ 4]  855 	sta	4,s
   AA75 4F            [ 1]  856 	clra
   AA76 9E E7 03      [ 4]  857 	sta	3,s
   AA79 4F            [ 1]  858 	clra
   AA7A 9E E7 02      [ 4]  859 	sta	2,s
   AA7D 86            [ 2]  860 	pula
   AA7E 95            [ 2]  861 	tsx
   AA7F E7 07         [ 3]  862 	sta	7,x
   AA81 5F            [ 1]  863 	clrx
   AA82 9E EF 07      [ 4]  864 	stx	7,s
   AA85 9E EF 06      [ 4]  865 	stx	6,s
   AA88 9E EF 05      [ 4]  866 	stx	5,s
   AA8B 95            [ 2]  867 	tsx
   AA8C E6 07         [ 3]  868 	lda	7,x
   AA8E 87            [ 2]  869 	psha
   AA8F E6 06         [ 3]  870 	lda	6,x
   AA91 87            [ 2]  871 	psha
   AA92 E6 05         [ 3]  872 	lda	5,x
   AA94 87            [ 2]  873 	psha
   AA95 E6 04         [ 3]  874 	lda	4,x
   AA97 87            [ 2]  875 	psha
   AA98 E6 03         [ 3]  876 	lda	3,x
   AA9A 87            [ 2]  877 	psha
   AA9B E6 02         [ 3]  878 	lda	2,x
   AA9D 87            [ 2]  879 	psha
   AA9E E6 01         [ 3]  880 	lda	1,x
   AAA0 87            [ 2]  881 	psha
   AAA1 F6            [ 2]  882 	lda	,x
   AAA2 87            [ 2]  883 	psha
   AAA3 CD D0 87      [ 5]  884 	jsr	__mullong
   AAA6 9E E7 0C      [ 4]  885 	sta	12,s
   AAA9 9E EF 0B      [ 4]  886 	stx	11,s
   AAAC B6 4A         [ 3]  887 	lda	*___SDCC_hc08_ret2
   AAAE 9E E7 0A      [ 4]  888 	sta	10,s
   AAB1 B6 4B         [ 3]  889 	lda	*___SDCC_hc08_ret3
   AAB3 9E E7 09      [ 4]  890 	sta	9,s
   AAB6 A7 08         [ 2]  891 	ais	#8
   AAB8 A6 64         [ 2]  892 	lda	#0x64
   AABA 87            [ 2]  893 	psha
   AABB 4F            [ 1]  894 	clra
   AABC 87            [ 2]  895 	psha
   AABD 87            [ 2]  896 	psha
   AABE 87            [ 2]  897 	psha
   AABF 95            [ 2]  898 	tsx
   AAC0 E6 07         [ 3]  899 	lda	7,x
   AAC2 87            [ 2]  900 	psha
   AAC3 E6 06         [ 3]  901 	lda	6,x
   AAC5 87            [ 2]  902 	psha
   AAC6 E6 05         [ 3]  903 	lda	5,x
   AAC8 87            [ 2]  904 	psha
   AAC9 E6 04         [ 3]  905 	lda	4,x
   AACB 87            [ 2]  906 	psha
   AACC CD CF 5C      [ 5]  907 	jsr	__divulong
   AACF 9E E7 0C      [ 4]  908 	sta	12,s
   AAD2 9E EF 0B      [ 4]  909 	stx	11,s
   AAD5 B6 4A         [ 3]  910 	lda	*___SDCC_hc08_ret2
   AAD7 9E E7 0A      [ 4]  911 	sta	10,s
   AADA B6 4B         [ 3]  912 	lda	*___SDCC_hc08_ret3
   AADC 9E E7 09      [ 4]  913 	sta	9,s
   AADF A7 08         [ 2]  914 	ais	#8
   AAE1 95            [ 2]  915 	tsx
   AAE2 E6 03         [ 3]  916 	lda	3,x
   AAE4 E7 01         [ 3]  917 	sta	1,x
   AAE6 E6 02         [ 3]  918 	lda	2,x
   AAE8 F7            [ 2]  919 	sta	,x
                            920 ;fuel.c:66: ae = correctionAE();
   AAE9 CD AD 4D      [ 5]  921 	jsr	_correctionAE
                            922 ;fuel.c:67: total += ae;
   AAEC 97            [ 1]  923 	tax
   AAED 8C            [ 1]  924 	clrh
   AAEE 9E E6 02      [ 4]  925 	lda	2,s
   AAF1 9E E7 02      [ 4]  926 	sta	2,s
   AAF4 9E E6 01      [ 4]  927 	lda	1,s
   AAF7 9E E7 01      [ 4]  928 	sta	1,s
   AAFA 9F            [ 1]  929 	txa
   AAFB 9E EB 02      [ 4]  930 	add	2,s
   AAFE 87            [ 2]  931 	psha
   AAFF 8B            [ 2]  932 	pshh
   AB00 86            [ 2]  933 	pula
   AB01 9E E9 02      [ 4]  934 	adc	2,s
   AB04 97            [ 1]  935 	tax
   AB05 86            [ 2]  936 	pula
                            937 ;fuel.c:69: if (total < CORR_MIN) total = CORR_MIN;
   AB06 9E E7 02      [ 4]  938 	sta	2,s
   AB09 9E EF 01      [ 4]  939 	stx	1,s
   AB0C 87            [ 2]  940 	psha
   AB0D 9E E6 03      [ 4]  941 	lda	3,s
   AB10 A0 32         [ 2]  942 	sub	#0x32
   AB12 9E E6 02      [ 4]  943 	lda	2,s
   AB15 A2 00         [ 2]  944 	sbc	#0x00
   AB17 86            [ 2]  945 	pula
   AB18 24 03         [ 3]  946 	bcc	00102$
   AB1A 5F            [ 1]  947 	clrx
   AB1B A6 32         [ 2]  948 	lda	#0x32
   AB1D                     949 00102$:
                            950 ;fuel.c:70: if (total > CORR_MAX) total = CORR_MAX;
   AB1D 9E E7 02      [ 4]  951 	sta	2,s
   AB20 9E EF 01      [ 4]  952 	stx	1,s
   AB23 87            [ 2]  953 	psha
   AB24 A6 C8         [ 2]  954 	lda	#0xc8
   AB26 9E E0 03      [ 4]  955 	sub	3,s
   AB29 4F            [ 1]  956 	clra
   AB2A 9E E2 02      [ 4]  957 	sbc	2,s
   AB2D 86            [ 2]  958 	pula
   AB2E 24 03         [ 3]  959 	bcc	00104$
   AB30 5F            [ 1]  960 	clrx
   AB31 A6 C8         [ 2]  961 	lda	#0xc8
   AB33                     962 00104$:
                            963 ;fuel.c:72: return total;
                            964 ;fuel.c:73: }
   AB33 A7 08         [ 2]  965 	ais	#8
   AB35 81            [ 4]  966 	rts
                            967 ;------------------------------------------------------------
                            968 ;Allocation info for local variables in function 'correctionWUE'
                            969 ;------------------------------------------------------------
                            970 ;temp                      Allocated to stack - sp +22
                            971 ;i                         Allocated to stack - sp +18
                            972 ;t1                        Allocated to registers a 
                            973 ;t2                        Allocated to stack - sp +21
                            974 ;v1                        Allocated to stack - sp +20
                            975 ;v2                        Allocated to stack - sp +19
                            976 ;sloc0                     Allocated to stack - sp +10
                            977 ;sloc1                     Allocated to stack - sp +11
                            978 ;sloc2                     Allocated to stack - sp +13
                            979 ;sloc3                     Allocated to stack - sp +3
                            980 ;sloc4                     Allocated to stack - sp +1
                            981 ;sloc5                     Allocated to stack - sp +6
                            982 ;sloc6                     Allocated to stack - sp +4
                            983 ;sloc7                     Allocated to stack - sp +14
                            984 ;------------------------------------------------------------
                            985 ;fuel.c:75: uint8_t correctionWUE(void) {
                            986 ;	-----------------------------------------
                            987 ;	 function correctionWUE
                            988 ;	-----------------------------------------
                            989 ;	Register assignment might be sub-optimal.
                            990 ;	Stack space usage: 22 bytes.
   AB36                     991 _correctionWUE:
   AB36 A7 EA         [ 2]  992 	ais	#-22
                            993 ;fuel.c:76: int8_t temp = currentStatus.coolant;
   AB38 C6 00 74      [ 4]  994 	lda	(_currentStatus + 0x0015)
   AB3B 9E E7 16      [ 4]  995 	sta	22,s
                            996 ;fuel.c:79: if (!BIT_CHECK(currentStatus.engineStatus, ENGINE_WARMUP)) {
   AB3E C6 00 89      [ 4]  997 	lda	(_currentStatus + 0x002a)
   AB41 A5 08         [ 2]  998 	bit	#0x08
   AB43 26 05         [ 3]  999 	bne	00102$
                           1000 ;fuel.c:80: return 100;
   AB45 A6 64         [ 2] 1001 	lda	#0x64
   AB47 CC AC CE      [ 3] 1002 	jmp	00111$
   AB4A                    1003 00102$:
                           1004 ;fuel.c:83: for (i = 0; i < 5; i++) {
   AB4A 95            [ 2] 1005 	tsx
   AB4B 4F            [ 1] 1006 	clra
   AB4C E7 09         [ 3] 1007 	sta	9,x
   AB4E E7 11         [ 3] 1008 	sta	17,x
   AB50                    1009 00109$:
                           1010 ;fuel.c:84: if (temp >= configPage1.wueBins[i] && temp < configPage1.wueBins[i + 1]) {
   AB50 95            [ 2] 1011 	tsx
   AB51 E6 15         [ 3] 1012 	lda	21,x
   AB53 E7 0B         [ 3] 1013 	sta	11,x
   AB55 49            [ 1] 1014 	rola	
   AB56 4F            [ 1] 1015 	clra	
   AB57 A2 00         [ 2] 1016 	sbc	#0x00
   AB59 E7 0A         [ 3] 1017 	sta	10,x
   AB5B EE 11         [ 3] 1018 	ldx	17,x
   AB5D 8C            [ 1] 1019 	clrh
   AB5E D6 00 A7      [ 4] 1020 	lda	((_configPage1 + 0x000b)),x
   AB61 5F            [ 1] 1021 	clrx
   AB62 87            [ 2] 1022 	psha
   AB63 9E E6 0D      [ 4] 1023 	lda	13,s
   AB66 9E E0 01      [ 4] 1024 	sub	1, s
   AB69 86            [ 2] 1025 	pula
   AB6A 9E E6 0B      [ 4] 1026 	lda	11,s
   AB6D 89            [ 2] 1027 	pshx
   AB6E 9E E2 01      [ 4] 1028 	sbc	1,s
   AB71 A7 01         [ 2] 1029 	ais	#1
   AB73 90 03         [ 3] 1030 	bge	00144$
   AB75 CC AC 9F      [ 3] 1031 	jmp	00110$
   AB78                    1032 00144$:
   AB78 95            [ 2] 1033 	tsx
   AB79 E6 11         [ 3] 1034 	lda	17,x
   AB7B AB 01         [ 2] 1035 	add	#0x01
   AB7D E7 0C         [ 3] 1036 	sta	12,x
   AB7F EE 0C         [ 3] 1037 	ldx	12,x
   AB81 8C            [ 1] 1038 	clrh
   AB82 D6 00 A7      [ 4] 1039 	lda	((_configPage1 + 0x000b)),x
   AB85 9E E7 03      [ 4] 1040 	sta	3,s
   AB88 9E E6 03      [ 4] 1041 	lda	3,s
   AB8B 5F            [ 1] 1042 	clrx
   AB8C 87            [ 2] 1043 	psha
   AB8D 9E E6 0D      [ 4] 1044 	lda	13,s
   AB90 9E E0 01      [ 4] 1045 	sub	1, s
   AB93 86            [ 2] 1046 	pula
   AB94 9E E6 0B      [ 4] 1047 	lda	11,s
   AB97 89            [ 2] 1048 	pshx
   AB98 9E E2 01      [ 4] 1049 	sbc	1,s
   AB9B A7 01         [ 2] 1050 	ais	#1
   AB9D 91 03         [ 3] 1051 	blt	00145$
   AB9F CC AC 9F      [ 3] 1052 	jmp	00110$
   ABA2                    1053 00145$:
                           1054 ;fuel.c:85: int8_t t1 = configPage1.wueBins[i];
   ABA2 9E EE 0A      [ 4] 1055 	ldx	10,s
   ABA5 D6 00 A7      [ 4] 1056 	lda	((_configPage1 + 0x000b)),x
                           1057 ;fuel.c:86: int8_t t2 = configPage1.wueBins[i + 1];
   ABA8 95            [ 2] 1058 	tsx
   ABA9 EE 02         [ 3] 1059 	ldx	2,x
   ABAB 9E EF 15      [ 4] 1060 	stx	21,s
                           1061 ;fuel.c:87: uint8_t v1 = configPage1.wueValues[i];
   ABAE 9E EE 0A      [ 4] 1062 	ldx	10,s
   ABB1 8C            [ 1] 1063 	clrh
   ABB2 DE 00 AD      [ 4] 1064 	ldx	((_configPage1 + 0x0011)),x
   ABB5 9E EF 14      [ 4] 1065 	stx	20,s
                           1066 ;fuel.c:88: uint8_t v2 = configPage1.wueValues[i + 1];
   ABB8 9E EE 0D      [ 4] 1067 	ldx	13,s
   ABBB DE 00 AD      [ 4] 1068 	ldx	((_configPage1 + 0x0011)),x
   ABBE 9E EF 13      [ 4] 1069 	stx	19,s
                           1070 ;fuel.c:89: return (uint8_t)(v1 + (int32_t)(temp - t1) * (v2 - v1) / (t2 - t1));
   ABC1 95            [ 2] 1071 	tsx
   ABC2 E7 01         [ 3] 1072 	sta	1,x
   ABC4 49            [ 1] 1073 	rola	
   ABC5 4F            [ 1] 1074 	clra	
   ABC6 A2 00         [ 2] 1075 	sbc	#0x00
   ABC8 F7            [ 2] 1076 	sta	,x
   ABC9 E6 0B         [ 3] 1077 	lda	11,x
   ABCB E0 01         [ 3] 1078 	sub	1,x
   ABCD 87            [ 2] 1079 	psha
   ABCE E6 0A         [ 3] 1080 	lda	10,x
   ABD0 F2            [ 2] 1081 	sbc	,x
   ABD1 97            [ 1] 1082 	tax
   ABD2 86            [ 2] 1083 	pula
   ABD3 9E E7 09      [ 4] 1084 	sta	9,s
   ABD6 9F            [ 1] 1085 	txa
   ABD7 9E E7 08      [ 4] 1086 	sta	8,s
   ABDA 49            [ 1] 1087 	rola	
   ABDB 4F            [ 1] 1088 	clra	
   ABDC A2 00         [ 2] 1089 	sbc	#0x00
   ABDE 9E E7 07      [ 4] 1090 	sta	7,s
   ABE1 9E E7 06      [ 4] 1091 	sta	6,s
   ABE4 9E EE 13      [ 4] 1092 	ldx	19,s
   ABE7 8C            [ 1] 1093 	clrh
   ABE8 9E E6 14      [ 4] 1094 	lda	20,s
   ABEB 9E E7 05      [ 4] 1095 	sta	5,s
   ABEE 4F            [ 1] 1096 	clra
   ABEF 9E E7 04      [ 4] 1097 	sta	4,s
   ABF2 9F            [ 1] 1098 	txa
   ABF3 9E E0 05      [ 4] 1099 	sub	5,s
   ABF6 87            [ 2] 1100 	psha
   ABF7 8B            [ 2] 1101 	pshh
   ABF8 86            [ 2] 1102 	pula
   ABF9 9E E2 05      [ 4] 1103 	sbc	5,s
   ABFC 97            [ 1] 1104 	tax
   ABFD 86            [ 2] 1105 	pula
   ABFE 9E E7 11      [ 4] 1106 	sta	17,s
   AC01 9F            [ 1] 1107 	txa
   AC02 9E E7 10      [ 4] 1108 	sta	16,s
   AC05 49            [ 1] 1109 	rola	
   AC06 4F            [ 1] 1110 	clra	
   AC07 A2 00         [ 2] 1111 	sbc	#0x00
   AC09 9E E7 0F      [ 4] 1112 	sta	15,s
   AC0C 9E E7 0E      [ 4] 1113 	sta	14,s
   AC0F 95            [ 2] 1114 	tsx
   AC10 E6 10         [ 3] 1115 	lda	16,x
   AC12 87            [ 2] 1116 	psha
   AC13 E6 0F         [ 3] 1117 	lda	15,x
   AC15 87            [ 2] 1118 	psha
   AC16 E6 0E         [ 3] 1119 	lda	14,x
   AC18 87            [ 2] 1120 	psha
   AC19 E6 0D         [ 3] 1121 	lda	13,x
   AC1B 87            [ 2] 1122 	psha
   AC1C E6 08         [ 3] 1123 	lda	8,x
   AC1E 87            [ 2] 1124 	psha
   AC1F E6 07         [ 3] 1125 	lda	7,x
   AC21 87            [ 2] 1126 	psha
   AC22 E6 06         [ 3] 1127 	lda	6,x
   AC24 87            [ 2] 1128 	psha
   AC25 E6 05         [ 3] 1129 	lda	5,x
   AC27 87            [ 2] 1130 	psha
   AC28 CD D0 87      [ 5] 1131 	jsr	__mullong
   AC2B 9E E7 19      [ 4] 1132 	sta	25,s
   AC2E 9E EF 18      [ 4] 1133 	stx	24,s
   AC31 B6 4A         [ 3] 1134 	lda	*___SDCC_hc08_ret2
   AC33 9E E7 17      [ 4] 1135 	sta	23,s
   AC36 B6 4B         [ 3] 1136 	lda	*___SDCC_hc08_ret3
   AC38 9E E7 16      [ 4] 1137 	sta	22,s
   AC3B A7 08         [ 2] 1138 	ais	#8
   AC3D 9E E6 15      [ 4] 1139 	lda	21,s
   AC40 87            [ 2] 1140 	psha
   AC41 49            [ 1] 1141 	rola	
   AC42 4F            [ 1] 1142 	clra	
   AC43 A2 00         [ 2] 1143 	sbc	#0x00
   AC45 97            [ 1] 1144 	tax
   AC46 86            [ 2] 1145 	pula
   AC47 9E E0 02      [ 4] 1146 	sub	2,s
   AC4A 87            [ 2] 1147 	psha
   AC4B 9F            [ 1] 1148 	txa
   AC4C 9E E2 02      [ 4] 1149 	sbc	2,s
   AC4F 97            [ 1] 1150 	tax
   AC50 86            [ 2] 1151 	pula
   AC51 9E E7 09      [ 4] 1152 	sta	9,s
   AC54 9F            [ 1] 1153 	txa
   AC55 9E E7 08      [ 4] 1154 	sta	8,s
   AC58 49            [ 1] 1155 	rola	
   AC59 4F            [ 1] 1156 	clra	
   AC5A A2 00         [ 2] 1157 	sbc	#0x00
   AC5C 9E E7 07      [ 4] 1158 	sta	7,s
   AC5F 9E E7 06      [ 4] 1159 	sta	6,s
   AC62 95            [ 2] 1160 	tsx
   AC63 E6 08         [ 3] 1161 	lda	8,x
   AC65 87            [ 2] 1162 	psha
   AC66 E6 07         [ 3] 1163 	lda	7,x
   AC68 87            [ 2] 1164 	psha
   AC69 E6 06         [ 3] 1165 	lda	6,x
   AC6B 87            [ 2] 1166 	psha
   AC6C E6 05         [ 3] 1167 	lda	5,x
   AC6E 87            [ 2] 1168 	psha
   AC6F E6 10         [ 3] 1169 	lda	16,x
   AC71 87            [ 2] 1170 	psha
   AC72 E6 0F         [ 3] 1171 	lda	15,x
   AC74 87            [ 2] 1172 	psha
   AC75 E6 0E         [ 3] 1173 	lda	14,x
   AC77 87            [ 2] 1174 	psha
   AC78 E6 0D         [ 3] 1175 	lda	13,x
   AC7A 87            [ 2] 1176 	psha
   AC7B CD CE 92      [ 5] 1177 	jsr	__divslong
   AC7E 9E E7 19      [ 4] 1178 	sta	25,s
   AC81 9E EF 18      [ 4] 1179 	stx	24,s
   AC84 B6 4A         [ 3] 1180 	lda	*___SDCC_hc08_ret2
   AC86 9E E7 17      [ 4] 1181 	sta	23,s
   AC89 B6 4B         [ 3] 1182 	lda	*___SDCC_hc08_ret3
   AC8B 9E E7 16      [ 4] 1183 	sta	22,s
   AC8E A7 08         [ 2] 1184 	ais	#8
   AC90 95            [ 2] 1185 	tsx
   AC91 E6 10         [ 3] 1186 	lda	16,x
   AC93 E7 0D         [ 3] 1187 	sta	13,x
   AC95 E6 13         [ 3] 1188 	lda	19,x
   AC97 E7 03         [ 3] 1189 	sta	3,x
   AC99 E6 0D         [ 3] 1190 	lda	13,x
   AC9B EB 03         [ 3] 1191 	add	3,x
   AC9D 20 2F         [ 3] 1192 	bra	00111$
   AC9F                    1193 00110$:
                           1194 ;fuel.c:83: for (i = 0; i < 5; i++) {
   AC9F 95            [ 2] 1195 	tsx
   ACA0 6C 11         [ 4] 1196 	inc	17,x
   ACA2 E6 11         [ 3] 1197 	lda	17,x
   ACA4 E7 09         [ 3] 1198 	sta	9,x
   ACA6 E6 11         [ 3] 1199 	lda	17,x
   ACA8 A1 05         [ 2] 1200 	cmp	#0x05
   ACAA 24 03         [ 3] 1201 	bcc	00146$
   ACAC CC AB 50      [ 3] 1202 	jmp	00109$
   ACAF                    1203 00146$:
                           1204 ;fuel.c:93: if (temp < configPage1.wueBins[0]) {
   ACAF C6 00 A7      [ 4] 1205 	lda	(_configPage1 + 0x000b)
   ACB2 5F            [ 1] 1206 	clrx
   ACB3 87            [ 2] 1207 	psha
   ACB4 9E E6 0D      [ 4] 1208 	lda	13,s
   ACB7 9E E0 01      [ 4] 1209 	sub	1, s
   ACBA 86            [ 2] 1210 	pula
   ACBB 9E E6 0B      [ 4] 1211 	lda	11,s
   ACBE 89            [ 2] 1212 	pshx
   ACBF 9E E2 01      [ 4] 1213 	sbc	1,s
   ACC2 A7 01         [ 2] 1214 	ais	#1
   ACC4 90 05         [ 3] 1215 	bge	00108$
                           1216 ;fuel.c:94: return configPage1.wueValues[0];
   ACC6 C6 00 AD      [ 4] 1217 	lda	(_configPage1 + 0x0011)
   ACC9 20 03         [ 3] 1218 	bra	00111$
   ACCB                    1219 00108$:
                           1220 ;fuel.c:96: return configPage1.wueValues[5];
   ACCB C6 00 B2      [ 4] 1221 	lda	(_configPage1 + 0x0016)
   ACCE                    1222 00111$:
                           1223 ;fuel.c:97: }
   ACCE A7 16         [ 2] 1224 	ais	#22
   ACD0 81            [ 4] 1225 	rts
                           1226 ;------------------------------------------------------------
                           1227 ;Allocation info for local variables in function 'correctionASE'
                           1228 ;------------------------------------------------------------
                           1229 ;fuel.c:99: uint8_t correctionASE(void) {
                           1230 ;	-----------------------------------------
                           1231 ;	 function correctionASE
                           1232 ;	-----------------------------------------
                           1233 ;	Register assignment is optimal.
                           1234 ;	Stack space usage: 0 bytes.
   ACD1                    1235 _correctionASE:
                           1236 ;fuel.c:100: if (!BIT_CHECK(currentStatus.engineStatus, ENGINE_ASE)) {
   ACD1 C6 00 89      [ 4] 1237 	lda	(_currentStatus + 0x002a)
   ACD4 A5 04         [ 2] 1238 	bit	#0x04
   ACD6 26 03         [ 3] 1239 	bne	00102$
                           1240 ;fuel.c:101: return 100;
   ACD8 A6 64         [ 2] 1241 	lda	#0x64
   ACDA 81            [ 4] 1242 	rts
   ACDB                    1243 00102$:
                           1244 ;fuel.c:103: return aseValue;
   ACDB C6 01 D6      [ 4] 1245 	lda	_aseValue
                           1246 ;fuel.c:104: }
   ACDE 81            [ 4] 1247 	rts
                           1248 ;------------------------------------------------------------
                           1249 ;Allocation info for local variables in function 'startASE'
                           1250 ;------------------------------------------------------------
                           1251 ;fuel.c:106: void startASE(void) {
                           1252 ;	-----------------------------------------
                           1253 ;	 function startASE
                           1254 ;	-----------------------------------------
                           1255 ;	Register assignment is optimal.
                           1256 ;	Stack space usage: 0 bytes.
   ACDF                    1257 _startASE:
                           1258 ;fuel.c:107: aseCounter = configPage1.aseCount;
   ACDF C6 00 B4      [ 4] 1259 	lda	(_configPage1 + 0x0018)
   ACE2 C7 01 D5      [ 4] 1260 	sta	_aseCounter
                           1261 ;fuel.c:108: aseValue = configPage1.asePct;
   ACE5 C6 00 B3      [ 4] 1262 	lda	(_configPage1 + 0x0017)
   ACE8 C7 01 D6      [ 4] 1263 	sta	_aseValue
                           1264 ;fuel.c:109: BIT_SET(currentStatus.engineStatus, ENGINE_ASE);
   ACEB C6 00 89      [ 4] 1265 	lda	(_currentStatus + 0x002a)
   ACEE AA 04         [ 2] 1266 	ora	#0x04
   ACF0 C7 00 89      [ 4] 1267 	sta	(_currentStatus + 0x002a)
                           1268 ;fuel.c:110: }
   ACF3 81            [ 4] 1269 	rts
                           1270 ;------------------------------------------------------------
                           1271 ;Allocation info for local variables in function 'decrementASE'
                           1272 ;------------------------------------------------------------
                           1273 ;step                      Allocated to registers a x 
                           1274 ;sloc0                     Allocated to stack - sp +1
                           1275 ;------------------------------------------------------------
                           1276 ;fuel.c:112: void decrementASE(void) {
                           1277 ;	-----------------------------------------
                           1278 ;	 function decrementASE
                           1279 ;	-----------------------------------------
                           1280 ;	Register assignment is optimal.
                           1281 ;	Stack space usage: 2 bytes.
   ACF4                    1282 _decrementASE:
   ACF4 A7 FE         [ 2] 1283 	ais	#-2
                           1284 ;fuel.c:113: if (aseCounter > 0) {
   ACF6 C6 01 D5      [ 4] 1285 	lda	_aseCounter
   ACF9 27 42         [ 3] 1286 	beq	00106$
                           1287 ;fuel.c:114: aseCounter--;
   ACFB 45 01 D5      [ 3] 1288 	ldhx	#_aseCounter
   ACFE 7A            [ 3] 1289 	dec	,x
                           1290 ;fuel.c:116: if (configPage1.aseCount > 0) {
   ACFF C6 00 B4      [ 4] 1291 	lda	(_configPage1 + 0x0018)
   AD02 27 46         [ 3] 1292 	beq	00108$
                           1293 ;fuel.c:117: uint16_t step = (uint16_t)(configPage1.asePct - 100) / configPage1.aseCount;
   AD04 CE 00 B3      [ 4] 1294 	ldx	(_configPage1 + 0x0017)
   AD07 8C            [ 1] 1295 	clrh
   AD08 AF 9C         [ 2] 1296 	aix	#-100
   AD0A 9E EF 02      [ 4] 1297 	stx	2,s
   AD0D 87            [ 2] 1298 	psha
   AD0E 8B            [ 2] 1299 	pshh
   AD0F 86            [ 2] 1300 	pula
   AD10 9E E7 02      [ 4] 1301 	sta	2,s
   AD13 86            [ 2] 1302 	pula
   AD14 5F            [ 1] 1303 	clrx
   AD15 87            [ 2] 1304 	psha
   AD16 89            [ 2] 1305 	pshx
   AD17 95            [ 2] 1306 	tsx
   AD18 E6 03         [ 3] 1307 	lda	3,x
   AD1A EE 02         [ 3] 1308 	ldx	2,x
   AD1C CD CE 04      [ 5] 1309 	jsr	__divuint
   AD1F A7 02         [ 2] 1310 	ais	#2
                           1311 ;fuel.c:118: aseValue = (uint8_t)(aseValue - step);
   AD21 45 01 D6      [ 3] 1312 	ldhx	#_aseValue
   AD24 F0            [ 2] 1313 	sub	,x
   AD25 40            [ 1] 1314 	nega	
   AD26 F7            [ 2] 1315 	sta	,x
                           1316 ;fuel.c:120: if (aseValue <= 100) {
   AD27 C6 01 D6      [ 4] 1317 	lda	_aseValue
   AD2A A1 64         [ 2] 1318 	cmp	#0x64
   AD2C 22 1C         [ 3] 1319 	bhi	00108$
                           1320 ;fuel.c:121: aseValue = 100;
   AD2E A6 64         [ 2] 1321 	lda	#0x64
   AD30 C7 01 D6      [ 4] 1322 	sta	_aseValue
                           1323 ;fuel.c:122: BIT_CLEAR(currentStatus.engineStatus, ENGINE_ASE);
   AD33 C6 00 89      [ 4] 1324 	lda	(_currentStatus + 0x002a)
   AD36 A4 FB         [ 2] 1325 	and	#0xfb
   AD38 C7 00 89      [ 4] 1326 	sta	(_currentStatus + 0x002a)
   AD3B 20 0D         [ 3] 1327 	bra	00108$
   AD3D                    1328 00106$:
                           1329 ;fuel.c:126: aseValue = 100;
   AD3D A6 64         [ 2] 1330 	lda	#0x64
   AD3F C7 01 D6      [ 4] 1331 	sta	_aseValue
                           1332 ;fuel.c:127: BIT_CLEAR(currentStatus.engineStatus, ENGINE_ASE);
   AD42 C6 00 89      [ 4] 1333 	lda	(_currentStatus + 0x002a)
   AD45 A4 FB         [ 2] 1334 	and	#0xfb
   AD47 C7 00 89      [ 4] 1335 	sta	(_currentStatus + 0x002a)
   AD4A                    1336 00108$:
                           1337 ;fuel.c:129: }
   AD4A A7 02         [ 2] 1338 	ais	#2
   AD4C 81            [ 4] 1339 	rts
                           1340 ;------------------------------------------------------------
                           1341 ;Allocation info for local variables in function 'correctionAE'
                           1342 ;------------------------------------------------------------
                           1343 ;ae                        Allocated to stack - sp +3
                           1344 ;sloc0                     Allocated to stack - sp +1
                           1345 ;------------------------------------------------------------
                           1346 ;fuel.c:131: uint8_t correctionAE(void) {
                           1347 ;	-----------------------------------------
                           1348 ;	 function correctionAE
                           1349 ;	-----------------------------------------
                           1350 ;	Register assignment might be sub-optimal.
                           1351 ;	Stack space usage: 3 bytes.
   AD4D                    1352 _correctionAE:
   AD4D A7 FD         [ 2] 1353 	ais	#-3
                           1354 ;fuel.c:132: if (configPage1.aeMode != AE_MODE_TPS) {
   AD4F C6 00 B5      [ 4] 1355 	lda	(_configPage1 + 0x0019)
   AD52 27 03         [ 3] 1356 	beq	00102$
                           1357 ;fuel.c:133: return 0;
   AD54 4F            [ 1] 1358 	clra
   AD55 20 60         [ 3] 1359 	bra	00107$
   AD57                    1360 00102$:
                           1361 ;fuel.c:136: if (currentStatus.TPSdot > configPage1.aeThresh) {
   AD57 C6 00 99      [ 4] 1362 	lda	(_currentStatus + 0x003a)
   AD5A 9E E7 01      [ 4] 1363 	sta	1,s
   AD5D C6 00 9A      [ 4] 1364 	lda	((_currentStatus + 0x003a) + 1)
   AD60 9E E7 02      [ 4] 1365 	sta	2,s
   AD63 CE 00 B6      [ 4] 1366 	ldx	(_configPage1 + 0x001a)
   AD66 8C            [ 1] 1367 	clrh
                           1368 ;fuel.c:138: BIT_SET(currentStatus.engineStatus, ENGINE_ACC);
   AD67 C6 00 89      [ 4] 1369 	lda	(_currentStatus + 0x002a)
                           1370 ;fuel.c:136: if (currentStatus.TPSdot > configPage1.aeThresh) {
   AD6A 87            [ 2] 1371 	psha
   AD6B 9F            [ 1] 1372 	txa
   AD6C 9E E0 03      [ 4] 1373 	sub	3,s
   AD6F 8B            [ 2] 1374 	pshh
   AD70 86            [ 2] 1375 	pula
   AD71 9E E2 02      [ 4] 1376 	sbc	2,s
   AD74 86            [ 2] 1377 	pula
   AD75 90 3A         [ 3] 1378 	bge	00106$
                           1379 ;fuel.c:138: BIT_SET(currentStatus.engineStatus, ENGINE_ACC);
   AD77 AA 10         [ 2] 1380 	ora	#0x10
   AD79 C7 00 89      [ 4] 1381 	sta	(_currentStatus + 0x002a)
                           1382 ;fuel.c:140: ae = (uint8_t)(configPage1.aePct - 100);
   AD7C C6 00 B7      [ 4] 1383 	lda	(_configPage1 + 0x001b)
   AD7F A0 64         [ 2] 1384 	sub	#0x64
   AD81 9E E7 03      [ 4] 1385 	sta	3,s
                           1386 ;fuel.c:142: if (currentStatus.TPSdot > ((int16_t)configPage1.aeThresh * 3)) {
   AD84 C6 00 99      [ 4] 1387 	lda	(_currentStatus + 0x003a)
   AD87 9E E7 01      [ 4] 1388 	sta	1,s
   AD8A C6 00 9A      [ 4] 1389 	lda	((_currentStatus + 0x003a) + 1)
   AD8D 9E E7 02      [ 4] 1390 	sta	2,s
   AD90 C6 00 B6      [ 4] 1391 	lda	(_configPage1 + 0x001a)
   AD93 5F            [ 1] 1392 	clrx
   AD94 87            [ 2] 1393 	psha
   AD95 89            [ 2] 1394 	pshx
   AD96 A6 03         [ 2] 1395 	lda	#0x03
   AD98 CD CE 65      [ 5] 1396 	jsr	__mulint
   AD9B A7 02         [ 2] 1397 	ais	#2
   AD9D 9E E0 02      [ 4] 1398 	sub	2,s
   ADA0 9F            [ 1] 1399 	txa
   ADA1 9E E2 01      [ 4] 1400 	sbc	1,s
   ADA4 90 06         [ 3] 1401 	bge	00104$
                           1402 ;fuel.c:143: ae = (uint8_t)(ae * 2);
   ADA6 95            [ 2] 1403 	tsx
   ADA7 E6 02         [ 3] 1404 	lda	2,x
   ADA9 48            [ 1] 1405 	lsla	
   ADAA E7 02         [ 3] 1406 	sta	2,x
   ADAC                    1407 00104$:
                           1408 ;fuel.c:146: return ae;
   ADAC 9E E6 03      [ 4] 1409 	lda	3,s
   ADAF 20 06         [ 3] 1410 	bra	00107$
   ADB1                    1411 00106$:
                           1412 ;fuel.c:149: BIT_CLEAR(currentStatus.engineStatus, ENGINE_ACC);
   ADB1 A4 EF         [ 2] 1413 	and	#0xef
   ADB3 C7 00 89      [ 4] 1414 	sta	(_currentStatus + 0x002a)
                           1415 ;fuel.c:150: return 0;
   ADB6 4F            [ 1] 1416 	clra
   ADB7                    1417 00107$:
                           1418 ;fuel.c:151: }
   ADB7 A7 03         [ 2] 1419 	ais	#3
   ADB9 81            [ 4] 1420 	rts
                           1421 ;------------------------------------------------------------
                           1422 ;Allocation info for local variables in function 'correctionCLT'
                           1423 ;------------------------------------------------------------
                           1424 ;reduction                 Allocated to registers a 
                           1425 ;------------------------------------------------------------
                           1426 ;fuel.c:153: uint8_t correctionCLT(void) {
                           1427 ;	-----------------------------------------
                           1428 ;	 function correctionCLT
                           1429 ;	-----------------------------------------
                           1430 ;	Register assignment is optimal.
                           1431 ;	Stack space usage: 0 bytes.
   ADBA                    1432 _correctionCLT:
                           1433 ;fuel.c:154: if (currentStatus.coolant > 100) {
   ADBA C6 00 74      [ 4] 1434 	lda	(_currentStatus + 0x0015)
   ADBD A1 64         [ 2] 1435 	cmp	#0x64
   ADBF 93 20         [ 3] 1436 	ble	00104$
                           1437 ;fuel.c:155: int8_t reduction = (int8_t)((currentStatus.coolant - 100) / 5);
   ADC1 97            [ 1] 1438 	tax
   ADC2 49            [ 1] 1439 	rola	
   ADC3 4F            [ 1] 1440 	clra	
   ADC4 A2 00         [ 2] 1441 	sbc	#0x00
   ADC6 87            [ 2] 1442 	psha
   ADC7 8A            [ 2] 1443 	pulh
   ADC8 AF 9C         [ 2] 1444 	aix	#-100
   ADCA A6 05         [ 2] 1445 	lda	#0x05
   ADCC 87            [ 2] 1446 	psha
   ADCD 4F            [ 1] 1447 	clra
   ADCE 87            [ 2] 1448 	psha
   ADCF 9F            [ 1] 1449 	txa
   ADD0 8B            [ 2] 1450 	pshh
   ADD1 88            [ 2] 1451 	pulx
   ADD2 CD D1 D3      [ 5] 1452 	jsr	__divsint
   ADD5 A7 02         [ 2] 1453 	ais	#2
                           1454 ;fuel.c:156: if (reduction > 5) reduction = 5;
   ADD7 A1 05         [ 2] 1455 	cmp	#0x05
   ADD9 93 02         [ 3] 1456 	ble	00102$
   ADDB A6 05         [ 2] 1457 	lda	#0x05
   ADDD                    1458 00102$:
                           1459 ;fuel.c:157: return (uint8_t)(100 - reduction);
   ADDD A0 64         [ 2] 1460 	sub	#0x64
   ADDF 40            [ 1] 1461 	nega	
   ADE0 81            [ 4] 1462 	rts
   ADE1                    1463 00104$:
                           1464 ;fuel.c:159: return 100;
   ADE1 A6 64         [ 2] 1465 	lda	#0x64
                           1466 ;fuel.c:160: }
   ADE3 81            [ 4] 1467 	rts
                           1468 ;------------------------------------------------------------
                           1469 ;Allocation info for local variables in function 'correctionBattery'
                           1470 ;------------------------------------------------------------
                           1471 ;voltage                   Allocated to registers a 
                           1472 ;------------------------------------------------------------
                           1473 ;fuel.c:162: uint8_t correctionBattery(void) {
                           1474 ;	-----------------------------------------
                           1475 ;	 function correctionBattery
                           1476 ;	-----------------------------------------
                           1477 ;	Register assignment is optimal.
                           1478 ;	Stack space usage: 0 bytes.
   ADE4                    1479 _correctionBattery:
                           1480 ;fuel.c:163: uint8_t voltage = currentStatus.battery10;
   ADE4 C6 00 78      [ 4] 1481 	lda	(_currentStatus + 0x0019)
                           1482 ;fuel.c:165: if (voltage < 110) {
   ADE7 A1 6E         [ 2] 1483 	cmp	#0x6e
   ADE9 24 03         [ 3] 1484 	bcc	00107$
                           1485 ;fuel.c:166: return 110;
   ADEB A6 6E         [ 2] 1486 	lda	#0x6e
   ADED 81            [ 4] 1487 	rts
   ADEE                    1488 00107$:
                           1489 ;fuel.c:167: } else if (voltage < 120) {
   ADEE A1 78         [ 2] 1490 	cmp	#0x78
   ADF0 24 03         [ 3] 1491 	bcc	00104$
                           1492 ;fuel.c:168: return 105;
   ADF2 A6 69         [ 2] 1493 	lda	#0x69
   ADF4 81            [ 4] 1494 	rts
   ADF5                    1495 00104$:
                           1496 ;fuel.c:169: } else if (voltage > 150) {
   ADF5 A1 96         [ 2] 1497 	cmp	#0x96
   ADF7 23 03         [ 3] 1498 	bls	00108$
                           1499 ;fuel.c:170: return 97;
   ADF9 A6 61         [ 2] 1500 	lda	#0x61
   ADFB 81            [ 4] 1501 	rts
   ADFC                    1502 00108$:
                           1503 ;fuel.c:172: return 100;
   ADFC A6 64         [ 2] 1504 	lda	#0x64
                           1505 ;fuel.c:173: }
   ADFE 81            [ 4] 1506 	rts
                           1507 ;------------------------------------------------------------
                           1508 ;Allocation info for local variables in function 'updateEngineStatus'
                           1509 ;------------------------------------------------------------
                           1510 ;sloc0                     Allocated to stack - sp +1
                           1511 ;firstRun                  Allocated with name '_updateEngineStatus_firstRun_65536_62'
                           1512 ;------------------------------------------------------------
                           1513 ;fuel.c:175: void updateEngineStatus(void) {
                           1514 ;	-----------------------------------------
                           1515 ;	 function updateEngineStatus
                           1516 ;	-----------------------------------------
                           1517 ;	Register assignment is optimal.
                           1518 ;	Stack space usage: 2 bytes.
   ADFF                    1519 _updateEngineStatus:
   ADFF A7 FE         [ 2] 1520 	ais	#-2
                           1521 ;fuel.c:178: if (currentStatus.RPM > 0 && currentStatus.RPM < ((uint16_t)configPage1.crankRPM * 10)) {
   AE01 CE 00 5F      [ 4] 1522 	ldx	_currentStatus
   AE04 C6 00 60      [ 4] 1523 	lda	(_currentStatus + 1)
   AE07 9E E7 02      [ 4] 1524 	sta	2,s
   AE0A 9E EF 01      [ 4] 1525 	stx	1,s
   AE0D 4D            [ 1] 1526 	tsta
   AE0E 26 01         [ 3] 1527 	bne	00140$
   AE10 5D            [ 1] 1528 	tstx
   AE11                    1529 00140$:
   AE11 27 2F         [ 3] 1530 	beq	00107$
   AE13 C6 00 B9      [ 4] 1531 	lda	(_configPage1 + 0x001d)
   AE16 5F            [ 1] 1532 	clrx
   AE17 87            [ 2] 1533 	psha
   AE18 89            [ 2] 1534 	pshx
   AE19 A6 0A         [ 2] 1535 	lda	#0x0a
   AE1B CD CE 65      [ 5] 1536 	jsr	__mulint
   AE1E A7 02         [ 2] 1537 	ais	#2
   AE20 87            [ 2] 1538 	psha
   AE21 9E E6 03      [ 4] 1539 	lda	3,s
   AE24 9E E0 01      [ 4] 1540 	sub	1, s
   AE27 86            [ 2] 1541 	pula
   AE28 9E E6 01      [ 4] 1542 	lda	1,s
   AE2B 89            [ 2] 1543 	pshx
   AE2C 9E E2 01      [ 4] 1544 	sbc	1,s
   AE2F A7 01         [ 2] 1545 	ais	#1
   AE31 24 0F         [ 3] 1546 	bcc	00107$
                           1547 ;fuel.c:179: BIT_SET(currentStatus.engineStatus, ENGINE_CRANK);
   AE33 C6 00 89      [ 4] 1548 	lda	(_currentStatus + 0x002a)
   AE36 AA 01         [ 2] 1549 	ora	#0x01
   AE38 C7 00 89      [ 4] 1550 	sta	(_currentStatus + 0x002a)
                           1551 ;fuel.c:180: BIT_CLEAR(currentStatus.engineStatus, ENGINE_RUN);
   AE3B A4 FD         [ 2] 1552 	and	#0xfd
   AE3D C7 00 89      [ 4] 1553 	sta	(_currentStatus + 0x002a)
   AE40 20 48         [ 3] 1554 	bra	00108$
   AE42                    1555 00107$:
                           1556 ;fuel.c:181: } else if (currentStatus.RPM >= ((uint16_t)configPage1.crankRPM * 10)) {
   AE42 C6 00 B9      [ 4] 1557 	lda	(_configPage1 + 0x001d)
   AE45 5F            [ 1] 1558 	clrx
   AE46 87            [ 2] 1559 	psha
   AE47 89            [ 2] 1560 	pshx
   AE48 A6 0A         [ 2] 1561 	lda	#0x0a
   AE4A CD CE 65      [ 5] 1562 	jsr	__mulint
   AE4D A7 02         [ 2] 1563 	ais	#2
   AE4F 87            [ 2] 1564 	psha
   AE50 9E E6 03      [ 4] 1565 	lda	3,s
   AE53 9E E0 01      [ 4] 1566 	sub	1, s
   AE56 86            [ 2] 1567 	pula
   AE57 9E E6 01      [ 4] 1568 	lda	1,s
   AE5A 89            [ 2] 1569 	pshx
   AE5B 9E E2 01      [ 4] 1570 	sbc	1,s
   AE5E A7 01         [ 2] 1571 	ais	#1
   AE60 25 1B         [ 3] 1572 	bcs	00104$
                           1573 ;fuel.c:182: BIT_CLEAR(currentStatus.engineStatus, ENGINE_CRANK);
   AE62 C6 00 89      [ 4] 1574 	lda	(_currentStatus + 0x002a)
   AE65 A4 FE         [ 2] 1575 	and	#0xfe
   AE67 C7 00 89      [ 4] 1576 	sta	(_currentStatus + 0x002a)
                           1577 ;fuel.c:183: BIT_SET(currentStatus.engineStatus, ENGINE_RUN);
   AE6A AA 02         [ 2] 1578 	ora	#0x02
   AE6C C7 00 89      [ 4] 1579 	sta	(_currentStatus + 0x002a)
                           1580 ;fuel.c:185: if (firstRun) {
   AE6F C6 01 75      [ 4] 1581 	lda	_updateEngineStatus_firstRun_65536_62
   AE72 27 16         [ 3] 1582 	beq	00108$
                           1583 ;fuel.c:186: startASE();
   AE74 CD AC DF      [ 5] 1584 	jsr	_startASE
                           1585 ;fuel.c:187: firstRun = false;
   AE77 4F            [ 1] 1586 	clra
   AE78 C7 01 75      [ 4] 1587 	sta	_updateEngineStatus_firstRun_65536_62
   AE7B 20 0D         [ 3] 1588 	bra	00108$
   AE7D                    1589 00104$:
                           1590 ;fuel.c:190: BIT_CLEAR(currentStatus.engineStatus, ENGINE_CRANK);
   AE7D C6 00 89      [ 4] 1591 	lda	(_currentStatus + 0x002a)
   AE80 A4 FE         [ 2] 1592 	and	#0xfe
   AE82 C7 00 89      [ 4] 1593 	sta	(_currentStatus + 0x002a)
                           1594 ;fuel.c:191: BIT_CLEAR(currentStatus.engineStatus, ENGINE_RUN);
   AE85 A4 FD         [ 2] 1595 	and	#0xfd
   AE87 C7 00 89      [ 4] 1596 	sta	(_currentStatus + 0x002a)
   AE8A                    1597 00108$:
                           1598 ;fuel.c:194: if (currentStatus.coolant < 60) {
   AE8A CE 00 74      [ 4] 1599 	ldx	(_currentStatus + 0x0015)
                           1600 ;fuel.c:195: BIT_SET(currentStatus.engineStatus, ENGINE_WARMUP);
   AE8D C6 00 89      [ 4] 1601 	lda	(_currentStatus + 0x002a)
                           1602 ;fuel.c:194: if (currentStatus.coolant < 60) {
   AE90 A3 3C         [ 2] 1603 	cpx	#0x3c
   AE92 90 07         [ 3] 1604 	bge	00111$
                           1605 ;fuel.c:195: BIT_SET(currentStatus.engineStatus, ENGINE_WARMUP);
   AE94 AA 08         [ 2] 1606 	ora	#0x08
   AE96 C7 00 89      [ 4] 1607 	sta	(_currentStatus + 0x002a)
   AE99 20 05         [ 3] 1608 	bra	00113$
   AE9B                    1609 00111$:
                           1610 ;fuel.c:197: BIT_CLEAR(currentStatus.engineStatus, ENGINE_WARMUP);
   AE9B A4 F7         [ 2] 1611 	and	#0xf7
   AE9D C7 00 89      [ 4] 1612 	sta	(_currentStatus + 0x002a)
   AEA0                    1613 00113$:
                           1614 ;fuel.c:199: }
   AEA0 A7 02         [ 2] 1615 	ais	#2
   AEA2 81            [ 4] 1616 	rts
                           1617 	.area CSEG    (CODE)
                           1618 	.area CONST   (CODE)
                           1619 	.area XINIT   (CODE)
   D24D                    1620 __xinit__aseCounter:
   D24D 00                 1621 	.db #0x00	; 0
   D24E                    1622 __xinit__aseValue:
   D24E 64                 1623 	.db #0x64	; 100	'd'
                           1624 	.area CABS    (ABS,CODE)
