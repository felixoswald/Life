#include "CUserInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "dirent.h"

using namespace std;

CUserInterface::CUserInterface() {
}

CUserInterface::~CUserInterface() {

}

void CUserInterface::printArray(int generationen, int genpersec) {
	printf(" \n Gen: %d\n Gen per Sec: %d\n", generationen, genpersec);

	for (int currgen = 1; currgen <= generationen; currgen++) {
		system("cls");
		printf("\n");
		printf(" ************************************************************\n");
		printf("                 Life - Generation %d von %d                \n", currgen, generationen);
		printf(" ************************************************************\n\n");
		if (genpersec == 0) printf(" [ENTER] n\204chste Generation\n\n");

		life.printCurrGen();
		life.calcNextGen();

		if (genpersec == 0) { // schrittweise
			_getch();
		} else {
			Sleep((1000 / genpersec));
		}
	}

}

void CUserInterface::MainMenu() {
	int curr= 1;
	int generationen;
	char schrittweise;
	int genpersec;
	int prozent;

	while (1) {
		generationen = -1;
		schrittweise = '.';
		genpersec = -1;
		prozent = -1;

		system("cls");
		printf("\n");
		printf(" ************************************************************\n");
		printf("                       Life - Hauptmen\201                     \n");
		printf(" ************************************************************\n\n");
		printf(" 0 - Programm beenden\n");
		printf(" 1 - Zuf\204lliges Array erstellen\n");
		printf(" 2 - Speicherst\204nde\n");
		gotoXY(1, 10);

		switch (_getch()) {
			case 48:	// 0 - Programm beenden
				exit(0);
				break;
			case 49:	// 1 - Random Array
				system("cls");

				printf("\n");
				printf(" ************************************************************\n");
				printf("                    Life - Zuf\204lliges Array                 \n");
				printf(" ************************************************************\n\n");
				
				printf(" Anzahl der Generationen: \t  ");
				if (!(cin >> generationen)) {
					printf(" Wert als Integer angeben!\n");
					cin.clear();
					cin.ignore(1000000, '\n');
					_getch();
					break;
				}

				printf(" Prozentsatz lebende Zellen: \t  ");
				if (!(cin >> prozent) || prozent > 100 || prozent < 0) {
					printf(" Wert als Integer 0..100 angeben!\n");
					cin.clear();
					cin.ignore(1000000, '\n');
					_getch();
					break;
				}

				printf(" Schrittweise Abarbeitung? (J/N): ");
				if (!(cin >> schrittweise)) {
					printf(" Nur J oder N angeben!\n");
					cin.clear();
					cin.ignore(1000000, '\n');
					_getch();
					break;
				} else if (schrittweise == 'N' || schrittweise == 'n') {
					printf(" Generationen pro Sekunde? (int): ");
					if (!(cin >> genpersec) || genpersec <= 0) {
						printf(" Wert als Integer > 0 angeben!\n");
						cin.clear();
						cin.ignore(1000000, '\n');
						_getch();
						break;
					}
				} else if (schrittweise == 'J' || schrittweise == 'j') {
					genpersec = 0;
				} else {
					cin.clear();
					cin.ignore(1000000, '\n');
					printf(" Nur J oder N angeben!\n");
					_getch();
					break;
				}

				life.calcRandomArray(prozent);
				printArray(generationen, genpersec);

				printf(" \n Ende erreicht. Beliebige Taste um ins Hauptmen\201 zu kommen. ");
				_getch();
				break;
			case 50:	//2
				fileselectMenu();
				break;
			default:
				system("cls");
				break;
		}
	}
}

