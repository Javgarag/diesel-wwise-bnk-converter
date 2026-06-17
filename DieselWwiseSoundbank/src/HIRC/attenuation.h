#pragma once
#include "common.h"

namespace Wwise {
	struct ConeParams {
		float inside_degrees;
		float outside_degrees;
		float outside_volume;
		float lo_pass;

		// > 2013
		std::optional<float> hi_pass;

		void Convert(Writer& writer);
		ConeParams(Reader& reader);
	};

	struct AttenuationCurve {
		CurveScaling curve_scaling;
		RTPCGraph rtpc_graph;

		void Convert(Writer& writer);
		AttenuationCurve(Reader& reader);
	};

	struct HIRCAttenuation {
		HIRCItemGeneric item_base;

		// 2022
		std::optional<uint8_t> height_spread_enabled;
		uint8_t cone_enabled;
		std::optional<ConeParams> cone_params;
		uint8_t num_curves;

		// length of this vector: 5 (2013), 7 (2015), 19 (2022)
		std::vector<int8_t> curve_to_use;

		uint8_t num_defined_curves;
		std::optional<std::vector<AttenuationCurve>> curves;

		InitialRTPC rtpcs;

		void Convert(Writer& writer);
		HIRCAttenuation(Reader& reader);
	};
}