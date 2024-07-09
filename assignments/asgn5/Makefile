CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LDFLAGS = -lm
OBJECTS = code.o huffman.o io.o node.o pq.o stack.o

all: encode decode

encode: $(OBJECTS) encode.o
		$(CC) $(CFLAGS) -o encode $(OBJECTS) encode.o
	
decode: $(OBJECTS) decode.o 
		$(CC) $(CFLAGS) -o decode $(OBJECTS) decode.o   

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f encode decode $(OBJECTS) encode.o decode.o 

format:
	clang-format -i -style=file *.[ch]

