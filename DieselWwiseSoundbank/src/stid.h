#pragma once
#include "bkhd.h"
#include <vector>

namespace Wwise {
	struct BankHash {
		uint32_t bank_id;
		uint8_t string_size;
		std::vector<char> filename;

		void Convert(Writer& writer);
		BankHash() = default;
		BankHash(Reader& reader);
	};

	struct STID {
		Section section_info;

		uint32_t type;
		uint32_t size;
		std::vector<BankHash> hash_lookup;

		void Convert(Writer& writer);
		STID() = default;
		STID(Reader& reader);
	};
}