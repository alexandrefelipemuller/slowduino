                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 4.2.0 #13081 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module timebase
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
                             22 	.globl _isr_tim2_overflow
                             23 	.globl _timebaseInit
                             24 	.globl _micros
                             25 ;--------------------------------------------------------
                             26 ; ram data
                             27 ;--------------------------------------------------------
                             28 	.area DSEG    (PAG)
                             29 ;--------------------------------------------------------
                             30 ; overlayable items in ram
                             31 ;--------------------------------------------------------
                             32 ;--------------------------------------------------------
                             33 ; absolute ram data
                             34 ;--------------------------------------------------------
                             35 	.area IABS    (ABS)
                             36 	.area IABS    (ABS)
                             37 ;--------------------------------------------------------
                             38 ; absolute external ram data
                             39 ;--------------------------------------------------------
                             40 	.area XABS    (ABS)
                             41 ;--------------------------------------------------------
                             42 ; external initialized ram data
                             43 ;--------------------------------------------------------
                             44 	.area XISEG
                             45 ;--------------------------------------------------------
                             46 ; extended address mode data
                             47 ;--------------------------------------------------------
                             48 	.area XSEG
   00DA                      49 _tim2OverflowCount:
   00DA                      50 	.ds 4
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
                             68 ;Allocation info for local variables in function 'noInterrupts'
                             69 ;------------------------------------------------------------
                             70 ;globals.h:100: static inline void noInterrupts(void) { __asm sei __endasm; }
                             71 ;	-----------------------------------------
                             72 ;	 function noInterrupts
                             73 ;	-----------------------------------------
                             74 ;	Register assignment is optimal.
                             75 ;	Stack space usage: 0 bytes.
   8039                      76 _noInterrupts:
   8039 9B            [ 2]   77 	 sei	
   803A 81            [ 4]   78 	rts
                             79 ;------------------------------------------------------------
                             80 ;Allocation info for local variables in function 'interrupts'
                             81 ;------------------------------------------------------------
                             82 ;globals.h:101: static inline void interrupts(void)   { __asm cli __endasm; }
                             83 ;	-----------------------------------------
                             84 ;	 function interrupts
                             85 ;	-----------------------------------------
                             86 ;	Register assignment is optimal.
                             87 ;	Stack space usage: 0 bytes.
   803B                      88 _interrupts:
   803B 9A            [ 2]   89 	 cli	
   803C 81            [ 4]   90 	rts
                             91 ;------------------------------------------------------------
                             92 ;Allocation info for local variables in function 'timebaseInit'
                             93 ;------------------------------------------------------------
                             94 ;timebase.c:15: void timebaseInit(void) {
                             95 ;	-----------------------------------------
                             96 ;	 function timebaseInit
                             97 ;	-----------------------------------------
                             98 ;	Register assignment is optimal.
                             99 ;	Stack space usage: 0 bytes.
   803D                     100 _timebaseInit:
                            101 ;timebase.c:16: T2SC = (1 << T2SC_TRST);  /* reset do contador */
   803D 6E 10 2B      [ 4]  102 	mov	#0x10,*0x2b
                            103 ;timebase.c:17: T2SC = (1 << T2SC_TOIE);  /* liga overflow interrupt, prescaler /1, roda */
   8040 6E 40 2B      [ 4]  104 	mov	#0x40,*0x2b
                            105 ;timebase.c:18: tim2OverflowCount = 0;
   8043 45 00 DA      [ 3]  106 	ldhx	#_tim2OverflowCount
   8046 4F            [ 1]  107 	clra
   8047 F7            [ 2]  108 	sta	,x
   8048 E7 01         [ 3]  109 	sta	1,x
   804A E7 02         [ 3]  110 	sta	2,x
   804C E7 03         [ 3]  111 	sta	3,x
                            112 ;timebase.c:19: }
   804E 81            [ 4]  113 	rts
                            114 ;------------------------------------------------------------
                            115 ;Allocation info for local variables in function 'micros'
                            116 ;------------------------------------------------------------
                            117 ;overflows                 Allocated to stack - sp +1
                            118 ;count                     Allocated to registers x h 
                            119 ;sloc0                     Allocated to stack - sp +13
                            120 ;sloc1                     Allocated to stack - sp +9
                            121 ;sloc2                     Allocated to stack - sp +5
                            122 ;------------------------------------------------------------
                            123 ;timebase.c:21: uint32_t micros(void) {
                            124 ;	-----------------------------------------
                            125 ;	 function micros
                            126 ;	-----------------------------------------
                            127 ;	Register assignment is optimal.
                            128 ;	Stack space usage: 14 bytes.
   804F                     129 _micros:
   804F A7 F2         [ 2]  130 	ais	#-14
                            131 ;timebase.c:30: }
   8051 85            [ 1]  132 	tpa
   8052 9B            [ 2]  133 	sei
   8053 87            [ 2]  134 	psha
                            135 ;timebase.c:28: overflows = tim2OverflowCount;
   8054 95            [ 2]  136 	tsx
   8055 45 00 DA      [ 3]  137 	ldhx	#_tim2OverflowCount
   8058 F6            [ 2]  138 	lda	,x
   8059 9E E7 02      [ 4]  139 	sta	2,s
   805C E6 01         [ 3]  140 	lda	1,x
   805E 9E E7 03      [ 4]  141 	sta	3,s
   8061 E6 02         [ 3]  142 	lda	2,x
   8063 9E E7 04      [ 4]  143 	sta	4,s
   8066 E6 03         [ 3]  144 	lda	3,x
   8068 9E E7 05      [ 4]  145 	sta	5,s
                            146 ;timebase.c:29: count = (uint16_t)((T2CNTH << 8) | T2CNTL);
   806B B6 2C         [ 3]  147 	lda	*0x2c
   806D 5F            [ 1]  148 	clrx
   806E 9E E7 0E      [ 4]  149 	sta	14,s
   8071 9E EF 0F      [ 4]  150 	stx	15,s
   8074 BE 2D         [ 3]  151 	ldx	*0x2d
   8076 8C            [ 1]  152 	clrh
   8077 9F            [ 1]  153 	txa
   8078 9E EA 0F      [ 4]  154 	ora	15,s
   807B 97            [ 1]  155 	tax
   807C 8B            [ 2]  156 	pshh
   807D 86            [ 2]  157 	pula
   807E 9E EA 0E      [ 4]  158 	ora	14,s
   8081 87            [ 2]  159 	psha
   8082 8A            [ 2]  160 	pulh
   8083 86            [ 2]  161 	pula
   8084 84            [ 2]  162 	tap
                            163 ;timebase.c:33: return (overflows << 13) + (count >> 3);
   8085 89            [ 2]  164 	pshx
   8086 9E E6 04      [ 4]  165 	lda	4,s
   8089 9E EE 03      [ 4]  166 	ldx	3,s
   808C 48            [ 1]  167 	lsla
   808D 59            [ 1]  168 	rolx
   808E 48            [ 1]  169 	lsla
   808F 59            [ 1]  170 	rolx
   8090 48            [ 1]  171 	lsla
   8091 59            [ 1]  172 	rolx
   8092 48            [ 1]  173 	lsla
   8093 59            [ 1]  174 	rolx
   8094 48            [ 1]  175 	lsla
   8095 59            [ 1]  176 	rolx
   8096 9E E7 0B      [ 4]  177 	sta	11,s
   8099 9E EF 0A      [ 4]  178 	stx	10,s
   809C 88            [ 2]  179 	pulx
   809D 9E E6 04      [ 4]  180 	lda	4,s
   80A0 62            [ 3]  181 	nsa	
   80A1 A4 F0         [ 2]  182 	and	#0xf0
   80A3 48            [ 1]  183 	lsla	
   80A4 9E E7 0B      [ 4]  184 	sta	11,s
   80A7 9E E6 04      [ 4]  185 	lda	4,s
   80AA 44            [ 1]  186 	lsra	
   80AB 44            [ 1]  187 	lsra	
   80AC 44            [ 1]  188 	lsra	
   80AD 9E EA 0A      [ 4]  189 	ora	10,s
   80B0 9E E7 0A      [ 4]  190 	sta	10,s
   80B3 4F            [ 1]  191 	clra
   80B4 9E E7 0C      [ 4]  192 	sta	12,s
   80B7 9F            [ 1]  193 	txa
   80B8 8B            [ 2]  194 	pshh
   80B9 88            [ 2]  195 	pulx
   80BA 54            [ 1]  196 	lsrx
   80BB 46            [ 1]  197 	rora
   80BC 54            [ 1]  198 	lsrx
   80BD 46            [ 1]  199 	rora
   80BE 54            [ 1]  200 	lsrx
   80BF 46            [ 1]  201 	rora
   80C0 9E E7 08      [ 4]  202 	sta	8,s
   80C3 9E EF 07      [ 4]  203 	stx	7,s
   80C6 87            [ 2]  204 	psha
   80C7 4F            [ 1]  205 	clra
   80C8 9E E7 07      [ 4]  206 	sta	7,s
   80CB 4F            [ 1]  207 	clra
   80CC 9E E7 06      [ 4]  208 	sta	6,s
   80CF 86            [ 2]  209 	pula
   80D0 95            [ 2]  210 	tsx
   80D1 E6 0B         [ 3]  211 	lda	11,x
   80D3 EB 07         [ 3]  212 	add	7,x
   80D5 E7 07         [ 3]  213 	sta	7,x
   80D7 E6 0A         [ 3]  214 	lda	10,x
   80D9 E9 06         [ 3]  215 	adc	6,x
   80DB E7 06         [ 3]  216 	sta	6,x
   80DD E6 09         [ 3]  217 	lda	9,x
   80DF E9 05         [ 3]  218 	adc	5,x
   80E1 E7 05         [ 3]  219 	sta	5,x
   80E3 E6 08         [ 3]  220 	lda	8,x
   80E5 E9 04         [ 3]  221 	adc	4,x
   80E7 E7 04         [ 3]  222 	sta	4,x
   80E9 E6 04         [ 3]  223 	lda	4,x
   80EB B7 4B         [ 3]  224 	sta	*___SDCC_hc08_ret3
   80ED E6 05         [ 3]  225 	lda	5,x
   80EF B7 4A         [ 3]  226 	sta	*___SDCC_hc08_ret2
   80F1 EE 06         [ 3]  227 	ldx	6,x
   80F3 9E E6 08      [ 4]  228 	lda	8,s
                            229 ;timebase.c:34: }
   80F6 A7 0E         [ 2]  230 	ais	#14
   80F8 81            [ 4]  231 	rts
                            232 ;------------------------------------------------------------
                            233 ;Allocation info for local variables in function 'isr_tim2_overflow'
                            234 ;------------------------------------------------------------
                            235 ;sloc0                     Allocated to stack - sp +1
                            236 ;------------------------------------------------------------
                            237 ;timebase.c:36: void isr_tim2_overflow(void) __interrupt(9) {
                            238 ;	-----------------------------------------
                            239 ;	 function isr_tim2_overflow
                            240 ;	-----------------------------------------
                            241 ;	Register assignment is optimal.
                            242 ;	Stack space usage: 4 bytes.
   80F9                     243 _isr_tim2_overflow:
   80F9 8B            [ 2]  244 	pshh
   80FA A7 FC         [ 2]  245 	ais	#-4
                            246 ;timebase.c:37: if (T2SC & (1 << T2SC_TOF)) {
   80FC B6 2B         [ 3]  247 	lda	*0x2b
   80FE 2A 3C         [ 3]  248 	bpl     00103$
                            249 ;timebase.c:38: tim2OverflowCount++;
   8100 95            [ 2]  250 	tsx
   8101 45 00 DA      [ 3]  251 	ldhx	#_tim2OverflowCount
   8104 F6            [ 2]  252 	lda	,x
   8105 9E E7 01      [ 4]  253 	sta	1,s
   8108 E6 01         [ 3]  254 	lda	1,x
   810A 9E E7 02      [ 4]  255 	sta	2,s
   810D E6 02         [ 3]  256 	lda	2,x
   810F 9E E7 03      [ 4]  257 	sta	3,s
   8112 E6 03         [ 3]  258 	lda	3,x
   8114 9E E7 04      [ 4]  259 	sta	4,s
   8117 95            [ 2]  260 	tsx
   8118 45 00 DA      [ 3]  261 	ldhx	#_tim2OverflowCount
   811B 9E E6 04      [ 4]  262 	lda	4,s
   811E AB 01         [ 2]  263 	add	#0x01
   8120 E7 03         [ 3]  264 	sta	3,x
   8122 9E E6 03      [ 4]  265 	lda	3,s
   8125 A9 00         [ 2]  266 	adc	#0
   8127 E7 02         [ 3]  267 	sta	2,x
   8129 9E E6 02      [ 4]  268 	lda	2,s
   812C A9 00         [ 2]  269 	adc	#0
   812E E7 01         [ 3]  270 	sta	1,x
   8130 9E E6 01      [ 4]  271 	lda	1,s
   8133 A9 00         [ 2]  272 	adc	#0
   8135 F7            [ 2]  273 	sta	,x
                            274 ;timebase.c:39: T2SC &= (uint8_t)~(1 << T2SC_TOF);  /* limpa flag (write 0 apos leitura) */
   8136 B6 2B         [ 3]  275 	lda	*0x2b
   8138 A4 7F         [ 2]  276 	and	#0x7f
   813A B7 2B         [ 3]  277 	sta	*0x2b
   813C                     278 00103$:
                            279 ;timebase.c:41: }
   813C A7 04         [ 2]  280 	ais	#4
   813E 8A            [ 2]  281 	pulh
   813F 80            [ 7]  282 	rti
                            283 	.area CSEG    (CODE)
                            284 	.area CONST   (CODE)
                            285 	.area XINIT   (CODE)
                            286 	.area CABS    (ABS,CODE)
