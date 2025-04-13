#pragma once

#include "core.h"

enum class ObjectType
{
	Object_,
	Mesh_,
	Scene_
};

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

	// ¸¸×Ó¹ØÏµ
	void addChild(Object* child);
	std::vector<Object*> getChildren() { return mChildren; }
	Object* getParent() { return mParent; }
	//void removeChild(Object* child);

	ObjectType getType() { return mType; }

protected:
	glm::vec3 mPosition{ 0.0f, 0.0f, 0.0f };

	glm::vec3 mScale{ 1.0f, 1.0f, 1.0f };

	float mAngleX{ 0.0f };
	float mAngleY{ 0.0f };
	float mAngleZ{ 0.0f };

	std::vector<Object*> mChildren{};
	Object* mParent{ nullptr };

	ObjectType mType;
};