#shader vertex
#version 460 core

layout(location = 0) in vec4 pos;

void main()
{
	gl_Position = pos;
};

#shader fragment
#version 460 core

out vec4 color;

uniform vec4 u_Color;

void main()
{
	color = u_Color;
};