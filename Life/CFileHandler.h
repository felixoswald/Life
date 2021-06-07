#pragma once
#include <stdio.h>

class CFileHandler {
public:
	CFileHandler();
	~CFileHandler();
	bool FileWriteContent(char* filename, char* content);
private:
	bool FileExisits(char* filename);
	FILE* f;
};

