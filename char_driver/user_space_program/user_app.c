#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int8_t write_buf[1024];
int8_t read_buf[1024];
int main()
{
        int fd;
        char option;
        fd = open("/dev/character_driver_device", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }
        while(1) {
    
            printf("Enter the string to write into driver :");
            scanf(" %[^\t\n]s", write_buf);
            printf("Data Writing ...");
            /* When below function is executed the character_driver_write from kernel space
               function is called to write the data to the character_driver_device file*/
            write(fd, write_buf, strlen(write_buf)+1); 
            printf("Done!\n");


            printf("Data Reading ...");
            /* When below function is executed the character_driver_read from kernel space
               function is called to read the data from the character_driver_device file 
               Here you will receive the same string you passed to the write function */
            read(fd, read_buf, 1024);
            printf("Done!\n\n");
            printf("Data = %s\n\n", read_buf);

        }
    close(fd);
}
        
