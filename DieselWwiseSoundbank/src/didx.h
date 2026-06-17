#pragma once
#include "bkhd.h"
#include <vector>

namespace Wwise {
	struct DIDX {
		Section section_info;

		// DIDX doesn't change between versions
		std::vector<unsigned char> data;

		void Convert(Writer& writer);

		DIDX() = default;
		DIDX(Reader& reader);
	};
}