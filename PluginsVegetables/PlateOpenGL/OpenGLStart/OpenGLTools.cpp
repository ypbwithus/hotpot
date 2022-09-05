#include "OpenGLTools.h"



OpenGLTools *OpenGLTools::GetInstance()
{
    LOG(INFO) << "Get Instance of OpenGLTools";

    // Initialized during first access
    static OpenGLTools inst;

    return &inst;
}

OpenGLTools::OpenGLTools()
{

    LOG(INFO) << "Instance OpenGLTools";
}

OpenGLTools::~OpenGLTools()
{
    // LOG(INFO) << "In Destructor of OpenGLTools" << endl;
}

unsigned int compileShader(unsigned int type, const std::string &source)
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

unsigned int creatShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

ShaderProgramSource parseShader(const std::string &filePath)
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

// void GLClearError()
// {
//     while (glGetError() != GL_NO_ERROR)
//         ;
// }

// void GLCheckError()
// {
//     while (GLenum error = glGetError())
//     {
//         LOG(FATAL) << "[OepnGL Error](" << error << ")";
//     }
// }