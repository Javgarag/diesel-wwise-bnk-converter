#pragma once
#include "common.h"

namespace Wwise {
	struct HIRCMusicSwitch {
		HIRCItemGeneric item_base;
		MusicTransitionNode transition_node;

		// doesn't change between any versions
		std::vector<unsigned char> data;

		void Convert(Writer& writer);
		HIRCMusicSwitch() = default;
		HIRCMusicSwitch(Reader& reader);
	};
}