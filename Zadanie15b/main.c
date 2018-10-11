#include<stdio.h>
#include<stdlib.h> // obs³uga qsort
#include<string.h>
#include<locale.h>
#include<malloc.h>
#include<Windows.h>
//#pragma _CTR_SECURE_NO_WARNINGS 1
#pragma warning(disable : 4996)

int myCompare(const void* p1, const void* p2)
{
	//return strcmp( (char*)p1, (char*)p2);
	//return strcmp( p1, p2);
	//return 1;
	const char* aa = *(const char**)p1;
	const char* bb = *(const char**)p2;
	//return strcmp( *(const char**)p1, *(const char**)p2); // tak jest dobrze
	return strcoll(*(const char**)p1, *(const char**)p2); // tak jest dobrze

														  //return strcmp(aa, bb); // tak te¿ dobrze, jeœli pwoy¿sze zrobiæ
														  //return strcmp(*(char* const*)p1, *(char* const*)p2); // tak jest celuj¹co!
}
int myCompareInt(const void *p1, const void *p2)
{
	//int *xx, *yy;
	//xx = (int*)p1;
	//yy = (int*)p2;
	//int res = *xx - *yy;
	//return res;
	return *(int*)p1 - *(int*)p2;
}

int main(void)
{
	char *pText;
	char *pWords[112];
	char wordToPrint[25];
	int sizeWords = 112;
	int wordWidth = 25;
	char separators[] = " \r\n;!,.?\"-";
	char *token;
	char *nextToken;
	char licznik = 0;
	FILE *fi, *fo2;

	//setlocale(LC_ALL, ""); // bez tego kod ASCII
	//setlocale(LC_ALL, "pl-PL"); // tu dobrze tak jak pusto
	setlocale(LC_CTYPE, "pl-PL"); // dobrze wyœwietla, Ÿle sortuje
								  //setlocale(LC_CTYPE, ""); // dobrze wyœwietla, Ÿle sortuje, jak wy¿ej
	setlocale(LC_COLLATE, "pl-PL"); // dobrze sortuje, Ÿle wyœwietla
									//setlocale(LC_ALL, "pl_PL"); // b³¹d daje œmietnik: ma byæ pl-PL
									//setlocale(LC_ALL, "en-US"); // kod ASCII
	fopen_s(&fi, "035.txt", "rb");
	//fopen_s(&fo1, "wynik_a.txt", "wt");
	fopen_s(&fo2, "wynik_b.txt", "wt");

	// pobranie wielkoœci pliku 
	fseek(fi, 0, SEEK_END);
	long fileSize = ftell(fi);
	rewind(fi);

	// wczytanie pliku do tablicy pText
	pText = malloc(fileSize * sizeof(char) + 1);
	fread_s(pText, fileSize, sizeof(char), fileSize, fi);
	pText[fileSize] = '\0';
	fclose(fi);

	//CharToOem(pText, pText);
	//printf_s("%s", pText);

	// wyrazów maksymalnie: 120, d³ugoœæ wyrazu maksymalna: 20

	// zainicjowanie tablicy na wyrazy
	for (char i = 0; i < sizeWords; i++)
	{
		pWords[i] = (char*)calloc(wordWidth, sizeof(char));
	}


	// odczytanie wyrazów funkcj¹ strtok
	token = strtok_s(pText, separators, &nextToken);

	do // musi byæ "do", bo najpierw zapisujemy pocz¹tkowy token do licznika zerowego
	{
		strcpy_s(pWords[licznik], wordWidth, token);
		licznik++;
		//sprintf_s(wordToPrint, 25, "%3d: %s\n", licznik, token);
		//fputs(wordToPrint, fo1);
		//CharToOem(wordToPrint, wordToPrint);
		//printf_s(wordToPrint);
		token = strtok_s(NULL, separators, &nextToken);
	} while (token != NULL);
	//fclose(fo1);
	printf_s("Wyczytano wyrazow: %d\r\n", licznik);

	char **pNewTab = NULL;
	// a[i][j] = *( (a + i) + j )
	pNewTab = malloc(sizeof(char**));
	for (char i=0; i < 5; i++)
	{
		pNewTab = realloc(pNewTab, (i+1) * sizeof(char**));
		pNewTab[i] = (char*)calloc(wordWidth,sizeof(char));
		int sizent = sizeof("7");
		strcpy_s(pNewTab[i], wordWidth, "7");
	}
	for (char i = 0; i < 5; i++)
	{
		printf_s("Specjalne: %s\n", pNewTab[i]);
	}

	//goto przeskocz;
	// usuwanie powtarzaj¹cych siê wyrazów
	char** pNewTaba = NULL;
	pNewTaba = malloc(sizeof(char**));
	int sizeNewTab = 0;
	for (char i = 0, was = 0; i < licznik; ++i, was = 0)
	{
		for (char j = i + 1; j < licznik; ++j)
		{
			// takie same wyrazy
			if (strcmp(pWords[i], pWords[j]) == 0)
			{
				strcpy_s(pWords[j], wordWidth, "");
				//	printf_s("Powtórzony wyraz: %s\n", pWords[j]);
				was++;
			}
		}
		if (was == 0)
		{
			if (strlen(pWords[i]))
			{
				pNewTaba = realloc(pNewTaba, (sizeNewTab + 1) * sizeof(char**));
				pNewTaba[sizeNewTab] = (char*)calloc(wordWidth, sizeof(char));
				strcpy_s(pNewTaba[sizeNewTab], wordWidth, pWords[i]);
				sizeNewTab++;
			}
		}

	}

przeskocz:;
	int aray[] = { 1, 5, 3, 4, 8 };
	int n = sizeof(aray) / sizeof(int);
	for (char i = 0; i < 5; i++)
		printf_s("Liczba %d\n", aray[i]);

	qsort(aray, n, sizeof(int), myCompareInt);

	for (char i = 0; i < 5; i++)
		printf_s("Liczba %d\n", aray[i]);
	printf_s("Wielkosc sizeof char i char*: %zu %zu\n",
		sizeof(char), sizeof(char*));

	qsort(pWords, 109, sizeof(char*), myCompare);
	qsort(pNewTaba, sizeNewTab, sizeof(char*), myCompare);

	// sortowanie w³asnej roboty

	/*for (char i = 0; i < licznik; i++)
	{
	for (char j = i + 1; j < licznik; ++j)
	{
	if (myCompare(pWords[i], pWords[j]) > 0)
	{
	strcpy_s(wordToPrint, wordWidth, pWords[j]);
	strcpy_s(pWords[j], wordWidth, pWords[i]);
	strcpy_s(pWords[i], wordWidth, wordToPrint);
	}
	}
	}*/
	licznik = sizeof(pNewTaba) / sizeof(pNewTaba[0]);
	printf_s("sizeoftab: %i\n", (int)sizeof(pNewTaba));
	printf_s("sizeof char*: %i\n", sizeof(pNewTaba[0]));
	printf_s("licznik: %i\n", licznik);
	licznik = 7;

	int *a = NULL;
	a = malloc(16 * sizeof(int));
	a[3] = 12;
	printf_s("a: %d\n", sizeof(a));
	printf_s("a[3]: %d\n", a[3]);
	free(a);
	system("pause");
	for (char i = 0; i < sizeNewTab; ++i)
	{

		//sprintf_s(wordToPrint, wordWidth, "%3d: %s", i + 1, pWords[i]);
		sprintf_s(wordToPrint, wordWidth, "%3d: %s", i + 1, pNewTaba[i]);
		//fprintf_s(fo2, "%3d: %s\n", i+1, pWords[i]);
		fprintf_s(fo2, "%s\n", wordToPrint);
		//AnsiToOem(wordToPrint, wordToPrint);
		printf_s("%s\n", wordToPrint);
	}

	// koñcowe zwalnianie pamiêci
	fclose(fo2);
	free(pText);
	for (char i = 0; i < sizeWords; i++)
	{
		free(pWords[i]);
	}
	//setlocale(LC_CTYPE, "ru-RU");
	for (char i =0; i < sizeNewTab ; i++)
		free(pNewTaba[i]);
	char tab[] = { 221, 143, '\0' };
	//printf_s("%s\n", tab);
	//setlocale(LC_ALL, "ru-RU");
	//printf_s("%s\n", tab);
	system("pause");
}