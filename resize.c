#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

int main() {
    // Load image
    int width, height, channels;
    unsigned char *image = stbi_load("kobe.jpg", &width, &height, &channels, STBI_rgb_alpha);
    if (!image) {
        printf("Error loading image\n");
        return 1;
    }

    // Resize image
    int new_width = width / 2;
    int new_height = height / 2;
    unsigned char *resized_image = malloc(new_width * new_height * channels);
    stbir_resize_uint8(image, width, height, 0, resized_image, new_width, new_height, 0, STBI_rgb_alpha);

    // Save resized image
    stbi_write_jpg("output.jpg", new_width, new_height, channels, resized_image, 100);

    // Free memory
    stbi_image_free(image);
    free(resized_image);

    return 0;
}
