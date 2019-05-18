// https://www.hackerrank.com/challenges/plus-minus/problem

#include <stdio.h>

int main()
{
	int n;
	double pos = 0, neg = 0, zer = 0;
	scanf("%d", &n);
	double A[n];

	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &A[i]);
		
		if (A[i] > 0)
			pos++;
		else if (A[i] < 0)
			neg++;
		else
			zer++;	
	}

	printf("%lf\n%lf\n%lf\n", pos/n, neg/n, zer/n);

	return 0;
}
