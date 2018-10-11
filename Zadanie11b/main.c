#include <string.h> // do obs³ugi memset
#include <stdio.h> //malloc
#include <stdlib.h>
#include <Windows.h>

long getFileSize(FILE*);

int main(void)
{
	FILE *fi;
	long fileLength;
	char *pNew = NULL;
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
	
	printf_s("Content of pNew at start: %s\n", pNew);

	printf_s("%14s %p\n", "Address of pArea:", &pArea);
	printf_s("%14s %p\n", "Address of pNew:", &pNew);
	printf_s("Pointer pArea: %p\n", pArea);
	printf_s("Pointer pNew: %p\n", pNew);

	// zmniejszenie pamiêci (zadanie 11b) =============================
	pNew = realloc(pArea, fileLength / 4); // na 2 przy krótszych plikach...
	//pArea = realloc(pArea, 30);
	printf_s("(realokacja)\n");
	//pArea[fileLength / 4 - 1] = '\0'; // [fileLength / 4] daje katastrofê jeœli nie zwiêkszono realloc + 1
	
	printf_s("%14s %p\n", "Address of pArea:", &pArea);
	printf_s("%14s %p\n", "Address of pNew:", &pNew);
	printf_s("%14s %p\n", "Pointer pArea:", pArea);
	printf_s("%14s %p\n", "Pointer pNew:", pNew);

	printf_s("%s\n", pArea);
	printf_s("%s\n", pNew);


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
