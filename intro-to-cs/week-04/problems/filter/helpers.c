#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      float blue = image[i][j].rgbtBlue;
      float red = image[i][j].rgbtRed;
      float green = image[i][j].rgbtGreen;

      float gray = round((blue + red + green) / 3);

      image[i][j].rgbtBlue = gray;
      image[i][j].rgbtRed = gray;
      image[i][j].rgbtGreen = gray;
    }
  }
  return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      BYTE blue = image[i][j].rgbtBlue;
      BYTE red = image[i][j].rgbtRed;
      BYTE green = image[i][j].rgbtGreen;

      float sepiaRed = round(.393 * red + .769 * green + .189 * blue);
      float sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
      float sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

      if ((int)sepiaRed > 255)
      {
        sepiaRed = 255.0;
      }
      if ((int)sepiaGreen > 255)
      {
        sepiaGreen = 255.0;
      }
      if ((int)sepiaBlue > 255)
      {
        sepiaBlue = 255.0;
      }

      image[i][j].rgbtBlue = (int)sepiaBlue;
      image[i][j].rgbtRed = (int)sepiaRed;
      image[i][j].rgbtGreen = (int)sepiaGreen;
    }
  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width / 2; j++)
    {
      int k = width - (j + 1);
      RGBTRIPLE opposite = image[i][j];
      image[i][j] = image[i][k];
      image[i][k] = opposite;
    }
  }
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
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
      float totalRed;
      float totalBlue;
      float totalGreen;
      int pixelCount;
      totalRed = totalBlue = totalGreen = pixelCount = 0;

      for (int h = -1; h < 2; h++)
      {
        for (int w = -1; w < 2; w++)
        {
          if (i + h < 0 || i + h >= height)
          {
            continue;
          }
          if (j + w < 0 || j + w >= width)
          {
            continue;
          }
          totalRed += copy[i + h][j + w].rgbtRed;
          totalBlue += copy[i + h][j + w].rgbtBlue;
          totalGreen += copy[i + h][j + w].rgbtGreen;
          pixelCount++;
        }
      }

      image[i][j].rgbtRed = round(totalRed / pixelCount);
      image[i][j].rgbtGreen = round(totalGreen / pixelCount);
      image[i][j].rgbtBlue = round(totalBlue / pixelCount);
    }
  }
  return;
}
