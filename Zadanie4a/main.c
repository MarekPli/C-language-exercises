#include <stdio.h>
#include <Windows.h>

int main(void)
{
	char buf[256];
	char tab[4];
	char a, b, c, d, result;

	sprintf_s(buf, 256, "Proszê podaæ cztery liczby 0 lub 1 w ci¹gu xxxx, np. 0101: ");
	CharToOem(buf, buf);
	printf_s(buf);
	//scanf_s("%s", tab, 5); // potrzebna d³ugoœæ, tablica musi byæ d³u¿sza
	scanf_s("%4c", tab, 4); // tutaj tablica mo¿e byæ w pe³ni wype³niona
	a = tab[0] == '0' ? 0 : 1;
	b = tab[1] == '0' ? 0 : 1;
	c = tab[2] == '0' ? 0 : 1;
	d = tab[3] == '0' ? 0 : 1;
	printf_s("Podano: %d %d %d %d\n", a, b, c, d);

	// liczê funkcjê z przyk³adu 1
	// ((a != 0) || (b != 0)) && (c != 0) # (d!=0)
	// # jest to XOR
	
	result = (a || b) && 
		( (c && !d) || (!c && d) ); // albo c != d
	printf_s("Wynik funkcji: %d\n", result);
	system("pause");
}
