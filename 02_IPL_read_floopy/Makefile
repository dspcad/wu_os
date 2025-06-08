AS	:= nasm
QEMU	:= qemu-system-x86_64
IMG	:= floppy.img

ipl:	ipl.asm
	$(AS) ipl.asm -o ipl.bin -l ipl.list

image:	ipl
	dd if=/dev/zero of=$(IMG) bs=512 count=2880
	dd if=ipl.bin of=$(IMG) seek=0 count=1 conv=notrunc

clean: 
	$(RM) -rf *.bin *.list *.img

qemu:	clean image
	$(QEMU) -fda floppy.img
.PHONY:
	clean
