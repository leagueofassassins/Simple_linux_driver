# Simple_linux_driver
->In this application a simple linux driver is created.</br> 
->Two applications are created one is part of Kernel Space and another one is part of User Space.</br> 
->The user Program will communicate with the kernel space program using the device file.</br> 
->Using this driver we can send string or data to the kernel device driver using the write function. It will store that string in the kernel space. Then    when we read the device file, it will send the data which is written by write by function to the userspace application.</br> 

# Output of Command dmesg 
[ 3292.073046] simple_linux_driver: loading out-of-tree module taints kernel.</br> 
[ 3292.073098] simple_linux_driver: module verification failed: signature and/or required key missing - tainting kernel</br> 
[ 3292.073581] Major = 234 Minor = 0 </br> 
[ 3418.631679] Device File Opened...!!! </br> 
[ 3434.553499] Write Function </br> 
[ 3434.553516] Read function </br> 

# output of User application program
$ sudo ./user_app </br> 
[sudo] password for user: </br> 
Enter the string to write into driver :hello this is a simple linux driver </br> 
Data Writing ...Done! </br> 
Data Reading ...Done! </br> 

Data = hello this is a simple linux driver </br> 

Enter the string to write into driver : </br> 
