#include "../Include/Read_BMP.hpp"

Read_BMP::Read_BMP()
{
	BITMAP_header_pointer = new BITMAP_header;
	DIB_header_pointer = new DIB_header;
	RGB_pointer = new RGB;

	Scale = new float{ 2.0f };

	// char type vector

	cImage_white_cannal = { std::vector <std::vector<unsigned char> > { 0 } };
	cImage_blue_cannal  = { std::vector <std::vector<unsigned char> > { 0 } };
	cImage_green_cannal = { std::vector <std::vector<unsigned char> > { 0 } };
	cImage_red_cannal   = { std::vector <std::vector<unsigned char> > { 0 } };

	cImage_RGB_white	= { std::vector<unsigned char> { 0 } };
	cImage_RGB_blue		= { std::vector<unsigned char> { 0 } };
	cImage_RGB_green	= { std::vector<unsigned char> { 0 } };
	cImage_RGB_red		= { std::vector<unsigned char> { 0 } };

	// float type vector

	fImage_white_cannal = { std::vector <std::vector<float> > { 0 } };
	fImage_blue_cannal  = { std::vector <std::vector<float> > { 0 } };
	fImage_green_cannal = { std::vector <std::vector<float> > { 0 } };
	fImage_red_cannal   = { std::vector <std::vector<float> > { 0 } };

	fImage_RGB_white	= { std::vector<float> { 0 } };
	fImage_RGB_blue		= { std::vector<float> { 0 } };
	fImage_RGB_green	= { std::vector<float> { 0 } };
	fImage_RGB_red		= { std::vector<float> { 0 } };
}

int Read_BMP::char_to_int(unsigned char height[4])
{
	return ((static_cast<int>(height[3]) << 24)
		| (static_cast<int>(height[2]) << 16)
		| (static_cast<int>(height[1]) << 8)
		| (static_cast<int>(height[0])));
};

void Read_BMP::printData()
{
	std::cout << "____PRINT DATA____" << std::endl;
	
	std::cout << "Name: " << BITMAP_header_pointer->name[0] << BITMAP_header_pointer->name[1] << " file." << std::endl;

	int size = char_to_int(&BITMAP_header_pointer->size[0]);

	int image_offset = char_to_int(&BITMAP_header_pointer->image_offset[0]);

	int header_size = char_to_int(&DIB_header_pointer->header_size[0]);

	int width = char_to_int(&DIB_header_pointer->width[0]);

	int height = char_to_int(&DIB_header_pointer->height[0]);

	short int colorplanes = char_to_int(&DIB_header_pointer->colorplanes[0]);

	short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

	int compression = char_to_int(&DIB_header_pointer->compression[0]);

	int image_size = char_to_int(&DIB_header_pointer->image_size[0]);


	std::cout << "Size of BMP file: " << size << " bytes." << std::endl;
	std::cout << "Image offset: " << image_offset << " bytes." << std::endl;
	std::cout << "Header size: " << header_size << " bytes." << std::endl;
	std::cout << "Width image: " << width << " pixels." << std::endl;
	std::cout << "Height image: " << height << " pixels." << std::endl;
	std::cout << "Colorplanes: " << colorplanes << std::endl;
	std::cout << "Bits per pixels: " << bitsperpixels << std::endl;
	std::cout << "Compression method: " << compression << std::endl;
	std::cout << "Image size: " << image_size << std::endl;
}

