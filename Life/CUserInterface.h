#pragma once

#include "CLife.h"

class CUserInterface {
public:
	CUserInterface();
	~CUserInterface();
	void printArray(int generationen, int genpersec);
	void MainMenu();
	void fileselectMenu();
	void editMenu();

private:
	CLife life;
	void gotoXY(int x, int y);
};