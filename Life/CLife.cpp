#include "CLife.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

CLife::CLife() {
	clearAll();
	srand(time(NULL)); // Zufalls Init
}
CLife::~CLife() {

}

void CLife::calcNextGen() {
	int nachbarn = 0;

	for (int y = 0; y < sizey; y++) {
		for (int x = 0; x < sizex; x++) {
			// Nachbarn für jederes Feld berechnen
			nachbarn = 0;
			if (y > 0 && x > 0) { // oben links
				if (currgen[y - 1][x - 1] == '*') nachbarn++;
			}
			if (y > 0) { // oben mitte
				if (currgen[y - 1][x] == '*') nachbarn++;
			}
			if (y > 0 && x < sizex-1) { // oben rechts
				if (currgen[y - 1][x + 1] == '*') nachbarn++;
			}
			if (x > 0) { // mitte links
				if (currgen[y][x - 1] == '*') nachbarn++;
			}
			if (x < sizex-1) { // mitte rechts
				if (currgen[y][x + 1] == '*') nachbarn++;
			}
			if (y < sizey-1 && x > 0) { // unten links
				if (currgen[y + 1][x - 1] == '*') nachbarn++;
			}
			if (y < sizey-1) { // unten mitte
				if (currgen[y + 1][x] == '*') nachbarn++;
			}
			if (y < sizey-1 && x < sizex-1) { // unten rechts
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
	for (int y = 0; y < sizey; y++) {
		for (int x = 0; x < sizex; x++) {
			currgen[y][x] = nextgen[y][x];
			nextgen[y][x] = 0;
		}
	}
}
void CLife::calcRandomArray(float percent) {
	for (int y = 0; y < sizey; y++) {
		for (int x = 0; x < sizex; x++) {
			currgen[y][x] = calcZufallZelle(percent);
		}
	}
}
void CLife::printCurrGen() {
	printf(" ------------------------------------------------------------------------------------------------------\n");
	for (int y = 0; y < sizey; y++) {
		printf(" |");
		for (int x = 0; x < sizex; x++) {
			printf("%c", currgen[y][x]);
		}
		printf("|\n");
	}
	printf(" ------------------------------------------------------------------------------------------------------\n");
}

bool CLife::saveGen(char filename[]) {
	try {
		FILE* fp;

		fopen_s(&fp, filename, "wt");
		if (fp == 0) throw 0; // Open Error handling

		for (int y = 0; y < sizey; y++) {
			for (int x = 0; x < sizex; x++) {
				fprintf(fp, "%c", currgen[y][x]);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
	} catch (...) {
		return false;
	}
	return true;
}
bool CLife::loadGen(char filename[]) {
	try {
		FILE* fp;
		char curr = '.';
		int x;

		fopen_s(&fp, filename, "rt");
		if (fp == 0) throw 0; // Open Error handling

		clearAll();
		rewind(fp); // Filepointer an Anfang setzen

		for (int y = 0; y < sizey; y++) {
			x = 0;
			while ((curr = fgetc(fp)) != EOF) {
				if (curr == '\n') break;
				if (x < sizex) {
					currgen[y][x] = curr;
					x += 1;
				}
			}
		}
		fclose(fp);
	} catch (...) {
		return false;
	}
	return true;
}

bool CLife::isCellAlive(int x, int y) {
	if (currgen[y][x] == '*') {
		return true;
	}
	return false;
}

void CLife::CellKill(int x, int y) {
	currgen[y][x] = ' ';
}

void CLife::CellBeleben(int x, int y) {
	currgen[y][x] = '*';
}


char CLife::calcZufallZelle(float percent) {
	if (rand() >= 32767 * (percent / 100)) {
		return ' ';
	}
	return '*';
}
void CLife::clearAll() {
	for (int y = 0; y < sizey; y++) {
		for (int x = 0; x < sizex; x++) {
			currgen[y][x] = NULL;
			nextgen[y][x] = NULL;
		}
	}
}