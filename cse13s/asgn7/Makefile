CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
OBJECTS = bv.o bf.o bst.o ht.o node.o speck.o parser.o

all: banhammer

banhammer: $(OBJECTS) banhammer.o
		$(CC) $(CFLAGS) -o banhammer $(OBJECTS) banhammer.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f banhammer $(OBJECTS) banhammer.o 

format:
	clang-format -i -style=file *.[ch]

