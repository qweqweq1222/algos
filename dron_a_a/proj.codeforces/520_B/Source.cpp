#include <iostream>
#include <cmath>
int main(void)
{
    int n,m = 0;
    std::cin >> n >> m;
    if(n>m)
        std::cout << n-m << std::endl;
    else
    {
        /*memory*/
        int memory = 1;
        int counter = m;
        while(n <= counter && counter > 1)
        {
            ++memory;
            counter = (counter % 2 == 0) ? (counter / 2) : (counter / 2 + 1);
        }
        int *mass = new int(memory);
        counter = m;
        mass[0] = m;
        for (int i =1; i< memory; ++i) {
            mass[i] = (counter % 2 == 0) ? (counter / 2) : (counter / 2 + 1);
            counter = mass[i];
        }
        counter = 0;
        int place = (n == mass[memory-2] && memory > 2) ? (memory - 2) : (memory - 1);
        if(n != mass[memory-2])
            counter = n - mass[memory-1];
        for (int i = place; i > 0; --i)
        {
            counter = (mass[i] * 2 != mass[i - 1]) ? (counter + 2) : ++counter;
        }
        std::cout << counter;
    }
}
