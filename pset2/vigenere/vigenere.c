#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

string shift(string c);
char shift_char(char c, int k);

string key;
int lower_min = 97;
int upper_min = 65;

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        //get key from command line argument
        key = argv[1];
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            //check if key is valid
            if (!isalpha(key[i]))
            {
                // print this if key not provided
                printf("Usage: ./vigenere k\n");
                return 1;
            }
        }
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
        printf("Usage: ./vigenere k\n");
        return 1;
    }

}

string shift(string s)
{
    int count = 0;
    int key_len = strlen(key);
    //for each character in the plaintext string
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        char c = s[i];
        char ck =  key[count % key_len];
        int k;
        if (isupper(ck))
        {

            k = ck - upper_min;
        }
        else
        {
            k = ck - lower_min;
        }
        char encrypted_c = shift_char(c, k);
        s[i] = encrypted_c;
        if (isalpha(s[i]))
        {
            count++;
        }
    }
    return s;
}

char shift_char(char c, int k)
{

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
