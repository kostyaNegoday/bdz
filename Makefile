CC ?= cc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all run clean
all: game21

game21: $(OBJECTS)
	$(CC) $^ -o $@

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $< -o $@

run: game21
	./game21

clean:
	rm -f *.o game21
