#include "../Include/Read_BMP.hpp"
#include "../ProjectConfig.h"

template<class start, class stop>
void Display_results_counting_time(start Start, stop Stop, std::string namefunction)
{
	std::cout << "Calculations " << namefunction << " lasted: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(Stop - Start).count()
		<< " millisecond/s\n" << std::endl;
	std::cout << "Calculations lasted: "
		<< (std::chrono::duration_cast<std::chrono::milliseconds>(Stop - Start).count()) / 1000
		<< " second/s\n" << std::endl;
}

int main()
{
	const char* Open_filename = { "C:/Users/patry/Desktop/GITHUB/Read_bitmaps/In_BMP/sample_1280×853.bmp" };		// name file to read
	const char* Output_filename_path = { "C:/Users/patry/Desktop/GitHub/Read_bitmaps/Out_BMP/" };					// name file to write

	std::cout << "Calculations started... " << std::endl;

	auto Start = std::chrono::high_resolution_clock::now();

	Read_BMP BMP;

	BMP.Calculating_BMP(BMP, Open_filename, Output_filename_path);

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "aggregatively");

	// case 32 !!!

}