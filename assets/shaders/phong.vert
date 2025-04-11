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
	// 顶点转换为齐次坐标
	vec4 transformPosition = vec4(aPos, 1.0);
	// 模型变换
	transformPosition = model * transformPosition;
	// 计算世界坐标
	worldPosition = transformPosition.xyz;
	// 视图、投影变换
	gl_Position = projection * view * transformPosition;
	uv = aUV;
	normal = normalMatrix * aNormal;
}