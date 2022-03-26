//
// Created by anreydron on 26.03.2022.
//

#ifndef INC_520_B_ALGOS_DRON_A_A_PRJ_LAB_BITMAP_BITMAP_H
#define INC_520_B_ALGOS_DRON_A_A_PRJ_LAB_BITMAP_BITMAP_H

//
// Created by anreydron on 26.03.2022.
//


#include <cstdint>
#include <iostream>
class Bitmap
{
public:
	struct BoolHolder
	{
		uint8_t* byte_ptr;
		uint8_t mask;
		BoolHolder() = delete;
		BoolHolder(uint8_t* byte_ptr, uint8_t mask) : byte_ptr(byte_ptr), mask(mask){
			//std::cout << "bytes: " << int(*byte_ptr) << " mask: " << int(mask) << std::endl;
		};

		BoolHolder(const BoolHolder&) = delete;
		BoolHolder(BoolHolder&&) = delete;

		BoolHolder&
		operator=(const BoolHolder&) = default;
		BoolHolder&
		operator=(BoolHolder&&) = default;
		BoolHolder& operator=(bool st) {
			std::cout << int(*byte_ptr) << " " << int(mask) << std::endl;
			*byte_ptr = (st) ? (*byte_ptr | mask) : (*byte_ptr & ~mask);
			return *this;
		}

		explicit operator bool() const {
			uint8_t check = *byte_ptr & mask;
			//std::cout << "conversion &: " << int(check) << std::endl;
			return ((*byte_ptr & mask) != 0);
		}
	};

	Bitmap() = default;
	Bitmap(Bitmap&& other) = default;
	Bitmap(const Bitmap& other) = default;
	Bitmap(const int size, const bool val = false);

	~Bitmap() = default;

	Bitmap& operator = (const Bitmap& other) = default;
	Bitmap& operator = (Bitmap&& other) = default;
	Bitmap& operator | (Bitmap& other);
	Bitmap& operator & (Bitmap& other);
	Bitmap& operator ^ (Bitmap& other);
	void operator << (const int len);
	void operator >> (const int len);
	void operator ~ ();

	int Size () const;
	void Resize(const int size);
	BoolHolder& operator [] (const int index);
	void Print();

private:
	int size;
	int capacity;
	uint8_t* bitmap;
};

#endif //INC_520_B_ALGOS_DRON_A_A_PRJ_LAB_BITMAP_BITMAP_H
