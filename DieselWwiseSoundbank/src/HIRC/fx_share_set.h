#pragma once
#include "common.h"

namespace Wwise {
	struct PluginParameters {
		uint32_t size;
		std::vector<unsigned char> data;
		// pad the rest

		void Convert(Writer& writer);
		PluginParameters() = default;
		PluginParameters(Reader& reader);
	};

	struct MediaMap {
		uint8_t index;
		uint32_t source_id;

		void Convert(Writer& writer);
		MediaMap() = default;
		MediaMap(Reader& reader);
	};

	struct RTPCInit2015 {
		uint8_t param_id;
		float init_value;

		void Convert(Writer& writer);
		RTPCInit2015() = default;
		RTPCInit2015(Reader& reader);
	};

	struct PluginPropertyValue {
		uint8_t property_id;
		uint8_t rtpc_accum;
		float value;

		void Convert(Writer& writer);
		PluginPropertyValue() = default;
		PluginPropertyValue(Reader& reader);
	};
	
	struct HIRCFxShareSet {
		HIRCItemGeneric item_base;
		Plugin fx_id;
		PluginParameters parameters;

		uint8_t num_bank_data;
		std::vector<MediaMap> media;
		InitialRTPC initial_rtpc;

		// 2015
		std::optional<uint16_t> num_init;
		std::optional<std::vector<RTPCInit2015>> rtpc_inits;

		// 2022
		std::optional<ParameterNodeStateChunkNew> state_chunk;
		std::optional<uint16_t> num_values;
		std::optional<std::vector<PluginPropertyValue>> property_values;

		void Convert(Writer& writer);
		HIRCFxShareSet() = default;
		HIRCFxShareSet(Reader& reader);
	};
}