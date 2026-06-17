#pragma once
#include "common.h"

namespace Wwise {
	struct RTPCGraphCurve {
		uint32_t curve_size;
		std::vector<RTPCGraphPoint> points;

		void Convert(Writer& writer);
		RTPCGraphCurve() = default;
		RTPCGraphCurve(Reader& reader);
	};

	struct LayerAssociatedChildren {
		uint32_t associated_child_id;
		RTPCGraphCurve rtpc_graph;

		void Convert(Writer& writer);
		LayerAssociatedChildren() = default;
		LayerAssociatedChildren(Reader& reader);
	};

	struct Layer {
		uint32_t layer_id;
		InitialRTPC initial_rtpc;
		uint32_t rtpc_id;

		// 2015, 2022
		std::optional<std::variant<RTPCType2015, RTPCType2022>> rtpc_type;

		uint32_t num_associated_children;
		std::vector<LayerAssociatedChildren> associated_children;

		void Convert(Writer& writer);
		Layer() = default;
		Layer(Reader& reader);
	};

	struct HIRCLayerContainer {
		HIRCItemGeneric item_base;
		BaseParams base_params;
		Children children;

		uint32_t num_layers;
		std::vector<Layer> layers;

		// 2022
		std::optional<uint8_t> is_continuous_validation;

		void Convert(Writer& writer);
		HIRCLayerContainer(Reader& reader);
	};
}