void CUserInterface::fileselectMenu() {
	bool loop = true;
	int auswahl = 0;
	int auswahl_offset = 11;
	int counter = 0;

	system("cls");
	printf("\n");
	printf(" ************************************************************\n");
	printf("                    Life - Speicherst\204nde                  \n");
	printf(" ************************************************************\n\n");
	printf(" [PFEILTASTEN]\tCursor bewegen\n [ENTER]\tDatei laden\n [N] \t\tNeue Datei anlegen\n [E] \t\tDatei bearbeiten\n [ESC]\t\tzur\201ck zum Hauptmen\201\n\n");

	DIR* dir;
	struct dirent* ent;
	string ext = ".cfg";
	string filename = "";

	if ((dir = opendir(".")) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			filename = ent->d_name;
			if (filename.find(ext) != string::npos) {
				printf(" > %s\n", ent->d_name);
				counter++;
			}
		}
		closedir(dir);
	} else {
		printf(" Fehler beim Lesen der Dateien!\n");
	}

	if (counter > 0) {
		gotoXY(1, auswahl_offset);
		while (loop) {
			switch (_getch()) {
				case 72:	//pfeil hoch
					if (auswahl > 0) {
						printf("\33[90m>\33[0m");
						gotoXY(1, (--auswahl) + auswahl_offset);
						printf(">");
						gotoXY(1, auswahl + auswahl_offset);
					}
					break;
				case 80:	//pfeil runter
					if (auswahl < counter -1) {
						printf("\33[90m>\33[0m");
						gotoXY(1, (++auswahl) + auswahl_offset);
						printf(">");
						gotoXY(1, auswahl + auswahl_offset);
					}
					break;
				case 27:	//ESC
					system("cls");
					loop = false;
					break;
				case 13:	//Enter
					//gotoXY(0, 5);
					life.calcRandomArray(50);
					editMenu();
					break;
				default:
					break;
			}
		}
	} else {
		printf(" Es wurden keine Speicherstände gefunden.\n");
	}
}

void CUserInterface::editMenu() {
	system("cls");
	printf("\n");
	printf(" ************************************************************\n");
	printf("                      Life - Bearbeitung                      \n");
	printf(" ************************************************************\n\n");
	printf(" [PFEILTASTEN]\t Cursor bewegen\n [ENTER]\t Zustand Zelle umschalten\n [ESC]\t\t Bearbeitung beenden\n\n");

	life.printCurrGen();

	const int x_offset = 2;
	const int y_offset = 10;
	int x = 0;
	int y = 0;
	bool loop = true;


	gotoXY(x_offset, y_offset);

	while (loop) {
		switch (_getch()) {
			case 72:	//pfeil hoch
				if (y > 0) {
					y--;
					gotoXY(x + x_offset, y + y_offset);
				}
				break;
			case 80:	//pfeil runter
				if (y < 19) {
					y++;
					gotoXY(x + x_offset, y + y_offset);
				}
				break;
			case 75:	//pfeil links
				if (x > 0) {
					x--;
					gotoXY(x + x_offset, y + y_offset);
				}
				break;
			case 77:	//pfeil rechts
				if (x < 99) {
					x++;
					gotoXY(x + x_offset, y + y_offset);
				}
				break;
			case 27:	//ESC
				system("cls");
				printf("\n");
				printf(" ************************************************************\n");
				printf("                      Life - Bearbeitung                      \n");
				printf(" ************************************************************\n\n");
				printf(" Sollen die Änderungen in %s gespeichert werden?\n", "Test");
				printf(" [ENTER]\tSpeichern & zur Dateiauswahl\n");
				printf(" [ESC]\tohne Speichern beenden\n");
				switch (_getch()) {
					case 27: // ESC
						fileselectMenu();
						break;
					case 13: // ENTER
						// Speichern
						life.saveGen((char*) "test.cfg");
						fileselectMenu();
						break;
				}
				loop = false;
				break;
			case 13:	//Enter
				if (life.isCellAlive(x, y)) {
					life.CellKill(x, y);
					printf(" ");
				} else {
					life.CellBeleben(x, y);
					printf("*");
				}
				gotoXY(x + x_offset, y + y_offset);
				break;
			default:
				break;
		}
	}

}

void CUserInterface::gotoXY(int x, int y) {
	HANDLE  hConsoleOutput; COORD koords;
	koords.X = x; koords.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, koords);
}
