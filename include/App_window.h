#pragma once
#include <memory>
#include <string>
#include <SDL.h>
#include "Base_app_window.h"
#include "Buffer.h"

namespace suppositio {

template <typename Pix_t, uint32_t Pix_f>
class App_window : public Base_app_window<Pix_t> {
public:
	App_window(const std::string& title, const std::shared_ptr<Buffer<Pix_t>>& buffer);
	virtual void draw() override;
	virtual void show_message(uint32_t flags, const std::string& title, const std::string& message) override;
	virtual ~App_window();
protected:

	std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> window_{nullptr, SDL_DestroyWindow};
	std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> renderer_{nullptr, SDL_DestroyRenderer};
	std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)> texture_{nullptr, SDL_DestroyTexture};

	void init();
};

} // suppositio