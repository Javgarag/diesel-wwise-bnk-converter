#pragma once
#include "common.h"

namespace Wwise {
	struct MusicMarker {
		uint32_t id;
		double position;

		// 2013, 2015
		std::optional<uint32_t> string_size;
		std::optional<std::vector<char>> marker_name;

		// 2022
		std::optional<std::string> marker_name_null_terminated;

		void Convert(Writer& writer);
		MusicMarker() = default;
		MusicMarker(Reader& reader);
	};
	
	struct HIRCMusicSegment {
		HIRCItemGeneric item_base;
		MusicNodeParams node_params;
		double duration;
		uint32_t num_markers;
		std::vector<MusicMarker> markers;

		void Convert(Writer& writer);
		HIRCMusicSegment() = default;
		HIRCMusicSegment(Reader& reader);
	};
}