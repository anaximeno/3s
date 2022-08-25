.PHONY : examples test

CC = gcc
CFLAGS = -Wall -fPIC -g 

3S_LIBS = src/core.c src/llist.c src/stack.c src/queue.c
3S_OBJS = core.o llist.o stack.o queue.o

EXAMPLES_BIN = example01 example02 example03

default: examples

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

test: test_value_t

test_value_t: $(3S_OBJS) tests/test_value_t.c
	-@$(CC) $(CFLAGS) tests/test_value_t.c -c
	-@$(CC) $(CFLAGS) $(3S_OBJS) test_value_t.o -o $@
	-@echo
	-@echo "Running tests for 'test_value_t'"
	-@echo -n "|__ Result: " && ./$@
	-@rm $@

clean:
	rm *.o $(EXAMPLES_BIN)
