;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.2.0 #13081 (Linux)
;--------------------------------------------------------
	.module comms
	.optsdcc -mhc08
	
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
	.area XINIT   (CODE)
	.area CONST   (CODE)
	.area DSEG    (PAG)
	.area OSEG    (PAG, OVR)
	.area XSEG
	.area XISEG
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _pageSize
	.globl ___memcpy
	.globl _strlen
	.globl _sciPrintString
	.globl _sciWriteBytes
	.globl _sciWriteByte
	.globl _sciReadByte
	.globl _sciAvailable
	.globl _sciInit
	.globl _saveAllConfig
	.globl _eepromWriteI8
	.globl _eepromWriteByte
	.globl _eepromReadI8
	.globl _eepromReadByte
	.globl _commsInit
	.globl _calculateCRC32
	.globl _sendByte
	.globl _sendBytes
	.globl _sendU16
	.globl _sendU16BE
	.globl _sendU32BE
	.globl _commsProcess
	.globl _processLegacyCommand
	.globl _sendRealtimeData
	.globl _sendFirmwareVersion
	.globl _sendProductString
	.globl _sendProtocolVersion
	.globl _sendTestComm
	.globl _processModernCommand
	.globl _getPageSize
	.globl _sendPageValues
	.globl _writePageValues
	.globl _sendPageCRC32
	.globl _sendOutputChannels
	.globl _burnEEPROM
	.globl _realtimeByte
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DSEG    (PAG)
;--------------------------------------------------------
; overlayable items in ram
;--------------------------------------------------------
;--------------------------------------------------------
; absolute ram data
;--------------------------------------------------------
	.area IABS    (ABS)
	.area IABS    (ABS)
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG
_serialBytesReceived:
	.ds 1
_modernProtocol:
	.ds 1
_expectedLength:
	.ds 1
;--------------------------------------------------------
; extended address mode data
;--------------------------------------------------------
	.area XSEG
_serialBuffer:
	.ds 24
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'noInterrupts'
;------------------------------------------------------------
;globals.h:100: static inline void noInterrupts(void) { __asm sei __endasm; }
;	-----------------------------------------
;	 function noInterrupts
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_noInterrupts:
	 sei	
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'interrupts'
;------------------------------------------------------------
;globals.h:101: static inline void interrupts(void)   { __asm cli __endasm; }
;	-----------------------------------------
;	 function interrupts
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_interrupts:
	 cli	
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'interpolate'
;------------------------------------------------------------
;x1                        Allocated to stack - sp +11
;x2                        Allocated to stack - sp +13
;y1                        Allocated to stack - sp +15
;y2                        Allocated to stack - sp +17
;x                         Allocated to registers a x 
;sloc0                     Allocated to stack - sp +1
;sloc1                     Allocated to stack - sp +5
;------------------------------------------------------------
;tables.h:33: static inline int16_t interpolate(int16_t x, int16_t x1, int16_t x2, int16_t y1, int16_t y2) {
;	-----------------------------------------
;	 function interpolate
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 8 bytes.
_interpolate:
	ais	#-8
;tables.h:34: if (x2 == x1) return y1;
	psha
	lda	15,s
	cmp	13,s
	pula
	bne	00110$
	psha
	lda	14,s
	cmp	12,s
	pula
	beq	00111$
00110$:
	bra	00102$
00111$:
	tsx
	ldx	14,x
	lda	16,s
	jmp	00103$
00102$:
;tables.h:35: return (int16_t)(y1 + (int32_t)(x - x1) * (y2 - y1) / (x2 - x1));
	sub	12,s
	psha
	txa
	sbc	12,s
	tax
	pula
	sta	4,s
	txa
	sta	3,s
	rola	
	clra	
	sbc	#0x00
	sta	2,s
	sta	1,s
	lda	18,s
	sub	16,s
	psha
	lda	18,s
	sbc	16,s
	tax
	pula
	sta	8,s
	txa
	sta	7,s
	rola	
	clra	
	sbc	#0x00
	sta	6,s
	sta	5,s
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	jsr	__mullong
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#8
	lda	14,s
	sub	12,s
	psha
	lda	14,s
	sbc	12,s
	tax
	pula
	sta	4,s
	txa
	sta	3,s
	rola	
	clra	
	sbc	#0x00
	sta	2,s
	sta	1,s
	tsx
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	jsr	__divslong
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#8
	lda	8,s
	ldx	7,s
	add	16,s
	psha
	txa
	adc	16,s
	tax
	pula
00103$:
;tables.h:36: }
	ais	#8
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'crc32Update'
;------------------------------------------------------------
;crc                       Allocated to stack - sp +11
;dataByte                  Allocated to stack - sp +15
;index                     Allocated to registers a 
;sloc0                     Allocated to stack - sp +1
;sloc1                     Allocated to stack - sp +5
;------------------------------------------------------------
;comms.c:95: static uint32_t crc32Update(uint32_t crc, uint8_t dataByte) {
;	-----------------------------------------
;	 function crc32Update
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 8 bytes.
_crc32Update:
	ais	#-8
;comms.c:96: uint8_t index = (uint8_t)((crc ^ dataByte) & 0xFF);
	tsx
	lda	13,x
	eor	14,x
;comms.c:97: return (crc >> 8) ^ crc32_table[index];
	psha
	lda	12,x
	sta	3,x
	lda	11,x
	sta	2,x
	lda	10,x
	sta	1,x
	clrx
	stx	2,s
	pula
	ldx	#0x04
	mul
	pshx
	pulh
	tax
	lda	(_crc32_table),x
	sta	5,s
	lda	(_crc32_table+1),x
	sta	6,s
	lda	(_crc32_table+2),x
	sta	7,s
	lda	(_crc32_table+3),x
	sta	8,s
	tsx
	lda	3,x
	eor	7,x
	sta	7,x
	lda	2,x
	eor	6,x
	sta	6,x
	lda	1,x
	eor	5,x
	sta	5,x
	lda	,x
	eor	4,x
	sta	4,x
	lda	4,x
	sta	*___SDCC_hc08_ret3
	lda	5,x
	sta	*___SDCC_hc08_ret2
	ldx	6,x
	lda	8,s
;comms.c:98: }
	ais	#8
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'clampU8'
;------------------------------------------------------------
;value                     Allocated to stack - sp +1
;------------------------------------------------------------
;comms.c:100: static uint8_t clampU8(int16_t value) {
;	-----------------------------------------
;	 function clampU8
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_clampU8:
	psha
	pshx
;comms.c:101: if (value < 0) return 0;
	pulh
	pulx
	pshx
	pshh
	cphx	#0x0000
	bge	00102$
	clra
	bra	00105$
00102$:
;comms.c:102: if (value > 255) return 255;
	cphx	#0x00ff
	ble	00104$
	lda	#0xff
	bra	00105$
00104$:
;comms.c:103: return (uint8_t)value;
	tsx
	lda	1,x
00105$:
;comms.c:104: }
	ais	#2
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'encodeIgnitionValue'
;------------------------------------------------------------
;advance                   Allocated to registers a 
;------------------------------------------------------------
;comms.c:106: static uint8_t encodeIgnitionValue(int8_t advance) {
;	-----------------------------------------
;	 function encodeIgnitionValue
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_encodeIgnitionValue:
;comms.c:107: return clampU8((int16_t)advance + 40);
	psha
	rola	
	clra	
	sbc	#0x00
	tax
	pula
	add	#0x28
	bcc	00103$
	incx
00103$:
;comms.c:108: }
	jmp	_clampU8
