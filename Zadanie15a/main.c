#include<stdio.h>
#include<stdlib.h> // obsługa qsort
#include<string.h>
#include<locale.h>
#include<Windows.h>

int myCompare(const void* p1, const void* p2)
{
	//return strcmp( (char*)p1, (char*)p2);
	//return strcmp( p1, p2);
	//return 1;
	const char* aa = *(const char**)p1;
	const char* bb = *(const char**)p2;
	//return strcmp( *(const char**)p1, *(const char**)p2); // tak jest dobrze
	return strcoll( *(const char**)p1, *(const char**)p2); // tak jest dobrze

	//return strcmp(aa, bb); // tak też dobrze, jeśli pwoyższe zrobić
	//return strcmp(*(char* const*)p1, *(char* const*)p2); // tak jest celująco!
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
	FILE *fi, *fo1, *fo2;
	
	//setlocale(LC_ALL, ""); // bez tego kod ASCII
	//setlocale(LC_ALL, "pl-PL"); // tu dobrze tak jak pusto
	setlocale(LC_CTYPE, "pl-PL"); // dobrze wyświetla, źle sortuje
	//setlocale(LC_CTYPE, ""); // dobrze wyświetla, źle sortuje, jak wyżej
	setlocale(LC_COLLATE, "pl-PL"); // dobrze sortuje, źle wyświetla
	//setlocale(LC_ALL, "pl_PL"); // błąd daje śmietnik: ma być pl-PL
	//setlocale(LC_ALL, "en-US"); // kod ASCII
	fopen_s(&fi, "035.txt", "rb");
	fopen_s(&fo1, "wynik_a.txt", "wt");
	fopen_s(&fo2, "wynik_b.txt", "wt");
	
	// pobranie wielkości pliku 
	fseek(fi, 0, SEEK_END);
	long fileSize = ftell(fi);
	rewind(fi);

	// wczytanie pliku do tablicy pText
	pText = malloc(fileSize * sizeof(char)+1);
	fread_s(pText, fileSize, sizeof(char), fileSize, fi);
	pText[fileSize] = '\0';
	fclose(fi);

	//CharToOem(pText, pText);
	//printf_s("%s", pText);
	
	// wyrazów maksymalnie: 120, długość wyrazu maksymalna: 20

	// zainicjowanie tablicy na wyrazy
	for (char i = 0; i < sizeWords; i++)
	{
		pWords[i] = (char*)calloc(wordWidth, sizeof(char));
	}
	
	
	// odczytanie wyrazów funkcją strtok
	token = strtok_s(pText, separators, &nextToken);

	do // musi być "do", bo najpierw zapisujemy początkowy token do licznika zerowego
	{
		strcpy_s(pWords[licznik], wordWidth, token);
		licznik++;
		sprintf_s(wordToPrint, 25, "%3d: %s\n", licznik, token);
		fputs(wordToPrint,fo1);
		//CharToOem(wordToPrint, wordToPrint);
		printf_s(wordToPrint);
		token = strtok_s(NULL, separators, &nextToken);
	} while (token != NULL);
	fclose(fo1);
	printf_s("Wyczytano wyrazow: %d\r\n", licznik);


	// usuwanie powtarzających się wyrazów
	for (char i = 0; i < licznik; ++i)
	{
		for (char j = i + 1; j < licznik; ++j)
		{
			// takie same wyrazy
			if ( strcmp(pWords[i],pWords[j]) == 0 )
			{
				strcpy_s(pWords[j], wordWidth, "");
//				printf_s("Powtórzony wyraz: %s\n", pWords[j]);
			}
		}
	}
	
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

	// sortowanie własnej roboty
	
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
	
	for (char i = 0; i < licznik; ++i)
	{
		
		sprintf_s(wordToPrint, wordWidth, "%3d: %s", i+1, pWords[i]);
		//fprintf_s(fo2, "%3d: %s\n", i+1, pWords[i]);
		fprintf_s(fo2, "%s\n", wordToPrint);
		//AnsiToOem(wordToPrint, wordToPrint);
		printf_s("%s\n", wordToPrint);
	}

	// końcowe zwalnianie pamięci
	//setlocale(LC_ALL, "ru-RU");
	//setlocale(LC_ALL, "ru");
	//printf_s("%s\n", "Путин");// niestety na konsoli nie zadziała
	fclose(fo2);
	free(pText);
	for (char i = 0; i < sizeWords; i++)
	{
		free(pWords[i]);
	}
	system("pause");
}