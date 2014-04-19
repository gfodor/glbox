#pragma once

#include <sb6.h>
#include "LogFile.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>

class App : public sb6::application
{
	LogFile log;
	GLuint renderingProgram;
	GLuint vertexArray;

public:
	App();
	~App();

	virtual void init() override;
	virtual void startup() override;
	virtual void shutdown() override;
	virtual void render(double) override;
	GLuint compileShaders(const char *vertexShaderSource, const char *tControlShaderSource, const char *tEvalShaderSource, const char *geometryShaderSource, const char *fragmentShaderSource);
};

