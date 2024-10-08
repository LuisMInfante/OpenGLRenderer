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
    // World Space
    v_Position = (u_Model * pos).xyz;

    v_Normal = mat3(transpose(inverse(u_Model))) * normal;

    // Clip Space
    gl_Position = u_Projection * u_View * u_Model * pos;

    v_TexCoord = texCoord;
}

#shader fragment
#version 460 core

in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_Position;

out vec4 color;

const int MaxPointLights = 3;

struct Light
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	vec3 direction;
	vec3 color;
	float intensity;
};

struct PointLight
{
	vec3 position;
	vec3 color;
	float intensity;
	float range;
	float constant;
	float linear;
	float quadratic;
};

struct Material
{
    float specularIntensity;
	float metallic;
};

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform Material u_Material;

uniform Light u_Light;
uniform DirectionalLight u_DirectionalLight;
uniform int u_PointLightCount;
uniform PointLight u_PointLights[MaxPointLights];

uniform vec3 u_CameraPosition;

vec4 CalculateLight(Light light, vec3 direction);
vec4 CalculateDirectionalLight();
vec4 CalculatePointLight();

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);

	color = texColor * (CalculateDirectionalLight() + CalculatePointLight());
};

vec4 CalculateLight(vec3 color, float intensity, vec3 direction)
{
	vec4 ambientColor = vec4(u_Light.color, 1.0) * u_Light.intensity;

	float diffuseFactor = max(dot(normalize(v_Normal), normalize(direction)), 0.0f);
	vec4 diffuseColor = vec4(color, 1.0) * intensity * diffuseFactor;

	vec4 specularColor = vec4(0.0, 0.0, 0.0, 0.0);
	if(diffuseFactor > 0.0)
	{
		vec3 viewDirection = normalize(u_CameraPosition - v_Position);
		vec3 reflectDirection = reflect(-normalize(direction), normalize(v_Normal));
		float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.metallic);
		specularColor = vec4(color * u_Material.specularIntensity * specularFactor, 1.0f);
	}

	return (ambientColor + diffuseColor + specularColor);
}

vec4 CalculateDirectionalLight()
{
	return CalculateLight(u_DirectionalLight.color, u_DirectionalLight.intensity, u_DirectionalLight.direction);
}

vec4 CalculatePointLight()
{
    vec4 result = vec4(0.0, 0.0, 0.0, 0.0);

    for (int i = 0; i < u_PointLightCount; i++)
    {
        vec3 lightDirection = u_PointLights[i].position - v_Position;
        float distance = length(lightDirection);
        lightDirection = normalize(lightDirection);

        float attenuation = u_PointLights[i].constant + 
                            u_PointLights[i].linear * distance + 
                            u_PointLights[i].quadratic * (distance * distance);

        float smoothFalloff = clamp(1.0 - (distance / u_PointLights[i].range), 0.0, 1.0);
        vec4 lightColor = CalculateLight(u_PointLights[i].color, u_PointLights[i].intensity, lightDirection);
        result += lightColor * (smoothFalloff / attenuation);  
    }

    return result;
}
