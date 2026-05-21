//Գրել ռեկուրսիվ ֆունկցիա, որը կհաշվի փոխանցված num թվի power աստիճանը։

#include <stdio.h>

int power (int, int);

int main ()
{
printf("Power is: %i\n", power(2, 3));
return 0;
}

int power (int n, int p)
{
 if (p == 0) return 1;
 return power(n, --p) * n;
}