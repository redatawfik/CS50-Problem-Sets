
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdio.h>


int main(void)
{
    double a = pow(2, (5.0 / 12));
    printf("%f\n", a);
    double b = 440 / a;
    printf("%f\n", b);
    int c = round(b);
    printf("%i\n", c);
}