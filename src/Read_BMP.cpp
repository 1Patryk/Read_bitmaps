#include "../Include/Read_BMP.hpp"

Read_BMP::Read_BMP()
{
	BITMAP_header_pointer = new BITMAP_header;
	DIB_header_pointer = new DIB_header;
	RGB_pointer = new RGB;

	Scale = new float{2.0f};

	// char type vector

	cImage_white_cannal = {std::vector<std::vector<unsigned char>>{0}};
	cImage_blue_cannal = {std::vector<std::vector<unsigned char>>{0}};
	cImage_green_cannal = {std::vector<std::vector<unsigned char>>{0}};
	cImage_red_cannal = {std::vector<std::vector<unsigned char>>{0}};

	cImage_RGB_white = {std::vector<unsigned char>{0}};
	cImage_RGB_blue = {std::vector<unsigned char>{0}};
	cImage_RGB_green = {std::vector<unsigned char>{0}};
	cImage_RGB_red = {std::vector<unsigned char>{0}};

	// float type vector

	fImage_white_cannal = {std::vector<std::vector<float>>{0}};
	fImage_blue_cannal = {std::vector<std::vector<float>>{0}};
	fImage_green_cannal = {std::vector<std::vector<float>>{0}};
	fImage_red_cannal = {std::vector<std::vector<float>>{0}};

	fImage_RGB_white = {std::vector<float>{0}};
	fImage_RGB_blue = {std::vector<float>{0}};
	fImage_RGB_green = {std::vector<float>{0}};
	fImage_RGB_red = {std::vector<float>{0}};
}

