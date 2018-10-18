#include <stdio.h>
#include <Windows.h>

int main(void)
{
	HANDLE hinp = GetStdHandle(STD_INPUT_HANDLE); // deskryptor buforu wejœciowego
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //deskryptor buforu wyjœciowego
	int lenbuf, rozmfakt;
	
	char buf[256]; // bufor roboczy "do wszystkiego" (dlatego d³ugi)
	
	// przyk³adowe nazwy firm
	char przyklady[10][20] = { "Medic¹lgorithmics", "Ciêch", "Mênnica Polska", 
		"Pagêd", "Impexmeta³", "Mlekówita", "Boryœew", "Syrêna", "Wedel", "FSO" };

	// siedem nazw firm do wprowadzenia: wariant nr 1
	char firma[7][50];
	char answer;

	// wypisuje przyk³ady ========================================
	sprintf_s(buf, 256, "Przyk³adowe firmy:\r\n"); // nag³ówek przyk³adów
	lenbuf = strlen(buf);
	CharToOemA(buf, buf);
	WriteConsoleA(hout, buf, lenbuf, &rozmfakt, NULL);

	for (char i = 0; i < 10; ++i) // wypisanie przyk³adów (jest ich 10 wiêc litera³)
	{
		sprintf_s(buf, 256, "%s ", przyklady[i]);
		CharToOemA(buf, buf);
		//CharToOemA(przyklady[i], buf); // zamiast poprzednich, ale by nie by³o spacji po
		lenbuf = strlen(buf);
		WriteConsoleA(hout, buf, lenbuf, &rozmfakt, NULL);
	}
	
	// pobieranie nazw firm =====================================
	sprintf_s(buf, 256, "\n\nPodaj siedem firm:\r\n"); 
	lenbuf = strlen(buf);
	WriteConsoleA(hout, buf, lenbuf, &rozmfakt, NULL);
	
	for (char i = 0; i < 7; ++i)
	{
		// UWAGA: read z konsoli pobiera od razu tekst dobry do wypisywania,
		// nie potrzeba CharToOem
		ReadConsoleA(hinp, firma[i], 50, &lenbuf, 0); // firma przyjmuje 50
		//scanf_s("%s", buf, 256); // tak te¿ dzia³a, ale trzeba potem liczyæ d³ugoœæ
		//lenbuf = strlen(firma[i]); // ju¿ przeczytano d³ugoœæ, potrzebne przy scanf
		firma[i][lenbuf] = '\0'; // konieczne do skrócenia nazwy firmy, i tak zostaje \r\n
	}
	
	// wypisanie podanych nazw firm =====================================
	sprintf_s(buf, 256, "\r\nPodane firmy:\r\n");
	lenbuf = strlen(buf); // jeœli nie ustalê lenbuf to wypisze œmieci
	WriteConsoleA(hout, buf, lenbuf, &rozmfakt, NULL);

	for (char i = 0; i < 7; ++i)
	{
		sprintf_s(buf, 256, "%i: %s", i + 1, firma[i]);
		lenbuf = strlen(buf);
		WriteConsoleA(hout, buf, lenbuf, &rozmfakt, NULL);
	}


	// teraz prawdziwe rozwi¹zanie zadania: TABELA PORÓWNAÑ =============

	// nag³ówek tabelki: kolumny
	sprintf_s(buf, 256, "\r\n%16s\n", "1 2 3 4 5 6 7"); // 16 bo 3 odstêpu + 13 (7+7-1)
	lenbuf = strlen(buf);
	WriteConsoleA(hout, buf, lenbuf, &rozmfakt, NULL);

	for (char i = 0; i < 7; ++i)
	{
		sprintf_s(buf, 256, "%i: ", i + 1); // wypisuje numer rzêdu
		WriteConsoleA(hout, buf, 3, &rozmfakt, NULL);
		for (char j = 0; j < 7; ++j) // porównanie i wypisanie wyniku
		{
			// N: nierówne, R: równe, x dla tego samego (zawsze R)
			answer = strcmp(firma[i], firma[j]) ? 'N' : 'R';
			answer = j == i ? 'x' : answer;
			sprintf_s(buf, 256, "%-2c", answer);
			WriteConsoleA(hout, buf, 2, &rozmfakt, NULL);
		}
		WriteConsoleA(hout, "\n", 1, &rozmfakt, NULL);
	}
	WriteConsoleA(hout, "\n", 1, &rozmfakt, NULL); // odstêp koñcz¹cy
	
	system("pause");
	return 0;
}