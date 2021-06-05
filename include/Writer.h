#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Buffer.h"

namespace suppositio {

class Writer {
public:
	Writer(const std::shared_ptr<Buffer>& buffer);
	void write(const std::string& file_name);

protected:
	struct BMP_header;
	struct DIB_header;

	std::shared_ptr<Buffer> buffer_;
	int width_;
	int height_;
};

} // suppositio