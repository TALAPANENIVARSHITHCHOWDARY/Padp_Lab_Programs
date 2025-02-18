#include<gd.h>
#include<stdio.h>
#include<omp.h>

int main(int argc, char *argv[]){
    omp_set_num_threads(4);  // Set the number of threads for OpenMP to 4
    int tid, temp, x, y, w, h, red, blue, green, color;
    temp = red = blue = green = x = y = w = h = color = 0;  // Initialize variables

    // Check if the correct number of command-line arguments are provided
    if(argc != 3){
        printf("Usage: %s <input.png> <output.png>\n", argv[0]);
        return 1;  // Exit if arguments are not sufficient
    }

    // Input and output file paths from command-line arguments
    char *input = argv[1];
    char *output = argv[2];

    // Open the input PNG file for reading
    FILE *fp = fopen(input, "r");
    if (!fp) {
        printf("Failed to open input file\n");
        return 1;
    }

    // Create an image pointer from the PNG file
    gdImagePtr img = gdImageCreateFromPng(fp);
    if (img == NULL) {
        printf("Failed to create image from file\n");
        fclose(fp);
        return 1;
    }

    // Get the width and height of the image
    w = gdImageSX(img);
    h = gdImageSY(img);
    printf("Width: %d, Height: %d\n", w, h);

    // Start the timer for performance measurement
    double t = omp_get_wtime();

    // Parallelize the pixel manipulation using OpenMP
    #pragma omp parallel for schedule(guided, 100) // Schedule work in guided chunks of size 100
    for(x = 0; x < w; x++){
        for(y = 0; y < h; y++){
            tid = omp_get_thread_num();  // Get the current thread ID
            color = gdImageGetPixel(img, x, y);  // Get the RGB value of the pixel

            // Extract the red, green, and blue components from the pixel
            red = gdImageRed(img, color);
            blue = gdImageBlue(img, color);
            green = gdImageGreen(img, color);

            // Convert the RGB value to greyscale using the average method
            temp = (red + blue + green) / 3;

            // Assign a new color to the pixel depending on the thread ID
            if(tid == 0){
                color = gdImageColorAllocate(img, temp, 0, 0);  // Red scale
            } else if(tid == 1){
                color = gdImageColorAllocate(img, 0, temp, 0);  // Green scale
            } else if(tid == 2){
                color = gdImageColorAllocate(img, 0, 0, temp);  // Blue scale
            } else {
                color = gdImageColorAllocate(img, temp, temp, temp);  // Greyscale
            }

            // Set the new color to the current pixel
            gdImageSetPixel(img, x, y, color);
        }
    }

    // Stop the timer and calculate the time taken for processing
    t = omp_get_wtime() - t;
    printf("Time taken: %f\n", t);  // Print the time taken to process the image

    // Open the output file for writing
    fp = fopen(output, "w");
    if (!fp) {
        printf("Failed to open output file\n");
        gdImageDestroy(img);
        return 1;
    }

    // Write the processed image to the output file in PNG format
    gdImagePng(img, fp);

    // Clean up and free the memory used by the image
    gdImageDestroy(img);
    fclose(fp);

    return 0;
}
