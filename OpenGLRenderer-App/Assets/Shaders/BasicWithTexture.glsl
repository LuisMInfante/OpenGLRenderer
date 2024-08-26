#shader vertex
#version 460 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 texCoord;

out vec4 v_Color;
out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * pos;
	v_Color = vec4(clamp(pos.x, 0.0, 1.0), clamp(pos.y, 0.0, 1.0), clamp(pos.z, 0.0, 1.0), 1.0);
	v_TexCoord = texCoord;
};

#shader fragment
#version 460 core

in vec4 v_Color;
in vec2 v_TexCoord;

out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
};