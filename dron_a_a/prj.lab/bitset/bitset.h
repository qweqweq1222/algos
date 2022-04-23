//
// Created by anreydron on 26.03.2022.
//

#ifndef BitSet__BitSet_H
#define BitSet__BitSet_H
#include <cstdint>
#include <iosfwd>
class BitSet
{
private:
	class BitHolder;
public:

	BitSet() = default;
	BitSet(BitSet&& other) = default;
	BitSet(const BitSet& other) = default;
	BitSet(const int size, const bool val = false);
	~BitSet() = default;
	BitSet& operator = (const BitSet& other) = default;
	BitSet& operator = (BitSet&& other) = default;
	BitSet& operator |= (const BitSet& other);
	BitSet& operator &= (const BitSet& other);
	BitSet& operator ^= (const BitSet& other);
	const BitSet operator~();
	void operator << (const int len);
	void operator >> (const int len);
	int Size () const;
	void Resize(const int size);
	void Fill(const bool val);
	BitHolder& operator [] (const int index);
	bool operator[](const int index) const;

private:
	struct BitHolder
	{
		uint8_t* byte_ptr;
		uint8_t mask;
		BitHolder() = delete;
		BitHolder(uint8_t* byte_ptr, uint8_t mask) : byte_ptr(byte_ptr), mask(mask){
			//std::cout << "bytes: " << int(*byte_ptr) << " mask: " << int(mask) << std::endl;
		};
		BitHolder(const BitHolder&) = delete;
		BitHolder(BitHolder&&) = delete;
		BitHolder&
		operator=(const BitHolder&) = default;
		BitHolder&
		operator=(BitHolder&&) = default;
		BitHolder& operator=(bool st) {
			//std::cout << int(*byte_ptr) << " " << int(mask) << std::endl;
			*byte_ptr = (st) ? (*byte_ptr | mask) : (*byte_ptr & ~mask);
			return *this;
		}
		explicit operator bool() const {
			uint8_t check = *byte_ptr & mask;
			//std::cout << "conversion &: " << int(check) << std::endl;
			return ((*byte_ptr & mask) != 0);
		}
	};
	int size;
	uint8_t* set;
};
std::ostream& operator<<(std::ostream& ostrm, const BitSet& bs);
std::istream& operator>>(std::istream& istrm, BitSet& bs);
const BitSet operator|(const BitSet& first, const BitSet& second);
const BitSet operator&(const BitSet& first, const BitSet& second);
const BitSet operator^(const BitSet& first, const BitSet& second);
const BitSet operator^ (const BitSet& left, const BitSet& right);
const BitSet operator& (const BitSet& left, const BitSet& right);
const BitSet operator| (const BitSet& left, const BitSet& right);
#endif //BitSet__BitSet_H
