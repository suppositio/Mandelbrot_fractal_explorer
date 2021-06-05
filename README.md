# suppositio::Mandelbrot_fractal_explorer
## About the program
This is a simple program written in C++ that allows to view the details of [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set) fractal with zoom scale of up to 1.0e10. The fractal data is calculated via [renormalized Mandelbrot escape algorithm](http://linas.org/art-gallery/escape/escape.html). The image is colored using three different palette themes that can be switched at any time during the exploration. It is also possible to save the image to a BMP file. The current version supports image size of 800x600px and BGR24 BMP format only.
## Supported platforms
As of the current version, the program has been configured and tested for Windows desktop only. Both x64 and x86 builds are possible.
## Building the program
After cloning the repository or downloading its content, open the **Mandelbrot_fractal_explorer.sln** solution file in Microsoft Visual Studio (2019 or later). Build the solution  for the desired platform and configuration. Note that performance speed is much lower in the Debug configuration.
The executable file will be placed in the **build** directory created within the solution directory, in the subdirectory corresponding to the platform and configuration options selected. The dynamic library file necessary to run the program will be copied there as well.
## Using the program
The program starts with creating and displaying the image of the main cardioid of the Mandelbrot set fractal scaled to fit the main window.
To explore the details, point the mouse to the area that interests you and left-click to center on it. Than roll the mouse wheel forward or press the Up key on your keyboard to zoom into the area. To zoom out, roll the mouse wheel back or press the Down key. Once the maximum zoom is reached, you will be notified with a warning message.
You may cycle through the available coloring palette themes by clicking the right mouse button. To reset the explorer to its starting position and default palette theme, press Ctrl-R on your keyboard.
To save the current image to file, press Ctrl-S, then select destination directory and enter file name in the standard file save dialog that will appear. 
To quit the program, press Ctrl-Q or close the main window.
The above instructions are concisely summarized in the help box that can be called up by pressing F1 key.
## Credits
The use of the following external libraries is gratefully acknowledged:
- [Simple Directmedia Layer (SDL)](https://libsdl.org/)
- [Native File Dialog](https://github.com/mlabbe/nativefiledialog)