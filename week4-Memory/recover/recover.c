#include <stdio.h>
#include <stdlib.h>

int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // There can only be one argument
    if (argc != 2)
    {
        printf("Unvalid number of arguments\n");
        return 1;
    }
    // Put the name of file in a variable
    char *inputName = argv[1];
    // Open the file and store it to a pointer in memory
    FILE *f = fopen(inputName, "r");
    // If there is no file
    if (f == NULL)
    {
        printf("No valid file\n");
        return 1;
    }

    // Define pointer variable to hold the output file
    FILE *outputFile = NULL;
    // create a buffer array that will hold a block of memory from file
    unsigned char buffer[BLOCK_SIZE];
    // add a counter for for jpeg file names
    int jpegCounter = 0;

    // loop throught input file and search fo jpg
    // the fread return number of bit read
    while(fread(buffer, 1, BLOCK_SIZE, f) == BLOCK_SIZE)
    {
        // if its the start of a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous outputFil
            if (outputFile != NULL)
            {
                fclose(outputFile);
            }

            // Create a new variable that will hold the name of jpg. 7 letters plus \0
            char filename[8];
            // Make a variable with dinamical name
            // the name must have minimum 3 digits
            sprintf(filename, "%03d.jpg", jpegCounter++);
            // make an outputFile
            outputFile = fopen(filename, "w");
            // wrtie the current block
            fwrite(buffer, 1, BLOCK_SIZE, outputFile);
        }
        else
        {
            // If it's not the start of a new JPEG, write the block to the current output file (if open)
            if (outputFile != NULL)
            {
              fwrite(buffer, 1, BLOCK_SIZE, outputFile);
            }
        }
    }

    // Close the last output file (if open)
    if (outputFile != NULL)
    {
       fclose(outputFile);
    }

    // Close the input file
    fclose(f);



}