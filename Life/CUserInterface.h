#pragma once

#include "CLife.h"
#include <string>

class CUserInterface {
public:
	CUserInterface();
	~CUserInterface();
	void printArray(int generationen, int genpersec);
	void MainMenu();
	void fileselectMenu();
	void editMenu(char filename[]);

private:
	CLife life;
	void gotoXY(int x, int y);
	void printHeader(std::string menuname, bool cls);
};