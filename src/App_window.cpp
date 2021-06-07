#include "App_window.h"
#include "Error.h"
#include "Pixel_format_BGR24.h"

namespace suppositio {

template <typename Pix_t, uint32_t Pix_f>
App_window<Pix_t, Pix_f>::App_window(const std::string& title, const std::shared_ptr<Buffer<Pix_t>>& buffer) :
	title_{ title }, buffer_{ buffer }, width_{ buffer_->get_width() }, height_{ buffer_->get_height() } {
	init();
}

template <typename Pix_t, uint32_t Pix_f>
void App_window<Pix_t, Pix_f>::draw() {
	SDL_UpdateTexture(texture_, nullptr, buffer_->get_raw(), width_ * sizeof(Buffer<Pix_t>::Pixel));
	SDL_RenderClear(renderer_);
	SDL_RenderCopy(renderer_, texture_, nullptr, nullptr);
	SDL_RenderPresent(renderer_);
	buffer_->set_need_redraw(false);
}

template <typename Pix_t, uint32_t Pix_f>
void App_window<Pix_t, Pix_f>::show_message(uint32_t flags, const std::string& title, const std::string& message) {
	SDL_ShowSimpleMessageBox(flags, title.c_str(), message.c_str(), window_);
}

template <typename Pix_t, uint32_t Pix_f>
App_window<Pix_t, Pix_f>::~App_window() {
	SDL_DestroyTexture(texture_);
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_Quit();
}

template <typename Pix_t, uint32_t Pix_f>
void App_window<Pix_t, Pix_f>::init() {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
		throw Fatal_error("Failed to initialize video subsystem.");
	}

	window_ = SDL_CreateWindow(
		title_.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width_,
		height_,
		SDL_WINDOW_SHOWN);

	if (!window_) {
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		throw Fatal_error("Failed to create application window.");
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);

	if (!renderer_) {
		SDL_DestroyWindow(window_);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		throw Fatal_error("Failed to create renderer.");
	}

	texture_ = SDL_CreateTexture(
		renderer_,
		Pix_f,
		SDL_TEXTUREACCESS_STATIC,
		width_,
		height_);

	if (!texture_) {
		SDL_DestroyRenderer(renderer_);
		SDL_DestroyWindow(window_);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		throw Fatal_error("Failed to create texture.");
	}
}

template class App_window<Pixel_format_BGR24, SDL_PIXELFORMAT_BGR24>;

} // suppositio