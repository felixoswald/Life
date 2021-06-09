#pragma once

#include "CLife.h"

class CUserInterface {
public:
	CUserInterface();
	~CUserInterface();
	void printArray();
	void printMenu();

private:
	CLife life;
};