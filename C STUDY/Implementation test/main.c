#include "simage.h"
#include <stdio.h>    // FILE, fopen, fscanf, fclose
#include <stdlib.h>   // calloc, free
#include <string.h>   // memcpy

// | File         | Purpose                           |
// | ------------ | --------------------------------- |
// | **main.c**   | Your logic using SImage           |
// | **simage.h** | Structure + function declarations |
// | **simage.c** | Implementation of BMP load/save   |

// Since each pixel has bpp bytes, one row size in bytes is: row_size = width * bpp;


int main(int argc, char **argv)
{
    SImage x, y;  
    // Declare two image objects: x = input image, y = output image.

    loadImage(&x, argv[1]);  
    // Load input.bmp from command line (argv[1]) into x.

    initImage(&y, x.width, x.height);  
    // Create y with same width/height as x and allocate pixel buffer.

    int *rearrangeArray = calloc(x.height, sizeof(int));  
    // Allocate an array of ints, one per image row (initialized to 0).

    FILE *rearrangeFile = fopen(argv[3], "r");  
    // Open rearrange.txt (argv[3]) for reading.

    for (int i = 0; i < x.height; i++)  
    {  
        fscanf(rearrangeFile, "%i\n", &rearrangeArray[i]);  
        // Read line i from rearrange.txt → tells where row i should go in output.
    }

    fclose(rearrangeFile);  
    // Close the rearrange file.

    for (int i = 0; i < x.height; i++)  
    {
        memcpy(&y.data[rearrangeArray[i] * x.width * x.bpp],  
               // Destination row in y: rearrangeArray[i] * row_size

               &x.data[i * x.width * x.bpp],  
               // Source row in x: row i starting at i * row_size

               x.width * x.bpp);  
               // Number of bytes in one row (width * 3).
    }

    saveImage(&y, argv[2]);  
    // Save output.bmp to argv[2].

    free(rearrangeArray);  
    // Free mapping array.

    destroyImage(&x);  
    // Free x.data (input image memory).

    destroyImage(&y);  
    // Free y.data (output image memory).

    return 0;  
    // Program finished successfully.
}

// loop in a more explicit way
// int row_size = x.width * x.bpp;

// for (int i = 0; i < x.height; i++)
// {
//     int src_row    = i;                    // row in x
//     int dest_row   = rearrangeArray[i];    // row in y

//     int src_offset  = src_row  * row_size; // in bytes
//     int dest_offset = dest_row * row_size; // in bytes

//     memcpy(&y.data[dest_offset],
//            &x.data[src_offset],
//            row_size);
// }
