CFLAGS = --std=c11 -Wall -pedantic -Isrc/ -ggdb -Wextra -Werror -DDEBUG
CC     = gcc
BUILD  = ../build

all: bmp_rotate

bmp.o: bmp.c
	$(CC) -c $(CFLAGS) $< -o $@

util.o: util.c
	$(CC) -c $(CFLAGS) $< -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $@

bmp_rotate: main.o util.o bmp.o
	$(CC) -o $(BUILD)/bmp_rotate $^

run:
	$(BUILD)/bmp_rotate $(ARGS)

clean:
	rm -f main.o util.o bmp.o $(BUILD)/bmp_rotate