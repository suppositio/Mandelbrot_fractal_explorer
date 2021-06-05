#include "Buffer.h"

namespace suppositio {

Buffer::Buffer(int width, int height)
	: width_{ width }, height_{ height }, pixels_(width_* height_) {
}

void Buffer::set_pixel(int col, int row, Pixel pixel) {
	pixels_.at(row * width_ + col) = pixel;
}

const void* Buffer::get_raw() const {
	return static_cast<const void*>(pixels_.data());
}

} // suppositio
