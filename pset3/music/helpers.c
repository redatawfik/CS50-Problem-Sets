// Helper functions for music

#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    if (strcmp(fraction, "1/8") == 0)
    {
        return 1;
    }
    else if (strcmp(fraction, "1/4") == 0)
    {
        return 2;
    }
    else if (strcmp(fraction, "3/8") == 0)
    {
        return 3;
    }
    else
    {
        return 4;
    }

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
    //Create array of char to act as a string when executing
    //atoi() function
    char arr[2];
    //if no sharp then octive locate at index 1
    if (strlen(note) == 2)
    {
        arr[0] = note[1];
    }
    //otherwise it locate at index 2
    else
    {
        arr[0] = note[2];
    }
    arr[1] = '\0';
    //convert octive string to integer
    int octive = atoi(arr);
    //calculate primary frequncy according to octive
    int f = 440 *  pow(2, octive - 4);

    char c = note[0];
    double frequncy_var;

    //calculate final frequncy according to Char
    if (c == 'C')
    {
        frequncy_var = (f / pow(2, (9 / 12.0)));
    }
    else if (c == 'D')
    {
        frequncy_var = (f / pow(2, (7 / 12.0)));
    }
    else if (c == 'E')
    {
        frequncy_var = (f / pow(2, (5 / 12.0)));
    }
    else if (c == 'F')
    {
        frequncy_var = (f / pow(2, (4 / 12.0)));
    }
    else if (c == 'G')
    {
        frequncy_var = (f / pow(2, (2 / 12.0)));
    }
    else if (c == 'A')
    {
        frequncy_var = f;
    }
    else if (c == 'B')
    {
        frequncy_var = (f * pow(2, (2 / 12.0)));
    }



    if (strlen(note) == 3)
    {
        if (note[1] == '#')
        {
            frequncy_var = (frequncy_var * pow(2, (1 / 12.0)));
        }
        else
        {
            frequncy_var = (frequncy_var / pow(2, (1 / 12.0)));
        }

    }

    frequncy_var = round(frequncy_var);
    return frequncy_var;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // if line equals "" return true
    if (strcmp(s, "") == 0)
    {
        return true;
    }

    return false;
}
