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
	bool saveGen(char filename[]);
	bool loadGen(char filename[]);

private:
	char currgen[SIZEY][SIZEX];
	char nextgen[SIZEY][SIZEX];

	char calcZufallZelle(float percent);
	void clearAll();
};

