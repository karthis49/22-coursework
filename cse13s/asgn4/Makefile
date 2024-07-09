CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra

all: tsp

tsp: tsp.o graph.o stack.o path.o 
	$(CC) -o tsp tsp.o graph.o stack.o path.o 

tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -f tsp tsp.o graph.o stack.o path.o

format:
	clang-format -i -style=file *.[ch]
   

