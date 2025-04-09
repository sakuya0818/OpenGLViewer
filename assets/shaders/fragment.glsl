#version 460 core
out vec4 FragColor;

uniform sampler2D sampler;
uniform sampler2D sampler1;

in vec2 uv;
in vec3 normal;

// 光源参数
uniform vec3 lightDirection;
uniform vec3 lightColor;

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

	float diffuse = clamp(dot(-lightDirN, normalN), 0.0, 1.0);
	vec3 finalColor = objectColor * diffuse * lightColor;

	FragColor = vec4(finalColor, 1.0);
}