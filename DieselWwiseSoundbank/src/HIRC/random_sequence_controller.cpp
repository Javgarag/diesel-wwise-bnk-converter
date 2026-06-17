#include "random_sequence_controller.h"

namespace Wwise {
	PlaylistItem::PlaylistItem(Reader& reader) {
		reader.Read(&play_id);
		reader.Read(&weight);
	}

	void PlaylistItem::Convert(Writer& writer) {
		writer << play_id;
		writer << weight;
	}

	Playlist::Playlist(Reader& reader) {
		reader.Read(&num_playlist_items);

		for (uint16_t i = 0; i < num_playlist_items; i++) {
			playlist_items.push_back(PlaylistItem(reader));
		}
	}

	void Playlist::Convert(Writer& writer) {
		writer << num_playlist_items;

		for (uint16_t i = 0; i < num_playlist_items; i++) {
			playlist_items[i].Convert(writer);
		}
	}

	HIRCRandomSequenceController::HIRCRandomSequenceController(Reader& reader)
		: item_base(reader),
		base_params(reader)
	{
		reader.Read(&loop_count);
		reader.Read(&loop_mod_min);
		reader.Read(&loop_mod_max);
		reader.Read(&transition_time);
		reader.Read(&transition_time_mod_min);
		reader.Read(&transition_time_mod_max);
		reader.Read(&avoid_repeat_count);
		reader.Read(&transition_mode);
		reader.Read(&random_mode);
		reader.Read(&mode);

		if (VERSION == BankVersion::V2013) {
			is_using_weight = reader.Read<uint8_t>();
			reset_playlist_at_each_play = reader.Read<uint8_t>();
			is_restart_backward = reader.Read<uint8_t>();
			is_continuous = reader.Read<uint8_t>();
			is_global = reader.Read<uint8_t>();
		}
		else {
			by_bit_vector = reader.Read<RandomSequenceControllerByBitVector>(sizeof(uint8_t));
		}

		children = Children(reader);
		playlist = Playlist(reader);
	}

	void HIRCRandomSequenceController::Convert(Writer& writer) {
		item_base.Convert(writer);
		base_params.Convert(writer);

		writer << loop_count;
		writer << loop_mod_min;
		writer << loop_mod_max;
		writer << transition_time;
		writer << transition_time_mod_min;
		writer << transition_time_mod_max;
		writer << avoid_repeat_count;
		writer << transition_mode;
		writer << random_mode;
		writer << mode;

		if (VERSION == BankVersion::V2013) {
			uint8_t bit_flags = 0;
			bit_flags |= (is_using_weight.value() << 0);
			bit_flags |= (reset_playlist_at_each_play.value() << 1);
			bit_flags |= (is_restart_backward.value() << 2);
			bit_flags |= (is_continuous.value() << 3);
			bit_flags |= (is_global.value() << 4);
			writer << bit_flags;
		}
		else {
			writer.Write(by_bit_vector, sizeof(uint8_t));
		}

		children.Convert(writer);
		playlist.Convert(writer);

		item_base.UpdateSize(writer);
	}
}