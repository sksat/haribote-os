TOLSET	= ../tolset/
Z_TOOLS	= $(TOLSET)z_tools/
NASK	= $(Z_TOOLS)nask
EDIMG	= $(Z_TOOLS)edimg

# デフォルト動作

default :
	make img

# ファイル生成規則

ipl10.bin : ipl10.nas Makefile
	$(NASK) ipl10.nas ipl10.bin ipl10.lst

haribote.sys : haribote.nas Makefile
	$(NASK) haribote.nas haribote.sys haribote.lst

haribote.img : ipl10.bin haribote.sys Makefile
	$(EDIMG) imgin:$(Z_TOOLS)fdimg0at.tek \
		wbinimg src:ipl10.bin len:512 from:0 to:0 \
		copy from:haribote.sys to:@: \
		imgout:haribote.img

# コマンド

asm :
	make -r ipl.bin

img :
	make -r haribote.img

run :
	make img
	qemu-system-i386 -fda haribote.img

clean :
	rm ipl10.bin
	rm ipl10.lst
	rm haribote.sys
	rm haribote.lst

src_only :
	make clean
	rm haribote.img
