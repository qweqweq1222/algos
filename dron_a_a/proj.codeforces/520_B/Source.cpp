#include<iostream>
#include<cmath>
void main(void)
{
	int n, m, current = 0;
	std::cin >> n >> m;
	if (m > n)
	{
		current = m;
		int size = 0;
		while (current >= n && current > 1)
		{
			current = current / 2;
			++size;
		}
		size = size + 1;
		int* mas = new int[size];
		mas[0] = m;
		//std::cout << mas[0] << ' ';
		current = m;
		for (int i = 1; i < size; ++i)
		{
			current = (current % 2 == 0) ? current / 2 : ((current / 2) + 1);
			mas[i] = current;
			//std::cout << mas[i] << ' ';
		}
		int buffer = 0;
		int mesh = (mas[size - 1] < n) ? size - 2 : size - 1;
		int counter = abs(n - mas[mesh]);
		buffer = mas[mesh];
		for (int i = mesh; i > 0; --i)
		{
			counter = (mas[i] * 2 != mas[i - 1]) ? (counter + 2) : ++counter;
		}
		std::cout << counter;
	}
	else
		std::cout << abs(m - n);
}