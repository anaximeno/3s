.PHONY : examples test

CC = gcc
CFLAGS = -Wall -fPIC -g 

3S_LIBS = src/core.c src/llist.c src/stack.c src/queue.c
3S_OBJS = core.o llist.o stack.o queue.o

TINYTEST_PATH = tinytest
TINYTEST_OBJ = $(TINYTEST_PATH)/tinytest.o

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

$(TINYTEST_OBJ): $(TINYTEST_PATH)
	cd $(TINYTEST_PATH) && $(MAKE)

test: test_generic_values

test_generic_values: $(TINYTEST_OBJ) $(3S_OBJS) tests/test_generic_values.c
	-@$(CC) $(CFLAGS) tests/test_generic_values.c -c
	-@$(CC) $(CFLAGS) $(3S_OBJS) $(TINYTEST_OBJ) test_generic_values.o -o $@
	-@echo
	-@echo "Running tests for 'test_generic_values'"
	-@echo -n "|__ Result: " && ./$@
	-@rm $@

clean:
	-cd &(TINYTEST_PATH) && $(MAKE) clean
	-rm *.o $(EXAMPLES_BIN)
