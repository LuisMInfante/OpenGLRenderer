#shader vertex
#version 460 core

layout(location = 0) in vec4 pos;

out vec4 o_Color;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * u_Model * pos;
	o_Color = vec4(clamp(pos.x, 0.0, 1.0), clamp(pos.y, 0.0, 1.0), clamp(pos.z, 0.0, 1.0), 1.0);
};

#shader fragment
#version 460 core

in vec4 o_Color;

out vec4 color;

uniform vec4 u_Color;

void main()
{
	color = o_Color;
};