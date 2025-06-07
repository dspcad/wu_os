ipl: ipl.asm
	nasm ipl.asm -o ipl.bin -l ipl.list
	dd if=/dev/zero of=floppy.img bs=512 count=2880
	dd if=ipl.bin of=floppy.img seek=0 count=1 conv=notrunc

clean: 
	$(RM) *.bin *.list *.img *.sys

sys:	os_dev.asm
	nasm os_dev.asm -o os_dev.sys
install: os_dev.sys floppy.img
	dd if=os_dev.sys of=floppy.img seek=33 bs=512 conv=notrunc

run:
	make ipl
	make sys
	make install
	qemu-system-x86_64 -fda floppy.img
