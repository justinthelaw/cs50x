#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BLOCK 512

typedef uint8_t BYTE; // alias for 8 bits of data

int main(int argc, char *argv[])
{
  if (argc != 2) // ensure only 1 arg, the file to be read, is present
  {
    printf("Usage: ./recover image\n");
    return 1;
  }

  // remove existing .jpeg files from current directory
  char *command = "rm *.jpg -f";
  system(command);

  FILE *input = fopen(argv[1], "r");
  if (input == NULL)
  {
    printf("Could not open file.\n");
    return 1;
  }

  BYTE header[BLOCK];
  FILE *output;
  int count = 0;
  char filename[8];

  while (fread(&header, BLOCK, 1, input) == 1)
  {
    if (header[0] == 0xff && header[1] == 0xd8 && header[2] == 0xff && (header[3] == 0xe0 || header[3] == 0xe1 || header[3] == 0xe2 || header[3] == 0xe3 || header[3] == 0xe4 || header[3] == 0xe5 || header[3] == 0xe6 || header[3] == 0xe7 || header[3] == 0xe8 || header[3] == 0xe9 || header[3] == 0xea || header[3] == 0xeb || header[3] == 0xec || header[3] == 0xed || header[3] == 0xee || header[3] == 0xef))
    {
      if (count != 0)
      {
        fclose(output);
      }

      if (count < 10)
      {
        sprintf(filename, "00%i.jpg", count);
      }
      else if (count < 100)
      {
        sprintf(filename, "0%i.jpg", count);
      }
      else
      {
        sprintf(filename, "%i.jpg", count);
      }

      output = fopen(filename, "w");
      count++;
    }

    if (count != 0)
    {
      fwrite(&header, BLOCK, 1, output);
    }
  }
  fclose(input);
  fclose(output);
  return 0;
}