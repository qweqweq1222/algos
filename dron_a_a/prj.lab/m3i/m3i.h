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

class M3i
{
public:
	M3i();
	M3i(const M3i& tensor);
	M3i(int rows_, int cols_, int depth_);
	M3i(int rows_, int cols_, int depth_, int value);
	M3i(const std::initializer_list<std::initializer_list<std::initializer_list<int>>> &list);
	M3i(M3i&&) noexcept;

	~M3i();

	M3i& operator = (const M3i&);
	M3i& operator = (M3i&& );

	M3i Clone() const;
	int Size(const int dim) const;
	int& At(const int row_, const int column_, const int depth_);
	int At(const int row_, const int col, const int depth_) const;
	void Resize(int rows_, int cols_, int depth_);
	void Fill(const int val);
	std::istream& ReadFrom (std::istream& istrm);
	std::ostream& WriteTo (std::ostream& ostrm) const noexcept;

private:
	struct shared_ptr
	{
		shared_ptr(int* _data, const int col, const int row, const int depth, const int counter_);

		int* data = nullptr;
		int shape[3] = {0,0,0};
		std::atomic<int> counter{0};

		std::recursive_mutex mtx;
	};

	shared_ptr* ptr = nullptr;
};

std::ostream& operator << (std::ostream& ostrm, M3i& r) noexcept;
std::istream& operator >> (std::istream& istrm , M3i& r);

#endif  //  ALGOS_DRON_A_A_PRJ_LAB_M3I_M3I_H_

