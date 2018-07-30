#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // open input file
    FILE *imptr = fopen(argv[1], "rb");
    if (imptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    //pointer to image founded in file
    FILE *img = NULL;
    //Array for one block in memory
    unsigned char buffer[512];

    //to record number of jpg founded in file
    int counter = -1;
    //when jpg start state -> 1
    int state = 0;

    char filename[8];
    while (1)
    {
        int num = fread(buffer, 1, 512, imptr);

        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (state == 1)
            {
                fclose(img);
            }

            counter++;
            sprintf(filename, "%03i.jpg", counter);

            img = fopen(filename, "w");
            state = 1;

        }

        if (state == 1)
        {
            fwrite(buffer, 1, num, img);
        }

        if (num < 512)
        {
            fclose(img);
            break;
        }
    }
}