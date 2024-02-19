#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

class Read_BMP
{

private:

	struct BITMAP_header
	{
		unsigned char name[2];					// 2 bytes // BM Windows 3.1x, 95, NT, ... etc.
		unsigned char size[4];					// 4 bytes // The size of the BMP file in bytes
		unsigned char reserved[4];				// 2 * 2 bytes // If created manualy can be 0.
		unsigned char image_offset[4];			// 4 bytes // The offset, i.e. starting address, 
												// of the byte where the bitmap image data 
												// (pixel array) can be found.
	};

	struct DIB_header
	{
		unsigned char header_size[4];			// 4 bytes // the size of this header, in bytes(40)
		unsigned char width[4];					// 4 bytes // the bitmap width in pixels (signed integer)
		unsigned char height[4];				// 4 bytes // the bitmap height in pixels (signed integer)
		unsigned char colorplanes[2];			// 2 bytes // the number of color planes (must be 1)
		unsigned char bitsperpixels[2];			// 2 bytes // the number of bits per pixel, which is the color 
												// depth of the image. Typical values are:
												// 1, 4, 8, 16, 24 and 32.
		unsigned char compression[4];			// 4 bytes // the compression method being used. 
		unsigned char image_size[4];			// 4 bytes // the image size. This is the size of the raw bitmap data
		unsigned char temp[16];					// 16 bytes // template data, unused
	};

	struct RGB
	{
		//unsigned char white;
		unsigned char blue;
		unsigned char green;
		unsigned char red;
	};

	BITMAP_header* BITMAP_header_pointer;
	DIB_header* DIB_header_pointer;
	RGB* RGB_pointer;

	// char type vector

	std::vector <std::vector <unsigned char>> cImage_white_cannal;
	std::vector <std::vector <unsigned char>> cImage_blue_cannal;
	std::vector <std::vector <unsigned char>> cImage_green_cannal;
	std::vector <std::vector <unsigned char>> cImage_red_cannal;

	std::vector <unsigned char> cImage_RGB_white;
	std::vector <unsigned char> cImage_RGB_blue;
	std::vector <unsigned char> cImage_RGB_green;
	std::vector <unsigned char> cImage_RGB_red;


	// float type vector

	std::vector <std::vector <float>> fImage_white_cannal;
	std::vector <std::vector <float>> fImage_blue_cannal;
	std::vector <std::vector <float>> fImage_green_cannal;
	std::vector <std::vector <float>> fImage_red_cannal;

	std::vector <float> fImage_RGB_white;
	std::vector <float> fImage_RGB_blue;
	std::vector <float> fImage_RGB_green;
	std::vector <float> fImage_RGB_red;
	

public:

	Read_BMP();																// constructor 
	int char_to_int(unsigned char height [4]);								// convert char type to int type
	void printData();														// print data in prompt
	void readData(const char* name_file_r);									// read data from file
	void writeData(const char* name_file_w);								// save data to file
		
	void chartofloatVector();												// change data type from char to float and add '0' value 
	void floattocharVector();												// change data type from float to char
	void addzerovalueVector();												// and add '0' value 
	void lesszerovalueVector();												// less '0' value 
	void boxblurImage();													// Create box blur image (normalized)


	// The bitmap image starts in the lower left corner
};

