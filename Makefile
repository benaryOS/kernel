SRCPATH:=src
 
SRCS=$(shell find $(SRCPATH) -regextype posix-extended -regex '^.+\.(c|asm)$$')
OBJS=$(addprefix build,$(addsuffix .o,$(basename $(SRCS:$(SRCPATH)%=%)))) 

AS := nasm
CC := gcc
LD := ld

ASFLAGS	= -felf64 -g
CFLAGS	= -m64 -Wall -std=gnu89 -O0 -ffreestanding -mno-red-zone -mno-mmx \
	-mno-sse -mno-sse2 -mno-sse3 -mno-3dnow -I$(SRCPATH) -g #-mcmodel=kernel
LDFLAGS	= -Tsrc/linker.ld -nostdlib

default: build/kernel

all: clean build/kernel

build/kernel: build $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

build:
	@mkdir -p build

build/%.o: $(SRCPATH)/%.asm
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $^
build/%.o: $(SRCPATH)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJS)
	rm -f build/kernel

cleanall:
	rm -rf build/

.PHONY: clean cleanall

