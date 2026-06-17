#pragma once
#include "common.h"

namespace Wwise {
	struct SwitchPackage {
		uint32_t switch_id;
		uint32_t num_items;
		std::vector<uint32_t> node_id_list;

		void Convert(Writer& writer);
		SwitchPackage(Reader& reader);
	};

	struct SwitchByBitVector1 {
		bool is_first_only : 1;
		bool continue_playback : 1;
		unsigned char : 6;
	};

	struct SwitchByBitVector2 {
		bool on_switch_mode : 1;
		unsigned char : 7;
	};

	struct SwitchParams {
		uint32_t node_id;

		// 2013
		std::optional<uint8_t> is_first_only;
		std::optional<uint8_t> continue_playback;
		std::optional<uint32_t> on_switch_mode;

		// others
		std::optional<SwitchByBitVector1> bit_vector1;
		std::optional<SwitchByBitVector2> bit_vector2;

		uint32_t fade_out_time;
		uint32_t fade_in_time;

		void Convert(Writer& writer);
		SwitchParams(Reader& reader);
	};

	struct HIRCSwitchContainer {
		HIRCItemGeneric item_base;

		BaseParams base_params;
		std::variant<uint32_t, uint8_t> group_type;
		uint32_t group_id;
		uint32_t default_switch;
		uint8_t is_continuous_validation;
		Children children;

		uint32_t num_switch_groups;
		std::vector<SwitchPackage> switch_list;

		uint32_t num_switch_params;
		std::vector<SwitchParams> switch_params;

		void Convert(Writer& writer);
		HIRCSwitchContainer(Reader& reader);
	};
}