#pragma once

#include "Types.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>

struct Image {
private:
	uint32 x, y, n;
	uint8 *pixels;
public:
	Image(const String path, const uint8 channelCount = 4) {
		int32 t_x, t_y, t_n;
		pixels = stbi_load(path.c_str(), &t_x, &t_y, &t_n, channelCount);
		x = t_x;
		y = t_y;
		n = t_n;
	}

	inline uint32 getWidth() const {
		return x;
	}

	inline uint32 getHeight() const {
		return y;
	}

	inline uint32 getChannelCount() const {
		return n;
	}

	inline uint8* getPixels() const {
		return pixels;
	}


};
