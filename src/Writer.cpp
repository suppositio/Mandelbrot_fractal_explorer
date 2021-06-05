#include "Writer.h"
#include <fstream>
#include "Error.h"

namespace suppositio {

#pragma pack(push, 2)
struct Writer::BMP_header {
	char header[2]{ 'B', 'M' };
	int32_t file_size{ 0 };
	int32_t reserved{ 0 };
	int32_t data_offset{ 0 };
};
#pragma pack(pop)

#pragma pack(push, 2)
struct Writer::DIB_header {
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

Writer::Writer(const std::shared_ptr<Buffer>& buffer) :
	buffer_{ buffer },
	width_{ buffer_->get_width() },
	height_{ buffer_->get_height() } {}

void Writer::write(const std::string& file_name) {
	BMP_header bmp_header;
	DIB_header dib_header;
	bmp_header.file_size = sizeof(BMP_header) +
		sizeof(DIB_header) +
		width_ * height_ * sizeof(Buffer::Pixel);
	bmp_header.data_offset = sizeof(BMP_header) + sizeof(DIB_header);
	dib_header.width = width_;
	dib_header.height = height_;

	std::fstream file;
	file.open(file_name, std::ios::out | std::ios::binary);
	if (!file) {
		throw Non_fatal_error("Failed to open file:\n" + file_name);
	}

	file.write(reinterpret_cast<char*>(&bmp_header), sizeof(BMP_header));
	file.write(reinterpret_cast<char*>(&dib_header), sizeof(DIB_header));
	for (int i{ height_ - 1 }; i >= 0; --i) {
		file.write(reinterpret_cast<const char*>(buffer_->get_raw()) + i * width_ * sizeof(Buffer::Pixel),
			width_ * sizeof(Buffer::Pixel));
	}
	file.close();
	if (!file) {
		throw Non_fatal_error("Failed to close file:\n" + file_name);
	}
}

} // suppositio