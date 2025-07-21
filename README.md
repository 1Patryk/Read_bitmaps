# Project name: Read_bitmaps

This project is a tools for modification files (images) in "BMP" format.

## Bitmap format structure

The bitmap (.bmp) format consists of three structures: BITMAP_header, DIB_header and RGB values:

### BITMAP_header

| Offset (hex)    | Offset (dec) | Size (bytes)   | Purpose |
| --------- | ------- | --------- | ------- |
| 00     |    0     | 2     |    'BM' - for Windows (0x42 0x4D)     |
| 02     |    2     | 4     |    The size of the BMP file in bytes     |
| 06     |    6     | 4     |    Reserved, if created manualy can be 0     |
| 0A     |    10     | 4     |    The offset, i.e. starting address, of the byte where the bitmap image data the bitmap image data (pixel array) can be found.

### DIB_header

| Offset (hex)    | Offset (dec) | Size (bytes)   | Purpose |
| --------- | ------- | --------- | ------- |
| 0E    |    14     | 4     |    The size of header in bytes (40)     |
| 12    |    18     | 4     |    The bitmap width in pixels (signed integer)     |
| 16    |    22     | 4     |    The bitmap height in pixels (signed integer)     |
| 1A    |    26     | 2     |    The number of color planes (must be 1)     |
| 1C    |    28     | 2     |    the number of bits per pixel, which is the color depth of the image. Typical values are: 1, 4, 8, 16, 24 and 32.     |
| 1E    |    30     | 4     |    The compression method being used.      |
| 22    |    34     | 4     |    The image size. This is the size of the raw bitmap data.      |
| 26    |    38     | 2     |    Template data, unused    |

### RGB values

Example for 24-bit format (offset is the value of bit '0A' in BITMAP_header):
| Offset (hex)    | Size (bytes)  | Value (hex)   | Value (dec) | Description |
| --------- | ------- | --------- | ------- | ------- |
| 36    | 3  | FF FF FF  | 255 255 255 | White pixel |
| 39    | 3  | 00 00 FF  | 0 0 255 | Red pixel |
| 3C    | 3  | 00 FF 00  | 0 255 0 | Green pixel |
| 3F    | 3  | FF 00 00  | 255 0 0 | Blue pixel |

Example for 32-bit format (offset is the value of bit '0A' in BITMAP_header):
| Offset (hex)    | Size (bytes)  | Value (hex)   | Value (dec) | Description |
| --------- | ------- | --------- | ------- | ------- |
| 36    | 4  | FF FF FF 00 | 255 255 255 0 | White pixel (Alpha = 0)*|
| 3A    | 4  | 00 00 FF FF | 0 0 255 255 | Red pixel (Alpha = 255)|
| 3E    | 4  | 00 FF 00 7F | 0 255 0 127 | Green pixel (Alpha = 127)|
| 42    | 4  | FF 00 00 00 | 255 0 0  0 | Blue pixel (Alpha = 0)|

* - The alpha parameter is a number between 0 (fully transparent) and 255 (fully opaque).

### Exemplary files

![image](https://github.com/user-attachments/assets/7124d978-019d-4ff8-bf07-7191e791ceeb)

## Program capabilities

### Box blur image

A box blur is an algorithm that can blur an image according to the following equation:

$ n value of pix = 1/9 * sum(pix(-1, 1), pix(0, 1), pix(1, 1) ... etc. $ (for every RGB cannal)

### Upscaling image

The up-scaling algorithm can double the resolution of the input image by averaging the values of neighboring pixels according to the following equation:

$ n value of pix  = sum(pix(-1, -1), pix(-1, 1), pix(1, -1), pix(1, 1) / 4 $
