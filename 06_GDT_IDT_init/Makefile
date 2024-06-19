# $@: The target name of the rule.
# $<: The first prerequisite (dependency) of the rule.
# $^: The list of all prerequisites.
# $?: The list of all prerequisites that are newer than the target.

AS 		:= nasm
CC 		:= gcc
LD 		:= ld
CFLAGS 		:= -Wall -m32 -fno-pie
QEMU 		:= qemu-system-x86_64

OBJS := ipl.bin asmhead.bin bootpack.bin func.bin hankaku.bin
SYS := os_dev.sys
IMG := os_dev.img

hankaku.bin: ../hankaku/hankaku.asm
	$(AS) -f elf $< -o $@

ipl.bin:
	$(AS) -f bin ipl.asm -o ipl.bin -l ipl.list

asmhead.bin:
	$(AS) -f elf asmhead.asm -o asmhead.bin -l asmhead.list

bootpack.bin:
	$(CC) $(CFLAGS) -c bootpack.c -o bootpack.bin

func.bin:
	$(AS) -f elf func.asm -o func.bin -l func.list

os_dev.sys: asmhead.bin bootpack.bin func.bin hankaku.bin
	$(LD) -m elf_i386 --oformat binary asmhead.bin bootpack.bin func.bin hankaku.bin -o os_dev.sys -T os_dev.ld

image: ipl.bin os_dev.sys
	dd if=/dev/zero of=$(IMG) bs=512 count=2880
	dd if=ipl.bin of=$(IMG) bs=512 count=1 conv=notrunc
	dd if=os_dev.sys of=$(IMG) seek=33 bs=512 conv=notrunc
	
all: ${OBJS} os_dev.sys image

clean:
	rm -rf *.bin
	rm -rf *.sys
	rm -rf *.o
	rm -rf *.list
	rm -rf $(IMG)

qemu: clean all
	$(QEMU) -fda $(IMG) 

.PHONY:
	all
