# Assignment 6: Public Key Cryptpgraphy
 
This program is an implementation of public key cryptography using the RSA algorithm. There
will be three seperate main programs, one to generate public and private keys, one to
perform RSA encryption, and one to perform RSA decryption. These files will make use of 
functions implemented in three other files: randstate.c, numtheory.c, and rsa.c. 
 
## Building

Build the program with:
```
$ make
```
or
```
$ make all
```
or
```
$ make encrypt, decrypt, keygen
```
## Running

Run the program with:
```
$ ./keygen [-hv] [-b bits] -n pbfile -d pvfile
```
and
```
$ ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey
```
or
```
$ ./decrypt [-hv] [-i infile] [-o outfile] -n privkey
```

## Command Line Options

Keygen Options:\
   -h              Display program help and usage.\
   -v              Display verbose program output.\
   -b bits         Minimum bits needed for public key n (default: 256).\
   -i confidence   Miller-Rabin iterations for testing primes (default: 50).\
   -n pbfile       Public key file (default: rsa.pub).\
   -d pvfile       Private key file (default: rsa.priv).\
   -s seed         Random seed for testing.\\

Encrypt Options:\
   -h              Display program help and usage.\
   -v              Display verbose program output.\
   -i infile       Input file of data to encrypt (default: stdin).\
   -o outfile      Output file for encrypted data (default: stdout).\
   -n pbfile       Public key file (default: rsa.pub).\\

Decrypt Options:\
   -h              Display program help and usage.\
   -v              Display verbose program output.\
   -i infile       Input file of data to decrypt (default: stdin).\
   -o outfile      Output file for decrypted data (default: stdout).\
   -n pvfile       Private key file (default: rsa.priv).\

