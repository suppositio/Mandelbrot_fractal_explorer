#pragma once
#include <memory>
#include <type_traits>
#include "Base_palette.h"
#include "Buffer.h"

namespace suppositio {

template <typename Pix_t, typename Th>
class Palette : public Base_palette<Pix_t> {
public:
	Palette(int max_value) :
		max_value_{ max_value }, colors_(max_value_) {
		init();
	}

	virtual typename Buffer<Pix_t>::Pixel get_image_pixel(int current_value) const override {
		return colors_.at(current_value % max_value_);
	}

	virtual ~Palette() = default;

protected:
	Th theme_;
	int max_value_;
	std::vector <typename Buffer<Pix_t>::Pixel> colors_;

	void init() {
		for (int i{ 0 }; i < max_value_; ++i) {
			double curve_arg = static_cast<double>(i) / max_value_;
			static constexpr auto max_color_channel =
				std::numeric_limits<uint8_t>::max();
			colors_.at(i).red = max_color_channel * (theme_.curve_red(curve_arg));
			colors_.at(i).green = max_color_channel * (theme_.curve_green(curve_arg));
			colors_.at(i).blue = max_color_channel * (theme_.curve_blue(curve_arg));
		}
	}
};

} // suppositio