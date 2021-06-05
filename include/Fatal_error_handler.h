#pragma once
#include <exception>
#include "Error.h"

namespace suppositio {

class Fatal_error_handler {
public:
	void handle(const std::exception& e);
};

} // suppositio

