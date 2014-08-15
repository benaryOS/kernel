cmake_minimum_required (VERSION 2.4)

project (BENARYOS C ASM)

file(GLOB_RECURSE files ${BENARYOS_SOURCE_DIR}/src/*.c ${BENARYOS_SOURCE_DIR}/src/*.s) 

include_directories(${BENARYOS_SOURCE_DIR}/src/) 

set(CMAKE_EXE_LINKER_FLAGS "-T ${BENARYOS_SOURCE_DIR}/src/linker.ld")
set(CMAKE_CXX_FLAGS "-m32 -Wall -g -fno-stack-protector -nostdinc -std=gnu89")

add_executable ( kernel ${files} )

