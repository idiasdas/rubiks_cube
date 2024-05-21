#include "shader.h"

Shader::Shader(const std::string &vertex_file_path, const std::string &fragment_file_path)
{
	// Create the shaders
	uint32_t VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	uint32_t FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(EXECUTABLE_UTILS_PATH + vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else
	{
		std::cout << "Impossible to open " << EXECUTABLE_UTILS_PATH + vertex_file_path << std::endl;
		getchar();
		exit(EXIT_FAILURE);
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(EXECUTABLE_UTILS_PATH + fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else
	{
		std::cout << "Impossible to open " << EXECUTABLE_UTILS_PATH + fragment_file_path << std::endl;
		getchar();
		exit(EXIT_FAILURE);
	}

	int Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	std::cout << "Compiling shader: " << EXECUTABLE_UTILS_PATH + vertex_file_path << std::endl;
	char const *VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	std::cout << "Compiling shader: " << EXECUTABLE_UTILS_PATH + fragment_file_path << std::endl;

	char const *FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	uint32_t program_ID = glCreateProgram();
	glAttachShader(program_ID, VertexShaderID);
	glAttachShader(program_ID, FragmentShaderID);
	glLinkProgram(program_ID);

	// Check the program
	glGetProgramiv(program_ID, GL_LINK_STATUS, &Result);
	glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(program_ID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(program_ID, VertexShaderID);
	glDetachShader(program_ID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	m_renderer_ID = program_ID;
}

void Shader::bind() const
{
	glUseProgram(m_renderer_ID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}
