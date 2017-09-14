
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
int main(const int argument_count, const char* arguments) {
	de::platform::Window* window = new de::platform::Window;
	de::graphics::Shader shader = de::graphics::Shader("shader.vert", "shader.frag");
	de::graphics::Mesh mesh = de::graphics::Mesh(shader);

	de::graphics::Renderer renderer = de::graphics::Renderer();
	renderer.init();

	renderer.submit(mesh);
	while (!window->isClosed()) {
		renderer.prepare();
		renderer.finish();
		window->update();
	}
	std::cin.get();
}