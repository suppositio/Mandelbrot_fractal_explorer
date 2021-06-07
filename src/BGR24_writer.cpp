#include "BGR24_writer.h"
#include <fstream>
#include "Error.h"

namespace suppositio {

#pragma pack(push, 2)
struct BGR24_writer::Bitmap_file_header {
	char header[2]{ 'B', 'M' };
	int32_t file_size{ 0 };
	int32_t reserved{ 0 };
	int32_t data_offset{ 0 };
};
#pragma pack(pop)

#pragma pack(push, 2)
struct BGR24_writer::Bitmap_info_header {
	int32_t header_size{ 40 };
	int32_t width{ 0 };
	int32_t height{ 0 };
	int16_t planes{ 1 };
	int16_t bits_per_pixel{ 24 };
	int32_t compression{ 0 };
	int32_t data_size{ 0 };
	int32_t horizontal_resolution{ 2400 };
	int32_t vertical_resolution{ 2400 };
	int32_t colors{ 0 };
	int32_t important_colors{ 0 };
};
#pragma pack(pop)

void BGR24_writer::write(const std::string& file_name) {
	Bitmap_file_header bmp_file_header;
	Bitmap_info_header bmp_info_header;
	bmp_file_header.file_size = sizeof(bmp_file_header) +
		sizeof(bmp_info_header) +
		width_ * height_ * sizeof(Pixel_format_BGR24);
	bmp_file_header.data_offset = sizeof(bmp_file_header) + sizeof(bmp_info_header);
	bmp_info_header.width = width_;
	bmp_info_header.height = height_;

	std::fstream file;
	file.open(file_name, std::ios::out | std::ios::binary);
	if (!file) {
		throw Non_fatal_error("Failed to open file:\n" + file_name);
	}

	file.write(reinterpret_cast<char*>(&bmp_file_header), sizeof(bmp_file_header));
	file.write(reinterpret_cast<char*>(&bmp_info_header), sizeof(bmp_info_header));
	for (int i{ height_ - 1 }; i >= 0; --i) {
		file.write(reinterpret_cast<const char*>(buffer_->get_raw()) + i * width_ * sizeof(Pixel_format_BGR24),
			width_ * sizeof(Pixel_format_BGR24));
	}

	file.close();
	if (!file) {
		throw Non_fatal_error("Failed to close file:\n" + file_name);
	}
}

} // suppositio