#include "event.h"

namespace Wwise {
	HIRCEvent::HIRCEvent(Reader& reader)
		: item_base(reader)
	{
		action_list_size = VERSION == BankVersion::V2022 ? reader.Read<uint8_t>() : reader.Read<uint32_t>();
		std::visit([&](auto& action_list_size) {
			for (unsigned int i = 0; i < action_list_size; i++) {
				action_list.push_back(reader.Read<uint32_t>());
			}
		}, action_list_size);

		// safety padding
		reader.Seek(item_base.data_start + item_base.size);
	}

	void HIRCEvent::Convert(Writer& writer) {
		item_base.Convert(writer);

		if (CONVERT_VERSION == BankVersion::V2022) {
			writer << (uint8_t)std::get<uint32_t>(action_list_size);
		}
		else {
			writer << std::get<uint32_t>(action_list_size);
		}

		std::visit([&](auto& action_list_size) {
			for (unsigned int i = 0; i < action_list_size; i++) {
				writer << action_list[i];
			}
		}, action_list_size);

		item_base.UpdateSize(writer);
	}
}