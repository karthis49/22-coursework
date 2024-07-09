CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)
OBJECTS = rsa.o numtheory.o randstate.o

all: encrypt decrypt keygen

encrypt: encrypt.o $(OBJECTS) 
	$(CC) -o $@ $^ $(LFLAGS)

decrypt: decrypt.o $(OBJECTS) 
	$(CC) -o $@ $^ $(LFLAGS)

keygen: keygen.o $(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encrypt decrypt keygen *.o

cleankeys:
	rm -f *.pub *.priv

format:
	clang-format -i -style=file *.[ch]


