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

	// äÖÈ¾¹¦ÄÜº¯Êý
	void render(
		const std::vector<Mesh*>& meshes,
		Camera* camera,
		DirectionLight* dirLight,
		AmbientLight* ambLight
	);

	void setClearColor(glm::vec3 color);

private:
	Shader* pickShader(MaterialType type);

private:
	Shader* mPhongShader{ nullptr };
};