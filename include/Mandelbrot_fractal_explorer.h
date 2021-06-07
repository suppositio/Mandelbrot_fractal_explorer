#pragma once
#include <memory>
#include "Base_app_window.h"
#include "Base_writer.h"
#include "Buffer.h"
#include "File_save_dialog.h"
#include "Mandelbrot_fractal_creator.h"
#include "Pixel_format_BGR24.h"

namespace suppositio {

class Mandelbrot_fractal_explorer {
public:
	Mandelbrot_fractal_explorer(int width, int height, double zoom_factor);
	void process_events();
	void loop();

protected:
	const char* title_{ "suppositio::Mandelbrot_fractal_explorer" };
	int width_;
	int height_;
	double zoom_factor_;

	std::shared_ptr<Buffer<Pixel_format_BGR24>> buffer_;
	std::unique_ptr<Mandelbrot_fractal_creator<Pixel_format_BGR24>> creator_;
	std::unique_ptr<Base_app_window<Pixel_format_BGR24>> window_;
	std::unique_ptr<File_save_dialog> save_dialog_;
	std::unique_ptr<Base_writer<Pixel_format_BGR24>> writer_;

	bool quit_{ false };

	void init();
	void pane_image(int col, int row);
	void zoom_in_image();
	void zoom_out_image();
	void change_image_palette();
	void reset_image();
	void write_image();
	void show_welcome();
	void show_help();
};

} // suppositio

