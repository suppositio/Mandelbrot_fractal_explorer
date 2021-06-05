#pragma once
#include <vector>

namespace suppositio {

class Buffer {
public:
	using Color_channel_t = uint8_t;
#pragma pack(push, 1)
	struct Pixel {
		Color_channel_t blue;
		Color_channel_t green;
		Color_channel_t red;
	};
#pragma pack(pop)

	Buffer(int width, int height);
	inline int get_width() const { return width_; }
	inline int get_height() const { return height_; }
	inline bool get_need_redraw() const { return need_redraw_; }
	inline void set_need_redraw(bool need_redraw) { need_redraw_ = need_redraw; }
	void set_pixel(int col, int row, Pixel pixel);
	const void* get_raw() const;

protected:
	int width_;
	int height_;
	std::vector<Pixel> pixels_;
	bool need_redraw_{ false };
};

} // suppositio

