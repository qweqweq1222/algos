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

TEST_CASE("resize + fill")
{
    int shape[3] = {rand()%10, rand()%10, rand()%10};
    M3i tensor(shape[0], shape[1], shape[2]);
    int val = rand()%100;
    tensor.fill(val);

    for(int i = 0; i < shape[0]; ++i)
        for(int j = 0; j < shape[1]; ++j)
            for(int k = 0; k < shape[2]; ++k)
                CHECK(tensor.at(i,j,k) == val);

    int shape_[3] = { rand() % 10, rand() %10, rand() %10};
    tensor.resize(shape_[0], shape_[1], shape_[2]);
    bool s = tensor.size(0) == shape_[0] && tensor.size(1) == shape_[1] && tensor.size(2) == shape_[2];
    CHECK(s == true);
}


