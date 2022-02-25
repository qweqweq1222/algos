#include<vector>
#include<iostream>
#include<exception>
#include <initializer_list>

class M3i
{
public:
    M3i(): ten(shared_ptr(nullptr)), rows(0), cols(0), depth(0){};
    M3i(const M3i& tensor): ten(tensor.ten), rows(tensor.rows), cols(tensor.cols), depth(tensor.depth){};
    M3i(int rows_, int cols_, int depth_ = 1) noexcept;
    M3i(const std::initializer_list<int> &list);
    M3i(M3i&&) = default;
    ~M3i() = default;

    int& at(const int row_, const int column_, const int depth_);
    int at(const int row_, const int col, const int depth_) const;

    M3i& operator = (const M3i&);
    M3i& operator = (M3i&& ) = default;

    M3i clone() const;
    void resize(int rows_, int cols_, int depth_);
    int size(const int dim);

private:
    struct truc
    {
        int* ptr_;
        int counter;
    };
    class shared_ptr
    {
    public:
        shared_ptr()
        {
            gen = nullptr;
            gen->ptr_ = nullptr;
            gen->counter = 1;
        }
        shared_ptr(int* ptr)
        {
            gen = new truc;
            gen->ptr_ = ptr;
            gen->counter = 1;
        }
        shared_ptr(const shared_ptr& ptr)
        {
            gen = ptr.gen;
            ++(gen->counter);
        }
        ~shared_ptr()
        {
            if(gen->counter == 1)
                delete[] gen->ptr_;
            else
                --(gen->counter);
        }
        shared_ptr& operator =(const shared_ptr& ptr)
        {
            gen = ptr.gen;
            ++gen->counter;
            return *this;
        }
        int* GetGen() const
        {
            return gen->ptr_;
        }
        truc* GetTruck() const
        {
            return gen;
        }

    private:
        truc* gen;
    };
    shared_ptr ten;
    int rows;
    int cols;
    int depth;
};

std::ostream& operator << (std::ostream& ostrm, M3i& r) noexcept;
std::istream& operator >> (std::istream& istrm , M3i& r) noexcept;

