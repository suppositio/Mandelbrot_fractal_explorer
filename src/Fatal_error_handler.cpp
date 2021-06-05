#include "Fatal_error_handler.h"
#include <SDL.h>

namespace suppositio {

void Fatal_error_handler::handle(const std::exception& fe) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal error", fe.what(), nullptr);
	SDL_Quit();
}

} // suppositio
