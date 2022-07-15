#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int compute_grade(char *excerpt);

int main(int argc, char *argv[])
{
  // Get input words from bthe user
  char *excerpt = argv[1];
  printf("%s\n", excerpt);

  // Score the grade level of the excerpt
  int grade = compute_grade(excerpt);

  if (grade > 0 && grade < 16)
  {
    printf("Grade %i\n", grade);
  }
  else if (grade > 16)
  {
    printf("Grade 16+\n");
  }
  else
  {
    printf("Before Grade 1\n");
  }

  return 0;
}

int compute_grade(char *excerpt)
{
  int totalLetters = 0;   // used to store letter count in excerpt
  int totalWords = 1;     // used to store word count in excerpt
  int totalSentences = 0; // used to store sentence count in excerpt

  if (strlen(excerpt) == 0)
  {
    totalWords = 0;
  }

  // TODO: Compute and return grade level for excerpt
  for (int i = 0; i < strlen(excerpt) + 1; i++)
  {
    int ascii = (int)excerpt[i];

    if (ascii >= 65 && ascii <= 122)
    {
      totalLetters++;
    }

    if (ascii == 32)
    {
      totalWords++;
    }

    if (ascii == 33 || ascii == 46 || ascii == 63)
    {
      totalSentences++;
    }
  }
  printf("%i letter(s)\n", totalLetters);
  printf("%i word(s)\n", totalWords);
  printf("%i sentence(s)\n", totalSentences);

  if (totalLetters == 0 || totalSentences == 0 || totalWords == 0)
  {
    return 0;
  }

  float L = ((float)totalLetters / (float)totalWords) * 100;   // letters per 100 words
  float S = ((float)totalSentences / (float)totalWords) * 100; // sentences per 100 words
  printf("L: %f, S: %f\n", L, S);

  float index = 0.0588 * L - 0.296 * S - 15.8;
  int grade = round(index);

  return grade;
}