#include<vector>
#include<iostream>
#include<exception>
#include<string>
#include<algorithm>
#include <m3i/m3i.h>

M3i::shared_ptr::shared_ptr(int* data_, const int cols, const int rows, const int depth, const int counter_) : data(data_), shape{cols,rows,depth}, counter(counter_){}

M3i::M3i() : ptr(new shared_ptr(nullptr, 0, 0, 0, 1)) {}

M3i::M3i(int rows_, int cols_, int depth_) {
	if (rows_ <= 0 || cols_ <= 0 || depth_ <= 0 )
		throw std::invalid_argument("rows_ <= 0 || cols_ <= 0 || depth_ <= 0");
	ptr = new shared_ptr(new int [rows_*cols_*depth_], rows_,cols_,depth_, 1);
	Fill(0);
}

M3i::M3i(const M3i& other) {
	ptr = other.ptr;
	ptr->counter.fetch_add(1);
}

M3i::M3i(M3i&& other) noexcept {
	ptr = other.ptr;
	other.ptr = nullptr;
}

M3i::M3i(const std::initializer_list<std::initializer_list<std::initializer_list<int>>> &list): ptr(new shared_ptr{nullptr, 0, int(list.size()),0, 0}) {
	ptr->data = new int [list.size()*list.begin()->size()*list.begin()->begin()->size()];
	ptr->shape[0] = list.size();
	ptr->shape[1] = list.begin()->size();
	ptr->shape[2] = list.begin()->begin()->size();

	int i = 0;
	int j = 0;
	int k = 0;
	for (const auto &sublist : list) {
		j = 0;
		for (const auto &subsublist : sublist) {
			k = 0;
			for (const auto &elem : subsublist) {
				ptr->data[ptr->shape[2]*ptr->shape[1]*i + ptr->shape[2]*j + k] = elem;
				++k;
			}
			++j;
		}
		++i;
	}
}

M3i::~M3i() {
	if(ptr != nullptr) {
		if (ptr->counter.fetch_sub(1) == 1)
			delete[] ptr->data;
		ptr = nullptr;
	}
}


void M3i::Fill(const int val) {
	for (int i = 0; i < ptr->shape[0] * ptr->shape[1] * ptr->shape[2]; ++i)
		ptr->data[i] = val;
}

M3i& M3i::operator = (const M3i& object) {
	ptr = object.ptr;
	ptr->counter.fetch_add(1);
	return *this;
}

M3i& M3i::operator = (M3i&& other) {
	std::lock_guard<std::recursive_mutex> lock(ptr->mtx);
	if (this != &other) {
		ptr = other.ptr;
		ptr->counter.fetch_add(1);
		other.~M3i();
	}
	return *this;
}

M3i M3i::Clone() const {
	std::lock_guard<std::recursive_mutex> lock(ptr->mtx);

	M3i Cloned(ptr->shape[0], ptr->shape[1], ptr->shape[2]);

	for (int i = 0; i < ptr->shape[0]*ptr->shape[1]*ptr->shape[2]; ++i) {
		Cloned.ptr->data[i] = ptr->data[i];
	}

	return Cloned;
}

int& M3i::At(const int row_, const int column_, const int depth_) {
	std::lock_guard<std::recursive_mutex> lock(ptr->mtx);

	if (row_ < 0 || column_ < 0 || depth_ < 0 || row_ > this->Size(0) || column_ > this->Size(1) || depth_ > this->Size(2))
		throw std::invalid_argument("invalid_argument");

	return  ptr->data[ptr->shape[2]*ptr->shape[1]*row_ + ptr->shape[2]*column_ + depth_];
}

int M3i::At(const int row_, const int column_, const int depth_) const {
	std::lock_guard<std::recursive_mutex> lock(ptr->mtx);

	if (row_ < 0 || column_ < 0 || depth_ < 0 || row_ > this->Size(0) || column_ > this->Size(1) || depth_ > this->Size(2))
		throw std::invalid_argument("invalid_argument");

	return  ptr->data[ptr->shape[2]*ptr->shape[1]*row_ + ptr->shape[2]*column_ + depth_];
}

