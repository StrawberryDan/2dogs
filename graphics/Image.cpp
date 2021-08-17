#include "Image.hpp"

#include <stb/stb_image.h>
#include <loguru.h>

namespace Graphics {
	Image::Image(unsigned int width, unsigned int height): width(width), height(height), data(new uint8_t[width * height * 4]) {
		for (int i = 0; i < width * height * 4; i += 4) {
			data[i + 0] =   0;
			data[i + 1] =   0;
			data[i + 2] =   0;
			data[i + 3] = 255;
		}
	}

	Image::Image(unsigned int width, unsigned int height, Color color): width(width), height(height), data(new uint8_t[width * height * 4]) {
		for (int i = 0; i < width * height * 4; i += 4) {
			data[i + 0] = color.r;
			data[i + 1] = color.g;
			data[i + 2] = color.b;
			data[i + 3] = color.a;
		}
	}


	Image::Image(const char* file) {
		int width, height, channels;
		uint8_t* data = stbi_load(file, &width, &height, &channels, 4);
	
		if (data == nullptr) {
			auto reason = stbi_failure_reason();
			LOG_F(FATAL, "Could not load image file due to: %s", reason);
		}

		this->width = width;
		this->height = height;
		this->data = std::unique_ptr<uint8_t[]>(data);
	}

	Color Image::pixel(unsigned int x, unsigned int y) const {
		Color c;
		uint8_t *bytes = data.get() + (x + y * width) * 4;
		c.r = bytes[0];
		c.g = bytes[1];
		c.b = bytes[2];
		c.a = bytes[3];
		return c;
	}

	void Image::set_pixel(unsigned int x, unsigned int y, Color c) {
		uint8_t *bytes = data.get() + (x + y * width) * 4;
		bytes[0] = c.r;
		bytes[1] = c.g;
		bytes[2] = c.b;
		bytes[3] = c.a;
	}

	const uint8_t *Image::as_ptr() const {
		return data.get();
	}

	unsigned int Image::size() const {
		return width * height * 4;
	}
}
