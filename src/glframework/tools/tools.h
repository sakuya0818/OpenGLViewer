#pragma once

#include "../core.h"

class Tools
{
public:
	static void decompose(glm::mat4 matrix, glm::vec3& position, glm::vec3& eulerAngle, glm::vec3& scale);

};