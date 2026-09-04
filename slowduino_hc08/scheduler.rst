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
                             24 	.globl _ignitionSchedule2
                             25 	.globl _ignitionSchedule1
                             26 	.globl _setIgnitionSchedule_PARM_4
                             27 	.globl _setIgnitionSchedule_PARM_3
                             28 	.globl _setIgnitionSchedule_PARM_2
                             29 	.globl _schedulerInit
                             30 	.globl _setIgnitionSchedule
                             31 	.globl _clearIgnitionSchedule
                             32 ;--------------------------------------------------------
                             33 ; ram data
                             34 ;--------------------------------------------------------
                             35 	.area DSEG    (PAG)
   0084                      36 _handleIgnitionChannel_sloc0_1_0:
   0084                      37 	.ds 2
   0086                      38 _handleIgnitionChannel_sloc1_1_0:
   0086                      39 	.ds 2
   0088                      40 _handleIgnitionChannel_sloc2_1_0:
   0088                      41 	.ds 2
   008A                      42 _armIgnitionCompare_sloc0_1_0:
   008A                      43 	.ds 2
   008C                      44 _armIgnitionCompare_sloc1_1_0:
   008C                      45 	.ds 2
   008E                      46 _armIgnitionCompare_sloc2_1_0:
   008E                      47 	.ds 2
   0090                      48 _armIgnitionCompare_sloc3_1_0:
   0090                      49 	.ds 2
   0092                      50 _setIgnitionSchedule_sloc0_1_0:
   0092                      51 	.ds 2
   0094                      52 _setIgnitionSchedule_sloc1_1_0:
   0094                      53 	.ds 2
   0096                      54 _setIgnitionSchedule_sloc2_1_0:
   0096                      55 	.ds 4
   009A                      56 _setIgnitionSchedule_sloc3_1_0:
   009A                      57 	.ds 4
   009E                      58 _setIgnitionSchedule_sloc4_1_0:
   009E                      59 	.ds 4
                             60 ;--------------------------------------------------------
                             61 ; overlayable items in ram
                             62 ;--------------------------------------------------------
                             63 	.area	OSEG    (PAG, OVR)
   00B0                      64 _getTimer1Count_sloc0_1_0:
   00B0                      65 	.ds 2
                             66 ;--------------------------------------------------------
                             67 ; absolute ram data
                             68 ;--------------------------------------------------------
                             69 	.area IABS    (ABS)
                             70 	.area IABS    (ABS)
                             71 ;--------------------------------------------------------
                             72 ; absolute external ram data
                             73 ;--------------------------------------------------------
                             74 	.area XABS    (ABS)
                             75 ;--------------------------------------------------------
                             76 ; external initialized ram data
                             77 ;--------------------------------------------------------
                             78 	.area XISEG
   0190                      79 _ignitionSchedule1::
   0190                      80 	.ds 8
   0198                      81 _ignitionSchedule2::
   0198                      82 	.ds 8
                             83 ;--------------------------------------------------------
                             84 ; extended address mode data
                             85 ;--------------------------------------------------------
                             86 	.area XSEG
   0163                      87 _handleIgnitionChannel_PARM_2:
   0163                      88 	.ds 2
   0165                      89 _handleIgnitionChannel_PARM_3:
   0165                      90 	.ds 2
   0167                      91 _handleIgnitionChannel_PARM_4:
   0167                      92 	.ds 2
   0169                      93 _handleIgnitionChannel_schedule_65536_16:
   0169                      94 	.ds 2
   016B                      95 _armIgnitionCompare_PARM_2:
   016B                      96 	.ds 2
   016D                      97 _armIgnitionCompare_PARM_3:
   016D                      98 	.ds 2
   016F                      99 _armIgnitionCompare_PARM_4:
   016F                     100 	.ds 2
   0171                     101 _armIgnitionCompare_schedule_65536_26:
   0171                     102 	.ds 2
   0173                     103 _setIgnitionSchedule_PARM_2:
   0173                     104 	.ds 4
   0177                     105 _setIgnitionSchedule_PARM_3:
   0177                     106 	.ds 2
   0179                     107 _setIgnitionSchedule_PARM_4:
   0179                     108 	.ds 1
   017A                     109 _setIgnitionSchedule_schedule_65536_34:
   017A                     110 	.ds 2
   017C                     111 _setIgnitionSchedule___1310720006_131072_35:
   017C                     112 	.ds 2
   017E                     113 _setIgnitionSchedule_startTicks_65536_35:
   017E                     114 	.ds 4
   0182                     115 _setIgnitionSchedule_durationTicks_65536_35:
   0182                     116 	.ds 4
   0186                     117 _setIgnitionSchedule_startTicks16_65536_35:
   0186                     118 	.ds 2
   0188                     119 _setIgnitionSchedule_durationTicks16_65536_35:
   0188                     120 	.ds 2
   018A                     121 _clearIgnitionSchedule_schedule_65536_49:
   018A                     122 	.ds 2
                            123 ;--------------------------------------------------------
                            124 ; global & static initialisations
                            125 ;--------------------------------------------------------
                            126 	.area HOME    (CODE)
                            127 	.area GSINIT  (CODE)
                            128 	.area GSFINAL (CODE)
                            129 	.area GSINIT  (CODE)
                            130 ;--------------------------------------------------------
                            131 ; Home
                            132 ;--------------------------------------------------------
                            133 	.area HOME    (CODE)
                            134 	.area HOME    (CODE)
                            135 ;--------------------------------------------------------
                            136 ; code
                            137 ;--------------------------------------------------------
                            138 	.area CSEG    (CODE)
                            139 ;------------------------------------------------------------
                            140 ;Allocation info for local variables in function 'getTimer1Count'
                            141 ;------------------------------------------------------------
                            142 ;sloc0                     Allocated with name '_getTimer1Count_sloc0_1_0'
                            143 ;------------------------------------------------------------
                            144 ;scheduler.h:54: static inline uint16_t getTimer1Count(void) {
                            145 ;	-----------------------------------------
                            146 ;	 function getTimer1Count
                            147 ;	-----------------------------------------
                            148 ;	Register assignment is optimal.
                            149 ;	Stack space usage: 0 bytes.
   8102                     150 _getTimer1Count:
                            151 ;scheduler.h:55: return (uint16_t)((T1CNTH << 8) | T1CNTL);
   8102 B6 21         [ 3]  152 	lda	*0x21
   8104 5F            [ 1]  153 	clrx
   8105 B7 B0         [ 3]  154 	sta	*_getTimer1Count_sloc0_1_0
   8107 BF B1         [ 3]  155 	stx	*(_getTimer1Count_sloc0_1_0 + 1)
   8109 B6 22         [ 3]  156 	lda	*0x22
   810B BA B1         [ 3]  157 	ora	*(_getTimer1Count_sloc0_1_0 + 1)
   810D 87            [ 2]  158 	psha
   810E 9F            [ 1]  159 	txa
   810F BA B0         [ 3]  160 	ora	*_getTimer1Count_sloc0_1_0
   8111 97            [ 1]  161 	tax
   8112 86            [ 2]  162 	pula
                            163 ;scheduler.h:56: }
   8113 81            [ 4]  164 	rts
                            165 ;------------------------------------------------------------
                            166 ;Allocation info for local variables in function 'beginCoil1Charge'
                            167 ;------------------------------------------------------------
                            168 ;scheduler.c:27: static void beginCoil1Charge(void) { PTA |= COIL1_BIT; }
                            169 ;	-----------------------------------------
                            170 ;	 function beginCoil1Charge
                            171 ;	-----------------------------------------
                            172 ;	Register assignment is optimal.
                            173 ;	Stack space usage: 0 bytes.
   8114                     174 _beginCoil1Charge:
   8114 B6 00         [ 3]  175 	lda	*0x00
   8116 AA 01         [ 2]  176 	ora	#0x01
   8118 B7 00         [ 3]  177 	sta	*0x00
   811A 81            [ 4]  178 	rts
                            179 ;------------------------------------------------------------
                            180 ;Allocation info for local variables in function 'endCoil1Charge'
                            181 ;------------------------------------------------------------
                            182 ;scheduler.c:28: static void endCoil1Charge(void)   { PTA &= (uint8_t)~COIL1_BIT; }
                            183 ;	-----------------------------------------
                            184 ;	 function endCoil1Charge
                            185 ;	-----------------------------------------
                            186 ;	Register assignment is optimal.
                            187 ;	Stack space usage: 0 bytes.
   811B                     188 _endCoil1Charge:
   811B B6 00         [ 3]  189 	lda	*0x00
   811D A4 FE         [ 2]  190 	and	#0xfe
   811F B7 00         [ 3]  191 	sta	*0x00
   8121 81            [ 4]  192 	rts
                            193 ;------------------------------------------------------------
                            194 ;Allocation info for local variables in function 'beginCoil2Charge'
                            195 ;------------------------------------------------------------
                            196 ;scheduler.c:29: static void beginCoil2Charge(void) { PTA |= COIL2_BIT; }
                            197 ;	-----------------------------------------
                            198 ;	 function beginCoil2Charge
                            199 ;	-----------------------------------------
                            200 ;	Register assignment is optimal.
                            201 ;	Stack space usage: 0 bytes.
   8122                     202 _beginCoil2Charge:
   8122 B6 00         [ 3]  203 	lda	*0x00
   8124 AA 02         [ 2]  204 	ora	#0x02
   8126 B7 00         [ 3]  205 	sta	*0x00
   8128 81            [ 4]  206 	rts
                            207 ;------------------------------------------------------------
                            208 ;Allocation info for local variables in function 'endCoil2Charge'
                            209 ;------------------------------------------------------------
                            210 ;scheduler.c:30: static void endCoil2Charge(void)   { PTA &= (uint8_t)~COIL2_BIT; }
                            211 ;	-----------------------------------------
                            212 ;	 function endCoil2Charge
                            213 ;	-----------------------------------------
                            214 ;	Register assignment is optimal.
                            215 ;	Stack space usage: 0 bytes.
   8129                     216 _endCoil2Charge:
   8129 B6 00         [ 3]  217 	lda	*0x00
   812B A4 FD         [ 2]  218 	and	#0xfd
   812D B7 00         [ 3]  219 	sta	*0x00
   812F 81            [ 4]  220 	rts
                            221 ;------------------------------------------------------------
                            222 ;Allocation info for local variables in function 'schedulerInit'
                            223 ;------------------------------------------------------------
                            224 ;scheduler.c:32: void schedulerInit(void) {
                            225 ;	-----------------------------------------
                            226 ;	 function schedulerInit
                            227 ;	-----------------------------------------
                            228 ;	Register assignment is optimal.
                            229 ;	Stack space usage: 0 bytes.
   8130                     230 _schedulerInit:
                            231 ;scheduler.c:33: DDRA |= (COIL1_BIT | COIL2_BIT);  /* bobinas como saida */
   8130 B6 04         [ 3]  232 	lda	*0x04
   8132 AA 03         [ 2]  233 	ora	#0x03
   8134 B7 04         [ 3]  234 	sta	*0x04
                            235 ;scheduler.c:34: endCoil1Charge();
   8136 CD 81 1B      [ 5]  236 	jsr	_endCoil1Charge
                            237 ;scheduler.c:35: endCoil2Charge();
   8139 CD 81 29      [ 5]  238 	jsr	_endCoil2Charge
                            239 ;scheduler.c:40: T1SC = (1 << T1SC_TRST);
   813C 6E 10 20      [ 4]  240 	mov	#0x10,*0x20
                            241 ;scheduler.c:41: T1SC0 = (1 << TxSCx_MSxA);
   813F 6E 10 25      [ 4]  242 	mov	#0x10,*0x25
                            243 ;scheduler.c:42: T1SC0 |= (1 << TxSCx_CHxIE);
   8142 B6 25         [ 3]  244 	lda	*0x25
   8144 AA 40         [ 2]  245 	ora	#0x40
   8146 B7 25         [ 3]  246 	sta	*0x25
                            247 ;scheduler.c:43: T1SC1 = (1 << TxSCx_MSxA) | (1 << TxSCx_CHxIE);
   8148 6E 50 28      [ 4]  248 	mov	#0x50,*0x28
                            249 ;scheduler.c:44: T1SC = (6 << T1SC_PS0);  /* PS[2:0]=110 -> /64. Ver US_TO_TIMER1 em scheduler.h */
   814B 6E 06 20      [ 4]  250 	mov	#0x06,*0x20
                            251 ;scheduler.c:45: }
   814E 81            [ 4]  252 	rts
                            253 ;------------------------------------------------------------
                            254 ;Allocation info for local variables in function 'handleIgnitionChannel'
                            255 ;------------------------------------------------------------
                            256 ;sloc0                     Allocated with name '_handleIgnitionChannel_sloc0_1_0'
                            257 ;sloc1                     Allocated with name '_handleIgnitionChannel_sloc1_1_0'
                            258 ;sloc2                     Allocated with name '_handleIgnitionChannel_sloc2_1_0'
                            259 ;beginCharge               Allocated with name '_handleIgnitionChannel_PARM_2'
                            260 ;endCharge                 Allocated with name '_handleIgnitionChannel_PARM_3'
                            261 ;compareReg                Allocated with name '_handleIgnitionChannel_PARM_4'
                            262 ;schedule                  Allocated with name '_handleIgnitionChannel_schedule_65536_16'
                            263 ;__1966080002              Allocated to registers a x 
                            264 ;------------------------------------------------------------
                            265 ;scheduler.c:47: static void handleIgnitionChannel(volatile IgnitionSchedule *schedule,
                            266 ;	-----------------------------------------
                            267 ;	 function handleIgnitionChannel
                            268 ;	-----------------------------------------
                            269 ;	Register assignment is optimal.
                            270 ;	Stack space usage: 0 bytes.
   814F                     271 _handleIgnitionChannel:
   814F C7 01 6A      [ 4]  272 	sta	(_handleIgnitionChannel_schedule_65536_16 + 1)
   8152 CF 01 69      [ 4]  273 	stx	_handleIgnitionChannel_schedule_65536_16
                            274 ;scheduler.c:51: if (schedule->status == SCHED_PENDING) {
   8155 C6 01 69      [ 4]  275 	lda	_handleIgnitionChannel_schedule_65536_16
   8158 B7 84         [ 3]  276 	sta	*_handleIgnitionChannel_sloc0_1_0
   815A C6 01 6A      [ 4]  277 	lda	(_handleIgnitionChannel_schedule_65536_16 + 1)
   815D B7 85         [ 3]  278 	sta	*(_handleIgnitionChannel_sloc0_1_0 + 1)
   815F 55 84         [ 4]  279 	ldhx	*_handleIgnitionChannel_sloc0_1_0
   8161 F6            [ 2]  280 	lda	,x
   8162 A1 01         [ 2]  281 	cmp	#0x01
   8164 26 6C         [ 3]  282 	bne	00104$
                            283 ;scheduler.c:52: schedule->status = SCHED_RUNNING;
   8166 55 84         [ 4]  284 	ldhx	*_handleIgnitionChannel_sloc0_1_0
   8168 A6 02         [ 2]  285 	lda	#0x02
   816A F7            [ 2]  286 	sta	,x
                            287 ;scheduler.c:53: beginCharge();
   816B AD 02         [ 4]  288 	bsr	00127$
   816D 20 09         [ 3]  289 	bra	00126$
   816F                     290 00127$:
   816F C6 01 64      [ 4]  291 	lda	(_handleIgnitionChannel_PARM_2 + 1)
   8172 87            [ 2]  292 	psha
   8173 C6 01 63      [ 4]  293 	lda	_handleIgnitionChannel_PARM_2
   8176 87            [ 2]  294 	psha
   8177 81            [ 4]  295 	rts
   8178                     296 00126$:
                            297 ;scheduler.c:54: *compareReg = schedule->endCompare;
   8178 C6 01 67      [ 4]  298 	lda	_handleIgnitionChannel_PARM_4
   817B B7 86         [ 3]  299 	sta	*_handleIgnitionChannel_sloc1_1_0
   817D C6 01 68      [ 4]  300 	lda	(_handleIgnitionChannel_PARM_4 + 1)
   8180 B7 87         [ 3]  301 	sta	*(_handleIgnitionChannel_sloc1_1_0 + 1)
   8182 4E 84 88      [ 5]  302 	mov	*_handleIgnitionChannel_sloc0_1_0,*_handleIgnitionChannel_sloc2_1_0
   8185 4E 85 89      [ 5]  303 	mov	*(_handleIgnitionChannel_sloc0_1_0 + 1),*(_handleIgnitionChannel_sloc2_1_0 + 1)
   8188 55 88         [ 4]  304 	ldhx	*_handleIgnitionChannel_sloc2_1_0
   818A E6 04         [ 3]  305 	lda	4,x
   818C EE 03         [ 3]  306 	ldx	3,x
   818E 89            [ 2]  307 	pshx
   818F 55 86         [ 4]  308 	ldhx	*_handleIgnitionChannel_sloc1_1_0
   8191 E7 01         [ 3]  309 	sta	1,x
   8193 86            [ 2]  310 	pula
   8194 F7            [ 2]  311 	sta	,x
                            312 ;scheduler.h:55: return (uint16_t)((T1CNTH << 8) | T1CNTL);
   8195 B6 21         [ 3]  313 	lda	*0x21
   8197 5F            [ 1]  314 	clrx
   8198 B7 86         [ 3]  315 	sta	*_handleIgnitionChannel_sloc1_1_0
   819A BF 87         [ 3]  316 	stx	*(_handleIgnitionChannel_sloc1_1_0 + 1)
   819C B6 22         [ 3]  317 	lda	*0x22
   819E BA 87         [ 3]  318 	ora	*(_handleIgnitionChannel_sloc1_1_0 + 1)
   81A0 87            [ 2]  319 	psha
   81A1 9F            [ 1]  320 	txa
   81A2 BA 86         [ 3]  321 	ora	*_handleIgnitionChannel_sloc1_1_0
   81A4 97            [ 1]  322 	tax
   81A5 86            [ 2]  323 	pula
                            324 ;scheduler.c:56: if ((int16_t)(getTimer1Count() - schedule->endCompare) >= 0) {
   81A6 89            [ 2]  325 	pshx
   81A7 55 88         [ 4]  326 	ldhx	*_handleIgnitionChannel_sloc2_1_0
   81A9 87            [ 2]  327 	psha
   81AA E6 03         [ 3]  328 	lda	3,x
   81AC B7 88         [ 3]  329 	sta	*_handleIgnitionChannel_sloc2_1_0
   81AE E6 04         [ 3]  330 	lda	4,x
   81B0 B7 89         [ 3]  331 	sta	*(_handleIgnitionChannel_sloc2_1_0 + 1)
   81B2 86            [ 2]  332 	pula
   81B3 88            [ 2]  333 	pulx
   81B4 B0 89         [ 3]  334 	sub	*(_handleIgnitionChannel_sloc2_1_0 + 1)
   81B6 87            [ 2]  335 	psha
   81B7 9F            [ 1]  336 	txa
   81B8 B2 88         [ 3]  337 	sbc	*_handleIgnitionChannel_sloc2_1_0
   81BA 97            [ 1]  338 	tax
   81BB 86            [ 2]  339 	pula
   81BC 9F            [ 1]  340 	txa
   81BD A0 00         [ 2]  341 	sub	#0x00
   81BF 91 10         [ 3]  342 	blt	00102$
                            343 ;scheduler.c:57: schedule->status = SCHED_OFF;
   81C1 55 84         [ 4]  344 	ldhx	*_handleIgnitionChannel_sloc0_1_0
   81C3 4F            [ 1]  345 	clra
   81C4 F7            [ 2]  346 	sta	,x
                            347 ;scheduler.c:58: endCharge();
   81C5 AD 01         [ 4]  348 	bsr	00130$
   81C7 81            [ 4]  349 	rts
   81C8                     350 00130$:
   81C8 C6 01 66      [ 4]  351 	lda	(_handleIgnitionChannel_PARM_3 + 1)
   81CB 87            [ 2]  352 	psha
   81CC C6 01 65      [ 4]  353 	lda	_handleIgnitionChannel_PARM_3
   81CF 87            [ 2]  354 	psha
   81D0 81            [ 4]  355 	rts
   81D1                     356 00102$:
                            357 ;scheduler.c:60: return;
   81D1 81            [ 4]  358 	rts
   81D2                     359 00104$:
                            360 ;scheduler.c:63: if (schedule->status == SCHED_RUNNING) {
   81D2 55 84         [ 4]  361 	ldhx	*_handleIgnitionChannel_sloc0_1_0
   81D4 F6            [ 2]  362 	lda	,x
   81D5 A1 02         [ 2]  363 	cmp	#0x02
   81D7 26 10         [ 3]  364 	bne	00108$
                            365 ;scheduler.c:64: schedule->status = SCHED_OFF;
   81D9 55 84         [ 4]  366 	ldhx	*_handleIgnitionChannel_sloc0_1_0
   81DB 4F            [ 1]  367 	clra
   81DC F7            [ 2]  368 	sta	,x
                            369 ;scheduler.c:65: endCharge();
   81DD AD 01         [ 4]  370 	bsr	00133$
   81DF 81            [ 4]  371 	rts
   81E0                     372 00133$:
   81E0 C6 01 66      [ 4]  373 	lda	(_handleIgnitionChannel_PARM_3 + 1)
   81E3 87            [ 2]  374 	psha
   81E4 C6 01 65      [ 4]  375 	lda	_handleIgnitionChannel_PARM_3
   81E7 87            [ 2]  376 	psha
   81E8 81            [ 4]  377 	rts
   81E9                     378 00108$:
                            379 ;scheduler.c:67: }
   81E9 81            [ 4]  380 	rts
                            381 ;------------------------------------------------------------
                            382 ;Allocation info for local variables in function 'armIgnitionCompare'
                            383 ;------------------------------------------------------------
                            384 ;sloc0                     Allocated with name '_armIgnitionCompare_sloc0_1_0'
                            385 ;sloc1                     Allocated with name '_armIgnitionCompare_sloc1_1_0'
                            386 ;sloc2                     Allocated with name '_armIgnitionCompare_sloc2_1_0'
                            387 ;sloc3                     Allocated with name '_armIgnitionCompare_sloc3_1_0'
                            388 ;beginCharge               Allocated with name '_armIgnitionCompare_PARM_2'
                            389 ;endCharge                 Allocated with name '_armIgnitionCompare_PARM_3'
                            390 ;compareReg                Allocated with name '_armIgnitionCompare_PARM_4'
                            391 ;schedule                  Allocated with name '_armIgnitionCompare_schedule_65536_26'
                            392 ;__1310720004              Allocated to registers a x 
                            393 ;------------------------------------------------------------
                            394 ;scheduler.c:69: static void armIgnitionCompare(volatile IgnitionSchedule *schedule,
                            395 ;	-----------------------------------------
                            396 ;	 function armIgnitionCompare
                            397 ;	-----------------------------------------
                            398 ;	Register assignment is optimal.
                            399 ;	Stack space usage: 0 bytes.
   81EA                     400 _armIgnitionCompare:
   81EA C7 01 72      [ 4]  401 	sta	(_armIgnitionCompare_schedule_65536_26 + 1)
   81ED CF 01 71      [ 4]  402 	stx	_armIgnitionCompare_schedule_65536_26
                            403 ;scheduler.c:73: *compareReg = schedule->startCompare;
   81F0 C6 01 6F      [ 4]  404 	lda	_armIgnitionCompare_PARM_4
   81F3 B7 8A         [ 3]  405 	sta	*_armIgnitionCompare_sloc0_1_0
   81F5 C6 01 70      [ 4]  406 	lda	(_armIgnitionCompare_PARM_4 + 1)
   81F8 B7 8B         [ 3]  407 	sta	*(_armIgnitionCompare_sloc0_1_0 + 1)
   81FA C6 01 71      [ 4]  408 	lda	_armIgnitionCompare_schedule_65536_26
   81FD B7 8C         [ 3]  409 	sta	*_armIgnitionCompare_sloc1_1_0
   81FF C6 01 72      [ 4]  410 	lda	(_armIgnitionCompare_schedule_65536_26 + 1)
   8202 B7 8D         [ 3]  411 	sta	*(_armIgnitionCompare_sloc1_1_0 + 1)
   8204 4E 8C 8E      [ 5]  412 	mov	*_armIgnitionCompare_sloc1_1_0,*_armIgnitionCompare_sloc2_1_0
   8207 4E 8D 8F      [ 5]  413 	mov	*(_armIgnitionCompare_sloc1_1_0 + 1),*(_armIgnitionCompare_sloc2_1_0 + 1)
   820A 55 8E         [ 4]  414 	ldhx	*_armIgnitionCompare_sloc2_1_0
   820C E6 02         [ 3]  415 	lda	2,x
   820E EE 01         [ 3]  416 	ldx	1,x
   8210 89            [ 2]  417 	pshx
   8211 55 8A         [ 4]  418 	ldhx	*_armIgnitionCompare_sloc0_1_0
   8213 E7 01         [ 3]  419 	sta	1,x
   8215 86            [ 2]  420 	pula
   8216 F7            [ 2]  421 	sta	,x
                            422 ;scheduler.h:55: return (uint16_t)((T1CNTH << 8) | T1CNTL);
   8217 B6 21         [ 3]  423 	lda	*0x21
   8219 5F            [ 1]  424 	clrx
   821A B7 90         [ 3]  425 	sta	*_armIgnitionCompare_sloc3_1_0
   821C BF 91         [ 3]  426 	stx	*(_armIgnitionCompare_sloc3_1_0 + 1)
   821E B6 22         [ 3]  427 	lda	*0x22
   8220 BA 91         [ 3]  428 	ora	*(_armIgnitionCompare_sloc3_1_0 + 1)
   8222 87            [ 2]  429 	psha
   8223 9F            [ 1]  430 	txa
   8224 BA 90         [ 3]  431 	ora	*_armIgnitionCompare_sloc3_1_0
   8226 97            [ 1]  432 	tax
   8227 86            [ 2]  433 	pula
                            434 ;scheduler.c:75: if ((int16_t)(getTimer1Count() - schedule->startCompare) >= 0) {
   8228 89            [ 2]  435 	pshx
   8229 55 8E         [ 4]  436 	ldhx	*_armIgnitionCompare_sloc2_1_0
   822B 87            [ 2]  437 	psha
   822C E6 01         [ 3]  438 	lda	1,x
   822E B7 90         [ 3]  439 	sta	*_armIgnitionCompare_sloc3_1_0
   8230 E6 02         [ 3]  440 	lda	2,x
   8232 B7 91         [ 3]  441 	sta	*(_armIgnitionCompare_sloc3_1_0 + 1)
   8234 86            [ 2]  442 	pula
   8235 88            [ 2]  443 	pulx
   8236 B0 91         [ 3]  444 	sub	*(_armIgnitionCompare_sloc3_1_0 + 1)
   8238 87            [ 2]  445 	psha
   8239 9F            [ 1]  446 	txa
   823A B2 90         [ 3]  447 	sbc	*_armIgnitionCompare_sloc3_1_0
   823C 97            [ 1]  448 	tax
   823D 86            [ 2]  449 	pula
   823E 9F            [ 1]  450 	txa
   823F A0 00         [ 2]  451 	sub	#0x00
   8241 91 29         [ 3]  452 	blt	00104$
                            453 ;scheduler.c:76: handleIgnitionChannel(schedule, beginCharge, endCharge, compareReg);
   8243 C6 01 6B      [ 4]  454 	lda	_armIgnitionCompare_PARM_2
   8246 C7 01 63      [ 4]  455 	sta	_handleIgnitionChannel_PARM_2
   8249 C6 01 6C      [ 4]  456 	lda	(_armIgnitionCompare_PARM_2 + 1)
   824C C7 01 64      [ 4]  457 	sta	(_handleIgnitionChannel_PARM_2 + 1)
   824F C6 01 6D      [ 4]  458 	lda	_armIgnitionCompare_PARM_3
   8252 C7 01 65      [ 4]  459 	sta	_handleIgnitionChannel_PARM_3
   8255 C6 01 6E      [ 4]  460 	lda	(_armIgnitionCompare_PARM_3 + 1)
   8258 C7 01 66      [ 4]  461 	sta	(_handleIgnitionChannel_PARM_3 + 1)
   825B B6 8A         [ 3]  462 	lda	*_armIgnitionCompare_sloc0_1_0
   825D C7 01 67      [ 4]  463 	sta	_handleIgnitionChannel_PARM_4
   8260 B6 8B         [ 3]  464 	lda	*(_armIgnitionCompare_sloc0_1_0 + 1)
   8262 C7 01 68      [ 4]  465 	sta	(_handleIgnitionChannel_PARM_4 + 1)
   8265 B6 8D         [ 3]  466 	lda	*(_armIgnitionCompare_sloc1_1_0 + 1)
   8267 BE 8C         [ 3]  467 	ldx	*_armIgnitionCompare_sloc1_1_0
   8269 CD 81 4F      [ 5]  468 	jsr	_handleIgnitionChannel
   826C                     469 00104$:
                            470 ;scheduler.c:78: }
   826C 81            [ 4]  471 	rts
                            472 ;------------------------------------------------------------
                            473 ;Allocation info for local variables in function 'setIgnitionSchedule'
                            474 ;------------------------------------------------------------
                            475 ;sloc0                     Allocated with name '_setIgnitionSchedule_sloc0_1_0'
                            476 ;sloc1                     Allocated with name '_setIgnitionSchedule_sloc1_1_0'
                            477 ;sloc2                     Allocated with name '_setIgnitionSchedule_sloc2_1_0'
                            478 ;sloc3                     Allocated with name '_setIgnitionSchedule_sloc3_1_0'
                            479 ;sloc4                     Allocated with name '_setIgnitionSchedule_sloc4_1_0'
                            480 ;startTime                 Allocated with name '_setIgnitionSchedule_PARM_2'
                            481 ;duration                  Allocated with name '_setIgnitionSchedule_PARM_3'
                            482 ;channel                   Allocated with name '_setIgnitionSchedule_PARM_4'
                            483 ;schedule                  Allocated with name '_setIgnitionSchedule_schedule_65536_34'
                            484 ;__1310720006              Allocated with name '_setIgnitionSchedule___1310720006_131072_35'
                            485 ;startTicks                Allocated with name '_setIgnitionSchedule_startTicks_65536_35'
                            486 ;durationTicks             Allocated with name '_setIgnitionSchedule_durationTicks_65536_35'
                            487 ;totalTicks                Allocated with name '_setIgnitionSchedule_totalTicks_65536_35'
                            488 ;minTicks                  Allocated with name '_setIgnitionSchedule_minTicks_65536_35'
                            489 ;currentCount              Allocated to registers 
                            490 ;startTicks16              Allocated with name '_setIgnitionSchedule_startTicks16_65536_35'
                            491 ;durationTicks16           Allocated with name '_setIgnitionSchedule_durationTicks16_65536_35'
                            492 ;------------------------------------------------------------
                            493 ;scheduler.c:80: void setIgnitionSchedule(volatile IgnitionSchedule *schedule, uint32_t startTime,
                            494 ;	-----------------------------------------
                            495 ;	 function setIgnitionSchedule
                            496 ;	-----------------------------------------
                            497 ;	Register assignment might be sub-optimal.
                            498 ;	Stack space usage: 0 bytes.
   826D                     499 _setIgnitionSchedule:
   826D C7 01 7B      [ 4]  500 	sta	(_setIgnitionSchedule_schedule_65536_34 + 1)
   8270 CF 01 7A      [ 4]  501 	stx	_setIgnitionSchedule_schedule_65536_34
                            502 ;scheduler.c:86: schedule->status = SCHED_OFF;
   8273 C6 01 7A      [ 4]  503 	lda	_setIgnitionSchedule_schedule_65536_34
   8276 B7 92         [ 3]  504 	sta	*_setIgnitionSchedule_sloc0_1_0
   8278 C6 01 7B      [ 4]  505 	lda	(_setIgnitionSchedule_schedule_65536_34 + 1)
   827B B7 93         [ 3]  506 	sta	*(_setIgnitionSchedule_sloc0_1_0 + 1)
                            507 ;scheduler.c:85: if (channel > 2) {
   827D C6 01 79      [ 4]  508 	lda	_setIgnitionSchedule_PARM_4
   8280 A1 02         [ 2]  509 	cmp	#0x02
   8282 23 05         [ 3]  510 	bls	00102$
                            511 ;scheduler.c:86: schedule->status = SCHED_OFF;
   8284 55 92         [ 4]  512 	ldhx	*_setIgnitionSchedule_sloc0_1_0
   8286 4F            [ 1]  513 	clra
   8287 F7            [ 2]  514 	sta	,x
                            515 ;scheduler.c:87: return;
   8288 81            [ 4]  516 	rts
   8289                     517 00102$:
                            518 ;scheduler.c:90: if (schedule->status == SCHED_RUNNING) {
   8289 55 92         [ 4]  519 	ldhx	*_setIgnitionSchedule_sloc0_1_0
   828B F6            [ 2]  520 	lda	,x
                            521 ;scheduler.c:92: if (schedule->channel == 1) { endCoil1Charge(); } else { endCoil2Charge(); }
   828C 4E 92 94      [ 5]  522 	mov	*_setIgnitionSchedule_sloc0_1_0,*_setIgnitionSchedule_sloc1_1_0
   828F 4E 93 95      [ 5]  523 	mov	*(_setIgnitionSchedule_sloc0_1_0 + 1),*(_setIgnitionSchedule_sloc1_1_0 + 1)
                            524 ;scheduler.c:90: if (schedule->status == SCHED_RUNNING) {
   8292 A1 02         [ 2]  525 	cmp	#0x02
   8294 26 14         [ 3]  526 	bne	00107$
                            527 ;scheduler.c:91: schedule->status = SCHED_OFF;
   8296 55 92         [ 4]  528 	ldhx	*_setIgnitionSchedule_sloc0_1_0
   8298 4F            [ 1]  529 	clra
   8299 F7            [ 2]  530 	sta	,x
                            531 ;scheduler.c:92: if (schedule->channel == 1) { endCoil1Charge(); } else { endCoil2Charge(); }
   829A 55 94         [ 4]  532 	ldhx	*_setIgnitionSchedule_sloc1_1_0
   829C E6 07         [ 3]  533 	lda	7,x
   829E A1 01         [ 2]  534 	cmp	#0x01
   82A0 26 05         [ 3]  535 	bne	00104$
   82A2 CD 81 1B      [ 5]  536 	jsr	_endCoil1Charge
   82A5 20 03         [ 3]  537 	bra	00107$
   82A7                     538 00104$:
   82A7 CD 81 29      [ 5]  539 	jsr	_endCoil2Charge
   82AA                     540 00107$:
                            541 ;scheduler.c:95: startTicks = US_TO_TIMER1(startTime);
   82AA C6 01 76      [ 4]  542 	lda	(_setIgnitionSchedule_PARM_2 + 3)
   82AD CE 01 75      [ 4]  543 	ldx	(_setIgnitionSchedule_PARM_2 + 2)
   82B0 54            [ 1]  544 	lsrx
   82B1 46            [ 1]  545 	rora
   82B2 54            [ 1]  546 	lsrx
   82B3 46            [ 1]  547 	rora
   82B4 54            [ 1]  548 	lsrx
   82B5 46            [ 1]  549 	rora
   82B6 B7 99         [ 3]  550 	sta	*(_setIgnitionSchedule_sloc2_1_0 + 3)
   82B8 BF 98         [ 3]  551 	stx	*(_setIgnitionSchedule_sloc2_1_0 + 2)
   82BA C6 01 74      [ 4]  552 	lda	(_setIgnitionSchedule_PARM_2 + 1)
   82BD 62            [ 3]  553 	nsa	
   82BE A4 F0         [ 2]  554 	and	#0xf0
   82C0 48            [ 1]  555 	lsla	
   82C1 BA 98         [ 3]  556 	ora	*(_setIgnitionSchedule_sloc2_1_0 + 2)
   82C3 B7 98         [ 3]  557 	sta	*(_setIgnitionSchedule_sloc2_1_0 + 2)
   82C5 C6 01 74      [ 4]  558 	lda	(_setIgnitionSchedule_PARM_2 + 1)
   82C8 CE 01 73      [ 4]  559 	ldx	_setIgnitionSchedule_PARM_2
   82CB 54            [ 1]  560 	lsrx
   82CC 46            [ 1]  561 	rora
   82CD 54            [ 1]  562 	lsrx
   82CE 46            [ 1]  563 	rora
   82CF 54            [ 1]  564 	lsrx
   82D0 46            [ 1]  565 	rora
   82D1 B7 97         [ 3]  566 	sta	*(_setIgnitionSchedule_sloc2_1_0 + 1)
   82D3 BF 96         [ 3]  567 	stx	*_setIgnitionSchedule_sloc2_1_0
   82D5 B6 99         [ 3]  568 	lda	*(_setIgnitionSchedule_sloc2_1_0 + 3)
   82D7 BE 98         [ 3]  569 	ldx	*(_setIgnitionSchedule_sloc2_1_0 + 2)
   82D9 B7 99         [ 3]  570 	sta	*(_setIgnitionSchedule_sloc2_1_0 + 3)
   82DB BF 98         [ 3]  571 	stx	*(_setIgnitionSchedule_sloc2_1_0 + 2)
   82DD 6E 00 97      [ 4]  572 	mov	#0x00,*(_setIgnitionSchedule_sloc2_1_0 + 1)
   82E0 6E 00 96      [ 4]  573 	mov	#0x00,*_setIgnitionSchedule_sloc2_1_0
   82E3 45 01 7E      [ 3]  574 	ldhx	#_setIgnitionSchedule_startTicks_65536_35
   82E6 5E 96         [ 4]  575 	mov	*_setIgnitionSchedule_sloc2_1_0,x+
   82E8 5E 97         [ 4]  576 	mov	*(_setIgnitionSchedule_sloc2_1_0 + 1),x+
   82EA 5E 98         [ 4]  577 	mov	*(_setIgnitionSchedule_sloc2_1_0 + 2),x+
   82EC 5E 99         [ 4]  578 	mov	*(_setIgnitionSchedule_sloc2_1_0 + 3),x+
                            579 ;scheduler.c:96: durationTicks = US_TO_TIMER1(duration);
   82EE C6 01 78      [ 4]  580 	lda	(_setIgnitionSchedule_PARM_3 + 1)
   82F1 CE 01 77      [ 4]  581 	ldx	_setIgnitionSchedule_PARM_3
   82F4 54            [ 1]  582 	lsrx
   82F5 46            [ 1]  583 	rora
   82F6 54            [ 1]  584 	lsrx
   82F7 46            [ 1]  585 	rora
   82F8 54            [ 1]  586 	lsrx
   82F9 46            [ 1]  587 	rora
   82FA B7 9D         [ 3]  588 	sta	*(_setIgnitionSchedule_sloc3_1_0 + 3)
   82FC BF 9C         [ 3]  589 	stx	*(_setIgnitionSchedule_sloc3_1_0 + 2)
   82FE 6E 00 9B      [ 4]  590 	mov	#0x00,*(_setIgnitionSchedule_sloc3_1_0 + 1)
   8301 6E 00 9A      [ 4]  591 	mov	#0x00,*_setIgnitionSchedule_sloc3_1_0
   8304 45 01 82      [ 3]  592 	ldhx	#_setIgnitionSchedule_durationTicks_65536_35
   8307 5E 9A         [ 4]  593 	mov	*_setIgnitionSchedule_sloc3_1_0,x+
   8309 5E 9B         [ 4]  594 	mov	*(_setIgnitionSchedule_sloc3_1_0 + 1),x+
   830B 5E 9C         [ 4]  595 	mov	*(_setIgnitionSchedule_sloc3_1_0 + 2),x+
   830D 5E 9D         [ 4]  596 	mov	*(_setIgnitionSchedule_sloc3_1_0 + 3),x+
                            597 ;scheduler.c:97: if (durationTicks == 0) { durationTicks = 1; }
   830F B6 9A         [ 3]  598 	lda	*_setIgnitionSchedule_sloc3_1_0
   8311 BA 9B         [ 3]  599 	ora	*(_setIgnitionSchedule_sloc3_1_0 + 1)
   8313 BA 9C         [ 3]  600 	ora	*(_setIgnitionSchedule_sloc3_1_0 + 2)
   8315 BA 9D         [ 3]  601 	ora	*(_setIgnitionSchedule_sloc3_1_0 + 3)
   8317 26 0C         [ 3]  602 	bne	00109$
   8319 45 01 82      [ 3]  603 	ldhx	#_setIgnitionSchedule_durationTicks_65536_35
   831C 4F            [ 1]  604 	clra
   831D F7            [ 2]  605 	sta	,x
   831E E7 01         [ 3]  606 	sta	1,x
   8320 E7 02         [ 3]  607 	sta	2,x
   8322 4C            [ 1]  608 	inca
   8323 E7 03         [ 3]  609 	sta	3,x
   8325                     610 00109$:
                            611 ;scheduler.c:99: totalTicks = startTicks + durationTicks;
   8325 45 01 82      [ 3]  612 	ldhx	#_setIgnitionSchedule_durationTicks_65536_35
   8328 B6 99         [ 3]  613 	lda	*(_setIgnitionSchedule_sloc2_1_0 + 3)
   832A EB 03         [ 3]  614 	add	3,x
   832C B7 9D         [ 3]  615 	sta	*(_setIgnitionSchedule_sloc3_1_0 + 3)
   832E B6 98         [ 3]  616 	lda	*(_setIgnitionSchedule_sloc2_1_0 + 2)
   8330 E9 02         [ 3]  617 	adc	2,x
   8332 B7 9C         [ 3]  618 	sta	*(_setIgnitionSchedule_sloc3_1_0 + 2)
   8334 B6 97         [ 3]  619 	lda	*(_setIgnitionSchedule_sloc2_1_0 + 1)
   8336 E9 01         [ 3]  620 	adc	1,x
   8338 B7 9B         [ 3]  621 	sta	*(_setIgnitionSchedule_sloc3_1_0 + 1)
   833A B6 96         [ 3]  622 	lda	*_setIgnitionSchedule_sloc2_1_0
   833C F9            [ 2]  623 	adc	,x
   833D B7 9A         [ 3]  624 	sta	*_setIgnitionSchedule_sloc3_1_0
                            625 ;scheduler.c:100: minTicks = US_TO_TIMER1(IGNITION_MIN_DELAY_US);
   833F C6 85 BC      [ 4]  626 	lda	(_IGNITION_MIN_DELAY_US + 1)
   8342 CE 85 BB      [ 4]  627 	ldx	_IGNITION_MIN_DELAY_US
   8345 54            [ 1]  628 	lsrx
   8346 46            [ 1]  629 	rora
   8347 54            [ 1]  630 	lsrx
   8348 46            [ 1]  631 	rora
   8349 54            [ 1]  632 	lsrx
   834A 46            [ 1]  633 	rora
   834B B7 A1         [ 3]  634 	sta	*(_setIgnitionSchedule_sloc4_1_0 + 3)
   834D BF A0         [ 3]  635 	stx	*(_setIgnitionSchedule_sloc4_1_0 + 2)
   834F 6E 00 9F      [ 4]  636 	mov	#0x00,*(_setIgnitionSchedule_sloc4_1_0 + 1)
   8352 6E 00 9E      [ 4]  637 	mov	#0x00,*_setIgnitionSchedule_sloc4_1_0
                            638 ;scheduler.c:102: if (startTicks < minTicks) {
   8355 B6 99         [ 3]  639 	lda	*(_setIgnitionSchedule_sloc2_1_0 + 3)
   8357 B0 A1         [ 3]  640 	sub	*(_setIgnitionSchedule_sloc4_1_0 + 3)
   8359 B6 98         [ 3]  641 	lda	*(_setIgnitionSchedule_sloc2_1_0 + 2)
   835B B2 A0         [ 3]  642 	sbc	*(_setIgnitionSchedule_sloc4_1_0 + 2)
   835D B6 97         [ 3]  643 	lda	*(_setIgnitionSchedule_sloc2_1_0 + 1)
   835F B2 9F         [ 3]  644 	sbc	*(_setIgnitionSchedule_sloc4_1_0 + 1)
   8361 B6 96         [ 3]  645 	lda	*_setIgnitionSchedule_sloc2_1_0
   8363 B2 9E         [ 3]  646 	sbc	*_setIgnitionSchedule_sloc4_1_0
   8365 24 45         [ 3]  647 	bcc	00114$
                            648 ;scheduler.c:103: startTicks = minTicks;
   8367 45 01 7E      [ 3]  649 	ldhx	#_setIgnitionSchedule_startTicks_65536_35
   836A 5E 9E         [ 4]  650 	mov	*_setIgnitionSchedule_sloc4_1_0,x+
   836C 5E 9F         [ 4]  651 	mov	*(_setIgnitionSchedule_sloc4_1_0 + 1),x+
   836E 5E A0         [ 4]  652 	mov	*(_setIgnitionSchedule_sloc4_1_0 + 2),x+
   8370 5E A1         [ 4]  653 	mov	*(_setIgnitionSchedule_sloc4_1_0 + 3),x+
                            654 ;scheduler.c:104: if (totalTicks > startTicks) {
   8372 B6 A1         [ 3]  655 	lda	*(_setIgnitionSchedule_sloc4_1_0 + 3)
   8374 B0 9D         [ 3]  656 	sub	*(_setIgnitionSchedule_sloc3_1_0 + 3)
   8376 B6 A0         [ 3]  657 	lda	*(_setIgnitionSchedule_sloc4_1_0 + 2)
   8378 B2 9C         [ 3]  658 	sbc	*(_setIgnitionSchedule_sloc3_1_0 + 2)
   837A B6 9F         [ 3]  659 	lda	*(_setIgnitionSchedule_sloc4_1_0 + 1)
   837C B2 9B         [ 3]  660 	sbc	*(_setIgnitionSchedule_sloc3_1_0 + 1)
   837E B6 9E         [ 3]  661 	lda	*_setIgnitionSchedule_sloc4_1_0
   8380 B2 9A         [ 3]  662 	sbc	*_setIgnitionSchedule_sloc3_1_0
   8382 24 1C         [ 3]  663 	bcc	00111$
                            664 ;scheduler.c:105: durationTicks = totalTicks - startTicks;
   8384 45 01 82      [ 3]  665 	ldhx	#_setIgnitionSchedule_durationTicks_65536_35
   8387 B6 9D         [ 3]  666 	lda	*(_setIgnitionSchedule_sloc3_1_0 + 3)
   8389 B0 A1         [ 3]  667 	sub	*(_setIgnitionSchedule_sloc4_1_0 + 3)
   838B E7 03         [ 3]  668 	sta	3,x
   838D B6 9C         [ 3]  669 	lda	*(_setIgnitionSchedule_sloc3_1_0 + 2)
   838F B2 A0         [ 3]  670 	sbc	*(_setIgnitionSchedule_sloc4_1_0 + 2)
   8391 E7 02         [ 3]  671 	sta	2,x
   8393 B6 9B         [ 3]  672 	lda	*(_setIgnitionSchedule_sloc3_1_0 + 1)
   8395 B2 9F         [ 3]  673 	sbc	*(_setIgnitionSchedule_sloc4_1_0 + 1)
   8397 E7 01         [ 3]  674 	sta	1,x
   8399 B6 9A         [ 3]  675 	lda	*_setIgnitionSchedule_sloc3_1_0
   839B B2 9E         [ 3]  676 	sbc	*_setIgnitionSchedule_sloc4_1_0
   839D F7            [ 2]  677 	sta	,x
   839E 20 0C         [ 3]  678 	bra	00114$
   83A0                     679 00111$:
                            680 ;scheduler.c:107: durationTicks = 1;
   83A0 45 01 82      [ 3]  681 	ldhx	#_setIgnitionSchedule_durationTicks_65536_35
   83A3 4F            [ 1]  682 	clra
   83A4 F7            [ 2]  683 	sta	,x
   83A5 E7 01         [ 3]  684 	sta	1,x
   83A7 E7 02         [ 3]  685 	sta	2,x
   83A9 4C            [ 1]  686 	inca
   83AA E7 03         [ 3]  687 	sta	3,x
   83AC                     688 00114$:
                            689 ;scheduler.h:55: return (uint16_t)((T1CNTH << 8) | T1CNTL);
   83AC B6 21         [ 3]  690 	lda	*0x21
   83AE 5F            [ 1]  691 	clrx
   83AF B7 9E         [ 3]  692 	sta	*_setIgnitionSchedule_sloc4_1_0
   83B1 BF 9F         [ 3]  693 	stx	*(_setIgnitionSchedule_sloc4_1_0 + 1)
   83B3 B6 22         [ 3]  694 	lda	*0x22
   83B5 BA 9F         [ 3]  695 	ora	*(_setIgnitionSchedule_sloc4_1_0 + 1)
   83B7 87            [ 2]  696 	psha
   83B8 9F            [ 1]  697 	txa
   83B9 BA 9E         [ 3]  698 	ora	*_setIgnitionSchedule_sloc4_1_0
   83BB 97            [ 1]  699 	tax
   83BC 86            [ 2]  700 	pula
   83BD C7 01 7D      [ 4]  701 	sta	(_setIgnitionSchedule___1310720006_131072_35 + 1)
   83C0 CF 01 7C      [ 4]  702 	stx	_setIgnitionSchedule___1310720006_131072_35
                            703 ;scheduler.c:112: startTicks16 = (uint16_t)startTicks;
   83C3 C6 01 81      [ 4]  704 	lda	(_setIgnitionSchedule_startTicks_65536_35 + 3)
   83C6 C7 01 87      [ 4]  705 	sta	(_setIgnitionSchedule_startTicks16_65536_35 + 1)
   83C9 C6 01 80      [ 4]  706 	lda	(_setIgnitionSchedule_startTicks_65536_35 + 2)
   83CC C7 01 86      [ 4]  707 	sta	_setIgnitionSchedule_startTicks16_65536_35
                            708 ;scheduler.c:113: durationTicks16 = (uint16_t)durationTicks;
   83CF C6 01 85      [ 4]  709 	lda	(_setIgnitionSchedule_durationTicks_65536_35 + 3)
   83D2 C7 01 89      [ 4]  710 	sta	(_setIgnitionSchedule_durationTicks16_65536_35 + 1)
   83D5 C6 01 84      [ 4]  711 	lda	(_setIgnitionSchedule_durationTicks_65536_35 + 2)
   83D8 C7 01 88      [ 4]  712 	sta	_setIgnitionSchedule_durationTicks16_65536_35
                            713 ;scheduler.c:115: schedule->startCompare = currentCount + startTicks16;
   83DB 55 92         [ 4]  714 	ldhx	*_setIgnitionSchedule_sloc0_1_0
   83DD C6 01 87      [ 4]  715 	lda	(_setIgnitionSchedule_startTicks16_65536_35 + 1)
   83E0 CB 01 7D      [ 4]  716 	add	(_setIgnitionSchedule___1310720006_131072_35 + 1)
   83E3 B7 9F         [ 3]  717 	sta	*(_setIgnitionSchedule_sloc4_1_0 + 1)
   83E5 C6 01 86      [ 4]  718 	lda	_setIgnitionSchedule_startTicks16_65536_35
   83E8 C9 01 7C      [ 4]  719 	adc	_setIgnitionSchedule___1310720006_131072_35
   83EB B7 9E         [ 3]  720 	sta	*_setIgnitionSchedule_sloc4_1_0
   83ED 89            [ 2]  721 	pshx
   83EE 8B            [ 2]  722 	pshh
   83EF B6 9E         [ 3]  723 	lda	*_setIgnitionSchedule_sloc4_1_0
   83F1 E7 01         [ 3]  724 	sta	1,x
   83F3 B6 9F         [ 3]  725 	lda	*(_setIgnitionSchedule_sloc4_1_0 + 1)
   83F5 E7 02         [ 3]  726 	sta	2,x
   83F7 8A            [ 2]  727 	pulh
   83F8 88            [ 2]  728 	pulx
                            729 ;scheduler.c:116: schedule->endCompare = schedule->startCompare + durationTicks16;
   83F9 4E 92 9A      [ 5]  730 	mov	*_setIgnitionSchedule_sloc0_1_0,*_setIgnitionSchedule_sloc3_1_0
   83FC 4E 93 9B      [ 5]  731 	mov	*(_setIgnitionSchedule_sloc0_1_0 + 1),*(_setIgnitionSchedule_sloc3_1_0 + 1)
   83FF E6 01         [ 3]  732 	lda	1,x
   8401 E6 02         [ 3]  733 	lda	2,x
   8403 B6 9F         [ 3]  734 	lda	*(_setIgnitionSchedule_sloc4_1_0 + 1)
   8405 CB 01 89      [ 4]  735 	add	(_setIgnitionSchedule_durationTicks16_65536_35 + 1)
   8408 97            [ 1]  736 	tax
   8409 B6 9E         [ 3]  737 	lda	*_setIgnitionSchedule_sloc4_1_0
   840B C9 01 88      [ 4]  738 	adc	_setIgnitionSchedule_durationTicks16_65536_35
   840E 89            [ 2]  739 	pshx
   840F 55 9A         [ 4]  740 	ldhx	*_setIgnitionSchedule_sloc3_1_0
   8411 E7 03         [ 3]  741 	sta	3,x
   8413 86            [ 2]  742 	pula
   8414 E7 04         [ 3]  743 	sta	4,x
                            744 ;scheduler.c:117: schedule->duration = durationTicks16;
   8416 55 92         [ 4]  745 	ldhx	*_setIgnitionSchedule_sloc0_1_0
   8418 C6 01 88      [ 4]  746 	lda	_setIgnitionSchedule_durationTicks16_65536_35
   841B E7 05         [ 3]  747 	sta	5,x
   841D C6 01 89      [ 4]  748 	lda	(_setIgnitionSchedule_durationTicks16_65536_35 + 1)
   8420 E7 06         [ 3]  749 	sta	6,x
                            750 ;scheduler.c:118: schedule->channel = channel;
   8422 55 94         [ 4]  751 	ldhx	*_setIgnitionSchedule_sloc1_1_0
   8424 C6 01 79      [ 4]  752 	lda	_setIgnitionSchedule_PARM_4
   8427 E7 07         [ 3]  753 	sta	7,x
                            754 ;scheduler.c:119: schedule->status = SCHED_PENDING;
   8429 55 92         [ 4]  755 	ldhx	*_setIgnitionSchedule_sloc0_1_0
   842B A6 01         [ 2]  756 	lda	#0x01
   842D F7            [ 2]  757 	sta	,x
                            758 ;scheduler.c:121: if (channel == 1) {
   842E C6 01 79      [ 4]  759 	lda	_setIgnitionSchedule_PARM_4
   8431 A1 01         [ 2]  760 	cmp	#0x01
   8433 26 24         [ 3]  761 	bne	00116$
                            762 ;scheduler.c:122: armIgnitionCompare(schedule, beginCoil1Charge, endCoil1Charge, (volatile uint16_t *)&T1CH0H);
   8435 A6 81         [ 2]  763 	lda	#>_beginCoil1Charge
   8437 C7 01 6B      [ 4]  764 	sta	_armIgnitionCompare_PARM_2
   843A A6 14         [ 2]  765 	lda	#_beginCoil1Charge
   843C C7 01 6C      [ 4]  766 	sta	(_armIgnitionCompare_PARM_2 + 1)
   843F A6 81         [ 2]  767 	lda	#>_endCoil1Charge
   8441 C7 01 6D      [ 4]  768 	sta	_armIgnitionCompare_PARM_3
   8444 A6 1B         [ 2]  769 	lda	#_endCoil1Charge
   8446 C7 01 6E      [ 4]  770 	sta	(_armIgnitionCompare_PARM_3 + 1)
   8449 4F            [ 1]  771 	clra
   844A C7 01 6F      [ 4]  772 	sta	_armIgnitionCompare_PARM_4
   844D A6 26         [ 2]  773 	lda	#0x26
   844F C7 01 70      [ 4]  774 	sta	(_armIgnitionCompare_PARM_4 + 1)
   8452 B6 93         [ 3]  775 	lda	*(_setIgnitionSchedule_sloc0_1_0 + 1)
   8454 BE 92         [ 3]  776 	ldx	*_setIgnitionSchedule_sloc0_1_0
   8456 CC 81 EA      [ 3]  777 	jmp	_armIgnitionCompare
   8459                     778 00116$:
                            779 ;scheduler.c:124: armIgnitionCompare(schedule, beginCoil2Charge, endCoil2Charge, (volatile uint16_t *)&T1CH1H);
   8459 A6 81         [ 2]  780 	lda	#>_beginCoil2Charge
   845B C7 01 6B      [ 4]  781 	sta	_armIgnitionCompare_PARM_2
   845E A6 22         [ 2]  782 	lda	#_beginCoil2Charge
   8460 C7 01 6C      [ 4]  783 	sta	(_armIgnitionCompare_PARM_2 + 1)
   8463 A6 81         [ 2]  784 	lda	#>_endCoil2Charge
   8465 C7 01 6D      [ 4]  785 	sta	_armIgnitionCompare_PARM_3
   8468 A6 29         [ 2]  786 	lda	#_endCoil2Charge
   846A C7 01 6E      [ 4]  787 	sta	(_armIgnitionCompare_PARM_3 + 1)
   846D 4F            [ 1]  788 	clra
   846E C7 01 6F      [ 4]  789 	sta	_armIgnitionCompare_PARM_4
   8471 A6 29         [ 2]  790 	lda	#0x29
   8473 C7 01 70      [ 4]  791 	sta	(_armIgnitionCompare_PARM_4 + 1)
   8476 B6 93         [ 3]  792 	lda	*(_setIgnitionSchedule_sloc0_1_0 + 1)
   8478 BE 92         [ 3]  793 	ldx	*_setIgnitionSchedule_sloc0_1_0
                            794 ;scheduler.c:126: }
   847A CC 81 EA      [ 3]  795 	jmp	_armIgnitionCompare
                            796 ;------------------------------------------------------------
                            797 ;Allocation info for local variables in function 'clearIgnitionSchedule'
                            798 ;------------------------------------------------------------
                            799 ;schedule                  Allocated with name '_clearIgnitionSchedule_schedule_65536_49'
                            800 ;------------------------------------------------------------
                            801 ;scheduler.c:128: void clearIgnitionSchedule(volatile IgnitionSchedule *schedule) {
                            802 ;	-----------------------------------------
                            803 ;	 function clearIgnitionSchedule
                            804 ;	-----------------------------------------
                            805 ;	Register assignment is optimal.
                            806 ;	Stack space usage: 0 bytes.
   847D                     807 _clearIgnitionSchedule:
   847D C7 01 8B      [ 4]  808 	sta	(_clearIgnitionSchedule_schedule_65536_49 + 1)
   8480 CF 01 8A      [ 4]  809 	stx	_clearIgnitionSchedule_schedule_65536_49
                            810 ;scheduler.c:129: schedule->status = SCHED_OFF;
   8483 C6 01 8A      [ 4]  811 	lda	_clearIgnitionSchedule_schedule_65536_49
   8486 87            [ 2]  812 	psha
   8487 8A            [ 2]  813 	pulh
   8488 CE 01 8B      [ 4]  814 	ldx	(_clearIgnitionSchedule_schedule_65536_49 + 1)
   848B 89            [ 2]  815 	pshx
   848C 8B            [ 2]  816 	pshh
   848D 4F            [ 1]  817 	clra
   848E F7            [ 2]  818 	sta	,x
   848F 8A            [ 2]  819 	pulh
   8490 88            [ 2]  820 	pulx
                            821 ;scheduler.c:130: if (schedule->channel == 1) {
   8491 E6 07         [ 3]  822 	lda	7,x
   8493 A1 01         [ 2]  823 	cmp	#0x01
   8495 26 03         [ 3]  824 	bne	00104$
                            825 ;scheduler.c:131: endCoil1Charge();
   8497 CC 81 1B      [ 3]  826 	jmp	_endCoil1Charge
   849A                     827 00104$:
                            828 ;scheduler.c:132: } else if (schedule->channel == 2) {
   849A E6 07         [ 3]  829 	lda	7,x
   849C A1 02         [ 2]  830 	cmp	#0x02
   849E 26 03         [ 3]  831 	bne	00106$
                            832 ;scheduler.c:133: endCoil2Charge();
   84A0 CD 81 29      [ 5]  833 	jsr	_endCoil2Charge
   84A3                     834 00106$:
                            835 ;scheduler.c:135: }
   84A3 81            [ 4]  836 	rts
                            837 ;------------------------------------------------------------
                            838 ;Allocation info for local variables in function 'isr_tim1_ch0'
                            839 ;------------------------------------------------------------
                            840 ;scheduler.c:138: void isr_tim1_ch0(void) __interrupt(4) {
                            841 ;	-----------------------------------------
                            842 ;	 function isr_tim1_ch0
                            843 ;	-----------------------------------------
                            844 ;	Register assignment is optimal.
                            845 ;	Stack space usage: 0 bytes.
   84A4                     846 _isr_tim1_ch0:
   84A4 8B            [ 2]  847 	pshh
                            848 ;scheduler.c:139: handleIgnitionChannel(&ignitionSchedule1, beginCoil1Charge, endCoil1Charge, (volatile uint16_t *)&T1CH0H);
   84A5 A6 81         [ 2]  849 	lda	#>_beginCoil1Charge
   84A7 C7 01 63      [ 4]  850 	sta	_handleIgnitionChannel_PARM_2
   84AA A6 14         [ 2]  851 	lda	#_beginCoil1Charge
   84AC C7 01 64      [ 4]  852 	sta	(_handleIgnitionChannel_PARM_2 + 1)
   84AF A6 81         [ 2]  853 	lda	#>_endCoil1Charge
   84B1 C7 01 65      [ 4]  854 	sta	_handleIgnitionChannel_PARM_3
   84B4 A6 1B         [ 2]  855 	lda	#_endCoil1Charge
   84B6 C7 01 66      [ 4]  856 	sta	(_handleIgnitionChannel_PARM_3 + 1)
   84B9 4F            [ 1]  857 	clra
   84BA C7 01 67      [ 4]  858 	sta	_handleIgnitionChannel_PARM_4
   84BD A6 26         [ 2]  859 	lda	#0x26
   84BF C7 01 68      [ 4]  860 	sta	(_handleIgnitionChannel_PARM_4 + 1)
   84C2 A6 90         [ 2]  861 	lda	#_ignitionSchedule1
   84C4 AE 01         [ 2]  862 	ldx	#>_ignitionSchedule1
   84C6 CD 81 4F      [ 5]  863 	jsr	_handleIgnitionChannel
                            864 ;scheduler.c:140: }
   84C9 8A            [ 2]  865 	pulh
   84CA 80            [ 7]  866 	rti
                            867 ;------------------------------------------------------------
                            868 ;Allocation info for local variables in function 'isr_tim1_ch1'
                            869 ;------------------------------------------------------------
                            870 ;scheduler.c:142: void isr_tim1_ch1(void) __interrupt(5) {
                            871 ;	-----------------------------------------
                            872 ;	 function isr_tim1_ch1
                            873 ;	-----------------------------------------
                            874 ;	Register assignment is optimal.
                            875 ;	Stack space usage: 0 bytes.
   84CB                     876 _isr_tim1_ch1:
   84CB 8B            [ 2]  877 	pshh
                            878 ;scheduler.c:143: handleIgnitionChannel(&ignitionSchedule2, beginCoil2Charge, endCoil2Charge, (volatile uint16_t *)&T1CH1H);
   84CC A6 81         [ 2]  879 	lda	#>_beginCoil2Charge
   84CE C7 01 63      [ 4]  880 	sta	_handleIgnitionChannel_PARM_2
   84D1 A6 22         [ 2]  881 	lda	#_beginCoil2Charge
   84D3 C7 01 64      [ 4]  882 	sta	(_handleIgnitionChannel_PARM_2 + 1)
   84D6 A6 81         [ 2]  883 	lda	#>_endCoil2Charge
   84D8 C7 01 65      [ 4]  884 	sta	_handleIgnitionChannel_PARM_3
   84DB A6 29         [ 2]  885 	lda	#_endCoil2Charge
   84DD C7 01 66      [ 4]  886 	sta	(_handleIgnitionChannel_PARM_3 + 1)
   84E0 4F            [ 1]  887 	clra
   84E1 C7 01 67      [ 4]  888 	sta	_handleIgnitionChannel_PARM_4
   84E4 A6 29         [ 2]  889 	lda	#0x29
   84E6 C7 01 68      [ 4]  890 	sta	(_handleIgnitionChannel_PARM_4 + 1)
   84E9 A6 98         [ 2]  891 	lda	#_ignitionSchedule2
   84EB AE 01         [ 2]  892 	ldx	#>_ignitionSchedule2
   84ED CD 81 4F      [ 5]  893 	jsr	_handleIgnitionChannel
                            894 ;scheduler.c:144: }
   84F0 8A            [ 2]  895 	pulh
   84F1 80            [ 7]  896 	rti
                            897 	.area CSEG    (CODE)
                            898 	.area CONST   (CODE)
   85BB                     899 _IGNITION_MIN_DELAY_US:
   85BB 00 19               900 	.dw #0x0019
                            901 	.area XINIT   (CODE)
   85AB                     902 __xinit__ignitionSchedule1:
   85AB 00                  903 	.db #0x00	; 0
   85AC 00 00               904 	.dw #0x0000
   85AE 00 00               905 	.dw #0x0000
   85B0 00 00               906 	.dw #0x0000
   85B2 01                  907 	.db #0x01	; 1
   85B3                     908 __xinit__ignitionSchedule2:
   85B3 00                  909 	.db #0x00	; 0
   85B4 00 00               910 	.dw #0x0000
   85B6 00 00               911 	.dw #0x0000
   85B8 00 00               912 	.dw #0x0000
   85BA 02                  913 	.db #0x02	; 2
                            914 	.area CABS    (ABS,CODE)
