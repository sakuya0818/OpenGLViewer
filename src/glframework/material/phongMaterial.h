#pragma once

#include "material.h"
#include "../texture.h"

class PhongMaterial : public Material
{
public:
	PhongMaterial();
	~PhongMaterial();

public:
	Texture* mDiffuseTexture = nullptr;
	float mShininess = 32.0f;
};