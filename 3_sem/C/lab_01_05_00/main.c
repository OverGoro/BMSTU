#include <stdio.h>
#define OK 0
#define IO_ERROR 1
#define RANGE_ERROR 2

int power(int a, int n)
{
	int p = 1;
	while (n != 0)
	{
		if (n % 2 == 1)
		{
			p *= a;
			n--;
		}
		else
		{
			a *= a;
			n /= 2;
		}
	}
	return p;
}
int main(void)
{
	int a, n;
	printf("A, N: ");
	if (scanf("%d", &a) != 1)
	{
		return IO_ERROR;
	}
	if (scanf("%d", &n) != 1)
	{
		return IO_ERROR;
	}
	if (n < 1)
	{
		return RANGE_ERROR;
	}
	printf("%d\n", power(a, n));
	return OK;
}
