#pragma once
#include <vector>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class IndexBuffer {
private:
	std::vector<unsigned int> indices;
	GLuint elementbuffer;
public:
	IndexBuffer() {
		glGenBuffers(1, &elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	}

	void bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	}

	void unbind() {

	}


};