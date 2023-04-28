#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: recover [filename]\n");
        return 1;
    }

    unsigned char buffer[512];

    //OPENING A FILE
    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
    {
        printf("Couldn't open the file");
        return 2;
    }
    // DUMMY FILE FOR FILLING LATER
    FILE *img = NULL;

    int found_img = 0;
    int counter_img = 0;
    //READING CARD
    while (fread(buffer, 512, 1, f) == 1)
    {
        //USING TRICK TO LESSEN IF STATEMENT SHOWED IN VIDEO
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (found_img == 1)
            {
                fclose(img);
            }
            else
            {
                found_img = 1;
            }

            //DEFINE NEW FILE NAME AND CREATE NEW FILE
            char filename[8];
            sprintf(filename, "%03i.jpg", counter_img);
            img = fopen(filename, "w");
            counter_img++;
        }

        if (found_img == 1)
        {
            //WRITE TO IMAGE
            fwrite(&buffer, 512, 1, img);
        }

    }

    //CLOSING THE FILES

    fclose(img);
    fclose(f);

    return 0;
}