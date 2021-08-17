#pragma once

#include "Image.hpp"

namespace Graphics {
	class Texture {
	private:
		unsigned int gl_handle;

	public:
		Texture(const Image &image);
		Texture(const Texture &) = delete;
		Texture(Texture &&other);
		~Texture();

		Texture &operator=(const Texture &) = delete;
		Texture &operator=(Texture &&other);
	};
}
