#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE currRGB = image[i][j];
            int grayyed = round((currRGB.rgbtBlue + currRGB.rgbtGreen + currRGB.rgbtRed) / 3.0);

            currRGB.rgbtBlue = grayyed;
            currRGB.rgbtGreen = grayyed;
            currRGB.rgbtRed = grayyed;
            image[i][j] = currRGB;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int last = width - 1;
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE firstRGB = image[i][j];
            RGBTRIPLE lastRGB = image[i][last];
            RGBTRIPLE tmpRGB = lastRGB;
            image[i][j] = tmpRGB;
            image[i][last] = firstRGB;
            last--;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blueVal = -1;
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            { // is 'center' pixel
                blueVal = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                 image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                 image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) /
                                9.0);
            }

            int greenVal = -1;
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            { // is 'center' pixel
                greenVal = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                  image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                  image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) /
                                 9.0);
            }

            int redVal = -1;
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            { // is 'center' pixel
                redVal = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) /
                               9.0);
            }

            imageCp[i][j].rgbtBlue = blueVal;
            imageCp[i][j].rgbtGreen = greenVal;
            imageCp[i][j].rgbtRed = redVal;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageCp[i][j];
        }
    }

    return;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCp[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || i == height + 1 || j == 0 || j == width + 1)
            {
                imageCp[i][j].rgbtBlue = 0;
                imageCp[i][j].rgbtBlue = 0;
                imageCp[i][j].rgbtBlue = 0;
            }
            else
            {
                imageCp[i][j].rgbtBlue = image[i - 1][j - 1].rgbtBlue;
                imageCp[i][j].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                imageCp[i][j].rgbtRed = image[i - 1][j - 1].rgbtRed;
            }
        }
    }

    RGBTRIPLE imageCp2[height][width];
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            int xBlueVal = -1;
            int yBlueVal = -1;
            xBlueVal =
                ((-1 * imageCp[i - 1][j - 1].rgbtBlue) + (1 * imageCp[i - 1][j + 1].rgbtBlue) + (-2 * imageCp[i][j - 1].rgbtBlue) +
                 (2 * imageCp[i][j + 1].rgbtBlue) + (-1 * imageCp[i + 1][j - 1].rgbtBlue) + (1 * imageCp[i + 1][j + 1].rgbtBlue));
            yBlueVal =
                ((-1 * imageCp[i - 1][j - 1].rgbtBlue) + (1 * imageCp[i + 1][j - 1].rgbtBlue) + (-2 * imageCp[i - 1][j].rgbtBlue) +
                 (2 * imageCp[i + 1][j].rgbtBlue) + (-1 * imageCp[i - 1][j + 1].rgbtBlue) + (1 * imageCp[i + 1][j + 1].rgbtBlue));

            int xGreenVal = -1;
            int yGreenVal = -1;
            xGreenVal = ((-1 * imageCp[i - 1][j - 1].rgbtGreen) + (1 * imageCp[i - 1][j + 1].rgbtGreen) +
                         (-2 * imageCp[i][j - 1].rgbtGreen) + (2 * imageCp[i][j + 1].rgbtGreen) +
                         (-1 * imageCp[i + 1][j - 1].rgbtGreen) + (1 * imageCp[i + 1][j + 1].rgbtGreen));
            yGreenVal = ((-1 * imageCp[i - 1][j - 1].rgbtGreen) + (1 * imageCp[i + 1][j - 1].rgbtGreen) +
                         (-2 * imageCp[i - 1][j].rgbtGreen) + (2 * imageCp[i + 1][j].rgbtGreen) +
                         (-1 * imageCp[i - 1][j + 1].rgbtGreen) + (1 * imageCp[i + 1][j + 1].rgbtGreen));

            int xRedVal = -1;
            int yRedVal = -1;
            xRedVal =
                ((-1 * imageCp[i - 1][j - 1].rgbtRed) + (1 * imageCp[i - 1][j + 1].rgbtRed) + (-2 * imageCp[i][j - 1].rgbtRed) +
                 (2 * imageCp[i][j + 1].rgbtRed) + (-1 * imageCp[i + 1][j - 1].rgbtRed) + (1 * imageCp[i + 1][j + 1].rgbtRed));
            yRedVal =
                ((-1 * imageCp[i - 1][j - 1].rgbtRed) + (1 * imageCp[i + 1][j - 1].rgbtRed) + (-2 * imageCp[i - 1][j].rgbtRed) +
                 (2 * imageCp[i + 1][j].rgbtRed) + (-1 * imageCp[i - 1][j + 1].rgbtRed) + (1 * imageCp[i + 1][j + 1].rgbtRed));

            int blueVal = round(sqrt((xBlueVal * xBlueVal * 1.0) + (yBlueVal * yBlueVal * 1.0)));
            if (blueVal > 255)
            {
                blueVal = 255;
            }
            int greenVal = round(sqrt((xGreenVal * xGreenVal * 1.0) + (yGreenVal * yGreenVal * 1.0)));
            if (greenVal > 255)
            {
                greenVal = 255;
            }
            int redVal = round(sqrt((xRedVal * xRedVal * 1.0) + (yRedVal * yRedVal * 1.0)));
            if (redVal > 255)
            {
                redVal = 255;
            }

            imageCp2[i - 1][j - 1].rgbtBlue = blueVal;
            imageCp2[i - 1][j - 1].rgbtGreen = greenVal;
            imageCp2[i - 1][j - 1].rgbtRed = redVal;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageCp2[i][j];
        }
    }

    return;
}