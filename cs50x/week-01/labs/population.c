#include <stdio.h>

int main(void)
{
  // TODO: Prompt for start size
  int start = 200;
  // TODO: Prompt for end size
  int end = 200;

  // TODO: limit start to be greater than 9
  if (start < 9)
  {
    printf("Please use a start greater than 9.\n");
  }

  // TODO: limit end to be greater than start
  if (end < start)
  {
    printf("Please use an end greater than %i.\n", start);
  }

  if (start > 9 && end > start && start != end)
  { // initialize population counter
    int n = start;
    // initialize year counter
    int y = 0;

    // TODO: Calculate number of years until we reach threshold
    // n / 3 growth, n / 4 shrinkage
    do
    {
      n = n + (n / 3) - (n / 4);
      y++;
    } while (n < end);

    printf("Start size: %i\n", start);
    printf("End size: %i\n", end);
    // TODO: Print number of years
    printf("Years: %i\n", y);
  }
  else if (start == end)
  {
    printf("Start size: %i\n", start);
    printf("End size: %i\n", end);
    printf("Years: 0\n");
  }
}