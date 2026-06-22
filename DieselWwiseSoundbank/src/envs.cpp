#include "envs.h"

namespace Wwise {
	ENVSyConversionTable::ENVSyConversionTable(Reader& reader) {
		reader.Read(&curve_enabled);
		reader.Read(&curve_scaling);
		reader.Read(&curve_size);

		for (uint16_t i = 0; i < curve_size; i++) {
			graph_points.push_back(RTPCGraphPoint(reader));
		}
	}

	void ENVSyConversionTable::Convert(Writer& writer) {
		writer << curve_enabled;
		writer << curve_scaling;
		writer << curve_size;

		for (uint16_t i = 0; i < curve_size; i++) {
			graph_points[i].Convert(writer);
		}
	}

	ENVSxConversionTable::ENVSxConversionTable(Reader& reader) {
		conversion_table.push_back(ENVSyConversionTable(reader)); // CurveVol
		conversion_table.push_back(ENVSyConversionTable(reader)); // CurveLPF
		if (VERSION != BankVersion::V2013) {
			conversion_table.push_back(ENVSyConversionTable(reader)); // CurveHPF
		}
	}

	void ENVSxConversionTable::Convert(Writer& writer) {
		conversion_table[0].Convert(writer); // CurveVol 
		conversion_table[1].Convert(writer); // CurveLPF

		if (VERSION == BankVersion::V2015) {
			conversion_table[2].Convert(writer); // CurveHPF
		}
		else {
			// Create CurveHPF from defaults
			ENVSyConversionTable new_curve_hpf{};
			new_curve_hpf.curve_enabled = 0;
			new_curve_hpf.curve_size = 2;
			
			RTPCGraphPoint graph_point_1{};
			graph_point_1.gp_to = 0.0;
			graph_point_1.gp_from = 0.0;
			graph_point_1.interpolation = CurveInterpolation::Linear;
			new_curve_hpf.graph_points.push_back(graph_point_1);

			RTPCGraphPoint graph_point_2{};
			graph_point_1.gp_to = 100.0;
			graph_point_1.gp_from = 100.0;
			graph_point_1.interpolation = CurveInterpolation::Linear;
			new_curve_hpf.graph_points.push_back(graph_point_2);

			new_curve_hpf.Convert(writer);
		}
	}

	ENVS::ENVS(Reader& reader) 
		: section_info(reader)
	{
		conversion_table.push_back(ENVSxConversionTable(reader));
		conversion_table.push_back(ENVSxConversionTable(reader));
	}

	void ENVS::Convert(Writer& writer) {
		section_info.Convert(writer);

		conversion_table[0].Convert(writer);
		conversion_table[1].Convert(writer);

		section_info.UpdateSize(writer);
	}
}