#include <stdio.h>
#include <Windows.h>

int main(void)
{
	char buf[256];
	signed char a, b, c, d, result;
	//_Bool b;
	//a = -3;
	//printf_s("Wynik = %d (%x)\r\n", a, a);

	sprintf_s(buf, 256, "Proszê podaæ cztery liczby, w tym ujemne, oddzielaj¹c je spacjami: ");
	CharToOem(buf, buf);
	printf_s(buf);
	//a = -12;
	//printf_s("\n%d %d", a, ~a);

	scanf_s("%hhd %hhd %hhd %hhd", &a, &b, &c, &d); 

	// wariant pierwszy
	result = (a | b) & c^d;
	
	printf_s("Wprowadzono liczby:\n"
		"%d (%x)\n"
	    "%d (%x)\n"
		"%d (%x)\n"
		"%d (%x)\n"
		"wynik: %d (%x)\n",
		a, a, b, b, c, c, d, d,
		result, result);


	system("pause");
	return 0;
}