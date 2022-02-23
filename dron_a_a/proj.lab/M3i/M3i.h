#include<vector>
#include<iostream>
#include<exception>
class M3i
{
public:
    M3i(): ten(nullptr), rows(0), cols(0), depth(0){};
    M3i(const M3i& tensor);
    M3i(int rows_, int cols_, int depth_ = 1) noexcept;
    ~M3i()
    {
        for(int i=0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                delete [] ten[i][j];
            }
            delete[] ten[i];
        }
        delete [] ten;
    }
    int& operator ()(int row_, int column_, int depth_);
    void resize(int rows_, int cols_, int depth_) noexcept;
    int*** get_ten() const noexcept;
    const int get_rows() const noexcept;
    const int get_cols() const noexcept;
    const int get_depth() const noexcept;

private:
    int*** ten;
    int rows;
    int cols;
    int depth;
};

std::ostream& operator << (std::ostream& ostrm, const M3i& r) noexcept;
std::istream& operator >> (std::istream& istrm , M3i& r) noexcept;

