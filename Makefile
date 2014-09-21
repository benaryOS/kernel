SRCS = $(shell find src -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

AS = as
CC = cc
LD = ld

ASFLAGS	= -m32
CFLAGS	= -m32 -Werror -Wall -g -fno-stack-protector -nostdinc -std=gnu89 -Isrc
LDFLAGS	= -melf_i386 -Tsrc/linker.ld

default: all

all: build/kernel

build/kernel: build $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

build:
	@mkdir -p build

%.o: %.s
	$(AS) $(ASFLAGS) -c -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJS)
