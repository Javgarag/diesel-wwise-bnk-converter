#include "sound.h"

namespace Wwise {
	HIRCSound::HIRCSound(Reader& reader)
		: item_base(reader),
		source_data(reader),
		node_base_params(reader)
	{
		// safety padding
		reader.Seek(item_base.data_start + item_base.size);
	}

	void HIRCSound::Convert(Writer& writer) {
		item_base.Convert(writer);

		source_data.Convert(writer);
		node_base_params.Convert(writer);

		item_base.UpdateSize(writer);
	}
}