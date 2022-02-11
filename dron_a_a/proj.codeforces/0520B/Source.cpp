/*
 Вася нашел странное устройство. На передней панели устройства расположен дисплей, отображающий некоторое
 целое положительное число, а также красная и синяя кнопки. При нажатии на красную кнопку число на дисплее
 увеличивается в два раза. При нажатии на синюю кнопку число на дисплее уменьшается на единицу. Если в какой-то
 момент число перестает быть положительным, устройство ломается. Дисплей может отображать сколь угодно большие
 числа. Изначально на дисплее отображается число n.
 Вася хочет получить на дисплее число m. Какое минимальное количество нажатий ему придется совершить?
 */

#include <iostream>
#include <vector>
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
        int rubish = 0;
        while(n <= counter && counter > 1)
        {
            ++memory;
            counter = (counter % 2 == 0) ? (counter / 2) : (counter / 2 + 1);
        }
        std::vector<int> mass;
        counter = m;
        mass.push_back(m);
        for (int i =1; i< memory; ++i) {
            rubish = (counter % 2 == 0) ? (counter / 2) : (counter / 2 + 1);
            mass.push_back(rubish);
            counter = rubish;
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
