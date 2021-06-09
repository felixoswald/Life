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

}

void CUserInterface::MainMenu() {
	int curr = 1;
	int generationen = 0;
	char schrittweise = ' ';
	int genpersec = 0;

	while (1) {
		system("cls");
		printf("\n");
		printf(" ************************************************************\n");
		printf(" *                     Life - Hauptmen\201                     *\n");
		printf(" ************************************************************\n\n");
		printf(" 0 - Programm beenden\n");
		printf(" 1 - Zuf\204lliges Array erstellen\n");
		printf(" 2 - Zuf\204lliges Array mit Prozentangabe erstellen\n");
		printf(" 3 - Speicherst\204nde\n");
		gotoXY(1, 10);

		switch (_getch()) {
			case 48:	// 0 - Programm beenden
				exit(0);
			case 49:	// 1 - Random Array
				fflush(stdin);
				life.calcRandomArray(25);
				system("cls");

				printf("\n");
				printf(" ************************************************************\n");
				printf(" *                  Life - Zuf\204lliges Array                 *\n");
				printf(" ************************************************************\n\n");
				printf(" Anzahl der Generationen: ");
				cin >> generationen;
				if (!cin.good()) {
					cin.clear();
					printf(" Wert als Integer angeben!\n");
					_getch();
					break;
				}

				//generationen = _getch();
				//printf("%d\n", generationen);
				printf(" Schrittweise Abarbeitung? (J/N): ");
				schrittweise = _getch();
				printf("%c\n", schrittweise);
				if (schrittweise == 'N' || schrittweise == 'n') {
					printf(" \n Generationen pro Sekunde? (int): ");
					genpersec = (int) _getch();
					printf("%d\n", genpersec);
				}

				printArray(generationen, generationen);
				break;
			case 50:	//2
				fflush(stdin);
				break;
			case 51:	//3
				system("cls");
				printf("\033[93mHinweis:\033[0m Wenn das aktuelle Array gr\224\341er ist als das gespeicherte entstehen Leerstellen\nVorhandene Speicherst\204nde: (Mit Pfeiltasten navigieren, ESC - Men\201 verlassen)\n");

				gotoXY(0, curr + 3);
				printf(">");
				gotoXY(0, curr + 3);

				
				while (1) {
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
