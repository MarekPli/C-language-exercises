#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <conio.h>

_int64 silnia(_int64 n)
{
	if (n <= 1)
		return 1;
	else
		n = n * silnia(n - 1);
	return n;
}


int main(void)
{
	_int64 nr, result; 
	char buf[256] = "Podaj liczbê do obliczenia silni: ";
	CharToOem(buf, buf);
	printf_s(buf);
	scanf_s("%I64d", &nr);
	for (nr = 0; nr < 24; ++nr) {
		result = silnia(nr);
		printf_s("%I64d: silnia to %I64d\n", nr, result);
	}
	system("pause");
	return 0;
}
