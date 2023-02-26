#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define VGA_WIDTH 640
#define VGA_HEIGHT 480
#define QVGA_WIDTH 320
#define QVGA_HEIGHT 240

int main()
{
    // Open input file
    FILE *input_file = fopen("kobe.jpg", "rb");
    if (!input_file) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    // Open output file
    FILE *output_file = fopen("kobe4.bin", "wb");
    if (!output_file) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    // Allocate memory for input and output buffers
    uint8_t *input_buffer = malloc(VGA_WIDTH * VGA_HEIGHT * 3);
    uint8_t *output_buffer = malloc(QVGA_WIDTH * QVGA_HEIGHT * 3);

    // Read input buffer
    fread(input_buffer, sizeof(uint8_t), VGA_WIDTH * VGA_HEIGHT, input_file);

    // Convert VGA to QVGA
    for (int y = 0; y < QVGA_HEIGHT; y++) {
        for (int x = 0; x < QVGA_WIDTH; x++) {
            int vga_x = x * 2;
            int vga_y = y * 2;
            int qvga_index = y * QVGA_WIDTH + x;
            int vga_index1 = vga_y * VGA_WIDTH + vga_x;
            int vga_index2 = vga_y * VGA_WIDTH + vga_x + 1;
            int vga_index3 = (vga_y + 1) * VGA_WIDTH + vga_x;
            int vga_index4 = (vga_y + 1) * VGA_WIDTH + vga_x + 1;
            int vga_value1 = input_buffer[vga_index1];
            int vga_value2 = input_buffer[vga_index2];
            int vga_value3 = input_buffer[vga_index3];
            int vga_value4 = input_buffer[vga_index4];
            int qvga_value = (vga_value1 + vga_value2 + vga_value3 + vga_value4) / 4;
            output_buffer[qvga_index] = (uint8_t) qvga_value;
        }
    }

    // Write output buffer
    fwrite(output_buffer, sizeof(uint8_t), QVGA_WIDTH * QVGA_HEIGHT, output_file);

    // Clean up
    free(input_buffer);
    free(output_buffer);
    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}
