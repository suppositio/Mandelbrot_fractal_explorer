#include "Theme1.h"
#include <cmath>

namespace suppositio {

double Theme1::curve_red(double curve_arg) const {
	return (std::cos(curve_arg * std::acos(0) * 4.0) + 1) / 2.0;
}

double Theme1::curve_green(double curve_arg) const {
	double temp = curve_arg + 4.0 / 6.0;
	return curve_red(temp);
}

double Theme1::curve_blue(double curve_arg) const {
	double temp = curve_arg + 2.0 / 6.0;
	return curve_red(temp);
}

} // suppositio