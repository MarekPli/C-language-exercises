#include<stdio.h>
#include <conio.h>
#include<Windows.h>
int main(void)
{
	//FreeConsole();
	AllocConsole();
	char buf[256];

	SetConsoleTitleA("Aleksander");

	HANDLE hinp = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD field = GetLargestConsoleWindowSize(hout);
	COORD myPole = { 0, 0 };

	int rfakt;
	unsigned short kolor = 0xff;
	long sizePole = field.X * field.Y;
	//field.X = field.Y = 0;
	

	//field jest strukturπ, natomiast sizePole wynikiem mnoøenia
	// dlatego moøna uøyÊ wartoúci bez zmiany i wtedy malujemy poza skalπ

	FillConsoleOutputAttribute(hout, kolor, (field.X * field.Y), myPole, &rfakt);
	
	SetConsoleTextAttribute(hout, 0xf5);
	
	sprintf_s(buf, 256, "Rozmiar konsoli: %d %d\n", field.X, field.Y);
	WriteConsoleA(hout, buf, strlen(buf), &rfakt, NULL);
	sprintf_s(buf, 256, "Kolory sπ ustawione przez: %s %s\n", 
		"•∆ £—”åØè", "πÊÍ≥ÒÛúøü");
	CharToOem(buf, buf);
	WriteConsoleA(hout, buf, strlen(buf), &rfakt, NULL);

	for (signed short i = 0; i < 16 * 16; i++) //uwaga: char ujemne powoduje katastrofÍ
	{
		//for (char j = 0; j < 16 * 16; j++)
		//{
			SetConsoleTextAttribute(hout, i);
			WriteConsoleA(hout, "W", 1, &rfakt, NULL);
		//}
			if ((i + 1) % 16 == 0)
			{
				SetConsoleTextAttribute(hout, 0xff);
				WriteConsoleA(hout, "\n", 1, &rfakt, NULL);
			}
	}
	_getch();
	//system("pause");
	FreeConsole();
	return 0;
}