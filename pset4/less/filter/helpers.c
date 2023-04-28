#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float filteredPixel;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            filteredPixel = round((image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0);

            image[h][w].rgbtRed = filteredPixel;
            image[h][w].rgbtGreen = filteredPixel;
            image[h][w].rgbtBlue = filteredPixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float redPixel;
    float greenPixel;
    float bluePixel;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            redPixel = round(0.393 * image[h][w].rgbtRed + 0.769 * image[h][w].rgbtGreen + 0.189 * image[h][w].rgbtBlue);
            greenPixel = round(0.349 * image[h][w].rgbtRed + 0.686 * image[h][w].rgbtGreen + 0.168 * image[h][w].rgbtBlue);
            bluePixel = round(0.272 * image[h][w].rgbtRed + 0.534 * image[h][w].rgbtGreen + 0.131 * image[h][w].rgbtBlue);

            image[h][w].rgbtRed = (redPixel > 255) ? 255 : redPixel;
            image[h][w].rgbtGreen = (greenPixel > 255) ? 255 : greenPixel;
            image[h][w].rgbtBlue = (bluePixel > 255) ? 255 : bluePixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    if (width % 2 == 0)
    {
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width / 2; w++)
            {
                temp = image[h][w];
                image[h][w] = image[h][width - w - 1];
                image[h][width - w] = temp;
            }
        }
    }
    else
    {
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < (width / 2) - 1; w++)
            {
                temp = image[h][w];
                image[h][w] = image[h][width - w - 1];
                image[h][width - w] = temp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurredImage[height][width];
    float averageRed = 0;
    float averageGreen = 0;
    float averageBlue = 0;

    int totalPixels = 0;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            averageRed = 0;
            averageGreen = 0;
            averageBlue = 0;

            totalPixels = 0;

            for (int blurH = -1; blurH < 2; blurH++)
            {
                for (int blurW = -1; blurW < 2; blurW++)
                {
                    if ((h + blurH >= 0 && h + blurH < height) && (w + blurW >= 0 && w + blurW < width))
                    {
                        averageRed += image[h + blurH][w + blurW].rgbtRed;
                        averageBlue += image[h + blurH][w + blurW].rgbtBlue;
                        averageGreen += image[h + blurH][w + blurW].rgbtGreen;

                        totalPixels++;
                    }
                }
            }

            blurredImage[h][w].rgbtRed = averageRed / totalPixels;
            blurredImage[h][w].rgbtBlue = averageBlue / totalPixels;
            blurredImage[h][w].rgbtGreen = averageGreen / totalPixels;
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = blurredImage[h][w].rgbtRed;
            image[h][w].rgbtGreen = blurredImage[h][w].rgbtGreen;
            image[h][w].rgbtBlue = blurredImage[h][w].rgbtBlue;
        }
    }
    return;
}
