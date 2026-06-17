#pragma once
#include "bkhd.h"
#include <vector>

namespace Wwise {
	struct DATA {
		Section section_info;

		// DATA doesn't change between versions
		std::vector<unsigned char> data;

		void Convert(Writer& writer);

		DATA() = default;
		DATA(Reader& reader);
	};
}