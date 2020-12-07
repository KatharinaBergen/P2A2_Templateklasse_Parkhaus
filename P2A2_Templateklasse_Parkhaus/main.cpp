/*
	Author: Kat Bergen

	Program creates a parking lot in which the guard assigns short-term and long-term parking spots.

	v1 06.12.2020
*/


#include "myArray.h"
#include "parkhaus.h"

int main() try
{
	/*MyArray<int, 2> mine{2,3};
	mine.printall();*/

	Parkhaus meinParkhaus{};
	meinParkhaus.menue();

	return 0;
}
catch (const std::exception& e)
{
	std::cerr << e.what();
	return -1;
}
catch (...)
{
	std::cerr << "unknown error";
	return -2;
}