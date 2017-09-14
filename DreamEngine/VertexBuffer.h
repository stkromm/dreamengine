#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Types.h"
#include <cassert>

namespace de {
	namespace graphics {
		class DrawBuffer {
		private:
			uint32 id;
			uint8* data;
			uint32 count;
		public:
			DrawBuffer() {

			}
			DrawBuffer(const uint8* data, const uint32 count) {
				GLuint buffer;
				glGenBuffers(1, &buffer);
				id = buffer;
				glBindBuffer(GL_ARRAY_BUFFER, id);
				glBufferData(GL_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
			}

			void bind() const {
				glBindBuffer(GL_ARRAY_BUFFER, id);
			}

			const uint32 getByteCount() const {
				return count;
			}
			/*
			
			void clear() {

			}

			void resize(uint32 byte_count) {
				if (byte_count > count) {

				}
				else {

				}
			}
			void set(uint8* _data, const uint32 byte_count, const uint32 offset = 0) {
				if (byte_count + offset >= getByteCount()) {
					resize(byte_count + offset);
				}
				memcpy(data + offset, _data, byte_count);
			}

			uint8* pointerAt(const uint32 index) const {
				assert(index < getByteCount());
				return data + index;
			}*/
		};
	}
}