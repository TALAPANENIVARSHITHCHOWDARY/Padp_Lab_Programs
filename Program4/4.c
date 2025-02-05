#include <stdio.h>
#include <gd.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    omp_set_num_threads(4); // Set 4 threads for OpenMP
    int tid, temp, x, y, w, h, red, blue, green, color;
    temp = red = blue = green = w = x = y = h = color = 0;

    // Argument check
    if (argc != 3) {
        printf("Usage: %s <input.png> <output.png>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    char *output = argv[2];

    // Open input file
    FILE *fp = fopen(input, "r");
    if (!fp) {
        printf("Error: Unable to open input file '%s'\n", input);
        return 1;
    }

    // Load image
    gdImagePtr img = gdImageCreateFromPng(fp);
    fclose(fp); // Close input file after loading

    if (!img) {
        printf("Error: Unable to create image from file\n");
        return 1;
    }

    // Get image dimensions
    w = gdImageSX(img);
    h = gdImageSY(img);
    printf("Width: %d, Height: %d\n", w, h);

    // Start timing
    double t1 = omp_get_wtime();

    // Parallel loop for image processing
    #pragma omp parallel for schedule(guided, 100)
    for (x = 0; x < w; x++) {
        for (y = 0; y < h; y++) {
            tid = omp_get_thread_num(); // Get thread ID

            // Get pixel color
            color = gdImageGetPixel(img, x, y);
            red = gdImageRed(img, color);
            blue = gdImageBlue(img, color);
            green = gdImageGreen(img, color);

            // Convert to grayscale
            temp = (red + blue + green) / 3;

            // Apply different color filters based on thread ID
            if (tid == 0) {
                color = gdImageColorAllocate(img, temp, 0, 0); // Red filter
            } else if (tid == 1) {
                color = gdImageColorAllocate(img, 0, temp, 0); // Green filter
            } else if (tid == 2) {
                color = gdImageColorAllocate(img, 0, 0, temp); // Blue filter
            } else {
                color = gdImageColorAllocate(img, temp, temp, temp); // Grayscale
            }

            // Set modified pixel
            gdImageSetPixel(img, x, y, color);
        }
    }

    // End timing
    double t = omp_get_wtime() - t1;
    printf("Time taken: %.4f seconds\n", t);

    // Open output file
    fp = fopen(output, "w");
    if (!fp) {
        printf("Error: Unable to open output file '%s'\n", output);
        gdImageDestroy(img);
        return 1;
    }

    // Save processed image
    gdImagePng(img, fp);
    fclose(fp); // Close output file
    gdImageDestroy(img); // Free memory

    return 0;
}
