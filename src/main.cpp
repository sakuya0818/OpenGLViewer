#include <iostream>

#include "glframework/core.h"
#include "glframework/shader.h"
#include "glframework/texture.h"
#include "application/Application.h"
#include "application/camera/PerspectiveCamera.h"
#include "application/camera/TrackBallController.h"
#include "glframework/Geometry.h"
#include "glframework/Mesh.h"
#include "glframework/material/phongMaterial.h"
#include "glframework/renderer/renderer.h"

Renderer* renderer = nullptr;
std::vector<Mesh*> meshes{};
DirectionLight* dirLight = nullptr;
AmbientLight* ambLight = nullptr;

// ƽ�й�
glm::vec3 lightDirection = glm::vec3(-1.0f, 0.0, -1.0f);
glm::vec3 lightColor = glm::vec3(0.9f, 0.85f, 0.75f);

float specularIntensity = 0.6f;

glm::vec3 ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);

GLuint vao;
Shader* shader = nullptr;
Texture* texture = nullptr;
Texture* texture1 = nullptr;
glm::mat4 transform(1.0);
Geometry* geometry = nullptr;

PerspectiveCamera* camera = nullptr;
TrackBallController* cameraControl = nullptr;

void OnResize(int width, int height)
{
	std::cout << "�����С:" << width << height << std::endl;
	glViewport(0, 0, width, height);
}

void OnKey(int key, int action, int mods)
{
	cameraControl->onKey(key, action, mods);
}

void OnMouse(int button, int action, int mods)
{
	double x, y;
	Application::getInstance()->getCursorPosition(&x, &y);
	cameraControl->onMouse(button, action, x, y);
}

void OnCursor(double xPos, double yPos)
{
	cameraControl->onCursor(xPos, yPos);
}

void OnScroll(double offset)
{
	cameraControl->onScroll(offset);
}

// ׼�����
void prepareCamera()
{
	camera = new PerspectiveCamera(60.0f, (float)Application::getInstance()->getWidth() / (float)Application::getInstance()->getHeight(), 0.1f, 1000.0f);
	cameraControl = new TrackBallController();
	cameraControl->setCamera(camera);

	//viewMatrix = glm::lookAt(glm::vec3(0.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//std::cout << "111111111111111:" << glm::to_string(viewMatrix) << std::endl;
}

void prepare()
{
	renderer = new Renderer();

	// ��������
	auto geometry = Geometry::createSphere(1.0f);

	// �������ʲ����ò���
	auto material01 = new PhongMaterial();
	material01->mShininess = 10.0f;
	material01->mDiffuseTexture = new Texture("assets/textures/pikaqiu.jpg", 0);

	auto material02 = new PhongMaterial();
	material02->mShininess = 10.0f;
	material02->mDiffuseTexture = new Texture("assets/textures/111.jpg", 0);

	// ����Mesh
	auto mesh01 = new Mesh(geometry, material01);
	auto mesh02 = new Mesh(geometry, material02);
	mesh02->setPosition(glm::vec3(2.0f, 0.0f, 0.0f));

	meshes.push_back(mesh01);
	meshes.push_back(mesh02);

	dirLight = new DirectionLight();
	ambLight = new AmbientLight();
	ambLight->mColor = glm::vec3(0.1f);
}

int main()
{
	// ��ʼ������
	if (!Application::getInstance()->init(1600, 1200))
	{
		return -1;
	}

	glViewport(0, 0, 1600, 1200);
	glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// ���ü������ڴ�С�仯�Ͱ����ص�
	Application::getInstance()->setResizeCallback(OnResize);
	Application::getInstance()->setKeyBoardCallback(OnKey);
	Application::getInstance()->setMouseCallback(OnMouse);
	Application::getInstance()->setCursorCallback(OnCursor);
	Application::getInstance()->setScrollCallback(OnScroll);

	// ׼��Shader��vao��vbo
	prepareCamera();
	prepare();

	// ִ�д���ѭ��
	while (Application::getInstance()->update())
	{
		cameraControl->update();
		renderer->render(meshes, camera, dirLight, ambLight);
	}

	// �ͷ���Դ
	Application::getInstance()->destory();
	delete texture;
	
	return 0;
}