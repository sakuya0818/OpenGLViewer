#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Application* Application::mInstance = nullptr;
Application::Application()
{
}

Application::~Application()
{
}

Application* Application::getInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new Application();
	}

	return mInstance;
}

bool Application::init(const int& width, const int& height)
{
	mWidth = width;
	mHeight = height;

	// glfw��ʼ�������ð汾
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// �������壬��Ϊ��ǰ���崴��OPenGL������
	mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGLTest", nullptr, nullptr);
	if (mWindow == nullptr)
	{
		return false;
	}
	// ָ���Ĵ��ڵ� OpenGL ����������Ϊ��ǰ�̵߳ĵ�ǰ������
	glfwMakeContextCurrent(mWindow);

	// ʹ��glad�������е�ǰ�汾��OPenGL����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Could not load OpenGL functions" << std::endl;
		return false;
	}

	// ���ü������ڴ�С�仯�Ͱ����ص�
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);
	glfwSetKeyCallback(mWindow, keyCallback);
	glfwSetMouseButtonCallback(mWindow, mouseCallback);
	glfwSetCursorPosCallback(mWindow, cursorCallback);
	glfwSetScrollCallback(mWindow, scrollCallback);

	glfwSetWindowUserPointer(mWindow, this);

	return true;
}

bool Application::update()
{
	if (glfwWindowShouldClose(mWindow))
	{
		return false;
	}

	// �¼�ѭ��
	glfwPollEvents();

	// �л�˫����
	glfwSwapBuffers(mWindow);

	return true;
}

void Application::destory()
{
	glfwTerminate();
}

void Application::getCursorPosition(double* x, double* y)
{
	glfwGetCursorPos(mWindow, x, y);
}

void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mResizeCallback != nullptr)
	{
		self->mResizeCallback(width, height);
	}
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mKeyBoardCallback != nullptr)
	{
		self->mKeyBoardCallback(key, action, mods);
	}
}

void Application::mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mMouseCallback != nullptr)
	{
		self->mMouseCallback(button, action, mods);
	}
}

void Application::cursorCallback(GLFWwindow* window, double xPos, double yPos)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mCursorCallback != nullptr)
	{
		self->mCursorCallback(xPos, yPos);
	}
}

void Application::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mScrollCallback != nullptr)
	{
		self->mScrollCallback(yOffset);
	}
}
