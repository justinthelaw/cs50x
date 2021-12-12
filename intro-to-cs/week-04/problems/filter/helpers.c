#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      BYTE blue = image[i][j].rgbtBlue;
      BYTE red = image[i][j].rgbtRed;
      BYTE green = image[i][j].rgbtGreen;

      BYTE gray = (blue + red + green) / 3;

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

      float sepiaRed = .393 * red + .769 * green + .189 * blue;
      float sepiaGreen = .349 * red + .686 * green + .168 * blue;
      float sepiaBlue = .272 * red + .534 * green + .131 * blue;

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
  return;
}
