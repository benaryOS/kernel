include ../common.mk

ASFLAGS := -felf32

#FIXME: clean up
CARGOBUILD := release
CARGOTARGET := i686-unknown-linux-gnu
CARGOFLAGS := --$(CARGOBUILD) --target=$(CARGOTARGET)

CFLAGS := -m32 -std=c11 -ffreestanding -O2 -Wall -Wextra -nostdlib

LDFLAGS := -m32 -m elf_i386 -T linker.ld -nostdlib


SRCS = $(shell find asm -maxdepth 1 -type f -regextype posix-extended -regex '.+\.(c|asm)$$')
CRATES = $(shell find . -type d -exec test -f "{}/Cargo.toml" ";" -printf "%h/%f/target/$(CARGOTARGET)/$(CARGOBUILD)/lib%f.rlib")
OBJS = $(addsuffix .o,$(basename $(SRCS)))
OBJS += $(CRATES)


default: kernel

kernel: $(OBJS)
	@printf "[%6s] %s\n" "LD" "$@" 
	@$(LD) $(LDFLAGS) -o $@ $^

%.o: %.asm
	@printf "[%6s] %s\n" "ASM" "$@" 
	@$(AS) $(ASFLAGS) -o $@ $^

%.o: %.c
	@printf "[%6s] %s\n" "CC" "$@" 
	@$(CC) $(CFLAGS) -c -o $@ $^

#TODO: add dependencies
%.rlib:
	@printf "[%6s] %s\n" "CARGO" "$@" 
	@cd $(shell dirname $@) && $(CARGO) build --quiet $(CARGOFLAGS)

clean:
	rm -f $(OBJS)

clean-%.rlib: %
	@printf "[%6s] %s\n" "CLEAN" "$^" 
	@cd $^ && cargo clean

.PHONY: clean

