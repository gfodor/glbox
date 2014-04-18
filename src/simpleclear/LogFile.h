#pragma once

#include <iostream>
#include <fstream>

class LogFile
{
private:
	std::ofstream file;

public:
	LogFile();
	~LogFile();
	void log(const char *);
};

