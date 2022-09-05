#shader vertex
#version 330 core

layout(location = 0) in vec4 position; // 前4个浮点数据所代表的含义
layout(location = 1) in vec2 textCoord; // 后两个浮点数据的输入格式是自己定义的

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
        gl_Position = u_MVP * position;
        v_TexCoord = textCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
        vec4 textColor = texture(u_Texture,v_TexCoord);
        color = textColor;
};