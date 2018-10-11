#include <stdio.h>
#include <direct.h>
#include <time.h>
#include <Windows.h>

void printFileBin(FILE*, char*, char*);
void writeNextNumberBinary(char*, char, char, FILE*);

int main(void)
{
	char buf[256];
	FILE *fi, *fo1, *fo2;
	char isOdd, nOdd, nEven;
	char randomNr; // jeœli zmienna jest typu int, to plik ma 400 a nie 100 bajtów

	// warunek 1: plik1 ka¿da liczba parzysta, plik2 ka¿da liczba nieparzysta
	
	_mkdir("DANE"); // stwarza katalog jeœli go nie ma
	
	fopen_s(&fi, "DANE\\test.bin", "wb+"); 
	fopen_s(&fo1, "DANE\\plik1.bin", "wb+"); 
	fopen_s(&fo2, "DANE\\plik2.bin", "wb+"); 

	srand(_time32(NULL)); // bez unsigned wyskakuje ostrze¿enie

	printf_s("sizeof (w bajtach) zmiennej randomNr: %zu\n", sizeof(randomNr));
	printf_s("sizeof (w bajtach) typu char: %zu\n", sizeof(char));
	puts("\n");

	for (char i = 0; i < 100; ++i)
	{
		randomNr = (rand() % 198) - 99; // od -99 do +99
		if (i == 5) randomNr = 0; // test z zerem
		// zapisuje z bufora randomNr 1 blok o rozmiarze char (czyli 1 bajt)
		fwrite(&randomNr,sizeof(randomNr),1,fi);
	}
	fseek(fi, 0, SEEK_SET);
	nOdd = nEven = 0;
	for (char i = 0; i < 100; ++i)
	{
		fread(&randomNr, sizeof(randomNr), 1, fi); // tak samo jak fwrite
		
		isOdd = randomNr % 2 ? 1 : 0; // sprawdzanie parzystoœci
		if (isOdd)
			writeNextNumberBinary(&nOdd, randomNr, 1, fo2);
		else
			writeNextNumberBinary(&nEven, randomNr, 1, fo1);

		
		//if (isOdd)
		//{
		//	nOdd++;
		//	if (nOdd == 1)
		//	{
		//		fwrite(&randomNr, sizeof(randomNr), 1, fo2);
		//		nOdd = 0;
		//	}
		//}
		//else
		//{
		//	nEven++;
		//	if (nEven == 1)
		//	{
		//		fwrite(&randomNr, sizeof(randomNr), 1, fo1);
		//		nEven = 0;
		//	}

		//}
		//printf_s("%4i", randomNr);
		//if ((i+1) % 16 == 0) putchar('\n');
	}
	
	
	printFileBin(fi, buf, "Drukujemy ca³oœæ, zawartoœæ pliku DANE\\text.bin:");
	printFileBin(fo1, buf, "Drukujemy DANE\\plik1.bin - ka¿da liczba parzysta:");
	printFileBin(fo2, buf, "Drukujemy DANE\\plik2.bin - ka¿da liczba nieparzysta:");

	
	puts("\n");
	system("pause");
	return 0;
}


void printFileBin(FILE *fi, char *buf, char *msg)
{
	char nr;
	char i = 0;
	sprintf_s(buf, 256, "%s\n", msg);
	CharToOem(buf, buf);
	printf_s(buf);

	fseek(fi, 0, SEEK_SET);
	//	for (char i = 0; i < size; i++)
	{
		//fread(&nr, sizeof(nr), 1, fi); // tak samo jak fwrite
		//printf_s("%4i", nr);
		//if ((i + 1) % 16 == 0) putchar('\n');
		while (fread(&nr, sizeof(nr), 1, fi)) // dopóki nie zwróci 0 bajtów
		{
			printf_s("%4i", nr);
			i++;
			if (i % 16 == 0) putchar('\n');
		}
	}
	puts("\n");
}

void writeNextNumberBinary(char* n, char nr, char cond, FILE* fo)
{
	//*n = *n + 1; // nie mo¿na *(n)++
	(*n)++;
	if (*n == cond) // co cond-na liczba
	{
		fwrite(&nr, sizeof(nr), 1, fo);
		*n = 0;
	}
}

