#include <stdio.h>
#include <Windows.h> // bez tego nie ma CharToOem, ale system dzia³a


int main(void)
{
	// wpisa³em swoje imiê i nazwisko ze wszystkimi polskimi literami
	//char tt[] = "Program w C. Autor Marek ¥æê³ñóœ¿Ÿ \r\n\r\n";
	
	// albo zróbmy sobie dowcip
	char tt[] = "Program w C. Autor % Marek ¥æê³ñóœ¿Ÿ \r\n\r\n";
	char buf[128];
	
	system("COLOR 30"); // ¿eby by³o ciekawiej...

	//------------------
	CharToOemA(tt, buf); //zamiana kodowania
						 //lub AnsiToOem(tt,buf); //zamiana kodowania
	
						
	// AnsiToOem(tt, buf); // u mnie to te¿ dzia³a
	printf("polskie czcionki bez CharToOemA: %s\n\n", "¹æê³ñóœ¿Ÿ");
	//printf_s(tt); //tekst przed przekszta³ceniem - a tak naprawdê nie bêdzie to dzia³a³o!!!
	printf("dla printf: %s", buf); //dzia³a "niebezpiecznie", znak % jest pomijany
	printf("a teraz tylko lancuch formatujacy: "); // tu nie dawaæ polskich czcionek, bo bêdzie jak na pocz¹tku
	printf(buf); // zadzia³a jak wy¿ej
	// printf_s(buf); //wyprowadzenie na ekran - nie bêdzie dzia³a³o
	printf_s("dla printf_s: %s", buf); //tak jest bardziej profesjonalnie, dowcip nie dzia³a, samotne % jest traktowane jako zwyk³y znak
	// a tutaj sam ³añcuch formatuj¹cy
	printf("abc %% dla printf\n"); //dzia³a dobrze
	//printf("abc % ccc\n"); // dzia³a Ÿle, nie kompiluje siê
	//printf("abc \% ccc\n"); // dzia³a Ÿle, nie kompiluje siê
	printf_s("abc %% dla printf_s\n");
	//printf_s("abc % ccc\n"); // nie zadzia³a
	//printf_s("abc \% ccc\n"); // nie zadzia³a






	//------------------
	
	system("pause"); //zatrzymanie okna konsoli
	return 0;
}