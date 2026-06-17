#include "music_track.h"

namespace Wwise {
	FadeParams::FadeParams(Reader& reader) {
		reader.Read(&transition_time);
		reader.Read(&fade_curve);
		reader.Read(&fade_offset);
	}

	void FadeParams::Convert(Writer& writer) {
		writer << transition_time;
		writer << fade_curve;
		writer << fade_offset;
	}

	MusicTrackAutomationItem::MusicTrackAutomationItem(Reader& reader) {
		reader.Read(&clip_index);
		reader.Read(&auto_type);
		reader.Read(&num_points);
		for (uint32_t i = 0; i < num_points; i++) {
			graph_points.push_back(RTPCGraphPoint(reader));
		}
	}

	void MusicTrackAutomationItem::Convert(Writer& writer) {
		writer << clip_index;
		writer << auto_type;
		writer << num_points;
		for (uint32_t i = 0; i < num_points; i++) {
			graph_points[i].Convert(writer);
		}
	}

	MusicTrackPlaylistItem::MusicTrackPlaylistItem(Reader& reader) {
		reader.Read(&track_id);
		reader.Read(&source_id);
		if (VERSION == BankVersion::V2022) {
			event_id = reader.Read<uint32_t>();
		}
		reader.Read(&play_at);
		reader.Read(&begin_trim_offset);
		reader.Read(&end_trim_duration);
		reader.Read(&src_duration);
	}

	void MusicTrackPlaylistItem::Convert(Writer& writer) {
		writer << track_id;
		writer << source_id;
		if (CONVERT_VERSION == BankVersion::V2022) {
			writer << (uint32_t)0; // default
		}
		writer << play_at;
		writer << begin_trim_offset;
		writer << end_trim_duration;
		writer << src_duration;
	}

	HIRCMusicTrack::HIRCMusicTrack(Reader& reader)
		: item_base(reader)
	{
		if (VERSION > BankVersion::V2013) {
			reader.Read(&flags, sizeof(uint8_t));
		}

		reader.Read(&num_sources);
		for (uint32_t i = 0; i < num_sources; i++) {
			sources.push_back(SourceData(reader));
		}

		reader.Read(&num_playlist_items);
		for (uint32_t i = 0; i < num_playlist_items; i++) {
			playlist.push_back(MusicTrackPlaylistItem(reader));
		}
		if (num_playlist_items > 0) {
			num_sub_track = reader.Read<uint32_t>();
		}

		reader.Read(&num_clip_automation_item);
		for (uint32_t i = 0; i < num_clip_automation_item; i++) {
			automation_items.push_back(MusicTrackAutomationItem(reader));
		}

		base_params = BaseParams(reader);

		if (VERSION == BankVersion::V2013) {
			RS_rtpc = reader.Read<uint32_t>();
		}
		else {
			track_type = reader.Read<uint8_t>();
			if (track_type == 0x3) {
				group_type = reader.Read<uint8_t>();
				group_id = reader.Read<uint32_t>();
				default_switch = reader.Read<uint32_t>();
				num_switch_assoc = reader.Read<uint32_t>();
				switch_assocs.emplace();
				for (uint32_t i = 0; i < num_switch_assoc; i++) {
					switch_assocs.value().push_back(reader.Read<uint32_t>());
				}
				src_fade_params = FadeParams(reader);
				sync_type = reader.Read<uint32_t>();
				cue_filter_hash = reader.Read<uint32_t>();
				dest_fade_params = FadeParams(reader);
			}
		}

		reader.Read(&look_ahead_time);
	}

	void HIRCMusicTrack::Convert(Writer& writer) {
		item_base.Convert(writer);

		writer << (uint8_t)0; // flags; all default to false
		writer << num_sources;
		for (uint32_t i = 0; i < num_sources; i++) {
			sources[i].Convert(writer);
		}

		writer << num_playlist_items;
		for (uint32_t i = 0; i < num_playlist_items; i++) {
			playlist[i].Convert(writer);
		}
		if (num_playlist_items > 0) {
			writer << num_sub_track.value();
		}

		writer << num_clip_automation_item;
		for (uint32_t i = 0; i < num_clip_automation_item; i++) {
			automation_items[i].Convert(writer);
		}

		base_params.Convert(writer);

		writer << (uint8_t)0; // track type default for conversion from older versions
		writer << look_ahead_time;

		item_base.UpdateSize(writer);
	}
}