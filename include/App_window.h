#pragma once
#include <memory>
#include <string>
#include <SDL.h>
#include "Base_app_window.h"
#include "Buffer.h"

namespace suppositio {

class App_window : public Base_app_window {
public:
	App_window(const std::string& title, const std::shared_ptr<Buffer>& buffer);
	virtual void draw() override;
	virtual void show_message(uint32_t flags, const std::string& title, const std::string& message) override;
	virtual ~App_window();
protected:
	std::string title_;
	std::shared_ptr<Buffer> buffer_;
	int width_;
	int height_;

	SDL_Window* window_{ nullptr };
	SDL_Renderer* renderer_{ nullptr };
	SDL_Texture* texture_{ nullptr };

	void init();
};

} // suppositio