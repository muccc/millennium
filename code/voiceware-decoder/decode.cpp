/**
 * Attempts to decode speech data extracted from a North American phone.
 *
 * LICENSE: public domain.
 * (c) 2015, Philippe Michaud-Boudreault
 */
#include "upd.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

#include <vector>
#include <sstream>
#include <string>

/*
   We know from the datasheet that this chip has an internal 9-bit DAC.
   Play the resulting output as a signed 16-bit PCM stream.

    aplay -f S16_LE -r8421 pcm7

 */


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
	std::vector <uint8_t> au_buffer, au_buffer_nibbles;
	FILE *fo;

	// derive the filename for n
	std::ostringstream fn;
	fn << "pcm" << n;
	fo = fopen(fn.str().c_str(), "w+b");

	uint32_t index = sample_vector(n);
	index++; // why is this needed?	

	au_buffer.clear();

	for (; true;) {
		// do one opcode
		uint8_t op = read(index++);

		if (op == 0x00) {
			//printf("Sample end.\n");
			goto sample_end;
		} else if (op & 0b01000000) {
			//printf("Playing 256 nibbles\n");

			for (int i = 0; i < 128; ++i) {
				uint8_t nibbles = read(index++);
				//printf("2 nibbles: %02x\n", nibbles);
				au_buffer.push_back(nibbles);
				//fwrite(&nibbles, 1, 1, fo);
			}
		} else if ((op & 0b11000000) == 0) {
			//printf("Silence step\n");
		} else if (op & 0b10000000) {
			uint8_t operand = read(index++);
			operand++;
			//printf("Playing %d nibbles\n", operand);

			for (int i = 0; i < operand >> 1; ++i) {
				uint8_t nibbles = read(index++);
				//printf("2 nibbles: %02x\n", nibbles);
				au_buffer.push_back(nibbles);
				//fwrite(&nibbles, 1, 1, fo);
			}
		} else {
			printf("I don't know what the opcode means\n");
			abort();
		}
	}

sample_end:
	// fix the stream so it contains a bunch of nibbles
	au_buffer_nibbles.clear();
	for (uint8_t d : au_buffer) {
		au_buffer_nibbles.push_back(d >> 4);
		au_buffer_nibbles.push_back(d & 0x0F);
	}

	// process the audio data;
	// XXX split up
	{
		int8_t  state;  // Current ADPCM state
		uint8_t data;   // Current ADPCM data
		int16_t sample; // Current sample value

		state = sample = data = 0;
		for (uint8_t nibbles : au_buffer_nibbles)
		{
			data = nibbles & 0x0f;

			// update ADPCM

			sample += upd7759_step[state][data];
			state += upd7759_state_table[data];

			// clamp the state to 0..15
			if (state < 0) state = 0;
			else if (state > 15) state = 15;

			// Amplify output a bit. 9+7 = 16
			uint16_t sample2 = sample << 7;
			fwrite(&sample2, 2, 1, fo);
		}
	}


	fclose(fo);
}

int main(int argc, char **argv)
{
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Cannot open %s, errno = %d\n", argv[1], errno);
		return 1;
	}

	// process the speech ROM
	// first get the total amount of messages
	uint8_t messages = read(0);
	printf("This ROM contains %d messages\n", messages);


	// Consider all messages
	for (int i = 0; i < messages; ++i) {
		printf("Sample %d @ %05x\n", i, sample_vector(i) );
		em_sample(i); // start emulation of sample.
	}

	//
	fclose(fp);

	return 0;
}


