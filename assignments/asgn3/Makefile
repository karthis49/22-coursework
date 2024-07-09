CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm

all: sorting

sorting: sorting.o insert.o heap.o quick.o stats.o shell.o
	$(CC) -o sorting sorting.o insert.o heap.o quick.o stats.o shell.o $(LFLAGS)

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -f sorting sorting.o insert.o heap.o quick.o stats.o shell.o

format:
	clang-format -i -style=file *.[ch]
   
