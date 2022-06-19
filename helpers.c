#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++) {

        for (int y = 0; y < width; y++) {

            int average = (int) round((image[x][y].rgbtRed + image[x][y].rgbtBlue + image[x][y].rgbtGreen) / 3.0);

            image[x][y].rgbtRed = average;
            image[x][y].rgbtBlue = average;
            image[x][y].rgbtGreen = average;


        }

    }


    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++) {

        for (int y = 0; y < width; y++) {

           int originalRed = image[x][y].rgbtRed;
           int originalBlue = image[x][y].rgbtBlue;
           int originalGreen = image[x][y].rgbtGreen;

           int newRed = (int) round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
           int newGreen = (int) round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
           int newBlue = (int) round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

           if (newRed > 255) {

               newRed = 255;

           }
           if (newGreen > 255) {

               newGreen = 255;

           }
           if (newBlue > 255) {

               newBlue = 255;

           }

            image[x][y].rgbtRed = newRed;
            image[x][y].rgbtBlue = newBlue;
            image[x][y].rgbtGreen = newGreen;


        }

    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++) {

        for (int y = 0; y < width/2; y++) {

            RGBTRIPLE holder = image[x][y];
            image[x][y] = image[x][(width - 1) - y];
            image[x][(width - 1) - y] = holder;


        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    //create an array as big as image passed through as argument
    RGBTRIPLE holder[height][width];


    //iterate through image's pixels and copy them into RGBTRIPLE array
    for (int x = 0; x < height; x++) {

        for (int y = 0; y < width; y++) {

            holder[x][y] = image[x][y];

        }

    }

    int indexHeight = height - 1;
    int indexWidth = width - 1;



    for (int x = 0; x < height; x++) {


        for (int y = 0; y < width; y++) {

            int box = 0;
             int totalRed = 0;
             int totalBlue = 0;
             int totalGreen = 0;



             //check if there exists a row greater than or is row 0
            if (x - 1 >= 0) {

                //check if there exists a column greater than or is column 0
                if (y - 1 >= 0) {

                    totalRed = totalRed + holder[x - 1][y - 1].rgbtRed;
                    totalBlue = totalBlue + holder[x - 1][y - 1].rgbtBlue;
                    totalGreen = totalGreen + holder[x - 1][y - 1].rgbtGreen;

                    box++;


                }

                //check if there exists a column less than or is column width - 1
                if (y + 1 <= indexWidth) {

                    totalRed = totalRed + holder[x - 1][y + 1].rgbtRed;
                    totalBlue = totalBlue + holder[x - 1][y + 1].rgbtBlue;
                    totalGreen = totalGreen + holder[x - 1][y + 1].rgbtGreen;

                    box++;


                }

                //add box directly above current index
                totalRed = totalRed + holder[x - 1][y].rgbtRed;
                totalBlue = totalBlue + holder[x - 1][y].rgbtBlue;
                totalGreen = totalGreen + holder[x - 1][y].rgbtGreen;

                box++;




            }

            //check if there exists a row less than or is row height - 1
            if (x + 1 <= indexHeight) {


                //check if there exists a row greater than or is column 0
                if (y - 1 >= 0) {

                    totalRed = totalRed + holder[x + 1][y - 1].rgbtRed;
                    totalBlue = totalBlue + holder[x + 1][y - 1].rgbtBlue;
                    totalGreen = totalGreen + holder[x + 1][y - 1].rgbtGreen;

                    box++;

                }

                //check if there exists a column less than or is column width - 1
                if (y + 1 <= indexWidth) {

                     totalRed = totalRed + holder[x + 1][y + 1].rgbtRed;
                    totalBlue = totalBlue + holder[x + 1][y + 1].rgbtBlue;
                    totalGreen = totalGreen + holder[x + 1][y + 1].rgbtGreen;

                    box++;

                }

                // add box directly under index
                totalRed = totalRed + holder[x + 1][y].rgbtRed;
                totalBlue = totalBlue + holder[x + 1][y].rgbtBlue;
                totalGreen = totalGreen + holder[x + 1][y].rgbtGreen;

                box++;


            }
            // check columns directly left and right of box

             //check if there exists a row greater than or is row 0
                if (y - 1 >= 0) {

                    totalRed = totalRed + holder[x][y - 1].rgbtRed;
                    totalBlue = totalBlue + holder[x][y - 1].rgbtBlue;
                    totalGreen = totalGreen + holder[x][y - 1].rgbtGreen;

                    box++;


                }

                //check if there exists a column less than or is column width - 1
                if (y + 1 <= indexWidth) {

                    totalRed = totalRed + holder[x][y + 1].rgbtRed;
                    totalBlue = totalBlue + holder[x][y + 1].rgbtBlue;
                    totalGreen = totalGreen + holder[x][y + 1].rgbtGreen;

                    box++;

                }

                //add current box index
                    totalRed = totalRed + holder[x][y].rgbtRed;
                    totalBlue = totalBlue + holder[x][y].rgbtBlue;
                    totalGreen = totalGreen + holder[x][y].rgbtGreen;

                    box++;

                    totalRed = (int) round(totalRed / (double) box);
                    totalBlue = (int) round(totalBlue / (double) box);
                    totalGreen = (int) round(totalGreen / (double) box);

                    image[x][y].rgbtRed = totalRed;
                    image[x][y].rgbtBlue = totalBlue;
                    image[x][y].rgbtGreen = totalGreen;

        }

    }


    return;
}
