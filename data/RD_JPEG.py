#!/usr/bin/python
# -*- coding: iso-8859-15 -*-

import sys
import os

command = "rm jpeg.dat"
os.system(command)

command = "cjpeg -quality 100 ../lena.ppm > lena.jpg"
os.system(command)

bytes = 1000
while bytes < 212175:

    command = "printf " + str(bytes) + " >> jpeg.dat"
    os.system(command)

    command = "printf \" \" >> jpeg.dat"
    os.system(command)

    command = "dd if=lena.jpg of=1.jpg bs=1 count=" + str(bytes)
    os.system(command)

    command = "djpeg 1.jpg > 1.ppm"
    os.system(command)

    command = "(snr --type=uchar --peak=255 --file_A=../lena.ppm --file_B=1.ppm --block_size=786447 | grep PSNR[db]) 2>> jpeg.dat"
    os.system(command)
    
    bytes += 1000
