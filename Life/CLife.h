#pragma once


#define SIZEY 20
#define SIZEX 100

class CLife {
public:
	CLife();
	~CLife();
	void calcNextGen();
	void calcRandomArray(float percent);
	void printCurrGen();

private:
	char currgen[SIZEY][SIZEX];
	char nextgen[SIZEY][SIZEX];

	char calcZufallZelle(float percent);
};

