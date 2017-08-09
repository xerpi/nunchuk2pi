nunchuk2pi
==========

Connect Wii nunchuk to the Raspberry Pi (Linux)

Getting started
===============

Make sure you have everything you need for I2C.

    sudo apt-get install i2c-tools libi2c-dev
    
Activate I2C in the Raspberry Pi config:

    sudo raspi-config
   
Go to interfacing options and I2C, choose to enable it.

To compile the nunchuk2pi code, go to the directory where you unpacked it and write:

    make

To run it:

    sudo ./n2pi
    
    