void Read_BMP::readData(const char* Open_filename)
{
	std::cout << Open_filename << std::endl;

	std::ifstream file_r;
	file_r.open(Open_filename, std::ios::in | std::ios::binary);

	if (!file_r.is_open())
	{
	    std::cout << "Failed to open file!" << std::endl;
	}
	else
	{
		file_r.read(reinterpret_cast<char*>(&BITMAP_header_pointer->name[0]), 2 * sizeof(char));

		file_r.read(reinterpret_cast<char*>(&BITMAP_header_pointer->size[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char*>(&BITMAP_header_pointer->reserved[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char*>(&BITMAP_header_pointer->image_offset[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char*>(&DIB_header_pointer->header_size[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char*>(&DIB_header_pointer->width[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char*>(&DIB_header_pointer->height[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char*>(&DIB_header_pointer->colorplanes[0]), 2 * sizeof(char));

		file_r.read(reinterpret_cast<char*>(&DIB_header_pointer->bitsperpixels[0]), 2 * sizeof(char));

		file_r.read(reinterpret_cast<char*>(&DIB_header_pointer->compression[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char*>(&DIB_header_pointer->image_size[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char*>(&DIB_header_pointer->temp[0]), 16 * sizeof(char));

		unsigned char b = 0;										// blue value
		unsigned char g = 0;										// green value
		unsigned char r = 0;										// red value
		unsigned char w = 0;										// white value

		short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

		int width = char_to_int(&DIB_header_pointer->width[0]);

		int height = char_to_int(&DIB_header_pointer->height[0]);

		file_r.seekg(BITMAP_header_pointer->image_offset[0]);

		printData();

		switch (bitsperpixels)
		{
		case 24:

			cImage_blue_cannal.reserve(height  * (*Scale));
			cImage_green_cannal.reserve(height  * (*Scale));
			cImage_red_cannal.reserve(height  * (*Scale));

			cImage_RGB_blue.reserve(width  * (*Scale));
			cImage_RGB_green.reserve(width  * (*Scale));
			cImage_RGB_red.reserve(width  * (*Scale));

			for (int i = height - 1; i >= 0; i--)
			{
				for (int j = 0; j < width; j++)
				{
					file_r.read(reinterpret_cast<char*>(&b), 1);								// read RGB blue values
					cImage_RGB_blue.push_back(b);
					file_r.read(reinterpret_cast<char*>(&g), 1);								// read RGB green values
					cImage_RGB_green.push_back(g);
					file_r.read(reinterpret_cast<char*>(&r), 1);								// read RGB red values
					cImage_RGB_red.push_back(r);
				}

				cImage_blue_cannal.push_back(cImage_RGB_blue);
				cImage_green_cannal.push_back(cImage_RGB_green);
				cImage_red_cannal.push_back(cImage_RGB_red);

				cImage_RGB_blue.clear();
				cImage_RGB_green.clear();
				cImage_RGB_red.clear();
			}

			file_r.close();

			break;

		case 32:

			cImage_blue_cannal.reserve(height  * (*Scale));
			cImage_green_cannal.reserve(height  * (*Scale));
			cImage_red_cannal.reserve(height  * (*Scale));
			cImage_white_cannal.reserve(height  * (*Scale));

			cImage_RGB_blue.reserve(width  * (*Scale));
			cImage_RGB_green.reserve(width  * (*Scale));
			cImage_RGB_red.reserve(width  * (*Scale));
			cImage_RGB_white.reserve(width  * (*Scale));

			for (int i = height - 1; i >= 0; i--)
			{
				for (int j = 0; j < width; j++)
				{
					file_r.read(reinterpret_cast<char*>(&b), 1);								// read RGB blue values
					cImage_RGB_blue.push_back(b);
					file_r.read(reinterpret_cast<char*>(&g), 1);								// read RGB green values
					cImage_RGB_green.push_back(g);
					file_r.read(reinterpret_cast<char*>(&r), 1);								// read RGB red values
					cImage_RGB_red.push_back(r);
					file_r.read(reinterpret_cast<char*>(&w), 1);								// read RGB white values
					cImage_RGB_white.push_back(w);
				}

				cImage_blue_cannal.push_back(cImage_RGB_blue);
				cImage_green_cannal.push_back(cImage_RGB_green);
				cImage_red_cannal.push_back(cImage_RGB_red);
				cImage_white_cannal.push_back(cImage_RGB_white);

				cImage_RGB_blue.clear();
				cImage_RGB_green.clear();
				cImage_RGB_red.clear();
				cImage_RGB_white.clear();
			}

			file_r.close();

			break;

		default:

			std::cout << "Bits per pixels value is incorrect!" << std::endl;
			break;
		}
	}
}

void Read_BMP::writeData(const char* Output_filename_path)
{
	const auto Start = std::chrono::high_resolution_clock::now();

	auto now = std::chrono::system_clock::now();

	auto localTime = std::chrono::system_clock::to_time_t(now);

	const char* extension = ".bmp";

	std::stringstream ss;

	ss << "BMP_file " << std::put_time(std::localtime(&localTime), "%Y_%m_%d_%H_%M_%S") << extension;

	std::string file_date = ss.str();

	file_date.erase(remove(file_date.begin(), file_date.end(), '\"'), file_date.end());

	//std::basic_ofstream<unsigned char> file_w(Output_filename_path + file_date, std::ios::out | std::ios::binary);

	std::ofstream file_w;

	file_w.open(Output_filename_path + file_date, std::ios::out | std::ios::binary);

	file_w.write(reinterpret_cast<char*>(&BITMAP_header_pointer->name[0]), 2 * sizeof(char));

	file_w.write(reinterpret_cast<char*>(&BITMAP_header_pointer->size[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char*>(&BITMAP_header_pointer->reserved[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char*>(&BITMAP_header_pointer->image_offset[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char*>(&DIB_header_pointer->header_size[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char*>(&DIB_header_pointer->width[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char*>(&DIB_header_pointer->height[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char*>(&DIB_header_pointer->colorplanes[0]), 2 * sizeof(char));

	file_w.write(reinterpret_cast<char*>(&DIB_header_pointer->bitsperpixels[0]), 2 * sizeof(char));

	file_w.write(reinterpret_cast<char*>(&DIB_header_pointer->compression[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char*>(&DIB_header_pointer->image_size[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char*>(&DIB_header_pointer->temp[0]), 16 * sizeof(char));

	// Write pixels

	unsigned char b = 0;										// blue value
	unsigned char g = 0;										// green value
	unsigned char r = 0;										// red value
	unsigned char w = 0;										// white value

	short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

	int height = char_to_int(&DIB_header_pointer->height[0]) * (*Scale);

	int width = char_to_int(&DIB_header_pointer->width[0]) * (*Scale);

	file_w.seekp(BITMAP_header_pointer->image_offset[0]);

	switch (bitsperpixels)
	{
	case 24:

		while ((cImage_blue_cannal.size() == 0 ||
				cImage_green_cannal.size() == 0 ||
				cImage_red_cannal.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'char' type!");
		}

		for (int i = 0; i <= height - 1; i++)
		{
			for (int j = 0; j < width; j++)
			{
				b = cImage_blue_cannal[i][j];
				file_w.write(reinterpret_cast<char*>(&b), 1);										// write blue pixel values
				g = cImage_green_cannal[i][j];
				file_w.write(reinterpret_cast<char*>(&g), 1);										// write green pixel values
				r = cImage_red_cannal[i][j];
				file_w.write(reinterpret_cast<char*>(&r), 1);										// write red pixel values
			}
		}

		file_w.close();

		break;

	case 32:

		while ((cImage_white_cannal.size() == 0 ||
				cImage_blue_cannal.size() == 0 ||
				cImage_green_cannal.size() == 0 ||
				cImage_red_cannal.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'char' type!");
		}
		for (int i = 0; i <= height - 1; i++)
		{
			for (int j = 0; j < width; j++)
			{
				b = cImage_blue_cannal[i][j];
				file_w.write(reinterpret_cast<char*>(&b), 1);										// write blue pixel values
				g = cImage_green_cannal[i][j];
				file_w.write(reinterpret_cast<char*>(&g), 1);										// write green pixel values
				r = cImage_red_cannal[i][j];
				file_w.write(reinterpret_cast<char*>(&r), 1);										// write red pixel values
				w = cImage_white_cannal[i][j];
				file_w.write(reinterpret_cast<char*>(&w), 1);										// write white pixel values
			}
		}

		file_w.close();

		break;

	default:

		std::cout << "Bits per pixels value is incorrect!" << std::endl;
		break;
	}
}

void Read_BMP::chartofloatVector()
{
	short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

	int height = char_to_int(&DIB_header_pointer->height[0]);

	int width = char_to_int(&DIB_header_pointer->width[0]);

	switch (bitsperpixels)
	{
	case 24:

		fImage_blue_cannal.clear();
		fImage_green_cannal.clear();
		fImage_red_cannal.clear();

		fImage_RGB_blue.clear();
		fImage_RGB_green.clear();
		fImage_RGB_red.clear();

		fImage_blue_cannal.reserve(height);							// storage reserve
		fImage_green_cannal.reserve(height);						//	
		fImage_red_cannal.reserve(height);							//

		fImage_RGB_blue.reserve(width);								//
		fImage_RGB_green.reserve(width);							//
		fImage_RGB_red.reserve(width);								// 

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j <= width; j++)
			{
				fImage_RGB_blue.push_back(static_cast<float>(cImage_blue_cannal[i][j]));
				fImage_RGB_green.push_back(static_cast<float>(cImage_green_cannal[i][j]));
				fImage_RGB_red.push_back(static_cast<float>(cImage_red_cannal[i][j]));
			}

			fImage_blue_cannal.push_back(fImage_RGB_blue);
			fImage_green_cannal.push_back(fImage_RGB_green);
			fImage_red_cannal.push_back(fImage_RGB_red);

			fImage_RGB_blue.clear();
			fImage_RGB_green.clear();
			fImage_RGB_red.clear();
		}

		cImage_blue_cannal.clear();
		cImage_green_cannal.clear();
		cImage_red_cannal.clear();

		break;

	case 32:

		std::cout << "case 32" << std::endl;

		break;

	default:

		std::cout << "Bits per pixels value is incorrect!" << std::endl;
		break;
	}
}

void Read_BMP::floattocharVector()
{
	short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

	int height = char_to_int(&DIB_header_pointer->height[0]) * (*Scale);

	int width = char_to_int(&DIB_header_pointer->width[0]) * (*Scale);

	switch (bitsperpixels)
	{
	case 24:

		cImage_blue_cannal.reserve(height);
		cImage_green_cannal.reserve(height);
		cImage_red_cannal.reserve(height);

		cImage_RGB_blue.reserve(width);
		cImage_RGB_green.reserve(width);
		cImage_RGB_red.reserve(width);

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				cImage_RGB_blue.push_back(static_cast<unsigned char>(fImage_blue_cannal[i][j]));
				cImage_RGB_green.push_back(static_cast<unsigned char>(fImage_green_cannal[i][j]));
				cImage_RGB_red.push_back(static_cast<unsigned char>(fImage_red_cannal[i][j]));
			}

			std::cout << "";

			cImage_blue_cannal.push_back(cImage_RGB_blue);
			cImage_green_cannal.push_back(cImage_RGB_green);
			cImage_red_cannal.push_back(cImage_RGB_red);

			cImage_RGB_blue.clear();
			cImage_RGB_green.clear();
			cImage_RGB_red.clear();
		}

		fImage_blue_cannal.clear();
		fImage_green_cannal.clear();
		fImage_red_cannal.clear();

		break;

	case 32:

		std::cout << "case 32" << std::endl;

		break;

	default:

		std::cout << "Bits per pixels value is incorrect!" << std::endl;
		break;
	}
}

void Read_BMP::addzerovalueVector()
{
	short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

	int height = char_to_int(&DIB_header_pointer->height[0]);

	int width = char_to_int(&DIB_header_pointer->width[0]);

	switch (bitsperpixels)
	{
	case 24:

		while ((fImage_blue_cannal.size() == 0 ||
				fImage_green_cannal.size() == 0 ||
				fImage_red_cannal.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'float' type!");
		}

		fImage_blue_cannal.reserve((height + 2)  * (*Scale));							// storage reserve
		fImage_green_cannal.reserve((height + 2)  * (*Scale));						//	
		fImage_red_cannal.reserve((height + 2)  * (*Scale));							//

		fImage_RGB_blue.resize(((width + 2)  * (*Scale)), 0);
		fImage_RGB_green.resize(((width + 2)  * (*Scale)), 0);
		fImage_RGB_red.resize(((width + 2)  * (*Scale)), 0);

		fImage_blue_cannal.insert(fImage_blue_cannal.begin(), fImage_RGB_blue);
		fImage_green_cannal.insert(fImage_green_cannal.begin(), fImage_RGB_green);
		fImage_red_cannal.insert(fImage_red_cannal.begin(), fImage_RGB_red);

		fImage_blue_cannal.push_back(fImage_RGB_blue);
		fImage_green_cannal.push_back(fImage_RGB_green);
		fImage_red_cannal.push_back(fImage_RGB_red);

		fImage_RGB_blue.clear();
		fImage_RGB_green.clear();
		fImage_RGB_red.clear();

		for (int i = 0; i < height; i++)
		{
			fImage_blue_cannal[i + 1].insert(fImage_blue_cannal[i + 1].begin(), 0);
			fImage_blue_cannal[i + 1].push_back(0);
			fImage_green_cannal[i + 1].insert(fImage_green_cannal[i + 1].begin(), 0);
			fImage_green_cannal[i + 1].push_back(0);
			fImage_red_cannal[i + 1].insert(fImage_red_cannal[i + 1].begin(), 0);
			fImage_red_cannal[i + 1].push_back(0);
		}

		break;

	case 32:

		while ((fImage_white_cannal.size() == 0 ||
			fImage_blue_cannal.size() == 0 ||
			fImage_green_cannal.size() == 0 ||
			fImage_red_cannal.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'float' type!");
		}

		for (int i = 0; i <= height - 1; i++)
		{
			for (int j = 0; j < width; j++)
			{
			}
		}

		break;

	default:

		std::cout << "Bits per pixels value is incorrect!" << std::endl;
		break;
	}
}

void Read_BMP::lesszerovalueVector()
{
	short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

	int height = char_to_int(&DIB_header_pointer->height[0]) * (*Scale);

	int width = char_to_int(&DIB_header_pointer->width[0]) * (*Scale);

	switch (bitsperpixels)
	{
	case 24:

		while ((fImage_blue_cannal.size() == 0 ||
				fImage_green_cannal.size() == 0 ||
				fImage_red_cannal.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'float' type!");
		}

		fImage_blue_cannal.erase(fImage_blue_cannal.begin());
		fImage_green_cannal.erase(fImage_green_cannal.begin());
		fImage_red_cannal.erase(fImage_red_cannal.begin());

		fImage_blue_cannal.pop_back();
		fImage_green_cannal.pop_back();
		fImage_red_cannal.pop_back();

		for (int i = 0; i < height; i++)
		{
			fImage_blue_cannal[i].erase(fImage_blue_cannal[i].begin());
			fImage_blue_cannal[i].pop_back();
			fImage_green_cannal[i].erase(fImage_green_cannal[i].begin());
			fImage_green_cannal[i].pop_back();
			fImage_red_cannal[i].erase(fImage_red_cannal[i].begin());
			fImage_red_cannal[i].pop_back();
		}

		break;

	case 32:

		while ((fImage_white_cannal.size() == 0 ||
			fImage_blue_cannal.size() == 0 ||
			fImage_green_cannal.size() == 0 ||
			fImage_red_cannal.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'float' type!");
		}

		for (int i = 0; i <= height - 1; i++)
		{
			for (int j = 0; j < width; j++)
			{
			}
		}

		break;

	default:

		std::cout << "Bits per pixels value is incorrect!" << std::endl;
		break;
	}
}

void Read_BMP::boxblurImage()
{
	short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

	int height = char_to_int(&DIB_header_pointer->height[0]);

	int width = char_to_int(&DIB_header_pointer->width[0]);

	float BoX_b = 0.111111f;

	switch (bitsperpixels)
	{
	case 24:

		while ((fImage_blue_cannal.size() == 0 ||
				fImage_green_cannal.size() == 0 ||
				fImage_red_cannal.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'float' type!");
		}

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				fImage_blue_cannal[i + 1][j + 1] = (fImage_blue_cannal[i + 2][j] * BoX_b +
													fImage_blue_cannal[i + 2][j + 1] * BoX_b +
													fImage_blue_cannal[i + 2][j + 2] * BoX_b +
													fImage_blue_cannal[i + 1][j] * BoX_b +
													fImage_blue_cannal[i + 1][j + 1] * BoX_b +
													fImage_blue_cannal[i + 1][j + 2] * BoX_b +
													fImage_blue_cannal[i][j] * BoX_b +
													fImage_blue_cannal[i][j + 1] * BoX_b +
													fImage_blue_cannal[i][j + 2] * BoX_b);
				fImage_green_cannal[i + 1][j + 1] = (fImage_green_cannal[i + 2][j] * BoX_b +
													 fImage_green_cannal[i + 2][j + 1] * BoX_b +
													 fImage_green_cannal[i + 2][j + 2] * BoX_b +
													 fImage_green_cannal[i + 1][j] * BoX_b +
													 fImage_green_cannal[i + 1][j + 1] * BoX_b +
													 fImage_green_cannal[i + 1][j + 2] * BoX_b +
													 fImage_green_cannal[i][j] * BoX_b +
													 fImage_green_cannal[i][j + 1] * BoX_b +
													 fImage_green_cannal[i][j + 2] * BoX_b);
				fImage_red_cannal[i + 1][j + 1] = (fImage_red_cannal[i + 2][j] * BoX_b +
												   fImage_red_cannal[i + 2][j + 1] * BoX_b +
												   fImage_red_cannal[i + 2][j + 2] * BoX_b +
												   fImage_red_cannal[i + 1][j] * BoX_b +
												   fImage_red_cannal[i + 1][j + 1] * BoX_b +
												   fImage_red_cannal[i + 1][j + 2] * BoX_b +
												   fImage_red_cannal[i][j] * BoX_b +
												   fImage_red_cannal[i][j + 1] * BoX_b +
												   fImage_red_cannal[i][j + 2] * BoX_b);
			}
		}

		break;

	case 32:

		while ((fImage_white_cannal.size() == 0 ||
				fImage_blue_cannal.size() == 0 ||
				fImage_green_cannal.size() == 0 ||
				fImage_red_cannal.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'float' type!");
		}

		break;

	default:

		std::cout << "Bits per pixels value is incorrect!" << std::endl;
		break;
	}
}

void Read_BMP::upscaling()
{
	short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

	int height = char_to_int(&DIB_header_pointer->height[0]) * (*Scale);

	int width = char_to_int(&DIB_header_pointer->width[0]) * (*Scale);

	std::vector <std::vector <float>> fImage_blue_cannal_copy = fImage_blue_cannal;
	std::vector <std::vector <float>> fImage_green_cannal_copy = fImage_green_cannal;
	std::vector <std::vector <float>> fImage_red_cannal_copy = fImage_red_cannal;

	switch (bitsperpixels)
	{
	case 24:

		while ((fImage_blue_cannal.size() == 0 ||
			fImage_green_cannal.size() == 0 ||
			fImage_red_cannal.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'float' type!");
		}

		// adding zero value
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				fImage_blue_cannal[i + 1][j + 1] = 0.0f;
				fImage_green_cannal[i + 1][j + 1] = 0.0f;
				fImage_red_cannal[i + 1][j + 1] = 0.0f;
			}
		}

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				fImage_blue_cannal[(i * 2) + 2][(j * 2) + 2] = fImage_blue_cannal_copy[i + 1][j + 1];
				fImage_green_cannal[(i * 2) + 2][(j * 2) + 2] = fImage_green_cannal_copy[i + 1][j + 1];
				fImage_red_cannal[(i * 2) + 2][(j * 2) + 2] = fImage_red_cannal_copy[i + 1][j + 1];
			}
		}

		printData();

		break;

	case 32:

		while ((fImage_white_cannal.size() == 0 ||
			fImage_blue_cannal.size() == 0 ||
			fImage_green_cannal.size() == 0 ||
			fImage_red_cannal.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'float' type!");
		}

		break;

	default:

		std::cout << "Bits per pixels value is incorrect!" << std::endl;
		break;
	}
}

void Read_BMP::Calculating_BMP(Read_BMP BMP, 
	const char* Open_filename,
	const char* Output_filename_path)
{
	BMP.readData(Open_filename);
	BMP.chartofloatVector();
	BMP.addzerovalueVector();

	//BMP.upscaling();
	BMP.boxblurImage();


	BMP.lesszerovalueVector();
	BMP.floattocharVector();
	BMP.writeData(Output_filename_path);
}
