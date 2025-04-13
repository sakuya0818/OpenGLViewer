#pragma once

#include <vector>

#include "../core.h"
#include "../Mesh.h"
#include "../../application/camera/Camera.h"
#include "../light/directionLight.h"
#include "../light/ambientLight.h"
#include "../shader.h"
#include "../Scene.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	// äÖÈ¾¹¦ÄÜº¯Êý
	void render(
		Scene *scene,
		Camera* camera,
		DirectionLight* dirLight,
		AmbientLight* ambLight
	);

	void renderObject(
		Object* object,
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