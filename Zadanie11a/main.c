#include <string.h> // do obs³ugi memset
#include <stdio.h> //malloc
#include <stdlib.h>
#include <Windows.h>

int main(void)
{
	FILE *fi;
	long fileLength;
	char* pArea;
	
//	printf_s("WskaŸnik: %zu\n", sizeof(pArea));

	fopen_s(&fi,"035.txt", "rb");
	//fopen_s(&fi,"018.txt", "rb");
	
	// pobranie rozmiaru pliku
	fseek(fi, 0, SEEK_END);
	fileLength = ftell(fi);
	rewind(fi);

	// przydzielenie obszaru pamiêci
	pArea = (char*)malloc( (fileLength + 1 ) * sizeof(char));
	
	// przeczytanie i zamkniêcie pliku
	fread(pArea, sizeof(char), fileLength, fi);
	//fread_s(pArea, fileLength+1, sizeof(char), fileLength, fi);
	fclose(fi);
	
	CharToOem(pArea, pArea);
	//printf_s("Rozmiar pliku: %ld\n", fileLength);
	
	pArea[fileLength] = '\0';

	//printf_s("Wielkoœæ pliku %ld\n", strlen(pArea));

	printf_s("%s\n", pArea);

	// zmniejszenie pamiêci (zadanie 11b) =============================
	//realloc(pArea, fileLength / 2);
	realloc(pArea, 30);
	//printf_s("%s\n", pArea);

	// ponowne zwiêkszenie pamiêci (zadanie 11c) =======================
	pArea = (char*)realloc(pArea, fileLength +1);
	pArea[31] = 'x';
	//printf_s("%s\n", pArea);
	free(pArea);

	system("pause");
}