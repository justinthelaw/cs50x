#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *s = "INVALID";

int checkLength(long creditCardNumber)
{
  int length = floor(log10(labs(creditCardNumber))) + 1;
  // simple boolean return based on length of card number
  if (length >= 13 && length <= 16)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

char *checkCreditCardCompany(long creditCardNumber)
{
  char *company = s;
  long firstTwoDigits = creditCardNumber;

  // get the first two digits
  while (firstTwoDigits >= 100)
  {
    firstTwoDigits /= 10;
  }

  // run checks on the first two digits to find the credit card company
  if (firstTwoDigits >= 40 && firstTwoDigits < 50)
  {
    company = "VISA";
  }
  else if (firstTwoDigits == 34 || firstTwoDigits == 37)
  {
    company = "AMEX";
  }
  else if (firstTwoDigits >= 51 && firstTwoDigits <= 55)
  {
    company = "MASTERCARD";
  }
  return company;
}

int checkLuhnsAlgorithm(long creditCardNumber)
{
  // even product and summation loop
  long buffer = creditCardNumber;
  int evenSum = 0;
  int oddSum = 0;
  while (buffer >= 1)
  {
    int y = buffer % 10;
    oddSum += y;

    buffer /= 10;
    int x = buffer % 10;

    buffer /= 10;
    x *= 2;

    if (x / 10 == 0)
    {
      evenSum += x;
    }
    else
    {
      evenSum += ((x / 10) + (x % 10));
    }
  }

  int valid = 0;
  if ((evenSum + oddSum) % 10 == 0)
  {
    valid = 1;
  }
  return valid;
}

void checkCreditCardCompliance(long creditCardNumber)
{
  int validLength = checkLength(creditCardNumber);

  if (validLength)
  {
    // check Luhn's Algorithm compliance
    int validNumber = checkLuhnsAlgorithm(creditCardNumber);
    if (validNumber)
    {
      // check credit card company pattern compliance
      char *company = checkCreditCardCompany(creditCardNumber);
      printf("%s\n", company);
    }
    else
    {
      printf("%s\n", s);
    }
  }
  else
  {
    printf("%s\n", s);
  }
}

int main(void)
{
  printf("Should be AMEX: ");
  checkCreditCardCompliance(378282246310005);
  printf("Should be AMEX: ");
  checkCreditCardCompliance(371449635398431);
  printf("Should be VISA: ");
  checkCreditCardCompliance(4222222222222);
  printf("Should be VISA: ");
  checkCreditCardCompliance(4003600000000014);
  printf("Should be VISA: ");
  checkCreditCardCompliance(4111111111111111);
  printf("Should be MASTERCARD: ");
  checkCreditCardCompliance(5555555555554444);
  printf("Should be MASTERCARD: ");
  checkCreditCardCompliance(5105105105105100);
  printf("Should be INVALID: ");
  checkCreditCardCompliance(369421438430814);
  printf("Should be INVALID: ");
  checkCreditCardCompliance(5673598276138003);
  printf("Should be INVALID: ");
  checkCreditCardCompliance(4111111111111113);
  printf("Should be INVALID: ");
  checkCreditCardCompliance(4222222222223);
}