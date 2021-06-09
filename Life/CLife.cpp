#include "CLife.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

CLife::CLife() {
	for (int y = 0; y < SIZEY; y++) {
		for (int x = 0; x < SIZEX; x++) {
			currgen[y][x] = NULL;
			nextgen[y][x] = NULL;
		}
	}

	// Zufalls Init
	srand(time(NULL));
}
CLife::~CLife() {

}

void CLife::calcNextGen() {
	int nachbarn = 0;

	for (int y = 0; y < SIZEY; y++) {
		for (int x = 0; x < SIZEX; x++) {
			// Nachbarn für jederes Feld berechnen
			nachbarn = 0;
			if (y > 0 && x > 0) { // oben links
				if (currgen[y - 1][x - 1] == '*') nachbarn++;
			}
			if (y > 0) { // oben mitte
				if (currgen[y - 1][x] == '*') nachbarn++;
			}
			if (y > 0 && x < SIZEX) { // oben rechts
				if (currgen[y - 1][x + 1] == '*') nachbarn++;
			}
			if (x > 0) { // mitte links
				if (currgen[y][x - 1] == '*') nachbarn++;
			}
			if (x < SIZEX) { // mitte rechts
				if (currgen[y][x + 1] == '*') nachbarn++;
			}
			if (y < SIZEY && x > 0) { // unten links
				if (currgen[y + 1][x - 1] == '*') nachbarn++;
			}
			if (y < SIZEY) { // unten mitte
				if (currgen[y + 1][x] == '*') nachbarn++;
			}
			if (y < SIZEY && x < SIZEX) { // unten rechts
				if (currgen[y + 1][x + 1] == '*') nachbarn++;
			}
			
			// neuen Zustand ermitteln
			if (currgen[y][x] == '*' && (nachbarn == 0 || nachbarn == 1 || nachbarn > 3)) { // Zelle stribt wegen Überbevölkerung
				nextgen[y][x] = ' ';
			} else if (currgen[y][x] == '*' && (nachbarn == 2 || nachbarn == 3)) { // Zelle überlebt
				nextgen[y][x] = '*';
			} else if (currgen[y][x] == ' ' && nachbarn == 3) { // tote Zelle wird wiederbelebt
				nextgen[y][x] = '*';
			} else { // tote Zelle bleibt tot
				nextgen[y][x] = ' ';
			}
		}
	}

	// Kopiere nextgen -> currgen
	for (int y = 0; y < SIZEY; y++) {
		for (int x = 0; x < SIZEX; x++) {
			currgen[y][x] = nextgen[y][x];
			nextgen[y][x] = 0;
		}
	}
}
void CLife::calcRandomArray(float percent) {
	for (int y = 0; y < SIZEY; y++) {
		for (int x = 0; x < SIZEX; x++) {
			currgen[y][x] = calcZufallZelle(percent);
		}
	}
}
void CLife::printCurrGen() {
	for (int y = 0; y < SIZEY; y++) {
		for (int x = 0; x < SIZEX; x++) {
			printf("%c", currgen[y][x]);
		}
		printf("\n");
	}
}


char CLife::calcZufallZelle(float percent) {
	if (rand() >= 32767 * (percent / 100)) {
		return ' ';
	}
	return '*';
}