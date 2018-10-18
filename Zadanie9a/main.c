#include <stdio.h>
#include <direct.h>
#include <time.h>
#include <Windows.h>
int main(void)
{
	char buf[256];
	FILE *fi;
	char randomNr, nr;
	char idx = 0;
	char *read;
	


	_mkdir("DANE"); // stwarza katalog jeœli go nie ma

	fopen_s(&fi, "DANE\\test.txt", "wt+"); // chodzi o element **FILE
	
	//srand((unsigned)time(NULL)); // bez unsigned wyskakuje ostrze¿enie
	//srand(_time32(NULL)); // bez unsigned wyskakuje ostrze¿enie
	
	for (char i = 0; i < 100; ++i)
	{
		randomNr = ( rand() % 198 ) - 99; // od -99 do +99
		fprintf_s(fi, "%3i", randomNr);
	}
	fseek(fi, 0, SEEK_SET);
	while (!feof(fi))
	{
		read = fgets(buf, 4, fi);
		if (read == NULL)
		{
			puts("\n");
			// inaczej bufor nie zostanie zmieniony
			// i wydrukowana bêdzie powtórnie ostatnia liczba
			break;
		}
		sscanf_s(buf, "%hhd", &nr);
		++idx;
		//put(buf);
//		printf_s(buf);
		printf_s("%4d", nr);
		if (idx % 16 == 0) {
			puts("\n");
			idx = 0;
		}
		else {
			//printf_s(" ");
		}

	}

	//_getcwd(buf, 256); // odczytuje do buf bie¿¹cy katalog
	//printf_s(buf);
	//printf_s("\n\n");
	fclose(fi);
	system("pause");
	return 0;
}