#include <stdlib.h>
#include <stdio.h>

// Convert byte to two hex characters
void byteToHex(char* output, unsigned char b) {
  char conversion[] =
  {'0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  'A',
  'B',
  'C',
  'D',
  'E',
  'F'};
  *output = (conversion[b >> 4]);
  *(output + 1) = (conversion[b & 0b00001111]);
}

// Find the value of a single hex character
int hexToHalfByte(char hex) {
  char conversion[] =
  {'0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  'A',
  'B',
  'C',
  'D',
  'E',
  'F'};

  for (int i = 0; i < 16; i++) {
    if (hex == conversion[i]){
      return i;
    }
  }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        return 1;
    }

    // Get user provided value
    unsigned int inputNum = 0;
    {

        int numLen = 0;
        while (argv[1][numLen]) {
          numLen++;
        }
        for (int i = 0; i < numLen; i++) {
          inputNum += hexToHalfByte(argv[1][i]) << 4 * (numLen - i - 1);
        }
    }

    // Convert value to utf-8
    char* output = (char*) malloc(17); // Allocate space for output text up to 16 chars
    output[16] = 0; // Last char is null terminator
    unsigned int hexNum = 0;
    int byteCount = 0;

    if (inputNum < 0x80) { // Special case for one byte codes
      byteCount = 0;
      hexNum = inputNum;
    } else {
      if (inputNum < 0x800) {
        byteCount = 1;
      } else if (inputNum < 0x10000) {
        byteCount = 2;
      } else {
        byteCount = 3;
      }

      for (int i = 0; i < byteCount; i++) {
          hexNum |= (inputNum & (0b111111 << (i * 6))) << (2 * i); // Move 6 bit blocks out to 8 bit blocks
          hexNum |= 0b10000000 << (i * 8); // Start each byte with 0b10...
      }
      hexNum |= (inputNum & (((64 >> byteCount) - 1) << (byteCount * 6))) << (2 * byteCount); // Move first block out to first 8 bit block
      hexNum |= ((2 << byteCount) - 1) << (byteCount * 8 + 7 - byteCount); // Add byte count to first byte

    }


    char* hexLetters = (char*) malloc(2);
    for (int i = 0; i <= byteCount; i++) {
      byteToHex(hexLetters, hexNum >> ((byteCount - i) * 8));

      *(output + i * 4) = '\\';
      *(output + i * 4 + 1) = 'x';
      *(output + i * 4 + 2) = *hexLetters;
      *(output + i * 4 + 3) = *(hexLetters + 1);
    }
    printf("%s\n", output);

    free(output);
    free(hexLetters);
    return 0;
}
