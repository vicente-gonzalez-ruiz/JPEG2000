#!/usr/bin/python
# -*- coding: iso-8859-15 -*-

import sys
import os

command = "rm jpeg2000-1.dat"
os.system(command)

command = "kdu_compress -i ../lena.ppm -o lena-1.j2c -rate 6.5379307176"
os.system(command)

bytes = 1000
while bytes < 212175:

    command = "printf " + str(bytes) + " >> jpeg2000-1.dat"
    os.system(command)

    command = "printf \" \" >> jpeg2000-1.dat"
    os.system(command)

    command = "dd if=lena-1.j2c of=1.j2c bs=1 count=" + str(bytes)
    os.system(command)

    command = "kdu_expand -i 1.j2c -o 1.ppm"
    os.system(command)

    command = "(snr --type=uchar --peak=255 --file_A=../lena.ppm --file_B=1.ppm --block_size=786447 | grep PSNR[db]) 2>> jpeg2000-1.dat"
    os.system(command)
    
    bytes += 1000
