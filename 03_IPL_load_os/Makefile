AS	:= nasm
QEMU	:= qemu-system-x86_64
IMG	:= floppy.img

ipl:	ipl.asm
	nasm ipl.asm -o ipl.bin -l ipl.list

sys:	os_dev.asm
	nasm os_dev.asm -o os_dev.sys

image:	ipl sys
	dd if=/dev/zero of=floppy.img bs=512 count=2880
	dd if=ipl.bin of=floppy.img seek=0 count=1 conv=notrunc
	dd if=os_dev.sys of=floppy.img seek=33 bs=512 conv=notrunc

clean: 
	$(RM) *.bin *.list *.img *.sys

qemu: clean image
	$(QEMU) -fda floppy.img
.PHONY:
	clean
