#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
//             {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q , r, s, t, u, v, w, x, y, z};

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
    return 0;
  }
  else if (score1 < score2)
  {
    printf("Player 2 wins!\n");
    return 0;
  }
  else
  {
    printf("Tie!\n");
    return 0;
  }
}

int compute_score(char *word)
{
  int score = 0;
  // TODO: Compute and return score for string
  for (int i = 0; i < strlen(word); i++)
  {
    // turn the characters to lowercase and subtract 97 from ascii integer to get character score position
    int index = (int)tolower(word[i]) - 97;
    if (index >= 0 && index < 25)
    {
      score += POINTS[index];
      printf("%c: %i\n", word[i], POINTS[index]);
    }
  }
  return score;
}