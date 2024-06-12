; Disassembly of file: bootpack.o
; Tue Jun 11 19:03:25 2024
; Mode: 32 bits
; Syntax: YASM/NASM
; Instruction set: 80386


global HariMain: function


SECTION .text   align=16 execute                        ; section number 1, code

HariMain:; Function begin
        jmp     HariMain                                ; 0000 _ EB, FE
; HariMain End of function


SECTION .data   align=1 noexecute                       ; section number 2, data


SECTION .bss    align=1 noexecute                       ; section number 3, bss


