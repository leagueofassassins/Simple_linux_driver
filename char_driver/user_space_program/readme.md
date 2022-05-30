-> Use the below line to compile the user space program
gcc -o user_app user_app.c
-> To run the user space program use below line 
sudo ./user_app
-> when we write the data to the device file character_driver_write() function is called from kernel space.
-> when we read the data from the device file character_driver_read() function is called from kernel space. 
