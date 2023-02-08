#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>
using namespace std;

HANDLE hOut; //potrzebne do zmiany koloru czcionki

string sprawdzenieWpisanych(string wiersz, string kolumna, string cyfra, int domyslneWartosci[9][9]) {	//sprawdza czy wartosci podane podczas wczytywania cyfr do tablicy "plansza" s� akceptowalne
	int wartosc_wiersz{}, wartosc_kolumna{}, wartosc_cyfra{};
	wartosc_wiersz = atoi(wiersz.c_str());
	wartosc_kolumna = atoi(kolumna.c_str());
	wartosc_cyfra = atoi(cyfra.c_str());
	if (cyfra.length() > 1 || wiersz.length() > 1 || kolumna.length() > 1) {
		return "bledne wartosci";
	}
	else {
		if (wartosc_cyfra < 0 || wartosc_cyfra > 9 || wartosc_wiersz < 1 || wartosc_wiersz > 9 || wartosc_kolumna < 1 || wartosc_kolumna > 9) //wiersze, kolumny i cyfry s� wpisywane z przedzia�u 1-9
			return "bledne wartosci";
		else if (domyslneWartosci[wartosc_wiersz - 1][wartosc_kolumna - 1] != 0)	//nie mo�na zast�powa� domy�lnych warto�ci
			return "domyslne wartosci";
		else
			return "mozna wpisac";
	}
}

void wyswietlanie(int plansza[9][9], int domyslneWartosci[9][9], int zle[9][9]) {	//wy�wietla aktualn� plansz� - tablic� "plansza"
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);											//potrzebne do zmniay koloru czcionki
	int color{};
	cout << "Twoja plansza sudoku: " << endl;
	SetConsoleTextAttribute(hOut, 2);												//zmiana koloru czcionki na zielony - numery kolumn
	cout << "     1 2 3   4 5 6   7 8 9" << endl;
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED); //zmiana koloru z powrotem na czarny
	cout << "   ";
	for (int k = 0; k < 25; k++)
		cout << "-";
	cout << endl;
	for (int i = 0; i < 9; i++) {
		cout << " ";
		SetConsoleTextAttribute(hOut, 2);											//zmiana koloru czcionki na zielony - numery wierszy
		cout << i + 1 << " ";
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "| ";
		for (int j = 0; j < 9; j++) {
			if (domyslneWartosci[i][j] != 0) {										//jesli wartosc w tablicy "plansza" na pozycji [i][j] jest domyslnie wpisana - nie mo�na nic wpisa�
				if (j == 3 || j == 6) {
					cout << left << "| ";
				}
				cout.width(2);
				if (plansza[i][j] == 0)
					cout << left << " ";
				else {
					color = 3;														// 3 - niebieski kolor czcionki - domy�lnie wpisane warto�ci
					SetConsoleTextAttribute(hOut, 3);
					cout << left << plansza[i][j];
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
			}
			else {																	//jesli wartosc w tablicy "plansza" na pozycji [i][j] nie jest domy�lnie wpisana - mo�e zosta� wprowadzona przez u�ytkownika
				if (j == 3 || j == 6) {
					cout << left << "| ";
				}
				cout.width(2);
				if (plansza[i][j] == 0)
					cout << left << " ";
				else {
					if (zle[i][j] == 0) {											//je�li w tablicy ze z�ymi odpowiedziami "zle" na pozycji [i][j] jest 0 - brak z�ej odpowiedzi lub nie zosta�a sprawdzona plansza
						cout << left << plansza[i][j];
					}
					else {															//je�li w tablicy ze z�ymi odpowiedziami "zle" na pozycji [i][j] jest 1 - b��dna warto�� w planszy - kolor czerowny czcionki
						color = 4;													// 4 - czerwony kolor czcionki po sprawdzeniu - b��dna warto��
						SetConsoleTextAttribute(hOut, color);
						cout << left << plansza[i][j];
						SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
					}
				}
			}
		}
		cout << "|";
		cout << endl;
		if (i == 2 || i == 5 || i == 8) {
			cout << " ";
			cout << " ";
			cout << " ";
			for (int k = 0; k < 25; k++)
				cout << "-";
			cout << endl;
		}

	}
}

