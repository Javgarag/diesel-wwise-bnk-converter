#include "switch_container.h"

namespace Wwise {
	SwitchPackage::SwitchPackage(Reader& reader) {
		reader.Read(&switch_id);
		reader.Read(&num_items);
		for (uint32_t i = 0; i < num_items; i++) {
			node_id_list.push_back(reader.Read<uint32_t>());
		}
	}

	void SwitchPackage::Convert(Writer& writer) {
		writer << switch_id;
		writer << num_items;
		for (uint32_t i = 0; i < num_items; i++) {
			writer << node_id_list[i];
		}
	}

	SwitchParams::SwitchParams(Reader& reader) {
		reader.Read(&node_id);
		if (VERSION == BankVersion::V2013) {
			is_first_only = reader.Read<uint8_t>();
			continue_playback = reader.Read<uint8_t>();
			on_switch_mode = reader.Read<uint32_t>();
		}
		else {
			bit_vector1 = reader.Read<SwitchByBitVector1>(sizeof(uint8_t));
			bit_vector2 = reader.Read<SwitchByBitVector2>(sizeof(uint8_t));
		}
		reader.Read(&fade_out_time);
		reader.Read(&fade_in_time);
	}

	void SwitchParams::Convert(Writer& writer) {
		writer << node_id;

		if (VERSION == BankVersion::V2013) {
			uint8_t bit_flag_1 = 0;
			bit_flag_1 |= (is_first_only.value() << 0);
			bit_flag_1 |= (continue_playback.value() << 1);
			writer << bit_flag_1;

			uint8_t bit_flag_2 = 0;
			bit_flag_2 |= (on_switch_mode.value() << 0);
			writer << bit_flag_2;
		}
		else {
			writer.Write(bit_vector1, sizeof(uint8_t));
			writer.Write(bit_vector2, sizeof(uint8_t));
		}

		writer << fade_out_time;
		writer << fade_in_time;
	}

	HIRCSwitchContainer::HIRCSwitchContainer(Reader& reader)
		: item_base(reader),
		base_params(reader)
	{
		if (VERSION == BankVersion::V2013) {
			group_type = reader.Read<uint32_t>();
		}
		else {
			group_type = reader.Read<uint8_t>();
		}

		reader.Read(&group_id);
		reader.Read(&default_switch);
		reader.Read(&is_continuous_validation);
		children = Children(reader);

		reader.Read(&num_switch_groups);
		for (uint32_t i = 0; i < num_switch_groups; i++) {
			switch_list.push_back(SwitchPackage(reader));
		}
		reader.Read(&num_switch_params);
		for (uint32_t i = 0; i < num_switch_params; i++) {
			switch_params.push_back(SwitchParams(reader));
		}
	}

	void HIRCSwitchContainer::Convert(Writer& writer) {
		item_base.Convert(writer);
		base_params.Convert(writer);
		
		if (VERSION == BankVersion::V2013) {
			writer << (uint8_t)std::get<uint32_t>(group_type);
		}
		else {
			writer << std::get<uint8_t>(group_type);
		}

		writer << group_id;
		writer << default_switch;
		writer << is_continuous_validation;
		children.Convert(writer);

		writer << num_switch_groups;
		for (uint32_t i = 0; i < num_switch_groups; i++) {
			switch_list[i].Convert(writer);
		}

		writer << num_switch_params;
		for (uint32_t i = 0; i < num_switch_params; i++) {
			switch_params[i].Convert(writer);
		}

		item_base.UpdateSize(writer);
	}
}