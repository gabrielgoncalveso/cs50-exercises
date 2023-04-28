#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edgedImage[height][width];
    int gxRed = 0;
    int gxGreen = 0;
    int gxBlue = 0;

    int gyRed = 0;
    int gyGreen = 0;
    int gyBlue = 0;

    int newPixelRed;
    int newPixelGreen;
    int newPixelBlue;

    int gxMatriz[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gyMatriz[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            gxRed = 0;
            gxGreen = 0;
            gxBlue = 0;
            gyRed = 0;
            gyGreen = 0;
            gyBlue = 0;

            for (int edgeH = -1; edgeH < 2; edgeH++)
            {
                for (int edgeW = -1; edgeW < 2; edgeW++)
                {
                    if ((h + edgeH >= 0 && h + edgeH < height) && (w + edgeW >= 0 && w + edgeW < width))
                    {
                        gxRed += image[h + edgeH][w + edgeW].rgbtRed * gxMatriz[edgeH + 1][edgeW + 1];
                        gxGreen += image[h + edgeH][w + edgeW].rgbtGreen * gxMatriz[edgeH + 1][edgeW + 1];
                        gxBlue += image[h + edgeH][w + edgeW].rgbtBlue * gxMatriz[edgeH + 1][edgeW + 1];

                        gyRed += image[h + edgeH][w + edgeW].rgbtRed * gyMatriz[edgeH + 1][edgeW + 1];
                        gyGreen += image[h + edgeH][w + edgeW].rgbtGreen * gyMatriz[edgeH + 1][edgeW + 1];
                        gyBlue += image[h + edgeH][w + edgeW].rgbtBlue * gyMatriz[edgeH + 1][edgeW + 1];

                    }
                }
            }

            int newRedPixel = sqrt((gxRed * gxRed) + (gyRed * gyRed));
            int newBluePixel = sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue));
            int newGreenPixel = sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen));

            edgedImage[h][w].rgbtRed = (newRedPixel < 255) ? newRedPixel : 255;
            edgedImage[h][w].rgbtBlue = (newBluePixel < 255) ? newBluePixel : 255;
            edgedImage[h][w].rgbtGreen = (newGreenPixel < 255) ? newGreenPixel : 255;
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = edgedImage[h][w].rgbtRed;
            image[h][w].rgbtGreen = edgedImage[h][w].rgbtGreen;
            image[h][w].rgbtBlue = edgedImage[h][w].rgbtBlue;
        }
    }

    return;
}
