BUILD_DIR = build/
_IMG      = haribote.img
IMG       = $(BUILD_DIR)$(_IMG)
EMULATOR  = qemu-system-i386
EMU_FLAGS = -fda $(IMG)

default:
	make build

build:
	make $(IMG)

$(IMG):
	make -C src
	mkdir $(BUILD_DIR)
	mv src/$(_IMG) $@

run:$(IMG)
	$(EMULATOR) $(EMU_FLAGS)

clean:
	rm -rf $(BUILD_DIR)
	make -C src clean
