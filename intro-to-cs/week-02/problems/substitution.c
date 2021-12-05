#include <stdio.h>
#include <ctype.h>
#include <string.h>

int hasAlphabetCheck(char *key);

int main(int argc, char *argv[])
{

  if (argc < 3)
  {
    printf("Missing arguments - make sure there is [1] a key and [2] a plainText message to convert.\n");
    return 1;
  }
  else if (argc > 3)
  {
    printf("Extra arguments given - ignoring everything beyond [1] key and [2] plainText message.\n");
  }

  char *key = argv[1];
  char *plainText = argv[2];    // stores the original message
  char *cipherText = plainText; // stores the encrypted message

  if (hasAlphabetCheck(key) == 0 && strlen(key) == 26)
  {
    for (int i = 0; i < strlen(plainText); i++)
    {
      int x = plainText[i];
      if (x >= 97 && x <= 122)
      {
        cipherText[i] = tolower(key[x - 97]);
      }
      else if (x >= 65 && x <= 90)
      {
        cipherText[i] = toupper(key[x - 65]);
      }
    }

    printf("%s\n", cipherText);
  }
  else
  {
    printf("Must have all 26 letters of the alphabet, with each occuring only once.\n");
    return 1;
  }

  return 0;
}

int hasAlphabetCheck(char *key)
{
  for (int i = 0; i < strlen(key); i++)
  {
    if (!isalpha(key[i]))
    {
      printf("Only letters of the alphabet are allowed. '%c' is an unallowed character.\n", (char)key[i]);
      return 1;
    }
    for (int j = 0; j < strlen(key); j++)
    {
      if (tolower(key[i]) == tolower(key[j]) && i != j)
      {
        printf("Only 1 occurance of each letter in the alphabet is allowed. '%c' appears twice.\n", (char)key[j]);
        return 1;
      }
    }
  }
  return 0;
}