int Read_BMP::char_to_int(unsigned char height[4])
{
	return ((static_cast<int>(height[3]) << 24) | (static_cast<int>(height[2]) << 16) 
			| (static_cast<int>(height[1]) << 8) | (static_cast<int>(height[0])));
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

void Read_BMP::readData(const char *Open_filename)
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
		file_r.read(reinterpret_cast<char *>(&BITMAP_header_pointer->name[0]), 2 * sizeof(char));

		file_r.read(reinterpret_cast<char *>(&BITMAP_header_pointer->size[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char *>(&BITMAP_header_pointer->reserved[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char *>(&BITMAP_header_pointer->image_offset[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char *>(&DIB_header_pointer->header_size[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char *>(&DIB_header_pointer->width[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char *>(&DIB_header_pointer->height[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char *>(&DIB_header_pointer->colorplanes[0]), 2 * sizeof(char));

		file_r.read(reinterpret_cast<char *>(&DIB_header_pointer->bitsperpixels[0]), 2 * sizeof(char));

		file_r.read(reinterpret_cast<char *>(&DIB_header_pointer->compression[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char *>(&DIB_header_pointer->image_size[0]), 4 * sizeof(char));

		file_r.read(reinterpret_cast<char *>(&DIB_header_pointer->temp[0]), 16 * sizeof(char));

		unsigned char b = 0; // blue value
		unsigned char g = 0; // green value
		unsigned char r = 0; // red value
		unsigned char w = 0; // white value

		short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

		int width = char_to_int(&DIB_header_pointer->width[0]);

		int height = char_to_int(&DIB_header_pointer->height[0]);

		file_r.seekg(BITMAP_header_pointer->image_offset[0]);

		printData();

		switch (bitsperpixels)
		{
		case 24:

			cImage_blue_cannal.reserve(height);
			cImage_green_cannal.reserve(height);
			cImage_red_cannal.reserve(height);

			cImage_RGB_blue.reserve(width);
			cImage_RGB_green.reserve(width);
			cImage_RGB_red.reserve(width);

			for (int i = height - 1; i >= 0; i--)
			{
				for (int j = 0; j < width; j++)
				{
					file_r.read(reinterpret_cast<char *>(&b), 1); // read RGB blue values
					cImage_RGB_blue.push_back(b);
					file_r.read(reinterpret_cast<char *>(&g), 1); // read RGB green values
					cImage_RGB_green.push_back(g);
					file_r.read(reinterpret_cast<char *>(&r), 1); // read RGB red values
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

			cImage_blue_cannal.reserve(height * (*Scale));
			cImage_green_cannal.reserve(height * (*Scale));
			cImage_red_cannal.reserve(height * (*Scale));
			cImage_white_cannal.reserve(height * (*Scale));

			cImage_RGB_blue.reserve(width * (*Scale));
			cImage_RGB_green.reserve(width * (*Scale));
			cImage_RGB_red.reserve(width * (*Scale));
			cImage_RGB_white.reserve(width * (*Scale));

			for (int i = height - 1; i >= 0; i--)
			{
				for (int j = 0; j < width; j++)
				{
					file_r.read(reinterpret_cast<char *>(&b), 1); // read RGB blue values
					cImage_RGB_blue.push_back(b);
					file_r.read(reinterpret_cast<char *>(&g), 1); // read RGB green values
					cImage_RGB_green.push_back(g);
					file_r.read(reinterpret_cast<char *>(&r), 1); // read RGB red values
					cImage_RGB_red.push_back(r);
					file_r.read(reinterpret_cast<char *>(&w), 1); // read RGB white values
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

void Read_BMP::writeData
(
	const char *Output_filename_path,
	std::vector <std::vector <float>> Image_white_cannal,
	std::vector <std::vector <float>> Image_blue_cannal,
	std::vector <std::vector <float>> Image_green_cannal,
	std::vector <std::vector <float>> Image_red_cannal
)
{
	const auto Start = std::chrono::high_resolution_clock::now();

	auto now = std::chrono::system_clock::now();

	auto localTime = std::chrono::system_clock::to_time_t(now);

	int height = char_to_int(&DIB_header_pointer->height[0]);

	int width = char_to_int(&DIB_header_pointer->width[0]);

	int img_scale = height * width * 3;
	*(uint32_t*)&DIB_header_pointer->image_size[0] = *(uint32_t*)&(img_scale);
	
	const char *extension = ".bmp";

	std::stringstream ss;

	ss << "BMP_file " << std::put_time(std::localtime(&localTime), "%Y_%m_%d_%H_%M_%S") << extension;

	std::string file_date = ss.str();

	file_date.erase(remove(file_date.begin(), file_date.end(), '\"'), file_date.end());

	// std::basic_ofstream<unsigned char> file_w(Output_filename_path + file_date, std::ios::out | std::ios::binary);

	std::ofstream file_w;

	file_w.open(Output_filename_path + file_date, std::ios::out | std::ios::binary);

	file_w.write(reinterpret_cast<char *>(&BITMAP_header_pointer->name[0]), 2 * sizeof(char));

	file_w.write(reinterpret_cast<char *>(&BITMAP_header_pointer->size[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char *>(&BITMAP_header_pointer->reserved[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char *>(&BITMAP_header_pointer->image_offset[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char *>(&DIB_header_pointer->header_size[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char *>(&DIB_header_pointer->width[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char *>(&DIB_header_pointer->height[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char *>(&DIB_header_pointer->colorplanes[0]), 2 * sizeof(char));

	file_w.write(reinterpret_cast<char *>(&DIB_header_pointer->bitsperpixels[0]), 2 * sizeof(char));

	file_w.write(reinterpret_cast<char *>(&DIB_header_pointer->compression[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char *>(&DIB_header_pointer->image_size[0]), 4 * sizeof(char));

	file_w.write(reinterpret_cast<char *>(&DIB_header_pointer->temp[0]), 16 * sizeof(char));

	// Write pixels

	unsigned char b = 0; // blue value
	unsigned char g = 0; // green value
	unsigned char r = 0; // red value
	unsigned char w = 0; // white value

	short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

	file_w.seekp(BITMAP_header_pointer->image_offset[0]);

	printData();

	switch (bitsperpixels)
	{
	case 24:

		while ((Image_blue_cannal.size() == 0 ||
				Image_green_cannal.size() == 0 ||
				Image_red_cannal.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'char' type!");
		}

		for (int i = 0; i <= height - 1; i++)
		{
			for (int j = 0; j < width; j++)
			{
				b = Image_blue_cannal[i][j];
				file_w.write(reinterpret_cast<char *>(&b), 1); // write blue pixel values
				g = Image_green_cannal[i][j];
				file_w.write(reinterpret_cast<char *>(&g), 1); // write green pixel values
				r = Image_red_cannal[i][j];
				file_w.write(reinterpret_cast<char *>(&r), 1); // write red pixel values
			}
		}

		file_w.close();

		break;

	case 32:

		while ((Image_white_cannal.size() == 0 ||
				Image_blue_cannal.size() == 0 ||
				Image_green_cannal.size() == 0 ||
				Image_red_cannal.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'char' type!");
		}
		for (int i = 0; i <= height - 1; i++)
		{
			for (int j = 0; j < width; j++)
			{
				b = Image_blue_cannal[i][j];
				file_w.write(reinterpret_cast<char *>(&b), 1); // write blue pixel values
				g = Image_green_cannal[i][j];
				file_w.write(reinterpret_cast<char *>(&g), 1); // write green pixel values
				r = Image_red_cannal[i][j];
				file_w.write(reinterpret_cast<char *>(&r), 1); // write red pixel values
				w = Image_white_cannal[i][j];
				file_w.write(reinterpret_cast<char *>(&w), 1); // write white pixel values
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

		fImage_blue_cannal.reserve(height);	 // storage reserve
		fImage_green_cannal.reserve(height); //
		fImage_red_cannal.reserve(height);	 //

		fImage_RGB_blue.reserve(width);	 //
		fImage_RGB_green.reserve(width); //
		fImage_RGB_red.reserve(width);	 //

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

void Read_BMP::floattocharVector
(
	std::vector <std::vector <float>> Image_white_cannal,
	std::vector <std::vector <float>> Image_blue_cannal,
	std::vector <std::vector <float>> Image_green_cannal,
	std::vector <std::vector <float>> Image_red_cannal,
	std::vector <float> Image_RGB_white,
	std::vector <float> Image_RGB_blue,
	std::vector <float> Image_RGB_green,
	std::vector <float> Image_RGB_red
)
{
	short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

	int height = char_to_int(&DIB_header_pointer->height[0]);

	int width = char_to_int(&DIB_header_pointer->width[0]);

	switch (bitsperpixels)
	{
	case 24:

		Image_blue_cannal.reserve(height);
		Image_green_cannal.reserve(height);
		Image_red_cannal.reserve(height);

		Image_RGB_blue.reserve(width);
		Image_RGB_green.reserve(width);
		Image_RGB_red.reserve(width);

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				Image_RGB_blue.push_back(static_cast<unsigned char>(Image_blue_cannal[i][j]));
				Image_RGB_green.push_back(static_cast<unsigned char>(Image_green_cannal[i][j]));
				Image_RGB_red.push_back(static_cast<unsigned char>(Image_red_cannal[i][j]));
			}

			std::cout << "";

			Image_blue_cannal.push_back(Image_RGB_blue);
			Image_green_cannal.push_back(Image_RGB_green);
			Image_red_cannal.push_back(Image_RGB_red);

			Image_RGB_blue.clear();
			Image_RGB_green.clear();
			Image_RGB_red.clear();
		}

		Image_blue_cannal.clear();
		Image_green_cannal.clear();
		Image_red_cannal.clear();

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

		fImage_blue_cannal.reserve((height + 2) * (*Scale));  // storage reserve
		fImage_green_cannal.reserve((height + 2) * (*Scale)); //
		fImage_red_cannal.reserve((height + 2) * (*Scale));	  //

		fImage_RGB_blue.resize(((width + 2) * (*Scale)), 0);
		fImage_RGB_green.resize(((width + 2) * (*Scale)), 0);
		fImage_RGB_red.resize(((width + 2) * (*Scale)), 0);

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

void Read_BMP::boxblurImage
(
	Read_BMP BMP,
	const char *Open_filename,
	const char *Output_filename_path
)
{
	readData(Open_filename);
	chartofloatVector();
	addzerovalueVector();

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
			std::cout << "Vector is not converted to 'float' type!" << std::endl;
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

		lesszerovalueVector();
		floattocharVector
		(
			fImage_white_cannal,
			fImage_blue_cannal,
			fImage_green_cannal,
			fImage_red_cannal,
			fImage_RGB_white,
			fImage_RGB_blue,
			fImage_RGB_green,
			fImage_RGB_red
		);
		writeData
		(
			Output_filename_path,
			fImage_white_cannal,
			fImage_blue_cannal,
			fImage_green_cannal,
			fImage_red_cannal
		);

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

void Read_BMP::upscaling
(
	Read_BMP BMP,
	float Scale_factor,
	const char *Open_filename,
	const char *Output_filename_path
)
{
	readData(Open_filename);
	chartofloatVector();

	*Scale = Scale_factor;
	short int bitsperpixels = char_to_int(&DIB_header_pointer->bitsperpixels[0]);

	int height = char_to_int(&DIB_header_pointer->height[0]) * (*Scale);

	int width = char_to_int(&DIB_header_pointer->width[0]) * (*Scale);

	std::vector <std::vector <float>> fImage_blue_cannal_resize;
	std::vector <std::vector <float>> fImage_green_cannal_resize;
	std::vector <std::vector <float>> fImage_red_cannal_resize;

	std::vector <float> fImage_RGB_blue_resize;
	std::vector <float> fImage_RGB_green_resize;
	std::vector <float> fImage_RGB_red_resize;

	fImage_blue_cannal_resize.reserve(height);
	fImage_green_cannal_resize.reserve(height);
	fImage_red_cannal_resize.reserve(height);

	fImage_RGB_blue_resize.reserve(width);
	fImage_RGB_green_resize.reserve(width);
	fImage_RGB_red_resize.reserve(width);

	for (int i = height - 1; i >= 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			fImage_RGB_blue_resize.push_back(0.0f);
			fImage_RGB_green_resize.push_back(0.0f);
			fImage_RGB_red_resize.push_back(0.0f);
		}

		fImage_blue_cannal_resize.push_back(fImage_RGB_blue_resize);
		fImage_green_cannal_resize.push_back(fImage_RGB_green_resize);
		fImage_red_cannal_resize.push_back(fImage_RGB_red_resize);

		fImage_RGB_blue_resize.clear();
		fImage_RGB_green_resize.clear();
		fImage_RGB_red_resize.clear();
	}

	int k = 0;
	int l = 0;

	switch (bitsperpixels)
	{
	case 24:

		while ((fImage_blue_cannal_resize.size() == 0 ||
				fImage_green_cannal_resize.size() == 0 ||
				fImage_red_cannal_resize.size() == 0))
		{
			throw std::invalid_argument("Vector is not converted to 'float' type!");
		}

		for (int i = 1; i < height + 1; i += 2)
		{
			for (int j = 1; j < width + 1; j += 2)
			{
				fImage_blue_cannal_resize[i][j] = fImage_blue_cannal[k][l];
				fImage_green_cannal_resize[i][j] = fImage_green_cannal[k][l];
				fImage_red_cannal_resize[i][j] = fImage_red_cannal[k][l];
				l++;
			}
			l = 0;
			k++;
		}
		k = 0;

		/*
		for (int i = 1; i < width + 1; i += 2)
		{
			fImage_blue_cannal_resize[0][i] = (0.0f + fImage_blue_cannal_resize[1][i]) / 2.0f;
			std::cout << fImage_blue_cannal_resize[0][i] << std::endl;
		}
		*/
		
		*(uint32_t*)&DIB_header_pointer->height[0] = *(uint32_t*)&(height);
		*(uint32_t*)&DIB_header_pointer->width[0] = *(uint32_t*)&(width);

		printData();

		floattocharVector
		(
			fImage_white_cannal,
			fImage_blue_cannal_resize,
			fImage_green_cannal_resize,
			fImage_red_cannal_resize,
			fImage_RGB_white,
			fImage_RGB_blue_resize,
			fImage_RGB_green_resize,
			fImage_RGB_red_resize
		);
		writeData
		(
			Output_filename_path, 
			fImage_white_cannal, 
			fImage_blue_cannal_resize,
			fImage_green_cannal_resize,
			fImage_red_cannal_resize
		);

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
