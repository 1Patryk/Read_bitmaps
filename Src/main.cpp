#include "../Include/Read_BMP.hpp"
#include "../Include/Fully_connected_network.hpp"

template<class start, class stop>
void Display_results_counting_time(start Start, stop Stop, std::string namefunction)
{
	std::cout << "Calculations '" << namefunction << "' lasted: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(Stop - Start).count()
		<< " millisecond/s\n" << std::endl;
	std::cout << "Calculations lasted: "
		<< (std::chrono::duration_cast<std::chrono::milliseconds>(Stop - Start).count()) / 1000
		<< " second/s\n" << std::endl;
}

int main()
{

	const char* name_file_r_1 = { "sample_640×426.bmp" };		// name file to read
	const char* name_file_w_1 = { "new.bmp" };					// name file to write

	std::cout << "Calculations started... " << std::endl;

	auto Start = std::chrono::high_resolution_clock::now();

	Read_BMP BMP;

	BMP.readData(name_file_r_1);

	auto Stop1 = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop1, "readData()");

	BMP.chartofloatVector();

	auto Stop2 = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Stop1, Stop2, "chartofloatVector()");

	BMP.addzerovalueVector();

	auto Stop3 = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Stop2, Stop3, "addzerovalueVector()");

	BMP.boxblurImage();

	auto Stop4 = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Stop3, Stop4, "boxblurImage()");

	BMP.lesszerovalueVector();

	auto Stop5 = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Stop4, Stop5, "lesszerovalueVector()");

	BMP.floattocharVector();

	auto Stop6 = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Stop5, Stop6, "floattocharVector()");

	BMP.writeData(name_file_w_1);

	auto Stop7 = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Stop6, Stop7, "writeData()");

	Fully_connected_network DATA;

	DATA.Display_results_for_MLP_x_x();

	auto Stop = std::chrono::high_resolution_clock::now();

	Display_results_counting_time(Start, Stop, "ALL");

	// case 32 !!!

}