#include <stdio.h>
#include <Windows.h>

int main(void)
{
	char buf[256];
	char a, b, c, d, result;
	char tab[4];
	label:
	sprintf_s(buf, 256, "Proszê podaæ cztery liczby 0 lub 1 w ci¹gu xxxx, np. 0101: ");
	CharToOem(buf, buf);
	printf_s(buf);
	//scanf_s("%s", tab, 5); // prawid³owo
	//scanf_s("%c", tab, 5); // prawid³owo
	// scanf_s("%4c", tab, 5); // nieprawid³owo, za drugim wywo³aniem \nxxx
	scanf_s("%5c", tab, 5); // prawid³owo, tak¿e dla tab[4] i tab[5]

	a = tab[0] == '0' ? 0 : 1;
	b = tab[1] == '0' ? 0 : 1;
	c = tab[2] == '0' ? 0 : 1;
	d = tab[3] == '0' ? 0 : 1;
	printf_s("Podano: %d %d %d %d", a, b, c, d);

	// minimalizacja funkcji Kanrnaugha w wariancie 1

	result = (!b && !c) ||
		(!a && b && c) ||
		(a && !b);
	// inny, d³u¿szy zapis:
	result = (b==0 && c==0) ||
		(a==0 && b!=0 && c!=0) ||
		(a!=0 && b==0);


	printf_s(" Wynik funkcji: %d\n", result);
	goto label;
	system("pause");
}
