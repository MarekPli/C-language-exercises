#include <stdio.h>
#include <Windows.h>

void showBinary(char nr)
{
	char size = sizeof(nr) * 8; // rozmiar elementu liczony jest w bajtach, 
	// mno¿¹c przez 8 zamieniam na bity
	char c;
	int k = 1, kn;
	
	k <<= size-1 ; // odejmuje 1, bo ju¿ jest 1 na pocz¹tku
	kn = k;
	while (k)
	{
		printf_s("%3d ", k);
		k >>= 1;
			
	}
	printf_s("\n");
	k = kn;
	for (char i = 0; i < size; ++i, k >>= 1)
	{
		c = (nr & k) ? 1 : 0;
		printf_s("%3d ", c);
	}

	printf_s(" (%d)\n", nr);
}


int main(void)
{
	char nr; // zakres od -128 127
	char buf[256] = "Podaj liczbê (z zakresu signed char): ";
	CharToOem(buf, buf);
	printf_s(buf); 
	scanf_s("%hhd", &nr);
	showBinary(nr);
	system("pause");
	return 0;
}
