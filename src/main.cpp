#include <iostream>

#include "glframework/core.h"
#include "glframework/shader.h"
#include "glframework/texture.h"
#include "application/Application.h"
#include "application/camera/PerspectiveCamera.h"
#include "application/camera/TrackBallController.h"
#include "glframework/Geometry.h"

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
glm::mat4 viewMatrix(1.0);
glm::mat4 orthoMatrix(1.0);
glm::mat4 perspectiveMatrix(1.0);
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

// ��ת�仯
void doRotationTransform()
{
	transform = glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
}

// ƽ�Ʊ仯
void doTranslationTransform()
{
	transform = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.5f, 0.0f, 0.0f));
}

// ���ű任
void doScaleTransform()
{
	transform = glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.5f, 0.5f, 1.0f));
}

// ��ת��ƽ�Ʊ任���
void doTransform()
{
	glm::mat4 rotateMat = glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	glm::mat4 translateMat = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.5f, 0.0f, 0.0f));
	transform = translateMat * rotateMat;
}

// ׼��SingleBuffer����
void prepareSingleBuffer()
{
	// ����ƽ��
	//geometry = Geometry::createPlane(1.0f, 1.0f);

	// ��������
	geometry = Geometry::createBox(1.0f);

	// ��������
	//geometry = Geometry::createSphere(1.0f);
}

// ׼��Shader
void prepareShader()
{
	shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

// ׼��Texture
void prepareTexture()
{
	texture = new Texture("assets/textures/pikaqiu.jpg", 0);
	texture1 = new Texture("assets/textures/111.jpg", 1);
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

void prepareOrtho()
{
	// ����ͶӰ����
	// left:��߽磬right:�ұ߽磬bottom:�ױ߽磬top:���߽磬near:���ü��棬far:Զ�ü���
	orthoMatrix = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 100.0f);
	std::cout << "222222222222222:" << glm::to_string(orthoMatrix) << std::endl;
}

void preparePerspective()
{
	// ͸��ͶӰ����
	// fovy:y�����Ұ�Ƕȣ�aspect:��߱ȣ�near:���ü��棬far:Զ�ü���
	perspectiveMatrix = glm::perspective(glm::radians(60.0f), (float)Application::getInstance()->getWidth() / (float)Application::getInstance()->getHeight(), 0.1f, 100.0f);
	std::cout << "333333333333333:" << glm::to_string(perspectiveMatrix) << std::endl;
}

// ��Ⱦ
void render()
{
	// ��������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �󶨵�ǰ��program
	shader->beigin();

	shader->setInt("sampler", 0);
	shader->setInt("sampler1", 1);

	shader->setMatrix4x4("model", transform);
	shader->setMatrix4x4("view", camera->getViewMatrix());
	shader->setMatrix4x4("projection", camera->getProjectionMatrix());

	shader->setVector3("lightDirection", lightDirection);
	shader->setVector3("lightColor", lightColor);

	shader->setVector3("cameraPos", camera->mPosition);
	shader->setFloat("specularIntensity", specularIntensity);
	shader->setVector3("ambientColor", ambientColor);

	// �󶨵�ǰ��vao
	glBindVertexArray(geometry->getVao());

	// ����������
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	shader->end();
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
	prepareShader();
	prepareSingleBuffer();
	prepareTexture();
	prepareCamera();

	// ִ�д���ѭ��
	while (Application::getInstance()->update())
	{
		cameraControl->update();
		render();
	}

	// �ͷ���Դ
	Application::getInstance()->destory();
	delete texture;
	
	return 0;
}