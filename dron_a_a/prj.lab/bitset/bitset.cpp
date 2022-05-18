//
// Created by anreydron on 26.03.2022.
//
#include "bitset.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
BitSet::BitSet(const int size_, const bool val)
{
	if (size_ <= 0) throw std::invalid_argument("invalid input");
	this->size = size_;
	int len = (size_ % 8 == 0) ? int((size_ / 8)) : int((1 + (size_ / 8)));
	set = new uint8_t [len];
	if (!val)
		for (int i = 0; i < len; ++i)
			set[i] = 0;
	else {
		int tail = size_ - 8 * (size_ / 8);
		int result = 0;
		for(int i = 0; i < len; ++i) set[i] = 255;
		for(int i = 0; i < tail; ++i) result += int(pow(2, i));
		set[len-1] = (result != 0) ? set[len-1] & result : set[len -1];
	}
	size = size_;
}
BitSet::BitSet(BitSet&& other):set(other.set), size(other.size)
{
	other.size = 0;
	other.set = nullptr;
}
BitSet& BitSet::operator = (BitSet&& other) noexcept
{
	if(this != &other)
	{
		delete[] set;
		set = other.set;
		size = other.size;
		other.set = nullptr;
		other.size = 0;
	}
}
void BitSet::operator << (const int len)
{
	int iteration = (size % 8 == 0) ? size : (size + 1);
	uint8_t first_sign_ = 0;
	uint8_t first_sign = 0;
	for(int j = 0; j < len; ++j) {
		first_sign = set[iteration - 1] & 128;
		set[iteration - 1] <<= 1;
		for (int i = (iteration > 1) ? (iteration - 2) : 0; i >= 0; --i) {
			first_sign_ = set[i] & 128;
			set[i] = set[i] << 1;
			if(first_sign == 128) set[i] = set[i] | 1;
			first_sign = first_sign_;
		}
	}
}
void BitSet::operator >> (const int len)
{
	int length = (size % 8 == 0) ? (size / 8) : (1 + (size / 8));
	uint8_t first_sign_ = 0;
	uint8_t first_sign = 0;
	for(int j = 0; j < len; ++j) {
		first_sign = set[0] & 1;
		set[0] >>= 1;
		for (int i = 1; i < length; ++i) {
			first_sign_ = set[i] & 1;
			set[i] = set[i] >> 1;
			if(first_sign == 1) set[i] = set[i] | 128;
			first_sign = first_sign_;
		}
	}
	BitSet equalizer(size, true);
	*this & equalizer;
}
BitSet& BitSet::operator = (const BitSet& other)
{
	size = other.size;
	int length = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	delete[] set;
	set = new uint8_t(length);
	for (int i = 0; i < length; ++i)
		set[i] = other.set[i];
	return *this;
}
BitSet& BitSet::operator &= (const BitSet& other)
{
	if (size != other.size)
		throw std::invalid_argument("l.size != r.size");
	int length = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	int other_length = (other.size % 8 == 0) ? int((other.size / 8)) : int((1 + (other.size / 8)));
	int minimum = std::min(length, other_length);
	for(int i = 0; i < minimum; ++i)
		set[i] &= other.set[i];
	for(int i = minimum; i < length; ++i)
		set[i] = 0;
	return *this;
}
BitSet& BitSet::operator |= (const BitSet& other)
{
	if (size != other.size)
		throw std::invalid_argument("l.size != r.size");
	int length = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	int other_length = (other.size % 8 == 0) ? int((other.size / 8)) : int((1 + (other.size / 8)));
	int minimum = std::min(length, other_length);
	for(int i = 0; i < minimum; ++i)
		set[i] |= other.set[i];
	return *this;
}
BitSet& BitSet::operator ^= (const BitSet& other)
{
	if (size != other.size)
		throw std::invalid_argument("l.size != r.size");
	int length = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	for(int i = 0; i < length; ++i)
		set[i] ^= other.set[i];
	return *this;
}
void BitSet::Resize(const int size_)
{
	if (size_ <= 0)
		throw std::invalid_argument("invalid input");
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
int BitSet::Size() const { return size; }
BitSet::BitHolder& BitSet::operator[](const int index)
{
	if (index < 0 || index >= size)
		throw std::out_of_range("index is out of range");
	int pos = index / 8;
	int idx = index%8;
	std::vector<uint8_t> vec = {1,2,4,8,16,32,64,128};
	auto* bh = new BitSet::BitHolder(&set[pos], vec[idx]);
	return *bh;
}
bool BitSet::operator[](const int index) const {
	if (index < 0 || index >= size) {
		throw std::out_of_range("index is out of range");
	}
	uint8_t mask = 1;
	int array_index = index / 8;
	return (set[array_index] >> (index % 8)) & mask;
}
const BitSet operator^ (const BitSet& left, const BitSet& right)
{
	BitSet result(left.Size(), false);
	if (left.Size() != right.Size())
		throw std::invalid_argument("invalid input");
	for(int i = 0; i < left.Size(); ++i)
		result[i] = (left[i] != right[i]);
	return result;
}
const BitSet operator& (const BitSet& left, const BitSet& right) { return BitSet(left) &= right; }
const BitSet operator| (const BitSet& left, const BitSet& right) { return BitSet(left) |= right; }
std::ostream& operator<<(std::ostream& ostrm, const BitSet& bs) {
	for (int i = 0; i < bs.Size(); ++i)
		ostrm << bs[i];
	return ostrm;
}
std::istream& operator>>(std::istream& istrm, BitSet& bs) {
	std::string bs_str;
	istrm >> bs_str;
	if (istrm.rdstate() == std::ios_base::failbit)
		return istrm;
	int size = bs_str.size();
	if (size == 0) {
		istrm.clear(std::ios_base::failbit);
		return istrm;
	}
	bs = BitSet(size);
	for (int i = 0; i < size; ++i) {
		if (bs_str[i] == '1' || bs_str[i] == '0')
			bs[i] = bs_str[i] == '1';
		else {
			istrm.clear(std::ios_base::failbit);
			return istrm;
		}
	}
	return istrm;
}
const BitSet  BitSet::operator~()
{

	BitSet bs = *this;
	int len = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	int tail = size % 8;
	for (int i = 0; i < size / 8; ++i) {
		bs.set[i] = ~set[i];
	}
	if (tail > 0) {
		uint16_t mask = UINT8_MAX >> (8 - tail);
		bs.set[len - 1] = mask & ~set[len - 1];
	}
	return bs;
}
void BitSet::Fill(const bool val)
{
	for(int i = 0; i < size / 8; ++i)
		set[i] = !val ? 0 : 255;
	int tail = size - 8*(size/8);
	int len = (size % 8 == 0) ? int((size / 8)) : int((1 + (size / 8)));
	int result = 0;
	if(tail > 0)
	{
		set[len - 1] = !val ? 0 : 255;
		for(int i = 0; i < tail; ++i)
			result += int(pow(2, i));
		set[len-1] = set[len-1] & result;
	}
}