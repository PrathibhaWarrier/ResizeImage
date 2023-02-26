#include <stdio.h> 
    #include "jpegsr6b/jpeg-6b/jconfig.h"
    // #include "/jpegsr9e/jpeg-9e/jpeglib.h"

    int main() { 
        // Open the input and output files 
        FILE *infile = fopen("wallpaper.jpg", "rb"); 
        FILE *outfile = fopen("output.jpg", "wb"); 

        // Allocate the compression and decompression structures 
        struct jpeg_compress_struct cinfo; 
        struct jpeg_error_mgr jerr; 

        // Set up the error handling 
        cinfo.err = jpeg_std_error(&jerr); 
        jpeg_create_compress(&cinfo); 

        // Set the destination for the compressed data 
        jpeg_stdio_dest(&cinfo, outfile); 

        // Set the compression parameters 
        cinfo.image_width = 800; 
        cinfo.image_height = 600; 
        cinfo.input_components = 3; 
        cinfo.in_color_space = JCS_RGB; 
        jpeg_set_defaults(&cinfo); 
        jpeg_set_quality(&cinfo, 75, TRUE); 

        // Start the compression process 
        jpeg_start_compress(&cinfo, TRUE); 

        // Allocate a buffer for reading the image data 
        int row_stride = cinfo.image_width * 3; 
        JSAMPROW row_pointer[1]; 
        row_pointer[0] = new JSAMPLE[row_stride]; 

        // Read the image data and write it to the output file 
        while (cinfo.next_scanline < cinfo.image_height) { 
            fread(row_pointer[0], 1, row_stride, infile); 
            jpeg_write_scanlines(&cinfo, row_pointer, 1); 
        } 

        // Finish the compression process 
        jpeg_finish_compress(&cinfo); 

        // Clean up 
        jpeg_destroy_compress(&cinfo); 
        fclose(outfile); 
        fclose(infile); 

        return 0; 
    }