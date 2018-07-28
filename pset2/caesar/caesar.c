#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

string shift(string c);
char shift_char(char c);
int k;

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        //get key from command line argument and tturn it to integet
        k = atoi(argv[1]);
        // prompt user for plaintext
        string plaintext = get_string("plaintext:  ");

        //convert plaintext tp ciphertext
        string ciphertext = shift(plaintext);

        // print ciphertext
        printf("ciphertext: %s\n", ciphertext);
    }
    else
    {
        // print this if key not provided
        printf("Usage: ./caesar k\n");
        return 1;
    }

}

string shift(string s)
{
    //for each character in the plaintext string
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        char c = s[i];
        char encrypted_c = shift_char(c);
        s[i] = encrypted_c;
    }
    return s;
}

char shift_char(char c)
{
    int lower_min = 97;
    int upper_min = 65;

    //shift plaintext character by key
    if (islower(c))
    {
        int index = (((c - lower_min) + k) % 26) +  lower_min;
        return (char)index;
    }
    else if (isupper(c))
    {
        int index = (((c - upper_min) + k) % 26) +  upper_min;
        return (char)index;
    }
    else
    {
        return c;
    }
}
