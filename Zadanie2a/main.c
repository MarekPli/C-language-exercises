#include <stdio.h>
#include <Windows.h> // bez tego nie ma CharToOem, ale system dzia�a


int main(void)
{
	// wpisa�em swoje imi� i nazwisko ze wszystkimi polskimi literami
	//char tt[] = "Program w C. Autor Marek ����󜿟 \r\n\r\n";
	
	// albo zr�bmy sobie dowcip
	char tt[] = "Program w C. Autor % Marek ����󜿟 \r\n\r\n";
	char buf[128];
	
	system("COLOR 30"); // �eby by�o ciekawiej...

	//------------------
	CharToOemA(tt, buf); //zamiana kodowania
						 //lub AnsiToOem(tt,buf); //zamiana kodowania
	
						
	// AnsiToOem(tt, buf); // u mnie to te� dzia�a
	printf("polskie czcionki bez CharToOemA: %s\n\n", "����󜿟");
	//printf_s(tt); //tekst przed przekszta�ceniem - a tak naprawd� nie b�dzie to dzia�a�o!!!
	printf("dla printf: %s", buf); //dzia�a "niebezpiecznie", znak % jest pomijany
	printf("a teraz tylko lancuch formatujacy: "); // tu nie dawa� polskich czcionek, bo b�dzie jak na pocz�tku
	printf(buf); // zadzia�a jak wy�ej
	// printf_s(buf); //wyprowadzenie na ekran - nie b�dzie dzia�a�o
	printf_s("dla printf_s: %s", buf); //tak jest bardziej profesjonalnie, dowcip nie dzia�a, samotne % jest traktowane jako zwyk�y znak
	// a tutaj sam �a�cuch formatuj�cy
	printf("abc %% dla printf\n"); //dzia�a dobrze
	//printf("abc % ccc\n"); // dzia�a �le, nie kompiluje si�
	//printf("abc \% ccc\n"); // dzia�a �le, nie kompiluje si�
	printf_s("abc %% dla printf_s\n");
	//printf_s("abc % ccc\n"); // nie zadzia�a
	//printf_s("abc \% ccc\n"); // nie zadzia�a






	//------------------
	
	system("pause"); //zatrzymanie okna konsoli
	return 0;
}