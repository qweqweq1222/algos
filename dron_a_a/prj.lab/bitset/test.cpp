#include <iostream>
#include <bitset/bitset.h>

void Print(Bitmap &bitmap)
{

	for(int i = 0; i < bitmap.Size(); ++i) {
		if(bitmap[i])
			std::cout << 1 << " ";
		else
			std::cout << 0 << " ";
	}
	std::cout << std::endl;
}

int main()
{
	Bitmap bitmap(16, true);
	Bitmap bitmap_(8, true);
	bitmap & bitmap_;
	std::cout << bitmap.Capacity();
	return 0;
}

