/*
 * andrey dron
 * 3-d tensor implementation
 * */

#ifndef ALGOS_DRON_A_A_PRJ_LAB_M3I_M3I_H_
#define ALGOS_DRON_A_A_PRJ_LAB_M3I_M3I_H_
#include<iosfwd>
#include <mutex>
#include <atomic>
#include <initializer_list>

class M3i {
 public:
    M3i();
    M3i(const M3i& tensor);
    M3i(int rows_, int cols_, int depth_ = 1) noexcept;
    M3i(const std::initializer_list<int> &list);
    M3i(M3i&&) noexcept;

    ~M3i();

    M3i& operator = (const M3i&);
    M3i& operator = (M3i&&);

    M3i clone() const;
    int size(const int dim) const;
    int& at(const int row_, const int column_, const int depth_);
    int at(const int row_, const int col, const int depth_) const;
    void resize(int rows_, int cols_, int depth_);
    void fill(const int val);


 private:
    struct shared_ptr {
        shared_ptr(int* _data, const int col, const int row, const int depth, const int counter_);

        int* data = nullptr;
        int shape[3] = {0,0,0};
        std::atomic<int> counter{0};

        std::recursive_mutex mtx;
    };

    shared_ptr* ptr = nullptr;
};

std::ostream& operator << (std::ostream& ostrm, M3i& r) noexcept;
std::istream& operator >> (std::istream& istrm , M3i& r) noexcept;

#endif  //  ALGOS_DRON_A_A_PRJ_LAB_M3I_M3I_H_

