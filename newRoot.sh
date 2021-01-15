#!/bin/bash

#KHADIM Meriem & EL OUADI Abdelati IRISI2

#  Creating a new repository which will be the new root of our namespace
mkdir host 

 # Creating new repositories that will hold the binary files, which are the actual executable code to run multiple commands
mkdir host/bin
mkdir host/lib
mkdir host/lib64
mkdir host/usr


# Creating the proc repository which is gonna be the mout point of the namespace,also it will contain the image memory of the namespace.
mkdir host/proc


sudo cp -r /bin/* host/bin
sudo cp -r /lib/* host/lib
sudo cp -r /lib64/* host/lib64
sudo cp -r /usr/* host/usr

mv testForMem.c host/
mv testForPids.c host/

 #Executing the files in Host directory
gcc -o host/testForMem host/testForMem.c
gcc -o host/testForPids host/testForPids.c
