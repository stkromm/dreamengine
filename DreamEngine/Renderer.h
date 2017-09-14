#pragma once
#include "Mesh.h"
#include "VertexBuffer.h"

namespace de {
	namespace graphics {

		class Renderer {
		private:
			de::graphics::DrawBuffer vertexBuffer;
			de::graphics::DrawBuffer colorBuffer;

		public:
			Renderer() {

			}
			void init() {
				GLuint VertexArrayID;
				glGenVertexArrays(1, &VertexArrayID);
				glBindVertexArray(VertexArrayID);
				// Enable depth test
				glEnable(GL_DEPTH_TEST);
				// Accept fragment if it closer to the camera than the former one
				glDepthFunc(GL_LESS);
			}

			void prepare() {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}

			void submit(const Mesh& mesh) {
				vertexBuffer = de::graphics::DrawBuffer(mesh.getVertices(), mesh.getByteCount());
				colorBuffer = de::graphics::DrawBuffer(mesh.getColors(), mesh.getByteCount());
			}

			void finish() {
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(
					1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
					3,                                // size
					GL_FLOAT,                         // type
					GL_FALSE,                         // normalized?
					0,                                // stride
					(void*)0                          // array buffer offset
				);
				glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
			}
		};
	}
}