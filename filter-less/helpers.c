#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            BYTE buffer =
                round((image[i][j].rgbtGreen + image[i][j].rgbtRed + image[i][j].rgbtBlue) / 3.0);
            // Update pixel values
            image[i][j].rgbtRed = buffer;
            image[i][j].rgbtGreen = buffer;
            image[i][j].rgbtBlue = buffer;
            // (&buffer,sizeof(RGBTRIPLE),1,outptr);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalBlue = image[i][j].rgbtBlue;
            BYTE originalGreen = image[i][j].rgbtGreen;
            int buffer;

            buffer = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            if (buffer > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = (BYTE) buffer;
            }

            buffer = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            if (buffer > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = (BYTE) buffer;
            }

            buffer = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (buffer > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = (BYTE) buffer;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++) // 合理利用punctration
        {
            // Swap pixels
            RGBTRIPLE buffer = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // 此处其实可以在原图片的周围加上一圈0，来避免判断某像素是否是边缘像素？（不行，因为分母也会不一样）
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // judge pixels one by one to exam if the pixel is at the edge and caculate the answer;
            int red_sum = 0;
            int green_sum = 0;
            int blue_sum = 0;
            int pixels_count = 0;
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    if (k > -1 && k < height && l > -1 && l < width)
                    {
                        red_sum += copy[k][l].rgbtRed;
                        green_sum += copy[k][l].rgbtGreen;
                        blue_sum += copy[k][l].rgbtBlue;
                        pixels_count += 1;
                    }
                }
            }
            image[i][j].rgbtRed = round(red_sum / (float) pixels_count);
            image[i][j].rgbtGreen = round(green_sum / (float) pixels_count);
            image[i][j].rgbtBlue = round(blue_sum / (float) pixels_count);
        }
    }
    return;
}
