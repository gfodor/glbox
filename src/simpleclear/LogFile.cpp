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
