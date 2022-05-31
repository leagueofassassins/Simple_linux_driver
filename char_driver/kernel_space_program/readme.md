-> To run the kernel space program execute following commands in the folder of kernel_space_program.</br> 
#command sudo make </br> 
-> This command will create certain object files and a .ko file which is the kernel module object file which we are suppose to load. </br> 
#command sudo insmod simple_device_driver.ko </br> 
-> This command will insert the module into the kernel space. </br> 
-> After these steps are succesfully executed then move to run user space program. </br> 
-> Without inserting the kernel module we will not be able to open the device file. </br> 
#command dmesg </br> 
-> To see all the print statements of kernel module inserted. </br> 
