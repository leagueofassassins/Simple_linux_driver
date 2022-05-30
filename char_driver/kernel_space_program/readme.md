-> To run the kernel space program execute following commands in the folder of kernel_space_program.
#command sudo make
-> This command will create certain object files and a .ko file which is the kernel module object file which we are suppose to load.
#command sudo insmod simple_device_driver.ko
-> This command will insert the module into the kernel space.
-> After these steps are succesfully executed then move to run user space program.
-> Without inserting the kernel module we will not be able to open the device file.
#command dmesg
-> To see all the print statements of kernel module inserted.
