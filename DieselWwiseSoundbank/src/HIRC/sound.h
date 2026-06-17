#pragma once
#include "common.h"

namespace Wwise {
	struct HIRCSound {
		HIRCItemGeneric item_base;

		SourceData source_data;
		BaseParams node_base_params;

		void Convert(Writer& writer);
		HIRCSound(Reader& reader);
	};
}