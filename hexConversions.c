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
