#pragma once

class CLife {
public:
	CLife();
	~CLife();
	void calcNextGen();
	void calcRandomArray(float percent);
	void printCurrGen();
	bool saveGen(char filename[]);
	bool loadGen(char filename[]);
	bool isCellAlive(int x, int y);
	void CellKill(int x, int y);
	void CellBeleben(int x, int y);

private:
	int sizex = 100;
	int sizey = 20;
	char currgen[20][100];
	char nextgen[20][100];

	char calcZufallZelle(float percent);
	void clearAll();
};

