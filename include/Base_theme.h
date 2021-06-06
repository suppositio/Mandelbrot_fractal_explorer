#pragma once

namespace suppositio {

template <typename Der_th>
class Base_theme {
public:
	double curve_red(double curve_arg) const {
		return static_cast<Der_th const&>(*this).curve_red(curve_arg);
	}
	double curve_green(double curve_arg) const {
		return static_cast<Der_th const&>(*this).curve_green(curve_arg);
	}
	double curve_blue(double curve_arg) const {
		return static_cast<Der_th const&>(*this).curve_blue(curve_arg);
	}
};

} // suppositio