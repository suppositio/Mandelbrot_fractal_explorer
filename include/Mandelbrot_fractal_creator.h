#pragma once
#include <memory>
#include <vector>
#include "Base_palette.h"
#include "Buffer.h"

namespace suppositio {

class Mandelbrot_fractal_creator {
public:
	using Coord_t = double;
	Mandelbrot_fractal_creator(const std::shared_ptr<Buffer>& buffer);
	void reset();
	void pane(int col, int row);
	void zoom_in(double zoom_factor);
	void zoom_out();
	void change_palette();

protected:
	struct World_coords {
		Coord_t x;
		Coord_t y;
	};

	std::shared_ptr<Buffer> buffer_;
	int width_;
	int height_;
	std::vector<std::unique_ptr<Base_palette>> palette_list_;
	std::vector<Coord_t> scale_stack_;

	int palette_size_;
	std::vector<std::unique_ptr<Base_palette>>::iterator current_palette_;

	World_coords center_;
	Coord_t scale_;

	int max_iterations_;

	void init();
	void update_max_iterations();
	World_coords image_to_world(int col, int row);
	int iterations(World_coords coords);
	void create_image_part(int row_begin, int row_end);
	void create_image();
};

} // suppositio