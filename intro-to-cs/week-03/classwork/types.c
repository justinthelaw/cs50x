#include <stdio.h>
#include <string.h>

typedef struct
{
  char *name;
  char *number;
} person;

int main(void)
{
  person people[2];

  people[0].name = "Brian";
  people[0].number = "000-000-0000";
  people[1].name = "David";
  people[1].number = "111-111-1111";

  for (int i = 0; i < 2; i++)
  {
    if (strcmp(people[i].name, "David"))
    {
      printf("Found %s\n", people[i].number);
      return 0;
    }
  }
  printf("Not Found");
  return 1;
}