#include <stdio.h>
#include <Windows.h>

int main(void)
{
	char a, b, c, d, result;
	printf_s("a b c d  funkcja\n");
	for (a = 0; a <= 1; ++a)
	{
		for (b = 0; b <= 1; ++b)
		{
			for (c = 0; c <= 1; ++c)
			{
				for (d = 0; d <= 1; ++d)
				{
					// zminimalizowana funkcja: przyk³ad 1 z 4b
					result = (b == 0 && c == 0) ||
						(a == 0 && b != 0 && c != 0) ||
						(a != 0 && b == 0);

					printf_s("%d %d %d %d  %d\n", 
						a, b, c, d, result);
				}
			}
		}
	}

	// drugi wariant
	printf_s("a b c d  funkcja (drugi wariant: 02)\n");
	for (char i = 0; i < 16; ++i) 
	{
		a = (8 & i) ? 1 : 0;
		b = (4 & i) ? 1 : 0;
		c = (2 & i) ? 1 : 0;
		d = (1 & i) ? 1 : 0;
		result = (!b && c) || (a && !c);

		printf_s("%d %d %d %d  %d\n",
			a, b, c, d, result);
	}
		
	system("pause");
	return 0;
}
