#include "attenuation.h"

namespace Wwise {
	/*
		CURVES
		2013: 5
			Output Bus Volume
				No options
			Aux send volumes (Game def.)
				None = -1
				Use Output Bus Volume = 0
				Custom = 1
			Aux send volumes (User def.)
				None = -1
				Use Output Bus Volume = 0
				Custom = 1
			LPF
				None = -1
				Custom = 1
			Spread
				None = -1
				Custom = 1
		2015: ? (7. safe to assume same curve order, probably includes only driven by distance on 2022+)
		2022: 17
			Drived by distance:
				Volume
				Aux send volumes (Game def.) (default = UseOutputBusVolume)
				Aux send volumes (User def.) (default = UseOutputBusVolume)
				LPF (default = None)
				HPF (default = None)
				Spread (default = None)
				Focus (default = None)
			Drived by obstruction, occlussion, diffraction and transmission (curve for each depending on driver; 12 more in total): default = UseProjectDriverValue
				Volume
				LPF
				HPF
	*/

	enum class CurveOption : int8_t {
		UseOutputBusVolume, // always 0 on Bus Volume
		Custom, // needs to specify the curve index instead?
		None = -1,
		UseProjectDriverValue = -2, // Use Proejct Obstruction or Use Project Occlusion
	};

	AttenuationCurve::AttenuationCurve(Reader& reader) {
		reader.Read(&curve_scaling);
		rtpc_graph = RTPCGraph(reader);
	}

	void AttenuationCurve::Convert(Writer& writer) {
		writer << curve_scaling;
		rtpc_graph.Convert(writer);
	}

	ConeParams::ConeParams(Reader& reader) {
		reader.Read(&inside_degrees);
		reader.Read(&outside_degrees);
		reader.Read(&outside_volume);
		reader.Read(&lo_pass);

		if (VERSION > BankVersion::V2013) {
			hi_pass = reader.Read<float>();
		}
	}

	void ConeParams::Convert(Writer& writer) {
		writer << inside_degrees;
		writer << outside_degrees;
		writer << outside_volume;
		writer << lo_pass;

		if (CONVERT_VERSION > BankVersion::V2013) {
			writer << (float)0; // high pass attenuation
		}
	}

	HIRCAttenuation::HIRCAttenuation(Reader& reader)
		: item_base(reader)
	{
		if (VERSION == BankVersion::V2022) {
			height_spread_enabled = reader.Read<uint8_t>();
		}

		reader.Read(&cone_enabled);
		if (cone_enabled == 1) {
			cone_params = ConeParams(reader);
		}

		int num_curves = 0;
		switch (VERSION) {
		case BankVersion::V2013:
			num_curves = 5;
			break;
		case BankVersion::V2015:
			num_curves = 7;
			break;
		case BankVersion::V2022:
			num_curves = 19;
			break;
		}

		curve_to_use.resize(num_curves);
		reader.Read(curve_to_use.data(), sizeof(int8_t) * num_curves);
		reader.Read(&num_defined_curves);

		if (num_defined_curves > 0) {
			curves.emplace();
		}

		for (uint8_t i = 0; i < num_defined_curves; i++) {
			curves.value().push_back(AttenuationCurve(reader));
		}

		rtpcs = InitialRTPC(reader);
	}

	void HIRCAttenuation::Convert(Writer& writer) {
		item_base.Convert(writer);

		if (CONVERT_VERSION == BankVersion::V2022) {
			writer << (uint8_t)1; // height spread (introduced 2021, default true)
		}

		writer << cone_enabled;
		if (cone_enabled == 1) {
			cone_params.value().Convert(writer);
		}

		// curves		
		writer.Write(*curve_to_use.data(), sizeof(int8_t) * 4); // shared curves among versions
		if (VERSION == BankVersion::V2013) {
			// write everything else as default values except for Spread
			writer << CurveOption::None; // HPF
			writer << curve_to_use[4]; // Spread
			writer << CurveOption::None; // Focus

			if (CONVERT_VERSION == BankVersion::V2022) {
				for (int i = 0; i < 4; i++) { // obstruction, occlussion, diffraction and transmission curves defaults
					writer << CurveOption::UseProjectDriverValue; // Volume
					writer << CurveOption::UseProjectDriverValue; // LPF
					writer << CurveOption::UseProjectDriverValue; // HPF
				}
			}
		}
		else if (VERSION == BankVersion::V2015) {
			writer << curve_to_use[3]; // HPF
			writer << curve_to_use[4]; // Spread
			writer << curve_to_use[5]; // Focus

			for (int i = 0; i < 4; i++) { // obstruction, occlussion, diffraction and transmission curves defaults
				writer << CurveOption::UseProjectDriverValue; // Volume
				writer << CurveOption::UseProjectDriverValue; // LPF
				writer << CurveOption::UseProjectDriverValue; // HPF
			}
		}

		writer << num_defined_curves;
		for (uint8_t i = 0; i < num_defined_curves; i++) {
			curves.value()[i].Convert(writer);
		}

		rtpcs.Convert(writer);

		item_base.UpdateSize(writer);
	}
}