int zliczaniePustych(int plansza[9][9]) {											//zlicza ile p�l w planszy - tablica "plansza" - nie ma wpisanej warto�ci tzn. ma warto�� 0
	int ile_pustych{};
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (plansza[i][j] == 0)
				ile_pustych++;
		}
	}
	return ile_pustych;
}

void uzupelnianie(int plansza[9][9], int domyslneWartosci[9][9], int zle[9][9]) {	//wpisuje podan� cyfr� w podane pole w tablicy "plansza" pod warunkiem spe�nienia odpowiednich kryteri�w
	string wiersz{}, kolumna{}, cyfra{};
	while (zliczaniePustych(plansza) > 0) {
		system("cls");
		wyswietlanie(plansza, domyslneWartosci, zle);
		cout << endl;
		cout << "Podaj numer wiersza i kolumny oraz liczbe: ";
		cin >> wiersz >> kolumna >> cyfra;

		int wartosc_wiersz{}, wartosc_kolumna{}, wartosc_cyfra{};
		wartosc_wiersz = atoi(wiersz.c_str());
		wartosc_kolumna = atoi(kolumna.c_str());
		wartosc_cyfra = atoi(cyfra.c_str());

		string czy_mozna_wpisac{};
		czy_mozna_wpisac = sprawdzenieWpisanych(wiersz, kolumna, cyfra, domyslneWartosci);	//podaje warto�ci wpisane przez u�ytkownika do funkcji sprawdzaj�cej ich poprawno�� zgodnie z mo�liwymi do wpisania do planszy warto�ciami

		if (czy_mozna_wpisac == "mozna wpisac") {
			plansza[wartosc_wiersz - 1][wartosc_kolumna - 1] = wartosc_cyfra;
		}
		else if (czy_mozna_wpisac == "bledne wartosci") {
			cout << "Prosze podac wlasciwe wartosci" << endl;
			Sleep(2000);
		}
		else if (czy_mozna_wpisac == "domyslne wartosci") {
			cout << "Nie mozesz zmieniac cyfr podanych domyslnie." << endl;
			Sleep(2000);
		}
	}
}

int sprawdzenieSudoku(int plansza[9][9], int rozwiazanie[9][9], int zle[9][9]) { //sprawdza kt�re pola s� �le uzupe�nione, zwraca ile jest takich p�l oraz zamienia odpowiednie 
																				 //pola w tablicy "zle" na 1 je�li warto�� w tablicy "plansza" podana przez u�ytkownika jest b��dna
	int ile_zlych{};
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (plansza[i][j] != rozwiazanie[i][j]) {
				zle[i][j]++;
				ile_zlych++;
			}
		}
	}
	return ile_zlych;
}

void usuniecieZlych(int plansza[9][9], int zle[9][9]) {							//usuwa b��dne cyfry w polach, kt�re na tej samej pozycji w tablicy "zle" maj� warto�� 1, czyli maj� b��dn� warto��, zeruje tablic� "zle"
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (zle[i][j] == 1) {
				plansza[i][j] = 0;
				zle[i][j] = 0;
			}
		}
	}
}

bool czyTak(string slowo) {														//sprawdza czy podanie s�owo jest jednym mo�liwych opcji
	if (slowo.length() == 3)										//3 znaki
		if (slowo[0] == 84 || slowo[0] == 116)						//t lub T
			if (slowo[1] == 65 || slowo[1] == 97)					//a lub A
				if (slowo[2] == 75 || slowo[2] == 107)				//k lub K
					return true;
	return false;
}

bool czyNie(string slowo) {
	if (slowo.length() == 3)										//3 znaki
		if (slowo[0] == 78 || slowo[0] == 110)						//n lub N
			if (slowo[1] == 73 || slowo[1] == 105)					//i lub I
				if (slowo[2] == 69 || slowo[2] == 101)				//e lub E
					return true;
	return false;
}

