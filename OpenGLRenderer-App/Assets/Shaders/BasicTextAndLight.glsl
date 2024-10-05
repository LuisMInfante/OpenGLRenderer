#shader vertex
#version 460 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec4 v_Color;
out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * pos;
	v_Color = vec4(clamp(pos.x, 0.0, 1.0), clamp(pos.y, 0.0, 1.0), clamp(pos.z, 0.0, 1.0), 1.0);
	v_TexCoord = texCoord;
	v_Normal = mat3(transpose(inverse(u_Model))) * normal;
	v_Position = (u_Model * pos).xyz;
};

#shader fragment
#version 460 core

in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_Position;

out vec4 color;

struct Light
{
	vec3 position;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 direction;
	float ambientIntensity;
	float diffuseIntensity;
};

struct Material
{
    float specularIntensity;
	float metallic;
};

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform Light u_Light;
uniform Material u_Material;

uniform vec3 u_CameraPosition;

void main()
{
	vec4 ambientColor = vec4(u_Light.ambientColor, 1.0) * u_Light.ambientIntensity;

	float diffuseFactor = max(dot(normalize(v_Normal), normalize(u_Light.direction)), 0.0f);
	vec4 diffuseColor = vec4(u_Light.diffuseColor, 1.0) * u_Light.diffuseIntensity * diffuseFactor;

	vec4 specularColor = vec4(0.0, 0.0, 0.0, 0.0);
	if(diffuseFactor > 0.0)
	{
		vec3 viewDirection = normalize(u_CameraPosition - v_Position);
		vec3 reflectDirection = reflect(-normalize(u_Light.direction), normalize(v_Normal));
		float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.metallic);
		specularColor = vec4(u_Light.diffuseColor * u_Material.specularIntensity * specularFactor, 1.0f);
	}

	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor * (ambientColor + diffuseColor + specularColor);
};