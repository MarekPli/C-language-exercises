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

	// printf_s(tt); //wyprowadzenie na ekran pokazuje tekst przed przekszta³ceniem
	printf(buf); //wyprowadzenie na ekran
	printf_s(buf); //wyprowadzenie na ekran
	// printf_s("%s", buf); //tak jest bardziej profesjonalnie, dowcip nie dzia³a

	//------------------
	
	system("pause"); //zatrzymanie okna konsoli
	return 0;
}