#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include<string>
#include <doctest/doctest.h>
#include <m3i/m3i.h>

TEST_CASE("constuctos")
{
    SUBCASE("x,y,z")
    {
        int shape[3] = {rand()%10, rand()%10, rand()%10};
        M3i tensor(shape[0], shape[1], shape[2]);
        for(int i = 0; i < shape[0]; ++i)
        for(int j = 0; j < shape[1]; ++j)
        for(int k = 0; k < shape[2]; ++k)
        CHECK(tensor.at(i,j,k) == 0);
    }
    SUBCASE("M3i&")
    {
        int shape[3] = {rand()%10, rand()%10, rand()%10};
        M3i tensor(shape[0], shape[1], shape[2]);
        M3i tensor_(tensor);
        for(int i = 0; i < shape[0]; ++i)
        for(int j = 0; j < shape[1]; ++j)
        for(int k = 0; k < shape[2]; ++k)
        CHECK(tensor.at(i,j,k) == tensor_.at(i,j,k));
    }
    SUBCASE("move")
    {
        int shape[3] = {rand()%10, rand()%10, rand()%10};
        M3i tensor(shape[0], shape[1], shape[2]);
        M3i tensor_ = std::move(tensor);
        for(int i = 0; i < shape[0]; ++i)
        for(int j = 0; j < shape[1]; ++j)
        for(int k = 0; k < shape[2]; ++k)
        CHECK(tensor_.at(i,j,k) == 0);
    }
    SUBCASE("init list")
    {
        std::initializer_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        M3i tensor(list);
        for(int i = 0; i < 9; ++i)
        {
            int a = *(list.begin() + i);
            CHECK(tensor.at(0,i ,0) == *(list.begin() + i));
        }
    }
}
/*
 * TEST_CASE("heavy_copy")
{
    int shape[3] = {rand() % 10 + 1, rand() % 10 + 1, rand() % 10 + 1};
    int shape_[3] = {rand() % 10 + 1, rand() % 10 + 1, rand() % 10 + 1};
    M3i tensor(shape[0], shape[1], shape[2]);
    M3i tensor_ = tensor.clone();
    tensor.resize(shape_[0], shape_[1], shape_[2]);
    bool check_ = tensor_.size(0) == shape[0] && tensor_.size(1) == shape[1] && tensor_.size(2) == shape[2];
    CHECK(check_ == true);
}
 */

TEST_CASE("wrong indexes")
{
int size_limit = 10;

SUBCASE("resize")
{
    for(int i = 0; i < size_limit; ++i)
    {
        M3i tensor(rand() % size_limit + 1, rand() % size_limit + 1, rand() % size_limit + 1);
        CHECK_THROWS_WITH_AS(tensor.resize(rand()%size_limit - size_limit,rand()%size_limit - size_limit,rand()%size_limit - size_limit ), "invalid_argument",std::invalid_argument);
    }
    }
    SUBCASE("at")
    {
        int shape[3] = {rand() % size_limit + 1, rand() % size_limit + 1, rand() % size_limit + 1};
        for(int i = 0; i < size_limit; ++i)
        {
            M3i tensor(rand() % size_limit + 1, rand() % size_limit + 1, rand() % size_limit + 1);
            CHECK_THROWS_WITH_AS(tensor.at(rand()%size_limit - size_limit,rand()%size_limit - size_limit,rand()%size_limit - size_limit ), "invalid_argument",std::invalid_argument);
        }
    }
}

TEST_CASE("light copy")
{
    int counter = 10;
    bool check_ = false;
    int shape[3] = {rand()%10 + 1, rand()%10 + 1, rand()%10 + 1};
    M3i tensor(shape[0], shape[1], shape[2]);

    std::vector<M3i> m3i_vec(counter);
    for(int i = 0; i < counter; ++i)
    {
        m3i_vec[i] = tensor;
        for(int j = 0; j < 3; ++j)
        {
            check_ = m3i_vec[i].size(j) == tensor.size(j);
            CHECK(check_ == true);
        }

    }
    int shape_[3] = {rand()%10 + counter, rand()%10 + counter, rand()%10 + counter};
    tensor.resize(shape[0], shape[1], shape[2]);
    for(int i = 0; i < counter; ++i)
        for(int j = 0; j < 3; ++j)
        {
            check_ = m3i_vec[i].size(j) == tensor.size(j);
            CHECK(check_ == true);
        }
}

TEST_CASE("resize + fill")
{
    int shape[3] = {rand()%10 + 1, rand()%10 + 1, rand()%10 + 1};
    M3i tensor(shape[0], shape[1], shape[2]);
    int val = rand()%100;
    tensor.fill(val);

    for(int i = 0; i < shape[0]; ++i)
    for(int j = 0; j < shape[1]; ++j)
    for(int k = 0; k < shape[2]; ++k)
    CHECK(tensor.at(i,j,k) == val);

    int shape_[3] = { rand() % 10 + 1, rand() %10 + 1, rand() %10 + 1};
    tensor.resize(shape_[0], shape_[1], shape_[2]);
    bool s = tensor.size(0) == shape_[0] && tensor.size(1) == shape_[1] && tensor.size(2) == shape_[2];
    CHECK(s == true);
}


