SRCPATH:=src
 
SRCS=$(shell find $(SRCPATH) -regextype posix-extended -regex '^.+\.(c|asm)$$')
OBJS=$(addprefix build,$(addsuffix .o,$(basename $(SRCS:$(SRCPATH)%=%)))) 

AS := nasm
CC := gcc
LD := ld

ASFLAGS	= -felf64 -g
CFLAGS	= -m64 -Wall -fno-stack-protector -std=gnu89 -ffreestanding -mno-mmx \
	-mno-red-zone -mcmodel=large -mno-sse -mno-sse2 -I$(SRCPATH) -g
LDFLAGS	= -Tsrc/linker.ld -nostdlib -z max-page-size=0x1000

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

