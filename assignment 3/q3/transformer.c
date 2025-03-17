#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Collaborated with: Muhammad Ayaan Hafeez

#define IMG_MAX_WIDTH 1000    // Maximum allowed width for the image
#define IMG_MAX_HEIGHT 1000   // Maximum allowed height for the image

// Structure representing a single pixel with red, green, and blue color components.
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

// Global image matrix to store pixel data, using the maximum dimensions defined.
Pixel imgMatrix[IMG_MAX_HEIGHT][IMG_MAX_WIDTH];
// Global variables for the actual image dimensions read from the file.
int imgWidth, imgHeight;

// Reads a PPM image from standard input.
void readPPM() {
    char ppmFormat[3];   // Buffer for the PPM format string (should be "P3")
    int maxColorValue;   // The maximum color value (should be 255)

    // Read the image format header.
    scanf("%s", ppmFormat);
    if (strcmp(ppmFormat, "P3") != 0) {
        fprintf(stderr, "Unsupported format\n");
        exit(1);
    }

    // Read image dimensions (width and height).
    scanf("%d %d", &imgWidth, &imgHeight);
    
    // Read the maximum color value.
    scanf("%d", &maxColorValue);
    if (maxColorValue != 255) {
        fprintf(stderr, "Unsupported max color value\n");
        exit(1);
    }

    // Read the pixel data for each position in the image matrix.
    for (int row = 0; row < imgHeight; row++) {
        for (int col = 0; col < imgWidth; col++) {
            scanf("%hhu %hhu %hhu", &imgMatrix[row][col].r, &imgMatrix[row][col].g, &imgMatrix[row][col].b);
        }
    }
}

// Flips the image horizontally.
void flipImage() {
    // For each row in the image...
    for (int row = 0; row < imgHeight; row++) {
        // Swap pixels from the left half with the corresponding pixels from the right half.
        for (int col = 0; col < imgWidth / 2; col++) {
            Pixel temp = imgMatrix[row][col];
            imgMatrix[row][col] = imgMatrix[row][imgWidth - 1 - col];
            imgMatrix[row][imgWidth - 1 - col] = temp;
        }
    }
}

// Applies a sepia filter to the image.
void applySepiaFilter() {
    // Process each pixel in the image.
    for (int row = 0; row < imgHeight; row++) {
        for (int col = 0; col < imgWidth; col++) {
            // Save the original color values.
            unsigned char origRed = imgMatrix[row][col].r;
            unsigned char origGreen = imgMatrix[row][col].g;
            unsigned char origBlue = imgMatrix[row][col].b;

            // Calculate the new red value using the sepia formula and clamp to 255.
            imgMatrix[row][col].r = (unsigned char)((origRed * 0.393 + origGreen * 0.769 + origBlue * 0.189) > 255 ? 255 : (origRed * 0.393 + origGreen * 0.769 + origBlue * 0.189));
            // Calculate the new green value using the sepia formula and clamp to 255.
            imgMatrix[row][col].g = (unsigned char)((origRed * 0.349 + origGreen * 0.686 + origBlue * 0.168) > 255 ? 255 : (origRed * 0.349 + origGreen * 0.686 + origBlue * 0.168));
            // Calculate the new blue value using the sepia formula and clamp to 255.
            imgMatrix[row][col].b = (unsigned char)((origRed * 0.272 + origGreen * 0.534 + origBlue * 0.131) > 255 ? 255 : (origRed * 0.272 + origGreen * 0.534 + origBlue * 0.131));
        }
    }
}

// Writes the image in PPM format to standard output.
void writePPM() {
    // Output the PPM header.
    printf("P3\n%d %d\n255\n", imgWidth, imgHeight);
    // Output each pixel's color data.
    for (int row = 0; row < imgHeight; row++) {
        for (int col = 0; col < imgWidth; col++) {
            printf("%d %d %d ", imgMatrix[row][col].r, imgMatrix[row][col].g, imgMatrix[row][col].b);
        }
        printf("\n");
    }
}

// Main function: processes command line arguments and applies transformations.
int main(int argc, char *argv[]) {
    int doFlip = 0, doSepia = 0;

    // Parse command line arguments for transformation options.
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            doFlip = 1;    // Set flag to flip the image horizontally.
        } else if (strcmp(argv[i], "-s") == 0) {
            doSepia = 1;   // Set flag to apply the sepia filter.
        }
    }

    // Read the PPM image from standard input.
    readPPM();

    // Apply the flip transformation if the flag is set.
    if (doFlip) {
        flipImage();
    }
    // Apply the sepia filter if the flag is set.
    if (doSepia) {
        applySepiaFilter();
    }

    // Output the transformed image.
    writePPM();

    return 0;
}