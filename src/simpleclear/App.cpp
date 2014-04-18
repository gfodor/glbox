#include "App.h"


App::App() : log()
{
}


App::~App()
{
}

void App::init()
{
	using namespace std;

    static const char title[] = "OpenGL SuperBible - Simple Clear";

    sb6::application::init();

    memcpy(info.title, title, sizeof(title));
}

void App::startup()
{
	std::ifstream vertexFile("vertex.glsl");
	std::string vertexGLSL((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());

	std::ifstream fragmentFile("fragment.glsl");
	std::string fragmentGLSL((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());

	renderingProgram = compileShaders(vertexGLSL.c_str(), fragmentGLSL.c_str());
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
}

void App::shutdown()
{
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteProgram(renderingProgram);
}

void App::render(double currentTime)
{
	float r = (float)sin(currentTime) * 0.5f + 0.5f;
	float g = (float)cos(currentTime) * 0.5f + 0.5f;

    const GLfloat red[] = { r, g, 0.0f, 1.0f };

	glPointSize(40.0f);
    glClearBufferfv(GL_COLOR, 0, red);
	glUseProgram(renderingProgram);
	glDrawArrays(GL_POINTS, 0, 1);
}

GLuint App::compileShaders(const char *vertexShaderSource, const char *fragmentShaderSource)
{
	GLuint vertexShader, fragmentShader, program;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}