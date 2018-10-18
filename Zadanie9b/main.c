#include <stdio.h>
#include <direct.h>
#include <time.h>
#include <Windows.h>

void writeNextNumber(FILE *fo, char *n, char cond, char nr)
{
	*n = *n + 1; // nie mozna *(n)++, ale dzia³a (*n)++
	if ( *n == cond) // co druga parzysta, co trzecia nieparzysta
	{
		fprintf(fo, "%3i", nr);
		*n = 0;
	}
}

void printFile(FILE *fo, char *buf, char *msg)
{
	char nr, idx = 0;

	sprintf_s(buf, 256, "%s\n", msg);
	CharToOem(buf, buf);
	printf_s(buf);

	fseek(fo, 0, SEEK_SET);
	while (fgets(buf, 4, fo))
	{
		sscanf_s(buf, "%hhd", &nr);
		++idx;
		//put(buf);
		//		printf_s(buf);
		printf_s("%4d", nr);
		if (idx % 16 == 0) {
			printf_s("\n");
//			idx = 0;
		}
	}
	puts("\n"); // puts dopisuje \n, wiêc mamy tutaj \n\n
}

int main(void)
{
	char buf[256];
	FILE *fi, *fo1, *fo2; // moja tradycja: odczyt/zapis - fi/fo 
	char nr;
	char idx = 0;
	// odd, even: nieparzysty (dziwny, strange), parzysty (nawet, w³aœnie, równo, evenly)
	char isOdd; // parzyste czy nieparzyste
	char nOdd, nEven;

	// tym razem wariant 10: co druga parzysta i co trzecia nieparzysta
	// bo wariant 1 (ka¿da parzysta i ka¿da nieparzysta) jest zbyt prosty 
	// a warto przeæwiczyæ ró¿ne indeksy parzystych i nieparzystych

	// wczeœniej skopiowa³em do bie¿¹cego katalogu
	// katalog DANE wraz z zawartoœci¹: plikiem test.txt
	// stworzony w zadaniu 9a

	fopen_s(&fi, "DANE\\test.txt", "rt"); // otwieram istniej¹cy plik w podkatalogu
	fopen_s(&fo1, "DANE\\plik1.txt", "wt+");
	fopen_s(&fo2, "DANE\\plik2.txt", "wt+");

	/*
	// rozbudowana wersja programu: 
	// pêtla sprawdzania czy koniec pliku
	// i zakoñczenie warunkowe: wyjœcie z pêtli przez break
	while (!feof(fi)) {
		read = fgets(buf, 4, fi);
		if (read == NULL)
			break;
		// ... g³ówna czêœæ programu ...
	}
	*/
	nOdd = nEven = 0;
	while (fgets(buf, 4, fi)) // fgets zwraca NULL przy koñcu pliku
	{
		// odczytujê kolejn¹ liczbê
		sscanf_s(buf, "%hhd", &nr);
		++idx;

		isOdd = nr % 2 ? 1 : 0; // sprawdzanie parzystoœci

		if (isOdd)
		{
			writeNextNumber(fo2, &nOdd, 3, nr); // co trzecia nieparzysta czyli odd
		} 
		else
		{
			//nEven++;
			//if (nEven == 2) // co druga parzysta
			//{
			//	fprintf(fo1, "%3i", nr);
			//	nEven = 0;
			//}
			writeNextNumber(fo1, &nEven, 2, nr);
		}
	}

	// fseek(fi, 0, SEEK_SET);


	//sprintf_s(buf,256,"%s\n", "Drukujemy parzyste, zawartoœæ pliku plik1:");
	//CharToOem(buf, buf);
	//printf_s(buf);
	// GDY zrobi³em b³¹d w opisie, martwi³em siê ¿e wychodz¹ inne liczby
	printFile(fi, buf, "Drukujemy ca³oœæ, zawartoœæ pliku DANE\\text.txt:");
	printFile(fo1, buf, "Drukujemy co drugie parzyste, zawartoœæ pliku plik1.txt:");
	printFile(fo2, buf, "Drukujemy co trzecie nieparzyste, zawartoœæ pliku plik2.txt:");
	//fseek(fo1, 0, SEEK_SET);
	//while (fgets(buf, 4, fo1))
	//{
	//	sscanf_s(buf, "%hhd", &nr);
	//	++idx;
	//	//put(buf);
	//	//		printf_s(buf);
	//	printf_s("%4d", nr);
	//	if (idx % 16 == 0) {
	//		puts("\n");
	//		idx = 0;
	//	}
	//}
	//puts("\n");

	fclose(fi);
	fclose(fo1);
	fclose(fo2);
	system("pause");
	return 0;
}