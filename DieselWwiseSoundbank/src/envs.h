#pragma once
#include "bkhd.h"
#include "HIRC/common.h"

namespace Wwise {
	struct ENVSyConversionTable {
		uint8_t curve_enabled;
		uint8_t curve_scaling;
		uint16_t curve_size;

		std::vector<RTPCGraphPoint> graph_points;

		void Convert(Writer& writer);
		ENVSyConversionTable() = default;
		ENVSyConversionTable(Reader& reader);
	};

	struct ENVSxConversionTable {
		std::vector<ENVSyConversionTable> conversion_table;

		void Convert(Writer& writer);
		ENVSxConversionTable() = default;
		ENVSxConversionTable(Reader& reader);
	};

	struct ENVS {
		Section section_info;

		std::vector<ENVSxConversionTable> conversion_table;

		void Convert(Writer& writer);
		ENVS() = default;
		ENVS(Reader& reader);
	};
}