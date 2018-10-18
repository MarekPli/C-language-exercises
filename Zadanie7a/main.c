#include <stdio.h>
#include <math.h>
#include <Windows.h>

// funkcja zwracaj�ca wynik przez return
double function_average(int x, int y, int z, int n) 
{
	return (x + y + z + n) / 4;
}

// funkcja zwracaj�ca wynik przez argument
void function_sinus(double average, double* pSinus)
{
	*pSinus = sin(average);
	return;
}

// funkcja zwracaj�ca wynik przez argument

int main(void)
{
	char buf[256];

	// wariant 1: 4 liczby ca�kowite char, oblicza si� sin
	char x1, x2, x3, x4;
	double mean;
	double sinus;

	// Zaproszenie
	sprintf_s(buf, 256, "Wprowad� cztery liczby ca�kowite, oddzielaj�c je spacjami");
	CharToOem(buf, buf);
	printf_s("%s\n", buf);

	// pobranie danych
	// u�ycie %d generuje b��d, %hhd jest konieczne
	scanf_s("%hhd %hhd %hhd %hhd", &x1, &x2, &x3, &x4);

	// wy�wietlenie pobranych danych
	printf_s("Podano: %d %d %d %d\n", x1, x2, x3, x4);

	// obliczenie i wy�wietlenie �redniej
	mean = function_average(x1, x2, x3, x4);
	sprintf_s(buf, 256, "�rednia: %.2lf", mean);
	CharToOem(buf, buf);
	printf_s("%s\n", buf);

	// obliczenie i wy�wietlenie sinusa
	//sinus = sin(mean);
	function_sinus(mean, &sinus);
	printf_s("Wynik funkcji sinus: %.2lf\n", sinus);

	system("pause");
}