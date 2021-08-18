#pragma once

#include "Image.hpp"

namespace Graphics {
	/// Class representing a 2D Texture in OpenGL.
	class Texture {
	private:
		/// Handle to the opengl texture
		unsigned int handle;

	public:
		/// Makes a texture from an image.
		Texture(const Image &image);
		/// Disable copy constructor.
		Texture(const Texture &) = delete;
		/// Define move constructor.
		Texture(Texture && other);
		/// Cleanup destructor.
		~Texture();

		/// Disable copy assignment.
		Texture &operator=(const Texture &other) = delete;
		/// Define move assignment
		Texture &operator=(Texture &&other);
		
		/// Binds the texture to the GL texture slot.
		void bind();
	};
}
