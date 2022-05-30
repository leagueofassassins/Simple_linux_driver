# Simple_linux_driver
->In this application a simple linux driver is created. 
->Two applications are created one is part of Kernel Space and another one is part of User Space.
->The user Program will communicate with the kernel space program using the device file.
->Using this driver we can send string or data to the kernel device driver using the write function. It will store that string in the kernel space. Then    when we read the device file, it will send the data which is written by write by function to the userspace application.

# Output of Command dmesg 
[ 3292.073046] simple_linux_driver: loading out-of-tree module taints kernel.
[ 3292.073098] simple_linux_driver: module verification failed: signature and/or required key missing - tainting kernel
[ 3292.073581] Major = 234 Minor = 0 
[ 3418.631679] Device File Opened...!!!
[ 3434.553499] Write Function
[ 3434.553516] Read function

# output of User application program
$ sudo ./user_app
[sudo] password for ixm: 
Enter the string to write into driver :hello this is a simple linux driver
Data Writing ...Done!
Data Reading ...Done!

Data = hello this is a simple linux driver

Enter the string to write into driver :
