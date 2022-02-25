//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "doctest.h"
#include "M3i.h"

int main(void)
{
    M3i tensor = M3i(2,2,1);
    std::cin >> tensor;
    std::cout << tensor;
    tensor.resize(2,1,3);
    std::cout << tensor;
    std::cout << tensor.at(0,0,1) << std::endl;
    M3i tensor_{1,2,3,45};
    std::cout << tensor_;
}
