#pragma once
#include <cstdint>

namespace suppositio {

#pragma pack(push, 1)
struct Pixel_format_BGR24 {
	uint8_t blue{ 0 };
	uint8_t green{ 0 };
	uint8_t red{ 0 };
};
#pragma pack(pop)

} // suppositio
