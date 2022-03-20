#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include<string>
#include <doctest/doctest.h>
#include <m3i/m3i.h>

TEST_CASE("constuctos") {

	SUBCASE("x,y,z") {
		int shape[3] = {rand()%10, rand()%10, rand()%10};
		M3i tensor(shape[0], shape[1], shape[2]);
		for (int i = 0; i < shape[0]; ++i)
			for (int j = 0; j < shape[1]; ++j)
				for (int k = 0; k < shape[2]; ++k)
					CHECK(tensor.At(i, j, k) == 0);
	}

	SUBCASE("M3i&") {
		int shape[3] = {rand()%10, rand()%10, rand()%10};
		M3i tensor(shape[0], shape[1], shape[2]);
		M3i tensor_(tensor);
		for (int i = 0; i < shape[0]; ++i)
			for (int j = 0; j < shape[1]; ++j)
				for (int k = 0; k < shape[2]; ++k)
					CHECK(tensor.At(i, j, k) == tensor_.At(i,j,k));
	}
	SUBCASE("move") {
		int shape[3] = {rand()%10, rand()%10, rand()%10};
		M3i tensor(shape[0], shape[1], shape[2]);
		M3i tensor_ = std::move(tensor);
		for (int i = 0; i < shape[0]; ++i)
			for (int j = 0; j < shape[1]; ++j)
				for (int k = 0; k < shape[2]; ++k)
					CHECK(tensor_.At(i, j, k) == 0);
	}

}

TEST_CASE("heavy_copy")
{
	int shape[3] = {rand() % 10 + 1, rand() % 10 + 1, rand() % 10 + 1};
	int shape_[3] = {rand() % 10 + 1, rand() % 10 + 1, rand() % 10 + 1};
	M3i tensor(shape[0], shape[1], shape[2]);
	M3i tensor_ = tensor.Clone();
	tensor.Resize(shape_[0], shape_[1], shape_[2]);
	bool check_ = tensor_.Size(0) == shape[0] && tensor_.Size(1) == shape[1] && tensor_.Size(2) == shape[2];
	CHECK(check_ == true);
}

TEST_CASE("wrong indexes") {
	int Size_limit = 10;

	SUBCASE("ReSize") {
		for (int i = 0; i < Size_limit; ++i) {
			M3i tensor(rand() % Size_limit + 1, rand() % Size_limit + 1, rand() % Size_limit + 1);
			CHECK_THROWS_WITH_AS(tensor.Resize(rand()%Size_limit - Size_limit,rand()%Size_limit - Size_limit,rand()%Size_limit - Size_limit), "invalid_argument", std::invalid_argument);
			}
	}
	SUBCASE("At") {
		int shape[3] = {rand() % Size_limit + 1, rand() % Size_limit + 1, rand() % Size_limit + 1};
		for (int i = 0; i < Size_limit; ++i) {
			M3i tensor(rand() % Size_limit + 1, rand() % Size_limit + 1, rand() % Size_limit + 1);
			CHECK_THROWS_WITH_AS(tensor.At(rand()%Size_limit - Size_limit,rand()%Size_limit - Size_limit,rand()%Size_limit - Size_limit), "invalid_argument", std::invalid_argument);
		}
	}
}

TEST_CASE("light copy") {
	int counter = 10;
	bool check_ = false;
	int shape[3] = {rand()%10 + 1, rand()%10 + 1, rand()%10 + 1};
	M3i tensor(shape[0], shape[1], shape[2]);

	std::vector<M3i> m3i_vec(counter);
	for (int i = 0; i < counter; ++i) {
		m3i_vec[i] = tensor;
		for (int j = 0; j < 3; ++j) {
			check_ = m3i_vec[i].Size(j) == tensor.Size(j);
			CHECK(check_ == true);
		}
	}

	int shape_[3] = {rand()%10 + counter, rand()%10 + counter, rand()%10 + counter};
	tensor.Resize(shape[0], shape[1], shape[2]);

	for (int i = 0; i < counter; ++i)
		for (int j = 0; j < 3; ++j) {
			check_ = m3i_vec[i].Size(j) == tensor.Size(j);
			CHECK(check_ == true);
		}
}

TEST_CASE("ReSize + Fill") {
	int shape[3] = {rand()%10 + 1, rand()%10 + 1, rand()%10 + 1};
	M3i tensor(shape[0], shape[1], shape[2]);
	int val = rand()%100;
	tensor.Fill(val);

	for (int i = 0; i < shape[0]; ++i)
		for (int j = 0; j < shape[1]; ++j)
			for (int k = 0; k < shape[2]; ++k)
				CHECK(tensor.At(i, j, k) == val);

	int shape_[3] = { rand() % 10 + 1, rand() %10 + 1, rand() %10 + 1};
	tensor.Resize(shape_[0], shape_[1], shape_[2]);
	bool s = tensor.Size(0) == shape_[0] && tensor.Size(1) == shape_[1] && tensor.Size(2) == shape_[2];
	CHECK(s == true);
}

TEST_CASE(">>") {
	int shape[3] = {rand()%10 + 1, rand()%10 + 1, rand()%10 + 1};
	std::stringstream  str;
	M3i tensor(shape[0], shape[1], shape[2]);
	M3i tensor_(shape[0], shape[1], shape[2]);
	for (int i = 0; i < shape[0]; ++i)
		for (int j = 0; j < shape[1]; ++j)
			for (int k = 0; k < shape[2]; ++k) {
				tensor.At(i, j, k) = i + j + k;
				str << i + j + k << std::endl;
				}

	str >> tensor_;

	for (int i = 0; i < shape[0]; ++i)
		for (int j = 0; j < shape[1]; ++j)
			for (int k = 0; k < shape[2]; ++k)
				CHECK(tensor_.At(i, j, k) == tensor.At(i, j, k));
}

