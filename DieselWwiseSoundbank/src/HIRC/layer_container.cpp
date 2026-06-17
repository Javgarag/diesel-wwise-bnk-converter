#include "layer_container.h"

namespace Wwise {
	RTPCGraphCurve::RTPCGraphCurve(Reader& reader) {
		reader.Read(&curve_size);
		for (uint32_t i = 0; i < curve_size; i++) {
			points.push_back(RTPCGraphPoint(reader));
		}
	}

	void RTPCGraphCurve::Convert(Writer& writer) {
		writer << curve_size;
		for (uint32_t i = 0; i < curve_size; i++) {
			points[i].Convert(writer);
		}
	}

	LayerAssociatedChildren::LayerAssociatedChildren(Reader& reader) {
		reader.Read(&associated_child_id);
		rtpc_graph = RTPCGraphCurve(reader);
	}

	void LayerAssociatedChildren::Convert(Writer& writer) {
		writer << associated_child_id;
		rtpc_graph.Convert(writer);
	}

	Layer::Layer(Reader& reader) {
		reader.Read(&layer_id);
		initial_rtpc = InitialRTPC(reader);
		reader.Read(&rtpc_id);

		if (VERSION == BankVersion::V2015) {
			reader.Read(&rtpc_type.emplace().emplace<RTPCType2015>(), sizeof(RTPCType2015));
		}
		else if (VERSION == BankVersion::V2022) {
			reader.Read(&rtpc_type.emplace().emplace<RTPCType2022>(), sizeof(RTPCType2022));
		}

		reader.Read(&num_associated_children);
		for (uint32_t i = 0; i < num_associated_children; i++) {
			associated_children.push_back(LayerAssociatedChildren(reader));
		}
	}

	void Layer::Convert(Writer& writer) {
		writer << layer_id;
		initial_rtpc.Convert(writer);
		writer << rtpc_id;

		if (rtpc_type.has_value()) {
			std::visit([&](auto& rtpc_type) {
				writer.Write(rtpc_type, sizeof(uint8_t));
				}, rtpc_type.value());
		}
		else { // 2013
			writer << RTPCType2015::GameParameter;
		}

		writer << num_associated_children;
		for (uint32_t i = 0; i < num_associated_children; i++) {
			associated_children[i].Convert(writer);
		}
	}

	HIRCLayerContainer::HIRCLayerContainer(Reader& reader)
		: item_base(reader),
		base_params(reader),
		children(reader)
	{
		reader.Read(&num_layers);
		for (uint32_t i = 0; i < num_layers; i++) {
			layers.push_back(Layer(reader));
		}

		if (VERSION == BankVersion::V2022) {
			is_continuous_validation = reader.Read<uint8_t>();
		}
	}

	void HIRCLayerContainer::Convert(Writer& writer) {
		item_base.Convert(writer);
		base_params.Convert(writer);
		children.Convert(writer);

		writer << num_layers;
		for (uint32_t i = 0; i < num_layers; i++) {
			layers[i].Convert(writer);
		}

		if (CONVERT_VERSION == BankVersion::V2022) {
			writer << (uint8_t)0; // is_continuous_validation
		}

		item_base.UpdateSize(writer);
	}
}