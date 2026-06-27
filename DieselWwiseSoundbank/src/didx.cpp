#include "didx.h"

namespace Wwise {
	DIDX::DIDX(Reader& reader) {
		section_info = Section(reader);

		data.resize(section_info.size);
		reader.Read(data.data(), section_info.size);
	}

	void DIDX::Convert(Writer& writer) {
		section_info.Convert(writer);

		writer.Write(*data.data(), data.size());

		section_info.UpdateSize(writer);
	}
}