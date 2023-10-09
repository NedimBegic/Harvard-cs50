#include "helpers.h"
#include <stdio.h>
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop throught the height image
    for (int i = 0; i < height; i++)
    {
        // loop throught the width of image
        for (int j = 0; j < width; j++)
        {
            // Find the average of red, green, blue for that pixel
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            // set all colors to the average
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through the height of the image
    for (int i = 0; i < height; i++)
    {
        // Loop through the width of the image
        for (int j = 0; j < width; j++)
        {
            int red = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int green = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int blue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // Clamp values to [0, 255]
            image[i][j].rgbtRed = (red > 255) ? 255 : (red < 0) ? 0 : red;
            image[i][j].rgbtGreen = (green > 255) ? 255 : (green < 0) ? 0 : green;
            image[i][j].rgbtBlue = (blue > 255) ? 255 : (blue < 0) ? 0 : blue;
        }
    }
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // half the width
    int halfWidth = width / 2;
    // loop throught the height image
    for (int i = 0; i < height; i++)
    {
        // loop throught the width of image
        for (int j = 0; j < halfWidth; j++)
        {
           // take first and move it to last
           RGBTRIPLE temp = image[i][j];
           image[i][j] = image[i][width - j - 1];
           image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary image to store the blurred result
    RGBTRIPLE temp[height][width];

    // Loop through the height of the image
    for (int i = 0; i < height; i++)
    {
        // Loop through the width of the image
        for (int j = 0; j < width; j++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            int count = 0;

            // Loop through the 3x3 neighborhood around the pixel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if the neighboring pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        red += image[ni][nj].rgbtRed;
                        green += image[ni][nj].rgbtGreen;
                        blue += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average values and store in the temporary image
            temp[i][j].rgbtRed = round((float)red / count);
            temp[i][j].rgbtGreen = round((float)green / count);
            temp[i][j].rgbtBlue = round((float)blue / count);
        }
    }

    // Copy the blurred result back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

