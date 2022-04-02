#include <iostream>
#include <bitset/bitset.h>

void Print(BitSet &bitmap)
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
	BitSet bitmap(16, true);
	BitSet bitmap_(8, true);
	bitmap & bitmap_;
	std::cout << bitmap.Capacity();
	return 0;
}

