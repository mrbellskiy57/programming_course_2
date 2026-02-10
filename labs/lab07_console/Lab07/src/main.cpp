#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

int main()
{
	double x = 0.0;
    double end = 4.0;
	double step = end / 10.0; // шаг 4/10 = 0.4
	for (int i = 0; i < 10; i = i + 1)
	{
		x = x + step;
		double y = sin(x) / x;
		cout  << y << " ";
	}

	return 0;
}

//int main()
//{
//	double max_value = 100.0;
//	double f0 = 0.0;
//	double f1 = 1.0;
//	double sum = 1.0;
//	int n = 2;
//
//	while (sum < max_value)
//	{
//		double next = f0 + f1;
//		sum = sum + next;
//		n = n + 1;
//		f0 = f1;
//		f1 = next;
//	}
//
//	cout << n << " " << sum;
//	return  0;
//}


	
