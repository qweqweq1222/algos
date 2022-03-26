//
// Created by anreydron on 26.03.2022.
//

#include "bitmap.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
Bitmap::Bitmap(const int size, const bool val)
{
	this->size = size;
	int len = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	bitmap = new uint8_t [len];

	if (!val) {
		for (int i = 0; i < len; ++i)
			bitmap[i] = 0;
		capacity = 0;
	}
	else
	{
		int tail = size - 8 * (size / 8);
		int result = 0;
		for(int i = 0; i < len; ++i)
			bitmap[i] = 255;
		for(int i = 0; i < tail; ++i) {
			result += int(pow(2, 7 - i));
		}
		bitmap[len-1] = (result != 0) ? bitmap[len-1] & result : bitmap[len -1];
		capacity = size;
	}
}

void Bitmap::operator << (const int len)
{
	int iteration = (capacity % 8 == 0) ? capacity : (capacity + 1);
	uint8_t first_sign_ = 0;
	uint8_t first_sign = 0;
	for(int j = 0; j < len; ++j)
	{
		first_sign = bitmap[iteration - 1] & 128;
		bitmap[iteration - 1] <<= 1;
		for (int i = (iteration > 1) ? (iteration - 2) : 0; i >= 0; --i)
		{
			first_sign_ = bitmap[i] & 128;
			bitmap[i] = bitmap[i] << 1;
			if(first_sign == 128)
				bitmap[i] = bitmap[i] | 1;
			first_sign = first_sign_;
		}
		capacity = (capacity > 0) ? (capacity - 1) : capacity;
	}
	// only size elements
}

void Bitmap::operator >> (const int len)
{
	int length = (capacity % 8 == 0) ? (capacity / 8) : (1 + (size / 8));
	uint8_t first_sign_ = 0;
	uint8_t first_sign = 0;
	for(int j = 0; j < len; ++j)
	{
		first_sign = bitmap[0] & 1;
		bitmap[0] >>= 1;
		for (int i = 1; i < length; ++i)
		{
			first_sign_ = bitmap[i] & 1;
			bitmap[i] = bitmap[i] >> 1;
			if(first_sign == 1)
				bitmap[i] = bitmap[i] | 128;
			first_sign = first_sign_;
		}
		capacity = (capacity < size) ? (capacity + 1) : capacity;
	}
	Bitmap equalizer(size, true);
	*this & equalizer;
}

void Bitmap::operator ~ ()
{
	int length = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	for (int i = 0; i < length; ++i)
		bitmap[i] = ~bitmap[i];

	Bitmap equalizer(size, true);
	*this & equalizer;
}

void Bitmap::Print()
{
	int length = (size % 8 == 0) ? (size / 8) : (1 + (size / 8));
	for(int i = 0; i < length; ++i)
		std::cout << int(bitmap[i]) << " ";
	std::cout << std::endl;
}

Bitmap& Bitmap::operator & (Bitmap& other)
{
	int length = (capacity % 8 == 0) ? int((capacity / 8)) : int((1 + (capacity / 8)));
	int other_length = (other.capacity % 8 == 0) ? int((other.capacity / 8)) : int((1 + (other.capacity / 8)));
	int minimum = std::min(length, other_length);
	for(int i = 0; i < minimum; ++i)
		bitmap[i] &= other.bitmap[i];
	for(int i = minimum; i < length; ++i)
		bitmap[i] = 0;
	return *this;
}

Bitmap& Bitmap::operator | (Bitmap& other)
{
	int length = (capacity % 8 == 0) ? int((capacity / 8)) : int((1 + (capacity / 8)));
	int other_length = (other.capacity % 8 == 0) ? int((other.capacity / 8)) : int((1 + (other.capacity / 8)));
	int minimum = std::min(length, other_length);
	for(int i = 0; i < minimum; ++i)
		bitmap[i] |= other.bitmap[i];
	return *this;
}

Bitmap& Bitmap::operator ^ (Bitmap& other)
{
	int length = (capacity % 8 == 0) ? int((capacity / 8)) : int((1 + (capacity / 8)));
	int other_length = (other.capacity % 8 == 0) ? int((other.capacity / 8)) : int((1 + (other.capacity / 8)));
	int minimum = std::min(length, other_length);
	for(int i = 0; i < minimum; ++i)
		bitmap[i] ^= other.bitmap[i];
	return *this;
}
void Bitmap::Resize(const int size_)
{
	int len = (size_ % 8 == 0) ? int((size_ / 8)) : int((1 + (size_ / 8)));
	int len_ = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	int minimum = std::min(len, len_);
	auto* bitmap_ = new uint8_t [len];
	for(int i = 0; i < minimum; ++i)
		bitmap_[i] = bitmap[i];
	for(int i = minimum; i < len; ++i)
		bitmap_[i] = 0;
	delete [] bitmap;
	bitmap = bitmap_;
	size = size_;
}

int Bitmap::Size() const { return size; }
Bitmap::BoolHolder& Bitmap::operator[](const int index)
{
	int pos = (index % 8 == 0 & index != 0) ? index/8 : (1 + index/8);
	int idx = index - 8*(index/8);
	std::vector<uint8_t> vec = {1,2,4,8,16,32,64,128};
	pos = (pos > 0) ? (pos - 1): pos;
	auto* bh = new Bitmap::BoolHolder(&bitmap[pos], vec[7 - idx]);
	return *bh;
}