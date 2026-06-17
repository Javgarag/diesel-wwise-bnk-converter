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

#include <cstdint>
#include <vector>

namespace Wwise {
	struct HIRC {
		Section section_info;

		uint32_t num_items;
		// add HIRC types to this std::variant
		std::vector<std::variant<HIRCUnknown, HIRCAttenuation, HIRCEvent, HIRCSound, HIRCActionBase, HIRCRandomSequenceController, HIRCActorMixer, HIRCLayerContainer, HIRCSwitchContainer, HIRCFxShareSet>> items;

		void Convert(Writer& writer);

		HIRC() = default;
		HIRC(Reader& reader);
	};
}