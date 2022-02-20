#include<vector>
#include<iostream>
#include<exception>
class M3i
{
public:
    M3i() = default;
    ~M3i() = default;
    M3i(const M3i& tensor) = default;
    M3i(M3i&& tensor) noexcept : rows(tensor.rows), cols(tensor.cols), depth(tensor.depth), ten(tensor.ten)
    {
        tensor.resize(0,0,0);
    }
    M3i(int rows_, int cols_, int depth_ = 1) noexcept;
    int& operator ()(int row_, int column_, int depth_);
    void resize(int rows_, int cols_, int depth_) noexcept;
    std::vector <std::vector <std::vector <int>>> get_ten() const noexcept;
    const int get_rows() const noexcept;
    const int get_cols() const noexcept;
    const int get_depth() const noexcept;

private:
    std::vector <std::vector <std::vector <int>>> ten;
    int rows;
    int cols;
    int depth;
};

std::istream& operator >> (std::istream& istrm , M3i& r) noexcept;
std::ostream& operator << (std::ostream& ostrm, const M3i& r) noexcept;