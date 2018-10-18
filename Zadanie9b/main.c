#include <stdio.h>
#include <direct.h>
#include <time.h>
#include <Windows.h>

void writeNextNumber(FILE *fo, char *n, char cond, char nr)
{
	*n = *n + 1; // nie mozna *(n)++, ale dzia�a (*n)++
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
	puts("\n"); // puts dopisuje \n, wi�c mamy tutaj \n\n
}

int main(void)
{
	char buf[256];
	FILE *fi, *fo1, *fo2; // moja tradycja: odczyt/zapis - fi/fo 
	char nr;
	char idx = 0;
	// odd, even: nieparzysty (dziwny, strange), parzysty (nawet, w�a�nie, r�wno, evenly)
	char isOdd; // parzyste czy nieparzyste
	char nOdd, nEven;

	// tym razem wariant 10: co druga parzysta i co trzecia nieparzysta
	// bo wariant 1 (ka�da parzysta i ka�da nieparzysta) jest zbyt prosty 
	// a warto prze�wiczy� r�ne indeksy parzystych i nieparzystych

	// wcze�niej skopiowa�em do bie��cego katalogu
	// katalog DANE wraz z zawarto�ci�: plikiem test.txt
	// stworzony w zadaniu 9a

	fopen_s(&fi, "DANE\\test.txt", "rt"); // otwieram istniej�cy plik w podkatalogu
	fopen_s(&fo1, "DANE\\plik1.txt", "wt+");
	fopen_s(&fo2, "DANE\\plik2.txt", "wt+");

	/*
	// rozbudowana wersja programu: 
	// p�tla sprawdzania czy koniec pliku
	// i zako�czenie warunkowe: wyj�cie z p�tli przez break
	while (!feof(fi)) {
		read = fgets(buf, 4, fi);
		if (read == NULL)
			break;
		// ... g��wna cz�� programu ...
	}
	*/
	nOdd = nEven = 0;
	while (fgets(buf, 4, fi)) // fgets zwraca NULL przy ko�cu pliku
	{
		// odczytuj� kolejn� liczb�
		sscanf_s(buf, "%hhd", &nr);
		++idx;

		isOdd = nr % 2 ? 1 : 0; // sprawdzanie parzysto�ci

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


	//sprintf_s(buf,256,"%s\n", "Drukujemy parzyste, zawarto�� pliku plik1:");
	//CharToOem(buf, buf);
	//printf_s(buf);
	// GDY zrobi�em b��d w opisie, martwi�em si� �e wychodz� inne liczby
	printFile(fi, buf, "Drukujemy ca�o��, zawarto�� pliku DANE\\text.txt:");
	printFile(fo1, buf, "Drukujemy co drugie parzyste, zawarto�� pliku plik1.txt:");
	printFile(fo2, buf, "Drukujemy co trzecie nieparzyste, zawarto�� pliku plik2.txt:");
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