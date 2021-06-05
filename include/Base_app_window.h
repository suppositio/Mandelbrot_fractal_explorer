#pragma once
#include <string>

namespace suppositio {

class Base_app_window {
public:
	virtual void draw() = 0;
	virtual void show_message(uint32_t flags, const std::string& title, const std::string& message) = 0;
	virtual ~Base_app_window() = default;
};

} // suppositio