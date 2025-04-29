#include "helpers.h"
#include <math.h>

BYTE Sobel(int Gx_value,int Gy_value);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // I need to write pseudocode first.
    // intialize two two-dimentional arrays (Gx,Gy)
    int Gx[3][3] = {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };
    int Gy[3][3] = {
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    };

    // copy the image to a new two-dimentional array which has a black edge
    // RGBTRIPLE copy[height + 2][width + 2] = {0};（只有固定大小的数组可以这么做）
    RGBTRIPLE copy[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            copy[i][j].rgbtRed = 0;
            copy[i][j].rgbtGreen = 0;
            copy[i][j].rgbtBlue = 0;
        }
    } // 其实这个nested loops可以简化（可以只给边框赋值）

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i + 1][j + 1] = image[i][j];
        }
    }

    // loop over the core pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the Gx_value and the Gy_value
            int Gx_count_Red = 0;
            int Gy_count_Red = 0;
            int Gx_count_Green = 0;
            int Gy_count_Green = 0;
            int Gx_count_Blue = 0;
            int Gy_count_Blue = 0; // 这样子写实在是太蠢了，等我学了case以后，一定不再这么写
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    Gx_count_Red += copy[k][l].rgbtRed * Gx[k - i + 1][l - j + 1];
                    Gy_count_Red += copy[k][l].rgbtRed * Gy[k - i + 1][l - j + 1];
                    Gx_count_Green += copy[k][l].rgbtGreen * Gx[k - i + 1][l - j + 1];
                    Gy_count_Green += copy[k][l].rgbtGreen * Gy[k - i + 1][l - j + 1];
                    Gx_count_Blue += copy[k][l].rgbtBlue * Gx[k - i + 1][l - j + 1];
                    Gy_count_Blue += copy[k][l].rgbtBlue * Gy[k - i + 1][l - j + 1];
                }
            }
            // calculate the Sobel_value(pay attention: round;upper limit of 255)
            // write the value in image(array)
            image[i][j].rgbtRed = Sobel(Gx_count_Red, Gy_count_Red);
            image[i][j].rgbtGreen = Sobel(Gx_count_Green, Gy_count_Green);
            image[i][j].rgbtBlue = Sobel(Gx_count_Blue, Gy_count_Blue);
        }
    }

    return;
}

BYTE Sobel(int Gx_count,int Gy_count)
{
    float Gx_value = Gx_count / 9.0;
    float Gy_value = Gy_count / 9.0;
    int buffer = round(pow(Gx_value, 2) + pow(Gy_value, 2));
    BYTE Sobel_value;
    if (buffer > 255)
    {
        Sobel_value = 255;
    }
    else
    {
        Sobel_value = (BYTE) buffer;
    }
    return Sobel_value;
}
