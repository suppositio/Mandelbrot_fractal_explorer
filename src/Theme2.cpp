#include "Theme2.h"
#include <cmath>

namespace suppositio {

double Theme2::curve_red(double curve_arg) const {
	if (curve_arg >= 0.0 && curve_arg < 3.0 / 12.0) {
		return 1.0;
	}
	else if (curve_arg >= 3.0 / 12.0 && curve_arg < 4.0 / 12.0) {
		return 0.5;
	}
	else if (curve_arg >= 4.0 / 12.0 && curve_arg < 9.0 / 12.0) {
		return 0.0;
	}
	else if (curve_arg >= 9.0 / 12.0 && curve_arg < 10.0 / 12.0) {
		return 0.5;
	}
	else if (curve_arg >= 10.0 / 12.0 && curve_arg < 12.0 / 12.0) {
		return 1.0;
	}
	else {
		return 1.0;
	}
}

double Theme2::curve_green(double curve_arg) const {
	double temp = curve_arg + 8.0 / 12.0;
	return curve_red(temp - std::floor(temp));
}

double Theme2::curve_blue(double curve_arg) const {
	double temp = curve_arg + 4.0 / 12.0;
	return curve_red(temp - std::floor(temp));
}

} // suppositio
