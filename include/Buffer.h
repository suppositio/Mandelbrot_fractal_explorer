#pragma once
#include <vector>

namespace suppositio {

template <typename Pix_t>
class Buffer {
public:
	using Pixel = Pix_t;
	Buffer(int width, int height) :
		width_{ width }, height_{ height }, pixels_(width_* height_){};
	inline int get_width() const { return width_; }
	inline int get_height() const { return height_; }
	inline bool get_need_redraw() const { return need_redraw_; }
	inline void set_need_redraw(bool need_redraw) { need_redraw_ = need_redraw; }
	void set_pixel(int col, int row, Pixel pixel) {
		pixels_.at(row * width_ + col) = pixel;
	};
	const void* get_raw() const {
		return static_cast<const void*>(pixels_.data());
	};

protected:
	int width_;
	int height_;
	std::vector<Pixel> pixels_;
	bool need_redraw_{ false };
};

} // suppositio