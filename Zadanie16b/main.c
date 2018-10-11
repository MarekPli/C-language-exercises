#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>

int randomizeColor(int bkg)
{
	int randColor;
	do
	{
		// randColor = rand() % 256;
		randColor = rand() % 16;
		randColor += bkg;
	} while (randColor / 16 == randColor % 16);
	return randColor;
}

int main(void)
{
	FILE *fi;
	char buf[256];
	int size, rfakt;
	int randColor;
	int background;
	COORD myPole = { 0, 0 };
	COORD field; 

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	field = GetLargestConsoleWindowSize(hout);

	srand(_time32(NULL));
	background = rand() % 16 + 1;
	background *= 16;
	
	FillConsoleOutputAttribute(hout, background, (field.X * field.Y), myPole, &rfakt);

	fopen_s(&fi, "016.txt", "rt");
	while (fgets(buf, 256, fi))
	{
		size = strlen(buf);
		CharToOem(buf, buf);
		randColor = randomizeColor(background);
		SetConsoleTextAttribute(hout, randColor);
		WriteConsoleA(hout, buf, size, &rfakt, NULL);

	}
	fclose(fi);
	
	_getch();
	FreeConsole();
	return 0;
}