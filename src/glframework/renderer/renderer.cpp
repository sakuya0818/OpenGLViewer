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

void Renderer::render(const std::vector<Mesh*>& meshes, Camera* camera, DirectionLight* dirLight, AmbientLight* ambLight)
{
	// 开启深度检测
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// 画布清理
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 绘制Mesh
	for (int i = 0; i < meshes.size(); i++)
	{
		auto mesh = meshes[i];
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

		// 绑定vao
		glBindVertexArray(geometry->getVao());

		// 执行绘制命令
		glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0);

		shader->end();
	}
}

Shader* Renderer::pickShader(MaterialType type)
{
	Shader* result = nullptr;

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
