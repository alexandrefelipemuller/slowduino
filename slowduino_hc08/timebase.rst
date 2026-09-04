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
   0080                      29 _isr_tim2_overflow_sloc0_1_0:
   0080                      30 	.ds 4
                             31 ;--------------------------------------------------------
                             32 ; overlayable items in ram
                             33 ;--------------------------------------------------------
                             34 	.area	OSEG    (PAG, OVR)
   00B0                      35 _micros_sloc0_1_0:
   00B0                      36 	.ds 2
   00B2                      37 _micros_sloc1_1_0:
   00B2                      38 	.ds 4
   00B6                      39 _micros_sloc2_1_0:
   00B6                      40 	.ds 4
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
                             54 ;--------------------------------------------------------
                             55 ; extended address mode data
                             56 ;--------------------------------------------------------
                             57 	.area XSEG
   0159                      58 _tim2OverflowCount:
   0159                      59 	.ds 4
   015D                      60 _micros_overflows_65536_6:
   015D                      61 	.ds 4
   0161                      62 _micros_count_65536_6:
   0161                      63 	.ds 2
                             64 ;--------------------------------------------------------
                             65 ; global & static initialisations
                             66 ;--------------------------------------------------------
                             67 	.area HOME    (CODE)
                             68 	.area GSINIT  (CODE)
                             69 	.area GSFINAL (CODE)
                             70 	.area GSINIT  (CODE)
                             71 ;--------------------------------------------------------
                             72 ; Home
                             73 ;--------------------------------------------------------
                             74 	.area HOME    (CODE)
                             75 	.area HOME    (CODE)
                             76 ;--------------------------------------------------------
                             77 ; code
                             78 ;--------------------------------------------------------
                             79 	.area CSEG    (CODE)
                             80 ;------------------------------------------------------------
                             81 ;Allocation info for local variables in function 'timebaseInit'
                             82 ;------------------------------------------------------------
                             83 ;timebase.c:14: void timebaseInit(void) {
                             84 ;	-----------------------------------------
                             85 ;	 function timebaseInit
                             86 ;	-----------------------------------------
                             87 ;	Register assignment is optimal.
                             88 ;	Stack space usage: 0 bytes.
   802C                      89 _timebaseInit:
                             90 ;timebase.c:15: T2SC = (1 << T2SC_TRST);  /* reset do contador */
   802C 6E 10 2B      [ 4]   91 	mov	#0x10,*0x2b
                             92 ;timebase.c:16: T2SC = (1 << T2SC_TOIE);  /* liga overflow interrupt, prescaler /1, roda */
   802F 6E 40 2B      [ 4]   93 	mov	#0x40,*0x2b
                             94 ;timebase.c:17: tim2OverflowCount = 0;
   8032 45 01 59      [ 3]   95 	ldhx	#_tim2OverflowCount
   8035 4F            [ 1]   96 	clra
   8036 F7            [ 2]   97 	sta	,x
   8037 E7 01         [ 3]   98 	sta	1,x
   8039 E7 02         [ 3]   99 	sta	2,x
   803B E7 03         [ 3]  100 	sta	3,x
                            101 ;timebase.c:18: }
   803D 81            [ 4]  102 	rts
                            103 ;------------------------------------------------------------
                            104 ;Allocation info for local variables in function 'micros'
                            105 ;------------------------------------------------------------
                            106 ;overflows                 Allocated with name '_micros_overflows_65536_6'
                            107 ;count                     Allocated with name '_micros_count_65536_6'
                            108 ;sloc0                     Allocated with name '_micros_sloc0_1_0'
                            109 ;sloc1                     Allocated with name '_micros_sloc1_1_0'
                            110 ;sloc2                     Allocated with name '_micros_sloc2_1_0'
                            111 ;------------------------------------------------------------
                            112 ;timebase.c:20: uint32_t micros(void) {
                            113 ;	-----------------------------------------
                            114 ;	 function micros
                            115 ;	-----------------------------------------
                            116 ;	Register assignment is optimal.
                            117 ;	Stack space usage: 0 bytes.
   803E                     118 _micros:
                            119 ;timebase.c:26: __asm sei __endasm;
   803E 9B            [ 2]  120 	 sei	
                            121 ;timebase.c:27: overflows = tim2OverflowCount;
   803F 45 01 5D      [ 3]  122 	ldhx	#_micros_overflows_65536_6
   8042 C6 01 59      [ 4]  123 	lda	_tim2OverflowCount
   8045 F7            [ 2]  124 	sta	,x
   8046 C6 01 5A      [ 4]  125 	lda	(_tim2OverflowCount + 1)
   8049 E7 01         [ 3]  126 	sta	1,x
   804B C6 01 5B      [ 4]  127 	lda	(_tim2OverflowCount + 2)
   804E E7 02         [ 3]  128 	sta	2,x
   8050 C6 01 5C      [ 4]  129 	lda	(_tim2OverflowCount + 3)
   8053 E7 03         [ 3]  130 	sta	3,x
                            131 ;timebase.c:28: count = (uint16_t)((T2CNTH << 8) | T2CNTL);
   8055 B6 2C         [ 3]  132 	lda	*0x2c
   8057 5F            [ 1]  133 	clrx
   8058 B7 B0         [ 3]  134 	sta	*_micros_sloc0_1_0
   805A BF B1         [ 3]  135 	stx	*(_micros_sloc0_1_0 + 1)
   805C B6 2D         [ 3]  136 	lda	*0x2d
   805E BA B1         [ 3]  137 	ora	*(_micros_sloc0_1_0 + 1)
   8060 87            [ 2]  138 	psha
   8061 9F            [ 1]  139 	txa
   8062 BA B0         [ 3]  140 	ora	*_micros_sloc0_1_0
   8064 97            [ 1]  141 	tax
   8065 86            [ 2]  142 	pula
   8066 C7 01 62      [ 4]  143 	sta	(_micros_count_65536_6 + 1)
   8069 CF 01 61      [ 4]  144 	stx	_micros_count_65536_6
                            145 ;timebase.c:29: __asm cli __endasm;
   806C 9A            [ 2]  146 	 cli	
                            147 ;timebase.c:32: return (overflows << 13) + (count >> 3);
   806D C6 01 5F      [ 4]  148 	lda	(_micros_overflows_65536_6 + 2)
   8070 CE 01 5E      [ 4]  149 	ldx	(_micros_overflows_65536_6 + 1)
   8073 48            [ 1]  150 	lsla
   8074 59            [ 1]  151 	rolx
   8075 48            [ 1]  152 	lsla
   8076 59            [ 1]  153 	rolx
   8077 48            [ 1]  154 	lsla
   8078 59            [ 1]  155 	rolx
   8079 48            [ 1]  156 	lsla
   807A 59            [ 1]  157 	rolx
   807B 48            [ 1]  158 	lsla
   807C 59            [ 1]  159 	rolx
   807D B7 B3         [ 3]  160 	sta	*(_micros_sloc1_1_0 + 1)
   807F BF B2         [ 3]  161 	stx	*_micros_sloc1_1_0
   8081 C6 01 60      [ 4]  162 	lda	(_micros_overflows_65536_6 + 3)
   8084 62            [ 3]  163 	nsa	
   8085 A4 F0         [ 2]  164 	and	#0xf0
   8087 48            [ 1]  165 	lsla	
   8088 B7 B4         [ 3]  166 	sta	*(_micros_sloc1_1_0 + 2)
   808A C6 01 60      [ 4]  167 	lda	(_micros_overflows_65536_6 + 3)
   808D 44            [ 1]  168 	lsra	
   808E 44            [ 1]  169 	lsra	
   808F 44            [ 1]  170 	lsra	
   8090 BA B3         [ 3]  171 	ora	*(_micros_sloc1_1_0 + 1)
   8092 B7 B3         [ 3]  172 	sta	*(_micros_sloc1_1_0 + 1)
   8094 6E 00 B5      [ 4]  173 	mov	#0x00,*(_micros_sloc1_1_0 + 3)
   8097 C6 01 62      [ 4]  174 	lda	(_micros_count_65536_6 + 1)
   809A CE 01 61      [ 4]  175 	ldx	_micros_count_65536_6
   809D 54            [ 1]  176 	lsrx
   809E 46            [ 1]  177 	rora
   809F 54            [ 1]  178 	lsrx
   80A0 46            [ 1]  179 	rora
   80A1 54            [ 1]  180 	lsrx
   80A2 46            [ 1]  181 	rora
   80A3 B7 B9         [ 3]  182 	sta	*(_micros_sloc2_1_0 + 3)
   80A5 BF B8         [ 3]  183 	stx	*(_micros_sloc2_1_0 + 2)
   80A7 6E 00 B7      [ 4]  184 	mov	#0x00,*(_micros_sloc2_1_0 + 1)
   80AA 6E 00 B6      [ 4]  185 	mov	#0x00,*_micros_sloc2_1_0
   80AD B6 B5         [ 3]  186 	lda	*(_micros_sloc1_1_0 + 3)
   80AF BB B9         [ 3]  187 	add	*(_micros_sloc2_1_0 + 3)
   80B1 B7 B9         [ 3]  188 	sta	*(_micros_sloc2_1_0 + 3)
   80B3 B6 B4         [ 3]  189 	lda	*(_micros_sloc1_1_0 + 2)
   80B5 B9 B8         [ 3]  190 	adc	*(_micros_sloc2_1_0 + 2)
   80B7 B7 B8         [ 3]  191 	sta	*(_micros_sloc2_1_0 + 2)
   80B9 B6 B3         [ 3]  192 	lda	*(_micros_sloc1_1_0 + 1)
   80BB B9 B7         [ 3]  193 	adc	*(_micros_sloc2_1_0 + 1)
   80BD B7 B7         [ 3]  194 	sta	*(_micros_sloc2_1_0 + 1)
   80BF B6 B2         [ 3]  195 	lda	*_micros_sloc1_1_0
   80C1 B9 B6         [ 3]  196 	adc	*_micros_sloc2_1_0
   80C3 B7 B6         [ 3]  197 	sta	*_micros_sloc2_1_0
   80C5 4E B6 AB      [ 5]  198 	mov	*_micros_sloc2_1_0,*___SDCC_hc08_ret3
   80C8 4E B7 AA      [ 5]  199 	mov	*(_micros_sloc2_1_0 + 1),*___SDCC_hc08_ret2
   80CB BE B8         [ 3]  200 	ldx	*(_micros_sloc2_1_0 + 2)
   80CD B6 B9         [ 3]  201 	lda	*(_micros_sloc2_1_0 + 3)
                            202 ;timebase.c:33: }
   80CF 81            [ 4]  203 	rts
                            204 ;------------------------------------------------------------
                            205 ;Allocation info for local variables in function 'isr_tim2_overflow'
                            206 ;------------------------------------------------------------
                            207 ;sloc0                     Allocated with name '_isr_tim2_overflow_sloc0_1_0'
                            208 ;------------------------------------------------------------
                            209 ;timebase.c:35: void isr_tim2_overflow(void) __interrupt(9) {
                            210 ;	-----------------------------------------
                            211 ;	 function isr_tim2_overflow
                            212 ;	-----------------------------------------
                            213 ;	Register assignment is optimal.
                            214 ;	Stack space usage: 0 bytes.
   80D0                     215 _isr_tim2_overflow:
   80D0 8B            [ 2]  216 	pshh
                            217 ;timebase.c:36: if (T2SC & (1 << T2SC_TOF)) {
   80D1 B6 2B         [ 3]  218 	lda	*0x2b
   80D3 2A 2B         [ 3]  219 	bpl     00103$
                            220 ;timebase.c:37: tim2OverflowCount++;
   80D5 45 01 59      [ 3]  221 	ldhx	#_tim2OverflowCount
   80D8 7E 80         [ 4]  222 	mov	,x+,*_isr_tim2_overflow_sloc0_1_0
   80DA 7E 81         [ 4]  223 	mov	,x+,*(_isr_tim2_overflow_sloc0_1_0 + 1)
   80DC 7E 82         [ 4]  224 	mov	,x+,*(_isr_tim2_overflow_sloc0_1_0 + 2)
   80DE 7E 83         [ 4]  225 	mov	,x+,*(_isr_tim2_overflow_sloc0_1_0 + 3)
   80E0 45 01 59      [ 3]  226 	ldhx	#_tim2OverflowCount
   80E3 B6 83         [ 3]  227 	lda	*(_isr_tim2_overflow_sloc0_1_0 + 3)
   80E5 AB 01         [ 2]  228 	add	#0x01
   80E7 E7 03         [ 3]  229 	sta	3,x
   80E9 B6 82         [ 3]  230 	lda	*(_isr_tim2_overflow_sloc0_1_0 + 2)
   80EB A9 00         [ 2]  231 	adc	#0
   80ED E7 02         [ 3]  232 	sta	2,x
   80EF B6 81         [ 3]  233 	lda	*(_isr_tim2_overflow_sloc0_1_0 + 1)
   80F1 A9 00         [ 2]  234 	adc	#0
   80F3 E7 01         [ 3]  235 	sta	1,x
   80F5 B6 80         [ 3]  236 	lda	*_isr_tim2_overflow_sloc0_1_0
   80F7 A9 00         [ 2]  237 	adc	#0
   80F9 F7            [ 2]  238 	sta	,x
                            239 ;timebase.c:38: T2SC &= (uint8_t)~(1 << T2SC_TOF);  /* limpa flag (write 0 apos leitura) */
   80FA B6 2B         [ 3]  240 	lda	*0x2b
   80FC A4 7F         [ 2]  241 	and	#0x7f
   80FE B7 2B         [ 3]  242 	sta	*0x2b
   8100                     243 00103$:
                            244 ;timebase.c:40: }
   8100 8A            [ 2]  245 	pulh
   8101 80            [ 7]  246 	rti
                            247 	.area CSEG    (CODE)
                            248 	.area CONST   (CODE)
                            249 	.area XINIT   (CODE)
                            250 	.area CABS    (ABS,CODE)
