#pragma once
#include "Base_theme.h"

namespace suppositio {

class Theme3 : public Base_theme {
public:
	virtual double curve_red(double curve_arg) const override;
	virtual double curve_green(double curve_arg) const override;
	virtual double curve_blue(double curve_arg) const override;
	virtual ~Theme3() = default;
};

} // suppositio
