#include "stid.h"

namespace Wwise {
	BankHash::BankHash(Reader& reader) {
		reader.Read(&bank_id);
		reader.Read(&string_size);

		for (uint32_t i = 0; i < string_size; i++) {
			filename.push_back(reader.Read<char>());
		}
	}

	void BankHash::Convert(Writer& writer) {
		writer << bank_id;
		writer << string_size;

		for (uint32_t i = 0; i < string_size; i++) {
			writer << filename[i];
		}
	}

	STID::STID(Reader& reader) {
		std::cout << "Reading: STID (string mapping)" << std::endl;
		section_info = Section(reader);

		reader.Read(&type);
		reader.Read(&size);

		for (uint32_t i = 0; i < size; i++) {
			hash_lookup.push_back(BankHash(reader));
		}
	}

	void STID::Convert(Writer& writer) {
		section_info.Convert(writer);

		writer << type;
		writer << size;
		for (uint32_t i = 0; i < size; i++) {
			hash_lookup[i].Convert(writer);
		}

		section_info.UpdateSize(writer);
	}
}