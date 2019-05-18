// https://www.hackerrank.com/challenges/time-conversion/problem

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* time = (char *) malloc (10240 * sizeof(char));
	scanf("%s", time);

	if (time[0] == '1' && time[1] == '2')
		{
			time[0] = '0';
			time[1] = '0';
		}

	if (time[8] == 'P')
	{
		int x = 10*(time[0] - '0') + (time[1] - '0');
		x += 12;
		
		time[0] = (x / 10) + '0';
		time[1] = (x % 10) + '0';
	}
	
	time[8] = '\0';
	
	printf("%s\n", time);

	return 0;
}
