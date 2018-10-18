#include <stdio.h>
#include <Windows.h>


void inverser_nombres(int *nombreA, int *nombreB) // dowód ¿e nie zawsze trzeba pisaæ o typach parametrów
{
	int temporaire = *nombreB;
	printf("AVANT : A = %d et B = %d\n", *nombreA, *nombreB);
	*nombreB = *nombreA;
	*nombreA = temporaire;
	printf("APRES : A = %d et B = %d\n", *nombreA, *nombreB);
}

int main(void)
{
	char buf[256];
	signed char a, b, c, d, result;
	//_Bool b;
	int nombA = 18, nombB = 28;
	inverser_nombres(&nombA, &nombB);
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
		"wynik operacji punktu (a): %d (%x)\n",
		a, a, b, b, c, c, d, d,
		result, result);
	// wariant 1 punktu b:przesuwanie w lewo 1, przesuwanie w prawo 8
	printf_s("%d: Przesuwanie w lewo o 1: %d %x\n", result, result << 1, result << 1);
	printf_s("%d: Przesuwanie w prawo o 8: %d %x\n", result, result >> 8, result >> 8);
	system("pause");
	return 0;
}