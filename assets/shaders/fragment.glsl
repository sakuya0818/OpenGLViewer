#version 460 core
out vec4 FragColor;

uniform sampler2D sampler;
uniform sampler2D sampler1;

in vec2 uv;
in vec3 normal;
in vec3 worldPosition;

// ��Դ����
uniform vec3 lightDirection;
uniform vec3 lightColor;
// �����������
uniform vec3 cameraPos;
// ���淴���ǿ��
uniform float specularIntensity;

void main()
{
	// ��ȡ���嵱ǰ��������ɫ
	vec4 aColor = texture(sampler, uv);
	vec4 bColor = texture(sampler1, uv);
	vec4 color = aColor * 0.5 + bColor * 0.5;
	vec3 objectColor = color.xyz;

	// ��һ���������͹�Դ����
	vec3 normalN = normalize(normal);
	vec3 lightDirN = normalize(lightDirection);
	vec3 viewDirN = normalize(cameraPos - worldPosition);

	// �������������
	float diffuse = clamp(dot(-lightDirN, normalN), 0.0, 1.0);
	vec3 diffuseColor = objectColor * diffuse * lightColor;

	// ���㾵�淴�����
	vec3 reflectDir = normalize(reflect(lightDirN, normalN));
	// ��64�η������ƾ��淴��Ĺ�ߴ�С
	float specular = pow(clamp(dot(viewDirN, reflectDir), 0.0, 1.0), 64);
	vec3 specularColor = specular * lightColor * specularIntensity;

	vec3 finalColor = diffuseColor + specularColor;

	FragColor = vec4(finalColor, 1.0);
}