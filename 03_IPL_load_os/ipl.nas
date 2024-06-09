; hhwu-ipl
; TAB=4

CYLS	EQU	10

	ORG	0x7c00

	JMP	entry
	DB	0x90
	DB 	"HHWU-IPL"
	DW	512
	DB	1
	DW	1
	DB	2
	DW	224
	DW	2880
	DB	0xf0
	DW	9
	DW	18
	DW	2
	DD	0
	DD	2880               
	DW	0, 0, 0x29
	DD	0xffffffff
	DB	"hhwu-os-dev"
	DB	"FAT12   "
	RESB	18


entry:
	MOV	SP, 0x7c00
	MOV	AX, 0
	MOV	SS, AX
	MOV	DS, AX
	MOV	ES, AX

;initial value of floppy reading 
	MOV	AX, 0x0820
	MOV	ES, AX

	MOV	CH, 0		; track 0
	MOV	CL, 2		; sector 2
	MOV	DX, 0
	MOV	BX, 0

readloop:
	MOV	AH, 0x02
	MOV	AL, 1		; Number of sectors to be read 

	INT	0x13		;Reads one or more disk sectors into a buffer. 

next:
	MOV	AX, ES
	ADD	AX, 0x0020
	MOV	ES, AX

	ADD	CL, 1
	CMP	CL, 18
	JBE	readloop	;if CL<=18, jump to readloop

	MOV	CL, 1
	ADD	DH, 1		
	CMP	DH, 2
	JB 	readloop	;if DH<2, jump to readloop

	MOV	DH, 0
	ADD	CH, 1
	CMP	CH, CYLS
	JB 	readloop	;if CH<CYLS, jump to readloop

	MOV	[0x0ff0],CH	;will be used in 04_IPL_32_bits
	JMP	0xc200

	RESB	0x1fe-($-$$)
	DB	0x55, 0xaa
