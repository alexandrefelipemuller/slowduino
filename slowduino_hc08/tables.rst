                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 4.2.0 #13081 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module tables
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
                             22 	.globl _eepromReadI8
                             23 	.globl _eepromReadByte
                             24 	.globl _ignTable
                             25 	.globl _veTable
                             26 	.globl _initTables
                             27 	.globl _getTableValue
                             28 	.globl _findTableXIndices
                             29 	.globl _findTableYIndices
                             30 	.globl _lookupCurveU8
                             31 	.globl _lookupCurveI8
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
   0127                      56 _veTable::
   0127                      57 	.ds 39
   014E                      58 _ignTable::
   014E                      59 	.ds 39
                             60 ;--------------------------------------------------------
                             61 ; global & static initialisations
                             62 ;--------------------------------------------------------
                             63 	.area HOME    (CODE)
                             64 	.area GSINIT  (CODE)
                             65 	.area GSFINAL (CODE)
                             66 	.area GSINIT  (CODE)
                             67 ;--------------------------------------------------------
                             68 ; Home
                             69 ;--------------------------------------------------------
                             70 	.area HOME    (CODE)
                             71 	.area HOME    (CODE)
                             72 ;--------------------------------------------------------
                             73 ; code
                             74 ;--------------------------------------------------------
                             75 	.area CSEG    (CODE)
                             76 ;------------------------------------------------------------
                             77 ;Allocation info for local variables in function 'interpolate'
                             78 ;------------------------------------------------------------
                             79 ;x1                        Allocated to stack - sp +11
                             80 ;x2                        Allocated to stack - sp +13
                             81 ;y1                        Allocated to stack - sp +15
                             82 ;y2                        Allocated to stack - sp +17
                             83 ;x                         Allocated to registers a x 
                             84 ;sloc0                     Allocated to stack - sp +1
                             85 ;sloc1                     Allocated to stack - sp +5
                             86 ;------------------------------------------------------------
                             87 ;tables.h:33: static inline int16_t interpolate(int16_t x, int16_t x1, int16_t x2, int16_t y1, int16_t y2) {
                             88 ;	-----------------------------------------
                             89 ;	 function interpolate
                             90 ;	-----------------------------------------
                             91 ;	Register assignment might be sub-optimal.
                             92 ;	Stack space usage: 8 bytes.
   9773                      93 _interpolate:
   9773 A7 F8         [ 2]   94 	ais	#-8
                             95 ;tables.h:34: if (x2 == x1) return y1;
   9775 87            [ 2]   96 	psha
   9776 9E E6 0F      [ 4]   97 	lda	15,s
   9779 9E E1 0D      [ 4]   98 	cmp	13,s
   977C 86            [ 2]   99 	pula
   977D 26 0A         [ 3]  100 	bne	00110$
   977F 87            [ 2]  101 	psha
   9780 9E E6 0E      [ 4]  102 	lda	14,s
   9783 9E E1 0C      [ 4]  103 	cmp	12,s
   9786 86            [ 2]  104 	pula
   9787 27 02         [ 3]  105 	beq	00111$
   9789                     106 00110$:
   9789 20 09         [ 3]  107 	bra	00102$
   978B                     108 00111$:
   978B 95            [ 2]  109 	tsx
   978C EE 0E         [ 3]  110 	ldx	14,x
   978E 9E E6 10      [ 4]  111 	lda	16,s
   9791 CC 98 59      [ 3]  112 	jmp	00103$
   9794                     113 00102$:
                            114 ;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
   9794 9E E0 0C      [ 4]  115 	sub	12,s
   9797 87            [ 2]  116 	psha
   9798 9F            [ 1]  117 	txa
   9799 9E E2 0C      [ 4]  118 	sbc	12,s
   979C 97            [ 1]  119 	tax
   979D 86            [ 2]  120 	pula
   979E 9E E7 04      [ 4]  121 	sta	4,s
   97A1 9F            [ 1]  122 	txa
   97A2 9E E7 03      [ 4]  123 	sta	3,s
   97A5 49            [ 1]  124 	rola	
   97A6 4F            [ 1]  125 	clra	
   97A7 A2 00         [ 2]  126 	sbc	#0x00
   97A9 9E E7 02      [ 4]  127 	sta	2,s
   97AC 9E E7 01      [ 4]  128 	sta	1,s
   97AF 9E E6 12      [ 4]  129 	lda	18,s
   97B2 9E E0 10      [ 4]  130 	sub	16,s
   97B5 87            [ 2]  131 	psha
   97B6 9E E6 12      [ 4]  132 	lda	18,s
   97B9 9E E2 10      [ 4]  133 	sbc	16,s
   97BC 97            [ 1]  134 	tax
   97BD 86            [ 2]  135 	pula
   97BE 9E E7 08      [ 4]  136 	sta	8,s
   97C1 9F            [ 1]  137 	txa
   97C2 9E E7 07      [ 4]  138 	sta	7,s
   97C5 49            [ 1]  139 	rola	
   97C6 4F            [ 1]  140 	clra	
   97C7 A2 00         [ 2]  141 	sbc	#0x00
   97C9 9E E7 06      [ 4]  142 	sta	6,s
   97CC 9E E7 05      [ 4]  143 	sta	5,s
   97CF 95            [ 2]  144 	tsx
   97D0 E6 07         [ 3]  145 	lda	7,x
   97D2 87            [ 2]  146 	psha
   97D3 E6 06         [ 3]  147 	lda	6,x
   97D5 87            [ 2]  148 	psha
   97D6 E6 05         [ 3]  149 	lda	5,x
   97D8 87            [ 2]  150 	psha
   97D9 E6 04         [ 3]  151 	lda	4,x
   97DB 87            [ 2]  152 	psha
   97DC E6 03         [ 3]  153 	lda	3,x
   97DE 87            [ 2]  154 	psha
   97DF E6 02         [ 3]  155 	lda	2,x
   97E1 87            [ 2]  156 	psha
   97E2 E6 01         [ 3]  157 	lda	1,x
   97E4 87            [ 2]  158 	psha
   97E5 F6            [ 2]  159 	lda	,x
   97E6 87            [ 2]  160 	psha
   97E7 CD D0 87      [ 5]  161 	jsr	__mullong
   97EA 9E E7 10      [ 4]  162 	sta	16,s
   97ED 9E EF 0F      [ 4]  163 	stx	15,s
   97F0 B6 4A         [ 3]  164 	lda	*___SDCC_hc08_ret2
   97F2 9E E7 0E      [ 4]  165 	sta	14,s
   97F5 B6 4B         [ 3]  166 	lda	*___SDCC_hc08_ret3
   97F7 9E E7 0D      [ 4]  167 	sta	13,s
   97FA A7 08         [ 2]  168 	ais	#8
   97FC 9E E6 0E      [ 4]  169 	lda	14,s
   97FF 9E E0 0C      [ 4]  170 	sub	12,s
   9802 87            [ 2]  171 	psha
   9803 9E E6 0E      [ 4]  172 	lda	14,s
   9806 9E E2 0C      [ 4]  173 	sbc	12,s
   9809 97            [ 1]  174 	tax
   980A 86            [ 2]  175 	pula
   980B 9E E7 04      [ 4]  176 	sta	4,s
   980E 9F            [ 1]  177 	txa
   980F 9E E7 03      [ 4]  178 	sta	3,s
   9812 49            [ 1]  179 	rola	
   9813 4F            [ 1]  180 	clra	
   9814 A2 00         [ 2]  181 	sbc	#0x00
   9816 9E E7 02      [ 4]  182 	sta	2,s
   9819 9E E7 01      [ 4]  183 	sta	1,s
   981C 95            [ 2]  184 	tsx
   981D E6 03         [ 3]  185 	lda	3,x
   981F 87            [ 2]  186 	psha
   9820 E6 02         [ 3]  187 	lda	2,x
   9822 87            [ 2]  188 	psha
   9823 E6 01         [ 3]  189 	lda	1,x
   9825 87            [ 2]  190 	psha
   9826 F6            [ 2]  191 	lda	,x
   9827 87            [ 2]  192 	psha
   9828 E6 07         [ 3]  193 	lda	7,x
   982A 87            [ 2]  194 	psha
   982B E6 06         [ 3]  195 	lda	6,x
   982D 87            [ 2]  196 	psha
   982E E6 05         [ 3]  197 	lda	5,x
   9830 87            [ 2]  198 	psha
   9831 E6 04         [ 3]  199 	lda	4,x
   9833 87            [ 2]  200 	psha
   9834 CD CE 92      [ 5]  201 	jsr	__divslong
   9837 9E E7 10      [ 4]  202 	sta	16,s
   983A 9E EF 0F      [ 4]  203 	stx	15,s
   983D B6 4A         [ 3]  204 	lda	*___SDCC_hc08_ret2
   983F 9E E7 0E      [ 4]  205 	sta	14,s
   9842 B6 4B         [ 3]  206 	lda	*___SDCC_hc08_ret3
   9844 9E E7 0D      [ 4]  207 	sta	13,s
   9847 A7 08         [ 2]  208 	ais	#8
   9849 9E E6 08      [ 4]  209 	lda	8,s
   984C 9E EE 07      [ 4]  210 	ldx	7,s
   984F 9E EB 10      [ 4]  211 	add	16,s
   9852 87            [ 2]  212 	psha
   9853 9F            [ 1]  213 	txa
   9854 9E E9 10      [ 4]  214 	adc	16,s
   9857 97            [ 1]  215 	tax
   9858 86            [ 2]  216 	pula
   9859                     217 00103$:
                            218 ;tables.h:36: }
   9859 A7 08         [ 2]  219 	ais	#8
   985B 81            [ 4]  220 	rts
                            221 ;------------------------------------------------------------
                            222 ;Allocation info for local variables in function 'initTables'
                            223 ;------------------------------------------------------------
                            224 ;tables.c:17: void initTables(void) {
                            225 ;	-----------------------------------------
                            226 ;	 function initTables
                            227 ;	-----------------------------------------
                            228 ;	Register assignment is optimal.
                            229 ;	Stack space usage: 0 bytes.
   985C                     230 _initTables:
                            231 ;tables.c:18: veTable.isSigned = false;
   985C 4F            [ 1]  232 	clra
   985D C7 01 4D      [ 4]  233 	sta	(_veTable + 0x0026)
                            234 ;tables.c:19: ignTable.isSigned = true;
   9860 4C            [ 1]  235 	inca
   9861 C7 01 74      [ 4]  236 	sta	(_ignTable + 0x0026)
                            237 ;tables.c:20: veTable.eepromValuesBase = EEPROM_VE_TABLE;
   9864 4A            [ 1]  238 	deca
   9865 C7 01 4B      [ 4]  239 	sta	(_veTable + 0x0024)
   9868 C7 01 4C      [ 4]  240 	sta	((_veTable + 0x0024) + 1)
                            241 ;tables.c:21: ignTable.eepromValuesBase = EEPROM_IGN_TABLE;
   986B C7 01 72      [ 4]  242 	sta	(_ignTable + 0x0024)
   986E A6 90         [ 2]  243 	lda	#0x90
   9870 C7 01 73      [ 4]  244 	sta	((_ignTable + 0x0024) + 1)
                            245 ;tables.c:22: }
   9873 81            [ 4]  246 	rts
                            247 ;------------------------------------------------------------
                            248 ;Allocation info for local variables in function 'readTableCell'
                            249 ;------------------------------------------------------------
                            250 ;y                         Allocated to stack - sp +9
                            251 ;x                         Allocated to stack - sp +10
                            252 ;table                     Allocated to stack - sp +5
                            253 ;addr                      Allocated to registers a x 
                            254 ;sloc0                     Allocated to stack - sp +3
                            255 ;sloc1                     Allocated to stack - sp +1
                            256 ;------------------------------------------------------------
                            257 ;tables.c:24: static int16_t readTableCell(const struct Table3D *table, uint8_t y, uint8_t x) {
                            258 ;	-----------------------------------------
                            259 ;	 function readTableCell
                            260 ;	-----------------------------------------
                            261 ;	Register assignment is optimal.
                            262 ;	Stack space usage: 6 bytes.
   9874                     263 _readTableCell:
   9874 87            [ 2]  264 	psha
   9875 89            [ 2]  265 	pshx
   9876 A7 FC         [ 2]  266 	ais	#-4
                            267 ;tables.c:25: uint16_t addr = table->eepromValuesBase + ((uint16_t)y * TABLE_SIZE_X) + x;
   9878 95            [ 2]  268 	tsx
   9879 E6 04         [ 3]  269 	lda	4,x
   987B E7 02         [ 3]  270 	sta	2,x
   987D E6 05         [ 3]  271 	lda	5,x
   987F E7 03         [ 3]  272 	sta	3,x
   9881 E6 02         [ 3]  273 	lda	2,x
   9883 87            [ 2]  274 	psha
   9884 8A            [ 2]  275 	pulh
   9885 9E EE 04      [ 4]  276 	ldx	4,s
   9888 E6 24         [ 3]  277 	lda	36,x
   988A 9E E7 03      [ 4]  278 	sta	3,s
   988D E6 25         [ 3]  279 	lda	37,x
   988F 9E E7 04      [ 4]  280 	sta	4,s
   9892 9E E6 09      [ 4]  281 	lda	9,s
   9895 5F            [ 1]  282 	clrx
   9896 87            [ 2]  283 	psha
   9897 89            [ 2]  284 	pshx
   9898 A6 0C         [ 2]  285 	lda	#0x0c
   989A CD CE 65      [ 5]  286 	jsr	__mulint
   989D 9E E7 04      [ 4]  287 	sta	4,s
   98A0 9E EF 03      [ 4]  288 	stx	3,s
   98A3 A7 02         [ 2]  289 	ais	#2
   98A5 9E E6 04      [ 4]  290 	lda	4,s
   98A8 9E EE 03      [ 4]  291 	ldx	3,s
   98AB 9E EB 02      [ 4]  292 	add	2,s
   98AE 9E E7 02      [ 4]  293 	sta	2,s
   98B1 9F            [ 1]  294 	txa
   98B2 9E E9 01      [ 4]  295 	adc	1,s
   98B5 9E E7 01      [ 4]  296 	sta	1,s
   98B8 9E E6 0A      [ 4]  297 	lda	10,s
   98BB 5F            [ 1]  298 	clrx
   98BC 9E EB 02      [ 4]  299 	add	2,s
   98BF 87            [ 2]  300 	psha
   98C0 9F            [ 1]  301 	txa
   98C1 9E E9 02      [ 4]  302 	adc	2,s
   98C4 97            [ 1]  303 	tax
                            304 ;tables.c:26: return table->isSigned ? (int16_t)eepromReadI8(addr) : (int16_t)eepromReadByte(addr);
   98C5 9E E6 06      [ 4]  305 	lda	6,s
   98C8 9E E7 02      [ 4]  306 	sta	2,s
   98CB 9E E6 07      [ 4]  307 	lda	7,s
   98CE 9E E7 03      [ 4]  308 	sta	3,s
   98D1 86            [ 2]  309 	pula
   98D2 89            [ 2]  310 	pshx
   98D3 9E EE 02      [ 4]  311 	ldx	2,s
   98D6 89            [ 2]  312 	pshx
   98D7 8A            [ 2]  313 	pulh
   98D8 9E EE 03      [ 4]  314 	ldx	3,s
   98DB 87            [ 2]  315 	psha
   98DC E6 26         [ 3]  316 	lda	38,x
   98DE 86            [ 2]  317 	pula
   98DF 88            [ 2]  318 	pulx
   98E0 27 0C         [ 3]  319 	beq	00103$
   98E2 CD 97 6D      [ 5]  320 	jsr	_eepromReadI8
   98E5 87            [ 2]  321 	psha
   98E6 49            [ 1]  322 	rola	
   98E7 4F            [ 1]  323 	clra	
   98E8 A2 00         [ 2]  324 	sbc	#0x00
   98EA 97            [ 1]  325 	tax
   98EB 86            [ 2]  326 	pula
   98EC 20 04         [ 3]  327 	bra	00104$
   98EE                     328 00103$:
   98EE CD 97 6A      [ 5]  329 	jsr	_eepromReadByte
   98F1 5F            [ 1]  330 	clrx
   98F2                     331 00104$:
                            332 ;tables.c:27: }
   98F2 A7 06         [ 2]  333 	ais	#6
   98F4 81            [ 4]  334 	rts
                            335 ;------------------------------------------------------------
                            336 ;Allocation info for local variables in function 'getTableValue'
                            337 ;------------------------------------------------------------
                            338 ;valueY                    Allocated to stack - sp +81
                            339 ;valueX                    Allocated to stack - sp +82
                            340 ;table                     Allocated to stack - sp +62
                            341 ;xLow                      Allocated to stack - sp +3
                            342 ;xHigh                     Allocated to stack - sp +2
                            343 ;yLow                      Allocated to stack - sp +1
                            344 ;yHigh                     Allocated to stack - sp +4
                            345 ;q11                       Allocated to stack - sp +77
                            346 ;q21                       Allocated to stack - sp +75
                            347 ;q12                       Allocated to stack - sp +73
                            348 ;q22                       Allocated to stack - sp +71
                            349 ;x1                        Allocated to stack - sp +69
                            350 ;x2                        Allocated to stack - sp +67
                            351 ;y1                        Allocated to stack - sp +66
                            352 ;y2                        Allocated to registers x 
                            353 ;result                    Allocated to stack - sp +64
                            354 ;__1966080001              Allocated to stack - sp +11
                            355 ;__1966080002              Allocated to stack - sp +58
                            356 ;__1966080003              Allocated to stack - sp +56
                            357 ;__1966080004              Allocated to stack - sp +54
                            358 ;__1966080005              Allocated to registers 
                            359 ;__1966080006              Allocated to registers 
                            360 ;x                         Allocated to registers 
                            361 ;x1                        Allocated to registers 
                            362 ;x2                        Allocated to registers 
                            363 ;y1                        Allocated to registers 
                            364 ;y2                        Allocated to registers 
                            365 ;__1966080008              Allocated to stack - sp +20
                            366 ;__1966080009              Allocated to stack - sp +52
                            367 ;__1966080010              Allocated to stack - sp +50
                            368 ;__1966080011              Allocated to stack - sp +48
                            369 ;__1966080012              Allocated to registers 
                            370 ;__1966080013              Allocated to registers 
                            371 ;x                         Allocated to registers 
                            372 ;x1                        Allocated to registers 
                            373 ;x2                        Allocated to registers 
                            374 ;y1                        Allocated to registers 
                            375 ;y2                        Allocated to registers 
                            376 ;__1966080029              Allocated to stack - sp +34
                            377 ;__1966080022              Allocated to stack - sp +22
                            378 ;__1966080015              Allocated to stack - sp +34
                            379 ;r1                        Allocated to stack - sp +60
                            380 ;r2                        Allocated to registers 
                            381 ;__1966080016              Allocated to stack - sp +20
                            382 ;__1966080017              Allocated to stack - sp +26
                            383 ;__1966080018              Allocated to stack - sp +36
                            384 ;__1966080019              Allocated to registers 
                            385 ;__1966080020              Allocated to registers 
                            386 ;x                         Allocated to registers 
                            387 ;x1                        Allocated to registers 
                            388 ;x2                        Allocated to registers 
                            389 ;y1                        Allocated to registers 
                            390 ;y2                        Allocated to registers 
                            391 ;__1966080023              Allocated to registers 
                            392 ;__1966080024              Allocated to registers 
                            393 ;__1966080025              Allocated to registers 
                            394 ;__1966080026              Allocated to registers 
                            395 ;__1966080027              Allocated to registers 
                            396 ;x                         Allocated to registers 
                            397 ;x1                        Allocated to registers 
                            398 ;x2                        Allocated to registers 
                            399 ;y1                        Allocated to registers 
                            400 ;y2                        Allocated to registers 
                            401 ;__1966080030              Allocated to stack - sp +46
                            402 ;__1966080031              Allocated to stack - sp +44
                            403 ;__1966080032              Allocated to stack - sp +42
                            404 ;__1966080033              Allocated to registers 
                            405 ;__1966080034              Allocated to registers 
                            406 ;x                         Allocated to registers 
                            407 ;x1                        Allocated to registers 
                            408 ;x2                        Allocated to registers 
                            409 ;y1                        Allocated to registers 
                            410 ;y2                        Allocated to registers 
                            411 ;sloc0                     Allocated to stack - sp +11
                            412 ;sloc1                     Allocated to stack - sp +40
                            413 ;sloc2                     Allocated to stack - sp +13
                            414 ;sloc3                     Allocated to stack - sp +9
                            415 ;sloc4                     Allocated to stack - sp +18
                            416 ;sloc5                     Allocated to stack - sp +14
                            417 ;sloc6                     Allocated to stack - sp +30
                            418 ;sloc7                     Allocated to stack - sp +5
                            419 ;sloc8                     Allocated to stack - sp +20
                            420 ;sloc9                     Allocated to stack - sp +26
                            421 ;sloc10                    Allocated to stack - sp +36
                            422 ;sloc11                    Allocated to stack - sp +34
                            423 ;sloc12                    Allocated to stack - sp +22
                            424 ;------------------------------------------------------------
                            425 ;tables.c:29: int16_t getTableValue(struct Table3D *table, uint8_t valueY, uint16_t valueX) {
                            426 ;	-----------------------------------------
                            427 ;	 function getTableValue
                            428 ;	-----------------------------------------
                            429 ;	Register assignment might be sub-optimal.
                            430 ;	Stack space usage: 78 bytes.
   98F5                     431 _getTableValue:
   98F5 A7 B2         [ 2]  432 	ais	#-78
   98F7 9E E7 3F      [ 4]  433 	sta	63,s
   98FA 9E EF 3E      [ 4]  434 	stx	62,s
                            435 ;tables.c:36: findTableXIndices(table, valueX, &xLow, &xHigh);
   98FD 95            [ 2]  436 	tsx
   98FE AF 01         [ 2]  437 	aix	#1
   9900 9E EF 0C      [ 4]  438 	stx	12,s
   9903 8B            [ 2]  439 	pshh
   9904 86            [ 2]  440 	pula
   9905 9E E7 0B      [ 4]  441 	sta	11,s
   9908 95            [ 2]  442 	tsx
   9909 AF 02         [ 2]  443 	aix	#2
   990B 9E E6 0C      [ 4]  444 	lda	12,s
   990E 87            [ 2]  445 	psha
   990F 9E E6 0C      [ 4]  446 	lda	12,s
   9912 87            [ 2]  447 	psha
   9913 89            [ 2]  448 	pshx
   9914 8B            [ 2]  449 	pshh
   9915 95            [ 2]  450 	tsx
   9916 E6 56         [ 3]  451 	lda	86,x
   9918 87            [ 2]  452 	psha
   9919 E6 55         [ 3]  453 	lda	85,x
   991B 87            [ 2]  454 	psha
   991C E6 42         [ 3]  455 	lda	66,x
   991E EE 41         [ 3]  456 	ldx	65,x
   9920 CD 9F 6F      [ 5]  457 	jsr	_findTableXIndices
   9923 A7 06         [ 2]  458 	ais	#6
                            459 ;tables.c:37: findTableYIndices(table, valueY, &yLow, &yHigh);
   9925 95            [ 2]  460 	tsx
   9926 AF 03         [ 2]  461 	aix	#3
   9928 9E EF 0C      [ 4]  462 	stx	12,s
   992B 8B            [ 2]  463 	pshh
   992C 86            [ 2]  464 	pula
   992D 9E E7 0B      [ 4]  465 	sta	11,s
   9930 95            [ 2]  466 	tsx
   9931 9E E6 0C      [ 4]  467 	lda	12,s
   9934 87            [ 2]  468 	psha
   9935 9E E6 0C      [ 4]  469 	lda	12,s
   9938 87            [ 2]  470 	psha
   9939 89            [ 2]  471 	pshx
   993A 8B            [ 2]  472 	pshh
   993B 95            [ 2]  473 	tsx
   993C E6 54         [ 3]  474 	lda	84,x
   993E 87            [ 2]  475 	psha
   993F E6 42         [ 3]  476 	lda	66,x
   9941 EE 41         [ 3]  477 	ldx	65,x
   9943 CD A0 8A      [ 5]  478 	jsr	_findTableYIndices
   9946 A7 05         [ 2]  479 	ais	#5
                            480 ;tables.c:39: q11 = readTableCell(table, yLow, xLow);
   9948 95            [ 2]  481 	tsx
   9949 E6 02         [ 3]  482 	lda	2,x
   994B 87            [ 2]  483 	psha
   994C F6            [ 2]  484 	lda	,x
   994D 87            [ 2]  485 	psha
   994E E6 3E         [ 3]  486 	lda	62,x
   9950 EE 3D         [ 3]  487 	ldx	61,x
   9952 CD 98 74      [ 5]  488 	jsr	_readTableCell
   9955 9E E7 50      [ 4]  489 	sta	80,s
   9958 9E EF 4F      [ 4]  490 	stx	79,s
   995B A7 02         [ 2]  491 	ais	#2
                            492 ;tables.c:40: q21 = readTableCell(table, yLow, xHigh);
   995D 95            [ 2]  493 	tsx
   995E E6 01         [ 3]  494 	lda	1,x
   9960 87            [ 2]  495 	psha
   9961 F6            [ 2]  496 	lda	,x
   9962 87            [ 2]  497 	psha
   9963 E6 3E         [ 3]  498 	lda	62,x
   9965 EE 3D         [ 3]  499 	ldx	61,x
   9967 CD 98 74      [ 5]  500 	jsr	_readTableCell
   996A 9E E7 4E      [ 4]  501 	sta	78,s
   996D 9E EF 4D      [ 4]  502 	stx	77,s
   9970 A7 02         [ 2]  503 	ais	#2
                            504 ;tables.c:41: q12 = readTableCell(table, yHigh, xLow);
   9972 95            [ 2]  505 	tsx
   9973 E6 02         [ 3]  506 	lda	2,x
   9975 87            [ 2]  507 	psha
   9976 E6 03         [ 3]  508 	lda	3,x
   9978 87            [ 2]  509 	psha
   9979 E6 3E         [ 3]  510 	lda	62,x
   997B EE 3D         [ 3]  511 	ldx	61,x
   997D CD 98 74      [ 5]  512 	jsr	_readTableCell
   9980 9E E7 4C      [ 4]  513 	sta	76,s
   9983 9E EF 4B      [ 4]  514 	stx	75,s
   9986 A7 02         [ 2]  515 	ais	#2
                            516 ;tables.c:42: q22 = readTableCell(table, yHigh, xHigh);
   9988 95            [ 2]  517 	tsx
   9989 E6 01         [ 3]  518 	lda	1,x
   998B 87            [ 2]  519 	psha
   998C E6 03         [ 3]  520 	lda	3,x
   998E 87            [ 2]  521 	psha
   998F E6 3E         [ 3]  522 	lda	62,x
   9991 EE 3D         [ 3]  523 	ldx	61,x
   9993 CD 98 74      [ 5]  524 	jsr	_readTableCell
   9996 9E E7 4A      [ 4]  525 	sta	74,s
   9999 9E EF 49      [ 4]  526 	stx	73,s
   999C A7 02         [ 2]  527 	ais	#2
                            528 ;tables.c:44: if (xLow == xHigh && yLow == yHigh) {
   999E 95            [ 2]  529 	tsx
   999F E6 02         [ 3]  530 	lda	2,x
   99A1 E1 01         [ 3]  531 	cmp	1,x
   99A3 27 03         [ 3]  532 	beq	00173$
   99A5 4F            [ 1]  533 	clra
   99A6 20 02         [ 3]  534 	bra	00172$
   99A8                     535 00173$:
   99A8 A6 01         [ 2]  536 	lda	#0x01
   99AA                     537 00172$:
   99AA E7 0A         [ 3]  538 	sta	10,x
   99AC 6D 0A         [ 3]  539 	tst	10,x
   99AE 27 0D         [ 3]  540 	beq	00102$
   99B0 F6            [ 2]  541 	lda	,x
   99B1 E1 03         [ 3]  542 	cmp	3,x
   99B3 26 08         [ 3]  543 	bne	00102$
                            544 ;tables.c:45: return q11;
   99B5 EE 4C         [ 3]  545 	ldx	76,x
   99B7 9E E6 4E      [ 4]  546 	lda	78,s
   99BA CC 9F 6C      [ 3]  547 	jmp	00125$
   99BD                     548 00102$:
                            549 ;tables.c:48: x1 = table->axisX[xLow];
   99BD 9E E6 03      [ 4]  550 	lda	3,s
   99C0 48            [ 1]  551 	lsla	
   99C1 9E EB 3F      [ 4]  552 	add	63,s
   99C4 97            [ 1]  553 	tax
   99C5 4F            [ 1]  554 	clra
   99C6 9E E9 3E      [ 4]  555 	adc	62,s
   99C9 87            [ 2]  556 	psha
   99CA 8A            [ 2]  557 	pulh
   99CB F6            [ 2]  558 	lda	,x
   99CC 9E E7 45      [ 4]  559 	sta	69,s
   99CF E6 01         [ 3]  560 	lda	1,x
   99D1 9E E7 46      [ 4]  561 	sta	70,s
                            562 ;tables.c:49: x2 = table->axisX[xHigh];
   99D4 9E E6 02      [ 4]  563 	lda	2,s
   99D7 48            [ 1]  564 	lsla	
   99D8 9E EB 3F      [ 4]  565 	add	63,s
   99DB 97            [ 1]  566 	tax
   99DC 4F            [ 1]  567 	clra
   99DD 9E E9 3E      [ 4]  568 	adc	62,s
   99E0 87            [ 2]  569 	psha
   99E1 8A            [ 2]  570 	pulh
   99E2 F6            [ 2]  571 	lda	,x
   99E3 9E E7 43      [ 4]  572 	sta	67,s
   99E6 E6 01         [ 3]  573 	lda	1,x
   99E8 9E E7 44      [ 4]  574 	sta	68,s
                            575 ;tables.c:50: y1 = table->axisY[yLow];
   99EB 95            [ 2]  576 	tsx
   99EC E6 3E         [ 3]  577 	lda	62,x
   99EE AB 18         [ 2]  578 	add	#0x18
   99F0 E7 28         [ 3]  579 	sta	40,x
   99F2 E6 3D         [ 3]  580 	lda	61,x
   99F4 A9 00         [ 2]  581 	adc	#0
   99F6 E7 27         [ 3]  582 	sta	39,x
   99F8 F6            [ 2]  583 	lda	,x
   99F9 E7 0C         [ 3]  584 	sta	12,x
   99FB E6 0C         [ 3]  585 	lda	12,x
   99FD EB 28         [ 3]  586 	add	40,x
   99FF 97            [ 1]  587 	tax
   9A00 A6 00         [ 2]  588 	lda	#0x00
   9A02 9E E9 28      [ 4]  589 	adc	40,s
   9A05 87            [ 2]  590 	psha
   9A06 8A            [ 2]  591 	pulh
   9A07 F6            [ 2]  592 	lda	,x
   9A08 9E E7 42      [ 4]  593 	sta	66,s
                            594 ;tables.c:51: y2 = table->axisY[yHigh];
   9A0B 9E E6 04      [ 4]  595 	lda	4,s
   9A0E 87            [ 2]  596 	psha
   9A0F 8A            [ 2]  597 	pulh
   9A10 8B            [ 2]  598 	pshh
   9A11 86            [ 2]  599 	pula
   9A12 9E EB 29      [ 4]  600 	add	41,s
   9A15 97            [ 1]  601 	tax
   9A16 4F            [ 1]  602 	clra
   9A17 9E E9 28      [ 4]  603 	adc	40,s
   9A1A 8B            [ 2]  604 	pshh
   9A1B 87            [ 2]  605 	psha
   9A1C 8A            [ 2]  606 	pulh
   9A1D FE            [ 2]  607 	ldx	,x
   9A1E 8A            [ 2]  608 	pulh
                            609 ;tables.c:54: result = interpolate((int16_t)valueY, y1, y2, q11, q12);
   9A1F 9E EF 29      [ 4]  610 	stx	41,s
   9A22 4F            [ 1]  611 	clra
   9A23 9E E7 28      [ 4]  612 	sta	40,s
   9A26 9E E6 42      [ 4]  613 	lda	66,s
   9A29 9E E7 0A      [ 4]  614 	sta	10,s
   9A2C 4F            [ 1]  615 	clra
   9A2D 9E E7 09      [ 4]  616 	sta	9,s
   9A30 9E E6 51      [ 4]  617 	lda	81,s
   9A33 9E E7 13      [ 4]  618 	sta	19,s
   9A36 4F            [ 1]  619 	clra
   9A37 9E E7 12      [ 4]  620 	sta	18,s
                            621 ;tables.c:53: if (xLow == xHigh) {
   9A3A 9E 6D 0B      [ 4]  622 	tst	11,s
   9A3D 26 03         [ 3]  623 	bne	00176$
   9A3F CC 9B 4F      [ 3]  624 	jmp	00108$
   9A42                     625 00176$:
                            626 ;tables.c:54: result = interpolate((int16_t)valueY, y1, y2, q11, q12);
   9A42 95            [ 2]  627 	tsx
   9A43 E6 27         [ 3]  628 	lda	39,x
   9A45 E7 35         [ 3]  629 	sta	53,x
   9A47 E6 28         [ 3]  630 	lda	40,x
   9A49 E7 36         [ 3]  631 	sta	54,x
   9A4B E6 08         [ 3]  632 	lda	8,x
   9A4D E7 37         [ 3]  633 	sta	55,x
   9A4F E6 09         [ 3]  634 	lda	9,x
   9A51 E7 38         [ 3]  635 	sta	56,x
   9A53 E6 11         [ 3]  636 	lda	17,x
   9A55 E7 39         [ 3]  637 	sta	57,x
   9A57 E6 12         [ 3]  638 	lda	18,x
   9A59 E7 3A         [ 3]  639 	sta	58,x
                            640 ;tables.h:34: if (x2 == x1) return y1;
   9A5B E6 36         [ 3]  641 	lda	54,x
   9A5D E1 38         [ 3]  642 	cmp	56,x
   9A5F 26 06         [ 3]  643 	bne	00177$
   9A61 E6 35         [ 3]  644 	lda	53,x
   9A63 E1 37         [ 3]  645 	cmp	55,x
   9A65 27 02         [ 3]  646 	beq	00178$
   9A67                     647 00177$:
   9A67 20 0B         [ 3]  648 	bra	00111$
   9A69                     649 00178$:
   9A69 E6 4C         [ 3]  650 	lda	76,x
   9A6B E7 0A         [ 3]  651 	sta	10,x
   9A6D E6 4D         [ 3]  652 	lda	77,x
   9A6F E7 0B         [ 3]  653 	sta	11,x
   9A71 CC 9B 43      [ 3]  654 	jmp	00112$
   9A74                     655 00111$:
                            656 ;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
   9A74 9E E6 3B      [ 4]  657 	lda	59,s
   9A77 9E E0 39      [ 4]  658 	sub	57,s
   9A7A 87            [ 2]  659 	psha
   9A7B 9E E6 3B      [ 4]  660 	lda	59,s
   9A7E 9E E2 39      [ 4]  661 	sbc	57,s
   9A81 97            [ 1]  662 	tax
   9A82 86            [ 2]  663 	pula
   9A83 9E E7 11      [ 4]  664 	sta	17,s
   9A86 9F            [ 1]  665 	txa
   9A87 9E E7 10      [ 4]  666 	sta	16,s
   9A8A 49            [ 1]  667 	rola	
   9A8B 4F            [ 1]  668 	clra	
   9A8C A2 00         [ 2]  669 	sbc	#0x00
   9A8E 9E E7 0F      [ 4]  670 	sta	15,s
   9A91 9E E7 0E      [ 4]  671 	sta	14,s
   9A94 9E E6 4A      [ 4]  672 	lda	74,s
   9A97 9E E0 4E      [ 4]  673 	sub	78,s
   9A9A 87            [ 2]  674 	psha
   9A9B 9E E6 4A      [ 4]  675 	lda	74,s
   9A9E 9E E2 4E      [ 4]  676 	sbc	78,s
   9AA1 97            [ 1]  677 	tax
   9AA2 86            [ 2]  678 	pula
   9AA3 9E E7 21      [ 4]  679 	sta	33,s
   9AA6 9F            [ 1]  680 	txa
   9AA7 9E E7 20      [ 4]  681 	sta	32,s
   9AAA 49            [ 1]  682 	rola	
   9AAB 4F            [ 1]  683 	clra	
   9AAC A2 00         [ 2]  684 	sbc	#0x00
   9AAE 9E E7 1F      [ 4]  685 	sta	31,s
   9AB1 9E E7 1E      [ 4]  686 	sta	30,s
   9AB4 95            [ 2]  687 	tsx
   9AB5 E6 20         [ 3]  688 	lda	32,x
   9AB7 87            [ 2]  689 	psha
   9AB8 E6 1F         [ 3]  690 	lda	31,x
   9ABA 87            [ 2]  691 	psha
   9ABB E6 1E         [ 3]  692 	lda	30,x
   9ABD 87            [ 2]  693 	psha
   9ABE E6 1D         [ 3]  694 	lda	29,x
   9AC0 87            [ 2]  695 	psha
   9AC1 E6 10         [ 3]  696 	lda	16,x
   9AC3 87            [ 2]  697 	psha
   9AC4 E6 0F         [ 3]  698 	lda	15,x
   9AC6 87            [ 2]  699 	psha
   9AC7 E6 0E         [ 3]  700 	lda	14,x
   9AC9 87            [ 2]  701 	psha
   9ACA E6 0D         [ 3]  702 	lda	13,x
   9ACC 87            [ 2]  703 	psha
   9ACD CD D0 87      [ 5]  704 	jsr	__mullong
   9AD0 9E E7 29      [ 4]  705 	sta	41,s
   9AD3 9E EF 28      [ 4]  706 	stx	40,s
   9AD6 B6 4A         [ 3]  707 	lda	*___SDCC_hc08_ret2
   9AD8 9E E7 27      [ 4]  708 	sta	39,s
   9ADB B6 4B         [ 3]  709 	lda	*___SDCC_hc08_ret3
   9ADD 9E E7 26      [ 4]  710 	sta	38,s
   9AE0 A7 08         [ 2]  711 	ais	#8
   9AE2 9E E6 37      [ 4]  712 	lda	55,s
   9AE5 9E E0 39      [ 4]  713 	sub	57,s
   9AE8 87            [ 2]  714 	psha
   9AE9 9E E6 37      [ 4]  715 	lda	55,s
   9AEC 9E E2 39      [ 4]  716 	sbc	57,s
   9AEF 97            [ 1]  717 	tax
   9AF0 86            [ 2]  718 	pula
   9AF1 9E E7 11      [ 4]  719 	sta	17,s
   9AF4 9F            [ 1]  720 	txa
   9AF5 9E E7 10      [ 4]  721 	sta	16,s
   9AF8 49            [ 1]  722 	rola	
   9AF9 4F            [ 1]  723 	clra	
   9AFA A2 00         [ 2]  724 	sbc	#0x00
   9AFC 9E E7 0F      [ 4]  725 	sta	15,s
   9AFF 9E E7 0E      [ 4]  726 	sta	14,s
   9B02 95            [ 2]  727 	tsx
   9B03 E6 10         [ 3]  728 	lda	16,x
   9B05 87            [ 2]  729 	psha
   9B06 E6 0F         [ 3]  730 	lda	15,x
   9B08 87            [ 2]  731 	psha
   9B09 E6 0E         [ 3]  732 	lda	14,x
   9B0B 87            [ 2]  733 	psha
   9B0C E6 0D         [ 3]  734 	lda	13,x
   9B0E 87            [ 2]  735 	psha
   9B0F E6 20         [ 3]  736 	lda	32,x
   9B11 87            [ 2]  737 	psha
   9B12 E6 1F         [ 3]  738 	lda	31,x
   9B14 87            [ 2]  739 	psha
   9B15 E6 1E         [ 3]  740 	lda	30,x
   9B17 87            [ 2]  741 	psha
   9B18 E6 1D         [ 3]  742 	lda	29,x
   9B1A 87            [ 2]  743 	psha
   9B1B CD CE 92      [ 5]  744 	jsr	__divslong
   9B1E 9E E7 29      [ 4]  745 	sta	41,s
   9B21 9E EF 28      [ 4]  746 	stx	40,s
   9B24 B6 4A         [ 3]  747 	lda	*___SDCC_hc08_ret2
   9B26 9E E7 27      [ 4]  748 	sta	39,s
   9B29 B6 4B         [ 3]  749 	lda	*___SDCC_hc08_ret3
   9B2B 9E E7 26      [ 4]  750 	sta	38,s
   9B2E A7 08         [ 2]  751 	ais	#8
   9B30 9E E6 21      [ 4]  752 	lda	33,s
   9B33 9E EE 20      [ 4]  753 	ldx	32,s
   9B36 9E EB 4E      [ 4]  754 	add	78,s
   9B39 9E E7 0C      [ 4]  755 	sta	12,s
   9B3C 9F            [ 1]  756 	txa
   9B3D 9E E9 4D      [ 4]  757 	adc	77,s
   9B40 9E E7 0B      [ 4]  758 	sta	11,s
                            759 ;tables.c:54: result = interpolate((int16_t)valueY, y1, y2, q11, q12);
   9B43                     760 00112$:
   9B43 95            [ 2]  761 	tsx
   9B44 E6 0A         [ 3]  762 	lda	10,x
   9B46 E7 3F         [ 3]  763 	sta	63,x
   9B48 E6 0B         [ 3]  764 	lda	11,x
   9B4A E7 40         [ 3]  765 	sta	64,x
   9B4C CC 9F 66      [ 3]  766 	jmp	00109$
   9B4F                     767 00108$:
                            768 ;tables.c:56: result = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q11, q21);
   9B4F 9E E6 44      [ 4]  769 	lda	68,s
   9B52 9E E7 1F      [ 4]  770 	sta	31,s
   9B55 9E E6 43      [ 4]  771 	lda	67,s
   9B58 9E E7 1E      [ 4]  772 	sta	30,s
   9B5B 9E E6 46      [ 4]  773 	lda	70,s
   9B5E 9E E7 0F      [ 4]  774 	sta	15,s
   9B61 9E E6 45      [ 4]  775 	lda	69,s
   9B64 9E E7 0E      [ 4]  776 	sta	14,s
   9B67 9E E6 53      [ 4]  777 	lda	83,s
   9B6A 9E E7 0C      [ 4]  778 	sta	12,s
   9B6D 9E E6 52      [ 4]  779 	lda	82,s
   9B70 9E E7 0B      [ 4]  780 	sta	11,s
                            781 ;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
   9B73 9E E6 4C      [ 4]  782 	lda	76,s
   9B76 9E E0 4E      [ 4]  783 	sub	78,s
   9B79 87            [ 2]  784 	psha
   9B7A 9E E6 4C      [ 4]  785 	lda	76,s
   9B7D 9E E2 4E      [ 4]  786 	sbc	78,s
   9B80 97            [ 1]  787 	tax
   9B81 86            [ 2]  788 	pula
   9B82 9E E7 08      [ 4]  789 	sta	8,s
   9B85 9F            [ 1]  790 	txa
   9B86 9E E7 07      [ 4]  791 	sta	7,s
   9B89 49            [ 1]  792 	rola	
   9B8A 4F            [ 1]  793 	clra	
   9B8B A2 00         [ 2]  794 	sbc	#0x00
   9B8D 9E E7 06      [ 4]  795 	sta	6,s
   9B90 9E E7 05      [ 4]  796 	sta	5,s
                            797 ;tables.c:55: } else if (yLow == yHigh) {
   9B93 8B            [ 2]  798 	pshh
   9B94 86            [ 2]  799 	pula
   9B95 9E E1 0D      [ 4]  800 	cmp	13,s
   9B98 27 03         [ 3]  801 	beq	00179$
   9B9A CC 9C 8A      [ 3]  802 	jmp	00105$
   9B9D                     803 00179$:
                            804 ;tables.c:56: result = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q11, q21);
   9B9D 95            [ 2]  805 	tsx
   9B9E E6 1D         [ 3]  806 	lda	29,x
   9BA0 E7 2F         [ 3]  807 	sta	47,x
   9BA2 E6 1E         [ 3]  808 	lda	30,x
   9BA4 E7 30         [ 3]  809 	sta	48,x
   9BA6 E6 0D         [ 3]  810 	lda	13,x
   9BA8 E7 31         [ 3]  811 	sta	49,x
   9BAA E6 0E         [ 3]  812 	lda	14,x
   9BAC E7 32         [ 3]  813 	sta	50,x
   9BAE E6 0A         [ 3]  814 	lda	10,x
   9BB0 E7 33         [ 3]  815 	sta	51,x
   9BB2 E6 0B         [ 3]  816 	lda	11,x
   9BB4 E7 34         [ 3]  817 	sta	52,x
                            818 ;tables.h:34: if (x2 == x1) return y1;
   9BB6 E6 30         [ 3]  819 	lda	48,x
   9BB8 E1 32         [ 3]  820 	cmp	50,x
   9BBA 26 06         [ 3]  821 	bne	00180$
   9BBC E6 2F         [ 3]  822 	lda	47,x
   9BBE E1 31         [ 3]  823 	cmp	49,x
   9BC0 27 02         [ 3]  824 	beq	00181$
   9BC2                     825 00180$:
   9BC2 20 0B         [ 3]  826 	bra	00114$
   9BC4                     827 00181$:
   9BC4 E6 4C         [ 3]  828 	lda	76,x
   9BC6 E7 13         [ 3]  829 	sta	19,x
   9BC8 E6 4D         [ 3]  830 	lda	77,x
   9BCA E7 14         [ 3]  831 	sta	20,x
   9BCC CC 9C 7E      [ 3]  832 	jmp	00115$
   9BCF                     833 00114$:
                            834 ;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
   9BCF 9E E6 35      [ 4]  835 	lda	53,s
   9BD2 9E E0 33      [ 4]  836 	sub	51,s
   9BD5 87            [ 2]  837 	psha
   9BD6 9E E6 35      [ 4]  838 	lda	53,s
   9BD9 9E E2 33      [ 4]  839 	sbc	51,s
   9BDC 97            [ 1]  840 	tax
   9BDD 86            [ 2]  841 	pula
   9BDE 9E E7 1D      [ 4]  842 	sta	29,s
   9BE1 9F            [ 1]  843 	txa
   9BE2 9E E7 1C      [ 4]  844 	sta	28,s
   9BE5 49            [ 1]  845 	rola	
   9BE6 4F            [ 1]  846 	clra	
   9BE7 A2 00         [ 2]  847 	sbc	#0x00
   9BE9 9E E7 1B      [ 4]  848 	sta	27,s
   9BEC 9E E7 1A      [ 4]  849 	sta	26,s
   9BEF 95            [ 2]  850 	tsx
   9BF0 E6 07         [ 3]  851 	lda	7,x
   9BF2 87            [ 2]  852 	psha
   9BF3 E6 06         [ 3]  853 	lda	6,x
   9BF5 87            [ 2]  854 	psha
   9BF6 E6 05         [ 3]  855 	lda	5,x
   9BF8 87            [ 2]  856 	psha
   9BF9 E6 04         [ 3]  857 	lda	4,x
   9BFB 87            [ 2]  858 	psha
   9BFC E6 1C         [ 3]  859 	lda	28,x
   9BFE 87            [ 2]  860 	psha
   9BFF E6 1B         [ 3]  861 	lda	27,x
   9C01 87            [ 2]  862 	psha
   9C02 E6 1A         [ 3]  863 	lda	26,x
   9C04 87            [ 2]  864 	psha
   9C05 E6 19         [ 3]  865 	lda	25,x
   9C07 87            [ 2]  866 	psha
   9C08 CD D0 87      [ 5]  867 	jsr	__mullong
   9C0B 9E E7 25      [ 4]  868 	sta	37,s
   9C0E 9E EF 24      [ 4]  869 	stx	36,s
   9C11 B6 4A         [ 3]  870 	lda	*___SDCC_hc08_ret2
   9C13 9E E7 23      [ 4]  871 	sta	35,s
   9C16 B6 4B         [ 3]  872 	lda	*___SDCC_hc08_ret3
   9C18 9E E7 22      [ 4]  873 	sta	34,s
   9C1B A7 08         [ 2]  874 	ais	#8
   9C1D 9E E6 31      [ 4]  875 	lda	49,s
   9C20 9E E0 33      [ 4]  876 	sub	51,s
   9C23 87            [ 2]  877 	psha
   9C24 9E E6 31      [ 4]  878 	lda	49,s
   9C27 9E E2 33      [ 4]  879 	sbc	51,s
   9C2A 97            [ 1]  880 	tax
   9C2B 86            [ 2]  881 	pula
   9C2C 9E E7 27      [ 4]  882 	sta	39,s
   9C2F 9F            [ 1]  883 	txa
   9C30 9E E7 26      [ 4]  884 	sta	38,s
   9C33 49            [ 1]  885 	rola	
   9C34 4F            [ 1]  886 	clra	
   9C35 A2 00         [ 2]  887 	sbc	#0x00
   9C37 9E E7 25      [ 4]  888 	sta	37,s
   9C3A 9E E7 24      [ 4]  889 	sta	36,s
   9C3D 95            [ 2]  890 	tsx
   9C3E E6 26         [ 3]  891 	lda	38,x
   9C40 87            [ 2]  892 	psha
   9C41 E6 25         [ 3]  893 	lda	37,x
   9C43 87            [ 2]  894 	psha
   9C44 E6 24         [ 3]  895 	lda	36,x
   9C46 87            [ 2]  896 	psha
   9C47 E6 23         [ 3]  897 	lda	35,x
   9C49 87            [ 2]  898 	psha
   9C4A E6 1C         [ 3]  899 	lda	28,x
   9C4C 87            [ 2]  900 	psha
   9C4D E6 1B         [ 3]  901 	lda	27,x
   9C4F 87            [ 2]  902 	psha
   9C50 E6 1A         [ 3]  903 	lda	26,x
   9C52 87            [ 2]  904 	psha
   9C53 E6 19         [ 3]  905 	lda	25,x
   9C55 87            [ 2]  906 	psha
   9C56 CD CE 92      [ 5]  907 	jsr	__divslong
   9C59 9E E7 2F      [ 4]  908 	sta	47,s
   9C5C 9E EF 2E      [ 4]  909 	stx	46,s
   9C5F B6 4A         [ 3]  910 	lda	*___SDCC_hc08_ret2
   9C61 9E E7 2D      [ 4]  911 	sta	45,s
   9C64 B6 4B         [ 3]  912 	lda	*___SDCC_hc08_ret3
   9C66 9E E7 2C      [ 4]  913 	sta	44,s
   9C69 A7 08         [ 2]  914 	ais	#8
   9C6B 9E E6 27      [ 4]  915 	lda	39,s
   9C6E 9E EE 26      [ 4]  916 	ldx	38,s
   9C71 9E EB 4E      [ 4]  917 	add	78,s
   9C74 9E E7 15      [ 4]  918 	sta	21,s
   9C77 9F            [ 1]  919 	txa
   9C78 9E E9 4D      [ 4]  920 	adc	77,s
   9C7B 9E E7 14      [ 4]  921 	sta	20,s
                            922 ;tables.c:56: result = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q11, q21);
   9C7E                     923 00115$:
   9C7E 95            [ 2]  924 	tsx
   9C7F E6 13         [ 3]  925 	lda	19,x
   9C81 E7 3F         [ 3]  926 	sta	63,x
   9C83 E6 14         [ 3]  927 	lda	20,x
   9C85 E7 40         [ 3]  928 	sta	64,x
   9C87 CC 9F 66      [ 3]  929 	jmp	00109$
   9C8A                     930 00105$:
                            931 ;tables.c:58: int16_t r1 = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q11, q21);
   9C8A 95            [ 2]  932 	tsx
   9C8B E6 1D         [ 3]  933 	lda	29,x
   9C8D E7 23         [ 3]  934 	sta	35,x
   9C8F E6 1E         [ 3]  935 	lda	30,x
   9C91 E7 24         [ 3]  936 	sta	36,x
   9C93 E6 0D         [ 3]  937 	lda	13,x
   9C95 E7 19         [ 3]  938 	sta	25,x
   9C97 E6 0E         [ 3]  939 	lda	14,x
   9C99 E7 1A         [ 3]  940 	sta	26,x
   9C9B E6 0A         [ 3]  941 	lda	10,x
   9C9D E7 13         [ 3]  942 	sta	19,x
   9C9F E6 0B         [ 3]  943 	lda	11,x
   9CA1 E7 14         [ 3]  944 	sta	20,x
   9CA3 E6 24         [ 3]  945 	lda	36,x
   9CA5 E1 1A         [ 3]  946 	cmp	26,x
   9CA7 26 06         [ 3]  947 	bne	00182$
   9CA9 E6 23         [ 3]  948 	lda	35,x
   9CAB E1 19         [ 3]  949 	cmp	25,x
   9CAD 27 02         [ 3]  950 	beq	00183$
   9CAF                     951 00182$:
   9CAF 20 0B         [ 3]  952 	bra	00117$
   9CB1                     953 00183$:
   9CB1 E6 4C         [ 3]  954 	lda	76,x
   9CB3 E7 21         [ 3]  955 	sta	33,x
   9CB5 E6 4D         [ 3]  956 	lda	77,x
   9CB7 E7 22         [ 3]  957 	sta	34,x
   9CB9 CC 9D 6B      [ 3]  958 	jmp	00118$
   9CBC                     959 00117$:
   9CBC 9E E6 15      [ 4]  960 	lda	21,s
   9CBF 9E E0 1B      [ 4]  961 	sub	27,s
   9CC2 87            [ 2]  962 	psha
   9CC3 9E E6 15      [ 4]  963 	lda	21,s
   9CC6 9E E2 1B      [ 4]  964 	sbc	27,s
   9CC9 97            [ 1]  965 	tax
   9CCA 86            [ 2]  966 	pula
   9CCB 9E E7 19      [ 4]  967 	sta	25,s
   9CCE 9F            [ 1]  968 	txa
   9CCF 9E E7 18      [ 4]  969 	sta	24,s
   9CD2 49            [ 1]  970 	rola	
   9CD3 4F            [ 1]  971 	clra	
   9CD4 A2 00         [ 2]  972 	sbc	#0x00
   9CD6 9E E7 17      [ 4]  973 	sta	23,s
   9CD9 9E E7 16      [ 4]  974 	sta	22,s
   9CDC 95            [ 2]  975 	tsx
   9CDD E6 07         [ 3]  976 	lda	7,x
   9CDF 87            [ 2]  977 	psha
   9CE0 E6 06         [ 3]  978 	lda	6,x
   9CE2 87            [ 2]  979 	psha
   9CE3 E6 05         [ 3]  980 	lda	5,x
   9CE5 87            [ 2]  981 	psha
   9CE6 E6 04         [ 3]  982 	lda	4,x
   9CE8 87            [ 2]  983 	psha
   9CE9 E6 18         [ 3]  984 	lda	24,x
   9CEB 87            [ 2]  985 	psha
   9CEC E6 17         [ 3]  986 	lda	23,x
   9CEE 87            [ 2]  987 	psha
   9CEF E6 16         [ 3]  988 	lda	22,x
   9CF1 87            [ 2]  989 	psha
   9CF2 E6 15         [ 3]  990 	lda	21,x
   9CF4 87            [ 2]  991 	psha
   9CF5 CD D0 87      [ 5]  992 	jsr	__mullong
   9CF8 9E E7 21      [ 4]  993 	sta	33,s
   9CFB 9E EF 20      [ 4]  994 	stx	32,s
   9CFE B6 4A         [ 3]  995 	lda	*___SDCC_hc08_ret2
   9D00 9E E7 1F      [ 4]  996 	sta	31,s
   9D03 B6 4B         [ 3]  997 	lda	*___SDCC_hc08_ret3
   9D05 9E E7 1E      [ 4]  998 	sta	30,s
   9D08 A7 08         [ 2]  999 	ais	#8
   9D0A 9E E6 25      [ 4] 1000 	lda	37,s
   9D0D 9E E0 1B      [ 4] 1001 	sub	27,s
   9D10 87            [ 2] 1002 	psha
   9D11 9E E6 25      [ 4] 1003 	lda	37,s
   9D14 9E E2 1B      [ 4] 1004 	sbc	27,s
   9D17 97            [ 1] 1005 	tax
   9D18 86            [ 2] 1006 	pula
   9D19 9E E7 27      [ 4] 1007 	sta	39,s
   9D1C 9F            [ 1] 1008 	txa
   9D1D 9E E7 26      [ 4] 1009 	sta	38,s
   9D20 49            [ 1] 1010 	rola	
   9D21 4F            [ 1] 1011 	clra	
   9D22 A2 00         [ 2] 1012 	sbc	#0x00
   9D24 9E E7 25      [ 4] 1013 	sta	37,s
   9D27 9E E7 24      [ 4] 1014 	sta	36,s
   9D2A 95            [ 2] 1015 	tsx
   9D2B E6 26         [ 3] 1016 	lda	38,x
   9D2D 87            [ 2] 1017 	psha
   9D2E E6 25         [ 3] 1018 	lda	37,x
   9D30 87            [ 2] 1019 	psha
   9D31 E6 24         [ 3] 1020 	lda	36,x
   9D33 87            [ 2] 1021 	psha
   9D34 E6 23         [ 3] 1022 	lda	35,x
   9D36 87            [ 2] 1023 	psha
   9D37 E6 18         [ 3] 1024 	lda	24,x
   9D39 87            [ 2] 1025 	psha
   9D3A E6 17         [ 3] 1026 	lda	23,x
   9D3C 87            [ 2] 1027 	psha
   9D3D E6 16         [ 3] 1028 	lda	22,x
   9D3F 87            [ 2] 1029 	psha
   9D40 E6 15         [ 3] 1030 	lda	21,x
   9D42 87            [ 2] 1031 	psha
   9D43 CD CE 92      [ 5] 1032 	jsr	__divslong
   9D46 9E E7 21      [ 4] 1033 	sta	33,s
   9D49 9E EF 20      [ 4] 1034 	stx	32,s
   9D4C B6 4A         [ 3] 1035 	lda	*___SDCC_hc08_ret2
   9D4E 9E E7 1F      [ 4] 1036 	sta	31,s
   9D51 B6 4B         [ 3] 1037 	lda	*___SDCC_hc08_ret3
   9D53 9E E7 1E      [ 4] 1038 	sta	30,s
   9D56 A7 08         [ 2] 1039 	ais	#8
   9D58 9E E6 19      [ 4] 1040 	lda	25,s
   9D5B 9E EE 18      [ 4] 1041 	ldx	24,s
   9D5E 9E EB 4E      [ 4] 1042 	add	78,s
   9D61 9E E7 23      [ 4] 1043 	sta	35,s
   9D64 9F            [ 1] 1044 	txa
   9D65 9E E9 4D      [ 4] 1045 	adc	77,s
   9D68 9E E7 22      [ 4] 1046 	sta	34,s
   9D6B                    1047 00118$:
   9D6B 95            [ 2] 1048 	tsx
   9D6C E6 21         [ 3] 1049 	lda	33,x
   9D6E E7 3B         [ 3] 1050 	sta	59,x
   9D70 E6 22         [ 3] 1051 	lda	34,x
   9D72 E7 3C         [ 3] 1052 	sta	60,x
                           1053 ;tables.c:59: int16_t r2 = interpolate((int16_t)valueX, (int16_t)x1, (int16_t)x2, q12, q22);
   9D74 E6 1E         [ 3] 1054 	lda	30,x
   9D76 E1 0E         [ 3] 1055 	cmp	14,x
   9D78 26 06         [ 3] 1056 	bne	00184$
   9D7A E6 1D         [ 3] 1057 	lda	29,x
   9D7C E1 0D         [ 3] 1058 	cmp	13,x
   9D7E 27 02         [ 3] 1059 	beq	00185$
   9D80                    1060 00184$:
   9D80 20 0B         [ 3] 1061 	bra	00120$
   9D82                    1062 00185$:
   9D82 E6 48         [ 3] 1063 	lda	72,x
   9D84 E7 15         [ 3] 1064 	sta	21,x
   9D86 E6 49         [ 3] 1065 	lda	73,x
   9D88 E7 16         [ 3] 1066 	sta	22,x
   9D8A CC 9E 5C      [ 3] 1067 	jmp	00121$
   9D8D                    1068 00120$:
   9D8D 9E E6 0C      [ 4] 1069 	lda	12,s
   9D90 9E E0 0F      [ 4] 1070 	sub	15,s
   9D93 87            [ 2] 1071 	psha
   9D94 9E E6 0C      [ 4] 1072 	lda	12,s
   9D97 9E E2 0F      [ 4] 1073 	sbc	15,s
   9D9A 97            [ 1] 1074 	tax
   9D9B 86            [ 2] 1075 	pula
   9D9C 9E E7 27      [ 4] 1076 	sta	39,s
   9D9F 9F            [ 1] 1077 	txa
   9DA0 9E E7 26      [ 4] 1078 	sta	38,s
   9DA3 49            [ 1] 1079 	rola	
   9DA4 4F            [ 1] 1080 	clra	
   9DA5 A2 00         [ 2] 1081 	sbc	#0x00
   9DA7 9E E7 25      [ 4] 1082 	sta	37,s
   9DAA 9E E7 24      [ 4] 1083 	sta	36,s
   9DAD 9E E6 48      [ 4] 1084 	lda	72,s
   9DB0 9E E0 4A      [ 4] 1085 	sub	74,s
   9DB3 87            [ 2] 1086 	psha
   9DB4 9E E6 48      [ 4] 1087 	lda	72,s
   9DB7 9E E2 4A      [ 4] 1088 	sbc	74,s
   9DBA 97            [ 1] 1089 	tax
   9DBB 86            [ 2] 1090 	pula
   9DBC 9E E7 1D      [ 4] 1091 	sta	29,s
   9DBF 9F            [ 1] 1092 	txa
   9DC0 9E E7 1C      [ 4] 1093 	sta	28,s
   9DC3 49            [ 1] 1094 	rola	
   9DC4 4F            [ 1] 1095 	clra	
   9DC5 A2 00         [ 2] 1096 	sbc	#0x00
   9DC7 9E E7 1B      [ 4] 1097 	sta	27,s
   9DCA 9E E7 1A      [ 4] 1098 	sta	26,s
   9DCD 95            [ 2] 1099 	tsx
   9DCE E6 1C         [ 3] 1100 	lda	28,x
   9DD0 87            [ 2] 1101 	psha
   9DD1 E6 1B         [ 3] 1102 	lda	27,x
   9DD3 87            [ 2] 1103 	psha
   9DD4 E6 1A         [ 3] 1104 	lda	26,x
   9DD6 87            [ 2] 1105 	psha
   9DD7 E6 19         [ 3] 1106 	lda	25,x
   9DD9 87            [ 2] 1107 	psha
   9DDA E6 26         [ 3] 1108 	lda	38,x
   9DDC 87            [ 2] 1109 	psha
   9DDD E6 25         [ 3] 1110 	lda	37,x
   9DDF 87            [ 2] 1111 	psha
   9DE0 E6 24         [ 3] 1112 	lda	36,x
   9DE2 87            [ 2] 1113 	psha
   9DE3 E6 23         [ 3] 1114 	lda	35,x
   9DE5 87            [ 2] 1115 	psha
   9DE6 CD D0 87      [ 5] 1116 	jsr	__mullong
   9DE9 9E E7 2F      [ 4] 1117 	sta	47,s
   9DEC 9E EF 2E      [ 4] 1118 	stx	46,s
   9DEF B6 4A         [ 3] 1119 	lda	*___SDCC_hc08_ret2
   9DF1 9E E7 2D      [ 4] 1120 	sta	45,s
   9DF4 B6 4B         [ 3] 1121 	lda	*___SDCC_hc08_ret3
   9DF6 9E E7 2C      [ 4] 1122 	sta	44,s
   9DF9 A7 08         [ 2] 1123 	ais	#8
   9DFB 9E E6 1F      [ 4] 1124 	lda	31,s
   9DFE 9E E0 0F      [ 4] 1125 	sub	15,s
   9E01 87            [ 2] 1126 	psha
   9E02 9E E6 1F      [ 4] 1127 	lda	31,s
   9E05 9E E2 0F      [ 4] 1128 	sbc	15,s
   9E08 97            [ 1] 1129 	tax
   9E09 86            [ 2] 1130 	pula
   9E0A 9E E7 1D      [ 4] 1131 	sta	29,s
   9E0D 9F            [ 1] 1132 	txa
   9E0E 9E E7 1C      [ 4] 1133 	sta	28,s
   9E11 49            [ 1] 1134 	rola	
   9E12 4F            [ 1] 1135 	clra	
   9E13 A2 00         [ 2] 1136 	sbc	#0x00
   9E15 9E E7 1B      [ 4] 1137 	sta	27,s
   9E18 9E E7 1A      [ 4] 1138 	sta	26,s
   9E1B 95            [ 2] 1139 	tsx
   9E1C E6 1C         [ 3] 1140 	lda	28,x
   9E1E 87            [ 2] 1141 	psha
   9E1F E6 1B         [ 3] 1142 	lda	27,x
   9E21 87            [ 2] 1143 	psha
   9E22 E6 1A         [ 3] 1144 	lda	26,x
   9E24 87            [ 2] 1145 	psha
   9E25 E6 19         [ 3] 1146 	lda	25,x
   9E27 87            [ 2] 1147 	psha
   9E28 E6 26         [ 3] 1148 	lda	38,x
   9E2A 87            [ 2] 1149 	psha
   9E2B E6 25         [ 3] 1150 	lda	37,x
   9E2D 87            [ 2] 1151 	psha
   9E2E E6 24         [ 3] 1152 	lda	36,x
   9E30 87            [ 2] 1153 	psha
   9E31 E6 23         [ 3] 1154 	lda	35,x
   9E33 87            [ 2] 1155 	psha
   9E34 CD CE 92      [ 5] 1156 	jsr	__divslong
   9E37 9E E7 2F      [ 4] 1157 	sta	47,s
   9E3A 9E EF 2E      [ 4] 1158 	stx	46,s
   9E3D B6 4A         [ 3] 1159 	lda	*___SDCC_hc08_ret2
   9E3F 9E E7 2D      [ 4] 1160 	sta	45,s
   9E42 B6 4B         [ 3] 1161 	lda	*___SDCC_hc08_ret3
   9E44 9E E7 2C      [ 4] 1162 	sta	44,s
   9E47 A7 08         [ 2] 1163 	ais	#8
   9E49 9E E6 27      [ 4] 1164 	lda	39,s
   9E4C 9E EE 26      [ 4] 1165 	ldx	38,s
   9E4F 9E EB 4A      [ 4] 1166 	add	74,s
   9E52 9E E7 17      [ 4] 1167 	sta	23,s
   9E55 9F            [ 1] 1168 	txa
   9E56 9E E9 49      [ 4] 1169 	adc	73,s
   9E59 9E E7 16      [ 4] 1170 	sta	22,s
   9E5C                    1171 00121$:
                           1172 ;tables.c:60: result = interpolate((int16_t)valueY, y1, y2, r1, r2);
   9E5C 95            [ 2] 1173 	tsx
   9E5D E6 27         [ 3] 1174 	lda	39,x
   9E5F E7 29         [ 3] 1175 	sta	41,x
   9E61 E6 28         [ 3] 1176 	lda	40,x
   9E63 E7 2A         [ 3] 1177 	sta	42,x
   9E65 E6 08         [ 3] 1178 	lda	8,x
   9E67 E7 2B         [ 3] 1179 	sta	43,x
   9E69 E6 09         [ 3] 1180 	lda	9,x
   9E6B E7 2C         [ 3] 1181 	sta	44,x
   9E6D E6 11         [ 3] 1182 	lda	17,x
   9E6F E7 2D         [ 3] 1183 	sta	45,x
   9E71 E6 12         [ 3] 1184 	lda	18,x
   9E73 E7 2E         [ 3] 1185 	sta	46,x
                           1186 ;tables.h:34: if (x2 == x1) return y1;
   9E75 E6 2A         [ 3] 1187 	lda	42,x
   9E77 E1 2C         [ 3] 1188 	cmp	44,x
   9E79 26 06         [ 3] 1189 	bne	00186$
   9E7B E6 29         [ 3] 1190 	lda	41,x
   9E7D E1 2B         [ 3] 1191 	cmp	43,x
   9E7F 27 02         [ 3] 1192 	beq	00187$
   9E81                    1193 00186$:
   9E81 20 0B         [ 3] 1194 	bra	00123$
   9E83                    1195 00187$:
   9E83 E6 3B         [ 3] 1196 	lda	59,x
   9E85 E7 21         [ 3] 1197 	sta	33,x
   9E87 E6 3C         [ 3] 1198 	lda	60,x
   9E89 E7 22         [ 3] 1199 	sta	34,x
   9E8B CC 9F 5D      [ 3] 1200 	jmp	00124$
   9E8E                    1201 00123$:
                           1202 ;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
   9E8E 9E E6 2F      [ 4] 1203 	lda	47,s
   9E91 9E E0 2D      [ 4] 1204 	sub	45,s
   9E94 87            [ 2] 1205 	psha
   9E95 9E E6 2F      [ 4] 1206 	lda	47,s
   9E98 9E E2 2D      [ 4] 1207 	sbc	45,s
   9E9B 97            [ 1] 1208 	tax
   9E9C 86            [ 2] 1209 	pula
   9E9D 9E E7 27      [ 4] 1210 	sta	39,s
   9EA0 9F            [ 1] 1211 	txa
   9EA1 9E E7 26      [ 4] 1212 	sta	38,s
   9EA4 49            [ 1] 1213 	rola	
   9EA5 4F            [ 1] 1214 	clra	
   9EA6 A2 00         [ 2] 1215 	sbc	#0x00
   9EA8 9E E7 25      [ 4] 1216 	sta	37,s
   9EAB 9E E7 24      [ 4] 1217 	sta	36,s
   9EAE 9E E6 17      [ 4] 1218 	lda	23,s
   9EB1 9E E0 3D      [ 4] 1219 	sub	61,s
   9EB4 87            [ 2] 1220 	psha
   9EB5 9E E6 17      [ 4] 1221 	lda	23,s
   9EB8 9E E2 3D      [ 4] 1222 	sbc	61,s
   9EBB 97            [ 1] 1223 	tax
   9EBC 86            [ 2] 1224 	pula
   9EBD 9E E7 19      [ 4] 1225 	sta	25,s
   9EC0 9F            [ 1] 1226 	txa
   9EC1 9E E7 18      [ 4] 1227 	sta	24,s
   9EC4 49            [ 1] 1228 	rola	
   9EC5 4F            [ 1] 1229 	clra	
   9EC6 A2 00         [ 2] 1230 	sbc	#0x00
   9EC8 9E E7 17      [ 4] 1231 	sta	23,s
   9ECB 9E E7 16      [ 4] 1232 	sta	22,s
   9ECE 95            [ 2] 1233 	tsx
   9ECF E6 18         [ 3] 1234 	lda	24,x
   9ED1 87            [ 2] 1235 	psha
   9ED2 E6 17         [ 3] 1236 	lda	23,x
   9ED4 87            [ 2] 1237 	psha
   9ED5 E6 16         [ 3] 1238 	lda	22,x
   9ED7 87            [ 2] 1239 	psha
   9ED8 E6 15         [ 3] 1240 	lda	21,x
   9EDA 87            [ 2] 1241 	psha
   9EDB E6 26         [ 3] 1242 	lda	38,x
   9EDD 87            [ 2] 1243 	psha
   9EDE E6 25         [ 3] 1244 	lda	37,x
   9EE0 87            [ 2] 1245 	psha
   9EE1 E6 24         [ 3] 1246 	lda	36,x
   9EE3 87            [ 2] 1247 	psha
   9EE4 E6 23         [ 3] 1248 	lda	35,x
   9EE6 87            [ 2] 1249 	psha
   9EE7 CD D0 87      [ 5] 1250 	jsr	__mullong
   9EEA 9E E7 21      [ 4] 1251 	sta	33,s
   9EED 9E EF 20      [ 4] 1252 	stx	32,s
   9EF0 B6 4A         [ 3] 1253 	lda	*___SDCC_hc08_ret2
   9EF2 9E E7 1F      [ 4] 1254 	sta	31,s
   9EF5 B6 4B         [ 3] 1255 	lda	*___SDCC_hc08_ret3
   9EF7 9E E7 1E      [ 4] 1256 	sta	30,s
   9EFA A7 08         [ 2] 1257 	ais	#8
   9EFC 9E E6 2B      [ 4] 1258 	lda	43,s
   9EFF 9E E0 2D      [ 4] 1259 	sub	45,s
   9F02 87            [ 2] 1260 	psha
   9F03 9E E6 2B      [ 4] 1261 	lda	43,s
   9F06 9E E2 2D      [ 4] 1262 	sbc	45,s
   9F09 97            [ 1] 1263 	tax
   9F0A 86            [ 2] 1264 	pula
   9F0B 9E E7 27      [ 4] 1265 	sta	39,s
   9F0E 9F            [ 1] 1266 	txa
   9F0F 9E E7 26      [ 4] 1267 	sta	38,s
   9F12 49            [ 1] 1268 	rola	
   9F13 4F            [ 1] 1269 	clra	
   9F14 A2 00         [ 2] 1270 	sbc	#0x00
   9F16 9E E7 25      [ 4] 1271 	sta	37,s
   9F19 9E E7 24      [ 4] 1272 	sta	36,s
   9F1C 95            [ 2] 1273 	tsx
   9F1D E6 26         [ 3] 1274 	lda	38,x
   9F1F 87            [ 2] 1275 	psha
   9F20 E6 25         [ 3] 1276 	lda	37,x
   9F22 87            [ 2] 1277 	psha
   9F23 E6 24         [ 3] 1278 	lda	36,x
   9F25 87            [ 2] 1279 	psha
   9F26 E6 23         [ 3] 1280 	lda	35,x
   9F28 87            [ 2] 1281 	psha
   9F29 E6 18         [ 3] 1282 	lda	24,x
   9F2B 87            [ 2] 1283 	psha
   9F2C E6 17         [ 3] 1284 	lda	23,x
   9F2E 87            [ 2] 1285 	psha
   9F2F E6 16         [ 3] 1286 	lda	22,x
   9F31 87            [ 2] 1287 	psha
   9F32 E6 15         [ 3] 1288 	lda	21,x
   9F34 87            [ 2] 1289 	psha
   9F35 CD CE 92      [ 5] 1290 	jsr	__divslong
   9F38 9E E7 21      [ 4] 1291 	sta	33,s
   9F3B 9E EF 20      [ 4] 1292 	stx	32,s
   9F3E B6 4A         [ 3] 1293 	lda	*___SDCC_hc08_ret2
   9F40 9E E7 1F      [ 4] 1294 	sta	31,s
   9F43 B6 4B         [ 3] 1295 	lda	*___SDCC_hc08_ret3
   9F45 9E E7 1E      [ 4] 1296 	sta	30,s
   9F48 A7 08         [ 2] 1297 	ais	#8
   9F4A 9E E6 19      [ 4] 1298 	lda	25,s
   9F4D 9E EE 18      [ 4] 1299 	ldx	24,s
   9F50 9E EB 3D      [ 4] 1300 	add	61,s
   9F53 9E E7 23      [ 4] 1301 	sta	35,s
   9F56 9F            [ 1] 1302 	txa
   9F57 9E E9 3C      [ 4] 1303 	adc	60,s
   9F5A 9E E7 22      [ 4] 1304 	sta	34,s
                           1305 ;tables.c:60: result = interpolate((int16_t)valueY, y1, y2, r1, r2);
   9F5D                    1306 00124$:
   9F5D 95            [ 2] 1307 	tsx
   9F5E E6 21         [ 3] 1308 	lda	33,x
   9F60 E7 3F         [ 3] 1309 	sta	63,x
   9F62 E6 22         [ 3] 1310 	lda	34,x
   9F64 E7 40         [ 3] 1311 	sta	64,x
   9F66                    1312 00109$:
                           1313 ;tables.c:63: return result;
   9F66 95            [ 2] 1314 	tsx
   9F67 EE 3F         [ 3] 1315 	ldx	63,x
   9F69 9E E6 41      [ 4] 1316 	lda	65,s
   9F6C                    1317 00125$:
                           1318 ;tables.c:64: }
   9F6C A7 4E         [ 2] 1319 	ais	#78
   9F6E 81            [ 4] 1320 	rts
                           1321 ;------------------------------------------------------------
                           1322 ;Allocation info for local variables in function 'findTableXIndices'
                           1323 ;------------------------------------------------------------
                           1324 ;value                     Allocated to stack - sp +13
                           1325 ;idxLow                    Allocated to stack - sp +15
                           1326 ;idxHigh                   Allocated to stack - sp +17
                           1327 ;table                     Allocated to stack - sp +9
                           1328 ;i                         Allocated to stack - sp +8
                           1329 ;sloc0                     Allocated to stack - sp +6
                           1330 ;sloc1                     Allocated to stack - sp +4
                           1331 ;sloc2                     Allocated to stack - sp +2
                           1332 ;sloc3                     Allocated to stack - sp +1
                           1333 ;------------------------------------------------------------
                           1334 ;tables.c:66: void findTableXIndices(struct Table3D *table, uint16_t value, uint8_t *idxLow, uint8_t *idxHigh) {
                           1335 ;	-----------------------------------------
                           1336 ;	 function findTableXIndices
                           1337 ;	-----------------------------------------
                           1338 ;	Register assignment is optimal.
                           1339 ;	Stack space usage: 10 bytes.
   9F6F                    1340 _findTableXIndices:
   9F6F 87            [ 2] 1341 	psha
   9F70 89            [ 2] 1342 	pshx
   9F71 A7 F8         [ 2] 1343 	ais	#-8
                           1344 ;tables.c:69: if (value <= table->axisX[0]) {
   9F73 9E E6 09      [ 4] 1345 	lda	9,s
   9F76 87            [ 2] 1346 	psha
   9F77 8A            [ 2] 1347 	pulh
   9F78 9E EE 0A      [ 4] 1348 	ldx	10,s
   9F7B F6            [ 2] 1349 	lda	,x
   9F7C 87            [ 2] 1350 	psha
   9F7D EE 01         [ 3] 1351 	ldx	1,x
   9F7F 8A            [ 2] 1352 	pulh
                           1353 ;tables.c:70: *idxLow = 0;
   9F80 9E E6 0F      [ 4] 1354 	lda	15,s
   9F83 9E E7 06      [ 4] 1355 	sta	6,s
   9F86 9E E6 10      [ 4] 1356 	lda	16,s
   9F89 9E E7 07      [ 4] 1357 	sta	7,s
                           1358 ;tables.c:71: *idxHigh = 0;
   9F8C 9E E6 11      [ 4] 1359 	lda	17,s
   9F8F 9E E7 04      [ 4] 1360 	sta	4,s
   9F92 9E E6 12      [ 4] 1361 	lda	18,s
   9F95 9E E7 05      [ 4] 1362 	sta	5,s
                           1363 ;tables.c:69: if (value <= table->axisX[0]) {
   9F98 9F            [ 1] 1364 	txa
   9F99 9E E0 0E      [ 4] 1365 	sub	14,s
   9F9C 8B            [ 2] 1366 	pshh
   9F9D 86            [ 2] 1367 	pula
   9F9E 9E E2 0D      [ 4] 1368 	sbc	13,s
   9FA1 25 17         [ 3] 1369 	bcs	00102$
                           1370 ;tables.c:70: *idxLow = 0;
   9FA3 9E E6 06      [ 4] 1371 	lda	6,s
   9FA6 87            [ 2] 1372 	psha
   9FA7 8A            [ 2] 1373 	pulh
   9FA8 9E EE 07      [ 4] 1374 	ldx	7,s
   9FAB 4F            [ 1] 1375 	clra
   9FAC F7            [ 2] 1376 	sta	,x
                           1377 ;tables.c:71: *idxHigh = 0;
   9FAD 9E E6 04      [ 4] 1378 	lda	4,s
   9FB0 87            [ 2] 1379 	psha
   9FB1 8A            [ 2] 1380 	pulh
   9FB2 9E EE 05      [ 4] 1381 	ldx	5,s
   9FB5 4F            [ 1] 1382 	clra
   9FB6 F7            [ 2] 1383 	sta	,x
                           1384 ;tables.c:72: return;
   9FB7 CC A0 87      [ 3] 1385 	jmp	00111$
   9FBA                    1386 00102$:
                           1387 ;tables.c:74: if (value >= table->axisX[TABLE_SIZE_X - 1]) {
   9FBA 95            [ 2] 1388 	tsx
   9FBB E6 08         [ 3] 1389 	lda	8,x
   9FBD E7 01         [ 3] 1390 	sta	1,x
   9FBF E6 09         [ 3] 1391 	lda	9,x
   9FC1 E7 02         [ 3] 1392 	sta	2,x
   9FC3 E6 01         [ 3] 1393 	lda	1,x
   9FC5 87            [ 2] 1394 	psha
   9FC6 8A            [ 2] 1395 	pulh
   9FC7 9E EE 03      [ 4] 1396 	ldx	3,s
   9FCA E6 17         [ 3] 1397 	lda	23,x
   9FCC EE 16         [ 3] 1398 	ldx	22,x
   9FCE 87            [ 2] 1399 	psha
   9FCF 9E E6 0F      [ 4] 1400 	lda	15,s
   9FD2 9E E0 01      [ 4] 1401 	sub	1, s
   9FD5 86            [ 2] 1402 	pula
   9FD6 9E E6 0D      [ 4] 1403 	lda	13,s
   9FD9 89            [ 2] 1404 	pshx
   9FDA 9E E2 01      [ 4] 1405 	sbc	1,s
   9FDD A7 01         [ 2] 1406 	ais	#1
   9FDF 25 19         [ 3] 1407 	bcs	00104$
                           1408 ;tables.c:75: *idxLow = TABLE_SIZE_X - 1;
   9FE1 9E E6 06      [ 4] 1409 	lda	6,s
   9FE4 87            [ 2] 1410 	psha
   9FE5 8A            [ 2] 1411 	pulh
   9FE6 9E EE 07      [ 4] 1412 	ldx	7,s
   9FE9 A6 0B         [ 2] 1413 	lda	#0x0b
   9FEB F7            [ 2] 1414 	sta	,x
                           1415 ;tables.c:76: *idxHigh = TABLE_SIZE_X - 1;
   9FEC 9E E6 04      [ 4] 1416 	lda	4,s
   9FEF 87            [ 2] 1417 	psha
   9FF0 8A            [ 2] 1418 	pulh
   9FF1 9E EE 05      [ 4] 1419 	ldx	5,s
   9FF4 A6 0B         [ 2] 1420 	lda	#0x0b
   9FF6 F7            [ 2] 1421 	sta	,x
                           1422 ;tables.c:77: return;
   9FF7 CC A0 87      [ 3] 1423 	jmp	00111$
   9FFA                    1424 00104$:
                           1425 ;tables.c:80: for (i = 0; i < TABLE_SIZE_X - 1; i++) {
   9FFA 95            [ 2] 1426 	tsx
   9FFB 4F            [ 1] 1427 	clra
   9FFC E7 01         [ 3] 1428 	sta	1,x
   9FFE E7 07         [ 3] 1429 	sta	7,x
   A000                    1430 00109$:
                           1431 ;tables.c:81: if (value >= table->axisX[i] && value < table->axisX[i + 1]) {
   A000 9E E6 08      [ 4] 1432 	lda	8,s
   A003 48            [ 1] 1433 	lsla	
   A004 9E EB 0A      [ 4] 1434 	add	10,s
   A007 97            [ 1] 1435 	tax
   A008 4F            [ 1] 1436 	clra
   A009 9E E9 09      [ 4] 1437 	adc	9,s
   A00C 87            [ 2] 1438 	psha
   A00D 8A            [ 2] 1439 	pulh
   A00E E6 01         [ 3] 1440 	lda	1,x
   A010 FE            [ 2] 1441 	ldx	,x
   A011 87            [ 2] 1442 	psha
   A012 9E E6 0F      [ 4] 1443 	lda	15,s
   A015 9E E0 01      [ 4] 1444 	sub	1, s
   A018 86            [ 2] 1445 	pula
   A019 9E E6 0D      [ 4] 1446 	lda	13,s
   A01C 89            [ 2] 1447 	pshx
   A01D 9E E2 01      [ 4] 1448 	sbc	1,s
   A020 A7 01         [ 2] 1449 	ais	#1
   A022 25 41         [ 3] 1450 	bcs	00110$
   A024 95            [ 2] 1451 	tsx
   A025 E6 07         [ 3] 1452 	lda	7,x
   A027 AB 01         [ 2] 1453 	add	#0x01
   A029 F7            [ 2] 1454 	sta	,x
   A02A F6            [ 2] 1455 	lda	,x
   A02B 48            [ 1] 1456 	lsla	
   A02C EB 09         [ 3] 1457 	add	9,x
   A02E 97            [ 1] 1458 	tax
   A02F 4F            [ 1] 1459 	clra
   A030 9E E9 09      [ 4] 1460 	adc	9,s
   A033 87            [ 2] 1461 	psha
   A034 8A            [ 2] 1462 	pulh
   A035 E6 01         [ 3] 1463 	lda	1,x
   A037 FE            [ 2] 1464 	ldx	,x
   A038 87            [ 2] 1465 	psha
   A039 9E E6 0F      [ 4] 1466 	lda	15,s
   A03C 9E E0 01      [ 4] 1467 	sub	1, s
   A03F 86            [ 2] 1468 	pula
   A040 9E E6 0D      [ 4] 1469 	lda	13,s
   A043 89            [ 2] 1470 	pshx
   A044 9E E2 01      [ 4] 1471 	sbc	1,s
   A047 A7 01         [ 2] 1472 	ais	#1
   A049 24 1A         [ 3] 1473 	bcc	00110$
                           1474 ;tables.c:82: *idxLow = i;
   A04B 9E E6 06      [ 4] 1475 	lda	6,s
   A04E 87            [ 2] 1476 	psha
   A04F 8A            [ 2] 1477 	pulh
   A050 9E EE 07      [ 4] 1478 	ldx	7,s
   A053 9E E6 02      [ 4] 1479 	lda	2,s
   A056 F7            [ 2] 1480 	sta	,x
                           1481 ;tables.c:83: *idxHigh = i + 1;
   A057 9E E6 04      [ 4] 1482 	lda	4,s
   A05A 87            [ 2] 1483 	psha
   A05B 8A            [ 2] 1484 	pulh
   A05C 9E EE 05      [ 4] 1485 	ldx	5,s
   A05F 9E E6 01      [ 4] 1486 	lda	1,s
   A062 F7            [ 2] 1487 	sta	,x
                           1488 ;tables.c:84: return;
   A063 20 22         [ 3] 1489 	bra	00111$
   A065                    1490 00110$:
                           1491 ;tables.c:80: for (i = 0; i < TABLE_SIZE_X - 1; i++) {
   A065 95            [ 2] 1492 	tsx
   A066 6C 07         [ 4] 1493 	inc	7,x
   A068 E6 07         [ 3] 1494 	lda	7,x
   A06A E7 01         [ 3] 1495 	sta	1,x
   A06C E6 07         [ 3] 1496 	lda	7,x
   A06E A1 0B         [ 2] 1497 	cmp	#0x0b
   A070 25 8E         [ 3] 1498 	bcs	00109$
                           1499 ;tables.c:88: *idxLow = TABLE_SIZE_X - 2;
   A072 E6 05         [ 3] 1500 	lda	5,x
   A074 87            [ 2] 1501 	psha
   A075 8A            [ 2] 1502 	pulh
   A076 9E EE 07      [ 4] 1503 	ldx	7,s
   A079 A6 0A         [ 2] 1504 	lda	#0x0a
   A07B F7            [ 2] 1505 	sta	,x
                           1506 ;tables.c:89: *idxHigh = TABLE_SIZE_X - 1;
   A07C 9E E6 04      [ 4] 1507 	lda	4,s
   A07F 87            [ 2] 1508 	psha
   A080 8A            [ 2] 1509 	pulh
   A081 9E EE 05      [ 4] 1510 	ldx	5,s
   A084 A6 0B         [ 2] 1511 	lda	#0x0b
   A086 F7            [ 2] 1512 	sta	,x
   A087                    1513 00111$:
                           1514 ;tables.c:90: }
   A087 A7 0A         [ 2] 1515 	ais	#10
   A089 81            [ 4] 1516 	rts
                           1517 ;------------------------------------------------------------
                           1518 ;Allocation info for local variables in function 'findTableYIndices'
                           1519 ;------------------------------------------------------------
                           1520 ;value                     Allocated to stack - sp +16
                           1521 ;idxLow                    Allocated to stack - sp +17
                           1522 ;idxHigh                   Allocated to stack - sp +19
                           1523 ;table                     Allocated to stack - sp +5
                           1524 ;i                         Allocated to stack - sp +7
                           1525 ;sloc0                     Allocated to stack - sp +12
                           1526 ;sloc1                     Allocated to stack - sp +1
                           1527 ;sloc2                     Allocated to stack - sp +3
                           1528 ;sloc3                     Allocated to stack - sp +10
                           1529 ;sloc4                     Allocated to stack - sp +8
                           1530 ;------------------------------------------------------------
                           1531 ;tables.c:92: void findTableYIndices(struct Table3D *table, uint8_t value, uint8_t *idxLow, uint8_t *idxHigh) {
                           1532 ;	-----------------------------------------
                           1533 ;	 function findTableYIndices
                           1534 ;	-----------------------------------------
                           1535 ;	Register assignment might be sub-optimal.
                           1536 ;	Stack space usage: 13 bytes.
   A08A                    1537 _findTableYIndices:
   A08A A7 F3         [ 2] 1538 	ais	#-13
   A08C 9E E7 06      [ 4] 1539 	sta	6,s
   A08F 9E EF 05      [ 4] 1540 	stx	5,s
                           1541 ;tables.c:95: if (value <= table->axisY[0]) {
   A092 9E E6 05      [ 4] 1542 	lda	5,s
   A095 9E EE 06      [ 4] 1543 	ldx	6,s
   A098 87            [ 2] 1544 	psha
   A099 8A            [ 2] 1545 	pulh
   A09A EE 18         [ 3] 1546 	ldx	24,x
                           1547 ;tables.c:96: *idxLow = 0;
   A09C 9E E6 11      [ 4] 1548 	lda	17,s
   A09F 9E E7 0C      [ 4] 1549 	sta	12,s
   A0A2 9E E6 12      [ 4] 1550 	lda	18,s
   A0A5 9E E7 0D      [ 4] 1551 	sta	13,s
                           1552 ;tables.c:97: *idxHigh = 0;
   A0A8 9E E6 13      [ 4] 1553 	lda	19,s
   A0AB 9E E7 01      [ 4] 1554 	sta	1,s
   A0AE 9E E6 14      [ 4] 1555 	lda	20,s
   A0B1 9E E7 02      [ 4] 1556 	sta	2,s
                           1557 ;tables.c:95: if (value <= table->axisY[0]) {
   A0B4 9E E3 10      [ 4] 1558 	cpx	16,s
   A0B7 25 12         [ 3] 1559 	bcs	00102$
                           1560 ;tables.c:96: *idxLow = 0;
   A0B9 9E E6 0C      [ 4] 1561 	lda	12,s
   A0BC 87            [ 2] 1562 	psha
   A0BD 8A            [ 2] 1563 	pulh
   A0BE 9E EE 0D      [ 4] 1564 	ldx	13,s
   A0C1 4F            [ 1] 1565 	clra
   A0C2 F7            [ 2] 1566 	sta	,x
                           1567 ;tables.c:97: *idxHigh = 0;
   A0C3 8A            [ 2] 1568 	pulh
   A0C4 88            [ 2] 1569 	pulx
   A0C5 89            [ 2] 1570 	pshx
   A0C6 8B            [ 2] 1571 	pshh
   A0C7 F7            [ 2] 1572 	sta	,x
                           1573 ;tables.c:98: return;
   A0C8 CC A1 6B      [ 3] 1574 	jmp	00111$
   A0CB                    1575 00102$:
                           1576 ;tables.c:100: if (value >= table->axisY[TABLE_SIZE_Y - 1]) {
   A0CB 95            [ 2] 1577 	tsx
   A0CC E6 05         [ 3] 1578 	lda	5,x
   A0CE AB 18         [ 2] 1579 	add	#0x18
   A0D0 E7 03         [ 3] 1580 	sta	3,x
   A0D2 E6 04         [ 3] 1581 	lda	4,x
   A0D4 A9 00         [ 2] 1582 	adc	#0
   A0D6 E7 02         [ 3] 1583 	sta	2,x
   A0D8 E6 02         [ 3] 1584 	lda	2,x
   A0DA E7 09         [ 3] 1585 	sta	9,x
   A0DC E6 03         [ 3] 1586 	lda	3,x
   A0DE E7 0A         [ 3] 1587 	sta	10,x
   A0E0 E6 09         [ 3] 1588 	lda	9,x
   A0E2 87            [ 2] 1589 	psha
   A0E3 8A            [ 2] 1590 	pulh
   A0E4 9E EE 0B      [ 4] 1591 	ldx	11,s
   A0E7 E6 0B         [ 3] 1592 	lda	11,x
   A0E9 9E E1 10      [ 4] 1593 	cmp	16,s
   A0EC 22 12         [ 3] 1594 	bhi	00104$
                           1595 ;tables.c:101: *idxLow = TABLE_SIZE_Y - 1;
   A0EE 9E E6 0C      [ 4] 1596 	lda	12,s
   A0F1 87            [ 2] 1597 	psha
   A0F2 8A            [ 2] 1598 	pulh
   A0F3 9E EE 0D      [ 4] 1599 	ldx	13,s
   A0F6 A6 0B         [ 2] 1600 	lda	#0x0b
   A0F8 F7            [ 2] 1601 	sta	,x
                           1602 ;tables.c:102: *idxHigh = TABLE_SIZE_Y - 1;
   A0F9 8A            [ 2] 1603 	pulh
   A0FA 88            [ 2] 1604 	pulx
   A0FB 89            [ 2] 1605 	pshx
   A0FC 8B            [ 2] 1606 	pshh
   A0FD F7            [ 2] 1607 	sta	,x
                           1608 ;tables.c:103: return;
   A0FE 20 6B         [ 3] 1609 	bra	00111$
   A100                    1610 00104$:
                           1611 ;tables.c:106: for (i = 0; i < TABLE_SIZE_Y - 1; i++) {
   A100 95            [ 2] 1612 	tsx
   A101 4F            [ 1] 1613 	clra
   A102 E7 09         [ 3] 1614 	sta	9,x
   A104 E6 02         [ 3] 1615 	lda	2,x
   A106 E7 07         [ 3] 1616 	sta	7,x
   A108 E6 03         [ 3] 1617 	lda	3,x
   A10A E7 08         [ 3] 1618 	sta	8,x
   A10C 4F            [ 1] 1619 	clra
   A10D E7 06         [ 3] 1620 	sta	6,x
   A10F                    1621 00109$:
                           1622 ;tables.c:107: if (value >= table->axisY[i] && value < table->axisY[i + 1]) {
   A10F 9E E6 07      [ 4] 1623 	lda	7,s
   A112 9E EB 04      [ 4] 1624 	add	4,s
   A115 97            [ 1] 1625 	tax
   A116 A6 00         [ 2] 1626 	lda	#0x00
   A118 9E E9 03      [ 4] 1627 	adc	3,s
   A11B 87            [ 2] 1628 	psha
   A11C 8A            [ 2] 1629 	pulh
   A11D FE            [ 2] 1630 	ldx	,x
   A11E 9E E3 10      [ 4] 1631 	cpx	16,s
   A121 22 2B         [ 3] 1632 	bhi	00110$
   A123 9E E6 07      [ 4] 1633 	lda	7,s
   A126 4C            [ 1] 1634 	inca
   A127 87            [ 2] 1635 	psha
   A128 9E EB 0A      [ 4] 1636 	add	10,s
   A12B 97            [ 1] 1637 	tax
   A12C 4F            [ 1] 1638 	clra
   A12D 9E E9 09      [ 4] 1639 	adc	9,s
   A130 87            [ 2] 1640 	psha
   A131 8A            [ 2] 1641 	pulh
   A132 86            [ 2] 1642 	pula
   A133 FE            [ 2] 1643 	ldx	,x
   A134 9E E3 10      [ 4] 1644 	cpx	16,s
   A137 23 15         [ 3] 1645 	bls	00110$
                           1646 ;tables.c:108: *idxLow = i;
   A139 87            [ 2] 1647 	psha
   A13A 9E E6 0D      [ 4] 1648 	lda	13,s
   A13D 87            [ 2] 1649 	psha
   A13E 8A            [ 2] 1650 	pulh
   A13F 9E EE 0E      [ 4] 1651 	ldx	14,s
   A142 9E E6 0B      [ 4] 1652 	lda	11,s
   A145 F7            [ 2] 1653 	sta	,x
   A146 86            [ 2] 1654 	pula
                           1655 ;tables.c:109: *idxHigh = i + 1;
   A147 8A            [ 2] 1656 	pulh
   A148 88            [ 2] 1657 	pulx
   A149 89            [ 2] 1658 	pshx
   A14A 8B            [ 2] 1659 	pshh
   A14B F7            [ 2] 1660 	sta	,x
                           1661 ;tables.c:110: return;
   A14C 20 1D         [ 3] 1662 	bra	00111$
   A14E                    1663 00110$:
                           1664 ;tables.c:106: for (i = 0; i < TABLE_SIZE_Y - 1; i++) {
   A14E 95            [ 2] 1665 	tsx
   A14F 6C 06         [ 4] 1666 	inc	6,x
   A151 E6 06         [ 3] 1667 	lda	6,x
   A153 E7 09         [ 3] 1668 	sta	9,x
   A155 E6 06         [ 3] 1669 	lda	6,x
   A157 A1 0B         [ 2] 1670 	cmp	#0x0b
   A159 25 B4         [ 3] 1671 	bcs	00109$
                           1672 ;tables.c:114: *idxLow = TABLE_SIZE_Y - 2;
   A15B E6 0B         [ 3] 1673 	lda	11,x
   A15D 87            [ 2] 1674 	psha
   A15E 8A            [ 2] 1675 	pulh
   A15F 9E EE 0D      [ 4] 1676 	ldx	13,s
   A162 A6 0A         [ 2] 1677 	lda	#0x0a
   A164 F7            [ 2] 1678 	sta	,x
                           1679 ;tables.c:115: *idxHigh = TABLE_SIZE_Y - 1;
   A165 8A            [ 2] 1680 	pulh
   A166 88            [ 2] 1681 	pulx
   A167 89            [ 2] 1682 	pshx
   A168 8B            [ 2] 1683 	pshh
   A169 4C            [ 1] 1684 	inca
   A16A F7            [ 2] 1685 	sta	,x
   A16B                    1686 00111$:
                           1687 ;tables.c:116: }
   A16B A7 0D         [ 2] 1688 	ais	#13
   A16D 81            [ 4] 1689 	rts
                           1690 ;------------------------------------------------------------
                           1691 ;Allocation info for local variables in function 'lookupCurveU8'
                           1692 ;------------------------------------------------------------
                           1693 ;values                    Allocated to stack - sp +34
                           1694 ;size                      Allocated to stack - sp +36
                           1695 ;x                         Allocated to stack - sp +37
                           1696 ;bins                      Allocated to stack - sp +29
                           1697 ;i                         Allocated to stack - sp +31
                           1698 ;__3276800036              Allocated to stack - sp +19
                           1699 ;__3276800037              Allocated to registers a x 
                           1700 ;__3276800038              Allocated to stack - sp +27
                           1701 ;__3276800039              Allocated to stack - sp +25
                           1702 ;__3276800040              Allocated to stack - sp +23
                           1703 ;__3276800041              Allocated to stack - sp +21
                           1704 ;x                         Allocated to registers 
                           1705 ;x1                        Allocated to registers 
                           1706 ;x2                        Allocated to registers 
                           1707 ;y1                        Allocated to registers 
                           1708 ;y2                        Allocated to registers 
                           1709 ;sloc0                     Allocated to stack - sp +1
                           1710 ;sloc1                     Allocated to stack - sp +11
                           1711 ;sloc2                     Allocated to stack - sp +13
                           1712 ;sloc3                     Allocated to stack - sp +15
                           1713 ;sloc4                     Allocated to stack - sp +17
                           1714 ;sloc5                     Allocated to stack - sp +19
                           1715 ;sloc6                     Allocated to stack - sp +3
                           1716 ;sloc7                     Allocated to stack - sp +7
                           1717 ;------------------------------------------------------------
                           1718 ;tables.c:118: uint8_t lookupCurveU8(const int8_t *bins, const uint8_t *values, uint8_t size, int16_t x) {
                           1719 ;	-----------------------------------------
                           1720 ;	 function lookupCurveU8
                           1721 ;	-----------------------------------------
                           1722 ;	Register assignment might be sub-optimal.
                           1723 ;	Stack space usage: 31 bytes.
   A16E                    1724 _lookupCurveU8:
   A16E A7 E1         [ 2] 1725 	ais	#-31
   A170 9E E7 1E      [ 4] 1726 	sta	30,s
   A173 9E EF 1D      [ 4] 1727 	stx	29,s
                           1728 ;tables.c:120: if (size == 0) return 0;
   A176 9E 6D 24      [ 4] 1729 	tst	36,s
   A179 26 04         [ 3] 1730 	bne	00102$
   A17B 4F            [ 1] 1731 	clra
   A17C CC A3 97      [ 3] 1732 	jmp	00117$
   A17F                    1733 00102$:
                           1734 ;tables.c:121: if (x <= bins[0]) return values[0];
   A17F 9E E6 1D      [ 4] 1735 	lda	29,s
   A182 87            [ 2] 1736 	psha
   A183 8A            [ 2] 1737 	pulh
   A184 9E EE 1E      [ 4] 1738 	ldx	30,s
   A187 F6            [ 2] 1739 	lda	,x
   A188 87            [ 2] 1740 	psha
   A189 49            [ 1] 1741 	rola	
   A18A 4F            [ 1] 1742 	clra	
   A18B A2 00         [ 2] 1743 	sbc	#0x00
   A18D 97            [ 1] 1744 	tax
   A18E 86            [ 2] 1745 	pula
   A18F 9E E0 26      [ 4] 1746 	sub	38,s
   A192 9F            [ 1] 1747 	txa
   A193 9E E2 25      [ 4] 1748 	sbc	37,s
   A196 91 0C         [ 3] 1749 	blt	00104$
   A198 95            [ 2] 1750 	tsx
   A199 E6 21         [ 3] 1751 	lda	33,x
   A19B 87            [ 2] 1752 	psha
   A19C 8A            [ 2] 1753 	pulh
   A19D 9E EE 23      [ 4] 1754 	ldx	35,s
   A1A0 F6            [ 2] 1755 	lda	,x
   A1A1 CC A3 97      [ 3] 1756 	jmp	00117$
   A1A4                    1757 00104$:
                           1758 ;tables.c:122: if (x >= bins[size - 1]) return values[size - 1];
   A1A4 9E EE 24      [ 4] 1759 	ldx	36,s
   A1A7 8C            [ 1] 1760 	clrh
   A1A8 AF FF         [ 2] 1761 	aix	#-1
   A1AA 8B            [ 2] 1762 	pshh
   A1AB 86            [ 2] 1763 	pula
   A1AC 9E E7 01      [ 4] 1764 	sta	1,s
   A1AF 9E EF 02      [ 4] 1765 	stx	2,s
   A1B2 9E E6 02      [ 4] 1766 	lda	2,s
   A1B5 9E EB 1E      [ 4] 1767 	add	30,s
   A1B8 97            [ 1] 1768 	tax
   A1B9 9E E6 01      [ 4] 1769 	lda	1,s
   A1BC 9E E9 1D      [ 4] 1770 	adc	29,s
   A1BF 87            [ 2] 1771 	psha
   A1C0 8A            [ 2] 1772 	pulh
   A1C1 F6            [ 2] 1773 	lda	,x
   A1C2 95            [ 2] 1774 	tsx
   A1C3 E7 0B         [ 3] 1775 	sta	11,x
   A1C5 49            [ 1] 1776 	rola	
   A1C6 4F            [ 1] 1777 	clra	
   A1C7 A2 00         [ 2] 1778 	sbc	#0x00
   A1C9 E7 0A         [ 3] 1779 	sta	10,x
   A1CB E6 01         [ 3] 1780 	lda	1,x
   A1CD EB 22         [ 3] 1781 	add	34,x
   A1CF E7 0D         [ 3] 1782 	sta	13,x
   A1D1 F6            [ 2] 1783 	lda	,x
   A1D2 E9 21         [ 3] 1784 	adc	33,x
   A1D4 E7 0C         [ 3] 1785 	sta	12,x
   A1D6 E6 25         [ 3] 1786 	lda	37,x
   A1D8 E0 0B         [ 3] 1787 	sub	11,x
   A1DA E6 24         [ 3] 1788 	lda	36,x
   A1DC E2 0A         [ 3] 1789 	sbc	10,x
   A1DE 91 0B         [ 3] 1790 	blt	00106$
   A1E0 E6 0C         [ 3] 1791 	lda	12,x
   A1E2 87            [ 2] 1792 	psha
   A1E3 8A            [ 2] 1793 	pulh
   A1E4 9E EE 0E      [ 4] 1794 	ldx	14,s
   A1E7 F6            [ 2] 1795 	lda	,x
   A1E8 CC A3 97      [ 3] 1796 	jmp	00117$
   A1EB                    1797 00106$:
                           1798 ;tables.c:124: for (i = 0; i < size - 1; i++) {
   A1EB 95            [ 2] 1799 	tsx
   A1EC 4F            [ 1] 1800 	clra
   A1ED E7 0A         [ 3] 1801 	sta	10,x
   A1EF E7 1E         [ 3] 1802 	sta	30,x
   A1F1                    1803 00115$:
   A1F1 95            [ 2] 1804 	tsx
   A1F2 E6 1E         [ 3] 1805 	lda	30,x
   A1F4 E7 0F         [ 3] 1806 	sta	15,x
   A1F6 4F            [ 1] 1807 	clra
   A1F7 E7 0E         [ 3] 1808 	sta	14,x
   A1F9 E6 0F         [ 3] 1809 	lda	15,x
   A1FB E0 01         [ 3] 1810 	sub	1,x
   A1FD E6 0E         [ 3] 1811 	lda	14,x
   A1FF F2            [ 2] 1812 	sbc	,x
   A200 91 03         [ 3] 1813 	blt	00162$
   A202 CC A3 8E      [ 3] 1814 	jmp	00110$
   A205                    1815 00162$:
                           1816 ;tables.c:125: if (x >= bins[i] && x < bins[i + 1]) {
   A205 E6 1E         [ 3] 1817 	lda	30,x
   A207 EB 1D         [ 3] 1818 	add	29,x
   A209 97            [ 1] 1819 	tax
   A20A A6 00         [ 2] 1820 	lda	#0x00
   A20C 9E E9 1D      [ 4] 1821 	adc	29,s
   A20F 87            [ 2] 1822 	psha
   A210 8A            [ 2] 1823 	pulh
   A211 F6            [ 2] 1824 	lda	,x
   A212 95            [ 2] 1825 	tsx
   A213 E7 11         [ 3] 1826 	sta	17,x
   A215 49            [ 1] 1827 	rola	
   A216 4F            [ 1] 1828 	clra	
   A217 A2 00         [ 2] 1829 	sbc	#0x00
   A219 E7 10         [ 3] 1830 	sta	16,x
   A21B E6 25         [ 3] 1831 	lda	37,x
   A21D E0 11         [ 3] 1832 	sub	17,x
   A21F E6 24         [ 3] 1833 	lda	36,x
   A221 E2 10         [ 3] 1834 	sbc	16,x
   A223 90 03         [ 3] 1835 	bge	00163$
   A225 CC A3 84      [ 3] 1836 	jmp	00116$
   A228                    1837 00163$:
   A228 6C 0F         [ 4] 1838 	inc	15,x
   A22A 26 02         [ 3] 1839 	bne	00164$
   A22C 6C 0E         [ 4] 1840 	inc	14,x
   A22E                    1841 00164$:
   A22E E6 0F         [ 3] 1842 	lda	15,x
   A230 EB 1D         [ 3] 1843 	add	29,x
   A232 97            [ 1] 1844 	tax
   A233 9E E6 0F      [ 4] 1845 	lda	15,s
   A236 9E E9 1D      [ 4] 1846 	adc	29,s
   A239 87            [ 2] 1847 	psha
   A23A 8A            [ 2] 1848 	pulh
   A23B F6            [ 2] 1849 	lda	,x
   A23C 95            [ 2] 1850 	tsx
   A23D E7 13         [ 3] 1851 	sta	19,x
   A23F 49            [ 1] 1852 	rola	
   A240 4F            [ 1] 1853 	clra	
   A241 A2 00         [ 2] 1854 	sbc	#0x00
   A243 E7 12         [ 3] 1855 	sta	18,x
   A245 E6 25         [ 3] 1856 	lda	37,x
   A247 E0 13         [ 3] 1857 	sub	19,x
   A249 E6 24         [ 3] 1858 	lda	36,x
   A24B E2 12         [ 3] 1859 	sbc	18,x
   A24D 91 03         [ 3] 1860 	blt	00165$
   A24F CC A3 84      [ 3] 1861 	jmp	00116$
   A252                    1862 00165$:
                           1863 ;tables.c:126: return (uint8_t)interpolate(x, bins[i], bins[i + 1], values[i], values[i + 1]);
   A252 E6 0F         [ 3] 1864 	lda	15,x
   A254 EB 22         [ 3] 1865 	add	34,x
   A256 97            [ 1] 1866 	tax
   A257 9E E6 0F      [ 4] 1867 	lda	15,s
   A25A 9E E9 22      [ 4] 1868 	adc	34,s
   A25D 87            [ 2] 1869 	psha
   A25E 8A            [ 2] 1870 	pulh
   A25F F6            [ 2] 1871 	lda	,x
   A260 95            [ 2] 1872 	tsx
   A261 E7 15         [ 3] 1873 	sta	21,x
   A263 5F            [ 1] 1874 	clrx
   A264 9E EF 15      [ 4] 1875 	stx	21,s
   A267 9E E6 0B      [ 4] 1876 	lda	11,s
   A26A 9E EB 23      [ 4] 1877 	add	35,s
   A26D 97            [ 1] 1878 	tax
   A26E A6 00         [ 2] 1879 	lda	#0x00
   A270 9E E9 22      [ 4] 1880 	adc	34,s
   A273 87            [ 2] 1881 	psha
   A274 8A            [ 2] 1882 	pulh
   A275 F6            [ 2] 1883 	lda	,x
   A276 95            [ 2] 1884 	tsx
   A277 E7 17         [ 3] 1885 	sta	23,x
   A279 5F            [ 1] 1886 	clrx
   A27A 9E EF 17      [ 4] 1887 	stx	23,s
   A27D 95            [ 2] 1888 	tsx
   A27E E6 12         [ 3] 1889 	lda	18,x
   A280 E7 18         [ 3] 1890 	sta	24,x
   A282 E6 13         [ 3] 1891 	lda	19,x
   A284 E7 19         [ 3] 1892 	sta	25,x
   A286 E6 10         [ 3] 1893 	lda	16,x
   A288 E7 1A         [ 3] 1894 	sta	26,x
   A28A E6 11         [ 3] 1895 	lda	17,x
   A28C E7 1B         [ 3] 1896 	sta	27,x
   A28E EE 24         [ 3] 1897 	ldx	36,x
   A290 9E E6 26      [ 4] 1898 	lda	38,s
                           1899 ;tables.h:34: if (x2 == x1) return y1;
   A293 87            [ 2] 1900 	psha
   A294 9E E6 1B      [ 4] 1901 	lda	27,s
   A297 9E E1 1D      [ 4] 1902 	cmp	29,s
   A29A 86            [ 2] 1903 	pula
   A29B 26 0A         [ 3] 1904 	bne	00166$
   A29D 87            [ 2] 1905 	psha
   A29E 9E E6 1A      [ 4] 1906 	lda	26,s
   A2A1 9E E1 1C      [ 4] 1907 	cmp	28,s
   A2A4 86            [ 2] 1908 	pula
   A2A5 27 02         [ 3] 1909 	beq	00167$
   A2A7                    1910 00166$:
   A2A7 20 0C         [ 3] 1911 	bra	00112$
   A2A9                    1912 00167$:
   A2A9 95            [ 2] 1913 	tsx
   A2AA E6 16         [ 3] 1914 	lda	22,x
   A2AC E7 12         [ 3] 1915 	sta	18,x
   A2AE E6 17         [ 3] 1916 	lda	23,x
   A2B0 E7 13         [ 3] 1917 	sta	19,x
   A2B2 CC A3 7F      [ 3] 1918 	jmp	00113$
   A2B5                    1919 00112$:
                           1920 ;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
   A2B5 9E E0 1C      [ 4] 1921 	sub	28,s
   A2B8 87            [ 2] 1922 	psha
   A2B9 9F            [ 1] 1923 	txa
   A2BA 9E E2 1C      [ 4] 1924 	sbc	28,s
   A2BD 97            [ 1] 1925 	tax
   A2BE 86            [ 2] 1926 	pula
   A2BF 9E E7 06      [ 4] 1927 	sta	6,s
   A2C2 9F            [ 1] 1928 	txa
   A2C3 9E E7 05      [ 4] 1929 	sta	5,s
   A2C6 49            [ 1] 1930 	rola	
   A2C7 4F            [ 1] 1931 	clra	
   A2C8 A2 00         [ 2] 1932 	sbc	#0x00
   A2CA 9E E7 04      [ 4] 1933 	sta	4,s
   A2CD 9E E7 03      [ 4] 1934 	sta	3,s
   A2D0 9E E6 16      [ 4] 1935 	lda	22,s
   A2D3 9E E0 18      [ 4] 1936 	sub	24,s
   A2D6 87            [ 2] 1937 	psha
   A2D7 9E E6 16      [ 4] 1938 	lda	22,s
   A2DA 9E E2 18      [ 4] 1939 	sbc	24,s
   A2DD 97            [ 1] 1940 	tax
   A2DE 86            [ 2] 1941 	pula
   A2DF 9E E7 0A      [ 4] 1942 	sta	10,s
   A2E2 9F            [ 1] 1943 	txa
   A2E3 9E E7 09      [ 4] 1944 	sta	9,s
   A2E6 49            [ 1] 1945 	rola	
   A2E7 4F            [ 1] 1946 	clra	
   A2E8 A2 00         [ 2] 1947 	sbc	#0x00
   A2EA 9E E7 08      [ 4] 1948 	sta	8,s
   A2ED 9E E7 07      [ 4] 1949 	sta	7,s
   A2F0 95            [ 2] 1950 	tsx
   A2F1 E6 09         [ 3] 1951 	lda	9,x
   A2F3 87            [ 2] 1952 	psha
   A2F4 E6 08         [ 3] 1953 	lda	8,x
   A2F6 87            [ 2] 1954 	psha
   A2F7 E6 07         [ 3] 1955 	lda	7,x
   A2F9 87            [ 2] 1956 	psha
   A2FA E6 06         [ 3] 1957 	lda	6,x
   A2FC 87            [ 2] 1958 	psha
   A2FD E6 05         [ 3] 1959 	lda	5,x
   A2FF 87            [ 2] 1960 	psha
   A300 E6 04         [ 3] 1961 	lda	4,x
   A302 87            [ 2] 1962 	psha
   A303 E6 03         [ 3] 1963 	lda	3,x
   A305 87            [ 2] 1964 	psha
   A306 E6 02         [ 3] 1965 	lda	2,x
   A308 87            [ 2] 1966 	psha
   A309 CD D0 87      [ 5] 1967 	jsr	__mullong
   A30C 9E E7 12      [ 4] 1968 	sta	18,s
   A30F 9E EF 11      [ 4] 1969 	stx	17,s
   A312 B6 4A         [ 3] 1970 	lda	*___SDCC_hc08_ret2
   A314 9E E7 10      [ 4] 1971 	sta	16,s
   A317 B6 4B         [ 3] 1972 	lda	*___SDCC_hc08_ret3
   A319 9E E7 0F      [ 4] 1973 	sta	15,s
   A31C A7 08         [ 2] 1974 	ais	#8
   A31E 9E E6 1A      [ 4] 1975 	lda	26,s
   A321 9E E0 1C      [ 4] 1976 	sub	28,s
   A324 87            [ 2] 1977 	psha
   A325 9E E6 1A      [ 4] 1978 	lda	26,s
   A328 9E E2 1C      [ 4] 1979 	sbc	28,s
   A32B 97            [ 1] 1980 	tax
   A32C 86            [ 2] 1981 	pula
   A32D 9E E7 06      [ 4] 1982 	sta	6,s
   A330 9F            [ 1] 1983 	txa
   A331 9E E7 05      [ 4] 1984 	sta	5,s
   A334 49            [ 1] 1985 	rola	
   A335 4F            [ 1] 1986 	clra	
   A336 A2 00         [ 2] 1987 	sbc	#0x00
   A338 9E E7 04      [ 4] 1988 	sta	4,s
   A33B 9E E7 03      [ 4] 1989 	sta	3,s
   A33E 95            [ 2] 1990 	tsx
   A33F E6 05         [ 3] 1991 	lda	5,x
   A341 87            [ 2] 1992 	psha
   A342 E6 04         [ 3] 1993 	lda	4,x
   A344 87            [ 2] 1994 	psha
   A345 E6 03         [ 3] 1995 	lda	3,x
   A347 87            [ 2] 1996 	psha
   A348 E6 02         [ 3] 1997 	lda	2,x
   A34A 87            [ 2] 1998 	psha
   A34B E6 09         [ 3] 1999 	lda	9,x
   A34D 87            [ 2] 2000 	psha
   A34E E6 08         [ 3] 2001 	lda	8,x
   A350 87            [ 2] 2002 	psha
   A351 E6 07         [ 3] 2003 	lda	7,x
   A353 87            [ 2] 2004 	psha
   A354 E6 06         [ 3] 2005 	lda	6,x
   A356 87            [ 2] 2006 	psha
   A357 CD CE 92      [ 5] 2007 	jsr	__divslong
   A35A 9E E7 12      [ 4] 2008 	sta	18,s
   A35D 9E EF 11      [ 4] 2009 	stx	17,s
   A360 B6 4A         [ 3] 2010 	lda	*___SDCC_hc08_ret2
   A362 9E E7 10      [ 4] 2011 	sta	16,s
   A365 B6 4B         [ 3] 2012 	lda	*___SDCC_hc08_ret3
   A367 9E E7 0F      [ 4] 2013 	sta	15,s
   A36A A7 08         [ 2] 2014 	ais	#8
   A36C 9E E6 0A      [ 4] 2015 	lda	10,s
   A36F 9E EE 09      [ 4] 2016 	ldx	9,s
   A372 9E EB 18      [ 4] 2017 	add	24,s
   A375 9E E7 14      [ 4] 2018 	sta	20,s
   A378 9F            [ 1] 2019 	txa
   A379 9E E9 17      [ 4] 2020 	adc	23,s
   A37C 9E E7 13      [ 4] 2021 	sta	19,s
                           2022 ;tables.c:126: return (uint8_t)interpolate(x, bins[i], bins[i + 1], values[i], values[i + 1]);
   A37F                    2023 00113$:
   A37F 95            [ 2] 2024 	tsx
   A380 E6 13         [ 3] 2025 	lda	19,x
   A382 20 13         [ 3] 2026 	bra	00117$
   A384                    2027 00116$:
                           2028 ;tables.c:124: for (i = 0; i < size - 1; i++) {
   A384 95            [ 2] 2029 	tsx
   A385 6C 1E         [ 4] 2030 	inc	30,x
   A387 E6 1E         [ 3] 2031 	lda	30,x
   A389 E7 0A         [ 3] 2032 	sta	10,x
   A38B CC A1 F1      [ 3] 2033 	jmp	00115$
   A38E                    2034 00110$:
                           2035 ;tables.c:129: return values[size - 1];
   A38E 9E E6 0D      [ 4] 2036 	lda	13,s
   A391 87            [ 2] 2037 	psha
   A392 8A            [ 2] 2038 	pulh
   A393 9E EE 0E      [ 4] 2039 	ldx	14,s
   A396 F6            [ 2] 2040 	lda	,x
   A397                    2041 00117$:
                           2042 ;tables.c:130: }
   A397 A7 1F         [ 2] 2043 	ais	#31
   A399 81            [ 4] 2044 	rts
                           2045 ;------------------------------------------------------------
                           2046 ;Allocation info for local variables in function 'lookupCurveI8'
                           2047 ;------------------------------------------------------------
                           2048 ;values                    Allocated to stack - sp +34
                           2049 ;size                      Allocated to stack - sp +36
                           2050 ;x                         Allocated to stack - sp +37
                           2051 ;bins                      Allocated to stack - sp +24
                           2052 ;i                         Allocated to stack - sp +23
                           2053 ;__3276800043              Allocated to stack - sp +19
                           2054 ;__3276800044              Allocated to registers a x 
                           2055 ;__3276800045              Allocated to stack - sp +26
                           2056 ;__3276800046              Allocated to stack - sp +21
                           2057 ;__3276800047              Allocated to stack - sp +28
                           2058 ;__3276800048              Allocated to stack - sp +30
                           2059 ;x                         Allocated to registers 
                           2060 ;x1                        Allocated to registers 
                           2061 ;x2                        Allocated to registers 
                           2062 ;y1                        Allocated to registers 
                           2063 ;y2                        Allocated to registers 
                           2064 ;sloc0                     Allocated to stack - sp +17
                           2065 ;sloc1                     Allocated to stack - sp +15
                           2066 ;sloc2                     Allocated to stack - sp +13
                           2067 ;sloc3                     Allocated to stack - sp +9
                           2068 ;sloc4                     Allocated to stack - sp +11
                           2069 ;sloc5                     Allocated to stack - sp +19
                           2070 ;sloc6                     Allocated to stack - sp +5
                           2071 ;sloc7                     Allocated to stack - sp +1
                           2072 ;------------------------------------------------------------
                           2073 ;tables.c:132: int8_t lookupCurveI8(const uint8_t *bins, const int8_t *values, uint8_t size, int16_t x) {
                           2074 ;	-----------------------------------------
                           2075 ;	 function lookupCurveI8
                           2076 ;	-----------------------------------------
                           2077 ;	Register assignment might be sub-optimal.
                           2078 ;	Stack space usage: 31 bytes.
   A39A                    2079 _lookupCurveI8:
   A39A A7 E1         [ 2] 2080 	ais	#-31
   A39C 9E E7 19      [ 4] 2081 	sta	25,s
   A39F 9E EF 18      [ 4] 2082 	stx	24,s
                           2083 ;tables.c:134: if (size == 0) return 0;
   A3A2 9E 6D 24      [ 4] 2084 	tst	36,s
   A3A5 26 04         [ 3] 2085 	bne	00102$
   A3A7 4F            [ 1] 2086 	clra
   A3A8 CC A5 BB      [ 3] 2087 	jmp	00117$
   A3AB                    2088 00102$:
                           2089 ;tables.c:135: if (x <= (int16_t)bins[0]) return values[0];
   A3AB 9E E6 18      [ 4] 2090 	lda	24,s
   A3AE 87            [ 2] 2091 	psha
   A3AF 8A            [ 2] 2092 	pulh
   A3B0 9E EE 19      [ 4] 2093 	ldx	25,s
   A3B3 F6            [ 2] 2094 	lda	,x
   A3B4 5F            [ 1] 2095 	clrx
   A3B5 9E E0 26      [ 4] 2096 	sub	38,s
   A3B8 9F            [ 1] 2097 	txa
   A3B9 9E E2 25      [ 4] 2098 	sbc	37,s
   A3BC 91 0C         [ 3] 2099 	blt	00104$
   A3BE 95            [ 2] 2100 	tsx
   A3BF E6 21         [ 3] 2101 	lda	33,x
   A3C1 87            [ 2] 2102 	psha
   A3C2 8A            [ 2] 2103 	pulh
   A3C3 9E EE 23      [ 4] 2104 	ldx	35,s
   A3C6 F6            [ 2] 2105 	lda	,x
   A3C7 CC A5 BB      [ 3] 2106 	jmp	00117$
   A3CA                    2107 00104$:
                           2108 ;tables.c:136: if (x >= (int16_t)bins[size - 1]) return values[size - 1];
   A3CA 9E EE 24      [ 4] 2109 	ldx	36,s
   A3CD 8C            [ 1] 2110 	clrh
   A3CE AF FF         [ 2] 2111 	aix	#-1
   A3D0 8B            [ 2] 2112 	pshh
   A3D1 86            [ 2] 2113 	pula
   A3D2 9E E7 11      [ 4] 2114 	sta	17,s
   A3D5 9E EF 12      [ 4] 2115 	stx	18,s
   A3D8 9E E6 12      [ 4] 2116 	lda	18,s
   A3DB 9E EB 19      [ 4] 2117 	add	25,s
   A3DE 97            [ 1] 2118 	tax
   A3DF 9E E6 11      [ 4] 2119 	lda	17,s
   A3E2 9E E9 18      [ 4] 2120 	adc	24,s
   A3E5 87            [ 2] 2121 	psha
   A3E6 8A            [ 2] 2122 	pulh
   A3E7 F6            [ 2] 2123 	lda	,x
   A3E8 95            [ 2] 2124 	tsx
   A3E9 E7 0F         [ 3] 2125 	sta	15,x
   A3EB 5F            [ 1] 2126 	clrx
   A3EC 9E EF 0F      [ 4] 2127 	stx	15,s
   A3EF 95            [ 2] 2128 	tsx
   A3F0 E6 11         [ 3] 2129 	lda	17,x
   A3F2 EB 22         [ 3] 2130 	add	34,x
   A3F4 E7 0D         [ 3] 2131 	sta	13,x
   A3F6 E6 10         [ 3] 2132 	lda	16,x
   A3F8 E9 21         [ 3] 2133 	adc	33,x
   A3FA E7 0C         [ 3] 2134 	sta	12,x
   A3FC E6 25         [ 3] 2135 	lda	37,x
   A3FE E0 0F         [ 3] 2136 	sub	15,x
   A400 E6 24         [ 3] 2137 	lda	36,x
   A402 E2 0E         [ 3] 2138 	sbc	14,x
   A404 91 0B         [ 3] 2139 	blt	00106$
   A406 E6 0C         [ 3] 2140 	lda	12,x
   A408 87            [ 2] 2141 	psha
   A409 8A            [ 2] 2142 	pulh
   A40A 9E EE 0E      [ 4] 2143 	ldx	14,s
   A40D F6            [ 2] 2144 	lda	,x
   A40E CC A5 BB      [ 3] 2145 	jmp	00117$
   A411                    2146 00106$:
                           2147 ;tables.c:138: for (i = 0; i < size - 1; i++) {
   A411 95            [ 2] 2148 	tsx
   A412 4F            [ 1] 2149 	clra
   A413 E7 0E         [ 3] 2150 	sta	14,x
   A415 E7 16         [ 3] 2151 	sta	22,x
   A417                    2152 00115$:
   A417 95            [ 2] 2153 	tsx
   A418 E6 16         [ 3] 2154 	lda	22,x
   A41A E7 09         [ 3] 2155 	sta	9,x
   A41C 4F            [ 1] 2156 	clra
   A41D E7 08         [ 3] 2157 	sta	8,x
   A41F E6 09         [ 3] 2158 	lda	9,x
   A421 E0 11         [ 3] 2159 	sub	17,x
   A423 E6 08         [ 3] 2160 	lda	8,x
   A425 E2 10         [ 3] 2161 	sbc	16,x
   A427 91 03         [ 3] 2162 	blt	00162$
   A429 CC A5 B2      [ 3] 2163 	jmp	00110$
   A42C                    2164 00162$:
                           2165 ;tables.c:139: if (x >= (int16_t)bins[i] && x < (int16_t)bins[i + 1]) {
   A42C E6 16         [ 3] 2166 	lda	22,x
   A42E EB 18         [ 3] 2167 	add	24,x
   A430 97            [ 1] 2168 	tax
   A431 A6 00         [ 2] 2169 	lda	#0x00
   A433 9E E9 18      [ 4] 2170 	adc	24,s
   A436 87            [ 2] 2171 	psha
   A437 8A            [ 2] 2172 	pulh
   A438 F6            [ 2] 2173 	lda	,x
   A439 95            [ 2] 2174 	tsx
   A43A E7 0B         [ 3] 2175 	sta	11,x
   A43C 5F            [ 1] 2176 	clrx
   A43D 9E EF 0B      [ 4] 2177 	stx	11,s
   A440 95            [ 2] 2178 	tsx
   A441 E6 25         [ 3] 2179 	lda	37,x
   A443 E0 0B         [ 3] 2180 	sub	11,x
   A445 E6 24         [ 3] 2181 	lda	36,x
   A447 E2 0A         [ 3] 2182 	sbc	10,x
   A449 90 03         [ 3] 2183 	bge	00163$
   A44B CC A5 A8      [ 3] 2184 	jmp	00116$
   A44E                    2185 00163$:
   A44E 6C 09         [ 4] 2186 	inc	9,x
   A450 26 02         [ 3] 2187 	bne	00164$
   A452 6C 08         [ 4] 2188 	inc	8,x
   A454                    2189 00164$:
   A454 E6 09         [ 3] 2190 	lda	9,x
   A456 EB 18         [ 3] 2191 	add	24,x
   A458 97            [ 1] 2192 	tax
   A459 9E E6 09      [ 4] 2193 	lda	9,s
   A45C 9E E9 18      [ 4] 2194 	adc	24,s
   A45F 87            [ 2] 2195 	psha
   A460 8A            [ 2] 2196 	pulh
   A461 F6            [ 2] 2197 	lda	,x
   A462 95            [ 2] 2198 	tsx
   A463 E7 13         [ 3] 2199 	sta	19,x
   A465 5F            [ 1] 2200 	clrx
   A466 9E EF 13      [ 4] 2201 	stx	19,s
   A469 95            [ 2] 2202 	tsx
   A46A E6 25         [ 3] 2203 	lda	37,x
   A46C E0 13         [ 3] 2204 	sub	19,x
   A46E E6 24         [ 3] 2205 	lda	36,x
   A470 E2 12         [ 3] 2206 	sbc	18,x
   A472 91 03         [ 3] 2207 	blt	00165$
   A474 CC A5 A8      [ 3] 2208 	jmp	00116$
   A477                    2209 00165$:
                           2210 ;tables.c:140: return (int8_t)interpolate(x, bins[i], bins[i + 1], values[i], values[i + 1]);
   A477 E6 09         [ 3] 2211 	lda	9,x
   A479 EB 22         [ 3] 2212 	add	34,x
   A47B 97            [ 1] 2213 	tax
   A47C 9E E6 09      [ 4] 2214 	lda	9,s
   A47F 9E E9 22      [ 4] 2215 	adc	34,s
   A482 87            [ 2] 2216 	psha
   A483 8A            [ 2] 2217 	pulh
   A484 F6            [ 2] 2218 	lda	,x
   A485 95            [ 2] 2219 	tsx
   A486 E7 1E         [ 3] 2220 	sta	30,x
   A488 49            [ 1] 2221 	rola	
   A489 4F            [ 1] 2222 	clra	
   A48A A2 00         [ 2] 2223 	sbc	#0x00
   A48C E7 1D         [ 3] 2224 	sta	29,x
   A48E E6 0E         [ 3] 2225 	lda	14,x
   A490 EB 22         [ 3] 2226 	add	34,x
   A492 97            [ 1] 2227 	tax
   A493 A6 00         [ 2] 2228 	lda	#0x00
   A495 9E E9 22      [ 4] 2229 	adc	34,s
   A498 87            [ 2] 2230 	psha
   A499 8A            [ 2] 2231 	pulh
   A49A F6            [ 2] 2232 	lda	,x
   A49B 95            [ 2] 2233 	tsx
   A49C E7 1C         [ 3] 2234 	sta	28,x
   A49E 49            [ 1] 2235 	rola	
   A49F 4F            [ 1] 2236 	clra	
   A4A0 A2 00         [ 2] 2237 	sbc	#0x00
   A4A2 E7 1B         [ 3] 2238 	sta	27,x
   A4A4 E6 12         [ 3] 2239 	lda	18,x
   A4A6 E7 14         [ 3] 2240 	sta	20,x
   A4A8 E6 13         [ 3] 2241 	lda	19,x
   A4AA E7 15         [ 3] 2242 	sta	21,x
   A4AC E6 0A         [ 3] 2243 	lda	10,x
   A4AE E7 19         [ 3] 2244 	sta	25,x
   A4B0 E6 0B         [ 3] 2245 	lda	11,x
   A4B2 E7 1A         [ 3] 2246 	sta	26,x
   A4B4 EE 24         [ 3] 2247 	ldx	36,x
   A4B6 9E E6 26      [ 4] 2248 	lda	38,s
                           2249 ;tables.h:34: if (x2 == x1) return y1;
   A4B9 87            [ 2] 2250 	psha
   A4BA 9E E6 17      [ 4] 2251 	lda	23,s
   A4BD 9E E1 1C      [ 4] 2252 	cmp	28,s
   A4C0 86            [ 2] 2253 	pula
   A4C1 26 0A         [ 3] 2254 	bne	00166$
   A4C3 87            [ 2] 2255 	psha
   A4C4 9E E6 16      [ 4] 2256 	lda	22,s
   A4C7 9E E1 1B      [ 4] 2257 	cmp	27,s
   A4CA 86            [ 2] 2258 	pula
   A4CB 27 02         [ 3] 2259 	beq	00167$
   A4CD                    2260 00166$:
   A4CD 20 0C         [ 3] 2261 	bra	00112$
   A4CF                    2262 00167$:
   A4CF 95            [ 2] 2263 	tsx
   A4D0 E6 1B         [ 3] 2264 	lda	27,x
   A4D2 E7 12         [ 3] 2265 	sta	18,x
   A4D4 E6 1C         [ 3] 2266 	lda	28,x
   A4D6 E7 13         [ 3] 2267 	sta	19,x
   A4D8 CC A5 A3      [ 3] 2268 	jmp	00113$
   A4DB                    2269 00112$:
                           2270 ;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
   A4DB 9E E0 1B      [ 4] 2271 	sub	27,s
   A4DE 87            [ 2] 2272 	psha
   A4DF 9F            [ 1] 2273 	txa
   A4E0 9E E2 1B      [ 4] 2274 	sbc	27,s
   A4E3 97            [ 1] 2275 	tax
   A4E4 86            [ 2] 2276 	pula
   A4E5 9E E7 08      [ 4] 2277 	sta	8,s
   A4E8 9F            [ 1] 2278 	txa
   A4E9 9E E7 07      [ 4] 2279 	sta	7,s
   A4EC 49            [ 1] 2280 	rola	
   A4ED 4F            [ 1] 2281 	clra	
   A4EE A2 00         [ 2] 2282 	sbc	#0x00
   A4F0 9E E7 06      [ 4] 2283 	sta	6,s
   A4F3 9E E7 05      [ 4] 2284 	sta	5,s
   A4F6 9E E6 1F      [ 4] 2285 	lda	31,s
   A4F9 9E E0 1D      [ 4] 2286 	sub	29,s
   A4FC 87            [ 2] 2287 	psha
   A4FD 9E E6 1F      [ 4] 2288 	lda	31,s
   A500 9E E2 1D      [ 4] 2289 	sbc	29,s
   A503 97            [ 1] 2290 	tax
   A504 86            [ 2] 2291 	pula
   A505 9E E7 04      [ 4] 2292 	sta	4,s
   A508 9F            [ 1] 2293 	txa
   A509 9E E7 03      [ 4] 2294 	sta	3,s
   A50C 49            [ 1] 2295 	rola	
   A50D 4F            [ 1] 2296 	clra	
   A50E A2 00         [ 2] 2297 	sbc	#0x00
   A510 9E E7 02      [ 4] 2298 	sta	2,s
   A513 9E E7 01      [ 4] 2299 	sta	1,s
   A516 95            [ 2] 2300 	tsx
   A517 E6 03         [ 3] 2301 	lda	3,x
   A519 87            [ 2] 2302 	psha
   A51A E6 02         [ 3] 2303 	lda	2,x
   A51C 87            [ 2] 2304 	psha
   A51D E6 01         [ 3] 2305 	lda	1,x
   A51F 87            [ 2] 2306 	psha
   A520 F6            [ 2] 2307 	lda	,x
   A521 87            [ 2] 2308 	psha
   A522 E6 07         [ 3] 2309 	lda	7,x
   A524 87            [ 2] 2310 	psha
   A525 E6 06         [ 3] 2311 	lda	6,x
   A527 87            [ 2] 2312 	psha
   A528 E6 05         [ 3] 2313 	lda	5,x
   A52A 87            [ 2] 2314 	psha
   A52B E6 04         [ 3] 2315 	lda	4,x
   A52D 87            [ 2] 2316 	psha
   A52E CD D0 87      [ 5] 2317 	jsr	__mullong
   A531 9E E7 0C      [ 4] 2318 	sta	12,s
   A534 9E EF 0B      [ 4] 2319 	stx	11,s
   A537 B6 4A         [ 3] 2320 	lda	*___SDCC_hc08_ret2
   A539 9E E7 0A      [ 4] 2321 	sta	10,s
   A53C B6 4B         [ 3] 2322 	lda	*___SDCC_hc08_ret3
   A53E 9E E7 09      [ 4] 2323 	sta	9,s
   A541 A7 08         [ 2] 2324 	ais	#8
   A543 9E E6 16      [ 4] 2325 	lda	22,s
   A546 9E E0 1B      [ 4] 2326 	sub	27,s
   A549 87            [ 2] 2327 	psha
   A54A 9E E6 16      [ 4] 2328 	lda	22,s
   A54D 9E E2 1B      [ 4] 2329 	sbc	27,s
   A550 97            [ 1] 2330 	tax
   A551 86            [ 2] 2331 	pula
   A552 9E E7 08      [ 4] 2332 	sta	8,s
   A555 9F            [ 1] 2333 	txa
   A556 9E E7 07      [ 4] 2334 	sta	7,s
   A559 49            [ 1] 2335 	rola	
   A55A 4F            [ 1] 2336 	clra	
   A55B A2 00         [ 2] 2337 	sbc	#0x00
   A55D 9E E7 06      [ 4] 2338 	sta	6,s
   A560 9E E7 05      [ 4] 2339 	sta	5,s
   A563 95            [ 2] 2340 	tsx
   A564 E6 07         [ 3] 2341 	lda	7,x
   A566 87            [ 2] 2342 	psha
   A567 E6 06         [ 3] 2343 	lda	6,x
   A569 87            [ 2] 2344 	psha
   A56A E6 05         [ 3] 2345 	lda	5,x
   A56C 87            [ 2] 2346 	psha
   A56D E6 04         [ 3] 2347 	lda	4,x
   A56F 87            [ 2] 2348 	psha
   A570 E6 03         [ 3] 2349 	lda	3,x
   A572 87            [ 2] 2350 	psha
   A573 E6 02         [ 3] 2351 	lda	2,x
   A575 87            [ 2] 2352 	psha
   A576 E6 01         [ 3] 2353 	lda	1,x
   A578 87            [ 2] 2354 	psha
   A579 F6            [ 2] 2355 	lda	,x
   A57A 87            [ 2] 2356 	psha
   A57B CD CE 92      [ 5] 2357 	jsr	__divslong
   A57E 9E E7 0C      [ 4] 2358 	sta	12,s
   A581 9E EF 0B      [ 4] 2359 	stx	11,s
   A584 B6 4A         [ 3] 2360 	lda	*___SDCC_hc08_ret2
   A586 9E E7 0A      [ 4] 2361 	sta	10,s
   A589 B6 4B         [ 3] 2362 	lda	*___SDCC_hc08_ret3
   A58B 9E E7 09      [ 4] 2363 	sta	9,s
   A58E A7 08         [ 2] 2364 	ais	#8
   A590 9E E6 04      [ 4] 2365 	lda	4,s
   A593 9E EE 03      [ 4] 2366 	ldx	3,s
   A596 9E EB 1D      [ 4] 2367 	add	29,s
   A599 9E E7 14      [ 4] 2368 	sta	20,s
   A59C 9F            [ 1] 2369 	txa
   A59D 9E E9 1C      [ 4] 2370 	adc	28,s
   A5A0 9E E7 13      [ 4] 2371 	sta	19,s
                           2372 ;tables.c:140: return (int8_t)interpolate(x, bins[i], bins[i + 1], values[i], values[i + 1]);
   A5A3                    2373 00113$:
   A5A3 95            [ 2] 2374 	tsx
   A5A4 E6 13         [ 3] 2375 	lda	19,x
   A5A6 20 13         [ 3] 2376 	bra	00117$
   A5A8                    2377 00116$:
                           2378 ;tables.c:138: for (i = 0; i < size - 1; i++) {
   A5A8 95            [ 2] 2379 	tsx
   A5A9 6C 16         [ 4] 2380 	inc	22,x
   A5AB E6 16         [ 3] 2381 	lda	22,x
   A5AD E7 0E         [ 3] 2382 	sta	14,x
   A5AF CC A4 17      [ 3] 2383 	jmp	00115$
   A5B2                    2384 00110$:
                           2385 ;tables.c:143: return values[size - 1];
   A5B2 9E E6 0D      [ 4] 2386 	lda	13,s
   A5B5 87            [ 2] 2387 	psha
   A5B6 8A            [ 2] 2388 	pulh
   A5B7 9E EE 0E      [ 4] 2389 	ldx	14,s
   A5BA F6            [ 2] 2390 	lda	,x
   A5BB                    2391 00117$:
                           2392 ;tables.c:144: }
   A5BB A7 1F         [ 2] 2393 	ais	#31
   A5BD 81            [ 4] 2394 	rts
                           2395 	.area CSEG    (CODE)
                           2396 	.area CONST   (CODE)
                           2397 	.area XINIT   (CODE)
                           2398 	.area CABS    (ABS,CODE)
