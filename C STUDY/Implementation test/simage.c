#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simage.h"

void initImage(SImage *img, int width, int height)
{
    img->width = width;
    img->height = height;
    img->bpp = 3;                        // RGB
    img->size = width * height;

    // Copy a default header or zero it
    memset(img->header, 0, 138);

    img->data = malloc(img->size * img->bpp);
    if (!img->data)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

int loadImage(SImage *img, const char *name)
{
    FILE *f = fopen(name, "rb");
    if (!f)
    {
        fprintf(stderr, "Cannot open %s\n", name);
        return 0;
    }

    // Read BMP header (138 bytes)
    fread(img->header, 1, 138, f);

    // Extract width/height from header
    img->width  = *(int*)&img->header[18];
    img->height = *(int*)&img->header[22];

    img->bpp = 3;
    img->size = img->width * img->height;

    img->data = malloc(img->size * img->bpp);
    if (!img->data)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(f);
        return 0;
    }

    fread(img->data, img->bpp, img->size, f);

    fclose(f);
    return 1;
}

int saveImage(SImage *img, const char *name)
{
    FILE *f = fopen(name, "wb");
    if (!f)
    {
        fprintf(stderr, "Cannot open %s for writing\n", name);
        return 0;
    }

    fwrite(img->header, 1, 138, f);
    fwrite(img->data, img->bpp, img->size, f);

    fclose(f);
    return 1;
}

void destroyImage(SImage *img)
{
    if (img->data)
        free(img->data);
    img->data = NULL;
}