void M3i::Resize (int rows_, int cols_, int depth_) {
	std::lock_guard<std::recursive_mutex> lock(ptr->mtx);

	if (rows_ <= 0 || cols_ <= 0 || depth_ <= 0)
		throw std::invalid_argument("invalid_argument");

	int* prev = ptr->data;
	int* new_data = new int [rows_ * cols_ * depth_];


	for (int i = 0; i < rows_*cols_*depth_; ++i)
		new_data[i] = 0;

	for (int i = 0; i < std::min(rows_, ptr->shape[0]); ++i)
		for (int j = 0; j < std::min(cols_, ptr->shape[1]); ++j)
			for (int k = 0; k < std::min(depth_, ptr->shape[2]); ++k)
				new_data[i * depth_ * cols_ + j * depth_ + k] = prev[i * ptr->shape[2]* ptr->shape[1] + j * ptr->shape[2] + k];

	ptr->data = new_data;
	delete [] prev;

	ptr->shape[0] = rows_;
	ptr->shape[1] = cols_;
	ptr->shape[2] = depth_;
}

int M3i::Size(const int dim) const {
	if (dim >= 3)
		throw std::out_of_range("index is out of range");
	else {
		if (dim == 0)
			return ptr->shape[0];
		else if (dim == 1)
			return ptr->shape[1];
		else
			return ptr->shape[2];
	}
}

std::ostream& M3i::WriteTo(std::ostream& ostrm) const noexcept
{
	ostrm << "start tensor" << std::endl;
	ostrm << "shape: " << Size(0) << " " << Size(1) << " " << Size(2) << "\n\n";
	for (int z = 0; z < Size(2); ++z){
		for (int x = 0; x < Size(0); ++x) {
			for (int y = 0; y < Size(1); ++y) {
				ostrm << At(x,y,z) << " ";
			}
			ostrm << std::endl;
		}
		ostrm << std::endl;
	}
	ostrm << "end tensor" << std::endl;
	return ostrm;
}

std::istream& M3i::ReadFrom (std::istream& istrm)
{
	std::string str;
	int shape[3]  = {};
	for (int i = 0; i < 3; ++i) {
		if(!isdigit(istrm.peek())) {
			istrm.clear(std::ios_base::failbit);
			return istrm;
		} else {
			istrm >> shape[i];
			if(!istrm.good())
			{
				istrm.clear(std::ios_base::failbit);
				return istrm;
			}
			if( i != 2)
				istrm.get();
		}
	}
	if(shape[0] <= 0 || shape[1] <= 0 || shape[2] <= 0 || !istrm.good()) {
		istrm.clear(std::ios_base::failbit);
		return istrm;
	}

	Resize(shape[0], shape[1], shape[2]);
	int buffer = 0;
	for (int i = 0; i < Size(0); ++i) {
		for (int j = 0; j < Size(1); ++j) {
			for (int k = 0; k < Size(2); ++k) {
				int number;
				istrm >> number;
				if(istrm.good())
					At(i, j, k) = number;
				/*
				char minus = '-';
				if(istrm.peek() != '\n') {
					istrm.clear(std::ios_base::failbit);
					return istrm;
				} else {
					istrm.get();
					if(!std::isdigit(istrm.peek()) && !(istrm.peek() == minus)) {
						istrm.clear(std::ios_base::failbit);
						return istrm;
					}
					istrm >> buffer;
					if (istrm.good())
						At(i,j,k) = buffer;
					else {
						if (istrm.eof())
							istrm.clear(std::ios_base::failbit | std::ios_base::eofbit);
						else
							istrm.clear(std::ios_base::failbit);
						return istrm;
					}
				}*/
			}
		}
	}
	return istrm;
}

std::ostream& operator << (std::ostream& ostrm, M3i& r) noexcept { return r.WriteTo(ostrm); }
std::istream& operator >> (std::istream& istrm , M3i& r) { return r.ReadFrom(istrm); }