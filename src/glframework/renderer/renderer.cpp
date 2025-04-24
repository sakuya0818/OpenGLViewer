#include "renderer.h"
#include "../material/phongMaterial.h"

#include <iostream>

Renderer::Renderer()
{
	mPhongShader = new Shader("assets/shaders/phong.vert", "assets/shaders/phong.frag");
}

Renderer::~Renderer()
{
}

void Renderer::render(Scene* scene, Camera* camera, DirectionLight* dirLight, AmbientLight* ambLight)
{
	// 开启深度检测
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// 画布清理
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 将Scene当做根节点渲染
	renderObject(scene, camera, dirLight, ambLight);
}

void Renderer::renderObject(Object* object, Camera* camera, DirectionLight* dirLight, AmbientLight* ambLight)
{
	// 判断当前物体类型，是Mesh就渲染
	if (object->getType() == ObjectType::Mesh_)
	{
		auto mesh = static_cast<Mesh*>(object);
		auto geometry = mesh->mGeometry;
		auto material = mesh->mMaterial;
		// 决定使用哪个Shader
		Shader* shader = pickShader(material->mType);
		// 更新Shader的uniform变量
		shader->beigin();
		switch (material->mType)
		{
		case MaterialType::MaterialTypePhong:
		{
			PhongMaterial* phongMaterial = static_cast<PhongMaterial*>(material);
			// 贴图
			shader->setInt("sampler", 0);
			shader->setInt("sampler1", 1);

			phongMaterial->mDiffuseTexture->bind();
			// MVP矩阵
			shader->setMatrix4x4("model", mesh->getModelMatrix());
			shader->setMatrix4x4("view", camera->getViewMatrix());
			shader->setMatrix4x4("projection", camera->getProjectionMatrix());
			auto normalMatrix = glm::mat3(glm::transpose(glm::inverse(mesh->getModelMatrix())));
			shader->setMatrix3x3("normalMatrix", normalMatrix);
			// 平行光
			shader->setVector3("directionalLight.direction", dirLight->mDirection);
			shader->setVector3("directionalLight.color", dirLight->mColor);
			shader->setFloat("directionalLight.specularIntensity", dirLight->mSpecularIntensity);
			shader->setFloat("directionalLight.shiness", phongMaterial->mShininess);
			// 环境光
			shader->setVector3("ambientColor", ambLight->mColor);
			// 相机位置
			shader->setVector3("cameraPos", camera->mPosition);
			break;
		}
		default:
			break;
		}
		glBindVertexArray(geometry->getVao());
		// 第三个参数是模型顶点的个数
		glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		shader->end();
	}

	// 递归渲染子物体
	auto children = object->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		renderObject(children[i], camera, dirLight, ambLight);
	}
}

void Renderer::setClearColor(glm::vec3 color)
{
	// 给上下文设置清屏
	glClearColor(color.x, color.y, color.z, 1.0f);
}

Shader* Renderer::pickShader(MaterialType type)
{
	Shader* result = nullptr;

	// 根据类型选择使用的Shader
	switch (type)
	{
	case MaterialType::MaterialTypePhong:
		result = mPhongShader;
		break;
	default:
		std::cout << "Renderer::pickShader: Unknown material type" << std::endl;
		break;
	}
	return result;
}
