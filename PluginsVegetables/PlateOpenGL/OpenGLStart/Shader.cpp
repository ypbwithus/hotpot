#include "Shader.h"

#include <Renderer.h>

Shader::Shader(const std::string &filePath)
    : m_FilePath(filePath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filePath);
    LOG(INFO) << "fragmentSource:\n"
              << source.fragmentSource;
    LOG(INFO) << "vertexSource:\n"
              << source.vertexSource;

    m_RendererID = CreatShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string &name,
                          float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name),
                       v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string &name)
{

    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

    if (location == -1)
    {
        LOG(WARNING) << "Warning :uniform" << name << " doesn't exist!";
    }

    m_UniformLocationCache[name] = location;

    return location;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);

    const char *src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);

    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;

        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &result);

        char *message = (char *)alloca(sizeof(char) * length);

        glGetShaderInfoLog(id, length, &length, message);

        LOG(INFO) << "Faild to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << endl;

        // LOG(INFO) << string(message, length);

        std::cout << message;

        glDeleteShader(id);

        free(message);

        return 0;
    }

    return id;
}

unsigned int Shader::CreatShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

ShaderProgramSource Shader::ParseShader(const std::string &filePath)
{
    std::fstream stream(filePath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return {ss[0].str(), ss[1].str()};
}

void Shader::SetUniform1f(const std::string &name,
                          float value)
{
    GLCall(glUniform1f(GetUniformLocation(name),
                       value));
}

void Shader::SetUniform1i(const std::string &name,
                          int value)
{
    GLCall(glUniform1i(GetUniformLocation(name),
                       value));
}

void Shader::SetUniformMat4f(const std::string &name,
                             const glm::mat4 &matrix)

{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name),
                              1, GL_FALSE, &matrix[0][0]));
}
