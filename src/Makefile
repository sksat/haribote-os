TOLSET	= ../tolset/
Z_TOOLS	= $(TOLSET)z_tools/
INCPATH = $(Z_TOOLS)haribote/

NASK	= $(Z_TOOLS)nask
EDIMG	= $(Z_TOOLS)edimg
CC1	= $(Z_TOOLS)gocc1 -I$(INCPATH) -Os -Wall -quiet
GAS2NASK= $(Z_TOOLS)gas2nask -a
OBJ2BIM = $(Z_TOOLS)obj2bim
MAKEFONT= $(Z_TOOLS)makefont
BIN2OBJ = $(Z_TOOLS)bin2obj
RULEFILE= haribote.rul
BIM2HRB	= $(Z_TOOLS)bim2hrb
HARITOL	= $(Z_TOOLS)haritol

# デフォルト動作

default :
	make img

# ファイル生成規則

ipl10.bin : ipl10.nas Makefile
	$(NASK) ipl10.nas ipl10.bin ipl10.lst

asmhead.bin : asmhead.nas Makefile
	$(NASK) asmhead.nas asmhead.bin asmhead.lst

bootpack.gas : bootpack.c Makefile
	$(CC1) -o bootpack.gas bootpack.c

bootpack.nas : bootpack.gas Makefile
	$(GAS2NASK) bootpack.gas bootpack.nas

bootpack.obj : bootpack.nas Makefile
	$(NASK) bootpack.nas bootpack.obj bootpack.lst

naskfunc.obj : naskfunc.nas Makefile
	$(NASK) naskfunc.nas naskfunc.obj naskfunc.lst

hankaku.bin : hankaku.txt Makefile
	$(MAKEFONT) hankaku.txt hankaku.bin

hankaku.obj : hankaku.bin Makefile
	$(BIN2OBJ) hankaku.bin hankaku.obj _hankaku

bootpack.bim : bootpack.obj naskfunc.obj hankaku.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map \
		bootpack.obj \
		naskfunc.obj \
		hankaku.obj
# 3MB+64KB=3136KB

bootpack.hrb : bootpack.bim Makefile
	$(BIM2HRB) bootpack.bim bootpack.hrb 0

haribote.sys : asmhead.bin bootpack.hrb Makefile
	$(HARITOL) concat haribote.sys asmhead.bin bootpack.hrb

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
	rm *.bin
	rm *.lst
	rm *.gas
	rm *.obj
	rm bootpack.hrb
	rm bootpack.map
	rm bootpack.bim
	rm bootpack.nas
	rm haribote.sys

src_only :
	make clean
	rm haribote.img
