# About this repo
This repository contains a simple example of a USB driver for linux.

# Using the code
## Compiling the driver
To compile the driver module run `make` in the build directory.

## Loading the driver
### Using the script
To load the driver module using the provided script use the following command:
```
sudo sh hellousbRun.sh 1 0
```
To enable tail output set the second parameter to '1'
```
sudo sh hellousbRun.sh 1 1
```

### Without the script
To load the driver module without the use of the script use the following command:
```
sudo nsmod hellousb.ko
```

## Unloading the driver
### Using the script
To unload the driver module using the provided script use the following command:
```
sudo sh hellousbRun.sh 2 0
```
To enable tail output set the second parameter to '1'
```
sudo sh hellousbRun.sh 2 1
```

### Without the script
To load the driver module without the use of the script use the following command:
```
sudo rmmod hellousb.ko
```

## Script input options
The list of possible input/parameter combinations for the script are as follows:
```
sudo sh hellousbRun.sh x y
```
* Parameter 1 (x):
   * 0 : dmesg
   * 1 : Load module
   * 2 : Unload module
   * 3 : Load and unload moule
* Parameter 2 (y):
  * 0 : desable tail
  * 1 : enable tail

The above list can be obtained by running the following command:
```
sudo sh hellousbRun.sh
```
