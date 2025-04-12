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
	// ������ȼ��
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// ��������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ����Mesh
	for (int i = 0; i < meshes.size(); i++)
	{
		auto mesh = meshes[i];
		auto geometry = mesh->mGeometry;
		auto material = mesh->mMaterial;
		
		// ����ʹ���ĸ�Shader
		Shader* shader = pickShader(material->mType);
		// ����Shader��uniform����
		shader->beigin();

		switch (material->mType)
		{
		case MaterialType::MaterialTypePhong:
		{
			PhongMaterial* phongMaterial = static_cast<PhongMaterial*>(material);
			// ��ͼ
			shader->setInt("sampler", 0);
			shader->setInt("sampler1", 1);

			phongMaterial->mDiffuseTexture->bind();
			// MVP����
			shader->setMatrix4x4("model", mesh->getModelMatrix());
			shader->setMatrix4x4("view", camera->getViewMatrix());
			shader->setMatrix4x4("projection", camera->getProjectionMatrix());
			auto normalMatrix = glm::mat3(glm::transpose(glm::inverse(mesh->getModelMatrix())));
			shader->setMatrix3x3("normalMatrix", normalMatrix);
			// ƽ�й�
			shader->setVector3("directionalLight.direction", dirLight->mDirection);
			shader->setVector3("directionalLight.color", dirLight->mColor);
			shader->setFloat("directionalLight.specularIntensity", dirLight->mSpecularIntensity);
			shader->setFloat("directionalLight.shiness", phongMaterial->mShininess);
			// ������
			shader->setVector3("ambientColor", ambLight->mColor);
			// ���λ��
			shader->setVector3("cameraPos", camera->mPosition);
			break;
		}
		default:
			break;
		}

		// ��vao
		glBindVertexArray(geometry->getVao());

		// ִ�л�������
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
