#pragma once

namespace suppositio {

class Base_theme {
public:
	virtual double curve_red(double curve_arg) const = 0;
	virtual double curve_green(double curve_arg) const = 0;
	virtual double curve_blue(double curve_arg) const = 0;
	virtual ~Base_theme() = default;
};

} // suppositio