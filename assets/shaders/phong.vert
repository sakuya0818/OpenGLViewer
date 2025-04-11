#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;

out vec2 uv;
out vec3 normal;
out vec3 worldPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat3 normalMatrix;

void main()
{
	// ����ת��Ϊ�������
	vec4 transformPosition = vec4(aPos, 1.0);
	// ģ�ͱ任
	transformPosition = model * transformPosition;
	// ������������
	worldPosition = transformPosition.xyz;
	// ��ͼ��ͶӰ�任
	gl_Position = projection * view * transformPosition;
	uv = aUV;
	normal = normalMatrix * aNormal;
}