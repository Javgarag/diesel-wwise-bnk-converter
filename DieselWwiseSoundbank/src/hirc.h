#pragma once
#include "reader.h"
#include "bkhd.h"

#include "HIRC/attenuation.h"
#include "HIRC/action.h"
#include "HIRC/actor_mixer.h"
#include "HIRC/event.h"
#include "HIRC/layer_container.h"
#include "HIRC/random_sequence_controller.h"
#include "HIRC/sound.h"
#include "HIRC/switch_container.h"
#include "HIRC/fx_share_set.h"
#include "HIRC/music_track.h"
#include "HIRC/music_segment.h"
#include "HIRC/music_switch.h"
#include "HIRC/music_random_sequence_controller.h"

#include <cstdint>
#include <vector>

namespace Wwise {
	struct HIRC {
		Section section_info;

		uint32_t num_items;

		std::vector<std::variant<
			HIRCUnknown, 
			HIRCAttenuation, 
			HIRCEvent, 
			HIRCSound, 
			HIRCActionBase, 
			HIRCRandomSequenceController, 
			HIRCActorMixer, 
			HIRCLayerContainer, 
			HIRCSwitchContainer, 
			HIRCFxShareSet, 
			HIRCMusicTrack, 
			HIRCMusicSegment, 
			HIRCMusicRandomSequenceController,
			HIRCMusicSwitch>> items;

		void Convert(Writer& writer);

		HIRC() = default;
		HIRC(Reader& reader);
	};
}