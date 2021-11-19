#include <stdio.h>

void sayHello(int n, int counter);

int main(void)
{
  printf("for loop\n");

  for (int i = 0; i < 3; i++)
  {
    sayHello(1, i);
  }

  printf("\nwhile loop\n");

  int y = 0;
  while (y < 3)
  {
    sayHello(2, y);
    y++;
  }

  printf("\ndo-while loop\n");

  int m = 0;
  do
  {
    sayHello(3, m);
    m++;
  } while (m < 3);

  printf("\nmaking a square\n");

  int size = 5;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      printf("#");
    }
    printf("\n");
  }
}

void sayHello(int n, int counter)
{
  if (n == 1)
  {
    printf("hello world %i\n", counter);
  }
  else if (n == 2)
  {
    printf("hello universe %i\n", counter);
  }
  else
  {
    printf("hello multiverse %i\n", counter);
  }
}