#include <stdio.h>
#include <Windows.h>


int main(void)
{
	char buf[256];
	HANDLE hinp;
	HANDLE hout;
	int rozm, rfakt;
	
	// w æwiczeniu zawsze bêdê wykorzystywa³ wariant pierwszy:
	// Data: 25-12-2017
	int day, month, year;

	hinp = GetStdHandle(STD_INPUT_HANDLE); 
	hout = GetStdHandle(STD_OUTPUT_HANDLE);

	// wypisanie za pomoc¹ API zapytania ===============================
	// (miniaturka ca³ego programu póŸniejszego, bez danych):
	// pobranie tekstu do bufora, Oem, a potem bufor wyprowadzany na ekran
	// - zamieniono litery polskie na OEM
	// - dopisano znaki nowej linijki, ¿eby mo¿na by³o wpisaæ tekst
	sprintf_s(buf, 256, "Napisz nastêpuj¹cy tekst:\nData: 25-12-2017\n\n");
	CharToOemA(buf, buf);
	rozm = strlen(buf); // zmienna rozm musi byæ zainicjowana przed wypisaniem
	WriteConsoleA(hout, buf, rozm, &rfakt, 0);

	// w³aœciwe zadanie: pobranie danych ==============================
	// najpierw czytam z konsoli do bufora tekst o okreœlonej konstrukcji, wyodrêbniaj¹cy zmienne
	ReadConsoleA(hinp, buf, 256, &rozm, 0); 
	buf[rozm] = '\0'; // rozmiar ustalono przez wskaŸnik

	// potem czytam z bufora do zmiennych, przedtem dowolny tekst do spacji
	// sscanf_s(buf, "Data: %d-%d-%d", &day, &month, &year); // w ten sposób trzeba wpisaæ bezb³êdnie
	sscanf_s(buf, "%*s %d-%d-%d", &day, &month, &year); // przed spacj¹ dopusczalny dowolny tekst, ale musi byæ co najmniej jeden znak i ta spacja
		
	// wypisujê uzyskane dane ===============
	// najpierw do bufora
	sprintf_s(buf, 256, "\r\nDzieñ=%d, miesi¹c=%d, rok=%d\r\n", day, month, year); // \r\n potrzebne w Windows
	rozm = strlen(buf); // lepiej obci¹æ, bo nie wiadomo co by³o przedtem
	// rozm = 250; // na przyk³ad mog³o byæ tak
	
	CharToOem(buf, buf);
	// a teraz wypisujê ten bufor
	WriteConsoleA(hout, buf, rozm, &rfakt, 0); // wyœwietla siê rozmiar 

	
	system("pause"); //zatrzymanie okna konsoli
	return 0;
}