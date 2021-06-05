#include "App_window.h"
#include "Error.h"

namespace suppositio {

App_window::App_window(const std::string& title, const std::shared_ptr<Buffer>& buffer) :
	title_{ title }, buffer_{ buffer }, width_{ buffer_->get_width() }, height_{ buffer_->get_height() } {
	init();
}

void App_window::draw() {
	SDL_UpdateTexture(texture_, nullptr, buffer_->get_raw(), width_ * sizeof(Buffer::Pixel));
	SDL_RenderClear(renderer_);
	SDL_RenderCopy(renderer_, texture_, nullptr, nullptr);
	SDL_RenderPresent(renderer_);
	buffer_->set_need_redraw(false);
}

void App_window::show_message(uint32_t flags, const std::string& title, const std::string& message) {
	SDL_ShowSimpleMessageBox(flags, title.c_str(), message.c_str(), window_);
}

App_window::~App_window() {
	SDL_DestroyTexture(texture_);
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_Quit();
}

void App_window::init() {
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
		SDL_PIXELFORMAT_BGR24,
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

} // suppositio