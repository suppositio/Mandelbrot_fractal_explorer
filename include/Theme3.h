#pragma once
#include "Base_theme.h"

namespace suppositio {

class Theme3 : public Base_theme<Theme3> {
public:
	double curve_red(double curve_arg) const;
	double curve_green(double curve_arg) const;
	double curve_blue(double curve_arg) const;
};

} // suppositio

