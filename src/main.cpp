#include "Error.h"
#include "Fatal_error_handler.h"
#include "Mandelbrot_fractal_explorer.h"

int main(int argc, char* args[]) {

	const int width{ 800 };
	const int height{ 600 };
	const double zoom_factor{ 1.0 / 3.0 };

	try {
		suppositio::Mandelbrot_fractal_explorer explorer(width, height, zoom_factor);
		explorer.loop();
	}
	catch (std::exception& fe) {
		suppositio::Fatal_error_handler feh;
		feh.handle(fe);
		return 1;
	}
	
	return 0;
}