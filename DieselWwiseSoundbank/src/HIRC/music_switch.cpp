#include "music_switch.h"

namespace Wwise {
	HIRCMusicSwitch::HIRCMusicSwitch(Reader& reader) 
		: item_base(reader),
		transition_node(reader)
	{
		size_t data_read = reader.Tell() - item_base.data_start;
		data.resize(item_base.size - data_read);
		reader.Read(data.data(), item_base.size - data_read);
	}

	void HIRCMusicSwitch::Convert(Writer& writer) {
		item_base.Convert(writer);
		transition_node.Convert(writer);

		writer.Write(*data.data(), data.size());

		item_base.UpdateSize(writer);
	}
}