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

	// printf_s(tt); //wyprowadzenie na ekran pokazuje tekst przed przekszta�ceniem
	printf(buf); //wyprowadzenie na ekran
	printf_s(buf); //wyprowadzenie na ekran
	// printf_s("%s", buf); //tak jest bardziej profesjonalnie, dowcip nie dzia�a

	//------------------
	
	system("pause"); //zatrzymanie okna konsoli
	return 0;
}