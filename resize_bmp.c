#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

int main()
{
    // Open the input file
    FILE* infile = fopen("bird2.bmp", "rb");
    if (!infile)
    {
        printf("Error: could not open input file\n");
        return 1;
    }

    // Read the BMP header
    BYTE header[54];
    fread(header, sizeof(BYTE), 54, infile);

    // Read the image dimensions
    int width = *(int*)&header[18];
    int height = *(int*)&header[22];

    // Allocate memory for the input and output images
    int input_size = width * height * 3;
    BYTE* input = (BYTE*)malloc(input_size);
    BYTE* output = (BYTE*)malloc(input_size * 4);

    // Read the input image
    fread(input, sizeof(BYTE), input_size, infile);
    fclose(infile);

    // Resize the image by a factor of 2
    int new_width = width * 2;
    int new_height = height * 2;

    for (int y = 0; y < new_height; y++)
    {
        for (int x = 0; x < new_width; x++)
        {
            int input_x = x / 2;
            int input_y = y / 2;

            int input_index = (input_y * width + input_x) * 3;
            int output_index = (y * new_width + x) * 3;

            output[output_index] = input[input_index];
            output[output_index + 1] = input[input_index + 1];
            output[output_index + 2] = input[input_index + 2];
        }
    }

    // Open the output file
    FILE* outfile = fopen("output2.bmp", "wb");
    if (!outfile)
    {
        printf("Error: could not open output file\n");
        return 1;
    }

    // Write the BMP header
    fwrite(header, sizeof(BYTE), 54, outfile);

    // Write the output image
    fwrite(output, sizeof(BYTE), input_size * 4, outfile);
    fclose(outfile);

    // Free memory
    free(input);
    free(output);

    return 0;
}
