Docs are here:
https://deepwiki.com/oyama/pico-vfs/1.2-getting-started

TLDR

Step 1:
    Add the FS as Git submodule, ensure in root directory:
        git submodule add https://github.com/oyama/pico-vfs.git

    then:
        git submodule update --init --recursive

Step 2:
    Add the FS in CMakeLists.txt:

        # Include pico-vfs directory
        add_subdirectory(pico-vfs)

        # Your application
        add_executable(TestFileSystem TestFileSystem.cpp)

        # Link pico-vfs libraries
        target_link_libraries(TestFileSystem PRIVATE
            pico_stdlib
            blockdevice_flash
            filesystem_littlefs
            filesystem_vfs
        )

        # Enable filesystem with default configuration
        pico_enable_filesystem(TestFileSystem AUTO_INIT 1)


Step 3:
    Basic read/write:
        
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
