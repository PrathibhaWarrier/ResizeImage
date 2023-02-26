#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint8_t r, g, b;
} RGB;

RGB* resize_image(RGB* image, int width, int height, float scale_factor, int* new_width, int* new_height) {
    *new_width = (int)(width * scale_factor);
    *new_height = (int)(height * scale_factor);

    RGB* resized_image = (RGB*) malloc((*new_width) * (*new_height) * sizeof(RGB));

    for (int i = 0; i < *new_height; i++) {
        for (int j = 0; j < *new_width; j++) {
            float x = (float) j / scale_factor;
            float y = (float) i / scale_factor;

            int x1 = (int) x;
            int y1 = (int) y;
            int x2 = x1 + 1;
            int y2 = y1 + 1;

            float alpha = x - x1;
            float beta = y - y1;

            if (x2 >= width) x2 = width - 1;
            if (y2 >= height) y2 = height - 1;

            RGB c1 = image[y1 * width + x1];
            RGB c2 = image[y1 * width + x2];
            RGB c3 = image[y2 * width + x1];
            RGB c4 = image[y2 * width + x2];

            RGB c = {
                (uint8_t)(c1.r * (1 - alpha) * (1 - beta) + c2.r * alpha * (1 - beta) + c3.r * beta * (1 - alpha) + c4.r * alpha * beta),
                (uint8_t)(c1.g * (1 - alpha) * (1 - beta) + c2.g * alpha * (1 - beta) + c3.g * beta * (1 - alpha) + c4.g * alpha * beta),
                (uint8_t)(c1.b * (1 - alpha) * (1 - beta) + c2.b * alpha * (1 - beta) + c3.b * beta * (1 - alpha) + c4.b * alpha * beta),
            };

            resized_image[i * (*new_width) + j] = c;
        }
    }

    return resized_image;
}

int main() {
    // Load image data
    FILE* f = fopen("image.rgb", "rb");
    int width = 640, height = 480;
    RGB* image = (RGB*) malloc(width * height * sizeof(RGB));
    fread(image, sizeof(RGB), width * height, f);
    fclose(f);

    // Resize image
    float scale_factor = 0.5f;
    int new_width, new_height;
    RGB* resized_image = resize_image(image, width, height, scale_factor, &new_width, &new_height);

    // Save resized image data
    FILE* g = fopen("resized_image.rgb", "wb");
    fwrite(resized_image, sizeof(RGB), new_width * new_height, g);
    fclose(g);

    // Free memory
    free(image);
    free(resized_image);

    return 0;
}
