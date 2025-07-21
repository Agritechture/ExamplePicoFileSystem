#include <stdio.h>
#include "pico/stdlib.h"


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
    if (f) {
        char buffer[100];
        // Read data
        if (fgets(buffer, sizeof(buffer), f)) {
            printf("Read: %s", buffer);
        }
        // Close the file
        fclose(f);
    }

    while (true) 
    {
        sleep_ms(1000);
    }
}
