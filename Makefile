CC = gcc
CFLAGS = -Wall -Wextra -g -I./include -I/usr/include
LIBS = -lncurses
SRC = src/main.c src/cpu.c src/memory.c src/disk.c src/process.c src/network.c src/display.c
OBJ = $(SRC:.c=.o)
TARGET = sysmon

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

setup:
	@chmod +x setup.sh
	@./setup.sh

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all setup clean	
