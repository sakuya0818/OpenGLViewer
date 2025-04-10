#pragma once

#include "../core.h"

enum class MaterialType
{
	MaterialTypeNone = 0,
	MaterialTypePhong,
	MaterialTypeBlinnPhong,
	MaterialTypeToon,
	MaterialTypePBR,
};

class Material
{
public:
	Material();
	virtual ~Material();
	
public:
	MaterialType mType;
};