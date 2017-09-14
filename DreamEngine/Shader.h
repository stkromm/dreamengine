#pragma once
#include "Types.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>


namespace de {
	namespace graphics {

		class Shader {
		private:
			uint32 id;
		public:
			Shader(cString vert, cString frag);
			void setUniformFloat(cString name, float* data);
			void bind();
		};
	}
}