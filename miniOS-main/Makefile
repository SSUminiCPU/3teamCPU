# Compiler and Compiler Flags
CC = gcc
GTK_FLAGS = $(shell pkg-config --cflags gtk+-3.0)
CFLAGS = -Wall -g -Iinclude $(GTK_FLAGS)

# Linker flags
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0)
LDFLAGS = -lreadline -lpthread $(GTK_LIBS)

# The build target executable:
TARGET = minios

# Source and Object files
SRCS = kernel/kernel.c kernel/system.c kernel/20211089/fork.c kernel/20211089/ipc.c kernel/20211089/rr.c
OBJDIR = obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Include directory
INCLUDE_DIR = include

# Phony targets
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up:
clean:
	rm -f $(OBJS) $(TARGET)
