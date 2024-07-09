CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm

all: mathlib-test

mathlib-test: mathlib-test.o e.o euler.o madhava.o viete.o bbp.o newton.o
	$(CC) -o mathlib-test mathlib-test.o e.o euler.o madhava.o viete.o bbp.o newton.o $(LFLAGS)

mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -f mathlib-test mathlib-test.o e.o euler.o madhava.o viete.o bbp.o newton.o

format:
	clang-format -i -style=file *.[ch]

