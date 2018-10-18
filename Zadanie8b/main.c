#include <stdio.h>
#include <Windows.h>

void recursiveReverse(char* buf)
{
	int len = strlen(buf);
	if (len == 0)
	{
		return;
	}
	recursiveReverse( buf+1 ); // litera nastêpna
	//printf_s("%c", *(buf)); // pierwsza litera
	putchar(*(buf));
	// kolejnoœæ operacji decyduje o porz¹dku wypisywania liter

}

int main(void)
{
	HANDLE hinp = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[256];
	int lenBuf, realWidth;

	sprintf_s(buf, 256, "Podaj swoje imiê i nazwisko: ");
	CharToOemA(buf, buf);
	lenBuf = strlen(buf);
	WriteConsoleA(hout, buf, lenBuf, &realWidth,NULL);

	ReadConsoleA(hinp, buf, 256, &lenBuf, NULL);
	buf[lenBuf] = '\0';

	WriteConsoleA(hout, buf, lenBuf, &realWidth, NULL);

	recursiveReverse(buf);
	putchar('\n');



	system("pause");
	return 0;
}