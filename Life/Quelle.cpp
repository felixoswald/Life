#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "CLife.h"
#include "CFileHandler.h"
#include "CUserInterface.h"

using namespace std;


int main() {
	CUserInterface ui;
	ui.printMenu();

	printf("Testausgabe :) \n");


	return 0;
}