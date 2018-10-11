#include <stdio.h>
#include <Windows.h>

int main(void)
{
	// pierwszy rz¹dek
	printf_s("%2s|","");
	for (char i = 0; i < 16; i++) {
		printf_s(" *%X", i);
	}
	printf_s("\n");
	
	// drugi rz¹dek
	printf_s("%s\n", 
		"--+------------------------------------------------");
	// g³ówne zadanie
	for (char i = 2; i <= 7; i++) {
		printf_s("%x*|", i);
		for (char j = 0; j < 16; j++)
		{
			printf("%3c", i * 16 + j);
		}
		printf_s("\n");
	}
	
	system("pause");
}