#include<iostream>
#include<vector>
#include<string>
#include<limits>
#include<cmath>
int main(void)
{
    int n, m, summ = 0;
    std::cin >> n >> m;
    std::vector < std::vector <int> > mass(n, std::vector <int>(m));
    std::string::size_type sz = 0;
    std::string str;
    std::cin.get();
    for (int i = 0; i < n; ++i)
    {
        std::getline(std::cin, str);
        int index = 0;
        while (sz <= str.length())
        {
            int x = std::stoi(str, &sz);
            mass[i][index] = x;
            str = str.substr(sz);
            index++;
        }
    }
    if (mass[n - 1][m - 1] == 0 || mass[n-1][m-1] <= mass[n-1][m-2] || mass[n-1][m-1] <= mass[n-2][m-1])
    {
        std::cout << -1;
        return 0;
    }
    //border problems _____
    for (int j = m - 1; j >= 0; --j)
        mass[n - 1][j] = (mass[n - 1][j] == 0) ? mass[n - 1][j + 1] : mass[n - 1][j];
    //border problems |
    for (int i = n - 1; i >= 0; --i)
        mass[i][m - 1] = (mass[i][m - 1] == 0) ? mass[i + 1][m - 1] : mass[i][m - 1];
    for(int i = n -2; i>=0; --i)
        for (int j = m - 2; j >= 0; --j)
        {
            if (mass[i][j] == 0)
                mass[i][j] = (mass[i + 1][j] > mass[i][j + 1]) ? (mass[i][j + 1] - 1) : mass[i + 1][j] - 1;
            else
                if (mass[i][j] >= mass[i + 1][j] || mass[i][j] >= mass[i][j + 1])
                {
                    std::cout << -1;
                    return 0;
                }
        }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            summ += mass[i][j];
    std::cout << summ;
    return 0;
}