#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char *word);

int main(int argc, char *argv[])
{
  // Get input words from both players
  char *word1 = argv[1];
  char *word2 = argv[2];

  // Score both words
  int score1 = compute_score(word1);
  int score2 = compute_score(word2);

  // TODO: Print the winner
  if (score1 > score2)
  {
    printf("Player 1 wins!\n");
    return 1;
  }
  else if (score2 < score1)
  {
    printf("Player 2 wins!\n");
    return 1;
  }
  else
  {
    printf("Tie!\n");
    return 1;
  }
}

int compute_score(char *word)
{
  // TODO: Compute and return score for string
  printf("%s\n", word);
  return 1;
}