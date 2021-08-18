#pragma once

#include <string>
#include <memory>

namespace Graphics {
	/**
	 * Struct representing an RGBA 8bit color
	 */
	struct Color {
		unsigned char r, g, b, a;
	};

	/**
	 * Struct representing a 2D planar image in RGBA 8bit color space.
	 */
	class Image {
	private:
		unsigned int width, height;
		std::unique_ptr<uint8_t[]> data;
	
	public:
		/// Creates and all black image with the given size.
		Image(unsigned int width, unsigned int height);
		/// Creates an image of the given size with all the given color.
		Image(unsigned int width, unsigned int height, Color color); 
		/// Loads an image from a file.
		Image(const char *file);
		inline Image(const std::string &file): Image(file.c_str()) {}

		inline unsigned int get_width() const { return width; }
		inline unsigned int get_height() const { return height; }
		
		/// Pixel color getter.
		Color pixel(unsigned int x, unsigned int y) const;
		/// Pixel color getter
		void set_pixel(unsigned int x, unsigned int y, Color c);
		/// Returns the pointer to the pixel buffer. Do not use after the this has been destroyed.
		const uint8_t *as_ptr() const;
		/// Returns the size of the pixel buffer in bytes.
		unsigned int size() const;
	};
}

