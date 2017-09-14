#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Types.h"

#include <vector>
#include <memory>
#include <iostream>

namespace de {
	namespace platform {
		constexpr uint32_t FULLSCREEN = 0;
		constexpr uint32_t BORDERLESS_WINDOWED = 1;
		constexpr uint32_t WINDOWED = 2;

		using KeyCallback = void(*)(const uint32, const  uint32, const  uint32, const  uint32);
		using CursorPositionCallback = void(*)(const double, const double);
		using MouseButtonCallback = void(*)(const uint32, const uint32, const uint32);
		class Window {
		public:
			std::vector<KeyCallback> keyCallbacks;
			std::vector<CursorPositionCallback> cursorPositionCallbacks;
			std::vector<MouseButtonCallback> mouseButtonCallbacks;
		private:
			int32_t width, height;
			const char *title;
			bool closed = false;
		public:
			Window();
			~Window() {
			}

			void update() const;
			void close();

			bool isClosed() const;

			void addKeyCallback(KeyCallback keyCallback) {
				keyCallbacks.push_back(keyCallback);
			}

			void addMouseButtonCallback(MouseButtonCallback mouseButtonCallback) {
				mouseButtonCallbacks.push_back(mouseButtonCallback);
			}

			void addCursorPositionCallback(CursorPositionCallback cursorPositionCallback) {
				cursorPositionCallbacks.push_back(cursorPositionCallback);
			}

			void setClipboardContent(const cString content) const;
			cString getClipboardContent() const;
			void resize(const uint32_t width, const uint32_t height);
			void goWindowed();
			void goBorderlessWindowed();
			void goFullscreen();
		private:
			void recreateWindow();
		};
	}
}