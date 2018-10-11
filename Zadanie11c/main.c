#include <string.h> // do obs³ugi memset
#include <stdio.h> //malloc
#include <stdlib.h>
#include <Windows.h>

long getFileSize(FILE*);

int main(void)
{
	FILE *fi;
	long fileLength;
	char* pArea;

	fopen_s(&fi, "035.txt", "rb");

	// pobranie rozmiaru pliku
	fileLength = getFileSize(fi);

	// przydzielenie obszaru pamiêci
	pArea = (char*)malloc((fileLength + 1) * sizeof(char));

	// przeczytanie i zamkniêcie pliku
	fread(pArea, sizeof(char), fileLength, fi);
	//fread_s(pArea, fileLength+1, sizeof(char), fileLength, fi);
	fclose(fi);

	CharToOem(pArea, pArea);
	pArea[fileLength] = '\0';


	// zmniejszenie pamiêci (jak w zadaniu 11b) ===========================
	realloc(pArea, fileLength / 3); // na 2 przy krótszych plikach...
	//pArea[fileLength / 3 ] = '\0'; // to jest prawid³owy rozmiar: ostatni znak przydzielony
	printf_s("%s\n", pArea);

	// ponowne nadanie tej samej wielkoœci ===========================
	pArea = realloc(pArea, fileLength + 1); 
	// jeœli nie ma przypisania, dziej¹ siê jakieœ dziwne rzeczy
	pArea[fileLength / 3] = 'Q';
	printf_s("%s\n", pArea);


	free(pArea);

	system("pause");
}

long getFileSize(FILE* file)
{
	long result;
	fseek(file, 0, SEEK_END);
	result = ftell(file);
	rewind(file);
	return result;
}
