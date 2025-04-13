#include "Mesh.h"

Mesh::Mesh(Geometry* geometry, Material* material)
{
	mGeometry = geometry;
	mMaterial = material;
	mType = ObjectType::Mesh_;
}

Mesh::~Mesh()
{
}
