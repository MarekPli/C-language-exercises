#include <stdio.h>
#include <Windows.h>


int main(void)
{
	char buf[256];
	HANDLE hinp;
	HANDLE hout;
	int rozm, rfakt;
	
	// w �wiczeniu zawsze b�d� wykorzystywa� wariant pierwszy:
	// Data: 25-12-2017
	int day, month, year;

	hinp = GetStdHandle(STD_INPUT_HANDLE); 
	hout = GetStdHandle(STD_OUTPUT_HANDLE);

	// wypisanie za pomoc� API zapytania ===============================
	// (miniaturka ca�ego programu p�niejszego, bez danych):
	// pobranie tekstu do bufora, Oem, a potem bufor wyprowadzany na ekran
	// - zamieniono litery polskie na OEM
	// - dopisano znaki nowej linijki, �eby mo�na by�o wpisa� tekst
	sprintf_s(buf, 256, "Napisz nast�puj�cy tekst:\nData: 25-12-2017\n\n");
	CharToOemA(buf, buf);
	rozm = strlen(buf); // zmienna rozm musi by� zainicjowana przed wypisaniem
	WriteConsoleA(hout, buf, rozm, &rfakt, 0);

	// w�a�ciwe zadanie: pobranie danych ==============================
	// najpierw czytam z konsoli do bufora tekst o okre�lonej konstrukcji, wyodr�bniaj�cy zmienne
	ReadConsoleA(hinp, buf, 256, &rozm, 0); 
	buf[rozm] = '\0'; // rozmiar ustalono przez wska�nik

	// potem czytam z bufora do zmiennych, przedtem dowolny tekst do spacji
	// sscanf_s(buf, "Data: %d-%d-%d", &day, &month, &year); // w ten spos�b trzeba wpisa� bezb��dnie
	sscanf_s(buf, "%*s %d-%d-%d", &day, &month, &year); // przed spacj� dopusczalny dowolny tekst, ale musi by� co najmniej jeden znak i ta spacja
		
	// wypisuj� uzyskane dane ===============
	// najpierw do bufora
	sprintf_s(buf, 256, "\r\nDzie�=%d, miesi�c=%d, rok=%d\r\n", day, month, year); // \r\n potrzebne w Windows
	rozm = strlen(buf); // lepiej obci��, bo nie wiadomo co by�o przedtem
	// rozm = 250; // na przyk�ad mog�o by� tak
	
	CharToOem(buf, buf);
	// a teraz wypisuj� ten bufor
	WriteConsoleA(hout, buf, rozm, &rfakt, 0); // wy�wietla si� rozmiar 

	
	system("pause"); //zatrzymanie okna konsoli
	return 0;
}