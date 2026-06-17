#pragma once
#include "common.h"

namespace Wwise {
	struct MusicTrackPlaylistItem {
		uint32_t track_id;
		uint32_t source_id;

		// 2022
		std::optional<uint32_t> event_id;

		double play_at;
		double begin_trim_offset;
		double end_trim_duration;
		double src_duration;

		void Convert(Writer& writer);
		MusicTrackPlaylistItem() = default;
		MusicTrackPlaylistItem(Reader& reader);
	};

	struct MusicTrackAutomationItem {
		uint32_t clip_index;
		uint32_t auto_type;
		uint32_t num_points;
		std::vector<RTPCGraphPoint> graph_points;

		void Convert(Writer& writer);
		MusicTrackAutomationItem() = default;
		MusicTrackAutomationItem(Reader& reader);
	};

	struct FadeParams {
		int32_t transition_time;
		CurveInterpolation fade_curve;
		int32_t fade_offset;

		void Convert(Writer& writer);
		FadeParams() = default;
		FadeParams(Reader& reader);
	};

	struct HIRCMusicTrack {
		HIRCItemGeneric item_base;

		// + 2013
		std::optional<MusicTrackFlags> flags;

		uint32_t num_sources;
		std::vector<SourceData> sources;

		uint32_t num_playlist_items;
		std::vector<MusicTrackPlaylistItem> playlist;
		std::optional<uint32_t> num_sub_track; // if num_playlist_items > 0

		uint32_t num_clip_automation_item;
		std::vector<MusicTrackAutomationItem> automation_items;

		BaseParams base_params;

		// 2013
		std::optional<uint32_t> RS_rtpc;
		// others
		std::optional<uint8_t> track_type;

		// if track_type == AkMusicTrackType::Switch
		std::optional<uint8_t> group_type;
		std::optional<uint32_t> group_id;
		std::optional<uint32_t> default_switch;
		std::optional<uint32_t> num_switch_assoc;
		std::optional<std::vector<uint32_t>> switch_assocs;
		std::optional<FadeParams> src_fade_params;
		std::optional<uint32_t> sync_type;
		std::optional<uint32_t> cue_filter_hash;
		std::optional<FadeParams> dest_fade_params;

		int32_t look_ahead_time;

		void Convert(Writer& writer);
		HIRCMusicTrack() = default;
		HIRCMusicTrack(Reader& reader);
	};
}