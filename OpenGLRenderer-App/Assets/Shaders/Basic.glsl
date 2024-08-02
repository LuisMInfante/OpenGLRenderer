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

void main()
{
	color = vec4(0.0, 0.5, 1.0, 1.0);
};