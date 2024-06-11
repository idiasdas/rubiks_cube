#include "shader.h"

Shader::Shader(const std::string &vertex_file_path, const std::string &fragment_file_path)
{
	// Create the shaders
	uint32_t vertez_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	uint32_t fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string vertex_shader_code;
	std::ifstream vertex_shader_stream(EXECUTABLE_UTILS_PATH + vertex_file_path, std::ios::in);
	if (vertex_shader_stream.is_open())
	{
		std::stringstream sstr;
		sstr << vertex_shader_stream.rdbuf();
		vertex_shader_code = sstr.str();
		vertex_shader_stream.close();
	}
	else
	{
		LOG_ERROR("Impossible to open {0}.", EXECUTABLE_UTILS_PATH + vertex_file_path);
		getchar();
		exit(EXIT_FAILURE);
	}

	// Read the Fragment Shader code from the file
	std::string fragment_shader_code;
	std::ifstream fragment_shader_stream(EXECUTABLE_UTILS_PATH + fragment_file_path, std::ios::in);
	if (fragment_shader_stream.is_open())
	{
		std::stringstream sstr;
		sstr << fragment_shader_stream.rdbuf();
		fragment_shader_code = sstr.str();
		fragment_shader_stream.close();
	}
	else
	{
		LOG_ERROR("Impossible to open {0}.", EXECUTABLE_UTILS_PATH + fragment_file_path);
		getchar();
		exit(EXIT_FAILURE);
	}

	int result = GL_FALSE;
	int infor_log_length;

	// Compile Vertex Shader
	LOG_INFO("Compiling shader: {0}", EXECUTABLE_UTILS_PATH + vertex_file_path);
	char const *vertex_source_pointer = vertex_shader_code.c_str();
	glShaderSource(vertez_shader_ID, 1, &vertex_source_pointer, NULL);
	glCompileShader(vertez_shader_ID);

	// Check Vertex Shader
	glGetShaderiv(vertez_shader_ID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertez_shader_ID, GL_INFO_LOG_LENGTH, &infor_log_length);
	if (infor_log_length > 0)
	{
		std::vector<char> vertex_shader_error_msg(infor_log_length + 1);
		glGetShaderInfoLog(vertez_shader_ID, infor_log_length, NULL, &vertex_shader_error_msg[0]);
		printf("%s\n", &vertex_shader_error_msg[0]);
	}

	// Compile Fragment Shader
	LOG_INFO("Compiling shader: {0}", EXECUTABLE_UTILS_PATH + fragment_file_path);

	char const *fragment_source_pointer = fragment_shader_code.c_str();
	glShaderSource(fragment_shader_ID, 1, &fragment_source_pointer, NULL);
	glCompileShader(fragment_shader_ID);

	// Check Fragment Shader
	glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragment_shader_ID, GL_INFO_LOG_LENGTH, &infor_log_length);
	if (infor_log_length > 0)
	{
		std::vector<char> fragment_shader_error_msg(infor_log_length + 1);
		glGetShaderInfoLog(fragment_shader_ID, infor_log_length, NULL, &fragment_shader_error_msg[0]);
		LOG_ERROR("{0}", fragment_shader_error_msg.data());
	}

	// Link the program
	LOG_INFO("Linking program.");
	uint32_t program_ID = glCreateProgram();
	glAttachShader(program_ID, vertez_shader_ID);
	glAttachShader(program_ID, fragment_shader_ID);
	glLinkProgram(program_ID);

	// Check the program
	glGetProgramiv(program_ID, GL_LINK_STATUS, &result);
	glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &infor_log_length);
	if (infor_log_length > 0)
	{
		std::vector<char> ProgramErrorMessage(infor_log_length + 1);
		glGetProgramInfoLog(program_ID, infor_log_length, NULL, &ProgramErrorMessage[0]);
		LOG_ERROR("{0}", ProgramErrorMessage.data());
	}

	glDetachShader(program_ID, vertez_shader_ID);
	glDetachShader(program_ID, fragment_shader_ID);

	glDeleteShader(vertez_shader_ID);
	glDeleteShader(fragment_shader_ID);

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
