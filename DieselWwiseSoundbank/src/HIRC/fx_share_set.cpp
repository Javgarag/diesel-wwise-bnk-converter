#include "fx_share_set.h"

namespace Wwise {
	HIRCFxShareSet::HIRCFxShareSet(Reader& reader) 
		: item_base(reader),
		fx_base(reader)
	{
		// safety padding
		reader.Seek(item_base.data_start + item_base.size);
	}

	void HIRCFxShareSet::Convert(Writer& writer) {
		item_base.Convert(writer);

		fx_base.Convert(writer);

		item_base.UpdateSize(writer);
	}
}