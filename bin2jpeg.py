# -*- coding: utf-8 -*-
"""
Created on Sun Feb 26 22:21:48 2023

@author: PRATHIBHA
"""

from PIL import Image
import numpy as np


import os

file_size = os.path.getsize("kobe4.bin")
print("Input file size: ", file_size)


# open binary file
with open('kobe4.bin', 'rb') as f:
    # read binary data
    data = np.fromfile(f, dtype=np.uint8)
    
# reshape data into image dimensions
img = Image.fromarray(np.reshape(data, (320, 240, 3)), 'RGB')

# save image as JPEG
img.save('output2.jpg')
