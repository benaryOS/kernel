cmake_minimum_required (VERSION 2.4)

project (BENARYOS)

file(GLOB_RECURSE files ${BENARYOS_SOURCE_DIR}/src/*.c) 
file(GLOB_RECURSE files ${BENARYOS_SOURCE_DIR}/src/*.s) 

set(CMAKE_EXE_LINKER_FLAGS "ld -T ${BENARYOS_SOURCE_DIR}/src/linker.ld")
set(CMAKE_CXX_FLAGS "-m32 -Wall -g -fno-stack-protector -nostdinc -std=gnu89")

add_executable ( kernel ${files} )

