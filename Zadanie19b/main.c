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

	int mouseState, virtualCode, controlState;

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

	sprintf_s(buf, 256, "Nowy modu³: %d\nProgram mo¿na zakoñczyæ naciskaj¹c lewy Alt + prawy przycisk myszy\n", consoleMode);
	CharToOem(buf, buf);
	bufSize = strlen(buf);
	WriteConsoleA(hout, buf, bufSize, &rfakt, NULL);

	// pêtla nieskoñczona
	while (1)
	{
		ReadConsoleInputA(hinp, &eventRecord, 1, &nrEvent); //odczyt komunikatu zdarzenia
		if (eventRecord.EventType == MOUSE_EVENT)
		{
			mouseState = eventRecord.Event.MouseEvent.dwButtonState;
			if (eventRecord.Event.MouseEvent.dwButtonState != 0)
			{
				sprintf_s(buf, 256, "Mouse event: %d\n",
					mouseState);
				bufSize = strlen(buf);
				WriteConsoleA(hout, buf, bufSize, &rfakt, NULL);
				// wariant 1: lewy Alt + prawy przycisk myszy
				if (virtualCode == 18 && controlState == 2 // lewy Alt
					&& mouseState == 2) {
					break;
				}
			}
		}
		else if (eventRecord.EventType == KEY_EVENT)
		{
			{
				virtualCode = eventRecord.Event.KeyEvent.wVirtualKeyCode;
				controlState = eventRecord.Event.KeyEvent.dwControlKeyState;
				if (!eventRecord.Event.KeyEvent.bKeyDown) {
					virtualCode = -1;
				}
				if (eventRecord.Event.KeyEvent.dwControlKeyState) {
					sprintf_s(buf, 256, "Vitual key code: %d, Control key state: %d\n",
						virtualCode, controlState
						);
					bufSize = strlen(buf);
					WriteConsoleA(hout, buf, bufSize, &rfakt, NULL);
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