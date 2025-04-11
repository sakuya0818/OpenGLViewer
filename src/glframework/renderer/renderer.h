#pragma once

#include <vector>

#include "../core.h"
#include "../Mesh.h"
#include "../../application/camera/Camera.h"
#include "../light/directionLight.h"
#include "../light/ambientLight.h"
#include "../shader.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	// ��Ⱦ���ܺ���
	void render(
		const std::vector<Mesh*>& meshes,
		Camera* camera,
		DirectionLight* dirLight,
		AmbientLight* ambLight
	);

private:
	Shader* pickShader(MaterialType type);

private:
	Shader* mPhongShader{ nullptr };
};