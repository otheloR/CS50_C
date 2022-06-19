#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

//                      create an array named argv, and store in it the address of the first character of the two strings, ./recover and card.raw
int main(int argc, char *argv[])
{
    if (argc != 2) {

        printf("Usage: ./recover image\n");
        return 1;


    }



    //open memory card

    FILE *f = fopen(argv[1], "r");

    if (f == NULL) {

        printf("Unable to open file %s\n", argv[1]);
        return 1;

    }

    //need buffer
    //need another file pointer to file that we are writing to
    //counter to count what jpg image currently on
    //track file name

    char filename[8]; //###.jpg\0
    FILE * img = NULL;
    int jpg_Counter = 0;
    BYTE buffer[512];

    int jpg_Finder = 0;
    //continuously iterate through first four bytes of 512 byte chunks


    while(fread(&buffer, 1, 512, f) == 512) {

        //Look for beginning of a JPEG
        //check for oxff, oxd8, and oxff... then oxe0 - oxef


        // check if its start of new jpeg

        if (buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0) {


        //close current jpeg file if not first jpeg

            if (jpg_Finder == 1) {

               fclose(img);


             }

        // flag it as first jpg if first jpeg

            else {

               jpg_Finder = 1;


            }

            sprintf(filename, "%03i.jpg", jpg_Counter);

                img = fopen(filename, "w");

                jpg_Counter++;


        }


        //if its not the start of a new jpeg...


                if (jpg_Finder == 1) {

                    fwrite(&buffer, 1, 512, img);

                }



        }






    return 0;
}