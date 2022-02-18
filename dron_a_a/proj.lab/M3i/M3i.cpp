#include<vector>
#include<iostream>
#include<exception>
#include "M3i.h"

    M3i::M3i(const int rows_,const int cols_,const int depth_) noexcept: rows(rows_), cols(cols_), depth(depth_),
    ten(std::vector <std::vector <std::vector <int>>>(rows_, std::vector< std::vector<int> >(cols_, std::vector <int>(depth_, 0)))) {}

    int& M3i::operator ()(int row_, int column_, int depth_)
    {
        if( row_ > rows || column_ > cols || depth_ > depth)
            throw std::out_of_range("index is out of range");
        return ten[row_-1][column_-1][depth_-1];
    }

    void M3i::resize(int rows_, int cols_, int depth_) noexcept
    {
        ten.resize(rows_);
        rows = rows_;
        cols = cols_;
        depth = depth_;
        for(int i =0;i<cols_;++i)
        {
            ten[i].resize(cols_);
            for(int j =0; j < depth_; j++)
                ten[i][j].resize((depth_), 0);
        }
    }

    std::vector <std::vector <std::vector <int>>> M3i::get_ten() const noexcept
    {
        return ten;
    }

    const int& M3i::get_rows() const noexcept
    {
        return rows;
    }

    const int& M3i::get_cols() const noexcept
    {
        return cols;
    }

    const int& M3i::get_depth() const noexcept
    {
        return depth;
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
