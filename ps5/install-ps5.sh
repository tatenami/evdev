#!/bin/bash

g++ -shared -fPIC -o libps5.so ../Pad*.cpp ps5.cpp
sudo cp ps5.hpp /usr/local/include

sudo cp libps5.so /lib64
sudo cp libps5.so /usr/lib/pad
sudo cp libps5.so /lib/pad

sudo install libps5.so /usr/local/lib
sudo ldconfig

rm ./libps5.so
