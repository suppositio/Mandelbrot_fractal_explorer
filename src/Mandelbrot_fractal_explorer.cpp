#include "Mandelbrot_fractal_explorer.h"
#include <SDL.h>
#include "App_window.h"
#include "BGR24_writer.h"
#include "Error.h"

namespace suppositio {

Mandelbrot_fractal_explorer::Mandelbrot_fractal_explorer(int width, int height, double zoom_factor) :
	width_{width}, height_{height}, zoom_factor_{zoom_factor},
	buffer_{ std::make_shared<Buffer<Pixel_format_BGR24>>(width_, height_) },
	creator_{ std::make_unique<Mandelbrot_fractal_creator<Pixel_format_BGR24>>(buffer_) },
	window_{ std::make_unique<App_window<Pixel_format_BGR24, SDL_PIXELFORMAT_BGR24>>(title_, buffer_) },
	save_dialog_{ std::make_unique<File_save_dialog>("bmp") },
	writer_{ std::make_unique<BGR24_writer>(buffer_) }{
	init();
}

void Mandelbrot_fractal_explorer::process_events() {
	SDL_Event event;
	SDL_WaitEvent(&event);
	if (event.type == SDL_QUIT) {
		quit_ = true;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks == 1) {
			pane_image(event.button.x, event.button.y);
		}
		else if (event.button.button == SDL_BUTTON_RIGHT && event.button.clicks == 1) {
			change_image_palette();
		}
	}

	else if (event.type == SDL_MOUSEWHEEL) {
		if (event.wheel.y > 0) {
			zoom_in_image();
		}
		else if (event.wheel.y < 0) {
			zoom_out_image();
		}
	}

	else if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.mod & KMOD_CTRL && event.key.keysym.scancode == SDL_SCANCODE_Q) {
			quit_ = true;
		}
		else if (event.key.keysym.mod & KMOD_CTRL && event.key.keysym.scancode == SDL_SCANCODE_R) {
			reset_image();
		}
		else if (event.key.keysym.mod & KMOD_CTRL && event.key.keysym.scancode == SDL_SCANCODE_S) {
			write_image();
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
			zoom_in_image();
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
			zoom_out_image();
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_F1) {
			show_help();
		}
	}
}

void Mandelbrot_fractal_explorer::loop() {
	while (true) {
		try {
			process_events();
		}
		catch (Non_fatal_error& nfe) {
			window_->show_warning("Warning", nfe.what());
		}
		if (quit_) {
			break;
		}
		if (buffer_->get_need_redraw()) {
			window_->draw();
		}
	}
}

void Mandelbrot_fractal_explorer::init() {
	if (zoom_factor_ <= 0.0 || zoom_factor_ > 1.0) {
		throw Fatal_error("Invalid zoom factor value.");
	}
	window_->draw();
	show_welcome();
}

void Mandelbrot_fractal_explorer::pane_image(int col, int row) {
	creator_->pane(col, row);
}

void Mandelbrot_fractal_explorer::zoom_in_image() {
	creator_->zoom_in(zoom_factor_);
}

void Mandelbrot_fractal_explorer::zoom_out_image() {
	creator_->zoom_out();
}

void Mandelbrot_fractal_explorer::change_image_palette() {
	creator_->change_palette();
}

void Mandelbrot_fractal_explorer::reset_image() {
	creator_->reset();
}

void Mandelbrot_fractal_explorer::write_image() {
	std::string file_name = save_dialog_->get_file_name();
	if (!file_name.empty()) {
		writer_->write(file_name);
	}
}

void Mandelbrot_fractal_explorer::show_welcome() {
	window_->show_message(
		"Welcome!",
		std::string(title_)+"\n\n"
		"Copyright (C) suppositio 2021.\n\n"
		"Help : keyboard F1.\n\n"
		"Enjoy!");
}

void Mandelbrot_fractal_explorer::show_help() {
	window_->show_message(
		"Help",
		"For best results, start exploring near the edges of solid black areas.\n\n"
		"- Center on an image point : mouse point + left click.\n"
		"- Zoom in : mouse wheel forward or keyboard Up.\n"
		"- Zoom out : mouse wheel backward or keyboard Down.\n"
		"- Change palette theme : mouse right click.\n"
		"- Reset explorer : keyboard Ctrl + R.\n"
		"- Save image : keyboard Ctrl + S.\n"
		"- Quit : keyboard Ctrl + Q or close window.\n"
		"- Help: keyboard F1.");
}

} // suppositio