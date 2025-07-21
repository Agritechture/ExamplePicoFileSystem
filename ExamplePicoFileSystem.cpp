#include <stdio.h>
#include "pico/stdlib.h"
#include <cstdlib>
#include <string>

int main()
{
    stdio_init_all();

     sleep_ms(1000);
    // When running in debug wait for usb
    while (!stdio_usb_connected())
    {
        sleep_ms(50);
    }

    // Open a file for writing
    FILE *f = fopen("/data.txt", "w");
    if (f) {
        // Write data
        fprintf(f, "Hello, pico-vfs!\n");
        // Close the file
        fclose(f);
    }

    // Open a file for reading
    f = fopen("/data.txt", "r");
    if (f) 
    {
        
        fseek(f, 0, SEEK_END);
        long length = ftell(f);
        rewind(f);  // Go back to beginning


        if (length <= 0) 
        {
            fclose(f);
            printf("Length was 0\n");
            return -1;
        }


        // Allocate buffer (+1 if you want to null-terminate)
        char* buffer = (char*)malloc(length + 1);
        if (!buffer) 
        {
            perror("Failed to allocate memory");
            fclose(f);
            return -1;
        }

      
        
        // Read into buffer
        size_t readCount = fread(buffer, 1, length, f);
        fclose(f);

        if (readCount != length) 
        {
            free(buffer);
            fprintf(stderr, "Incomplete read\n");
            return -1;
        }

        buffer[length] = '\0';  // Null-terminate if you're treating it as a string

        auto result = std::string(buffer);

        free(buffer);

        printf("Read result:\n");
        printf(result.c_str());

        while (true) 
        {
            sleep_ms(1000);
        }
    }
}
