#include <unistd.h>
#include <fcntl.h>
#include "defines.h"
#include <inttypes.h>
#include <string.h>
#include "io.h"
#include "code.h"

uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

static int bit_index = 0;
static uint8_t bit_buf[BLOCK] = { 0 };

static int code_index = 0;
static uint8_t code_buf[BLOCK] = { 0 };

// Reads bytes from input file
// Returns number of bytes read
//
// infile: file descriptor for input file
// buf: buf to be used for reading
// nbytes: total number of bytes to read
// CITE: function went over in Eugene's section
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int bytes = 0; // -1 on error?
    bytes_read = 0;
    do {
        bytes = read(infile, buf + bytes_read, nbytes - bytes_read);
        bytes_read += bytes;
    } while (bytes > 0);
    return bytes_read;
}

// Writes bytes to output file
// Returns number of bytes written
//
// outfile: file descriptor for output file
// buf: buf to be used for writing
// nbytes" total number of bytes to write
// CITE: function went over in Eugene's section
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int bytes = 0; // -1 on error?
    bytes_written = 0;
    do {
        bytes = write(outfile, buf + bytes_written, nbytes - bytes_written);
        bytes_written += bytes;
    } while (bytes > 0);
    return bytes_written;
}

// Reads bits, one at a time
// Returns boolean if all bits were read
//
// infile: file descriptor for input file
// bit: bit pointer to be used
// CITE: function went over in Eric's section
bool read_bit(int infile, uint8_t *bit) {
    static int end = -1; // end of buffer
    if (bit_index == 0) {
        int bytes = read_bytes(infile, bit_buf, BLOCK);
        if (bytes < BLOCK) {
            end = bytes + 1;
        }
    }
    *bit = (bit_buf[bit_index / 8] >> (bit_index % 8)) & 1; // check line
    bit_index = (bit_index + 1) % (BLOCK * 8);
    return (bit_index == (8 * BLOCK));
}

// Writes code to a specified outfile
// Return type is void
//
// outfile: file descriptor to an output file
// c: pointer to a code
// CITE: function went over in Eric's section
void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < code_size(c); i += 1) {
        if (code_get_bit(c, i) == 1) {
            code_buf[code_index / 8] |= (0x1 << code_index % 8);
        }
    }
    code_index = (code_index + 1) % (8 * BLOCK); //changed
    if (code_index == 0) {
        write_bytes(outfile, code_buf, BLOCK);
        memset(code_buf, 0, BLOCK);
    }
}

// Write any remaining codes to outfile
// Return type is void
//
// outfile: file descriptor for output file
// CITE: function went over in Eric's section
void flush_codes(int outfile) {
    int bytes_to_write = (code_index % 8) == 0 ? (code_index / 8) : (code_index / 8) + 1;
    write_bytes(outfile, code_buf, bytes_to_write);
}
