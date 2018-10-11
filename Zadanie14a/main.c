#include<Windows.h>
#include<stdio.h>
#include<malloc.h>
#include<time.h>
#include<locale.h>
//#pragma warning(disable : 4996)

typedef enum { matka, ojciec, corka, syn, pasierb, pasierbica } role;

struct s_data
{
	int dzien;
	int miesiac;
	int rok;
};
#pragma pack(push,1)
struct s_test
{
	int a;
	char b;
};
#pragma(pop)
struct s_osoba
{
	role rola;
	char *nazwisko;
	char *imie_1;
	char imie_2[20];
	char *nazw_rod;
	struct s_data data_ur;
	//s_data data_ur; // jeœli typedef struct {} s_data;
} ;


struct s_rodzina
{
	char nazwa[30];
	char ilosc;
	struct s_osoba* osoby;
} ;

int main(void)
{
	char buf[256];

	struct s_rodzina rRurykowicze, rPiastowie, rKarolingowie;

	struct s_osoba Ruryk = { ojciec, "z Waregów", "Ruryk", "Waruryk", "Wareg", {21,4,810} };
	struct s_osoba IwanGrozny;
	//struct s_osoba Piast, Mieszko, Boleslaw, Kazimierz = {matka, NULL};
	struct s_osoba Arnulf, Pepin, Karol, Ludwik;
	//Ruryk.imie_1 = "xxx";
	rRurykowicze.osoby = (struct s_osoba*)malloc(sizeof(struct s_osoba)+1);
	rRurykowicze.osoby[0] = Ruryk;

	strcpy_s(rRurykowicze.nazwa, 30, "Rurykowicze");
	
	sprintf_s(buf, 256, "Witamy rodzinê: %s", rRurykowicze.nazwa);
	CharToOem(buf, buf);
	printf_s("%s\n", buf);

	printf_s("Ruryk nazywa siê: %s\n", rRurykowicze.osoby[0].nazwisko);
	
	printf_s("Ruryk nazywa siê: %s\n", Ruryk.nazwisko);
	printf_s("Ruryk ma imiê: %s\n", Ruryk.imie_1);
	printf_s("Ruryk ma drugie imiê: %s\n", Ruryk.imie_2);
	printf_s("Ruryk ma rolê: %d\n", Ruryk.rola);
	
	// b³¹d nadawania tablicy wartoœci drugiej tablicy
	char tab[17] = "auXXXXXXX";
	//char tabi[] = tab; // kompilator zg³asza b³¹d
	char tabi[] = "zrobiê jakieœ b³êdy"; 
	// tab = tabi; // kompilator zg³asza b³¹d
	*(tab + 3) = 'a';
	*(tabi + 3) = 'a';
	printf_s("%s", tabi);

	printf_s("Wielkosc nazwiska Ruryka: %zu\n", sizeof(Ruryk.nazwisko));
	printf_s("trzecia litera nazwiska Ruryka: %c\n", Ruryk.nazwisko[2]);
	// nie mo¿na zmieniaæ wskaŸnikiem zmiennej, na któr¹ wskazuje wskaŸnik
	//*(Ruryk.nazwisko+2) = 'j'; // nie mo¿na tu zmieniaæ, b³¹d nie wyskakuje
	//Ruryk.nazwisko[2] = 'j'; // ani tak
	int len = strlen(Ruryk.nazwisko);
	char *str = Ruryk.nazwisko;
	//Ruryk.imie_2 = malloc(len + 1); // test na drugie imiê
	Ruryk.nazwisko = malloc(len+1); // nazwisko to teraz œmieci
	strcpy_s(Ruryk.nazwisko, len+1,str);
	Ruryk.nazwisko[2] = 'j'; // a teraz wolno
	*(Ruryk.nazwisko + 2) = 'J'; // i tak te¿ wolno

	printf_s("trzecia litera nazwiska Ruryka: %c\n", *(Ruryk.nazwisko+2));

	printf_s("- bo Ruryk nazywa siê: %s\n", Ruryk.nazwisko);
	
	
	//Ruryk.nazwisko = "a";
	printf_s("Wielkosc nazwiska Ruryka: %zu\n", sizeof(Ruryk.nazwisko));


	sprintf_s(buf, 256, "Nazwisko rodowe Ruryka: %s", rRurykowicze.osoby[0].nazw_rod);
	printf_s("%s\n", buf);

	printf_s("Symboliczna data urodzenia Ruryka (zmar³ 879): rok miesi¹c dzieñ %d %d %d\n", 
		Ruryk.data_ur.rok,
		Ruryk.data_ur.miesiac,
		Ruryk.data_ur.dzien
	);

	printf_s("Wielkosc struktury s_osoba: %zu\n", sizeof(struct s_osoba));
	printf_s("Wielkosc struktury s_rodzina: %zu\n", sizeof(struct s_rodzina));
	printf_s("Wielkosc Rurykowiczow: %zu\n", sizeof(rRurykowicze));
	printf_s("Wielkosc nazwy Rurykowiczow: %zu\n", sizeof(rRurykowicze.nazwa));

	printf_s("Wielkosc daty: %zu\n", sizeof(struct s_data));
	printf_s("Wielkosc testu: %zu\n", sizeof(struct s_test));

//SYSTEMTIME st;
	//GetLocalTime(&st);

	time_t timet;
	timet = time(NULL);
	//printf_s("Biezaca data: %d.%d.%d %d:%d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute);
	
	// albo jeszcze inaczej: zmienna po inicjalizacji :
	//time(&tm);
	//ctime(%tm); // zwraca string reprezentuj¹cy czas tm
	// zamiana na czas lokalny i zapisanie do struktury tm: 
	//struct tm *myTime = localtime_s(&tm);

	struct tm myTime; // nie wskaŸnik!!!
	gmtime_s(&myTime, &timet);
	printf_s("Biezaca data gmtime: %02d.%02d.%02d %02d:%02d\n",
		myTime.tm_mday, myTime.tm_mon, myTime.tm_year + 1900,
		myTime.tm_hour, myTime.tm_min);

	localtime_s(&myTime, &timet);
	printf_s("Biezaca data localtime: %02d.%02d.%02d %02d:%02d\n",
		myTime.tm_mday, myTime.tm_mon, myTime.tm_year + 1900,
		myTime.tm_hour, myTime.tm_min);

	ctime_s(buf, 256, &timet);
	printf_s("Biezaca data ze zmiennej typu time_t: %s\n", buf);

	//a teraz ju¿ przekszta³cona zmienna struct tm: myTime
	asctime_s(buf, 256, &myTime); 
	
	printf_s("asctime: %s\n", buf); // skutek ten sam co ctime
	
	strftime(buf,256,"Strefa czasowa: %Z" 
		"%nnazwa dnia tygodnia: %A%nnazwa miesi¹ca %B"
		"%nreprezentacja czasu dla ust.reg.: %X", 
		&myTime);
	CharToOem(buf, buf);
	printf_s("strftime:\n%s\n", buf); // skutek ten sam co ctime

	gmtime_s(&myTime, &timet);
	strftime(buf, 256, "Strefa czasowa: %Z"
		"%nnazwa dnia tygodnia: %A%nnazwa miesi¹ca %B"
		"%nreprezentacja czasu dla ust.reg.: %X",
		&myTime);
	CharToOem(buf, buf);
	printf_s("strftime:\n%s\n", buf); // skutek ten sam co ctime

	// i z powrotem do time_t
	timet = mktime(&myTime);
	ctime_s(buf, 256, &timet);
	printf_s("Zmienna typu time_t po odczytaniu jej z tm: %s\n", buf);

	//printf_s("Od symbolicznej daty urodzenia Ruryka minê³o: %x\n", st);
	//tm = time(78);

	//time_t sieosiem = 78;
	//time(&sieosiem);
	//printf_s("Wpisalem 78, wyswietla siê wynik time(78): %ld\n",
	//	sieosiem);

	system("pause");
	return 0;
}