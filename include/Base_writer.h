#pragma once
#include "Buffer.h"

namespace suppositio {

template <typename Pix_t>
class Base_writer {
public:
	Base_writer(const std::shared_ptr<Buffer<Pix_t>>& buffer) :
		buffer_{ buffer },
		width_{ buffer->get_width() },
		height_{ buffer->get_height() } {}
	virtual void write(const std::string& file_name) = 0;
	virtual ~Base_writer() = default;

protected:
	std::shared_ptr<Buffer<Pix_t>> buffer_;
	int width_;
	int height_;
};

} // suppositio