;------------------------------------------------------------
;Allocation info for local variables in function 'decodeIgnitionValue'
;------------------------------------------------------------
;stored                    Allocated to registers a 
;------------------------------------------------------------
;comms.c:110: static int8_t decodeIgnitionValue(uint8_t stored) {
;	-----------------------------------------
;	 function decodeIgnitionValue
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_decodeIgnitionValue:
;comms.c:111: return (int8_t)((int16_t)stored - 40);
	sub	#0x28
;comms.c:112: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'encodeRpmBin'
;------------------------------------------------------------
;rpm                       Allocated to registers x h 
;------------------------------------------------------------
;comms.c:114: static uint8_t encodeRpmBin(uint16_t rpm) {
;	-----------------------------------------
;	 function encodeRpmBin
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_encodeRpmBin:
	pshx
	tax
	pulh
;comms.c:115: return clampU8((int16_t)(rpm / 100));
	lda	#0x64
	psha
	clra
	psha
	txa
	pshh
	pulx
	jsr	__divuint
	ais	#2
;comms.c:116: }
	jmp	_clampU8
;------------------------------------------------------------
;Allocation info for local variables in function 'decodeRpmBin'
;------------------------------------------------------------
;stored                    Allocated to registers a 
;------------------------------------------------------------
;comms.c:118: static uint16_t decodeRpmBin(uint8_t stored) {
;	-----------------------------------------
;	 function decodeRpmBin
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_decodeRpmBin:
;comms.c:119: return (uint16_t)stored * 100U;
	clrx
	psha
	pshx
	lda	#0x64
	jsr	__mulint
	ais	#2
;comms.c:120: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'getFreeRam'
;------------------------------------------------------------
;comms.c:125: static uint16_t getFreeRam(void) {
;	-----------------------------------------
;	 function getFreeRam
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_getFreeRam:
;comms.c:126: return 0;
	clra
	tax
;comms.c:127: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'commsInit'
;------------------------------------------------------------
;comms.c:135: void commsInit(void) {
;	-----------------------------------------
;	 function commsInit
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_commsInit:
;comms.c:136: sciInit();
	jsr	_sciInit
;comms.c:137: serialBytesReceived = 0;
	clra
	sta	_serialBytesReceived
;comms.c:138: modernProtocol = false;
	sta	_modernProtocol
;comms.c:139: expectedLength = 0;
	sta	_expectedLength
;comms.c:140: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'calculateCRC32'
;------------------------------------------------------------
;length                    Allocated to stack - sp +15
;data                      Allocated to stack - sp +11
;crc                       Allocated to stack - sp +1
;i                         Allocated to registers x h 
;sloc0                     Allocated to stack - sp +9
;sloc1                     Allocated to stack - sp +5
;------------------------------------------------------------
;comms.c:145: uint32_t calculateCRC32(const uint8_t *data, uint16_t length) {
;	-----------------------------------------
;	 function calculateCRC32
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 12 bytes.
_calculateCRC32:
	psha
	pshx
	ais	#-10
;comms.c:146: uint32_t crc = 0xFFFFFFFFUL;
	tsx
	lda	#0xff
	sta	,x
	sta	1,x
	sta	2,x
	sta	3,x
;comms.c:148: for (i = 0; i < length; i++) {
	clrh
	clrx
00103$:
	txa
	sub	16,s
	pshh
	pula
	sbc	15,s
	bcc	00101$
;comms.c:149: crc = crc32Update(crc, data[i]);
	txa
	add	12,s
	sta	10,s
	pshh
	pula
	adc	11,s
	sta	9,s
	pshx
	pshh
	lda	11,s
	psha
	pulh
	ldx	12,s
	lda	,x
	pulh
	pulx
	pshx
	pshh
	psha
	lda	7,s
	psha
	lda	7,s
	psha
	lda	7,s
	psha
	lda	7,s
	psha
	jsr	_crc32Update
	sta	11,s
	stx	10,s
	lda	*___SDCC_hc08_ret2
	sta	9,s
	lda	*___SDCC_hc08_ret3
	sta	8,s
	ais	#5
	pulh
	pulx
;comms.c:148: for (i = 0; i < length; i++) {
	aix	#1
	bra	00103$
00101$:
;comms.c:151: return ~crc;
	tsx
	lda	3,x
	coma
	sta	7,x
	lda	2,x
	coma
	sta	6,x
	lda	1,x
	coma
	sta	5,x
	lda	,x
	coma
	sta	4,x
	lda	4,x
	sta	*___SDCC_hc08_ret3
	lda	5,x
	sta	*___SDCC_hc08_ret2
	ldx	6,x
	lda	8,s
;comms.c:152: }
	ais	#12
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'sendByte'
;------------------------------------------------------------
;data                      Allocated to registers a 
;------------------------------------------------------------
;comms.c:154: void sendByte(uint8_t data) {
;	-----------------------------------------
;	 function sendByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sendByte:
;comms.c:155: sciWriteByte(data);
;comms.c:156: }
	jmp	_sciWriteByte
;------------------------------------------------------------
;Allocation info for local variables in function 'sendBytes'
;------------------------------------------------------------
;length                    Allocated to stack - sp +3
;data                      Allocated to registers x h 
;------------------------------------------------------------
;comms.c:158: void sendBytes(const uint8_t *data, uint16_t length) {
;	-----------------------------------------
;	 function sendBytes
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sendBytes:
	pshx
	tax
	pulh
;comms.c:159: sciWriteBytes(data, length);
	lda	4,s
	psha
	lda	4,s
	psha
	txa
	pshh
	pulx
	jsr	_sciWriteBytes
	ais	#2
;comms.c:160: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'sendU16'
;------------------------------------------------------------
;value                     Allocated to registers a x 
;------------------------------------------------------------
;comms.c:162: void sendU16(uint16_t value) {
;	-----------------------------------------
;	 function sendU16
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sendU16:
;comms.c:163: sciWriteByte((uint8_t)(value & 0xFF));
	psha
	pulh
	psha
	pshx
	pshh
	pula
	jsr	_sciWriteByte
	pulx
	pula
;comms.c:164: sciWriteByte((uint8_t)((value >> 8) & 0xFF));
	txa
;comms.c:165: }
	jmp	_sciWriteByte
;------------------------------------------------------------
;Allocation info for local variables in function 'sendU16BE'
;------------------------------------------------------------
;value                     Allocated to registers a x 
;------------------------------------------------------------
;comms.c:167: void sendU16BE(uint16_t value) {
;	-----------------------------------------
;	 function sendU16BE
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sendU16BE:
;comms.c:168: sciWriteByte((uint8_t)((value >> 8) & 0xFF));
	pshx
	pulh
	psha
	pshx
	pshh
	pula
	jsr	_sciWriteByte
	pulx
	pula
;comms.c:169: sciWriteByte((uint8_t)(value & 0xFF));
;comms.c:170: }
	jmp	_sciWriteByte
;------------------------------------------------------------
;Allocation info for local variables in function 'sendU32BE'
;------------------------------------------------------------
;value                     Allocated to stack - sp +3
;------------------------------------------------------------
;comms.c:172: void sendU32BE(uint32_t value) {
;	-----------------------------------------
;	 function sendU32BE
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sendU32BE:
;comms.c:173: sciWriteByte((uint8_t)((value >> 24) & 0xFF));
	tsx
	lda	2,x
	jsr	_sciWriteByte
;comms.c:174: sciWriteByte((uint8_t)((value >> 16) & 0xFF));
	tsx
	lda	3,x
	jsr	_sciWriteByte
;comms.c:175: sciWriteByte((uint8_t)((value >> 8) & 0xFF));
	tsx
	lda	4,x
	jsr	_sciWriteByte
;comms.c:176: sciWriteByte((uint8_t)(value & 0xFF));
	tsx
	lda	5,x
;comms.c:177: }
	jmp	_sciWriteByte
;------------------------------------------------------------
;Allocation info for local variables in function 'commsProcess'
;------------------------------------------------------------
;firstByte                 Allocated to registers a 
;parsedLength              Allocated to registers x h 
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;comms.c:182: void commsProcess(void) {
;	-----------------------------------------
;	 function commsProcess
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_commsProcess:
	ais	#-2
;comms.c:183: if (!sciAvailable()) {
	jsr	_sciAvailable
	tsta
	bne	00102$
;comms.c:184: return;
	jmp	00123$
00102$:
;comms.c:187: if (serialBytesReceived == 0) {
	lda	_serialBytesReceived
	bne	00108$
;comms.c:188: uint8_t firstByte = sciReadByte();
	jsr	_sciReadByte
;comms.c:189: serialBuffer[0] = firstByte;
	sta	_serialBuffer
;comms.c:190: serialBytesReceived = 1;
	ldx	#0x01
	stx	_serialBytesReceived
;comms.c:192: if (firstByte >= 'A' && firstByte <= 'z') {
	cmp	#0x41
	bcs	00104$
	cmp	#0x7a
	bhi	00104$
;comms.c:193: modernProtocol = false;
	decx
	stx	_modernProtocol
;comms.c:194: processLegacyCommand(firstByte);
	jsr	_processLegacyCommand
;comms.c:195: serialBytesReceived = 0;
	clra
	sta	_serialBytesReceived
;comms.c:196: return;
	jmp	00123$
00104$:
;comms.c:198: modernProtocol = true;
	lda	#0x01
	sta	_modernProtocol
;comms.c:199: expectedLength = 0;
	deca
	sta	_expectedLength
00108$:
;comms.c:203: if (modernProtocol) {
	lda	_modernProtocol
	bne	00193$
	jmp	00123$
00193$:
;comms.c:204: while (sciAvailable() && serialBytesReceived < SERIAL_BUFFER_SIZE) {
00118$:
	jsr	_sciAvailable
	tsta
	bne	00194$
	jmp	00123$
00194$:
	lda	_serialBytesReceived
	cmp	#0x18
	bcs	00195$
	jmp	00123$
00195$:
;comms.c:205: serialBuffer[serialBytesReceived++] = sciReadByte();
	ldx	_serialBytesReceived
	txa
	add	#0x01
	sta	_serialBytesReceived
	clrh
	pshx
	pshh
	jsr	_sciReadByte
	pulh
	pulx
	sta	(_serialBuffer),x
;comms.c:207: if (serialBytesReceived == 2 && expectedLength == 0) {
	lda	_serialBytesReceived
	cmp	#0x02
	bne	00112$
	lda	_expectedLength
	bne	00112$
;comms.c:208: uint16_t parsedLength = ((uint16_t)serialBuffer[0] << 8) | serialBuffer[1];
	lda	_serialBuffer
	clrx
	sta	1,s
	stx	2,s
	ldx	(_serialBuffer + 0x0001)
	clrh
	txa
	ora	2,s
	tax
	pshh
	pula
	ora	1,s
	psha
	pulh
;comms.c:210: if (parsedLength > (SERIAL_BUFFER_SIZE - 6)) {
	cphx	#0x0012
	bls	00110$
;comms.c:211: serialBytesReceived = 0;
	clra
	sta	_serialBytesReceived
;comms.c:212: expectedLength = 0;
	sta	_expectedLength
;comms.c:213: modernProtocol = false;
	sta	_modernProtocol
;comms.c:214: return;
	bra	00123$
00110$:
;comms.c:217: expectedLength = (uint8_t)parsedLength;
	stx	_expectedLength
00112$:
;comms.c:220: if (expectedLength > 0 && serialBytesReceived >= (2 + expectedLength + 4)) {
	lda	_expectedLength
	beq	00118$
	ldx	_expectedLength
	clrh
	aix	#6
	pshh
	pula
	sta	1,s
	stx	2,s
	lda	_serialBytesReceived
	clrx
	sub	2,s
	txa
	sbc	1,s
	bge	00200$
	jmp	00118$
00200$:
;comms.c:221: processModernCommand();
	jsr	_processModernCommand
;comms.c:222: serialBytesReceived = 0;
	clra
	sta	_serialBytesReceived
;comms.c:223: expectedLength = 0;
	sta	_expectedLength
;comms.c:224: modernProtocol = false;
	sta	_modernProtocol
;comms.c:225: return;
00123$:
;comms.c:229: }
	ais	#2
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'processLegacyCommand'
;------------------------------------------------------------
;command                   Allocated to registers a 
;------------------------------------------------------------
;comms.c:234: void processLegacyCommand(uint8_t command) {
;	-----------------------------------------
;	 function processLegacyCommand
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_processLegacyCommand:
;comms.c:235: switch (command) {
	cbeqa	#0x41,00101$
	cbeqa	#0x42,00108$
	cbeqa	#0x43,00106$
	cbeqa	#0x46,00105$
	cbeqa	#0x49,00102$
	cbeqa	#0x4e,00111$
	cbeqa	#0x51,00103$
	cbeqa	#0x53,00104$
	cbeqa	#0x62,00108$
	cbeqa	#0x63,00109$
	cbeqa	#0x6d,00110$
	rts
;comms.c:236: case 'A': sendRealtimeData(); break;
00101$:
	jmp	_sendRealtimeData
;comms.c:237: case 'I': sciPrintString("speeduino 202402"); break;
00102$:
	lda	#___str_0
	ldx	#>___str_0
	jmp	_sciPrintString
;comms.c:238: case 'Q': sendFirmwareVersion(); break;
00103$:
	jmp	_sendFirmwareVersion
;comms.c:239: case 'S': sendProductString(); break;
00104$:
	jmp	_sendProductString
;comms.c:240: case 'F': sendProtocolVersion(); break;
00105$:
	jmp	_sendProtocolVersion
;comms.c:241: case 'C': sendTestComm(); break;
00106$:
	jmp	_sendTestComm
;comms.c:243: case 'b': burnEEPROM(); break;
00108$:
	jmp	_burnEEPROM
;comms.c:244: case 'c': sendU16(2000); break;
00109$:
	lda	#0xd0
	ldx	#0x07
	jmp	_sendU16
;comms.c:245: case 'm': sendU16(getFreeRam()); break;
00110$:
	jsr	_getFreeRam
	jmp	_sendU16
;comms.c:246: case 'N': sciPrintString("\r\n"); break;
00111$:
	lda	#___str_1
	ldx	#>___str_1
;comms.c:248: }
;comms.c:249: }
	jmp	_sciPrintString
;------------------------------------------------------------
;Allocation info for local variables in function 'sendRealtimeData'
;------------------------------------------------------------
;i                         Allocated to registers a 
;------------------------------------------------------------
;comms.c:251: void sendRealtimeData(void) {
;	-----------------------------------------
;	 function sendRealtimeData
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sendRealtimeData:
;comms.c:253: sciWriteByte(0x00);
	clra
	jsr	_sciWriteByte
;comms.c:254: for (i = 0; i < LOG_ENTRIES_COUNT; i++) {
	clra
00102$:
;comms.c:255: sciWriteByte(realtimeByte(i));
	psha
	jsr	_realtimeByte
	tax
	pula
	psha
	txa
	jsr	_sciWriteByte
	pula
;comms.c:254: for (i = 0; i < LOG_ENTRIES_COUNT; i++) {
	inca
	cmp	#0x7e
	bcs	00102$
;comms.c:257: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'sendFirmwareVersion'
;------------------------------------------------------------
;comms.c:259: void sendFirmwareVersion(void) { sciPrintString("Speeduino 202402"); }
;	-----------------------------------------
;	 function sendFirmwareVersion
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sendFirmwareVersion:
	lda	#___str_2
	ldx	#>___str_2
	jmp	_sciPrintString
;------------------------------------------------------------
;Allocation info for local variables in function 'sendProductString'
;------------------------------------------------------------
;comms.c:260: void sendProductString(void)   { sciPrintString("Speeduino 202402"); }
;	-----------------------------------------
;	 function sendProductString
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sendProductString:
	lda	#___str_2
	ldx	#>___str_2
	jmp	_sciPrintString
;------------------------------------------------------------
;Allocation info for local variables in function 'sendProtocolVersion'
;------------------------------------------------------------
;comms.c:261: void sendProtocolVersion(void) { sciPrintString("002"); }
;	-----------------------------------------
;	 function sendProtocolVersion
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sendProtocolVersion:
	lda	#___str_3
	ldx	#>___str_3
	jmp	_sciPrintString
;------------------------------------------------------------
;Allocation info for local variables in function 'sendTestComm'
;------------------------------------------------------------
;comms.c:263: void sendTestComm(void) {
;	-----------------------------------------
;	 function sendTestComm
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_sendTestComm:
;comms.c:264: sendByte(0x00);
	clra
	jsr	_sendByte
;comms.c:265: sendByte(0xFF);
	lda	#0xff
;comms.c:266: }
	jmp	_sendByte
;------------------------------------------------------------
;Allocation info for local variables in function 'processModernCommand'
;------------------------------------------------------------
;payload                   Allocated to registers 
;payloadLength             Allocated to stack - sp +58
;receivedCRC               Allocated to stack - sp +33
;calculatedCRC             Allocated to stack - sp +48
;command                   Allocated to registers a 
;errorByte                 Allocated to stack - sp +32
;responseLength            Allocated to registers 
;crc                       Allocated to stack - sp +29
;i                         Allocated to registers x 
;b                         Allocated to registers a 
;testBuf                   Allocated to stack - sp +31
;tempBuf                   Allocated to stack - sp +27
;tempBuf                   Allocated to stack - sp +1
;len                       Allocated to registers x 
;iface                     Allocated to registers 
;ilen                      Allocated to stack - sp +57
;tempBuf                   Allocated to stack - sp +1
;len                       Allocated to registers x 
;ver                       Allocated to registers 
;vlen                      Allocated to stack - sp +56
;tempBuf                   Allocated to stack - sp +1
;len                       Allocated to registers x 
;prod                      Allocated to registers 
;plen                      Allocated to stack - sp +55
;tempBuf                   Allocated to stack - sp +29
;page                      Allocated to stack - sp +54
;offset                    Allocated to stack - sp +52
;length                    Allocated to registers a x 
;err                       Allocated to stack - sp +32
;page                      Allocated to stack - sp +51
;offset                    Allocated to stack - sp +49
;length                    Allocated to registers x h 
;data                      Allocated to registers 
;result                    Allocated to stack - sp +32
;page                      Allocated to registers a 
;err                       Allocated to stack - sp +32
;subcmd                    Allocated to stack - sp +48
;offset                    Allocated to stack - sp +46
;length                    Allocated to registers a x 
;err                       Allocated to stack - sp +32
;statusByte                Allocated to stack - sp +32
;err                       Allocated to stack - sp +32
;sloc0                     Allocated to stack - sp +45
;sloc1                     Allocated to stack - sp +37
;sloc2                     Allocated to stack - sp +41
;------------------------------------------------------------
;comms.c:271: void processModernCommand(void) {
;	-----------------------------------------
;	 function processModernCommand
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 59 bytes.
_processModernCommand:
	ais	#-59
;comms.c:272: uint8_t *payload = &serialBuffer[2];
;comms.c:273: uint16_t payloadLength = expectedLength;
	tsx
	lda	_expectedLength
	sta	58,x
	clra
	sta	57,x
;comms.c:277: receivedCRC = ((uint32_t)serialBuffer[2 + payloadLength] << 24) |
	lda	58,x
	sta	44,x
	lda	44,x
	add	#0x02
	tax
	rola	
	clra	
	sbc	#0x00
	psha
	pulh
	lda	(_serialBuffer),x
	tsx
	sta	39,x
	clrx
	stx	39,s
	stx	38,s
	stx	37,s
	tsx
	lda	39,x
	sta	36,x
	clra
	sta	39,x
	sta	38,x
	sta	37,x
;comms.c:278: ((uint32_t)serialBuffer[2 + payloadLength + 1] << 16) |
	lda	44,x
	add	#0x03
	tax
	rola	
	clra	
	sbc	#0x00
	psha
	pulh
	lda	(_serialBuffer),x
	tsx
	sta	43,x
	clrx
	stx	43,s
	stx	42,s
	stx	41,s
	tsx
	lda	42,x
	sta	40,x
	lda	43,x
	sta	41,x
	clra
	sta	43,x
	sta	42,x
	lda	39,x
	ora	43,x
	sta	43,x
	lda	38,x
	ora	42,x
	sta	42,x
	lda	37,x
	ora	41,x
	sta	41,x
	lda	36,x
	ora	40,x
	sta	40,x
;comms.c:279: ((uint32_t)serialBuffer[2 + payloadLength + 2] << 8) |
	lda	44,x
	add	#0x04
	tax
	rola	
	clra	
	sbc	#0x00
	psha
	pulh
	lda	(_serialBuffer),x
	tsx
	sta	39,x
	clrx
	stx	39,s
	stx	38,s
	stx	37,s
	tsx
	lda	37,x
	sta	36,x
	lda	38,x
	sta	37,x
	lda	39,x
	sta	38,x
	clra
	sta	39,x
	lda	43,x
	ora	39,x
	sta	43,x
	lda	42,x
	ora	38,x
	sta	42,x
	lda	41,x
	ora	37,x
	sta	41,x
	lda	40,x
	ora	36,x
	sta	40,x
;comms.c:280: ((uint32_t)serialBuffer[2 + payloadLength + 3]);
	lda	44,x
	add	#0x05
	tax
	rola	
	clra	
	sbc	#0x00
	psha
	pulh
	lda	(_serialBuffer),x
	tsx
	sta	39,x
	clrx
	stx	39,s
	stx	38,s
	stx	37,s
	tsx
	lda	43,x
	ora	39,x
	sta	35,x
	lda	42,x
	ora	38,x
	sta	34,x
	lda	41,x
	ora	37,x
	sta	33,x
	lda	40,x
	ora	36,x
	sta	32,x
;comms.c:282: calculatedCRC = calculateCRC32(payload, payloadLength);
	lda	58,x
	psha
	lda	57,x
	psha
	lda	#(_serialBuffer + 0x0002)
	ldx	#>(_serialBuffer + 0x0002)
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
;comms.c:284: if (receivedCRC != calculatedCRC) {
	tsx
	lda	35,x
	cmp	43,x
	bne	00228$
	lda	34,x
	cmp	42,x
	bne	00228$
	lda	33,x
	cmp	41,x
	bne	00228$
	lda	32,x
	cmp	40,x
	beq	00102$
00228$:
;comms.c:285: uint8_t errorByte = SERIAL_RC_CRC_ERR;
	lda	#0x82
	sta	31,x
;comms.c:286: sendU16BE(1);
	lda	#0x01
	clrx
	jsr	_sendU16BE
;comms.c:287: sendByte(errorByte);
	lda	32,s
	jsr	_sendByte
;comms.c:288: sendU32BE(calculateCRC32(&errorByte, 1));
	tsx
	aix	#31
	lda	#0x01
	psha
	deca
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:289: return;
	jmp	00130$
00102$:
;comms.c:292: command = payload[0];
	lda	(_serialBuffer + 0x0002)
;comms.c:294: switch (command) {
	cbeqa	#0x41,00103$
	cmp	#0x42
	bne	00230$
	jmp	00125$
00230$:
	cmp	#0x43
	bne	00231$
	jmp	00105$
00231$:
	cmp	#0x46
	bne	00232$
	jmp	00110$
00232$:
	cmp	#0x49
	bne	00233$
	jmp	00107$
00233$:
	cmp	#0x4d
	bne	00234$
	jmp	00115$
00234$:
	cmp	#0x51
	bne	00235$
	jmp	00108$
00235$:
	cmp	#0x53
	bne	00236$
	jmp	00109$
00236$:
	cmp	#0x62
	bne	00237$
	jmp	00125$
00237$:
	cmp	#0x64
	bne	00238$
	jmp	00116$
00238$:
	cmp	#0x66
	bne	00239$
	jmp	00106$
00239$:
	cmp	#0x70
	bne	00240$
	jmp	00111$
00240$:
	cmp	#0x72
	bne	00241$
	jmp	00120$
00241$:
	jmp	00126$
;comms.c:295: case 'A': {
00103$:
;comms.c:300: sendU16BE(responseLength);
	lda	#0x80
	clrx
	jsr	_sendU16BE
;comms.c:301: sendByte(SERIAL_RC_OK);
	clra
	jsr	_sendByte
;comms.c:302: crc = crc32Update(crc, SERIAL_RC_OK);
	clra
	psha
	deca
	psha
	psha
	psha
	psha
	jsr	_crc32Update
	sta	49,s
	stx	48,s
	lda	*___SDCC_hc08_ret2
	sta	47,s
	lda	*___SDCC_hc08_ret3
	sta	46,s
	ais	#5
;comms.c:303: sendByte(0x00);
	clra
	jsr	_sendByte
;comms.c:304: crc = crc32Update(crc, 0x00);
	clra
	psha
	tsx
	lda	44,x
	psha
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	jsr	_crc32Update
	sta	37,s
	stx	36,s
	lda	*___SDCC_hc08_ret2
	sta	35,s
	lda	*___SDCC_hc08_ret3
	sta	34,s
	ais	#5
;comms.c:305: for (i = 0; i < LOG_ENTRIES_COUNT; i++) {
	clrx
00128$:
;comms.c:306: uint8_t b = realtimeByte(i);
	pshx
	txa
	jsr	_realtimeByte
	pulx
;comms.c:307: sendByte(b);
	psha
	pshx
	jsr	_sendByte
	pulx
	pula
;comms.c:308: crc = crc32Update(crc, b);
	pshx
	psha
	lda	34,s
	psha
	lda	34,s
	psha
	lda	34,s
	psha
	lda	34,s
	psha
	jsr	_crc32Update
	sta	50,s
	stx	49,s
	lda	*___SDCC_hc08_ret2
	sta	48,s
	lda	*___SDCC_hc08_ret3
	sta	47,s
	ais	#5
	pulx
	lda	41,s
	sta	29,s
	lda	42,s
	sta	30,s
	lda	43,s
	sta	31,s
	lda	44,s
	sta	32,s
;comms.c:305: for (i = 0; i < LOG_ENTRIES_COUNT; i++) {
	aix	#1
	cpx	#0x7e
	bcs	00128$
;comms.c:310: sendU32BE(~crc);
	tsx
	lda	43,x
	coma
	sta	43,x
	lda	42,x
	coma
	sta	42,x
	lda	41,x
	coma
	sta	41,x
	lda	40,x
	coma
	sta	40,x
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:311: break;
	jmp	00130$
;comms.c:314: case 'C': {
00105$:
;comms.c:316: testBuf[0] = SERIAL_RC_OK;
	tsx
	aix	#30
	pshh
	pula
	sta	41,s
	stx	42,s
	lda	41,s
	psha
	pulh
	ldx	42,s
	clra
	sta	,x
;comms.c:317: testBuf[1] = 0xFF;
	tsx
	lda	40,x
	sta	36,x
	lda	41,x
	sta	37,x
	lda	36,x
	psha
	pulh
	ldx	38,s
	lda	#0xff
	sta	1,x
;comms.c:318: sendU16BE(2);
	lda	#0x02
	clrx
	jsr	_sendU16BE
;comms.c:319: sendBytes(testBuf, 2);
	tsx
	lda	40,x
	sta	36,x
	lda	41,x
	sta	37,x
	lda	36,x
	psha
	pulh
	ldx	38,s
	lda	#0x02
	psha
	clra
	psha
	txa
	pshh
	pulx
	jsr	_sendBytes
	ais	#2
;comms.c:320: sendU32BE(calculateCRC32(testBuf, 2));
	tsx
	lda	40,x
	psha
	pulh
	ldx	42,s
	lda	#0x02
	psha
	clra
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:321: break;
	jmp	00130$
;comms.c:324: case 'f': {
00106$:
;comms.c:326: tempBuf[0] = SERIAL_RC_OK;
	tsx
	aix	#26
	pshh
	pula
	sta	41,s
	stx	42,s
	lda	41,s
	psha
	pulh
	ldx	42,s
	clra
	sta	,x
;comms.c:327: tempBuf[1] = 2;
	tsx
	lda	40,x
	sta	36,x
	lda	41,x
	sta	37,x
	lda	36,x
	psha
	pulh
	ldx	38,s
	lda	#0x02
	sta	1,x
;comms.c:328: tempBuf[2] = (BLOCKING_FACTOR >> 8) & 0xFF;
	tsx
	lda	40,x
	sta	36,x
	lda	41,x
	sta	37,x
	lda	36,x
	psha
	pulh
	ldx	38,s
	clra
	sta	2,x
;comms.c:329: tempBuf[3] = BLOCKING_FACTOR & 0xFF;
	tsx
	lda	40,x
	sta	36,x
	lda	41,x
	sta	37,x
	lda	36,x
	psha
	pulh
	ldx	38,s
	lda	#0x79
	sta	3,x
;comms.c:330: tempBuf[4] = (TABLE_BLOCKING_FACTOR >> 8) & 0xFF;
	tsx
	lda	40,x
	sta	36,x
	lda	41,x
	sta	37,x
	lda	36,x
	psha
	pulh
	ldx	38,s
	clra
	sta	4,x
;comms.c:331: tempBuf[5] = TABLE_BLOCKING_FACTOR & 0xFF;
	tsx
	lda	40,x
	sta	36,x
	lda	41,x
	sta	37,x
	lda	36,x
	psha
	pulh
	ldx	38,s
	lda	#0x40
	sta	5,x
;comms.c:332: sendU16BE(6);
	lda	#0x06
	clrx
	jsr	_sendU16BE
;comms.c:333: sendBytes(tempBuf, 6);
	tsx
	lda	40,x
	sta	36,x
	lda	41,x
	sta	37,x
	lda	36,x
	psha
	pulh
	ldx	38,s
	lda	#0x06
	psha
	clra
	psha
	txa
	pshh
	pulx
	jsr	_sendBytes
	ais	#2
;comms.c:334: sendU32BE(calculateCRC32(tempBuf, 6));
	tsx
	lda	40,x
	psha
	pulh
	ldx	42,s
	lda	#0x06
	psha
	clra
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:335: break;
	jmp	00130$
;comms.c:338: case 'I': {
00107$:
;comms.c:341: const char *iface = "speeduino 202402";
;comms.c:342: uint8_t ilen = (uint8_t)strlen(iface);
	lda	#___str_0
	ldx	#>___str_0
	jsr	_strlen
	sta	57,s
;comms.c:343: tempBuf[len++] = SERIAL_RC_OK;
	tsx
	pshh
	pula
	sta	41,s
	stx	42,s
	lda	41,s
	psha
	pulh
	ldx	42,s
	clra
	sta	,x
;comms.c:344: memcpy(&tempBuf[len], iface, ilen);
	tsx
	lda	56,x
	sta	37,x
	clra
	sta	36,x
	lda	40,x
	psha
	pulh
	ldx	42,s
	aix	#1
	lda	38,s
	psha
	lda	38,s
	psha
	lda	#___str_0
	psha
	lda	#>___str_0
	psha
	txa
	pshh
	pulx
	jsr	___memcpy
	ais	#4
;comms.c:345: len = (uint8_t)(len + ilen);
	ldx	57,s
	aix	#1
;comms.c:346: sendU16BE(len);
	clrh
	pshx
	pshh
	txa
	pshh
	pulx
	jsr	_sendU16BE
	pulh
	pulx
;comms.c:347: sendBytes(tempBuf, len);
	lda	41,s
	sta	37,s
	lda	42,s
	sta	38,s
	lda	38,s
	sta	38,s
	lda	37,s
	sta	37,s
	pshx
	pshh
	pshx
	pshh
	lda	42,s
	ldx	41,s
	jsr	_sendBytes
	ais	#2
	pulh
	pulx
;comms.c:348: sendU32BE(calculateCRC32(tempBuf, len));
	lda	42,s
	sta	42,s
	lda	41,s
	sta	41,s
	pshx
	pshh
	tsx
	lda	43,x
	ldx	42,x
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:349: break;
	jmp	00130$
;comms.c:352: case 'Q': {
00108$:
;comms.c:355: const char *ver = "speeduino 202207";
;comms.c:356: uint8_t vlen = (uint8_t)strlen(ver);
	lda	#___str_4
	ldx	#>___str_4
	jsr	_strlen
	sta	56,s
;comms.c:357: tempBuf[len++] = SERIAL_RC_OK;
	tsx
	pshh
	pula
	sta	41,s
	stx	42,s
	lda	41,s
	psha
	pulh
	ldx	42,s
	clra
	sta	,x
;comms.c:358: memcpy(&tempBuf[len], ver, vlen);
	tsx
	lda	55,x
	sta	37,x
	clra
	sta	36,x
	lda	40,x
	psha
	pulh
	ldx	42,s
	aix	#1
	lda	38,s
	psha
	lda	38,s
	psha
	lda	#___str_4
	psha
	lda	#>___str_4
	psha
	txa
	pshh
	pulx
	jsr	___memcpy
	ais	#4
;comms.c:359: len = (uint8_t)(len + vlen);
	ldx	56,s
	aix	#1
;comms.c:360: sendU16BE(len);
	clrh
	pshx
	pshh
	txa
	pshh
	pulx
	jsr	_sendU16BE
	pulh
	pulx
;comms.c:361: sendBytes(tempBuf, len);
	lda	41,s
	sta	37,s
	lda	42,s
	sta	38,s
	lda	38,s
	sta	38,s
	lda	37,s
	sta	37,s
	pshx
	pshh
	pshx
	pshh
	lda	42,s
	ldx	41,s
	jsr	_sendBytes
	ais	#2
	pulh
	pulx
;comms.c:362: sendU32BE(calculateCRC32(tempBuf, len));
	lda	42,s
	sta	42,s
	lda	41,s
	sta	41,s
	pshx
	pshh
	tsx
	lda	43,x
	ldx	42,x
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:363: break;
	jmp	00130$
;comms.c:366: case 'S': {
00109$:
;comms.c:369: const char *prod = "Speeduino 2024.02.4";
;comms.c:370: uint8_t plen = (uint8_t)strlen(prod);
	lda	#___str_5
	ldx	#>___str_5
	jsr	_strlen
	sta	55,s
;comms.c:371: tempBuf[len++] = SERIAL_RC_OK;
	tsx
	pshh
	pula
	sta	41,s
	stx	42,s
	lda	41,s
	psha
	pulh
	ldx	42,s
	clra
	sta	,x
;comms.c:372: memcpy(&tempBuf[len], prod, plen);
	tsx
	lda	54,x
	sta	37,x
	clra
	sta	36,x
	lda	40,x
	psha
	pulh
	ldx	42,s
	aix	#1
	lda	38,s
	psha
	lda	38,s
	psha
	lda	#___str_5
	psha
	lda	#>___str_5
	psha
	txa
	pshh
	pulx
	jsr	___memcpy
	ais	#4
;comms.c:373: len = (uint8_t)(len + plen);
	ldx	55,s
	aix	#1
;comms.c:374: sendU16BE(len);
	clrh
	pshx
	pshh
	txa
	pshh
	pulx
	jsr	_sendU16BE
	pulh
	pulx
;comms.c:375: sendBytes(tempBuf, len);
	lda	41,s
	sta	37,s
	lda	42,s
	sta	38,s
	lda	38,s
	sta	38,s
	lda	37,s
	sta	37,s
	pshx
	pshh
	pshx
	pshh
	lda	42,s
	ldx	41,s
	jsr	_sendBytes
	ais	#2
	pulh
	pulx
;comms.c:376: sendU32BE(calculateCRC32(tempBuf, len));
	lda	42,s
	sta	42,s
	lda	41,s
	sta	41,s
	pshx
	pshh
	tsx
	lda	43,x
	ldx	42,x
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:377: break;
	jmp	00130$
;comms.c:380: case 'F': {
00110$:
;comms.c:382: tempBuf[0] = SERIAL_RC_OK;
	tsx
	aix	#28
	pshh
	pula
	sta	41,s
	stx	42,s
	lda	41,s
	psha
	pulh
	ldx	42,s
	clra
	sta	,x
;comms.c:383: tempBuf[1] = '0';
	tsx
	lda	40,x
	sta	36,x
	lda	41,x
	sta	37,x
	lda	36,x
	psha
	pulh
	ldx	38,s
	lda	#0x30
	sta	1,x
;comms.c:384: tempBuf[2] = '0';
	tsx
	lda	40,x
	sta	36,x
	lda	41,x
	sta	37,x
	lda	36,x
	psha
	pulh
	ldx	38,s
	lda	#0x30
	sta	2,x
;comms.c:385: tempBuf[3] = '2';
	tsx
	lda	40,x
	sta	36,x
	lda	41,x
	sta	37,x
	lda	36,x
	psha
	pulh
	ldx	38,s
	lda	#0x32
	sta	3,x
;comms.c:386: sendU16BE(4);
	lda	#0x04
	clrx
	jsr	_sendU16BE
;comms.c:387: sendBytes(tempBuf, 4);
	tsx
	lda	40,x
	sta	36,x
	lda	41,x
	sta	37,x
	lda	36,x
	psha
	pulh
	ldx	38,s
	lda	#0x04
	psha
	clra
	psha
	txa
	pshh
	pulx
	jsr	_sendBytes
	ais	#2
;comms.c:388: sendU32BE(calculateCRC32(tempBuf, 4));
	tsx
	lda	40,x
	psha
	pulh
	ldx	42,s
	lda	#0x04
	psha
	clra
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:389: break;
	jmp	00130$
;comms.c:392: case 'p': {
00111$:
;comms.c:393: if (payloadLength >= 7) {
	lda	59,s
	ldx	58,s
	sub	#0x07
	txa
	sbc	#0x00
	bcs	00113$
;comms.c:394: uint8_t page = payload[2];
	lda	(_serialBuffer + 0x0004)
	sta	54,s
;comms.c:395: uint16_t offset = payload[3] | ((uint16_t)payload[4] << 8);
	lda	(_serialBuffer + 0x0005)
	ldx	(_serialBuffer + 0x0006)
	clrh
	psha
	txa
	sta	42,s
	psha
	clra
	sta	44,s
	pula
	pula
	clrx
	ora	42,s
	sta	53,s
	txa
	ora	41,s
	sta	52,s
;comms.c:396: uint16_t length = payload[5] | ((uint16_t)payload[6] << 8);
	lda	(_serialBuffer + 0x0007)
	ldx	(_serialBuffer + 0x0008)
	psha
	txa
	sta	42,s
	psha
	clra
	sta	44,s
	pula
	pula
	clrx
	ora	42,s
	psha
	txa
	ora	42,s
	tax
	pula
;comms.c:397: sendPageValues(page, offset, length);
	psha
	pshx
	tsx
	lda	54,x
	psha
	lda	53,x
	psha
	lda	55,x
	jsr	_sendPageValues
	ais	#4
	jmp	00130$
00113$:
;comms.c:399: uint8_t err = SERIAL_RC_UKWN_ERR;
	lda	#0x83
	sta	32,s
;comms.c:400: sendU16BE(1);
	lda	#0x01
	clrx
	jsr	_sendU16BE
;comms.c:401: sendByte(err);
	lda	32,s
	jsr	_sendByte
;comms.c:402: sendU32BE(calculateCRC32(&err, 1));
	tsx
	aix	#31
	lda	#0x01
	psha
	deca
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:404: break;
	jmp	00130$
;comms.c:407: case 'M': {
00115$:
;comms.c:408: uint8_t page = payload[2];
	lda	(_serialBuffer + 0x0004)
	sta	51,s
;comms.c:409: uint16_t offset = payload[3] | ((uint16_t)payload[4] << 8);
	lda	(_serialBuffer + 0x0005)
	ldx	(_serialBuffer + 0x0006)
	clrh
	psha
	txa
	sta	42,s
	psha
	clra
	sta	44,s
	pula
	pula
	clrx
	ora	42,s
	sta	50,s
	txa
	ora	41,s
	sta	49,s
;comms.c:410: uint16_t length = payload[5] | ((uint16_t)payload[6] << 8);
	lda	(_serialBuffer + 0x0007)
	ldx	(_serialBuffer + 0x0008)
	psha
	txa
	sta	42,s
	psha
	clra
	sta	44,s
	pula
	pula
	tax
	txa
	ora	42,s
	tax
	pshh
	pula
	ora	41,s
	psha
	pulh
;comms.c:411: uint8_t *data = &payload[7];
;comms.c:412: uint8_t result = writePageValues(page, offset, length, data);
	lda	#(_serialBuffer + 0x0009)
	psha
	lda	#>(_serialBuffer + 0x0009)
	psha
	pshx
	pshh
	tsx
	lda	53,x
	psha
	lda	52,x
	psha
	lda	54,x
	jsr	_writePageValues
	sta	38,s
	ais	#6
;comms.c:414: sendU16BE(1);
	lda	#0x01
	clrx
	jsr	_sendU16BE
;comms.c:415: sendByte(result);
	lda	32,s
	jsr	_sendByte
;comms.c:416: sendU32BE(calculateCRC32(&result, 1));
	tsx
	aix	#31
	lda	#0x01
	psha
	deca
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:417: break;
	jmp	00130$
;comms.c:420: case 'd': {
00116$:
;comms.c:421: if (payloadLength >= 3) {
	lda	59,s
	ldx	58,s
	sub	#0x03
	txa
	sbc	#0x00
	bcs	00118$
;comms.c:422: uint8_t page = payload[2];
	lda	(_serialBuffer + 0x0004)
;comms.c:423: sendPageCRC32(page);
	jsr	_sendPageCRC32
	jmp	00130$
00118$:
;comms.c:425: uint8_t err = SERIAL_RC_UKWN_ERR;
	lda	#0x83
	sta	32,s
;comms.c:426: sendU16BE(1);
	lda	#0x01
	clrx
	jsr	_sendU16BE
;comms.c:427: sendByte(err);
	lda	32,s
	jsr	_sendByte
;comms.c:428: sendU32BE(calculateCRC32(&err, 1));
	tsx
	aix	#31
	lda	#0x01
	psha
	deca
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:430: break;
	jmp	00130$
;comms.c:433: case 'r': {
00120$:
;comms.c:434: if (payloadLength >= 7) {
	lda	59,s
	ldx	58,s
	sub	#0x07
	txa
	sbc	#0x00
	bcs	00122$
;comms.c:435: uint8_t subcmd = payload[2];
	lda	(_serialBuffer + 0x0004)
	sta	48,s
;comms.c:436: uint16_t offset = payload[3] | ((uint16_t)payload[4] << 8);
	lda	(_serialBuffer + 0x0005)
	ldx	(_serialBuffer + 0x0006)
	clrh
	psha
	txa
	sta	42,s
	psha
	clra
	sta	44,s
	pula
	pula
	clrx
	ora	42,s
	sta	47,s
	txa
	ora	41,s
	sta	46,s
;comms.c:437: uint16_t length = payload[5] | ((uint16_t)payload[6] << 8);
	lda	(_serialBuffer + 0x0007)
	ldx	(_serialBuffer + 0x0008)
	psha
	txa
	sta	42,s
	psha
	clra
	sta	44,s
	pula
	pula
	clrx
	ora	42,s
	psha
	txa
	ora	42,s
	tax
	pula
;comms.c:438: sendOutputChannels(subcmd, offset, length);
	psha
	pshx
	tsx
	lda	48,x
	psha
	lda	47,x
	psha
	lda	49,x
	jsr	_sendOutputChannels
	ais	#4
	jmp	00130$
00122$:
;comms.c:440: uint8_t err = SERIAL_RC_UKWN_ERR;
	lda	#0x83
	sta	32,s
;comms.c:441: sendU16BE(1);
	lda	#0x01
	clrx
	jsr	_sendU16BE
;comms.c:442: sendByte(err);
	lda	32,s
	jsr	_sendByte
;comms.c:443: sendU32BE(calculateCRC32(&err, 1));
	tsx
	aix	#31
	lda	#0x01
	psha
	deca
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:445: break;
	jmp	00130$
;comms.c:449: case 'B': {
00125$:
;comms.c:450: uint8_t statusByte = SERIAL_RC_BURN_OK;
	lda	#0x04
	sta	32,s
;comms.c:451: burnEEPROM();
	jsr	_burnEEPROM
;comms.c:452: sendU16BE(1);
	lda	#0x01
	clrx
	jsr	_sendU16BE
;comms.c:453: sendByte(statusByte);
	lda	32,s
	jsr	_sendByte
;comms.c:454: sendU32BE(calculateCRC32(&statusByte, 1));
	tsx
	aix	#31
	lda	#0x01
	psha
	deca
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:455: break;
	bra	00130$
;comms.c:458: default: {
00126$:
;comms.c:459: uint8_t err = SERIAL_RC_UKWN_ERR;
	lda	#0x83
	sta	32,s
;comms.c:460: sendU16BE(1);
	lda	#0x01
	clrx
	jsr	_sendU16BE
;comms.c:461: sendByte(err);
	lda	32,s
	jsr	_sendByte
;comms.c:462: sendU32BE(calculateCRC32(&err, 1));
	tsx
	aix	#31
	lda	#0x01
	psha
	deca
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	46,s
	stx	45,s
	lda	*___SDCC_hc08_ret2
	sta	44,s
	lda	*___SDCC_hc08_ret3
	sta	43,s
	ais	#2
	tsx
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	lda	40,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:465: }
00130$:
;comms.c:466: }
	ais	#59
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'getPageSize'
;------------------------------------------------------------
;page                      Allocated to registers a 
;------------------------------------------------------------
;comms.c:471: uint16_t getPageSize(uint8_t page) {
;	-----------------------------------------
;	 function getPageSize
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_getPageSize:
;comms.c:472: if (page >= PAGE_COUNT) return 0;
	cmp	#0x10
	bcs	00102$
	clra
	tax
	rts
00102$:
;comms.c:473: return pageSize[page];
	ldx	#0x02
	mul
	pshx
	pulh
	tax
	lda	(_pageSize+1),x
	ldx	(_pageSize),x
;comms.c:474: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'readStructPageByte'
;------------------------------------------------------------
;size                      Allocated to stack - sp +5
;offset                    Allocated to stack - sp +7
;value                     Allocated to stack - sp +9
;base                      Allocated to registers x h 
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;comms.c:476: static bool readStructPageByte(const uint8_t *base, uint16_t size, uint16_t offset, uint8_t *value) {
;	-----------------------------------------
;	 function readStructPageByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_readStructPageByte:
	ais	#-2
	pshx
	tax
	pulh
;comms.c:477: if (offset >= size) return false;
	lda	8,s
	sub	6,s
	lda	7,s
	sbc	5,s
	bcs	00102$
	clra
	bra	00103$
00102$:
;comms.c:478: *value = base[offset];
	lda	9,s
	sta	1,s
	lda	10,s
	sta	2,s
	txa
	add	8,s
	tax
	pshh
	pula
	adc	7,s
	psha
	pulh
	lda	,x
	pulh
	pulx
	pshx
	pshh
	sta	,x
;comms.c:479: return true;
	lda	#0x01
00103$:
;comms.c:480: }
	ais	#2
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'writeStructPageByte'
;------------------------------------------------------------
;size                      Allocated to stack - sp +3
;offset                    Allocated to stack - sp +5
;value                     Allocated to stack - sp +7
;base                      Allocated to registers a x 
;------------------------------------------------------------
;comms.c:482: static PageWriteStatus writeStructPageByte(uint8_t *base, uint16_t size, uint16_t offset, uint8_t value) {
;	-----------------------------------------
;	 function writeStructPageByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_writeStructPageByte:
;comms.c:483: if (offset >= size) return PAGE_WRITE_FAIL;
	psha
	lda	7,s
	sub	5,s
	lda	6,s
	sbc	4,s
	pula
	bcs	00102$
	clra
	rts
00102$:
;comms.c:484: base[offset] = value;
	add	6,s
	psha
	txa
	adc	6,s
	tax
	pula
	pshx
	pulh
	tax
	lda	7,s
	sta	,x
;comms.c:485: return PAGE_WRITE_OK;
	lda	#0x01
;comms.c:486: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'readStubPageByte'
;------------------------------------------------------------
;offset                    Allocated to stack - sp +3
;value                     Allocated to stack - sp +5
;page                      Allocated to registers a 
;size                      Allocated to registers a x 
;------------------------------------------------------------
;comms.c:488: static bool readStubPageByte(uint8_t page, uint16_t offset, uint8_t *value) {
;	-----------------------------------------
;	 function readStubPageByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_readStubPageByte:
;comms.c:489: uint16_t size = getPageSize(page);
	jsr	_getPageSize
;comms.c:490: if (offset >= size) return false;
	psha
	lda	5,s
	sub	1, s
	pula
	lda	3,s
	pshx
	sbc	1,s
	ais	#1
	bcs	00102$
	clra
	rts
00102$:
;comms.c:491: *value = 0;
	lda	5,s
	ldx	6,s
	psha
	pulh
	clra
	sta	,x
;comms.c:492: return true;
	inca
;comms.c:493: }
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'readVeTablePageByte'
;------------------------------------------------------------
;value                     Allocated to stack - sp +7
;offset                    Allocated to registers x h 
;idx                       Allocated to registers a 
;idx                       Allocated to registers a 
;sloc0                     Allocated to stack - sp +3
;sloc1                     Allocated to stack - sp +1
;------------------------------------------------------------
;comms.c:495: static bool readVeTablePageByte(uint16_t offset, uint8_t *value) {
;	-----------------------------------------
;	 function readVeTablePageByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 4 bytes.
_readVeTablePageByte:
	ais	#-4
	pshx
	tax
	pulh
;comms.c:496: if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return false;
	cphx	#0x00a8
	bcs	00102$
	clra
	bra	00107$
00102$:
;comms.c:499: *value = eepromReadByte(veTable.eepromValuesBase + offset);
	lda	7,s
	sta	3,s
	lda	8,s
	sta	4,s
;comms.c:498: if (offset < SPEEDUINO_TABLE_CELLS) {
	cphx	#0x0090
	bcc	00104$
;comms.c:499: *value = eepromReadByte(veTable.eepromValuesBase + offset);
	lda	(_veTable + 0x0024)
	sta	1,s
	lda	((_veTable + 0x0024) + 1)
	sta	2,s
	txa
	add	2,s
	psha
	pshh
	pula
	adc	2,s
	tax
	pula
	jsr	_eepromReadByte
	ldx	3,s
	pshx
	pulh
	ldx	4,s
	sta	,x
;comms.c:500: return true;
	lda	#0x01
	bra	00107$
00104$:
;comms.c:503: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
	txa
;comms.c:502: if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
	cphx	#0x009c
	bcc	00106$
;comms.c:503: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
	sub	#0x90
;comms.c:504: *value = encodeRpmBin(veTable.axisX[idx]);
	lsla	
	tax
	clrh
	lda	(_veTable+1),x
	ldx	(_veTable),x
	jsr	_encodeRpmBin
	ldx	3,s
	pshx
	pulh
	ldx	4,s
	sta	,x
;comms.c:505: return true;
	lda	#0x01
	bra	00107$
00106$:
;comms.c:508: uint8_t idx = (uint8_t)(offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN));
	sub	#0x9c
;comms.c:509: *value = veTable.axisY[idx];
	tax
	clrh
	lda	((_veTable + 0x0018)),x
	ldx	3,s
	pshx
	pulh
	ldx	4,s
	sta	,x
;comms.c:510: return true;
	lda	#0x01
00107$:
;comms.c:512: }
	ais	#4
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'writeVeTablePageByte'
;------------------------------------------------------------
;value                     Allocated to stack - sp +5
;offset                    Allocated to registers x h 
;idx                       Allocated to registers a 
;idx                       Allocated to registers a 
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;comms.c:514: static PageWriteStatus writeVeTablePageByte(uint16_t offset, uint8_t value) {
;	-----------------------------------------
;	 function writeVeTablePageByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_writeVeTablePageByte:
	ais	#-2
	pshx
	tax
	pulh
;comms.c:515: if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return PAGE_WRITE_FAIL;
	cphx	#0x00a8
	bcs	00102$
	clra
	bra	00107$
00102$:
;comms.c:517: if (offset < SPEEDUINO_TABLE_CELLS) {
	cphx	#0x0090
	bcc	00104$
;comms.c:518: eepromWriteByte(veTable.eepromValuesBase + offset, value);
	lda	(_veTable + 0x0024)
	sta	1,s
	lda	((_veTable + 0x0024) + 1)
	sta	2,s
	txa
	add	2,s
	tax
	pshh
	pula
	adc	1,s
	psha
	pulh
	lda	5,s
	psha
	txa
	pshh
	pulx
	jsr	_eepromWriteByte
	ais	#1
;comms.c:519: return PAGE_WRITE_TABLE_CHANGED;
	lda	#0x02
	bra	00107$
00104$:
;comms.c:522: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
	txa
;comms.c:521: if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
	cphx	#0x009c
	bcc	00106$
;comms.c:522: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
	sub	#0x90
;comms.c:523: veTable.axisX[idx] = decodeRpmBin(value);
	lsla	
	tax
	clrh
	pshx
	pshh
	lda	7,s
	jsr	_decodeRpmBin
	sta	4,s
	stx	3,s
	pulh
	pulx
	lda	1,s
	sta	(_veTable),x
	lda	2,s
	sta	(_veTable+1),x
;comms.c:524: return PAGE_WRITE_TABLE_CHANGED;
	lda	#0x02
	bra	00107$
00106$:
;comms.c:527: uint8_t idx = (uint8_t)(offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN));
	sub	#0x9c
;comms.c:528: veTable.axisY[idx] = value;
	tax
	clrh
	lda	5,s
	sta	((_veTable + 0x0018)),x
;comms.c:529: return PAGE_WRITE_TABLE_CHANGED;
	lda	#0x02
00107$:
;comms.c:531: }
	ais	#2
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'readIgnTablePageByte'
;------------------------------------------------------------
;value                     Allocated to stack - sp +7
;offset                    Allocated to registers x h 
;cellValue                 Allocated to registers a 
;idx                       Allocated to registers a 
;idx                       Allocated to registers a 
;sloc0                     Allocated to stack - sp +3
;sloc1                     Allocated to stack - sp +1
;------------------------------------------------------------
;comms.c:533: static bool readIgnTablePageByte(uint16_t offset, uint8_t *value) {
;	-----------------------------------------
;	 function readIgnTablePageByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 4 bytes.
_readIgnTablePageByte:
	ais	#-4
	pshx
	tax
	pulh
;comms.c:534: if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return false;
	cphx	#0x00a8
	bcs	00102$
	clra
	bra	00107$
00102$:
;comms.c:538: *value = encodeIgnitionValue(cellValue);
	lda	7,s
	sta	3,s
	lda	8,s
	sta	4,s
;comms.c:536: if (offset < SPEEDUINO_TABLE_CELLS) {
	cphx	#0x0090
	bcc	00104$
;comms.c:537: int8_t cellValue = eepromReadI8(ignTable.eepromValuesBase + offset);
	lda	(_ignTable + 0x0024)
	sta	1,s
	lda	((_ignTable + 0x0024) + 1)
	sta	2,s
	txa
	add	2,s
	psha
	pshh
	pula
	adc	2,s
	tax
	pula
	jsr	_eepromReadI8
;comms.c:538: *value = encodeIgnitionValue(cellValue);
	jsr	_encodeIgnitionValue
	ldx	3,s
	pshx
	pulh
	ldx	4,s
	sta	,x
;comms.c:539: return true;
	lda	#0x01
	bra	00107$
00104$:
;comms.c:542: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
	txa
;comms.c:541: if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
	cphx	#0x009c
	bcc	00106$
;comms.c:542: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
	sub	#0x90
;comms.c:543: *value = encodeRpmBin(ignTable.axisX[idx]);
	lsla	
	tax
	clrh
	lda	(_ignTable+1),x
	ldx	(_ignTable),x
	jsr	_encodeRpmBin
	ldx	3,s
	pshx
	pulh
	ldx	4,s
	sta	,x
;comms.c:544: return true;
	lda	#0x01
	bra	00107$
00106$:
;comms.c:547: uint8_t idx = (uint8_t)(offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN));
	sub	#0x9c
;comms.c:548: *value = ignTable.axisY[idx];
	tax
	clrh
	lda	((_ignTable + 0x0018)),x
	ldx	3,s
	pshx
	pulh
	ldx	4,s
	sta	,x
;comms.c:549: return true;
	lda	#0x01
00107$:
;comms.c:551: }
	ais	#4
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'writeIgnTablePageByte'
;------------------------------------------------------------
;value                     Allocated to stack - sp +5
;offset                    Allocated to registers x h 
;idx                       Allocated to registers a 
;idx                       Allocated to registers a 
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;comms.c:553: static PageWriteStatus writeIgnTablePageByte(uint16_t offset, uint8_t value) {
;	-----------------------------------------
;	 function writeIgnTablePageByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_writeIgnTablePageByte:
	ais	#-2
	pshx
	tax
	pulh
;comms.c:554: if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return PAGE_WRITE_FAIL;
	cphx	#0x00a8
	bcs	00102$
	clra
	bra	00107$
00102$:
;comms.c:556: if (offset < SPEEDUINO_TABLE_CELLS) {
	cphx	#0x0090
	bcc	00104$
;comms.c:557: eepromWriteI8(ignTable.eepromValuesBase + offset, decodeIgnitionValue(value));
	pshx
	pshh
	lda	7,s
	jsr	_decodeIgnitionValue
	pulh
	pulx
	psha
	lda	(_ignTable + 0x0024)
	sta	2,s
	lda	((_ignTable + 0x0024) + 1)
	sta	3,s
	pula
	psha
	txa
	add	3,s
	tax
	pshh
	pula
	adc	2,s
	psha
	pulh
	pula
	psha
	txa
	pshh
	pulx
	jsr	_eepromWriteI8
	ais	#1
;comms.c:558: return PAGE_WRITE_TABLE_CHANGED;
	lda	#0x02
	bra	00107$
00104$:
;comms.c:561: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
	txa
;comms.c:560: if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
	cphx	#0x009c
	bcc	00106$
;comms.c:561: uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
	sub	#0x90
;comms.c:562: ignTable.axisX[idx] = decodeRpmBin(value);
	lsla	
	tax
	clrh
	pshx
	pshh
	lda	7,s
	jsr	_decodeRpmBin
	sta	4,s
	stx	3,s
	pulh
	pulx
	lda	1,s
	sta	(_ignTable),x
	lda	2,s
	sta	(_ignTable+1),x
;comms.c:563: return PAGE_WRITE_TABLE_CHANGED;
	lda	#0x02
	bra	00107$
00106$:
;comms.c:566: uint8_t idx = (uint8_t)(offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN));
	sub	#0x9c
;comms.c:567: ignTable.axisY[idx] = value;
	tax
	clrh
	lda	5,s
	sta	((_ignTable + 0x0018)),x
;comms.c:568: return PAGE_WRITE_TABLE_CHANGED;
	lda	#0x02
00107$:
;comms.c:570: }
	ais	#2
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'readPageByte'
;------------------------------------------------------------
;offset                    Allocated to stack - sp +4
;value                     Allocated to stack - sp +6
;page                      Allocated to stack - sp +1
;------------------------------------------------------------
;comms.c:572: static bool readPageByte(uint8_t page, uint16_t offset, uint8_t *value) {
;	-----------------------------------------
;	 function readPageByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 1 bytes.
_readPageByte:
	psha
;comms.c:573: switch (page) {
	lda	1,s
	cmp	#0x04
	bhi	00105$
	ldx	1,s
	clrh
	lda	00116$,x
	ldx	00115$,x
	psha
	pulh
	jmp	,x
00115$:
	.db	00105$
	.db	00101$
	.db	00102$
	.db	00103$
	.db	00104$
00116$:
	.db	>00105$
	.db	>00101$
	.db	>00102$
	.db	>00103$
	.db	>00104$
;comms.c:574: case 1: return readStructPageByte((uint8_t *)&configPage1, sizeof(struct ConfigPage1), offset, value);
00101$:
	tsx
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	lda	3,x
	psha
	lda	#0x1e
	psha
	clra
	psha
	lda	#_configPage1
	ldx	#>_configPage1
	jsr	_readStructPageByte
	ais	#6
	bra	00107$
;comms.c:575: case 2: return readVeTablePageByte(offset, value);
00102$:
	tsx
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	ldx	3,x
	jsr	_readVeTablePageByte
	ais	#2
	bra	00107$
;comms.c:576: case 3: return readIgnTablePageByte(offset, value);
00103$:
	tsx
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	ldx	3,x
	jsr	_readIgnTablePageByte
	ais	#2
	bra	00107$
;comms.c:577: case 4: return readStructPageByte((uint8_t *)&configPage2, sizeof(struct ConfigPage2), offset, value);
00104$:
	tsx
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	lda	3,x
	psha
	lda	#0x20
	psha
	clra
	psha
	lda	#_configPage2
	ldx	#>_configPage2
	jsr	_readStructPageByte
	ais	#6
	bra	00107$
;comms.c:578: default: return readStubPageByte(page, offset, value);
00105$:
	tsx
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	lda	3,x
	psha
	lda	,x
	jsr	_readStubPageByte
	ais	#4
;comms.c:579: }
00107$:
;comms.c:580: }
	ais	#1
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'writePageByte'
;------------------------------------------------------------
;offset                    Allocated to stack - sp +6
;value                     Allocated to stack - sp +8
;page                      Allocated to stack - sp +3
;pageSz                    Allocated to stack - sp +1
;sloc0                     Allocated to stack - sp +1
;------------------------------------------------------------
;comms.c:582: static PageWriteStatus writePageByte(uint8_t page, uint16_t offset, uint8_t value) {
;	-----------------------------------------
;	 function writePageByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 3 bytes.
_writePageByte:
	psha
	ais	#-2
;comms.c:583: switch (page) {
	lda	3,s
	cmp	#0x04
	bhi	00105$
	ldx	3,s
	clrh
	lda	00124$,x
	ldx	00123$,x
	psha
	pulh
	jmp	,x
00123$:
	.db	00105$
	.db	00101$
	.db	00102$
	.db	00103$
	.db	00104$
00124$:
	.db	>00105$
	.db	>00101$
	.db	>00102$
	.db	>00103$
	.db	>00104$
;comms.c:584: case 1: return writeStructPageByte((uint8_t *)&configPage1, sizeof(struct ConfigPage1), offset, value);
00101$:
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	#0x1e
	psha
	clra
	psha
	lda	#_configPage1
	ldx	#>_configPage1
	jsr	_writeStructPageByte
	ais	#5
	bra	00110$
;comms.c:585: case 2: return writeVeTablePageByte(offset, value);
00102$:
	tsx
	lda	7,x
	psha
	lda	6,x
	ldx	5,x
	jsr	_writeVeTablePageByte
	ais	#1
	bra	00110$
;comms.c:586: case 3: return writeIgnTablePageByte(offset, value);
00103$:
	tsx
	lda	7,x
	psha
	lda	6,x
	ldx	5,x
	jsr	_writeIgnTablePageByte
	ais	#1
	bra	00110$
;comms.c:587: case 4: return writeStructPageByte((uint8_t *)&configPage2, sizeof(struct ConfigPage2), offset, value);
00104$:
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	#0x20
	psha
	clra
	psha
	lda	#_configPage2
	ldx	#>_configPage2
	jsr	_writeStructPageByte
	ais	#5
	bra	00110$
;comms.c:588: default: {
00105$:
;comms.c:589: uint16_t pageSz = getPageSize(page);
	lda	3,s
	jsr	_getPageSize
	stx	1,s
	sta	2,s
;comms.c:590: if (pageSz == 0 || offset >= pageSz) return PAGE_WRITE_FAIL;
	tsta
	bne	00125$
	tstx
00125$:
	beq	00106$
	tsx
	lda	6,x
	sub	1,x
	lda	5,x
	sbc	,x
	bcs	00107$
00106$:
	clra
	bra	00110$
00107$:
;comms.c:591: return PAGE_WRITE_OK;
	lda	#0x01
;comms.c:593: }
00110$:
;comms.c:594: }
	ais	#3
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'sendPageValues'
;------------------------------------------------------------
;offset                    Allocated to stack - sp +63
;length                    Allocated to stack - sp +65
;page                      Allocated to stack - sp +60
;pageSz                    Allocated to registers a x 
;available                 Allocated to stack - sp +58
;actualLength              Allocated to stack - sp +56
;responseLength            Allocated to registers a x 
;remaining                 Allocated to stack - sp +54
;pos                       Allocated to stack - sp +52
;tempBuf                   Allocated to stack - sp +6
;crc                       Allocated to stack - sp +2
;err                       Allocated to stack - sp +1
;blockSize                 Allocated to stack - sp +50
;i                         Allocated to stack - sp +48
;byteValue                 Allocated to stack - sp +1
;sloc0                     Allocated to stack - sp +42
;sloc1                     Allocated to stack - sp +38
;sloc2                     Allocated to stack - sp +40
;sloc3                     Allocated to stack - sp +46
;------------------------------------------------------------
;comms.c:596: void sendPageValues(uint8_t page, uint16_t offset, uint16_t length) {
;	-----------------------------------------
;	 function sendPageValues
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 60 bytes.
_sendPageValues:
	psha
	ais	#-59
;comms.c:597: uint16_t pageSz = getPageSize(page);
	lda	60,s
	jsr	_getPageSize
;comms.c:602: if (pageSz == 0) {
	tsta
	bne	00181$
	tstx
00181$:
	bne	00102$
;comms.c:603: uint8_t err = SERIAL_RC_RANGE_ERR;
	lda	#0x80
	sta	1,s
;comms.c:604: sendU16BE(1);
	lda	#0x01
	clrx
	jsr	_sendU16BE
;comms.c:605: sendByte(err);
	lda	1,s
	jsr	_sendByte
;comms.c:606: sendU32BE(calculateCRC32(&err, 1));
	tsx
	lda	#0x01
	psha
	deca
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	47,s
	stx	46,s
	lda	*___SDCC_hc08_ret2
	sta	45,s
	lda	*___SDCC_hc08_ret3
	sta	44,s
	ais	#2
	tsx
	lda	44,x
	psha
	lda	43,x
	psha
	lda	42,x
	psha
	lda	41,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:607: return;
	jmp	00116$
00102$:
;comms.c:610: available = (offset < pageSz) ? (uint16_t)(pageSz - offset) : 0;
	psha
	psha
	lda	66,s
	sub	1, s
	pula
	lda	64,s
	pshx
	sbc	1,s
	ais	#1
	pula
	bcc	00118$
	sub	64,s
	psha
	txa
	sbc	64,s
	tax
	pula
	bra	00119$
00118$:
	clrx
	txa
00119$:
	sta	59,s
	stx	58,s
;comms.c:611: actualLength = (length < available) ? length : available;
	tsx
	lda	65,x
	sub	58,x
	lda	64,x
	sbc	57,x
	bcc	00120$
	lda	64,x
	sta	55,x
	lda	65,x
	sta	56,x
	bra	00121$
00120$:
	tsx
	lda	57,x
	sta	55,x
	lda	58,x
	sta	56,x
00121$:
	tsx
;comms.c:612: responseLength = (uint16_t)(1 + actualLength);
	lda	56,x
	ldx	55,x
	inca
	bne	00185$
	incx
00185$:
;comms.c:614: sendU16BE(responseLength);
	jsr	_sendU16BE
;comms.c:616: sendByte(SERIAL_RC_OK);
	clra
	jsr	_sendByte
;comms.c:617: crc = crc32Update(crc, SERIAL_RC_OK);
	clra
	psha
	deca
	psha
	psha
	psha
	psha
	jsr	_crc32Update
	sta	10,s
	stx	9,s
	lda	*___SDCC_hc08_ret2
	sta	8,s
	lda	*___SDCC_hc08_ret3
	sta	7,s
	ais	#5
;comms.c:619: remaining = actualLength;
	tsx
	lda	55,x
	sta	53,x
	lda	56,x
	sta	54,x
;comms.c:620: pos = 0;
	clra
	sta	51,x
	sta	52,x
;comms.c:622: while (remaining > 0) {
	tsx
	aix	#5
	pshh
	pula
	sta	42,s
	stx	43,s
	tsx
	lda	41,x
	sta	37,x
	lda	42,x
	sta	38,x
00107$:
	tsx
	lda	54,x
	ora	53,x
	bne	00186$
	jmp	00109$
00186$:
;comms.c:623: uint16_t blockSize = (remaining < sizeof(tempBuf)) ? remaining : (uint16_t)sizeof(tempBuf);
	lda	54,x
	sub	#0x20
	lda	53,x
	sbc	#0x00
	bcc	00122$
	lda	53,x
	sta	49,x
	lda	54,x
	sta	50,x
	bra	00123$
00122$:
	tsx
	clra
	sta	49,x
	lda	#0x20
	sta	50,x
00123$:
	tsx
;comms.c:626: for (i = 0; i < blockSize; i++) {
	lda	52,x
	add	63,x
	sta	40,x
	lda	51,x
	adc	62,x
	sta	39,x
	clra
	sta	47,x
	sta	48,x
00111$:
	tsx
	lda	48,x
	sub	50,x
	lda	47,x
	sbc	49,x
	bcc	00105$
;comms.c:627: uint8_t byteValue = 0;
	clra
	sta	,x
;comms.c:628: if (!readPageByte(page, (uint16_t)(offset + pos + i), &byteValue)) {
	tsx
	lda	49,s
	add	41,s
	sta	47,s
	lda	48,s
	adc	40,s
	sta	46,s
	pshx
	pshh
	tsx
	lda	48,x
	psha
	lda	47,x
	psha
	lda	61,x
	jsr	_readPageByte
	ais	#4
	tsta
	bne	00104$
;comms.c:629: byteValue = 0;
	clra
	sta	1,s
00104$:
;comms.c:631: tempBuf[i] = byteValue;
	lda	49,s
	add	43,s
	tax
	lda	48,s
	adc	42,s
	psha
	pulh
	lda	1,s
	sta	,x
;comms.c:626: for (i = 0; i < blockSize; i++) {
	tsx
	inc	48,x
	bne	00190$
	inc	47,x
00190$:
	bra	00111$
00105$:
;comms.c:634: sendBytes(tempBuf, blockSize);
	lda	38,s
	psha
	pulh
	ldx	39,s
	lda	51,s
	psha
	lda	51,s
	psha
	txa
	pshh
	pulx
	jsr	_sendBytes
	ais	#2
;comms.c:636: for (i = 0; i < blockSize; i++) {
	clrh
	clrx
00114$:
	txa
	sub	51,s
	pshh
	pula
	sbc	50,s
	bcc	00106$
;comms.c:637: crc = crc32Update(crc, tempBuf[i]);
	txa
	add	39,s
	sta	47,s
	pshh
	pula
	adc	38,s
	sta	46,s
	pshx
	pshh
	lda	48,s
	psha
	pulh
	ldx	49,s
	lda	,x
	pulh
	pulx
	pshx
	pshh
	psha
	lda	8,s
	psha
	lda	8,s
	psha
	lda	8,s
	psha
	lda	8,s
	psha
	jsr	_crc32Update
	sta	12,s
	stx	11,s
	lda	*___SDCC_hc08_ret2
	sta	10,s
	lda	*___SDCC_hc08_ret3
	sta	9,s
	ais	#5
	pulh
	pulx
;comms.c:636: for (i = 0; i < blockSize; i++) {
	aix	#1
	bra	00114$
00106$:
;comms.c:640: pos = (uint16_t)(pos + blockSize);
	tsx
	lda	50,x
	add	52,x
	sta	52,x
	lda	49,x
	adc	51,x
	sta	51,x
;comms.c:641: remaining = (uint16_t)(remaining - blockSize);
	lda	54,x
	sub	50,x
	sta	54,x
	lda	53,x
	sbc	49,x
	sta	53,x
	jmp	00107$
00109$:
;comms.c:644: crc = ~crc;
	tsx
	lda	4,x
	coma
	sta	4,x
	lda	3,x
	coma
	sta	3,x
	lda	2,x
	coma
	sta	2,x
	lda	1,x
	coma
	sta	1,x
;comms.c:645: sendU32BE(crc);
	lda	4,x
	psha
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	jsr	_sendU32BE
	ais	#4
00116$:
;comms.c:646: }
	ais	#60
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'writePageValues'
;------------------------------------------------------------
;offset                    Allocated to stack - sp +10
;length                    Allocated to stack - sp +12
;data                      Allocated to stack - sp +14
;page                      Allocated to stack - sp +5
;pageSz                    Allocated to stack - sp +3
;i                         Allocated to stack - sp +6
;status                    Allocated to registers a 
;sloc0                     Allocated to stack - sp +3
;sloc1                     Allocated to stack - sp +1
;------------------------------------------------------------
;comms.c:648: uint8_t writePageValues(uint8_t page, uint16_t offset, uint16_t length, const uint8_t *data) {
;	-----------------------------------------
;	 function writePageValues
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 7 bytes.
_writePageValues:
	ais	#-7
	sta	5,s
;comms.c:649: uint16_t pageSz = getPageSize(page);
	lda	5,s
	jsr	_getPageSize
	stx	3,s
	sta	4,s
;comms.c:652: if (pageSz == 0 || (offset + length) > pageSz) {
	tsta
	bne	00132$
	tstx
00132$:
	beq	00101$
	tsx
	lda	10,x
	add	12,x
	sta	1,x
	lda	9,x
	adc	11,x
	sta	,x
	lda	3,x
	sub	1,x
	lda	2,x
	sbc	,x
	bcc	00115$
00101$:
;comms.c:653: return SERIAL_RC_RANGE_ERR;
	lda	#0x80
	bra	00110$
;comms.c:656: for (i = 0; i < length; i++) {
00115$:
	tsx
	clra
	sta	5,x
	sta	6,x
00108$:
	tsx
	lda	6,x
	sub	12,x
	lda	5,x
	sbc	11,x
	bcc	00106$
;comms.c:657: PageWriteStatus status = writePageByte(page, (uint16_t)(offset + i), data[i]);
	lda	6,x
	add	14,x
	tax
	lda	6,s
	adc	14,s
	psha
	pulh
	lda	,x
	psha
	pulh
	lda	7,s
	add	11,s
	tax
	lda	6,s
	adc	10,s
	pshh
	pshx
	psha
	lda	8,s
	jsr	_writePageByte
	ais	#3
;comms.c:658: if (status == PAGE_WRITE_FAIL) {
	tsta
	bne	00109$
;comms.c:659: return SERIAL_RC_RANGE_ERR;
	lda	#0x80
	bra	00110$
00109$:
;comms.c:656: for (i = 0; i < length; i++) {
	tsx
	inc	6,x
	bne	00137$
	inc	5,x
00137$:
	bra	00108$
00106$:
;comms.c:663: return SERIAL_RC_OK;
	clra
00110$:
;comms.c:664: }
	ais	#7
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'sendPageCRC32'
;------------------------------------------------------------
;page                      Allocated to stack - sp +23
;pageSz                    Allocated to stack - sp +24
;crc                       Allocated to stack - sp +2
;pageCRC                   Allocated to stack - sp +17
;reversedCRC               Allocated to stack - sp +13
;i                         Allocated to stack - sp +26
;response                  Allocated to stack - sp +6
;err                       Allocated to stack - sp +1
;byteValue                 Allocated to stack - sp +1
;sloc0                     Allocated to stack - sp +19
;sloc1                     Allocated to stack - sp +15
;sloc2                     Allocated to stack - sp +11
;------------------------------------------------------------
;comms.c:666: void sendPageCRC32(uint8_t page) {
;	-----------------------------------------
;	 function sendPageCRC32
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 27 bytes.
_sendPageCRC32:
	ais	#-27
	sta	23,s
;comms.c:667: uint16_t pageSz = getPageSize(page);
	lda	23,s
	jsr	_getPageSize
	sta	25,s
	stx	24,s
;comms.c:668: uint32_t crc = 0xFFFFFFFFUL, pageCRC, reversedCRC;
	tsx
	lda	#0xff
	sta	1,x
	sta	2,x
	sta	3,x
	sta	4,x
;comms.c:672: if (pageSz == 0) {
	lda	24,x
	ora	23,x
	bne	00114$
;comms.c:673: uint8_t err = SERIAL_RC_RANGE_ERR;
	lda	#0x80
	sta	,x
;comms.c:674: sendU16BE(1);
	lda	#0x01
	clrx
	jsr	_sendU16BE
;comms.c:675: sendByte(err);
	lda	1,s
	jsr	_sendByte
;comms.c:676: sendU32BE(calculateCRC32(&err, 1));
	tsx
	lda	#0x01
	psha
	deca
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	24,s
	stx	23,s
	lda	*___SDCC_hc08_ret2
	sta	22,s
	lda	*___SDCC_hc08_ret3
	sta	21,s
	ais	#2
	tsx
	lda	21,x
	psha
	lda	20,x
	psha
	lda	19,x
	psha
	lda	18,x
	psha
	jsr	_sendU32BE
	ais	#4
;comms.c:677: return;
	jmp	00109$
;comms.c:680: for (i = 0; i < pageSz; i++) {
00114$:
	tsx
	clra
	sta	25,x
	sta	26,x
00107$:
	tsx
	lda	26,x
	sub	24,x
	lda	25,x
	sbc	23,x
	bcc	00105$
;comms.c:681: uint8_t byteValue = 0;
	clra
	sta	,x
;comms.c:682: if (!readPageByte(page, i, &byteValue)) {
	tsx
	pshx
	pshh
	tsx
	lda	28,x
	psha
	lda	27,x
	psha
	lda	24,x
	jsr	_readPageByte
	ais	#4
	tsta
	bne	00104$
;comms.c:683: byteValue = 0;
	clra
	sta	1,s
00104$:
;comms.c:685: crc = crc32Update(crc, byteValue);
	tsx
	lda	,x
	psha
	lda	4,x
	psha
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	jsr	_crc32Update
	sta	10,s
	stx	9,s
	lda	*___SDCC_hc08_ret2
	sta	8,s
	lda	*___SDCC_hc08_ret3
	sta	7,s
	ais	#5
;comms.c:680: for (i = 0; i < pageSz; i++) {
	tsx
	inc	26,x
	bne	00135$
	inc	25,x
00135$:
	bra	00107$
00105$:
;comms.c:688: pageCRC = ~crc;
	tsx
	lda	4,x
	coma
	sta	21,x
	lda	3,x
	coma
	sta	20,x
	lda	2,x
	coma
	sta	19,x
	lda	1,x
	coma
	sta	18,x
;comms.c:689: reversedCRC = ((pageCRC & 0xFFUL) << 24) | ((pageCRC & 0xFF00UL) << 8) |
	lda	21,x
	sta	17,x
	clra
	sta	16,x
	sta	15,x
	sta	14,x
	lda	17,x
	sta	14,x
	clra
	sta	17,x
	sta	16,x
	sta	15,x
	sta	13,x
	lda	20,x
	sta	12,x
	clra
	sta	11,x
	sta	10,x
	lda	11,x
	sta	10,x
	lda	12,x
	sta	11,x
	lda	13,x
	sta	12,x
	clra
	sta	13,x
	lda	17,x
	ora	13,x
	sta	13,x
	lda	16,x
	ora	12,x
	sta	12,x
	lda	15,x
	ora	11,x
	sta	11,x
	lda	14,x
	ora	10,x
	sta	10,x
;comms.c:690: ((pageCRC & 0xFF0000UL) >> 8) | ((pageCRC & 0xFF000000UL) >> 24);
	clra
	sta	17,x
	sta	16,x
	lda	19,x
	sta	15,x
	clra
	sta	14,x
	lda	16,x
	sta	17,x
	lda	15,x
	sta	16,x
	lda	14,x
	sta	15,x
	clrx
	stx	15,s
	tsx
	lda	13,x
	ora	17,x
	sta	13,x
	lda	12,x
	ora	16,x
	sta	12,x
	lda	11,x
	ora	15,x
	sta	11,x
	lda	10,x
	ora	14,x
	sta	10,x
	clra
	sta	17,x
	sta	16,x
	sta	15,x
	lda	18,x
	sta	14,x
	lda	14,x
	sta	17,x
	clrx
	stx	17,s
	stx	16,s
	stx	15,s
	tsx
	lda	13,x
	ora	17,x
	sta	13,x
	lda	12,x
	ora	16,x
	sta	12,x
	lda	11,x
	ora	15,x
	sta	11,x
	lda	10,x
	ora	14,x
	sta	10,x
;comms.c:692: response[0] = SERIAL_RC_OK;
	tsx
	aix	#5
	pshh
	pula
	sta	15,s
	stx	16,s
	lda	15,s
	psha
	pulh
	ldx	16,s
	clra
	sta	,x
;comms.c:693: response[1] = (uint8_t)(reversedCRC & 0xFF);
	tsx
	lda	14,x
	sta	18,x
	lda	15,x
	sta	19,x
	lda	13,x
	ldx	18,x
	pshx
	pulh
	ldx	20,s
	sta	1,x
;comms.c:694: response[2] = (uint8_t)((reversedCRC >> 8) & 0xFF);
	tsx
	lda	14,x
	sta	18,x
	lda	15,x
	sta	19,x
	lda	12,x
	ldx	18,x
	pshx
	pulh
	ldx	20,s
	sta	2,x
;comms.c:695: response[3] = (uint8_t)((reversedCRC >> 16) & 0xFF);
	tsx
	lda	14,x
	sta	18,x
	lda	15,x
	sta	19,x
	lda	11,x
	ldx	18,x
	pshx
	pulh
	ldx	20,s
	sta	3,x
;comms.c:696: response[4] = (uint8_t)((reversedCRC >> 24) & 0xFF);
	tsx
	lda	14,x
	sta	18,x
	lda	15,x
	sta	19,x
	lda	10,x
	ldx	18,x
	pshx
	pulh
	ldx	20,s
	sta	4,x
;comms.c:698: sendU16BE(5);
	lda	#0x05
	clrx
	jsr	_sendU16BE
;comms.c:699: sendBytes(response, 5);
	tsx
	lda	14,x
	sta	10,x
	lda	15,x
	sta	11,x
	lda	10,x
	psha
	pulh
	ldx	12,s
	lda	#0x05
	psha
	clra
	psha
	txa
	pshh
	pulx
	jsr	_sendBytes
	ais	#2
;comms.c:700: sendU32BE(calculateCRC32(response, 5));
	tsx
	lda	14,x
	sta	10,x
	lda	15,x
	sta	11,x
	lda	10,x
	psha
	pulh
	ldx	12,s
	lda	#0x05
	psha
	clra
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	16,s
	stx	15,s
	lda	*___SDCC_hc08_ret2
	sta	14,s
	lda	*___SDCC_hc08_ret3
	sta	13,s
	ais	#2
	tsx
	lda	13,x
	psha
	lda	12,x
	psha
	lda	11,x
	psha
	lda	10,x
	psha
	jsr	_sendU32BE
	ais	#4
00109$:
;comms.c:701: }
	ais	#27
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'sendOutputChannels'
;------------------------------------------------------------
;offset                    Allocated to stack - sp +13
;length                    Allocated to stack - sp +15
;subcmd                    Allocated to registers a 
;fullBufferSize            Allocated to registers 
;crc                       Allocated to stack - sp +1
;responseLength            Allocated to registers a x 
;i                         Allocated to stack - sp +9
;idx                       Allocated to registers a x 
;b                         Allocated to registers a 
;err                       Allocated to stack - sp +4
;sloc0                     Allocated to stack - sp +5
;------------------------------------------------------------
;comms.c:703: void sendOutputChannels(uint8_t subcmd, uint16_t offset, uint16_t length) {
;	-----------------------------------------
;	 function sendOutputChannels
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 10 bytes.
_sendOutputChannels:
	ais	#-10
;comms.c:704: if (subcmd == 0x30) {
	cbeqa	#0x30,00147$
	jmp	00107$
00147$:
;comms.c:709: if (offset >= fullBufferSize) {
	tsx
	lda	13,x
	sub	#0x7f
	lda	12,x
	sbc	#0x00
	bcs	00102$
;comms.c:710: offset = 0;
	clra
	sta	12,x
	sta	13,x
;comms.c:711: length = 0;
	sta	14,x
	sta	15,x
00102$:
;comms.c:713: if ((uint16_t)(offset + length) > fullBufferSize) {
	lda	14,s
	add	16,s
	tax
	lda	13,s
	adc	15,s
	psha
	pulh
	cphx	#0x007f
	bls	00104$
;comms.c:714: length = (uint16_t)(fullBufferSize - offset);
	tsx
	lda	#0x7f
	sub	13,x
	sta	15,x
	clra
	sbc	12,x
	sta	14,x
00104$:
;comms.c:717: responseLength = (uint16_t)(1 + length);
	lda	16,s
	ldx	15,s
	inca
	bne	00150$
	incx
00150$:
;comms.c:718: sendU16BE(responseLength);
	jsr	_sendU16BE
;comms.c:719: sendByte(SERIAL_RC_OK);
	clra
	jsr	_sendByte
;comms.c:720: crc = crc32Update(crc, SERIAL_RC_OK);
	clra
	psha
	deca
	psha
	psha
	psha
	psha
	jsr	_crc32Update
	sta	9,s
	stx	8,s
	lda	*___SDCC_hc08_ret2
	sta	7,s
	lda	*___SDCC_hc08_ret3
	sta	6,s
	ais	#5
;comms.c:722: for (i = 0; i < length; i++) {
	tsx
	clra
	sta	8,x
	sta	9,x
00110$:
	tsx
	lda	9,x
	sub	15,x
	lda	8,x
	sbc	14,x
	bcc	00105$
;comms.c:723: uint16_t idx = (uint16_t)(offset + i);
	lda	9,x
	add	13,x
	psha
	lda	8,x
	adc	12,x
	tax
	pula
;comms.c:724: uint8_t b = (idx == 0) ? 0x00 : realtimeByte((uint8_t)(idx - 1));
	tsta
	bne	00152$
	tstx
00152$:
	bne	00114$
	clrx
	txa
	bra	00115$
00114$:
	deca
	jsr	_realtimeByte
	clrx
00115$:
;comms.c:725: sendByte(b);
	psha
	jsr	_sendByte
	pula
;comms.c:726: crc = crc32Update(crc, b);
	psha
	tsx
	lda	4,x
	psha
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	jsr	_crc32Update
	sta	9,s
	stx	8,s
	lda	*___SDCC_hc08_ret2
	sta	7,s
	lda	*___SDCC_hc08_ret3
	sta	6,s
	ais	#5
;comms.c:722: for (i = 0; i < length; i++) {
	tsx
	inc	9,x
	bne	00154$
	inc	8,x
00154$:
	bra	00110$
00105$:
;comms.c:728: crc = ~crc;
	tsx
	lda	3,x
	coma
	sta	3,x
	lda	2,x
	coma
	sta	2,x
	lda	1,x
	coma
	sta	1,x
	lda	,x
	coma
	sta	,x
;comms.c:729: sendU32BE(crc);
	lda	3,x
	psha
	lda	2,x
	psha
	lda	1,x
	psha
	lda	,x
	psha
	jsr	_sendU32BE
	ais	#4
	bra	00112$
00107$:
;comms.c:731: uint8_t err = SERIAL_RC_UKWN_ERR;
	lda	#0x83
	sta	4,s
;comms.c:732: sendU16BE(1);
	lda	#0x01
	clrx
	jsr	_sendU16BE
;comms.c:733: sendByte(err);
	lda	4,s
	jsr	_sendByte
;comms.c:734: sendU32BE(calculateCRC32(&err, 1));
	tsx
	aix	#3
	lda	#0x01
	psha
	deca
	psha
	txa
	pshh
	pulx
	jsr	_calculateCRC32
	sta	10,s
	stx	9,s
	lda	*___SDCC_hc08_ret2
	sta	8,s
	lda	*___SDCC_hc08_ret3
	sta	7,s
	ais	#2
	tsx
	lda	7,x
	psha
	lda	6,x
	psha
	lda	5,x
	psha
	lda	4,x
	psha
	jsr	_sendU32BE
	ais	#4
00112$:
;comms.c:736: }
	ais	#10
	rts
;------------------------------------------------------------
;Allocation info for local variables in function 'burnEEPROM'
;------------------------------------------------------------
;comms.c:738: void burnEEPROM(void) {
;	-----------------------------------------
;	 function burnEEPROM
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_burnEEPROM:
;comms.c:739: saveAllConfig();
;comms.c:740: }
	jmp	_saveAllConfig
;------------------------------------------------------------
;Allocation info for local variables in function 'realtimeByte'
;------------------------------------------------------------
;index                     Allocated to registers a 
;------------------------------------------------------------
;comms.c:751: uint8_t realtimeByte(uint8_t index) {
;	-----------------------------------------
;	 function realtimeByte
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_realtimeByte:
;comms.c:752: switch (index) {
	cmp	#0x66
	bls	00164$
	jmp	00134$
00164$:
	tax
	clrh
	lda	00166$,x
	ldx	00165$,x
	psha
	pulh
	jmp	,x
00165$:
	.db	00101$
	.db	00102$
	.db	00103$
	.db	00104$
	.db	00105$
	.db	00106$
	.db	00107$
	.db	00108$
	.db	00109$
	.db	00110$
	.db	00111$
	.db	00112$
	.db	00113$
	.db	00114$
	.db	00115$
	.db	00116$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00117$
	.db	00118$
	.db	00119$
	.db	00120$
	.db	00121$
	.db	00122$
	.db	00134$
	.db	00134$
	.db	00123$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00124$
	.db	00134$
	.db	00134$
	.db	00125$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00126$
	.db	00127$
	.db	00128$
	.db	00129$
	.db	00130$
	.db	00131$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00132$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00134$
	.db	00133$
00166$:
	.db	>00101$
	.db	>00102$
	.db	>00103$
	.db	>00104$
	.db	>00105$
	.db	>00106$
	.db	>00107$
	.db	>00108$
	.db	>00109$
	.db	>00110$
	.db	>00111$
	.db	>00112$
	.db	>00113$
	.db	>00114$
	.db	>00115$
	.db	>00116$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00117$
	.db	>00118$
	.db	>00119$
	.db	>00120$
	.db	>00121$
	.db	>00122$
	.db	>00134$
	.db	>00134$
	.db	>00123$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00124$
	.db	>00134$
	.db	>00134$
	.db	>00125$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00126$
	.db	>00127$
	.db	>00128$
	.db	>00129$
	.db	>00130$
	.db	>00131$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00132$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00134$
	.db	>00133$
;comms.c:753: case 0:   return (uint8_t)(currentStatus.secl & 0xFF);
00101$:
	lda	((_currentStatus + 0x0032)+3)
	rts
;comms.c:754: case 1:   return (currentStatus.RPM > 0) ? 0x01 : 0x00;
00102$:
	ldx	_currentStatus
	lda	(_currentStatus + 1)
	bne	00167$
	tstx
00167$:
	beq	00138$
	clrx
	lda	#0x01
	rts
00138$:
	clrx
	txa
	rts
;comms.c:755: case 2:   return currentStatus.engineStatus;
00103$:
	lda	(_currentStatus + 0x002a)
	rts
;comms.c:756: case 3:   return currentStatus.hasSync ? 0 : 1;
00104$:
	lda	(_currentStatus + 0x0002)
	beq	00140$
	clrx
	txa
	rts
00140$:
	clrx
	lda	#0x01
	rts
;comms.c:757: case 4:   return (uint8_t)(((uint16_t)(currentStatus.MAP * 10)) & 0xFF);
00105$:
	lda	(_currentStatus + 0x0013)
	ldx	#0x0a
	mul
	rts
;comms.c:758: case 5:   return (uint8_t)((((uint16_t)(currentStatus.MAP * 10)) >> 8) & 0xFF);
00106$:
	lda	(_currentStatus + 0x0013)
	clrx
	psha
	pshx
	lda	#0x0a
	jsr	__mulint
	ais	#2
	txa
	rts
;comms.c:759: case 6:   return (uint8_t)(currentStatus.IAT + 40);
00107$:
	lda	(_currentStatus + 0x0016)
	add	#0x28
	rts
;comms.c:760: case 7:   return (uint8_t)(currentStatus.coolant + 40);
00108$:
	lda	(_currentStatus + 0x0015)
	add	#0x28
	rts
;comms.c:761: case 8:   return currentStatus.batCorrection;
00109$:
	lda	(_currentStatus + 0x0029)
	rts
;comms.c:762: case 9:   return currentStatus.battery10;
00110$:
	lda	(_currentStatus + 0x0019)
	rts
;comms.c:763: case 10:  return currentStatus.O2;
00111$:
	lda	(_currentStatus + 0x0017)
	rts
;comms.c:764: case 11:  return 100;
00112$:
	lda	#0x64
	rts
;comms.c:765: case 12:  return 100;
00113$:
	lda	#0x64
	rts
;comms.c:766: case 13:  return currentStatus.wueCorrection;
00114$:
	lda	(_currentStatus + 0x0028)
	rts
;comms.c:767: case 14:  return (uint8_t)(currentStatus.RPM & 0xFF);
00115$:
	lda	(_currentStatus+1)
	rts
;comms.c:768: case 15:  return (uint8_t)((currentStatus.RPM >> 8) & 0xFF);
00116$:
	ldx	_currentStatus
	lda	(_currentStatus + 1)
	txa
	rts
;comms.c:769: case 24:  return (uint8_t)(currentStatus.advance + 40);
00117$:
	lda	(_currentStatus + 0x0025)
	add	#0x28
	rts
;comms.c:770: case 25:  return currentStatus.TPS;
00118$:
	lda	(_currentStatus + 0x0014)
	rts
;comms.c:771: case 26:  return (uint8_t)(2000U & 0xFF);
00119$:
	lda	#0xd0
	rts
;comms.c:772: case 27:  return (uint8_t)((2000U >> 8) & 0xFF);
00120$:
	lda	#0x07
	rts
;comms.c:773: case 28:  return (uint8_t)(getFreeRam() & 0xFF);
00121$:
	jmp	_getFreeRam
;comms.c:774: case 29:  return (uint8_t)((getFreeRam() >> 8) & 0xFF);
00122$:
	jsr	_getFreeRam
	txa
	rts
;comms.c:775: case 32:  return currentStatus.hasSync ? 0x01 : 0x00;
00123$:
	lda	(_currentStatus + 0x0002)
	beq	00142$
	clrx
	lda	#0x01
	rts
00142$:
	clrx
	txa
	rts
;comms.c:776: case 38:  return currentStatus.idleValveDuty;
00124$:
	lda	(_currentStatus + 0x002e)
	rts
;comms.c:777: case 41:  return 100;
00125$:
	lda	#0x64
	rts
;comms.c:778: case 76:  return (uint8_t)(currentStatus.PW1 & 0xFF);
00126$:
	lda	((_currentStatus + 0x001c)+1)
	rts
;comms.c:779: case 77:  return (uint8_t)((currentStatus.PW1 >> 8) & 0xFF);
00127$:
	ldx	(_currentStatus + 0x001c)
	lda	((_currentStatus + 0x001c) + 1)
	txa
	rts
;comms.c:780: case 78:  return (uint8_t)(currentStatus.PW2 & 0xFF);
00128$:
	lda	((_currentStatus + 0x001e)+1)
	rts
;comms.c:781: case 79:  return (uint8_t)((currentStatus.PW2 >> 8) & 0xFF);
00129$:
	ldx	(_currentStatus + 0x001e)
	lda	((_currentStatus + 0x001e) + 1)
	txa
	rts
;comms.c:782: case 80:  return (uint8_t)(currentStatus.PW3 & 0xFF);
00130$:
	lda	((_currentStatus + 0x0020)+1)
	rts
;comms.c:783: case 81:  return (uint8_t)((currentStatus.PW3 >> 8) & 0xFF);
00131$:
	ldx	(_currentStatus + 0x0020)
	lda	((_currentStatus + 0x0020) + 1)
	txa
	rts
;comms.c:784: case 92:  return (uint8_t)(currentStatus.CLIdleTarget / 10U);
00132$:
	lda	(_currentStatus + 0x002f)
	psha
	pulh
	ldx	((_currentStatus + 0x002f) + 1)
	lda	#0x0a
	psha
	clra
	psha
	txa
	pshh
	pulx
	jsr	__divuint
	ais	#2
	rts
;comms.c:785: case 102: return currentStatus.VE;
00133$:
	lda	(_currentStatus + 0x0022)
	rts
;comms.c:786: default:  return 0;
00134$:
	clra
;comms.c:787: }
;comms.c:788: }
	rts
	.area CSEG    (CODE)
	.area CONST   (CODE)
_crc32_table:
	.byte #0x00, #0x00, #0x00, #0x00	; 0
	.byte #0x77, #0x07, #0x30, #0x96	; 1996959894
	.byte #0xee, #0x0e, #0x61, #0x2c	; 3993919788
	.byte #0x99, #0x09, #0x51, #0xba	; 2567524794
	.byte #0x07, #0x6d, #0xc4, #0x19	; 124634137
	.byte #0x70, #0x6a, #0xf4, #0x8f	; 1886057615
	.byte #0xe9, #0x63, #0xa5, #0x35	; 3915621685
	.byte #0x9e, #0x64, #0x95, #0xa3	; 2657392035
	.byte #0x0e, #0xdb, #0x88, #0x32	; 249268274
	.byte #0x79, #0xdc, #0xb8, #0xa4	; 2044508324
	.byte #0xe0, #0xd5, #0xe9, #0x1e	; 3772115230
	.byte #0x97, #0xd2, #0xd9, #0x88	; 2547177864
	.byte #0x09, #0xb6, #0x4c, #0x2b	; 162941995
	.byte #0x7e, #0xb1, #0x7c, #0xbd	; 2125561021
	.byte #0xe7, #0xb8, #0x2d, #0x07	; 3887607047
	.byte #0x90, #0xbf, #0x1d, #0x91	; 2428444049
	.byte #0x1d, #0xb7, #0x10, #0x64	; 498536548
	.byte #0x6a, #0xb0, #0x20, #0xf2	; 1789927666
	.byte #0xf3, #0xb9, #0x71, #0x48	; 4089016648
	.byte #0x84, #0xbe, #0x41, #0xde	; 2227061214
	.byte #0x1a, #0xda, #0xd4, #0x7d	; 450548861
	.byte #0x6d, #0xdd, #0xe4, #0xeb	; 1843258603
	.byte #0xf4, #0xd4, #0xb5, #0x51	; 4107580753
	.byte #0x83, #0xd3, #0x85, #0xc7	; 2211677639
	.byte #0x13, #0x6c, #0x98, #0x56	; 325883990
	.byte #0x64, #0x6b, #0xa8, #0xc0	; 1684777152
	.byte #0xfd, #0x62, #0xf9, #0x7a	; 4251122042
	.byte #0x8a, #0x65, #0xc9, #0xec	; 2321926636
	.byte #0x14, #0x01, #0x5c, #0x4f	; 335633487
	.byte #0x63, #0x06, #0x6c, #0xd9	; 1661365465
	.byte #0xfa, #0x0f, #0x3d, #0x63	; 4195302755
	.byte #0x8d, #0x08, #0x0d, #0xf5	; 2366115317
	.byte #0x3b, #0x6e, #0x20, #0xc8	; 997073096
	.byte #0x4c, #0x69, #0x10, #0x5e	; 1281953886
	.byte #0xd5, #0x60, #0x41, #0xe4	; 3579855332
	.byte #0xa2, #0x67, #0x71, #0x72	; 2724688242
	.byte #0x3c, #0x03, #0xe4, #0xd1	; 1006888145
	.byte #0x4b, #0x04, #0xd4, #0x47	; 1258607687
	.byte #0xd2, #0x0d, #0x85, #0xfd	; 3524101629
	.byte #0xa5, #0x0a, #0xb5, #0x6b	; 2768942443
	.byte #0x35, #0xb5, #0xa8, #0xfa	; 901097722
	.byte #0x42, #0xb2, #0x98, #0x6c	; 1119000684
	.byte #0xdb, #0xbb, #0xc9, #0xd6	; 3686517206
	.byte #0xac, #0xbc, #0xf9, #0x40	; 2898065728
	.byte #0x32, #0xd8, #0x6c, #0xe3	; 853044451
	.byte #0x45, #0xdf, #0x5c, #0x75	; 1172266101
	.byte #0xdc, #0xd6, #0x0d, #0xcf	; 3705015759
	.byte #0xab, #0xd1, #0x3d, #0x59	; 2882616665
	.byte #0x26, #0xd9, #0x30, #0xac	; 651767980
	.byte #0x51, #0xde, #0x00, #0x3a	; 1373503546
	.byte #0xc8, #0xd7, #0x51, #0x80	; 3369554304
	.byte #0xbf, #0xd0, #0x61, #0x16	; 3218104598
	.byte #0x21, #0xb4, #0xf4, #0xb5	; 565507253
	.byte #0x56, #0xb3, #0xc4, #0x23	; 1454621731
	.byte #0xcf, #0xba, #0x95, #0x99	; 3485111705
	.byte #0xb8, #0xbd, #0xa5, #0x0f	; 3099436303
	.byte #0x28, #0x02, #0xb8, #0x9e	; 671266974
	.byte #0x5f, #0x05, #0x88, #0x08	; 1594198024
	.byte #0xc6, #0x0c, #0xd9, #0xb2	; 3322730930
	.byte #0xb1, #0x0b, #0xe9, #0x24	; 2970347812
	.byte #0x2f, #0x6f, #0x7c, #0x87	; 795835527
	.byte #0x58, #0x68, #0x4c, #0x11	; 1483230225
	.byte #0xc1, #0x61, #0x1d, #0xab	; 3244367275
	.byte #0xb6, #0x66, #0x2d, #0x3d	; 3060149565
	.byte #0x76, #0xdc, #0x41, #0x90	; 1994146192
	.byte #0x01, #0xdb, #0x71, #0x06	; 31158534
	.byte #0x98, #0xd2, #0x20, #0xbc	; 2563907772
	.byte #0xef, #0xd5, #0x10, #0x2a	; 4023717930
	.byte #0x71, #0xb1, #0x85, #0x89	; 1907459465
	.byte #0x06, #0xb6, #0xb5, #0x1f	; 112637215
	.byte #0x9f, #0xbf, #0xe4, #0xa5	; 2680153253
	.byte #0xe8, #0xb8, #0xd4, #0x33	; 3904427059
	.byte #0x78, #0x07, #0xc9, #0xa2	; 2013776290
	.byte #0x0f, #0x00, #0xf9, #0x34	; 251722036
	.byte #0x96, #0x09, #0xa8, #0x8e	; 2517215374
	.byte #0xe1, #0x0e, #0x98, #0x18	; 3775830040
	.byte #0x7f, #0x6a, #0x0d, #0xbb	; 2137656763
	.byte #0x08, #0x6d, #0x3d, #0x2d	; 141376813
	.byte #0x91, #0x64, #0x6c, #0x97	; 2439277719
	.byte #0xe6, #0x63, #0x5c, #0x01	; 3865271297
	.byte #0x6b, #0x6b, #0x51, #0xf4	; 1802195444
	.byte #0x1c, #0x6c, #0x61, #0x62	; 476864866
	.byte #0x85, #0x65, #0x30, #0xd8	; 2238001368
	.byte #0xf2, #0x62, #0x00, #0x4e	; 4066508878
	.byte #0x6c, #0x06, #0x95, #0xed	; 1812370925
	.byte #0x1b, #0x01, #0xa5, #0x7b	; 453092731
	.byte #0x82, #0x08, #0xf4, #0xc1	; 2181625025
	.byte #0xf5, #0x0f, #0xc4, #0x57	; 4111451223
	.byte #0x65, #0xb0, #0xd9, #0xc6	; 1706088902
	.byte #0x12, #0xb7, #0xe9, #0x50	; 314042704
	.byte #0x8b, #0xbe, #0xb8, #0xea	; 2344532202
	.byte #0xfc, #0xb9, #0x88, #0x7c	; 4240017532
	.byte #0x62, #0xdd, #0x1d, #0xdf	; 1658658271
	.byte #0x15, #0xda, #0x2d, #0x49	; 366619977
	.byte #0x8c, #0xd3, #0x7c, #0xf3	; 2362670323
	.byte #0xfb, #0xd4, #0x4c, #0x65	; 4224994405
	.byte #0x4d, #0xb2, #0x61, #0x58	; 1303535960
	.byte #0x3a, #0xb5, #0x51, #0xce	; 984961486
	.byte #0xa3, #0xbc, #0x00, #0x74	; 2747007092
	.byte #0xd4, #0xbb, #0x30, #0xe2	; 3569037538
	.byte #0x4a, #0xdf, #0xa5, #0x41	; 1256170817
	.byte #0x3d, #0xd8, #0x95, #0xd7	; 1037604311
	.byte #0xa4, #0xd1, #0xc4, #0x6d	; 2765210733
	.byte #0xd3, #0xd6, #0xf4, #0xfb	; 3554079995
	.byte #0x43, #0x69, #0xe9, #0x6a	; 1131014506
	.byte #0x34, #0x6e, #0xd9, #0xfc	; 879679996
	.byte #0xad, #0x67, #0x88, #0x46	; 2909243462
	.byte #0xda, #0x60, #0xb8, #0xd0	; 3663771856
	.byte #0x44, #0x04, #0x2d, #0x73	; 1141124467
	.byte #0x33, #0x03, #0x1d, #0xe5	; 855842277
	.byte #0xaa, #0x0a, #0x4c, #0x5f	; 2852801631
	.byte #0xdd, #0x0d, #0x7c, #0xc9	; 3708648649
	.byte #0x50, #0x05, #0x71, #0x3c	; 1342533948
	.byte #0x27, #0x02, #0x41, #0xaa	; 654459306
	.byte #0xbe, #0x0b, #0x10, #0x10	; 3188396048
	.byte #0xc9, #0x0c, #0x20, #0x86	; 3373015174
	.byte #0x57, #0x68, #0xb5, #0x25	; 1466479909
	.byte #0x20, #0x6f, #0x85, #0xb3	; 544179635
	.byte #0xb9, #0x66, #0xd4, #0x09	; 3110523913
	.byte #0xce, #0x61, #0xe4, #0x9f	; 3462522015
	.byte #0x5e, #0xde, #0xf9, #0x0e	; 1591671054
	.byte #0x29, #0xd9, #0xc9, #0x98	; 702138776
	.byte #0xb0, #0xd0, #0x98, #0x22	; 2966460450
	.byte #0xc7, #0xd7, #0xa8, #0xb4	; 3352799412
	.byte #0x59, #0xb3, #0x3d, #0x17	; 1504918807
	.byte #0x2e, #0xb4, #0x0d, #0x81	; 783551873
	.byte #0xb7, #0xbd, #0x5c, #0x3b	; 3082640443
	.byte #0xc0, #0xba, #0x6c, #0xad	; 3233442989
	.byte #0xed, #0xb8, #0x83, #0x20	; 3988292384
	.byte #0x9a, #0xbf, #0xb3, #0xb6	; 2596254646
	.byte #0x03, #0xb6, #0xe2, #0x0c	; 62317068
	.byte #0x74, #0xb1, #0xd2, #0x9a	; 1957810842
	.byte #0xea, #0xd5, #0x47, #0x39	; 3939845945
	.byte #0x9d, #0xd2, #0x77, #0xaf	; 2647816111
	.byte #0x04, #0xdb, #0x26, #0x15	; 81470997
	.byte #0x73, #0xdc, #0x16, #0x83	; 1943803523
	.byte #0xe3, #0x63, #0x0b, #0x12	; 3814918930
	.byte #0x94, #0x64, #0x3b, #0x84	; 2489596804
	.byte #0x0d, #0x6d, #0x6a, #0x3e	; 225274430
	.byte #0x7a, #0x6a, #0x5a, #0xa8	; 2053790376
	.byte #0xe4, #0x0e, #0xcf, #0x0b	; 3826175755
	.byte #0x93, #0x09, #0xff, #0x9d	; 2466906013
	.byte #0x0a, #0x00, #0xae, #0x27	; 167816743
	.byte #0x7d, #0x07, #0x9e, #0xb1	; 2097651377
	.byte #0xf0, #0x0f, #0x93, #0x44	; 4027552580
	.byte #0x87, #0x08, #0xa3, #0xd2	; 2265490386
	.byte #0x1e, #0x01, #0xf2, #0x68	; 503444072
	.byte #0x69, #0x06, #0xc2, #0xfe	; 1762050814
	.byte #0xf7, #0x62, #0x57, #0x5d	; 4150417245
	.byte #0x80, #0x65, #0x67, #0xcb	; 2154129355
	.byte #0x19, #0x6c, #0x36, #0x71	; 426522225
	.byte #0x6e, #0x6b, #0x06, #0xe7	; 1852507879
	.byte #0xfe, #0xd4, #0x1b, #0x76	; 4275313526
	.byte #0x89, #0xd3, #0x2b, #0xe0	; 2312317920
	.byte #0x10, #0xda, #0x7a, #0x5a	; 282753626
	.byte #0x67, #0xdd, #0x4a, #0xcc	; 1742555852
	.byte #0xf9, #0xb9, #0xdf, #0x6f	; 4189708143
	.byte #0x8e, #0xbe, #0xef, #0xf9	; 2394877945
	.byte #0x17, #0xb7, #0xbe, #0x43	; 397917763
	.byte #0x60, #0xb0, #0x8e, #0xd5	; 1622183637
	.byte #0xd6, #0xd6, #0xa3, #0xe8	; 3604390888
	.byte #0xa1, #0xd1, #0x93, #0x7e	; 2714866558
	.byte #0x38, #0xd8, #0xc2, #0xc4	; 953729732
	.byte #0x4f, #0xdf, #0xf2, #0x52	; 1340076626
	.byte #0xd1, #0xbb, #0x67, #0xf1	; 3518719985
	.byte #0xa6, #0xbc, #0x57, #0x67	; 2797360999
	.byte #0x3f, #0xb5, #0x06, #0xdd	; 1068828381
	.byte #0x48, #0xb2, #0x36, #0x4b	; 1219638859
	.byte #0xd8, #0x0d, #0x2b, #0xda	; 3624741850
	.byte #0xaf, #0x0a, #0x1b, #0x4c	; 2936675148
	.byte #0x36, #0x03, #0x4a, #0xf6	; 906185462
	.byte #0x41, #0x04, #0x7a, #0x60	; 1090812512
	.byte #0xdf, #0x60, #0xef, #0xc3	; 3747672003
	.byte #0xa8, #0x67, #0xdf, #0x55	; 2825379669
	.byte #0x31, #0x6e, #0x8e, #0xef	; 829329135
	.byte #0x46, #0x69, #0xbe, #0x79	; 1181335161
	.byte #0xcb, #0x61, #0xb3, #0x8c	; 3412177804
	.byte #0xbc, #0x66, #0x83, #0x1a	; 3160834842
	.byte #0x25, #0x6f, #0xd2, #0xa0	; 628085408
	.byte #0x52, #0x68, #0xe2, #0x36	; 1382605366
	.byte #0xcc, #0x0c, #0x77, #0x95	; 3423369109
	.byte #0xbb, #0x0b, #0x47, #0x03	; 3138078467
	.byte #0x22, #0x02, #0x16, #0xb9	; 570562233
	.byte #0x55, #0x05, #0x26, #0x2f	; 1426400815
	.byte #0xc5, #0xba, #0x3b, #0xbe	; 3317316542
	.byte #0xb2, #0xbd, #0x0b, #0x28	; 2998733608
	.byte #0x2b, #0xb4, #0x5a, #0x92	; 733239954
	.byte #0x5c, #0xb3, #0x6a, #0x04	; 1555261956
	.byte #0xc2, #0xd7, #0xff, #0xa7	; 3268935591
	.byte #0xb5, #0xd0, #0xcf, #0x31	; 3050360625
	.byte #0x2c, #0xd9, #0x9e, #0x8b	; 752459403
	.byte #0x5b, #0xde, #0xae, #0x1d	; 1541320221
	.byte #0x9b, #0x64, #0xc2, #0xb0	; 2607071920
	.byte #0xec, #0x63, #0xf2, #0x26	; 3965973030
	.byte #0x75, #0x6a, #0xa3, #0x9c	; 1969922972
	.byte #0x02, #0x6d, #0x93, #0x0a	; 40735498
	.byte #0x9c, #0x09, #0x06, #0xa9	; 2617837225
	.byte #0xeb, #0x0e, #0x36, #0x3f	; 3943577151
	.byte #0x72, #0x07, #0x67, #0x85	; 1913087877
	.byte #0x05, #0x00, #0x57, #0x13	; 83908371
	.byte #0x95, #0xbf, #0x4a, #0x82	; 2512341634
	.byte #0xe2, #0xb8, #0x7a, #0x14	; 3803740692
	.byte #0x7b, #0xb1, #0x2b, #0xae	; 2075208622
	.byte #0x0c, #0xb6, #0x1b, #0x38	; 213261112
	.byte #0x92, #0xd2, #0x8e, #0x9b	; 2463272603
	.byte #0xe5, #0xd5, #0xbe, #0x0d	; 3855990285
	.byte #0x7c, #0xdc, #0xef, #0xb7	; 2094854071
	.byte #0x0b, #0xdb, #0xdf, #0x21	; 198958881
	.byte #0x86, #0xd3, #0xd2, #0xd4	; 2262029012
	.byte #0xf1, #0xd4, #0xe2, #0x42	; 4057260610
	.byte #0x68, #0xdd, #0xb3, #0xf8	; 1759359992
	.byte #0x1f, #0xda, #0x83, #0x6e	; 534414190
	.byte #0x81, #0xbe, #0x16, #0xcd	; 2176718541
	.byte #0xf6, #0xb9, #0x26, #0x5b	; 4139329115
	.byte #0x6f, #0xb0, #0x77, #0xe1	; 1873836001
	.byte #0x18, #0xb7, #0x47, #0x77	; 414664567
	.byte #0x88, #0x08, #0x5a, #0xe6	; 2282248934
	.byte #0xff, #0x0f, #0x6a, #0x70	; 4279200368
	.byte #0x66, #0x06, #0x3b, #0xca	; 1711684554
	.byte #0x11, #0x01, #0x0b, #0x5c	; 285281116
	.byte #0x8f, #0x65, #0x9e, #0xff	; 2405801727
	.byte #0xf8, #0x62, #0xae, #0x69	; 4167216745
	.byte #0x61, #0x6b, #0xff, #0xd3	; 1634467795
	.byte #0x16, #0x6c, #0xcf, #0x45	; 376229701
	.byte #0xa0, #0x0a, #0xe2, #0x78	; 2685067896
	.byte #0xd7, #0x0d, #0xd2, #0xee	; 3608007406
	.byte #0x4e, #0x04, #0x83, #0x54	; 1308918612
	.byte #0x39, #0x03, #0xb3, #0xc2	; 956543938
	.byte #0xa7, #0x67, #0x26, #0x61	; 2808555105
	.byte #0xd0, #0x60, #0x16, #0xf7	; 3495958263
	.byte #0x49, #0x69, #0x47, #0x4d	; 1231636301
	.byte #0x3e, #0x6e, #0x77, #0xdb	; 1047427035
	.byte #0xae, #0xd1, #0x6a, #0x4a	; 2932959818
	.byte #0xd9, #0xd6, #0x5a, #0xdc	; 3654703836
	.byte #0x40, #0xdf, #0x0b, #0x66	; 1088359270
	.byte #0x37, #0xd8, #0x3b, #0xf0	; 936918000
	.byte #0xa9, #0xbc, #0xae, #0x53	; 2847714899
	.byte #0xde, #0xbb, #0x9e, #0xc5	; 3736837829
	.byte #0x47, #0xb2, #0xcf, #0x7f	; 1202900863
	.byte #0x30, #0xb5, #0xff, #0xe9	; 817233897
	.byte #0xbd, #0xbd, #0xf2, #0x1c	; 3183342108
	.byte #0xca, #0xba, #0xc2, #0x8a	; 3401237130
	.byte #0x53, #0xb3, #0x93, #0x30	; 1404277552
	.byte #0x24, #0xb4, #0xa3, #0xa6	; 615818150
	.byte #0xba, #0xd0, #0x36, #0x05	; 3134207493
	.byte #0xcd, #0xd7, #0x06, #0x93	; 3453421203
	.byte #0x54, #0xde, #0x57, #0x29	; 1423857449
	.byte #0x23, #0xd9, #0x67, #0xbf	; 601450431
	.byte #0xb3, #0x66, #0x7a, #0x2e	; 3009837614
	.byte #0xc4, #0x61, #0x4a, #0xb8	; 3294710456
	.byte #0x5d, #0x68, #0x1b, #0x02	; 1567103746
	.byte #0x2a, #0x6f, #0x2b, #0x94	; 711928724
	.byte #0xb4, #0x0b, #0xbe, #0x37	; 3020668471
	.byte #0xc3, #0x0c, #0x8e, #0xa1	; 3272380065
	.byte #0x5a, #0x05, #0xdf, #0x1b	; 1510334235
	.byte #0x2d, #0x02, #0xef, #0x8d	; 755167117
_pageSize:
	.dw #0x0000
	.dw #0x001e
	.dw #0x00a8
	.dw #0x00a8
	.dw #0x0020
	.dw #0x0120
	.dw #0x0080
	.dw #0x00f0
	.dw #0x0180
	.dw #0x00c0
	.dw #0x00c0
	.dw #0x0120
	.dw #0x00c0
	.dw #0x0080
	.dw #0x0120
	.dw #0x0100
	.area CONST   (CODE)
___str_0:
	.ascii "speeduino 202402"
	.db 0x00
	.area CSEG    (CODE)
	.area CONST   (CODE)
___str_1:
	.db 0x0d
	.db 0x0a
	.db 0x00
	.area CSEG    (CODE)
	.area CONST   (CODE)
___str_2:
	.ascii "Speeduino 202402"
	.db 0x00
	.area CSEG    (CODE)
	.area CONST   (CODE)
___str_3:
	.ascii "002"
	.db 0x00
	.area CSEG    (CODE)
	.area CONST   (CODE)
___str_4:
	.ascii "speeduino 202207"
	.db 0x00
	.area CSEG    (CODE)
	.area CONST   (CODE)
___str_5:
	.ascii "Speeduino 2024.02.4"
	.db 0x00
	.area CSEG    (CODE)
	.area XINIT   (CODE)
__xinit__serialBytesReceived:
	.db #0x00	; 0
__xinit__modernProtocol:
	.db #0x00	;  0
__xinit__expectedLength:
	.db #0x00	; 0
	.area CABS    (ABS,CODE)
