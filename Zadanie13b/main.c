#include <string.h> // do obs≥ugi memset
#include <stdio.h> //malloc
#include <stdlib.h>
#include <Windows.h>

long getFileSize(FILE*);


int main(void)
{
	FILE *fi, *fo;
	long fileLength;
	unsigned char* pArea; // taki format naleøy zadeklarowaÊ jawnie w tym zadaniu

	char smallBuf[15];

	char polishTable[] = {
		'π', 'Ê', 'Í', '≥', 'Ò', 'Û', 'ú', 'ø', 'ü',
		'•', '∆', ' ', '£', '—', '”', 'å', 'Ø', 'è'
	};
	int polishCounter[18] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	fopen_s(&fi, "035.txt", "rb");
	fopen_s(&fo, "wynik.txt", "wt");

	// pobranie rozmiaru pliku
	fileLength = getFileSize(fi);

	// przydzielenie obszaru pamiÍci
	pArea = (char*)malloc((fileLength + 1) * sizeof(char));

	// przeczytanie i zamkniÍcie pliku
	fread(pArea, sizeof(char), fileLength, fi);
	//fread_s(pArea, fileLength+1, sizeof(char), fileLength, fi);
	fclose(fi);

	pArea[fileLength] = '\0';


	// liczenie polskich liter ==================================
	for (int znak = 0; pArea[znak]; ++znak) {
		for (int i = 0; i < 18; ++i)
		{
			if ((char)pArea[znak] == polishTable[i])
			{
				polishCounter[i]++;
				break;
			}
		}
	}

	// wypisywanie wynikÛw ======================================
	for (char i = 0; i < 18; i++)
	{
		sprintf_s(smallBuf, 15, "%c(%d)", polishTable[i], polishCounter[i]);

		if ((i + 1) % 9 == 0) // da≥em 9 zamiast 10 jak w zadaniu
			strcat_s(smallBuf, 15, "\n");
		
		fprintf_s(fo,"%6s", smallBuf);
		CharToOem(smallBuf, smallBuf);
		printf_s("%6s", smallBuf);
	}
	puts("\n");

	free(pArea);
	fclose(fo);
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
