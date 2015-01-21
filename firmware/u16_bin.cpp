#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

#include <vector>

FILE *fp;

uint8_t read(int index)
{
	uint8_t val;
	fseek(fp, index, 0);
	fread(&val, 1, 1, fp);
	return val;
}

// n < 256
uint32_t sample_vector(int n)
{
	uint32_t val;
	val = read(5 + 2*n) << 8;
	val |= read(5 + 2*n + 1);
	return val * 2;
}

void em_sample(int n)
{
	// Conversion things;
	std::vector <uint8_t> au_buffer;
	FILE *fo;
	fo = fopen("out", "w+b");

	uint32_t index = sample_vector(n);
	index++; // why is this needed?	


	for (int j = 0; j < 20; ++j) {
		// do one opcode
		uint8_t op = read(index++);

		if (op == 0x00) {
			printf("Sample end.\n");
			return;
		} else
		if (op & 0b01000000) {
			printf("Playing 256 nibbles\n");
			au_buffer.clear();
			for (int i = 0; i < 128; ++i) {
				uint8_t nibbles = read(index++);
				printf("2 nibbles: %02x\n", nibbles);

				fwrite(&nibbles, 1, 1, fo);
			}
			printf("index is now %06x\n", index);
		} else {
			// I don't know what the opcode means.
			abort();
		}
	}

	fclose(fo);
}

int main(int argc, char **argv)
{
	fp = fopen("U16.BIN", "r");
	if (fp == NULL) {
		printf("Cannot open U16.BIN, errno = %d\n", errno);
		return 1;
	}

	// process the speech ROM
	// first get the total amount of messages
	uint8_t messages = read(0);
	printf("This ROM contains %d messages\n", messages);

	for (int i = 0; i < messages; ++i) {
		printf("Sample %d @ %05x\n", i, sample_vector(i) );
	}

	// DEMO
	em_sample(2); // start emulation of sample 2.

	//
	fclose(fp);

	return 0;
}


