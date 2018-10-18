#include <stdio.h>
#include <Windows.h>


int main(void)
{
	char buf[256];

	// w �wiczeniu zawsze b�d� wykorzystywa� wariant pierwszy:
	// Data: 05-02-2017
	int day, month, year;

	// printf_s("Napisz nast�puj�cy tekst:\nData: 05-02-2017\n\n"); // to nie dzia�a bo polskie litery �le si� wy�wietlaj�
	sprintf_s(buf, 256, "Napisz nast�puj�cy tekst:\nData: 05-02-2017\n\n");
	CharToOem(buf, buf);
	printf_s(buf);

	// nie pobieram do bufora, tylko od razu z konsoli do zmiennych
	scanf_s("%*s %d-%d-%d", &day, &month, &year); // przed spacj� dopuszczalny dowolny tekst, ale musi by� co najmniej jeden znak i ta spacja

	sprintf_s(buf, 256, "Dzie�: %d, miesi�c: %d, rok: %d\n", day, month, year);
	CharToOem(buf, buf);
	printf_s(buf);
	
	system("pause"); //zatrzymanie okna konsoli
	return 0;
}