#include "CUserInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>

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
	int fileloop = 1;

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
				fileloop = 1;

				system("cls");
				printf("\033[93mHinweis:\033[0m Wenn das aktuelle Array gr\224\341er ist als das gespeicherte entstehen Leerstellen\nVorhandene Speicherst\204nde: (Mit Pfeiltasten navigieren, ESC - Men\201 verlassen)\n");

				gotoXY(0, curr + 3);
				printf(">");
				gotoXY(0, curr + 3);

				
				while (fileloop) {
					switch (_getch()) {
						case 72:	//pfeil hoch
							if (curr > 1) {
								printf("\33[90m>\33[0m");
								gotoXY(0, (--curr) + 3);
								printf(">");
								gotoXY(0, curr + 3);
							}
							break;
						case 80:	//pfeil runter
							if (curr < 5) {
								printf("\33[90m>\33[0m");
								gotoXY(0, (++curr) + 3);
								printf(">");
								gotoXY(0, curr + 3);
							}
							break;
						case 27:	//ESC
							system("cls");
							fileloop = 0;
							break;
						case 13:	//Enter
							gotoXY(0, 5);
							break;
						default:
							break;
					}
				}
				break;
			default:
				system("cls");
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
