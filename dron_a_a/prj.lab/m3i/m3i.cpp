#include<vector>
#include<iostream>
#include<exception>
#include<string>
#include<algorithm>
#include <m3i/m3i.h>

M3i::shared_ptr::shared_ptr(int* data_, const int cols, const int rows, const int depth, const int counter_) : data(data_), shape{cols,rows,depth}, counter(counter_) {}

M3i::M3i() : ptr(new shared_ptr(nullptr, 0, 0, 0, 1)) {}

M3i::M3i(int rows_, int cols_, int depth_) {
	this->ptr = new shared_ptr(new int[rows_*cols_*depth_], rows_, cols_, depth_, 1);
    if (rows_ <=0 || cols_ <=0 || depth_ <=0)
        throw std::invalid_argument("rows_ <=0 || cols_ <=0 || depth_ <= 0");
    fill(0);
}

M3i::M3i(const M3i& other) {
    ptr = other.ptr;
    ptr->counter++;
}

M3i::M3i(M3i&& other) noexcept {
    ptr = other.ptr;
    other.ptr = nullptr;
}

M3i::M3i(const std::initializer_list<int> &list): ptr(new shared_ptr{ new int[list.size()], 1, static_cast<int>(list.size()), 1, 1}) {
    int i = 0;
    for (auto &element : list) {
        ptr->data[i] = element;
        ++i;
    }
}

M3i::~M3i() {
    if (ptr != nullptr) {
        if (ptr->counter == 1)
            delete[] ptr->data;
        else
            ptr->counter--;
        ptr = nullptr;
    }
}


void M3i::fill(const int val) {
    for (int i = 0; i < ptr->shape[0] * ptr->shape[1] * ptr->shape[2]; ++i)
        ptr->data[i] = val;
}

M3i& M3i::operator = (const M3i& object) {
    ptr = object.ptr;
    ptr->counter++;
    return *this;
}

M3i& M3i::operator = (M3i&& other) {
    if (this != &other) {
        this->~M3i();
        ptr = other.ptr;
        other.ptr = nullptr;
    }
	return *this;
}

M3i M3i::clone() const {
    std::lock_guard<std::recursive_mutex> lock(ptr->mtx);

    M3i cloned(ptr->shape[0], ptr->shape[1], ptr->shape[2]);

    for (int i = 0; i < ptr->shape[0]*ptr->shape[1]*ptr->shape[2]; ++i) {
        cloned.ptr->data[i] = ptr->data[i];
    }

    return cloned;
}

int& M3i::at(const int row_, const int column_, const int depth_) {
    std::lock_guard<std::recursive_mutex> lock(ptr->mtx);

    if (row_ < 0 || column_ < 0 || depth_ < 0 || row_ > this->size(0) || column_ > this->size(1) || depth_ > this->size(2))
        throw std::invalid_argument("invalid_argument");

    return  ptr->data[ptr->shape[2]*ptr->shape[1]*row_ + ptr->shape[2]*column_ + depth_];
}

int M3i::at(const int row_, const int column_, const int depth_) const {
    std::lock_guard<std::recursive_mutex> lock(ptr->mtx);

    if (row_ < 0 || column_ < 0 || depth_ < 0 || row_ > this->size(0) || column_ > this->size(1) || depth_ > this->size(2))
        throw std::invalid_argument("invalid_argument");

    return  ptr->data[ptr->shape[2]*ptr->shape[1]*row_ + ptr->shape[2]*column_ + depth_];
}

void M3i::resize(int rows_, int cols_, int depth_) {
    std::lock_guard<std::recursive_mutex> lock(ptr->mtx);

    if (rows_ <= 0 || cols_ <= 0 || depth_ <= 0)
        throw std::invalid_argument("invalid_argument");

    int* prev = ptr->data;
    int* new_data = new int[rows_ * cols_ * depth_];


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

int M3i::size(const int dim) const {
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

std::istream& operator >> (std::istream& istrm , M3i& r) noexcept {
    std::string str;
    int buffer = 0;
    for (int i = 0; i < r.size(0); ++i) {
        for (int j = 0; j < r.size(1); ++j) {
            for (int k = 0; k < r.size(2); ++k) {
                istrm >> buffer;

                if (istrm.good())
                    r.at(i,j,k) = buffer;
                else {
                    if (istrm.eof())
                        istrm.clear(std::ios_base::failbit | std::ios_base::eofbit);
                    else
                        istrm.clear(std::ios_base::failbit);
                    return istrm;
                }
            }
        }
    }
    return istrm;
}

std::ostream& operator << (std::ostream& ostrm, M3i& r) noexcept {
    ostrm << "size:" << r.size(0) << "x" << r.size(1) << "x" << r.size(2) << std::endl;
    for (int z = 0; z < r.size(2); ++z) {
        for (int x = 0; x < r.size(0); ++x) {
            for (int y = 0; y < r.size(1); ++y) {
                ostrm << r.at(x, y, z) << " ";
            }
            ostrm << std::endl;
        }
        ostrm << std::endl;
    }
    return ostrm;
}
