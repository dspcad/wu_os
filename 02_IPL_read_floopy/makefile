run: ipl.nas
	nasm ipl.nas -o ipl.bin -l ipl.list
	dd if=/dev/zero of=floppy.img bs=512 count=2880
	dd if=ipl.bin of=floppy.img seek=0 count=1 conv=notrunc
	qemu-system-x86_64 -fda floppy.img

clean: 
	$(RM) *.bin *.list *.img
