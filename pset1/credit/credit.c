#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long n = get_long_long("Number: ");
    int sum = 0;
    int multiple_sum = 0;
    long copy =  n;
    int count = 1;

    //Set sum and multiple_sum values
    while (copy != 0)
    {
        int digit = copy % 10;
        if (count % 2 == 0)
        {
            digit *= 2;
            while (digit != 0)
            {
                int d = digit % 10;
                multiple_sum += d;
                digit /= 10;
            }
        }
        else
        {
            sum += digit;

        }
        copy /= 10;
        count++;
    }

    int final_sum = multiple_sum + sum;
    int number_of_digits = count - 1;
    int first_two_digit = n  / (long)pow(10, (number_of_digits - 2));
    int first_digit = first_two_digit / 10;

    //Check type of card
    if (final_sum % 10 == 0)
    {
        //AMEX card
        if (number_of_digits == 15 && ((first_two_digit == 34) || (first_two_digit == 37)))
        {
            printf("AMEX\n");
        }
        //MASTERCARD card
        else if (number_of_digits == 16 && ((first_two_digit == 51) || (first_two_digit == 52) || (first_two_digit == 53)
                                            || (first_two_digit == 54) || (first_two_digit == 55)))
        {
            printf("MASTERCARD\n");
        }
        //VISA card
        else if (((number_of_digits == 13) || (number_of_digits == 16)) && (first_digit == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}