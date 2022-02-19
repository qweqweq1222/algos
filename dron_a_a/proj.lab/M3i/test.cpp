//
// Created by anreydron on 18.02.2022.
//
#include "M3i.h"
int main(void)
{
    M3i tensor = M3i(5,4,2);
    M3i tensor_ = std::move(tensor);
    std::vector <std::vector <std::vector <int>>> s(5, std::vector< std::vector<int> >(5, std::vector <int>(3, 0)));
    int a = tensor_.get_depth();
    std::cout << tensor.get_rows();
    return 0;
}