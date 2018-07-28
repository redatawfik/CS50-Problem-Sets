#include <stdlib.h>
#include <string.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#define _GNU_SOURCE
#include <crypt.h>
#include <cs50.h>
#include <stdio.h>

bool one(void);
bool two(void);
bool three(void);
bool four(void);
bool five(void);
//All Capital and small letters to check
string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//lenth of letters string
int length;
//hashed passowrd that user provide
string hash;

int main(int argc, string argv[])
{
    length = strlen(letters);
    //check if user provide hashed passowrd
    if (argc == 2)
    {
        hash = argv[1];

        //check if passowrd consist of one letter
        if (one())
        {
            eprintf("now : one\n");
            return 0;
        }
        //check if passowrd consist of two letters
        else if (two())
        {
            eprintf("now : two\n");
            return 0;
        }
        //check if passowrd consist of three letters
        else if (three())
        {
            eprintf("now : three\n");
            return 0;
        }
        //check if passowrd consist of four letters
        else if (four())
        {
            four();
            eprintf("now : four\n");
            return 0;
        }
        //check if passowrd consist of five letters
        else if (five())
        {
            eprintf("now : five\n");
            return 0;
        }
        //print this if password not found
        else
        {
            printf("not found\n");
        }
    }
    else
    {
        // print this if key not provided
        printf("Usage: ./crack hash\n");
        return 1;
    }

}

bool one(void)
{
    //itrate throw one letter
    for (int i = 0; i < length; i++)
    {
        char c = letters[i];
        char str[2];
        str[0] = c;
        str[1] = '\0';
        string w = crypt(str, "aa");
        if (strcmp(w, hash) == 0)
        {
            printf("%s\n", str);
            return true;
        }
    }
    return false;
}


bool two(void)
{

    //itrate throw two letters
    //loop for first letter
    for (int i = 0; i < length; i++)
    {
        //loop for second letter
        for (int j = 0; j < length; j++)
        {
            char c1 = letters[i];
            char c2 = letters[j];
            char str[3];
            str[0] = c1;
            str[1] = c2;
            str[2] = '\0';
            string w = crypt(str, "aa");
            if (strcmp(w, hash) == 0)
            {
                printf("%s\n", str);
                return true;
            }
        }
    }
    return false;
}


bool three(void)
{
    //itrate throw three letters

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            for (int k = 0; k < length; k++)
            {
                char c1 = letters[i];
                char c2 = letters[j];
                char c3 = letters[k];
                char str[4];
                str[0] = c1;
                str[1] = c2;
                str[2] = c3;
                str[3] = '\0';
                string w = crypt(str, "aa");
                if (strcmp(w, hash) == 0)
                {
                    printf("%s\n", str);
                    return true;
                }
            }
        }
    }
    return false;
}


bool four(void)
{
    //itrate throw four letters
    //loop for first letter
    for (int i = 0; i < length; i++)
    {
        //loop for second letter
        for (int j = 0; j < length; j++)
        {
            //loop for third letter
            for (int k = 0; k < length; k++)
            {
                //loop for fourth letter
                for (int l = 0; l < length; l++)
                {
                    //loop for fifth letter
                    char c1 = letters[i];
                    char c2 = letters[j];
                    char c3 = letters[k];
                    char c4 = letters[l];
                    char str[5];
                    str[0] = c1;
                    str[1] = c2;
                    str[2] = c3;
                    str[3] = c4;
                    str[4] = '\0';
                    string w = crypt(str, "aa");
                    if (strcmp(w, hash) == 0)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


bool five(void)
{
    //itrate throw five letters
    //loop for first letter
    for (int i = 0; i < length; i++)
    {
        //loop for second letter
        for (int j = 0; j < length; j++)
        {
            //loop for third letter
            for (int k = 0; k < length; k++)
            {
                //loop for fourth letter
                for (int l = 0; l < length; l++)
                {
                    //loop for fifth letter
                    for (int m = 0; m < length; m++)
                    {
                        char c1 = letters[i];
                        char c2 = letters[j];
                        char c3 = letters[k];
                        char c4 = letters[l];
                        char c5 = letters[m];
                        char str[6];
                        str[0] = c1;
                        str[1] = c2;
                        str[2] = c3;
                        str[3] = c4;
                        str[4] = c5;
                        str[5] = '\0';
                        string w = crypt(str, "aa");
                        if (strcmp(w, hash) == 0)
                        {
                            printf("%s\n", str);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}