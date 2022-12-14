.PHONY : examples

CC = gcc
CFLAGS = -Wall -fPIC -g

3S_LIBS = src/core.c src/llist.c src/stack.c src/queue.c
3S_OBJS = core.o llist.o stack.o queue.o

EXAMPLES_BIN = example01 example02 example03

examples: $(EXAMPLES_BIN)

example01.o: examples/example01.c
	$(CC) $(CFLAGS) $^ -c

example01: $(3S_OBJS) example01.o
	$(CC) $(CFLAGS) $^ -o $@
	@echo Execute using ./$@

example02.o: examples/example02.c
	$(CC) $(CFLAGS) $^ -c

example02: $(3S_OBJS) example02.o
	$(CC) $(CFLAGS) $^ -o $@
	@echo Execute using ./$@

example03.o: examples/example03.c
	$(CC) $(CFLAGS) $^ -c

example03: $(3S_OBJS) example03.o
	$(CC) $(CFLAGS) $^ -o $@
	@echo Execute using ./$@

$(3S_OBJS): $(3S_LIBS)
	$(CC) $(CFLAGS) $^ -c

clean:
	rm $(EXAMPLES_BIN) *.o
