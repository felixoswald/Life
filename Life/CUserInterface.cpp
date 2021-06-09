#include "CUserInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

using namespace std;

CUserInterface::CUserInterface() {
}

CUserInterface::~CUserInterface() {

}

void CUserInterface::printArray() {

}

void CUserInterface::printMenu() {
	while (1) {
		printf("0 - Programm beenden\n1 - Array Random erstellen\n2 - Array mit Prozentangabe Random erstellen\n3 - Speicherst\204nde\n");
		switch (_getch()) {
			case 48:	//0
				exit(0);
			case 49:	//1
				fflush(stdin);
				life.calcRandomArray(25);
				system("cls");
				life.printCurrGen();
				printf("--------------------------------------------------------------------------------------------------------------------\n");
				life.calcNextGen();
				life.printCurrGen();
				break;
			case 50:	//2
				fflush(stdin);
				break;
			case 51:	//3
				system("cls");
				printf("\033[93mHinweis:\033[0m Wenn das aktuelle Array gr\224\341er ist als das gespeicherte entstehen Leerstellen\nVorhandene Speicherst\204nde: (Mit Pfeiltasten navigieren, ESC - Men\201 verlassen)\n");

				break;
			default:
				system("cls");
				break;
		}
	}
}
