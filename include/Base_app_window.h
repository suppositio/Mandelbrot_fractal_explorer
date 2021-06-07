#pragma once
#include <string>
#include "Buffer.h"

namespace suppositio {

template <typename Pix_t>
class Base_app_window {
public:
	Base_app_window(const std::string& title, const std::shared_ptr<Buffer<Pix_t>>& buffer) :
		title_{ title }, buffer_{ buffer }, width_{ buffer_->get_width() }, height_{ buffer_->get_height() }{}
	virtual void draw() = 0;
	virtual void show_message(uint32_t flags, const std::string& title, const std::string& message) = 0;
	virtual ~Base_app_window() = default;

protected:
	std::string title_;
	std::shared_ptr<Buffer<Pix_t>> buffer_;
	int width_;
	int height_;
};

} // suppositio