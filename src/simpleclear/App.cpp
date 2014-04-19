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

	std::ifstream tControlFile("tcontrol.glsl");
	std::string tControlGLSL((std::istreambuf_iterator<char>(tControlFile)), std::istreambuf_iterator<char>());

	std::ifstream tEvalFile("teval.glsl");
	std::string tEvalGLSL((std::istreambuf_iterator<char>(tEvalFile)), std::istreambuf_iterator<char>());

	std::ifstream geometryFile("geometry.glsl");
	std::string geometryGLSL((std::istreambuf_iterator<char>(geometryFile)), std::istreambuf_iterator<char>());

	std::ifstream fragmentFile("fragment.glsl");
	std::string fragmentGLSL((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());

	renderingProgram = compileShaders(vertexGLSL.c_str(), tControlGLSL.c_str(), tEvalGLSL.c_str(), geometryGLSL.c_str(), fragmentGLSL.c_str());
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glPointSize(5.0);
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

    const GLfloat red[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat attrib[] = { (float)sin(currentTime) * 0.5f, (float)cos(currentTime) * 0.6f, 0.0f, 0.0f };
	GLfloat colorAttrib[] = { 1.0f, 0.5f, 0.0f, 0.0f };

    glClearBufferfv(GL_COLOR, 0, red);

	glUseProgram(renderingProgram);

	glVertexAttrib4fv(16, attrib);
	glVertexAttrib4fv(17, colorAttrib);
	glDrawArrays(GL_PATCHES, 0, 3);
}

GLuint App::compileShaders(const char *vertexShaderSource, const char *tControlShaderSource, 
	                       const char *tEvalShaderSource, const char *geometryShaderSource, 
						   const char *fragmentShaderSource)
{
	GLuint vertexShader, fragmentShader, tControlShader, tEvalShader, geometryShader, program;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	tControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(tControlShader, 1, &tControlShaderSource, nullptr);
	glCompileShader(tControlShader);

    GLint infoLogLength;
    glGetShaderiv(tControlShader, GL_INFO_LOG_LENGTH, &infoLogLength);

    GLchar* strInfoLog = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog(tControlShader, infoLogLength, NULL, strInfoLog);
	delete[] strInfoLog;

	tEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(tEvalShader, 1, &tEvalShaderSource, nullptr);
	glCompileShader(tEvalShader);

    glGetShaderiv(tEvalShader, GL_INFO_LOG_LENGTH, &infoLogLength);

    strInfoLog = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog(tEvalShader, infoLogLength, NULL, strInfoLog);
	delete[] strInfoLog;

	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometryShader, 1, &geometryShaderSource, nullptr);
	glCompileShader(geometryShader);

    glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &infoLogLength);

    strInfoLog = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog(geometryShader, infoLogLength, NULL, strInfoLog);
	delete[] strInfoLog;

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, tControlShader);
	glAttachShader(program, tEvalShader);
	glAttachShader(program, geometryShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(tControlShader);
	glDeleteShader(tEvalShader);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return program;
}