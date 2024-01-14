
#include <stdio.h>
#include <stdlib.h>

#define SIZE 2
#define STARTPIXELS 10
#define WIDTH 18
#define HEIGHT 22
#define IMAGESIZE 34

int main() {
    char headers[54];
    char *otherdata;
    char *pixeldata;
    int read = fread(headers, sizeof(char), 54, stdin);
    if (read < 54) {
        exit(1);
    }
    if (headers[0] != 'B' || headers[1] != 'M') {
        exit(1);
    }

    int filesize, pixelstart, width, height, imagesize;
    filesize = *(unsigned int *)(headers + SIZE);
    pixelstart = *(unsigned int *)(headers + STARTPIXELS);
    width = *(unsigned int *)(headers + WIDTH);
    height = *(unsigned int *)(headers + HEIGHT);
    imagesize = *(unsigned int *)(headers + IMAGESIZE);
    int diafora = pixelstart - 54;
    otherdata = malloc(diafora * sizeof(char));
    fread(otherdata, sizeof(char), diafora, stdin);
    pixeldata = malloc(imagesize * sizeof(char));
    fread(pixeldata, sizeof(char), imagesize, stdin);

    // Create a 3D array to represent the image
    char ***image = malloc(height * sizeof(char **));
    for (int i = 0; i < height; i++) {
        image[i] = malloc(width * sizeof(char *));
        for (int j = 0; j < width; j++) {
            image[i][j] = malloc(3 * sizeof(char));
        }
    }

    // Populate the 3D array with pixel data
    int count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                if (pixeldata[count] == '\0') {
                    count++;
                    continue;
                }
                image[i][j][k] = pixeldata[count];
                count++;
            }
        }
    }

    // Create a 3D array for the rotated image
    int new_height = width;
    int new_width = height;
    char ***rotated = malloc(new_height * sizeof(char **));
    for (int i = 0; i < new_height; i++) {
        rotated[i] = malloc(new_width * sizeof(char *));
        for (int j = 0; j < new_width; j++) {
            rotated[i][j] = malloc(3 * sizeof(char));
        }
    }

    // Perform the rotation
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                rotated[width -1-j][i][k] = image[i][j][k];
            }
        }
    }

    int padding = (new_width*3)%4;

    // Update header for the rotated image
    *(unsigned int *)(headers + WIDTH) = new_width;
    *(unsigned int *)(headers + HEIGHT) = new_height;
    *(unsigned int *)(headers + SIZE) = 54 + diafora + (new_width * 3 * new_height) + (padding * new_height);
    *(unsigned int *)(headers + IMAGESIZE) = (new_width * 3 * new_height) + (padding * new_height * 3);

    // Write the updated header to stdout
    fwrite(headers, sizeof(char), 54, stdout);
    fwrite(otherdata, sizeof(char), diafora, stdout);

    // Write the rotated image to stdout
    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            for (int k = 0; k < 3; k++) {
                putchar(rotated[i][j][k]);
            }
        }
        for (int k = 0; k < padding; k++) {
            putchar('\0');
        }
    }

    // Free allocated memory
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            free(rotated[i][j]);
        }
        free(rotated[i]);
    }
    free(rotated);

    free(otherdata);
    free(pixeldata);

    return 0;
}

