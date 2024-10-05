#shader vertex
#version 460 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec4 v_Color;
out vec2 v_TexCoord;
out vec3 v_Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * pos;
	v_Color = vec4(clamp(pos.x, 0.0, 1.0), clamp(pos.y, 0.0, 1.0), clamp(pos.z, 0.0, 1.0), 1.0);
	v_TexCoord = texCoord;
	v_Normal = mat3(transpose(inverse(u_Model))) * normal;
};

#shader fragment
#version 460 core

in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;

out vec4 color;

struct Light
{
	vec3 position;
	vec3 color;
	vec3 direction;
	float ambientIntensity;
	float diffuseIntensity;
};

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform Light u_Light;

void main()
{
	vec4 ambientColor = vec4(u_Light.color, 1.0) * u_Light.ambientIntensity;
	float diffuseFactor = max(dot(normalize(v_Normal), normalize(u_Light.direction)), 0.0f);
	vec4 diffuseColor = vec4(u_Light.color, 1.0) * u_Light.diffuseIntensity * diffuseFactor;
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor * (ambientColor + diffuseColor);
};