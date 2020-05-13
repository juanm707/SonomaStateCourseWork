CFLAGS = -Iinclude
CC = gcc
SHELL = bash

all: pipe_demo.x lobo_shell.x

# $@ is make shorthand for the thing on the left side of the colon
#   (pipe_demo.x in this case)
# $^ stands for the dependencies, everything to right of colon (the .o files)
# $< stands for the first dependency
pipe_demo.x: pipe_demo.o
	$(CC) -g -o $@ $^

lobo_shell.x: main.o parsetools.o
	$(CC) -g -o $@ $^

# $< is the first item after the colon (main.c here)
main.o: main.c include/parsetools.h include/constants.h
	$(CC) $(CFLAGS) -g -c -o $@ $<

parsetools.o: src/parsetools.c include/constants.h
	$(CC) $(CFLAGS) -g -c -o $@ $<

pipe_demo.o: example/pipe_demo.c
	$(CC) $(CFLAGS) -g -c -o $@ $<

clean:
	rm -f *.x *.o *~
	rm -rf tests/output

check: lobo_shell.x
	mkdir -p tests/output
	for t in tests/*.sh; do sh $$t; done
