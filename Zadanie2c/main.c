#include <stdio.h>
#include <Windows.h>


int main(void)
{
	char buf[256];

	// w æwiczeniu zawsze bêdê wykorzystywa³ wariant pierwszy:
	// Data: 05-02-2017
	int day, month, year;

	// printf_s("Napisz nastêpuj¹cy tekst:\nData: 05-02-2017\n\n"); // to nie dzia³a bo polskie litery Ÿle siê wyœwietlaj¹
	sprintf_s(buf, 256, "Napisz nastêpuj¹cy tekst:\nData: 05-02-2017\n\n");
	CharToOem(buf, buf);
	printf_s(buf);

	// nie pobieram do bufora, tylko od razu z konsoli do zmiennych
	scanf_s("%*s %d-%d-%d", &day, &month, &year); // przed spacj¹ dopuszczalny dowolny tekst, ale musi byæ co najmniej jeden znak i ta spacja

	sprintf_s(buf, 256, "Dzieñ: %d, miesi¹c: %d, rok: %d\n", day, month, year);
	CharToOem(buf, buf);
	printf_s(buf);
	
	system("pause"); //zatrzymanie okna konsoli
	return 0;
}