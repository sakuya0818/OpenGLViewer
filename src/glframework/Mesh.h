#pragma once

#include "Object.h"
#include "Geometry.h"
#include "material/material.h"

class Mesh : public Object
{
public:
	Mesh(Geometry* geometry, Material* material);
	~Mesh();

public:
	Geometry* mGeometry{ nullptr };
	Material* mMaterial{ nullptr };
};