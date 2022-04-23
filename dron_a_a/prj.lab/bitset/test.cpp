#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <bitset/bitset.h>
#include <doctest/doctest.h>
bool operator==(const BitSet& left, const BitSet& right) {
	if (left.Size() != right.Size())
		return false;
	for (int i = 0; i < left.Size(); ++i)
		if (left[i] != right[i])
			return false;
	return true;
}

TEST_CASE("resize") {
	int sz= 24;
	BitSet bitset(sz, true);
	int new_size = 34;
	bitset.Resize(new_size);
	CHECK(bitset.Size() == new_size);
	for (int i = 0; i < sz; ++i)
		CHECK(bitset[i]);
	for (int i = sz; i < new_size; ++i)
		CHECK_FALSE(bitset[i]);
	CHECK_THROWS(bitset.Resize(0));
	CHECK_THROWS(bitset.Resize(-1));
}

TEST_CASE("Check_Fill") {
	BitSet bs_ps(10, true);
	BitSet bs_ng(10, false);
	bs_ps.Fill(false);
	CHECK(bs_ps == bs_ng);
}

TEST_CASE("operators") {
	SUBCASE("~") {
		int size = 40;
		BitSet bitset(size, true);
		BitSet minus_bitset = ~bitset;
		CHECK(minus_bitset.Size() == size);
		for (int i = 0; i < size; ++i)
			CHECK_FALSE(minus_bitset[i]);
		BitSet plus_bitset = ~minus_bitset;
		CHECK(plus_bitset.Size() == size);
		CHECK(plus_bitset == bitset);
	}
	SUBCASE("& &=") {
		int size = 10;
		BitSet first(size, true);
		BitSet wrong_second(size + 1, true);
		CHECK_THROWS(first & wrong_second);
		CHECK_THROWS(first &= wrong_second);
		BitSet second(size, true);
		first[0] = 0;
		first[1] = 0;
		first[5] = 0;
		BitSet result(size, true);
		for (auto index : {0, 1, 5})
			result[index] = false;
		auto res = first & second;
		CHECK(res == result);
		first &= second;
		CHECK(first == result);
	}
	SUBCASE("XOR") {
		BitSet bs1(10,true);
		BitSet bs2(10,false);
		BitSet rslt = bs1 ^ bs2;
		CHECK(rslt == bs1);
		BitSet bs3 (10, false);
		BitSet bs4 (10, false);
		for (auto idx : {1,3,5})
		bs3[idx] = true;
		BitSet rslt_ = bs3 ^ bs4;
		CHECK( rslt_ == bs3);
	}
}

TEST_CASE("input/output") {
	BitSet bitset;
	std::stringstream input_stream;
	input_stream << "111110104";
	input_stream >> bitset;
	CHECK(input_stream.fail());
	input_stream << "100qweqeq";
	input_stream >> bitset;
	CHECK(input_stream.fail());
	input_stream << "111101111";
	input_stream >> bitset;
	CHECK(input_stream.fail());
}

