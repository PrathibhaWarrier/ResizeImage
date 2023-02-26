#include <stdio.h>
#include <stdlib.h>
#include "jpegsr6b/jpeg-6b/jconfig.h"
#include "jpegsr6b/jpeg-6b/jpeglib.h"

typedef struct {
    unsigned char r, g, b;
} RGB;

int main() {
    // Open the JPEG file
    FILE* infile = fopen("input.jpg", "rb");
    if (!infile) {
        printf("Error opening input file\n");
        return 1;
    }

    // Initialize the JPEG decompression object
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);

    // Start the JPEG decompression process
    jpeg_start_decompress(&cinfo);

    // Allocate memory for the raw RGB data
    const int width = cinfo.output_width;
    const int height = cinfo.output_height;
    RGB* image = (RGB*) malloc(width * height * sizeof(RGB));

    // Read the scanlines and convert to RGB
    while (cinfo.output_scanline < cinfo.output_height) {
        JSAMPROW row_pointer[1];
        row_pointer[0] = (JSAMPROW) &image[cinfo.output_scanline * width];
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
    }

    // Finish the JPEG decompression process
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    // Save the raw RGB data to a file
    FILE* outfile = fopen("output.rgb", "wb");
    fwrite(image, sizeof(RGB), width * height, outfile);
    fclose(outfile);

    // Free the memory
    free(image);

    return 0;
}
