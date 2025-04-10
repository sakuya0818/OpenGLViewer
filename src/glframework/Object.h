#pragma once

#include "core.h"

class Object
{
public:
	Object();
	~Object();

	void setPosition(glm::vec3 pos);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

	void setscale(glm::vec3 scale);

	glm::mat4 getModelMatrix();

protected:
	glm::vec3 mPosition{ 0.0f, 0.0f, 0.0f };

	glm::vec3 mScale{ 1.0f, 1.0f, 1.0f };

	float mAngleX{ 0.0f };
	float mAngleY{ 0.0f };
	float mAngleZ{ 0.0f };
};