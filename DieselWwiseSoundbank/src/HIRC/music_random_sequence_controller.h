#pragma once
#include "common.h"

namespace Wwise {
	struct MusicRandomSequencePlaylistItem {
		uint32_t segment_id;
		uint32_t playlist_item_id;
		uint32_t num_children;
		uint32_t RS_type;
		uint16_t loop;

		// +2013
		std::optional<int16_t> loop_min;
		std::optional<int16_t> loop_max;
		
		uint32_t weight;
		uint16_t avoid_repeat_count;
		uint8_t is_using_weight;
		uint8_t is_shuffle;
		std::vector<MusicRandomSequencePlaylistItem> children; // layered

		void Convert(Writer& writer);
		MusicRandomSequencePlaylistItem() = default;
		MusicRandomSequencePlaylistItem(Reader& reader);
	};

	struct HIRCMusicRandomSequenceController {
		HIRCItemGeneric item_base;
		MusicTransitionNode transition_node;
		uint32_t num_playlist_items;
		MusicRandomSequencePlaylistItem base_playlist_item; // layered

		void Convert(Writer& writer);
		HIRCMusicRandomSequenceController() = default;
		HIRCMusicRandomSequenceController(Reader& reader);
	};
}