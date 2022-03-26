#include <iostream>
#include "bitmap.h"

int main()
{
	Bitmap bitmap(16, true);
	bitmap.Print();
	for(int i = 0; i < 16; ++i) {
		if (bitmap[i])
			std::cout << "T ";
		else
			std::cout << "F ";
	}
	std::cout << std::endl;
	bitmap[15] = false;
	for(int i = 0; i < 16; ++i) {
		if (bitmap[i])
			std::cout << "T ";
		else
			std::cout << "F ";
	}
	return 0;
}