int main() {
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);							//potrzebne do zmiany koloru czcionki
	string menu{};
	while (menu != "4") {											//p�tla obraca si� dop�ki u�ytkownik nie chce wyj�� z programu
		system("cls");
		SetConsoleTextAttribute(hOut, 10);							//zmiana koloru na jasnozielony
		cout << ".:SUDOKU:." << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "Witaj w grze Sudoku" << endl;						//pocz�tek menu
		cout << "1. Graj" << endl;
		cout << "2. Zasady" << endl;
		cout << "3. Autor" << endl;
		cout << "4. Wyjdz" << endl;									//koniec menu
		cout << endl << "Wybierz opcje ";
		cin >> menu;

		int wartosc_menu{};											//sprawdzanie poprawno�ci warto�ci zmiennej menu
		wartosc_menu = atoi(menu.c_str());
		if (menu.length() > 1 || wartosc_menu < 1 || wartosc_menu > 4) {//je�li b��dna warto�� to kolejny obr�t p�tli while
			cout << "Prosze podac prawidlowa wartosc.";
			Sleep(2000);
			continue;
		}

		switch (wartosc_menu) {
		case 1: {													//wybrano opcj� nowej gry
			string poziom{};
			bool czy_dobry_poziom = false;
			int wartosc_poziom{};
			while (!czy_dobry_poziom) {
				system("cls");
				cout << "Poziomy:" << endl;
				cout << "1. Latwy" << endl;
				cout << "2. Sredni" << endl;
				cout << "3. Trudny" << endl << endl;
				cout << "Wybierz poziom trudnosci: ";
				cin >> poziom;
				cout << endl;

				wartosc_poziom = atoi(poziom.c_str());				//sprawdzanie poprawno�ci warto�ci zmiennej poziom
				if (poziom.length() > 1 || wartosc_poziom < 1 || wartosc_poziom > 3) {
					cout << "Prosze podac prawidlowa wartosc.";
					czy_dobry_poziom = false;
					Sleep(2000);
					continue;
				}
				else {
					czy_dobry_poziom = true;
				}
			}
			string poziom_plik_nazwa, rozwiazanie_plik_nazwa;		//wczytywanie do zmiennych nazw plik�w, odpowiedznich do wybranego poziomu
			if (wartosc_poziom == 1) {
				poziom_plik_nazwa = "latwy_sudoku.txt";
				rozwiazanie_plik_nazwa = "latwy_rozwiazanie.txt";
			}
			else if (wartosc_poziom == 2) {
				poziom_plik_nazwa = "sredni_sudoku.txt";
				rozwiazanie_plik_nazwa = "sredni_rozwiazanie.txt";
			}
			else if (wartosc_poziom == 3) {
				poziom_plik_nazwa = "trudny_sudoku.txt";
				rozwiazanie_plik_nazwa = "trudny_rozwiazanie.txt";
			}

			int zle[9][9] = {};										// tablica na b��dne warto�ci w danych polach - domy�lnie wsz�dzie 0

																	//wczytywanie danych z plik�w: pocz�tek
			int plansza[9][9] = {};									//tablica z plansz�
			fstream plik_plansza(poziom_plik_nazwa, ios::in);
			if (plik_plansza.good()) {								//sprawdzenie czy plik sie otworzyl
				for (int i = 0; i < 9; i++) {
					for (int j = 0; j < 9; j++) {
						plik_plansza >> plansza[i][j];
					}
				}
				plik_plansza.close();
			}
			else {
				cout << "Problem z plikiem planszy " << poziom_plik_nazwa <<endl;
				plik_plansza.close();
				Sleep(2000);
				break;
			}
		
			int odpowiedzi[9][9] = {};								//tablica z odpowiedziami
			fstream plik_odpowiedzi(rozwiazanie_plik_nazwa, ios::in);
			if (plik_odpowiedzi.good()) {							//sprawdzenie czy plik sie otworzyl
				for (int i = 0; i < 9; i++) {
					for (int j = 0; j < 9; j++) {
						plik_odpowiedzi >> odpowiedzi[i][j];
					}
				}
				plik_odpowiedzi.close();
			}
			else {
				cout << "Problem z plikiem odpowiedzi " << rozwiazanie_plik_nazwa << endl;
				plik_odpowiedzi.close();
				Sleep(2000);
				break;
			}

			int domyslne_wartosci[9][9] = {};						//tablica z podanymi domy�lnie warto�ciami, kt�rych nie mo�na zmieni�
			fstream plik_domyslne_wartosci(poziom_plik_nazwa, ios::in);
			if (plik_domyslne_wartosci.good()) {					//sprawdzenie czy plik sie otworzyl
				for (int i = 0; i < 9; i++) {
					for (int j = 0; j < 9; j++) {
						plik_domyslne_wartosci >> domyslne_wartosci[i][j];
					}
				}
				plik_domyslne_wartosci.close();
			}
			else {
				cout << "Problem z plikiem domyslnych wartosci " << poziom_plik_nazwa << endl;
				plik_domyslne_wartosci.close();
				Sleep(2000);
				break;
			}														//wczytywanie danych z plik�w: koniec

			int ilosc_bledow{};
			do {
				uzupelnianie(plansza, domyslne_wartosci, zle);		//uzupe�nianie ca�ej planszy

				wyswietlanie(plansza, domyslne_wartosci, zle);		//wczytywanie uzupe�nionej planszy

																	//czy sprawdzenie b��d�w: pocz�tek
				system("cls");
				wyswietlanie(plansza, domyslne_wartosci, zle);
				string czy_sprawdzasz;
				cout << "Czy chcesz sprawdzic swoje rozwiazanie? Wpisz tak lub nie: ";
				do {												//dop�ki nie zostan� wisane poprawne warto�ci
					cin >> czy_sprawdzasz;
					if (!czyTak(czy_sprawdzasz) && !czyNie(czy_sprawdzasz)) {
						cout << "Wpisano bledna wartosc. Wpisz poprawna wartosc: tak lub nie: " << endl;
					}
				} while (!czyTak(czy_sprawdzasz) && !czyNie(czy_sprawdzasz));
																	//czy sprawdzenie b��d�w: koniec

																	//czy poprawa b��d�w: pocz�tek
				string czy_poprawiasz;
				if (czyTak(czy_sprawdzasz)) {
					ilosc_bledow = sprawdzenieSudoku(plansza, odpowiedzi, zle);
					if (ilosc_bledow == 0) {						//plansza uzupe�niona prawid�owo
						system("cls");
						wyswietlanie(plansza, domyslne_wartosci, zle);
						cout << "Gratulacje! Rozwiazales sudoku poprawnie!" << endl;
						Sleep(1000);
						cout << "Wcisnij ENTER aby wrocic do menu." << endl;
						cin.get();
						cin.get();
						continue;
					}
					else {											//plansza b�ednie uzupe�niona
						system("cls");
						wyswietlanie(plansza, domyslne_wartosci, zle);
						if (ilosc_bledow == 1) {					//�eby by�a �adna odmiana
							cout << "Masz " << ilosc_bledow << " blad. " << endl;
						}
						else if (ilosc_bledow > 1 && ilosc_bledow < 5) {
							cout << "Masz " << ilosc_bledow << " bledy. " << endl;
						}
						else
							cout << "Masz " << ilosc_bledow << " bledow. " << endl;
						cout << "Czy chcesz je poprawic ? Wpisz tak lub nie : ";
						do {
							cin >> czy_poprawiasz;
							if (!czyTak(czy_poprawiasz) && !czyNie(czy_poprawiasz)) {
								cout << "Wpisano bledna wartosc. Wpisz poprawna wartosc: tak lub nie: ";
							}
						} while (!czyTak(czy_poprawiasz) && !czyNie(czy_poprawiasz));
					}
																	//czy poprawa b��d�w: koniec

					if (czyTak(czy_poprawiasz)) {
						usuniecieZlych(plansza, zle);				//usuni�cie b��dnych odpowiedzi
					}
					else if (czyNie(czy_poprawiasz)) {
						cout << "Wcisnij ENTER aby wrocic do menu." << endl;
						cin.get();
						cin.get();
						break;
					}
				}
				else {
					cout << "Wcisnij ENTER aby wrocic do menu." << endl;
					cin.get();
					cin.get();
					break;
				}
			} while (ilosc_bledow > 0);
			break;
		}
		case 2: {													//wybrano opcj� zasad, wypisane s� zasady gry oraz instrukcja jak wpisywa� warto�ci, a tak�e legenda kolor�w
			system("cls");
			cout << "Zasady i instrukcja" << endl;
			cout << "Celem gry jest wypelnienie wszystkich pustych komorek cyframi od 1 do 9 w taki sposob, aby kazda cyfra wystepowala tylko raz w kolumnie (pionowo), w wierszu (poziomo) i w bloku (3x3 komorki)." << endl << endl;
			cout << "Wpisywanie cyfr w pola:" << endl;
			cout << "Aby wpisac cyfre w dane pole podaj kolejno: numer wiersza (1-9), numer kolumny (1-9) oraz cyfre (1-9) w formacie:" << endl;
			cout << "wiersz kolumna cyfra" << endl << endl;
			cout << "lub" << endl << endl;
			cout << "wiersz" << endl;
			cout << "kolumna" << endl;
			cout << "cyfra" << endl << endl;
			cout << "Jesli pomylisz sie podczas wpisywania i wpiszesz cyfre w bledne pole, to wpisz w to samo pole cyfre 0 - program uzna to jako usuniecie wartosci w tym polu. Natomiast jesli w dane pole wpiszesz bledna wartosc, wpisz w to samo pole poprawna wartosc." << endl << endl;
			cout << "Domyslnie uzupelnione cyfry sa wyswietlane w kolorze niebieskimm, natomiast cyfry ktore Ty wpiszesz - w kolorze bialym. Bledy sa wyswietlane w kolorze czerwonym. Kolorem zielonym sa oznaczone numery wierszy i kolumn." << endl << endl;
			cout << "Zycze milej gry :)" << endl;
			cout << endl;
			cout << "Wcisnij ENTER aby wrocic do menu." << endl;
			cin.get();
			cin.get();
			break;
		}
		case 3: {													//wybrano opcj� autora
			system("cls");
			cout << "Autorem tego kodu jest Karolina Kamela." << endl;
			Sleep(1000);
			cout << "Wcisnij ENTER aby wrocic do menu." << endl;
			cin.get();
			cin.get();
			break;
		}
		case 4: {													//wybrano opcj� wyj�cia
			system("cls");
			cout << "Czy na pewno chcesz wyjsc? [tak/nie]" << endl;
			string czy_wyjsc;
			cin >> czy_wyjsc;
			while (!czyNie(czy_wyjsc) && !czyTak(czy_wyjsc)) {
				system("cls");
				cout << "Wpisano bledna wartosc. Wpisz poprawna wartosc: tak lub nie: ";
				cin >> czy_wyjsc;
			}
			if (czyNie(czy_wyjsc)) {								//je�li nie wyj�� - powr�t do menu
				cout << "Nastapi powrot do menu gry." << endl;
				menu = {};											//wyzerowanie zmiennej menu �eby p�tla si� nie przerwa�a
				continue;
			}
			else if (czyTak(czy_wyjsc)) {							//je�li wyj�� - koniec obiegu p�tli
				cout << "Program za chwile sie zamknie." << endl;
				Sleep(2000);
				break;
			}
			break; }
		default: {
			cout << "Prosze podac wlasciwa wartosc.";
			Sleep(2000);
			break;
		}
		}

	}
}