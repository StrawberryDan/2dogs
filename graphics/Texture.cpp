#include "Texture.hpp"

#include <GL/gl3w.h>

namespace Graphics {
	Texture::Texture(const Image &image) {
		glGenTextures(1, &handle);

		glBindTexture(GL_TEXTURE_2D, handle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
				image.get_width(), image.get_height(),
				0, GL_RGBA, GL_RGBA8, image.as_ptr()
		);
	}

	Texture::Texture(Texture && other) {
		if (!handle) { glDeleteTextures(1, &handle); }
		handle = other.handle;
		other.handle = 0;
	}

	Texture::~Texture() {
		glDeleteTextures(1, &handle);
	}

	Texture &Texture::operator=(Texture && other) {
		if (!handle) { glDeleteTextures(1, &handle); }
		this->handle = other.handle;
		other.handle = 0;
		return *this;
	}

	void Texture::bind() {
		glBindTexture(GL_TEXTURE_2D, handle);
	}
}
