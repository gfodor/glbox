#include "LogFile.h"


LogFile::LogFile() : file("gbox.log", std::ios::out | std::ios::app)
{
	file << "Start" << std::endl;
	file.flush();
}


LogFile::~LogFile()
{
	file << "Closing" << std::endl;
	file.close();
}

void LogFile::log(const char *s)
{
	file << s << std::endl;
	file.flush();
}