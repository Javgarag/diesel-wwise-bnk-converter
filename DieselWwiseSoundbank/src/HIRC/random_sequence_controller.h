#pragma once
#include "common.h"

namespace Wwise {
	struct RandomSequenceControllerByBitVector {
		bool is_using_weight : 1;
		bool reset_playlist_at_each_play : 1;
		bool is_restart_backward : 1;
		bool is_continuous : 1;
		bool is_global : 1;
		unsigned char : 3;
	};

	struct PlaylistItem {
		uint32_t play_id;
		int32_t weight;

		void Convert(Writer& writer);
		PlaylistItem() = default;
		PlaylistItem(Reader& reader);
	};

	struct Playlist {
		uint16_t num_playlist_items;
		std::vector<PlaylistItem> playlist_items;

		void Convert(Writer& writer);
		Playlist() = default;
		Playlist(Reader& reader);
	};

	struct HIRCRandomSequenceController {
		HIRCItemGeneric item_base;
		BaseParams base_params;

		uint16_t loop_count;
		uint16_t loop_mod_min;
		uint16_t loop_mod_max;

		float transition_time;
		float transition_time_mod_min;
		float transition_time_mod_max;

		uint16_t avoid_repeat_count;
		uint8_t transition_mode; // AkTransitionMode
		uint8_t random_mode; // AkRandomMode
		uint8_t mode; // AkContainerMode

		// 2013
		std::optional<uint8_t> is_using_weight;
		std::optional<uint8_t> reset_playlist_at_each_play;
		std::optional<uint8_t> is_restart_backward;
		std::optional<uint8_t> is_continuous;
		std::optional<uint8_t> is_global;

		// others
		std::optional<RandomSequenceControllerByBitVector> by_bit_vector;

		Children children;
		Playlist playlist;

		void Convert(Writer& writer);
		HIRCRandomSequenceController(Reader& reader);
	};
}