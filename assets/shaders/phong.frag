#version 460 core
out vec4 FragColor;

uniform sampler2D sampler;
uniform sampler2D sampler1;

in vec2 uv;
in vec3 normal;
in vec3 worldPosition;

struct DirectionalLight
{
	vec3 direction;
	vec3 color;
	float specularIntensity;
	float shiness;
};

struct PointLight
{
	vec3 position;
	vec3 color;
	float specularIntensity;

	float k2;
	float k1;
	float k0;
};

struct SpotLight
{
	vec3 position;
	vec3 targetDirection;
	vec3 color;
	float outLine;
	float innerLine;
	float specularIntensity;
};

uniform DirectionalLight directionalLight;

// 环境光
uniform vec3 ambientColor;
// 相机世界坐标
uniform vec3 cameraPos;

// 计算漫反射光照
vec3 calculateDiffuse(vec3 lightColor, vec3 objectColor, vec3 lightDir, vec3 normal)
{
	float diffuse = clamp(dot(-lightDir, normal), 0.0, 1.0);
	vec3 diffuseColor = objectColor * diffuse * lightColor;
	return diffuseColor;
}

// 计算镜面反射光照
vec3 calculateSpecular(vec3 lightColor, vec3 lightDir, vec3 normal, vec3 viewDir, float intensity, float shiness)
{
	vec3 reflectDir = normalize(reflect(lightDir, normal));
	// 加次方来控制镜面反射的光斑大小
	float specular = pow(clamp(dot(viewDir, reflectDir), 0.0, 1.0), shiness);
	vec3 specularColor = specular * lightColor * intensity;

	return specularColor;
}

void main()
{
	// 获取物体当前的像素颜色
	vec4 aColor = texture(sampler, uv);
	vec4 bColor = texture(sampler1, uv);
	vec4 color = aColor * 0.5 + bColor * 0.5;
	vec3 objectColor = color.xyz;

	// 归一化法向量和光源方向
	vec3 normalN = normalize(normal);
	vec3 lightDirN = normalize(directionalLight.direction);
	vec3 viewDirN = normalize(cameraPos - worldPosition);

	vec3 diffuseColor = calculateDiffuse(directionalLight.color, objectColor, lightDirN, normalN);

	vec3 specularColor = calculateSpecular(directionalLight.color, lightDirN, normalN, viewDirN, directionalLight.specularIntensity, directionalLight.shiness);

	// 环境光计算
	vec3 ambient = ambientColor * objectColor;

	vec3 finalColor = diffuseColor + specularColor + ambient;

	FragColor = vec4(finalColor, 1.0);
}