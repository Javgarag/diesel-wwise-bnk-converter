#include "data.h"

namespace Wwise {
	DATA::DATA(Reader& reader) {
		std::cout << "Reading: DATA (embedded sounds)" << std::endl;
		section_info = Section(reader);

		data.resize(section_info.size);
		reader.Read(data.data(), section_info.size);
	}

	void DATA::Convert(Writer& writer) {
		section_info.Convert(writer);

		writer.Write(*data.data(), data.size());

		section_info.UpdateSize(writer);
	}
}