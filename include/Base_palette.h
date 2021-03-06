#pragma once
#include "Buffer.h"

namespace suppositio {

template <typename Pix_t>
class Base_palette {
public:
	virtual Pix_t get_image_pixel(int current_value) const = 0;
	virtual ~Base_palette() = default;
};

} //suppositio

