#include "music_random_sequence_controller.h"

namespace Wwise {
	MusicRandomSequencePlaylistItem::MusicRandomSequencePlaylistItem(Reader& reader) {
		reader.Read(&segment_id);
		reader.Read(&playlist_item_id);
		reader.Read(&num_children);
		reader.Read(&RS_type);
		reader.Read(&loop);

		if (VERSION > BankVersion::V2013) {
			loop_min = reader.Read<int16_t>();
			loop_max = reader.Read<int16_t>();
		}

		reader.Read(&weight);
		reader.Read(&avoid_repeat_count);
		reader.Read(&is_using_weight);
		reader.Read(&is_shuffle);

		for (uint32_t i = 0; i < num_children; i++) {
			children.push_back(MusicRandomSequencePlaylistItem(reader));
		}
	}

	void MusicRandomSequencePlaylistItem::Convert(Writer& writer) {
		writer << segment_id;
		writer << playlist_item_id;
		writer << num_children;
		writer << RS_type;
		writer << loop;

		// loop min and max defaults for old
		writer << (uint16_t)0;
		writer << (uint16_t)0;

		writer << weight;
		writer << avoid_repeat_count;
		writer << is_using_weight;
		writer << is_shuffle;

		for (uint32_t i = 0; i < num_children; i++) {
			children[i].Convert(writer);
		}
	}

	HIRCMusicRandomSequenceController::HIRCMusicRandomSequenceController(Reader& reader) 
		: item_base(reader),
		transition_node(reader)
	{
		reader.Read(&num_playlist_items);
		base_playlist_item = MusicRandomSequencePlaylistItem(reader); // contains all other playlist items
	}

	void HIRCMusicRandomSequenceController::Convert(Writer& writer) {
		item_base.Convert(writer);

		transition_node.Convert(writer);

		writer << num_playlist_items;
		base_playlist_item.Convert(writer);

		item_base.UpdateSize(writer);
	}
}