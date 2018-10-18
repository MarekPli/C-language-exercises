#include <stdio.h>
#include <math.h>
#include <Windows.h>

int main(void)
{
	char buf[256];
	HANDLE hinp;
	HANDLE hout;
	int rozm, rfakt;
	double number, result;

	// w æwiczeniu zawsze bêdê wykorzystywa³ wariant pierwszy:
	// 1, 5 * log10(x)

	hinp = GetStdHandle(STD_INPUT_HANDLE);
	hout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Zaproszenie
	sprintf_s(buf, 256, "Podaj liczbê typu double\n");
	CharToOem(buf, buf);
	rozm = strlen(buf);
	WriteConsoleA(hout, buf, rozm, &rfakt, 0);

	// pobranie liczby typu double (pobranej najpierw z konsoli do bufora)
	ReadConsoleA(hinp, buf, 256, &rozm, 0);
	//buf[rozm] = '\0'; 
	sscanf_s(buf, "%lf", &number);

	// wypisanie pobranej liczby (wpisanej najpierw do bufora) oraz wyniku
	result = 1.5 * log10(number);
	sprintf_s(buf, 256, "Podano liczbê: %lf\nWynik funkcji 1,5 * log10(%lf): %lf\n", 
		number, number, result);
	CharToOem(buf, buf);
	rozm = strlen(buf);
	WriteConsoleA(hout, buf, rozm, &rfakt, 0);

	system("pause");

}