//
// Created by anreydron on 26.03.2022.
//
#include <bitset/bitset.h>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
BitSet::BitSet(const int size, const bool val)
{
	this->size = size;
	int len = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	set = new uint8_t [len];

	if (!val) {
		for (int i = 0; i < len; ++i)
			set[i] = 0;
		capacity = 0;
	}
	else
	{
		int tail = size - 8 * (size / 8);
		int result = 0;
		for(int i = 0; i < len; ++i)
			set[i] = 255;
		for(int i = 0; i < tail; ++i) {
			result += int(pow(2, 7 - i));
		}
		set[len-1] = (result != 0) ? set[len-1] & result : set[len -1];
		capacity = size;
	}
}

void BitSet::operator << (const int len)
{
	int iteration = (capacity % 8 == 0) ? capacity : (capacity + 1);
	uint8_t first_sign_ = 0;
	uint8_t first_sign = 0;
	for(int j = 0; j < len; ++j)
	{
		first_sign = set[iteration - 1] & 128;
		set[iteration - 1] <<= 1;
		for (int i = (iteration > 1) ? (iteration - 2) : 0; i >= 0; --i)
		{
			first_sign_ = set[i] & 128;
			set[i] = set[i] << 1;
			if(first_sign == 128)
				set[i] = set[i] | 1;
			first_sign = first_sign_;
		}
		capacity = (capacity > 0) ? (capacity - 1) : capacity;
	}
	GetCapacity();
	// only size elements
}

void BitSet::operator >> (const int len)
{
	int length = (capacity % 8 == 0) ? (capacity / 8) : (1 + (size / 8));
	uint8_t first_sign_ = 0;
	uint8_t first_sign = 0;
	for(int j = 0; j < len; ++j)
	{
		first_sign = set[0] & 1;
		set[0] >>= 1;
		for (int i = 1; i < length; ++i)
		{
			first_sign_ = set[i] & 1;
			set[i] = set[i] >> 1;
			if(first_sign == 1)
				set[i] = set[i] | 128;
			first_sign = first_sign_;
		}
		capacity = (capacity < size) ? (capacity + 1) : capacity;
	}
	BitSet equalizer(size, true);
	GetCapacity();
	*this & equalizer;
}

void BitSet::operator ~ ()
{
	int length = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	for (int i = 0; i < length; ++i)
		set[i] = ~set[i];

	BitSet equalizer(size, true);
	GetCapacity();
	*this & equalizer;
}

BitSet& BitSet::operator & (BitSet& other)
{
	int length = (capacity % 8 == 0) ? int((capacity / 8)) : int((1 + (capacity / 8)));
	int other_length = (other.capacity % 8 == 0) ? int((other.capacity / 8)) : int((1 + (other.capacity / 8)));
	int minimum = std::min(length, other_length);
	for(int i = 0; i < minimum; ++i)
		set[i] &= other.set[i];
	for(int i = minimum; i < length; ++i)
		set[i] = 0;
	GetCapacity();
	return *this;
}

BitSet& BitSet::operator | (BitSet& other)
{
	int length = (capacity % 8 == 0) ? int((capacity / 8)) : int((1 + (capacity / 8)));
	int other_length = (other.capacity % 8 == 0) ? int((other.capacity / 8)) : int((1 + (other.capacity / 8)));
	int minimum = std::min(length, other_length);
	for(int i = 0; i < minimum; ++i)
		set[i] |= other.set[i];
	GetCapacity();
	return *this;
}

BitSet& BitSet::operator ^ (BitSet& other)
{
	int length = (capacity % 8 == 0) ? int((capacity / 8)) : int((1 + (capacity / 8)));
	int other_length = (other.capacity % 8 == 0) ? int((other.capacity / 8)) : int((1 + (other.capacity / 8)));
	int minimum = std::min(length, other_length);
	for(int i = 0; i < minimum; ++i)
		set[i] ^= other.set[i];
	GetCapacity();
	return *this;
}
void BitSet::Resize(const int size_)
{
	int len = (size_ % 8 == 0) ? int((size_ / 8)) : int((1 + (size_ / 8)));
	int len_ = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	int minimum = std::min(len, len_);
	auto* set_ = new uint8_t [len];
	for(int i = 0; i < minimum; ++i)
		set_[i] = set[i];
	for(int i = minimum; i < len; ++i)
		set_[i] = 0;
	delete [] set;
	set = set_;
	size = size_;
}

void BitSet::GetCapacity()
{
	int n_block = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	std::vector<uint8_t> vec = {1,2,4,8,16,32,64,128};
	for(int i = n_block - 1; i >=0; --i) {
		if(set[i] != 0) {
			for(auto mask : vec){
				if(mask & set[i])
				{
					i = 0;
					break;
				} else {
					capacity -= 1;
				}
			}
			break;
		} else {
			capacity -= 8;
		}
	}
}
int BitSet::Capacity() const { return capacity; }
int BitSet::Size() const { return size; }
BitSet::BitHolder& BitSet::operator[](const int index)
{
	int pos = index / 8;
	int idx = index%8;
	std::vector<uint8_t> vec = {1,2,4,8,16,32,64,128};
	auto* bh = new BitSet::BitHolder(&set[pos], vec[7 - idx]);
	return *bh;
}