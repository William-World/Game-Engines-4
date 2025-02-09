#version 450 core

struct Light
{
	vec3 lightPos;
	float ambValue;
	float diffValue;
	float specValue;
	vec3 lightColour;
};

struct Material
{
	sampler2D diffuseMap; //newmtl

	float shininess; //Ns
	float transparency; //d

	vec3 ambient; //Ka
	vec3 diffuse; //Kd
	vec3 specular; //Ks
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
//in vec3 Colour;

//uniform sampler2D inputTexture;
uniform Light light;
uniform Material material;
uniform vec3 viewPos;

out vec4 fColour;

void main()
{
	//Ambient
	vec3 ambient = light.ambValue * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;
	
	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;
	
	//Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * material.specular) * light.lightColour;
	
	vec3 result = ambient + diffuse + specular;
	fColour = vec4(result, material.transparency);

	
	//fColour = texture(inputTexture, TexCoords);
}