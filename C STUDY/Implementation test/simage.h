#ifndef SIMAGE_H
#define SIMAGE_H

/*
    A simple structure and functions for reading and writing basic bitmap formats.
    Each pixel is represented by three bytes (R, G, B).
    The image data is stored in a 1D array: the G component of pixel (x, y) is at
    index (width * y + x) * 3 + 1.
*/

typedef struct
{
    int width;                  // image width in pixels
    int height;                 // image height in pixels
    int size;                   // number of pixels
    int bpp;                    // bytes per pixel
    unsigned char header[138];  // BMP header data
    unsigned char* data;        // pixel data (RGB)
} SImage;

/* Initialise image and allocate memory */
void initImage(SImage *img, int width, int height);

/* Load BMP image from file; allocates memory */
int loadImage(SImage *img, const char* name);

/* Save BMP image to file */
int saveImage(SImage *img, const char* name);

/* Free memory used by SImage */
void destroyImage(SImage *img);

#endif // SIMAGE_H
