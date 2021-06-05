#pragma once
#include "Buffer.h"

namespace suppositio {

class Base_palette {
public:
	virtual Buffer::Pixel get_image_pixel(int current_value) const = 0;
	virtual ~Base_palette() = default;
};

} //suppositio

