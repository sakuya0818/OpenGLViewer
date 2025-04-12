#include "pointLight.h"

float PointLight::getK0() const
{
	return mK0;
}
float PointLight::getK1() const
{
	return mK1;
}
float PointLight::getK2() const
{
	return mK2;
}

void PointLight::setK(float k2, float k1, float k0)
{
	mK2 = k2;
	mK1 = k1;
	mK0 = k0;
}