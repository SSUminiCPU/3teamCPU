# Compiler and Compiler Flags
CC=gcc
CFLAGS=-Wall -g -Iinclude

# Linker flags
LDFLAGS=-lreadline

# The build target executable:
TARGET=minios
FORK_CHILD_PROGRAM=kernel/20192490/print_os_name

# Source -> Object files (자동 변환됨)
# 의존성 있는 Object file만 명시
OBJS=kernel/kernel.o kernel/system.o kernel/20192490/mini_fork.o

#Include directory
INCLUDE_DIR=include

all: $(TARGET) $(FORK_CHILD_PROGRAM)

$(TARGET): $(OBJS)
	ld -o $(TARGET) $^ -lc -dynamic-linker=/lib64/ld-linux-x86-64.so.2 /usr/lib/x86_64-linux-gnu/crt1.o \
        $(LDFLAGS)

$(FORK_CHILD_PROGRAM): kernel/20192490/print_os_name.o
	ld -o $@ $^ -lc -dynamic-linker=/lib64/ld-linux-x86-64.so.2 /usr/lib/x86_64-linux-gnu/crt1.o \
        $(LDFLAGS)

# Clean up:
clean:

