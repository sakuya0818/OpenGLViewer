#include "tools.h"

void Tools::decompose(glm::mat4 matrix, glm::vec3& position, glm::vec3& eulerAngle, glm::vec3& scale)
{
	glm::quat quaternion;
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(matrix, scale, quaternion, position, skew, perspective);

	// 将四元数转换为欧拉角
	glm::mat4 rotationMatrix = glm::toMat4(quaternion);
	glm::extractEulerAngleXYZ(rotationMatrix, eulerAngle.x, eulerAngle.y, eulerAngle.z);
	// 将弧度转换为角度
	eulerAngle.x = glm::degrees(eulerAngle.x);
	eulerAngle.y = glm::degrees(eulerAngle.y);
	eulerAngle.z = glm::degrees(eulerAngle.z);
}
