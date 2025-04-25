#include "Object.h"

Object::Object()
{
	mType = ObjectType::Object_;
}

Object::~Object()
{
}

void Object::setPosition(glm::vec3 pos)
{
	mPosition = pos;
}

void Object::rotateX(float angle)
{
	mAngleX += angle;
}

void Object::rotateY(float angle)
{
	mAngleY += angle;
}

void Object::rotateZ(float angle)
{
	mAngleZ += angle;
}

void Object::setAngleX(float angle)
{
	mAngleX = angle;
}

void Object::setAngleY(float angle)
{
	mAngleY = angle;
}

void Object::setAngleZ(float angle)
{
	mAngleY = angle;
}

void Object::setscale(glm::vec3 scale)
{
	mScale = scale;
}

glm::mat4 Object::getModelMatrix()
{
	// 先缩放，再旋转，最后平移
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, mScale);
	model = glm::rotate(model, glm::radians(mAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(mAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(mAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(glm::identity<glm::mat4>(), mPosition) * model;

	return model;
}

void Object::addChild(Object* child)
{
	auto iter = std::find(mChildren.begin(), mChildren.end(), child);
	if (iter != mChildren.end())
	{
		std::cout << "Object::addChild: child already exists" << std::endl;
		return;
	}
	mChildren.push_back(child);
	child->mParent = this;
}
