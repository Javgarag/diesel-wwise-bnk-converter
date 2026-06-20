#pragma once
#include "common.h"

namespace Wwise {
	struct HIRCFxShareSet {
		HIRCItemGeneric item_base;
		FXBase fx_base;

		void Convert(Writer& writer);
		HIRCFxShareSet() = default;
		HIRCFxShareSet(Reader& reader);
	};
}