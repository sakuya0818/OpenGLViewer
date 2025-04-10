#version 460 core
out vec4 FragColor;

uniform sampler2D sampler;
uniform sampler2D sampler1;

in vec2 uv;
in vec3 normal;
in vec3 worldPosition;

// 光源参数
uniform vec3 lightDirection;
uniform vec3 lightColor;
// 相机世界坐标
uniform vec3 cameraPos;
// 镜面反射光强度
uniform float specularIntensity;

void main()
{
	// 获取物体当前的像素颜色
	vec4 aColor = texture(sampler, uv);
	vec4 bColor = texture(sampler1, uv);
	vec4 color = aColor * 0.5 + bColor * 0.5;
	vec3 objectColor = color.xyz;

	// 归一化法向量和光源方向
	vec3 normalN = normalize(normal);
	vec3 lightDirN = normalize(lightDirection);
	vec3 viewDirN = normalize(cameraPos - worldPosition);

	// 计算漫反射光照
	float diffuse = clamp(dot(-lightDirN, normalN), 0.0, 1.0);
	vec3 diffuseColor = objectColor * diffuse * lightColor;

	// 计算镜面反射光照
	vec3 reflectDir = normalize(reflect(lightDirN, normalN));
	// 加64次方来控制镜面反射的光斑大小
	float specular = pow(clamp(dot(viewDirN, reflectDir), 0.0, 1.0), 64);
	vec3 specularColor = specular * lightColor * specularIntensity;

	vec3 finalColor = diffuseColor + specularColor;

	FragColor = vec4(finalColor, 1.0);
}