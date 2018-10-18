#include <stdio.h>
#include <math.h>
#include <Windows.h>
int main(void)
{
	char buf[256];

	// wariant 1: 4 liczby ca³kowite char, oblicza siê sin
	char x1, x2, x3, x4;
	double mean;
	double sinus;

	// Zaproszenie
	sprintf_s(buf, 256, "WprowadŸ cztery liczby ca³kowite, oddzielaj¹c je spacjami");
	CharToOem(buf, buf);
	printf_s("%s\n", buf);

	// pobranie danych
	// u¿ycie %d generuje b³¹d, %hhd jest konieczne
	scanf_s("%hhd %hhd %hhd %hhd", &x1, &x2, &x3, &x4);

	// wyœwietlenie pobranych danych
	printf_s("Podano: %d %d %d %d\n", x1, x2, x3, x4);

	// obliczenie i wyœwietlenie œredniej
	mean = (x1 + x2 + x3 + x4) / 4;
	sprintf_s(buf, 256, "œrednia: %.2lf", mean);
	CharToOem(buf, buf);
	printf_s("%s\n", buf);

	// obliczenie i wyœwietlenie sinusa
	sinus = sin(mean);
	printf_s("Wynik funkcji sinus: %.2lf\n", sinus);

	system("pause");
}