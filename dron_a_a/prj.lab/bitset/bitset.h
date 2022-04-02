#ifndef BitSet__BitSet_H
#define BitSet__BitSet_H
#include <cstdint>
#include <iostream>
class BitSet
{
public:
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

		BitHolder& operator=(const BitHolder&) = default;
		BitHolder& operator=(BitHolder&&) = default;
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

	BitSet() = default;
	BitSet(BitSet&& other) = default;
	BitSet(const BitSet& other) = default;
	BitSet(const int size, const bool val = false);

	~BitSet() = default;

	BitSet& operator = (const BitSet& other) = default;
	BitSet& operator = (BitSet&& other) = default;
	BitSet& operator | (BitSet& other);
	BitSet& operator & (BitSet& other);
	BitSet& operator ^ (BitSet& other);
	void operator << (const int len);
	void operator >> (const int len);
	void operator ~ ();

	int Size () const;
	void GetCapacity();
	int Capacity() const;
	void Resize(const int size);
	BitHolder& operator [] (const int index);
	BitHolder at(int idx);
	bool operator[](int idx) const;

private:
	int size;
	int capacity;
	uint8_t* set;
};

#endif //BitSet__BitSet_H
