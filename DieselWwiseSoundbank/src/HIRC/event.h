#pragma once
#include "common.h"

namespace Wwise {
	struct HIRCEvent {
		HIRCItemGeneric item_base;

		std::variant<uint32_t, uint8_t> action_list_size;
		std::vector<uint32_t> action_list;

		void Convert(Writer& writer);
		HIRCEvent(Reader& reader);
	};
}