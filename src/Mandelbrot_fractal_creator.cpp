#include "Mandelbrot_fractal_creator.h"
#include <algorithm>
#include <cmath>
#include <complex>
#include <limits>
#include <thread>
#include "Error.h"
#include "Palette.h"
#include "Theme1.h"
#include "Theme2.h"
#include "Theme3.h"

namespace suppositio {

Mandelbrot_fractal_creator::Mandelbrot_fractal_creator(const std::shared_ptr<Buffer>& buffer) :
	buffer_{ buffer }, width_{ buffer_->get_width() }, height_{ buffer_->get_height() },
	palette_size_{ std::max(height_ / 2, width_ / 2) }, palette_list_{}, scale_stack_{} {
	init();
}

void Mandelbrot_fractal_creator::reset() {
	scale_stack_.clear();
	center_ = { -0.5, 0.0 };
	scale_ = std::min(3.0 / height_, 4.0 / width_);
	update_max_iterations();
	current_palette_ = palette_list_.begin();
	create_image();
}

void Mandelbrot_fractal_creator::pane(int col, int row) {
	center_.x += (static_cast<Coord_t>(col) - static_cast<Coord_t>(width_) / 2) * scale_;
	center_.y += (static_cast<Coord_t>(row) - static_cast<Coord_t>(height_) / 2) * scale_;
	create_image();
}

void Mandelbrot_fractal_creator::zoom_in(double zoom_factor) {
	if (zoom_factor <= 0.0 || zoom_factor > 1.0) {
		throw Fatal_error("Invalid zoom factor value.");
	}
	static const Coord_t min_scale = std::numeric_limits<Coord_t>::epsilon() * std::max(width_, height_);
	Coord_t new_scale = scale_ * zoom_factor;
	if (min_scale > new_scale) {
		throw Non_fatal_error("Zoom limit reached.\nZoom out or reset the explorer.");
	}
	scale_stack_.push_back(scale_);
	scale_ = new_scale;
	update_max_iterations();
	create_image();
}

void Mandelbrot_fractal_creator::zoom_out() {
	if (!scale_stack_.empty()) {
		scale_ = scale_stack_.back();
		scale_stack_.pop_back();
		update_max_iterations();
		create_image();
	}
}

void Mandelbrot_fractal_creator::change_palette() {
	if (++current_palette_ == palette_list_.end()) {
		current_palette_ = palette_list_.begin();
	}
	create_image();
}

void Mandelbrot_fractal_creator::init() {
	palette_list_.emplace_back(std::make_unique<Palette<Theme1>>(Palette<Theme1>(palette_size_)));
	palette_list_.emplace_back(std::make_unique<Palette<Theme2>>(Palette<Theme2>(palette_size_)));
	palette_list_.emplace_back(std::make_unique<Palette<Theme3>>(Palette<Theme3>(palette_size_)));
	reset();
}

void Mandelbrot_fractal_creator::update_max_iterations() {
	max_iterations_ = palette_size_ * std::log(1 / scale_) + 2;
}

Mandelbrot_fractal_creator::World_coords Mandelbrot_fractal_creator::image_to_world(int col, int row) {
	World_coords coords;
	coords.x = (static_cast<Coord_t>(col) - static_cast<Coord_t>(width_) / 2) * scale_ + center_.x;
	coords.y = (static_cast<Coord_t>(row) - static_cast<Coord_t>(height_) / 2) * scale_ + center_.y;
	return coords;
}

int Mandelbrot_fractal_creator::iterations(World_coords coords) {
	int iterations{ 0 };
	std::complex<Coord_t> z{ 0 };
	std::complex<Coord_t> c{ coords.x, coords.y };
	while (z.real() * z.real() + z.imag() * z.imag() < 4.0 && iterations < max_iterations_) {
		z = z * z + c;
		++iterations;
	}
	static const Coord_t ln2 = std::log(2.0);
	return iterations = ((iterations >= max_iterations_) ? max_iterations_ :
		iterations - std::log((std::log(z.real() * z.real() + z.imag() * z.imag()) / ln2) / ln2));
}

void Mandelbrot_fractal_creator::create_image_part(int row_begin, int row_end) {
	for (int row{ row_begin }; row < row_end; ++row) {
		for (int col{ 0 }; col < width_; ++col) {
			World_coords coords = image_to_world(col, row);
			int iters = iterations(coords);
			if (iters != max_iterations_) {
				buffer_->set_pixel(col, row, (*current_palette_)->get_image_pixel(iters));
			}
			else {
				buffer_->set_pixel(col, row, { 0, 0, 0 });
			}
		}
	}
}

void Mandelbrot_fractal_creator::create_image() {
	int num_workers = std::thread::hardware_concurrency();
	int rows_per_worker = height_ / num_workers;
	std::vector<std::thread> workers;
	for (int i{ 0 }; i <= num_workers; ++i) {
		workers.emplace_back(std::thread(
			&Mandelbrot_fractal_creator::create_image_part, this,
			i * rows_per_worker, std::min((i + 1) * rows_per_worker, height_)));
	}
	for (auto& worker : workers) {
		if (worker.joinable()) {
			worker.join();
		}
	}
	buffer_->set_need_redraw(true);
}

} // suppositio