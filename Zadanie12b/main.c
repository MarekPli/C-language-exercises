#include <stdio.h>
#include <Windows.h>

int main(void)
{
	char buf[4];
	// pierwszy rz¹dek
	printf_s("%2s|", "");
	for (char i = 0; i < 16; i++) {
		printf_s(" *%X", i);
	}
	printf_s("\n");

	// drugi rz¹dek
	printf_s("%s\n",
		"--+------------------------------------------------");
	// g³ówne zadanie
	for (char i = 2; i <= 0xf; i++) {
		printf_s("%X*|", i);
		for (char j = 0; j < 16; j++)
		{
			//printf_s("%3c", i * 16 + j);
			sprintf_s(buf,4, "%3c", i * 16 + j); // konieczna jest tablica 4-elementowa
			// parametry: pSrc, pDest
			//CharToOemA(buf, buf);
			//CharToOem(buf, buf);
			//AnsiToOem(buf, buf);
			// powy¿sze nie dzia³aj¹ dobrze: "drukuj¹" cofniêcie
			CharToOemW((LPCWSTR)buf, buf);
			
			printf_s("%3s", buf);

		}
		printf_s("\n");
	}
	// dane CharToOemA wskazuj¹ na kodowanie Windows-1250: ¹ to B9 itd.
	// dane CharToOemW wskazuj¹ na inne kodowanie: ¹ to A5 itd.
	system("pause");
}