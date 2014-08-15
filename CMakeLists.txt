cmake_minimum_required (VERSION 2.4)

project (BENARYOS C ASM)

file(GLOB_RECURSE files ${BENARYOS_SOURCE_DIR}/src/*.c
	${BENARYOS_SOURCE_DIR}/src/start.S) 

include_directories(${BENARYOS_SOURCE_DIR}/src/) 

set(CMAKE_ASM_FLAGS "-m32")
set(CMAKE_CXX_FLAGS "-m32 -Wall -g -fno-stack-protector -nostdinc -std=gnu89")
set(CMAKE_EXE_LINKER_FLAGS "-march=elf_i386 -Ttext=0x100000 -T ${BENARYOS_SOURCE_DIR}/src/linker.ld")

add_executable ( kernel ${files} )

