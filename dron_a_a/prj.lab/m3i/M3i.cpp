#include<vector>
#include<iostream>
#include<exception>
#include<string>
#include<algorithm>
#include "M3i.h"

M3i::M3i(int rows_, int cols_, int depth_) noexcept: ten(shared_ptr(new int[rows_*cols_*depth_])), rows(rows_), cols(cols_), depth(depth_)
{
    for(int i = 0; i < rows_*cols_*depth_; ++i)
        ten.GetGen()[i] = 0;
}

M3i::M3i(const std::initializer_list<int> &list) : ten(shared_ptr(new int [list.size()])), rows(1), cols(list.size()), depth(1)
{
    int count = 0;
    for(auto &element : list)
    {
        ten.GetGen()[count] = element;
        ++count;
    }
}
M3i& M3i::operator = (const M3i& object)
{
    ten = object.ten;
    rows = object.rows;
    cols = object.cols;
    depth = object.depth;
    return *this;
}

M3i M3i::clone() const
{
    int *curr = ten.GetGen();
    int *curr_ = new int [rows*cols*depth];
    for(int i = 0; i <  rows*cols*depth; ++i)
        curr_[i] = curr[i];

    M3i cloned = M3i();

    cloned.ten = shared_ptr(curr_);
    cloned.depth = depth;
    cloned.cols = cols;
    cloned.rows = rows;

    return cloned;
}

int& M3i::at(const int row_, const int column_, const int depth_)
{
    if( row_ > rows || column_ > cols || depth_ > depth)
        throw std::out_of_range("index is out of range");
    return ten.GetGen()[depth*cols*row_ + depth*column_ + depth_];
}

int M3i::at(const int row_, const int column_, const int depth_) const
{
    if( row_ > rows || column_ > cols || depth_ > depth)
        throw std::out_of_range("index is out of range");
    int a = (ten.GetGen())[depth*cols*row_ + depth*column_ + depth_];
    return a;
}

void M3i::resize (int rows_, int cols_, int depth_)
{
    int* prev = ten.GetGen();
    int* new_data = new int [rows_ * cols_ * depth_];
    for(int i = 0; i < rows_*cols_*depth_; ++i)
        new_data[i] = 0;
    for(int i = 0; i < std::min(rows_, rows); ++i)
        for(int j = 0; j < std::min(cols_, cols); ++j)
            for(int k = 0; k < std::min(depth_, depth); ++k)
                new_data[i * depth_ * cols_ + j * depth_ + k] = prev[i * depth_ * cols_ + j * depth_ + k];

    ten.GetTruck()->ptr_ = new_data;
    delete [] prev;
    rows = rows_;
    cols = cols_;
    depth = depth_;
}

int M3i::size(const int dim)
{
    if(dim >= 3)
        throw std::out_of_range("index is out of range");
    else
    {
        if(dim == 0)
            return rows;
        else if(dim == 1)
            return cols;
        else
            return depth;
    }
}

std::istream& operator >> (std::istream& istrm , M3i& r) noexcept
{
    std::string str;
    int size = 0;
    for (int i = 0; i < r.size(0); ++i)
    {
        for (int j = 0; j < r.size(1); ++j)
        {
            std::cout << "[" << i << j <<  "] number____number " << r.size(2) << " times ";
            std::getline(istrm, str);
            for (int k = 0; k < r.size(2); ++k)
            {
                r.at(i,j,k) = std::stoi(str);
                size = std::to_string( r.at(i,j,k)).length();
                if( k != r.size(2) - 1)
                    str.erase(str.begin(), str.begin() + size + 1);
            }
            std::cout << std::endl;
        }
    }

}
std::ostream& operator << (std::ostream& ostrm, M3i& r) noexcept
{
    ostrm << "[" << std::endl;
    for (int i = 0; i < r.size(0); ++i)
    {
        ostrm << "[ ";
        for (int j = 0; j < r.size(1); ++j)
        {
            ostrm << "[";
            for (int k = 0; k < r.size(2); ++k)
            {
                if (k != r.size(2) - 1)
                    ostrm << r.at(i, j, k) << ",";
                else
                    ostrm << r.at(i, j, k);
            }
            ostrm << "], ";
        }
        ostrm << " ]" << std::endl;
    }
    ostrm << "]" << std::endl;
    return ostrm;
}
