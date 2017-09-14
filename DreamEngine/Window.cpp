#include "Types.h"
#include "Window.h"
#include "Image.h"

#include <iostream>
using namespace de::platform;

static GLFWwindow* window;
static GLFWcursor* cursor;
static GLFWimage icons[2];


GLFWimage toGLFW(const Image& image) {
	GLFWimage windowIcon;
	windowIcon.width = image.getWidth();
	windowIcon.height = image.getHeight();
	windowIcon.pixels = image.getPixels();
	return windowIcon;
}

Window::Window() {
	keyCallbacks = std::vector<KeyCallback>{};
	mouseButtonCallbacks = std::vector<MouseButtonCallback>{};
	cursorPositionCallbacks = std::vector<CursorPositionCallback>{};
	if (!glfwInit()) {
		std::cout << "GLFW init failed" << std::endl;
	}
	else {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		width = 1024;
		height = 720;
		title = "Nyan Quest";
		Image* icon = new Image("Res/icon.jpg");
		icons[0] = toGLFW(*icon);

		Image* cursorIcon = new Image("Res/cursor.png");
		icons[1] = toGLFW(*cursorIcon);

		cursor = glfwCreateCursor(&icons[1], 0, 0);
		goBorderlessWindowed();
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}
	}
}

void Window::update() const {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void glfwKeyCallback(GLFWwindow* w, const int key, const int action, const int c, const int d) {
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
	for (auto cb : window->keyCallbacks) {
		cb(key, action, c, d);
	}
	if (window && key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		window->close();
	}
}

void glfwCursorPositionCallback(GLFWwindow* w, const double x, const double y) {
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
	for (auto cb : window->cursorPositionCallbacks) {
		cb(x, y);
	}
}

void glfwMouseButtonCallback(GLFWwindow* w, const int a, const int b, const int c) {
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
	for (auto cb : window->mouseButtonCallbacks) {
		cb(a, b, c);
	}
}

void Window::close() {
	closed = true;
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::resize(const uint32_t width, const uint32_t height) {
	glfwSetWindowSize(window, width, height);
}

void Window::setClipboardContent(const cString content) const {
	glfwSetClipboardString(window, content);
}

cString Window::getClipboardContent() const {
	return glfwGetClipboardString(window);
}

void Window::recreateWindow() {
	if (window) {
		glfwDestroyWindow(window);
	}
	window = glfwCreateWindow(width, height, title, 0, window);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	glfwSetWindowPos(window, 0, 0);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, glfwKeyCallback);
	glfwSetCursorPosCallback(window, glfwCursorPositionCallback);
	glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
	glfwSetCursor(window, cursor);
	glfwSetWindowIcon(window, 1, icons);

}

void Window::goWindowed() {

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	width = mode->width;
	height = mode->height;
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	recreateWindow();
}

void Window::goBorderlessWindowed() {

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	width = mode->width;
	height = mode->height;
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	recreateWindow();
}

void Window::goFullscreen()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	width = mode->width;
	height = mode->height;
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	recreateWindow();
}

bool Window::isClosed() const {
	return closed || glfwWindowShouldClose(window);
}