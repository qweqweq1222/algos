#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <bitset/bitset.h>
#include <doctest/doctest.h>
bool operator== (const BitSet& left, const BitSet& right) {
	if (left.Size() != right.Size()) {
		return false;
	}
	for (int i = 0; i < left.Size(); ++i) {
		if (left[i] != right[i]) {
			return false;
		}
	}
	return true;
}

bool operator!=(const BitSet& left, const BitSet& right) {
	return !(left == right);
}

TEST_CASE("constructors")
{
	SUBCASE("empty -> Resize + Fill")
	{
		BitSet first;
		CHECK(first.Size() == 0);
		first.Resize(10);
		CHECK(first.Size() == 10);
		first.Fill(true);
		for(int i = 0; i < first.Size(); ++i)
			CHECK(first[i]);
	}
	SUBCASE("construct from BitSet")
	{
		BitSet first;
		BitSet second(first);
		CHECK(second.Size() == 0);
		first.Resize(10);
		first.Fill(true);
		CHECK(second.Size() == 0);
		second.Resize(10);
		second.Fill(true);
		first[8] = false;
		second[9] = false;
		CHECK(second[8]);
		CHECK(first[9]);
	}
	SUBCASE("throws") {
		CHECK_THROWS(BitSet(-1, true));
		CHECK_THROWS(BitSet(0, true));
	}
	SUBCASE("copy") {
		int size = 37;
		BitSet bitset(size, true);
		BitSet other = bitset;
		CHECK(other == bitset);
		other[0] = false;
		CHECK(bitset[0]);
		bitset[1] = false;
		CHECK(other[1]);
	}
	SUBCASE("move") {
		int size = 37;
		BitSet bitset(size, true);
		BitSet copy = bitset;
		BitSet other = std::move(bitset);
		CHECK(other == copy);
		copy[0] = false;
		CHECK(other[0]);
		other[1] = false;
		CHECK(copy[1]);
		CHECK(bitset.Size() == 0);
	}
	SUBCASE("copy operator") {
		int size = 37;
		BitSet bitset(size, true);
		BitSet other;
		other = bitset;
		CHECK(other == bitset);
		other[0] = false;
		CHECK(bitset[0]);
		bitset[1] = false;
		CHECK(other[1]);
	}
	SUBCASE("move operator") {
		int size = 37;
		BitSet bitset(size, true);
		BitSet copy = bitset;
		BitSet other;
		other = std::move(bitset);
		CHECK(other == copy);
		CHECK(bitset.Size() == 0);
	}
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
		CHECK(!bitset[i]);

	CHECK_THROWS(bitset.Resize(0));
	CHECK_THROWS(bitset.Resize(-1));
}

TEST_CASE("operators")
{
	SUBCASE("~")
	{
		int sz = 39;
		BitSet first(sz, true);
		BitSet second = ~first;
		for (int i = 0; i < first.Size(); ++i)
			CHECK(!second[i]);
	}
	SUBCASE("& &=")
	{
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
		for (auto index : { 0, 1, 5 })
			result[index] = false;
		auto res = first & second;
		CHECK(res == result);
		first &= second;
		CHECK(first == result);
	}
	SUBCASE(" | ")
	{
		int size = 37;
		BitSet first(size, true);
		BitSet wrong_second(size + 1, true);
		CHECK_THROWS(first | wrong_second);
		CHECK_THROWS(first |= wrong_second);
		BitSet second(size, true);
		first[33] = 0;
		first[20] = 0;
		first[30] = 0;
		first[15] = 0;
		second[20] = 0;
		second[1] = 0;
		second[33] = 0;
		second[4] = 0;
		second[36] = 0;
		BitSet result(size, true);
		for (auto index : { 20, 33 })
			result[index] = false;
		auto res = first | second;
		CHECK(res == result);
		first |= second;
		CHECK(first == result);
	}
}

TEST_CASE("XOR")
{
	int size = 43;
	BitSet first(size, true);
	BitSet wrong_second(size + 1, true);
	CHECK_THROWS(first ^ wrong_second);
	CHECK_THROWS(first ^= wrong_second);
	BitSet second(size, true);
	first[20] = 0;
	first[15] = 0;
	second[20] = 0;
	second[1] = 0;
	second[4] = 0;
	second[36] = 0;
	BitSet result(size, false);
	for (auto index : {1, 4, 15, 36})
		result[index] = true;
	auto res = first ^ second;
	CHECK(res == result);
	first ^= second;
	CHECK(first == result);
}

TEST_CASE("& bool")
{
	BitSet bs(10,false);
	const BitSet& cl(bs);
	bool ch = cl[0];
	CHECK(ch == false);
}


