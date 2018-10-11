#include <string.h> // do obs³ugi memset
#include <stdio.h> //malloc
#include <stdlib.h>
#include <Windows.h>

enum znaki {
	/*
	- wszystkich znaków,
	- drukowalnych znaków,
	- znaków alfanumerycznych,
	- znaków alfabetycznych,
	- separatorów,
	- bia³ych znaków,
	- du¿ych liter,
	- ma³ych liter.
	*/
	all, print, alnum, alpha, punct, blank, upper, lower
};

long getFileSize(FILE*);

int main(void)
{
	FILE *fi, *fo;
	long fileLength;
	unsigned char* pArea; // taki format nale¿y zadeklarowaæ jawnie w tym zadaniu
	
	int wyniki[] = {0, 0, 0, 0, 0, 0, 0, 0};
	char buf[1000] = {'\0'};
	char smallBuf[256];

	fopen_s(&fi, "035.txt", "rb");
	fopen_s(&fo, "wynik.txt", "wb");

	// pobranie rozmiaru pliku
	fileLength = getFileSize(fi);

	// przydzielenie obszaru pamiêci
	pArea = (char*)malloc((fileLength + 1) * sizeof(char));

	// przeczytanie i zamkniêcie pliku
	fread(pArea, sizeof(char), fileLength, fi);
	//fread_s(pArea, fileLength+1, sizeof(char), fileLength, fi);
	fclose(fi);

	pArea[fileLength] = '\0';
	// przekszta³cenie przed wpisaniem \0 tworzy problem?
	CharToOemA(pArea, pArea);

	printf_s("%s\n", pArea);

	for (int i = 0; pArea[i]; i++) {
		wyniki[all]++;
		if (isprint(pArea[i]))
			wyniki[print]++;
		if (isalnum(pArea[i]))
			wyniki[alnum]++;
		if (isalpha(pArea[i]))
			wyniki[alpha]++;
		if (ispunct(pArea[i]))
			wyniki[punct]++;
		if (isblank(pArea[i]))
			wyniki[blank]++;
		if (isupper(pArea[i]))
			wyniki[upper]++;
		if (islower(pArea[i]))
			wyniki[lower]++;
	}

	sprintf_s(smallBuf, 256, "%25s: %3d\n", "Wszystkie znaki", wyniki[all]);
	strcat_s(buf, 1000, smallBuf);
	sprintf_s(smallBuf, 256, "%25s: %3d\n", "drukowane (print)", wyniki[print]);
	strcat_s(buf, 1000, smallBuf);
	sprintf_s(smallBuf, 256, "%25s: %3d\n", "alfanumeryczne (alnum)", wyniki[alnum]);
	strcat_s(buf, 1000, smallBuf);
	sprintf_s(smallBuf, 256, "%25s: %3d\n", "alfabetyczne (alpha)", wyniki[alpha]);
	strcat_s(buf, 256, smallBuf);
	sprintf_s(smallBuf, 256, "%25s: %3d\n", "separatory (punct)", wyniki[punct]);
	strcat_s(buf, 1000, smallBuf);
	sprintf_s(smallBuf, 256, "%25s: %3d\n", "bia³e znaki (blank)", wyniki[blank]);
	strcat_s(buf, 256, smallBuf);
	sprintf_s(smallBuf, 256, "%25s: %3d\n", "du¿e litery (upper)", wyniki[upper]);
	strcat_s(buf, 1000, smallBuf);
	sprintf_s(smallBuf, 256, "%25s: %3d\n", "ma³e litery (lower)", wyniki[lower]);
	strcat_s(buf, 1000, smallBuf);
	
    
	fileLength = strlen(buf);
	fwrite(buf, sizeof(char), fileLength, fo);
	
	CharToOem(buf, buf);
	printf_s("%s\n", buf);
		
	fclose(fo);
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
