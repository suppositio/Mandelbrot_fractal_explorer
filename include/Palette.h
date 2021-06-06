#pragma once
#include <memory>
#include <type_traits>
#include "Base_palette.h"
#include "Base_theme.h"
#include "Buffer.h"

namespace suppositio {

template <typename Th>
class Palette : public Base_palette {
	static_assert(std::is_base_of<Base_theme<Th>, Th>(), "Invalid palette theme class");
public:
	Palette(int max_value) :
		max_value_{ max_value }, colors_(max_value_) {
		init();
	}

	virtual Buffer::Pixel get_image_pixel(int current_value) const override {
		return colors_.at(current_value % max_value_);
	}

	virtual ~Palette() = default;

protected:
	Th theme_;
	int max_value_;
	std::vector <Buffer::Pixel> colors_;

	void init() {
		for (int i{ 0 }; i < max_value_; ++i) {
			double curve_arg = static_cast<double>(i) / max_value_;
			static const Buffer::Color_channel_t max_color_channel =
				std::numeric_limits<Buffer::Color_channel_t>::max();
			colors_.at(i).red = max_color_channel * (theme_.curve_red(curve_arg));
			colors_.at(i).green = max_color_channel * (theme_.curve_green(curve_arg));
			colors_.at(i).blue = max_color_channel * (theme_.curve_blue(curve_arg));
		}
	}
};

} // suppositio