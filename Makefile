.PHONE = test

CC = gcc
CFLAGS = -Wall -Wextra -fPIC -g

3S_LIBS = src/btree.c src/core.c src/llist.c
3S_OBJS = btree.o core.o llist.o

test: $(3S_OBJS) test.o
	$(CC) $(CFLAGS) $^ -o $@

test.o: test.c
	$(CC) $(CFLAGS) $^ -c

$(3S_OBJS): $(3S_LIBS)
	$(CC) $(CFLAGS) $^ -c

clean:
	rm test *.o
