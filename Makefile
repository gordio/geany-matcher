CFILES := $(wildcard *.c)
OBJECTS = $(CFILES:.c=.o)

PCFLAGS = `pkg-config --cflags geany` -fPIC -std=c99 #-Wall -Wextra -pedantic
PLDFLAGS = `pkg-config --libs geany` -fPIC


.SUFFIXES: .c .h .o .a
.PHONY: all clean install uninstall

all: $(OBJECTS)
	@echo -e "\033[1;32m LINK\033[0m" matcher.so
	@$(CC) $(PLDFLAGS) $(LDFLAGS) $(OBJECTS) $(LIBS) -o "matcher.so" -shared

%.o: %.c
	@echo -e "\033[1m   CC\033[0m" $< "\t »" $@
	@$(CC) $(PCFLAGS) $(CFLAGS) $(OFLAGS) -c $< -o $@

clean: $(OBJECTS)
	rm $(OBJECTS) matcher.so

install: all
	cp matcher.so /usr/lib/geany/

uninstall: all
	rm /usr/lib/geany/matcher.so
