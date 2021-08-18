#pragma once

#include "Image.hpp"

namespace Graphics {
	/// Class representing a 2D Texture in OpenGL.
	class Texture {
	private:
		unsigned int handle;

	public:
		Texture(const Image &image);
		Texture(const Texture &) = delete;
		Texture(Texture && other);
		~Texture();

		Texture &operator=(const Texture &other) = delete;
		Texture &operator=(Texture &&other);

		void bind();
	};
}
