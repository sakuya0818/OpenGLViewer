#include <iostream>

#include "glframework/core.h"
#include "glframework/shader.h"
#include "glframework/texture.h"
#include "application/Application.h"
#include "application/camera/PerspectiveCamera.h"
#include "application/camera/TrackBallController.h"
#include "glframework/Geometry.h"
#include "glframework/Mesh.h"
#include "glframework/Scene.h"
#include "glframework/material/phongMaterial.h"
#include "glframework/renderer/renderer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

Renderer* renderer = nullptr;
Scene* scene = nullptr;
DirectionLight* dirLight = nullptr;
AmbientLight* ambLight = nullptr;

// 平行光
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
	std::cout << "窗体大小:" << width << height << std::endl;
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

void initIMGUI()
{
	 ImGui::CreateContext();
	 ImGui::StyleColorsDark();
	
	 // Setup Platform/Renderer bindings
	 ImGui_ImplGlfw_InitForOpenGL(Application::getInstance()->getWindow(), true);
	 ImGui_ImplOpenGL3_Init("#version 460");

	 //ImGuiIO& io = ImGui::GetIO(); (void)io;
	 //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	 //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	 //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
}

glm::vec3 clearColor{ 0.0f, 0.0f, 0.0f };

void renderIMGUI()
{
	// 开启当前的IMGUI渲染
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	// IMGUI渲染当前窗口的控件，从上到下渲染
	ImGui::Begin("Hello, world!");
	ImGui::Text("This is some useful text.");
	ImGui::Button("Test Button", ImVec2(40, 20));
	ImGui::ColorEdit3("clear color", (float*)&clearColor);
	ImGui::End();
	// UI渲染
	ImGui::Render();
	// 获取当前窗口的大小
	int displayWidth, displayHeight;
	glfwGetFramebufferSize(Application::getInstance()->getWindow(), &displayWidth, &displayHeight);
	// 重置视口大小
	glViewport(0, 0, displayWidth, displayHeight);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// 准备相机
void prepareCamera()
{
	camera = new PerspectiveCamera(60.0f, (float)Application::getInstance()->getWidth() / (float)Application::getInstance()->getHeight(), 0.1f, 1000.0f);
	cameraControl = new TrackBallController();
	cameraControl->setCamera(camera);
}

void prepare()
{
	renderer = new Renderer();
	scene = new Scene();

	// 创建几何
	auto geometry = Geometry::createSphere(1.0f);
	auto geometry1 = Geometry::createBox(1.0f);

	// 创建材质并配置参数
	auto material01 = new PhongMaterial();
	material01->mShininess = 10.0f;
	material01->mDiffuseTexture = new Texture("assets/textures/pikaqiu.jpg", 0);

	auto material02 = new PhongMaterial();
	material02->mShininess = 10.0f;
	material02->mDiffuseTexture = new Texture("assets/textures/111.jpg", 0);

	// 创建Mesh
	auto mesh01 = new Mesh(geometry, material01);
	auto mesh02 = new Mesh(geometry1, material02);
	mesh02->setPosition(glm::vec3(2.0f, 0.0f, 0.0f));

	mesh01->addChild(mesh02);
	scene->addChild(mesh01);

	dirLight = new DirectionLight();
	ambLight = new AmbientLight();
	ambLight->mColor = glm::vec3(0.1f);
}

int main()
{
	// 初始化窗体
	if (!Application::getInstance()->init(1600, 1200))
	{
		return -1;
	}

	glViewport(0, 0, 1600, 1200);
	glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// 设置监听窗口大小变化和按键回调
	Application::getInstance()->setResizeCallback(OnResize);
	Application::getInstance()->setKeyBoardCallback(OnKey);
	Application::getInstance()->setMouseCallback(OnMouse);
	Application::getInstance()->setCursorCallback(OnCursor);
	Application::getInstance()->setScrollCallback(OnScroll);

	// 准备Shader和vao，vbo
	prepareCamera();
	prepare();
	initIMGUI();

	// 执行窗体循环
	while (Application::getInstance()->update())
	{
		renderer->setClearColor(clearColor);
		cameraControl->update();
		renderer->render(scene, camera, dirLight, ambLight);
		renderIMGUI();
	}

	// 释放资源
	Application::getInstance()->destory();
	delete texture;
	
	return 0;
}