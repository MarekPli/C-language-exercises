#include<stdio.h>
#include<conio.h> // _getch()
#include<Windows.h>

int main(void)
{
	
	INPUT_RECORD eventRecord;
	
	int nrEvent, rfakt;
	int consoleMode, oldConsoleMode;

	char buf[256];
	int bufSize;

	char keyPressedBefore = '\0'; // NULL nie pasuje, chodzi o znak
	char keyPressed;

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hinp = GetStdHandle(STD_INPUT_HANDLE);
	//FreeConsole();
	AllocConsole();

	FlushConsoleInputBuffer(hinp); //czyszczenie kolejki komunikatów
	
	GetConsoleMode(hinp, &oldConsoleMode); // poprzedni modu³
	
	sprintf_s(buf, 256, "Dawny modu³: %d\n", oldConsoleMode);
	bufSize = strlen(buf);
	CharToOem(buf, buf);
	WriteConsoleA(hout, buf, bufSize, &rfakt, NULL); 
	
	consoleMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	
	sprintf_s(buf, 256, "Nowy modu³: %d\n", consoleMode);
	CharToOem(buf, buf);
	bufSize = strlen(buf);
	WriteConsoleA(hout, buf, bufSize, &rfakt, NULL); 
	
	// pêtla nieskoñczona
	while (1)
	{
		ReadConsoleInputA(hinp, &eventRecord, 1, &nrEvent); //odczyt komunikatu zdarzenia
		if (eventRecord.EventType == MOUSE_EVENT)
		{
			if (eventRecord.Event.MouseEvent.dwButtonState != 0)
			{
				sprintf_s(buf, 256, "Mouse event: %d, nr: %d\n",
					eventRecord.Event.MouseEvent.dwButtonState, nrEvent);
				bufSize = strlen(buf);
				WriteConsoleA(hout, buf, bufSize, &rfakt, NULL);
			}
		}
		else if (eventRecord.EventType == KEY_EVENT)
		{
			{
				if (eventRecord.Event.KeyEvent.uChar.AsciiChar
					&& eventRecord.Event.KeyEvent.bKeyDown == 0)
				{
					keyPressed = eventRecord.Event.KeyEvent.uChar.AsciiChar;
					sprintf_s(buf, 256, "Key event: %c\n",
						keyPressed);
					bufSize = strlen(buf);
					WriteConsoleA(hout, buf, bufSize, &rfakt, NULL);
					if (keyPressedBefore == 'a' && keyPressed == 'b')
					{
						break; // wyjœcie z pêtli bo wariant 1
					}
					keyPressedBefore = keyPressed;
				}
				
			}

		}


	}

	sprintf_s(buf, 256, "Pêtla zosta³a zakoñczona...\n");
	bufSize = strlen(buf);
	CharToOem(buf, buf);
	WriteConsoleA(hout, buf, bufSize, &rfakt, NULL);

	_getch();
	FreeConsole();
	return 0;
}