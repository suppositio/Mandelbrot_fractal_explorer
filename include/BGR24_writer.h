#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Base_writer.h"
#include "Buffer.h"
#include "Pixel_format_BGR24.h"

namespace suppositio {

class BGR24_writer : public Base_writer<Pixel_format_BGR24> {
public:
	BGR24_writer(const std::shared_ptr<Buffer<Pixel_format_BGR24>>& buffer) :
		Base_writer(buffer) {};
	virtual void write(const std::string& file_name) override;
	virtual ~BGR24_writer() = default;

protected:
	struct Bitmap_file_header;
	struct Bitmap_info_header;
};

} // suppositio