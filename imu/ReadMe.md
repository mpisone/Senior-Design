This is the code needs to measure imu measurement. 

Before start, we need to install 3 libraries in C++ environment. (Depending on systems we use, some of the libraries may be already there)

In ubuntu, the command to install is 
sudo apt install libi2c-dev
sudo apt install libi2c0
sudo apt install i2c-tools

Then, in order to install IMU unit required functions, we need to go to the directory of the code in terminal/cmd line, they type

make install


To run the code, type 

make run
sudo ./imu


*Note: sudo is to take the administrative control to run something. Some of the commands require administrative level operation. 
*If there is any other operations without "sudo" in code, and that appear administrative control to run it, simply add "sudo" infront of the command.