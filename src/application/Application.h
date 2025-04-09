#include <iostream>

using ResizeCallback = void (*)(int width, int height);
using KeyBoardCallback = void (*)(int key, int action, int mods);
using MouseCallback = void(*)(int button, int action, int mods);
using CursorCallback = void(*)(double xPos, double yPos);
using ScrollCallback = void(*)(double offset);

class GLFWwindow;

class Application
{
public:
	~Application();

	static Application* getInstance();

	bool init(const int& width = 800, const int& height = 600);

	bool update();

	void destory();

	uint32_t getWidth() const { return mWidth; }
	uint32_t getHeight() const { return mHeight; }

	void getCursorPosition(double* x, double* y);

	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
	void setKeyBoardCallback(KeyBoardCallback callback) { mKeyBoardCallback = callback; }
	void setMouseCallback(MouseCallback callback) { mMouseCallback = callback; }
	void setCursorCallback(CursorCallback callback) { mCursorCallback = callback; }
	void setScrollCallback(ScrollCallback callback) { mScrollCallback = callback; }

private:
	static void frameBufferSizeCallback(GLFWwindow *window, int width, int height);

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);

	static void cursorCallback(GLFWwindow* window, double xPos, double yPos);

	static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

private:
	Application();

	// ȫ��Ψһ�ľ�̬����ʵ��
	static Application* mInstance;

	GLFWwindow* mWindow{nullptr};
	uint32_t mWidth{0};
	uint32_t mHeight{0};

	ResizeCallback mResizeCallback{ nullptr };
	KeyBoardCallback mKeyBoardCallback{ nullptr };
	MouseCallback mMouseCallback{ nullptr };
	CursorCallback mCursorCallback{ nullptr };
	ScrollCallback mScrollCallback{ nullptr };
};