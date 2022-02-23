#include<vector>
#include<iostream>
#include<exception>
#include<string>
#include<algorithm>
#include "M3i.h"

M3i::M3i(const M3i& tensor): rows(tensor.rows), cols(tensor.cols), depth(tensor.depth)
{
    ten = new int** [rows];
    for(int i =0; i < rows; ++i)
    {
        ten[i] = new int* [cols];
        for (int j = 0; j < cols; ++j)
        {
            ten[i][j] = new int[depth];
            for (int k =0; k < depth; ++k)
                ten[i][j][k] = tensor.ten[i][j][k];
        }
    }
}
M3i::M3i(int rows_, int cols_, int depth_) noexcept: rows(rows_), cols(cols_), depth(depth_)
{
    ten = new int** [rows];
    for(int i =0; i < rows; ++i)
    {
        ten[i] = new int* [cols];
        for (int j = 0; j < cols; ++j)
        {
            ten[i][j] = new int[depth];
            for (int k =0; k < depth; ++k)
                ten[i][j][k] = 0;
        }
    }
}

int& M3i::operator ()(int row_, int column_, int depth_)
{
    if( row_ > rows || column_ > cols || depth_ > depth)
        throw std::out_of_range("index is out of range");
    return ten[row_-1][column_-1][depth_-1];
}
void M3i::resize (int rows_, int cols_, int depth_) noexcept
{
    int*** buffer = ten;
    ten = new int** [rows_];

    for(int i = 0; i < rows_; ++i)
    {
        ten[i] = new int* [cols_];
        for (int j = 0; j < cols_; ++j)
        {
            ten[i][j] = new int[depth_];
            for (int k = 0; k < depth_; ++k)
                ten[i][j][k] = 0;
        }
    }

    for(int i = 0; i < std::min(rows_, rows); ++i)
        for (int j = 0; j < std::min(cols_, cols); ++j)
            for (int k = 0; k < std::min(depth_, depth); ++k)
                ten[i][j][k] = buffer[i][j][k];

    for(int i=0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            delete [] buffer[i][j];
        }
        delete[] buffer[i];
    }
    delete [] buffer;

    cols = cols_;
    rows = rows_;
    depth = depth_;
}

int *** M3i::get_ten() const noexcept
{
    return ten;
}
const int M3i::get_rows() const noexcept
{
    return rows;
}
const int M3i::get_cols() const noexcept
{
    return cols;
}
const int M3i::get_depth() const noexcept
{
    return depth;
}

std::istream& operator >> (std::istream& istrm , M3i& r) noexcept
{
    std::string str;
    int size = 0;
    for (int i = 0; i < r.get_rows(); ++i)
    {
        for (int j = 0; j < r.get_cols(); ++j)
        {
            std::cout << "[" << i << j <<  "] number____number " << r.get_depth() << " times ";
            std::getline(istrm, str);
            for (int k = 0; k < r.get_depth(); ++k)
            {
                (r.get_ten())[i][j][k] = std::stoi(str);
                size = std::to_string((r.get_ten())[i][j][k]).length();
                if( k != r.get_depth() - 1)
                    str.erase(str.begin(), str.begin() + size + 1);
            }
            std::cout << std::endl;
        }
    }

}
std::ostream& operator << (std::ostream& ostrm, const M3i& r) noexcept {
    ostrm << "[" << std::endl;
    for (int i = 0; i < r.get_rows(); ++i) {
        ostrm << "[ ";
        for (int j = 0; j < r.get_cols(); ++j) {
            ostrm << "[";
            for (int k = 0; k < r.get_depth(); ++k)
                if (k != r.get_depth() - 1)
                    ostrm << r.get_ten()[i][j][k] << ",";
                else
                    ostrm << r.get_ten()[i][j][k];
            if (j != r.get_cols() - 1)
                ostrm << "], ";
            else
                ostrm << "] ]," << std::endl;
        }
    }
    ostrm << "]";
    return ostrm;
}
