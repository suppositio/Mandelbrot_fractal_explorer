#include "Theme3.h"
#include <cmath>

namespace suppositio {

double Theme3::curve_red(double curve_arg) const {
	return (std::cos(2.0 * (2.0 * curve_arg + 1.0) * std::acos(0.0)) + 1.0) / 2.0;
}

double Theme3::curve_green(double curve_arg) const {
	return curve_red(curve_arg);
}

double Theme3::curve_blue(double curve_arg) const {
	return curve_red(curve_arg);
}

} // suppositio