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

void CUserInterface::printArray(int generationen = -1, int genpersec = -1) {
	char schrittweise = ' ';

	while (generationen == -1) {
		printf(" Anzahl der Generationen: \t  ");
		if (!(cin >> generationen)) {
			printf(" Wert als Integer angeben!\n");
			generationen = -1;
			cin.clear();
			cin.ignore(1000000, '\n');
		}
	}

	while (schrittweise == ' ') {
		printf(" Schrittweise Abarbeitung? (J/N): ");
		if (!(cin >> schrittweise)) {
			printf(" Nur J oder N angeben!\n");
			schrittweise = ' ';
			cin.clear();
			cin.ignore(1000000, '\n');
		} else if (schrittweise == 'N' || schrittweise == 'n') {
			while (genpersec == -1) {
				printf(" Generationen pro Sekunde? (int): ");
				if (!(cin >> genpersec) || genpersec <= 0) {
					printf(" Wert als Integer > 0 angeben!\n");
					genpersec = -1;
					cin.clear();
					cin.ignore(1000000, '\n');
				}
			}
		} else if (schrittweise == 'J' || schrittweise == 'j') {
			genpersec = 0;
		} else {
			schrittweise = ' ';
			cin.clear();
			cin.ignore(1000000, '\n');
			printf(" Nur J oder N angeben!\n");
		}
	}

	for (int currgen = 1; currgen <= generationen; currgen++) {
		printHeader("Generation " + to_string(currgen) + " von " + to_string(generationen), true);
		if (genpersec == 0) printf(" [ENTER] n\204chste Generation\n\n");

		life.printCurrGen();
		life.calcNextGen();

		if (genpersec == 0) { // schrittweise
			_getch();
		} else {
			Sleep((1000 / genpersec));
		}
	}

	printf(" \n Ende erreicht. Beliebige Taste um zur\201ck ins Men\201 zu kommen. ");
	_getch();
}

void CUserInterface::MainMenu() {
	int prozent;

	while (1) {
		prozent = -1;

		printHeader((string)"Hauptmen\201", true);
		printf(" 0 - Programm beenden\n");
		printf(" 1 - Zuf\204lliges Array erstellen\n");
		printf(" 2 - Speicherst\204nde\n");
		gotoXY(1, 10);

		switch (_getch()) {
			case 48:	// 0 - Programm beenden
				exit(0);
				break;
			case 49:	// 1 - Random Array
				printHeader((string)"Zuf\204lliges Array", true);
				printf(" Prozentsatz lebende Zellen: \t  ");

				if (!(cin >> prozent) || prozent > 100 || prozent < 0) {
					printf(" Wert als Integer 0..100 angeben!\n");
					cin.clear();
					cin.ignore(1000000, '\n');
					_getch();
					break;
				}
				life.calcRandomArray(prozent);
				printArray();
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
	bool loop = true, loop2;
	int auswahl = 0;
	const int auswahl_offset = 12;
	int counter = 0;

	while (loop) {
		auswahl = counter = 0;
		loop2 = true;

		printHeader((string)"Speicherst\204nde", true);
		printf(" [^][v]\t\tCursor bewegen\n [ENTER]\tDatei laden\n [N] \t\tNeue Datei anlegen\n [E] \t\tDatei bearbeiten\n [D] \t\tDatei l\224schen\n [ESC]\t\tzur\201ck zum Hauptmen\201\n\n");

		DIR* dir;
		struct dirent* ent;
		const string ext = ".cfg";
		string filename = "";
		string dateien[100];

		if ((dir = opendir(".")) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				if (counter < 100) {
					filename = ent->d_name;
					if (filename.find(ext) != string::npos) {
						dateien[counter] = (string)ent->d_name;
						if (counter == 0) {
							printf(" > %s\n", dateien[counter].data());
						} else {
							printf(" \33[90m>\33[0m %s\n", dateien[counter].data());
						}
						counter++;
					}
				} else {
					printf(" FEHLER! Maximale Dateianzahl liegt bei 100. \n");
				}
			}
			closedir(dir);
		} else {
			printf(" Fehler beim Lesen der Dateien!\n");
		}

		if (counter > 0) {
			gotoXY(1, auswahl_offset);

			while (loop2) {
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
						loop2 = false;
						break;
					case 13:	//Enter
						printHeader("Speicherst\204nde", true);

						if (life.loadGen((char*)dateien[auswahl].data())) {
							printArray();
						} else {
							system("cls");
							printf(" Fehler beim Laden der Datei!");
							_getch();
						}
						loop2 = false;
						break;
					case 110: // N
					
						break;
					case 100: // D
						if (remove((char*)dateien[auswahl].data()) == 0) {
							printHeader("Speicherst\204nde", true);
							printf(" Datei gel\224scht!\n ");
							_getch();
						} else {
							printHeader("Speicherst\204nde", true);
							printf(" Datei konnte nicht gel\224scht werden!\n ");
							_getch();
						}
						loop2 = false;
						break;
					case 101: // E
						printf("%s \n", dateien[auswahl].data());
						if (life.loadGen((char*)dateien[auswahl].data())) {
							editMenu((char*)dateien[auswahl].data());
						} else {
							printf(" Fehler beim Laden der Datei!");
						}
						loop2 = false;
						break;
					default:
						//printf("%d", _getch());
						break;
				}
			}
		} else {
			printf(" Es wurden keine Speicherst\204nde gefunden.\n");
		}
	}
}

void CUserInterface::editMenu(char filename[]) {
	printHeader("Bearbeitung", true);
	printf(" [^][v][<][>]\t Cursor bewegen\n [ENTER]\t Zustand Zelle umschalten\n [ESC]\t\t Bearbeitung beenden\n\n");

	life.printCurrGen();

	const int x_offset = 2;
	const int y_offset = 10;
	int x = 0;
	int y = 0;
	bool loop = true;
	string newfilename;
	const string ext = ".cfg";


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
				printHeader("Bearbeitung", true);
				printf(" Sollen die \216nderungen in %s gespeichert werden?\n", filename);
				printf(" [ENTER]\tSpeichern & zur Dateiauswahl\n");
				printf(" [N]\t\tSpeichern unter neuem Dateinamen\n");
				printf(" [ESC]\t\tohne Speichern beenden\n ");
				switch (_getch()) {
					case 27: // ESC
						//fileselectMenu();
						loop = false;
						break;
					case 110: // N
						printHeader("Bearbeitung", true);
						printf(" Dateiname (ohne Erweiterung): ");
						if (!(cin >> newfilename)) {
							printf(" Fehler bei Eingabe, Datei wurde nicht gespeichert!\n");
							cin.clear();
							cin.ignore(1000000, '\n');
						} else {
							life.saveGen((char*)newfilename.append(ext).data());
						}
						loop = false;
						break;
					case 13: // ENTER
						// Speichern
						life.saveGen(filename);
						loop = false;
						break;
				}
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

void CUserInterface::printHeader(std::string menuname, bool cls) {
	if (cls) system("cls");
	printf("\n");
	printf(" ************************************************************\n");
	printf("  Life Game - %s\n", menuname.data());
	printf(" ************************************************************\n\n");
}
