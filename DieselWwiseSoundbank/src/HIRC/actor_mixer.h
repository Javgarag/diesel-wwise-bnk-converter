#pragma once
#include "common.h"

namespace Wwise {
	struct HIRCActorMixer {
		HIRCItemGeneric item_base;
		BaseParams base_params;
		Children children;

		void Convert(Writer& writer);
		HIRCActorMixer(Reader& reader);
	};
}