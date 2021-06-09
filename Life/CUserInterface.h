#pragma once

#include "CLife.h"

class CUserInterface {
public:
	CUserInterface();
	~CUserInterface();
	void printArray(int generationen, int genpersec);
	void MainMenu();

private:
	CLife life;
	void gotoXY(int x, int y);
};