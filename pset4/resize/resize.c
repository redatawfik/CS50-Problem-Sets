// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize f infile outfile\n");
        return 1;
    }

    const char *flt = argv[1];
    float f;
    sscanf(flt, "%f", &f);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);


    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    BITMAPFILEHEADER new_bf = bf;
    BITMAPINFOHEADER new_bi = bi;

    new_bi.biWidth *= f;
    new_bi.biHeight *= f;

    // determine padding for scanlines
    int new_padding = (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    new_bi.biSizeImage =
        ((sizeof(RGBTRIPLE) * new_bi.biWidth) + new_padding)
        * abs(new_bi.biHeight);

    new_bf.bfSize =
        new_bi.biSizeImage +
        sizeof(BITMAPFILEHEADER) +
        sizeof(BITMAPINFOHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    if (f >= 1)
    {

        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {

            for (int j = 0; j < f; j++)
            {

                // iterate over pixels in scanline
                for (int k = 0; k < bi.biWidth; k++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    for (int l = 0; l < f; l++)
                    {
                        // write RGB triple to outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                // then add it back (to demonstrate how)
                for (int l = 0; l < new_padding; l++)
                {
                    fputc(0x00, outptr);
                }


                fseek(inptr,  -1 * (sizeof(RGBTRIPLE) * bi.biWidth), SEEK_CUR);
            }

            fseek(inptr, (sizeof(RGBTRIPLE) * bi.biWidth), SEEK_CUR);
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

        }
    }
    else
    {

        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i += 2)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k += 2)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                fseek(inptr, sizeof(RGBTRIPLE), SEEK_CUR);

            }

            // then add it back (to demonstrate how)
            for (int l = 0; l < new_padding; l++)
            {
                fputc(0x00, outptr);
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
            fseek(inptr, (bi.biWidth * sizeof(RGBTRIPLE)) + padding, SEEK_CUR);
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
